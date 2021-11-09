.include "m328def.inc"

;запись в регистр (через temp)
.MACRO	_ldi
		ldi		temp, @1
		mov		@0, temp		
.ENDM

;запись в порт (через temp)
.MACRO	_out
		ldi		temp, @1
		out		@0, temp		
.ENDM

;запись в порт (через temp2)
.MACRO	_out2
		ldi		temp2, @1
		out		@0, temp2	
.ENDM

;запись в порт (через temp)
.MACRO	_outm
		ldi		temp, @1
		sts		@0, temp		
.ENDM

;запись в порт (через temp)
.MACRO	_rclr
		out		@0, zero
.ENDM


;запись WORD в порт (через temp) RL, RH, VAL
.MACRO	_outw
		_out	@1, high(@2)
		_out	@0, low(@2)
.ENDM

;запись WORD в порт (через temp) RL, RL, VAL
.MACRO	_outwm
		_outm	@1, high(@2)
		_outm	@0, low(@2)
.ENDM


//	delay for 3,6,9,12,... cycles
.MACRO 	delay3 //1=3 2=1+1*3+2
		ldi		temp, @0/3		//+1
_dlloop:
		dec		temp				//+1
		brne	_dlloop				//+2/1
.ENDM

.MACRO INSPI
		sbi		PORTB, PB1			// err=1
l_inspi:			
    in		temp, SPSR
		sbrs	temp, SPIF
		rjmp	l_inspi					// waiting for data
		in		@1, SPDR
		_out	SPDR, @0
		cbi		PORTB, PB1			// err=0
.ENDM


// program part
.CSEG
		// var definition
		.DEF	zero	 =r3		// 0
		.DEF	maxslH	 =r4
		.DEF	maxslL	 =r5

		.DEF	charsize =r6		// 19 or 20
		.DEF	linesno	 =r7		// 24 or 25

		.DEF	cpptrH	 =r8
		.DEF	cpptrL	 =r9		// codepage pointer

		.DEF	crc0	 =r10
		.DEF	crc1	 =r11

		.DEF	temp2	 =r16
		.DEF	temp	 =r17
		.DEF	line	 =r18
		.DEF	inchar	 =r19
		.DEF	lmode 	 =r20
		.DEF	temp3	 =r21

		.DEF	sline	 =r22
		.DEF	stroke	 =r23
		.DEF	RPTR 	 =r24
		.DEF	RPTRH 	 =r25


// BOOTLODER --------------------------------------------------------------------
// 256 words bootloader

.EQU	SPMEN = SELFPRGEN

.CSEG
.ORG	0x3F00

		_outw	SPL, SPH, RAMEND

		_out 	PORTB, (1<<PB2)|(1<<PB4)|(1<<PB5)|(1<<PB1)	// PUs for SPI bus
		_out 	DDRB, (1<<PB4)|(1<<PB1)	// MISO, ERR to out

		sbi		PORTB, PB1			// err=1

		sbic	PINB, PB2				// check programming request (SS=0)
		jmp		0								// go to normal operation if no

		cbi		PORTB, PB1			// err=0
		_out	DDRC, 0					// C to In

		cbi		PORTC, PC2			// suppress HS VS generation pulling down RESET AT13
		_out 	DDRC, (1<<PC2)	// hs disable pin

		_out	SPCR, (1<<SPE)	// SPI enable Slave mode

		cbi		PORTC, PC0			// notify rtr state
		_out 	DDRC, (1<<PC0)	// 

BL1:	
		_out	SPDR, 'C'				// clear to send

		ldi		XH, 1
		ldi		XL, 0				    // restore memory buffer address
		ldi		ZL, 0

BL91:	
		INSPI	'C', lmode      // waiting for data, loading mode

		cpi		lmode, 0xFF			// check for dummy filler
		breq	BL91						// if any wait for next byte

		cpi		lmode, 0x80			// check for run directive
		brne	BL2             // proceed if not requested to quit

;		_out	SPCR, 0         // stop spi
		rjmp	BL1

BL2:

		INSPI	'A', ZH				  // get address

		// getting 128 byte buffer
BL5:	
    INSPI	'W', inchar
		st		X+, inchar
		cpi		XL, 128
		brlo	BL5					// loading 128 bytes of data

		ldi		XH, 1
		ldi		XL, 0				// restore memory buffer address

		cpi		lmode, '5'
		breq	BL6					// CSEG overwrite requested

		cpi		lmode, '6'
		breq	BL8					// ESEG overwrite requested

		rjmp		BL1

BL6:	// writing to memory
		lsr		ZH
		ror		ZL					// move page number to 13:6 bits of PCPAGE (12:1 bits of Z)
		movw	Y, Z				// storing for future use	

		ldi 	temp, (1<<PGERS) | (1<<SPMEN)
		call 	DOSPM				// erase page Z
		ldi 	temp, (1<<RWWSRE) | (1<<SPMEN)
		call 	DOSPM				// erase page Z

		ldi		line, 64			// counter 64 words - page size for ATmega328

BL7:	// loading new data
		ld		r0, X+
		ld		r1, X+

		ldi		temp, 1<<SPMEN
		call	DOSPM			// write to temporary buffer

		adiw 	Z, 2				// Z counts in bytes !!!
		dec		line
		brne	BL7

		movw	Z, Y				// restore original Z

		ldi		temp, (1<<SPMEN)|(1<<PGWRT)
		call 	DOSPM				// store data in Flash
		ldi 	temp, (1<<RWWSRE) | (1<<SPMEN)
		call 	DOSPM				// store data in Flash

BL71: // verify that RWW section is safe to read
		in 		temp, SPMCSR
		sbrs 	temp, RWWSB ; If RWWSB is set, the RWW section is not ready yet
		rjmp	BL11
		; re-enable the RWW section
		ldi 	temp, (1<<RWWSRE) | (1<<SPMEN)
		call 	DOSPM
		rjmp 	BL71


BL11:	
		rjmp	BL1					// ready to next block


// storing buffer in EEPROM
BL8:	
		lsr		ZH
		ror		ZL					// move page number to 13:6 bits of PCPAGE (12:1 bits of Z)
		movw	Y, Z				// storing for future use	
		ldi		line, 128			// counter 128 bytes

BL10:
BL9:	
    sbic 	EECR, EEPE
		rjmp 	BL9					// Wait for completion of previous write

		out		EEARH, ZH
		out		EEARL, ZL

		ld		inchar, X+			// get next byte

		out 	EEDR, inchar		// Write data to Data Register
		sbi 	EECR, EEMPE			// Write logical one to EEMPE
		sbi 	EECR, EEPE			// Start eeprom write by setting EEPE

		adiw 	Z, 1
		dec		line
		brne	BL10				// procedd for all 128 bytes

		rjmp	BL11				// Send CONFIRM and wait for next block
		

// SPM routines -----------------------------------------
DOSPM:
		in 		temp2, SPMCSR
		sbrc 	temp2, SPMEN
		rjmp 	DOSPM

		out 	SPMCSR, temp
		spm

		ret

