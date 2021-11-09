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
;		sbi		PORTC, PC5
l_inspi:			
    in		temp, SPSR
		sbrs	temp, SPIF
		rjmp	l_inspi					// waiting for data
		in		@1, SPDR
		_out	SPDR, @0
;		cbi		PORTC, PC5
.ENDM


// send byte to UART0 (using temp)
.MACRO	send
		ldi		temp, @0
		call	UART_SEND
.ENDM

.MACRO tdelay
	  _out	TCNT0, 0			// reset timeout counter
tdl:	
    in		temp, TCNT0
		cpi		temp, @0			// waiting approx 10 ms
		brlo	tdl						// reutrn to main program in timeout detected
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

		.DEF  vga_pgm = r15		// =1 when VGA is restarted

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
// 512 words bootloader

.EQU	SPMEN = SELFPRGEN

.CSEG
.ORG	0x3E00

		_outw	SPL, SPH, RAMEND

		_out 	DDRB, (1<<PB4)		// MISO

;		_out 	DDRC, (1<<PC5)		; !!! For tests!!!
;		cbi		PORTC, PC5

		_outm	UBRR0H, 0
		_outm	UBRR0L, 21		// 57600 at 20MHz	
		_outm	UCSR0C, (1<<UCSZ01) | (1<<UCSZ00)		// 8 bit no parity 1 stop bit
		_outm	UCSR0B, (1<<RXEN0) | (1<<TXEN0)			// Tx and Rx enabled

		ldi		temp,0 
		mov		vga_pgm, temp
		
		_out	SPCR, (1<<SPE)		// SPI enable Slave mode
		_out	SPDR, 'C'					// clear to send

;		_out	TCCR0B, (1<<CS02) | (0<<CS01) | (1<<CS00) // start timer 0 with /1024 prescaler

BL1:	

		ldi		XH, 1
		ldi		XL, 0				    // restore memory buffer address
		ldi		ZL, 0

BL91:	
		INSPI	'C', lmode      // waiting for data, loading mode

		cpi		lmode, 0xFF			// check for dummy filler
		breq	BL91						// if any wait for next byte

		cpi		lmode, 0x80			// check for run directive
		brne	BL2             // proceed if not requested to quit

		_out	SPCR, 0         // stop spi
;		_out	TCCR0B, 0			// stop timer
		jmp		0

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

    send	13
		mov		temp, lmode
		call 	UART_SEND
		mov		temp, ZH
		call 	UART_SEND
		send  13
		ldi		line, 128
BL_9:	
		ld		temp, X+			// get next byte
		call 	UART_SEND
		dec		line
		brne	BL_9				// procedd for all 128 bytes

		ldi		XH, 1
		ldi		XL, 0				// restore memory buffer address		

;		rjmp	BL5

		cpi		lmode, '3'
		breq	BL6					// CSEG overwrite requested

		cpi		lmode, '4'
		breq	BL8					// ESEG overwrite requested

		jmp		SEND_VGA		// pass other commands to VGA controller


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
;		INSPI 'C', temp		// return Ready
		rjmp	BL1					// ready to next block


// storing buffer in EEPROM
BL8:	
;    send	13
;		mov		temp, lmode
;		call 	UART_SEND
;		mov		temp, ZH
;		call 	UART_SEND

		lsr		ZH
		ror		ZL					// move page number to 13:6 bits of PCPAGE (12:1 bits of Z)
		movw	Y, Z				// storing for future use	
		ldi		line, 128			// counter 128 bytes

		mov		temp, ZH
		call 	UART_SEND
		mov		temp, ZL
		call 	UART_SEND

BL10:
BL9:	
    sbic 	EECR, EEPE
		rjmp 	BL9			    		// Wait for completion of previous write

		out		EEARH, ZH
		out		EEARL, ZL

		ld		inchar, X+			// get next byte

		out 	EEDR, inchar		// Write data to Data Register
		sbi 	EECR, EEMPE			// Write logical one to EEMPE
		sbi 	EECR, EEPE			// Start eeprom write by setting EEPE

		mov		temp, inchar
		call 	UART_SEND
		
		adiw 	Z, 1
		dec		line
		brne	BL10				// proceed for all 128 bytes

		rjmp	BL11				// Send CONFIRM and wait for next block
		

// SPM routines -----------------------------------------
DOSPM:
		in 		temp2, SPMCSR
		sbrc 	temp2, SPMEN
		rjmp 	DOSPM

		out 	SPMCSR, temp
		spm

		ret


SEND_VGA:
    ; PC3 = CS, PC2 = MOSI, PC1 = MISO, PC0 = CLK

    send	13
    send	'V'

    mov		temp, vga_pgm
    call	UART_SEND

		_ldi	r0, (0<<PC0)			// clk 0
		_ldi	r1, (1<<PC0)			// clk 1

		_ldi	r2, (0<<PC0)|(0<<PC2)|(1<<PC3)|(1<<PC1)			// start state PU for MISO
		out		PORTC, r2								// start state
		_out	DDRC, (1<<PC3)|(1<<PC2)|(1<<PC0)		// set pins directions

		_out	DDRD, 0       // Port D to In
		sbi 	PORTD, PD3		// pull-up on D3 pin

		or		vga_pgm, vga_pgm
		brne	SV12								; skip if VGA already reseted

    send	'R'

		cbi		PORTD, PD5
		sbi		DDRD, PD5			// reset VGA


		cbi		PORTC, PC3		// set progr request
;		sbi		DDRC, PC3			// pull SS down to say that it will be programmed
		delay3	30

		cbi		DDRD, PD5			// restore VGA

		delay3	9
    send	'r'

SV11:
		sbic	PIND, PD3			// wait rtr confirmation
		rjmp	SV11				

		sbi		PORTC, PC3		// initial state - reset VGA SPI

		send	'A'

		ldi		temp, 1
		mov		vga_pgm, temp	// VGA is in SPI mode

SV12:
		_ldi	r2, (0<<PC0)|(0<<PC2)|(0<<PC3)|(1<<PC1)			// pause state
		delay3 9

		out   PORTC, r2
;		cbi		PORTC, PC3		// CS=0

		send	's'

SV2:	// waiting for confirmation
		ldi		temp, 0xFF
		call 	VGA_SPI_SEND
		cpi		temp3, 'C'
		brne	SV2

		mov		temp, lmode
		call 	VGA_SPI_SEND		// send command

		mov		temp, ZH
		call 	VGA_SPI_SEND

		send	'B'
		send	13

		ldi		line, 128			// counter 128 bytes
SV1:
		ld		temp, X+			// get next byte
		call 	VGA_SPI_SEND
    call	UART_SEND
		dec		line
		brne	SV1					// procedd for all 128 bytes

		sbi		PORTC, PC3	// CS=1

		jmp		BL11				// send confirm


.MACRO  VGA_SPI_CLK
		bst		temp, @0
		bld		r0, PC2				// set
		out		PORTC, r0			// clk0
		nop
		bld		r1, PC2				// set
		out		PORTC, r1			// clk1
		sbic	PINC, PC1
		sbr		temp3, 1<<@0	// read bit
.ENDM

VGA_SPI_SEND:
		clr		temp3
		VGA_SPI_CLK	7
		VGA_SPI_CLK	6
		VGA_SPI_CLK	5
		VGA_SPI_CLK	4
		VGA_SPI_CLK	3
		VGA_SPI_CLK	2
		VGA_SPI_CLK	1
		VGA_SPI_CLK	0
		out		PORTC, r2      // pause state
		ret

UART_SEND:
		sts		UDR0, temp
US1:	
    lds		temp, UCSR0A
		sbrs	temp, UDRE0
		rjmp	US1
		ret
