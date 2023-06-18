.include "m1284pdef.inc"

;запись в порт (через temp)
.MACRO	_out
	ldi	temp, @1
	out	@0, temp		
.ENDM

;запись в порт (через temp)
.MACRO	_outm
	ldi	temp, @1
	sts	@0, temp		
.ENDM

;запись WORD в порт (через temp) RL, RH, VAL
.MACRO	_outw
	_out	@1, high(@2)
	_out	@0, low(@2)
.ENDM

; send byte to UART0 (using temp)
.MACRO	send
	ldi	temp, @0
	call	UART_SEND
.ENDM

; read data from UART0 (using temp)
.MACRO	receive
BL1:	
    	lds	temp, UCSR0A
	sbrs	temp, RXC0
	rjmp	BL1				; waiting for data
	lds	@0, UDR0			; loading mode received to lmode
.ENDM

;	delay for 3,6,9,12,... cycles
.MACRO 	delay3 ;1=3 2=1+1*3+2
	ldi	temp, @0/3	; +1
_dlloop:
	dec	temp		; +1
	brne	_dlloop		; +2/1
.ENDM

.MACRO 	tdelay
	_out	TCNT0, 0			; reset timeout counter
tdl:	
    	in	temp, TCNT0
	cpi	temp, @0			; waiting approx 10 ms
	brlo	tdl				; reutrn to main program in timeout detected
.ENDM

.MACRO 	beep
	_outm	UCSR0B, 0			; disable UART
	cbi	PORTD, PD1
_out	PORTB, 	(1<<PB1)|(1<<PB0)|(1<<PB3)  	; select BUZZER
	rcall	TDELAY250	;tdelay 	250
	rcall	TDELAY250	;tdelay 	250
	rcall	TDELAY250	;tdelay 	250
	_out	PORTB, 0xFF  			; deselect BUZZER
	sbi	PORTD, PD1
	tdelay	64
	_outm	UCSR0B, (1<<RXEN0)|(1<<TXEN0)	; Tx and Rx reenabled
.ENDM

.MACRO 	SPI_START_PCU
	tdelay 32
	_outm	UCSR0B, 0			; disable UART
	cbi	PORTD, PD1  			; E2=0
	; enable SPI
;	_out	SPSR, (1<<SPI2X)		; Double speed
	_out	SPCR, (1<<SPE)|(1<<MSTR)	; Start SPI in Master Mode 20/4 MHz
	_out	PORTB, (1<<PB3)  		; select PCU
.ENDM

.MACRO 	SPI_START_CLR
	tdelay 32
	_outm	UCSR0B, 0			; disable UART
	cbi	PORTD, PD1  			; E2=0
	; enable SPI
;	_out	SPSR, (1<<SPI2X)		; Double speed
	_out	SPCR, (1<<SPR1)|(1<<SPE)|(1<<MSTR)	; Start SPI in Master Mode 20/64 MHz
	_out	PORTB, (1<<PB0)|(1<<PB1)|(1<<PB2)  	; select CLR
.ENDM


	.DEF	temp2	= r16
	.DEF	temp	= r17
	.DEF	line	= r18
	.DEF	inchar	= r19
	.DEF	lmode 	= r20
	.DEF	temp3	= r21

.CSEG
.ORG	0xFE00	; 512 words bootloader

START:
	; switch on SIG lamp
	_out	PORTB, (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)
	_out	DDRB, (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)|(1<<PB4)|(1<<PB7)|(1<<PB5)

	; CE2 for bus decoder and buzzer
	_out	PORTD, (1<<PD1)	
	_out	DDRD, (1<<PD1)

	; enable timer
	_out	TCCR0B, (1<<CS02)|(0<<CS01)|(1<<CS00) ; start timer 0 with /1024 prescaler

	_out	PORTB, (1<<PB1)|(1<<PB2)|(1<<PB3)	; reset CPD command
	cbi	PORTD, PD1			; reset pulse start

	; start-up delay to start pripherials
	ldi	temp3, 200
BL01:
	rcall	TDELAY250	;tdelay 250
	sbi	PORTD, PD1			; reset pulse end
	_out	PORTB, (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)	; SIG lamp on 
	cbi	PORTD, PD1			; SIG on
	dec	temp3
	brne	BL01

	sbi	PORTD, PD1			; SIG off

	; enable UART
	_outm	UBRR0H, 0
	_outm	UBRR0L, 21			; 12 = 38400 at 8MHz	// 21 = 57600 at 20MHz // 10 = 115200 bod at 20MHz
	_outm	UCSR0C, (1<<UCSZ01)|(1<<UCSZ00)	; 8 bit no parity 1 stop bit
	_outm	UCSR0B, (1<<RXEN0)|(1<<TXEN0)	; Tx and Rx enabled

	; Stack pointer settings --------------------------------------
	_outw	SPL, SPH, RAMEND

BL4:
	; switch on SIG lamp
	_out	PORTB, (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3)

	clr	temp3
	rcall	TDELAY250	;tdelay 	250
		
	ldi	XH, 1
	ldi	XL, 0				; memory buffer for loading

	send	'R'				; send Ready
BL1:	
	rcall	TDELAY250	;tdelay 250
	inc	temp3
	cpi	temp3, 250
	brlo	BL1_GO		; goto UART check 
	rjmp	BL2		; timeout - return to ain program

BL1_GO:	
	lds	temp, UCSR0A
	sbrs	temp, RXC0
	rjmp	BL1				; waiting for data

	lds	lmode, UDR0			; loading mode received to lmode

	cpi	lmode, 0xFF			; check for dummy filler
	breq	BL4				; if any wait for next byte

	cpi	lmode, 'Q'			; check for quit command
	brne	BL15				; proceed if not Q

	rjmp  BL2             			; goto 0

BL15:
	send	'A'				; reply for confirm and address block request

	receive	ZH				; page address (!!!) received
	ldi	Zl, 0
	movw	Y, Z				; storing for future use

	send	0xFF				; dummy reply for start data block
	ldi	line, 0				; 256 bytes for MCU

	cpi	lmode, '3'
	brlo	BL5				; MCU overwrite requested

	cpi	lmode, '7'
	brlo	BL5_128				; CPD or VGA overwrite requested

	ldi	line, 64			; for programming CLR just 64 bytes required
	rjmp	BL5

BL5_128:	
	ldi	line, 128			; for programming PCU just 128 bytes required

	; getting 256/128 byte buffer
BL5:	
	receive	inchar
	mov	temp, inchar
	call	UART_SEND 
	st	X+, inchar
	cp	XL, line
	brne	BL5				; loading 256/128 bytes of data

	send	'W'				; Notify that working for updates

	ldi	XH, 1
	ldi	XL, 0				; restore memory buffer address

	cpi	lmode, '2'
	brlo	_BL6				; CSEG overwrite requested
	breq	_BL8				; ESEG overwrite requested
	rjmp	BL12				; other commands just pass to PDU

_BL6:	rjmp	BL6
_BL8:	rjmp	BL8
	; otherwise return to main code (unknown command)	
	; final, no command received
BL2:

	send	'Q'				; Quiting
	beep

	SPI_START_PCU
	ldi	temp, 0x80			; command to PCU to start
	call 	DOSPI		    		; send command

	_out	TCCR0B, 0			; stop timer
	_outm	UCSR0B, 0			; disable UART
	_out	DDRB, 0
	_out	DDRD, 0
	_out	SPCR, 0				; Stop SPI
	jmp	0				; goto main program

BL8: 	; write to eeprom
	jmp	BL81

BL6:	; writing to FLASH memory

	mov	temp, lmode
	subi	temp, '0'
	out	RAMPZ, temp			; selecting low or high 64k block

	ldi 	temp, (1<<PGERS) | (1<<SPMEN)
	call 	DOSPM				; erase page Z
	ldi 	temp, (1<<RWWSRE) | (1<<SPMEN)
	call 	DOSPM				; re-enable the RWW section
	send 	':'

	ldi	line, 128			; counter 128 words - page size

BL7:	; loading new data
	ld	r0, X+
	ld	r1, X+

	ldi	temp, 1<<SPMEN
	call	DOSPM				; write to temporary buffer
	send 	'.'

	adiw 	Z, 2				; Z counts in bytes !!!
	dec	line
	brne	BL7

	movw	Z, Y				; restore original Z

	ldi	temp, (1<<SPMEN)|(1<<PGWRT)
	call 	DOSPM				; store data in Flash
	ldi 	temp, (1<<RWWSRE) | (1<<SPMEN)
	call 	DOSPM				; re-enable the RWW section

BL71:	; verify that RWW section is safe to read
	in 	temp, SPMCSR
	sbrs 	temp, RWWSB 			; If RWWSB is set, the RWW section is not ready yet
	rjmp	BL11
	; re-enable the RWW section
	ldi 	temp, (1<<RWWSRE) | (1<<SPMEN)
	call 	DOSPM
	rjmp 	BL71

BL11:
	send	'C'				; return Compleated
	beep
	rjmp	BL4				; ready to next block

BL81:	; storing buffer in EEPROM
	ldi		line, 0			; counter 256 bytes
	send 	':'

BL10:
BL9:	
    	sbic 	EECR, EEPE
	rjmp 	BL9				; Wait for completion of previous write

	out	EEARH, ZH
	out	EEARL, ZL

	ld	inchar, X+			; get next byte

	out 	EEDR, inchar			; Write data to Data Register
	sbi 	EECR, EEMPE			; Write logical one to EEMPE
	sbi 	EECR, EEPE			; Start eeprom write by setting EEPE
		
	send 	'.'

	adiw 	Z, 1
	dec	line
	brne	BL10				; procedd for all 128 bytes

	rjmp	BL11				; Send CONFIRM and wait for next block


BL12:	; pass data to PCU or CLR
	send	'F'				; forwrd data notification

	cpi	lmode, '7'			; CLR controller?
	brlo	BL_CPD				; 3,4,5,6 passed to CPU

	; reset CLR to enter bootloader mode
	_out	PORTB, (1<<PB1)|(1<<PB2)	; Y6 - CLR version only!!!!!
	cbi	PORTD, PD1			; reset CLR pulse start
	nop
	nop
	nop
	nop	
	in	temp, PIND
	sbi	PORTD, PD1			; reset CLR pulse stop
	sbrc	temp, 6				; check EXT version
	rjmp	BL11				; skip command - but returns OK
	rcall	TDELAY250	;tdelay 250	; 1/76 s
	rcall	TDELAY250	;tdelay 250	; 1/76 s
	rcall	TDELAY250	;tdelay 250	; 1/76 s
	rcall	TDELAY250	;tdelay 250	; 1/76 s
	rcall	TDELAY250	;tdelay 250	; 1/76 s
	rcall	TDELAY250	;tdelay 250	; 1/76 s - time to start
	
BL_CLR: 					; 7,8 passed to CLR
	SPI_START_CLR
	ldi	line, 64			; counter 64 bytes
	rjmp	BL141

BL_CPD:
	SPI_START_PCU
	ldi	line, 128			; counter 128 bytes

BL141:
	delay3	30
	ldi	temp, 0xFF
	call 	DOSPI
	cpi	temp, 'C'
	brne	BL141				; waiting for clearance

	mov	temp, lmode
	call 	DOSPI			   	; send command
	delay3	30

;	ldi	line, 128			; counter 128 bytes

	mov	temp, ZH
	call 	DOSPI				; send page address
	delay3	30

BL13:
	ld	temp, X+			; get next byte
	call 	DOSPI				; send via SPI
	delay3	12
	dec 	line
	brne	BL13

BL14:
	delay3	30

	sbi	PORTB, PB4			; SS to high
	_out	SPCR, 0				; disable SPI
	   
	sbi	PORTD, PD1  			; E2=1
	tdelay	64
	_outm	UCSR0B, (1<<RXEN0) | (1<<TXEN0)	; Tx and Rx reenabled
		
	rjmp	BL11				; Send CONFIRM and wait for next block

		
	; SPM routines -----------------------------------------
DOSPM:
	in 	temp2, SPMCSR
	sbrc 	temp2, SPMEN
	rjmp 	DOSPM

	out 	SPMCSR, temp
	spm

	ret 

	; --------------------------------------------------------
UART_SEND:
	sts	UDR0, temp
US1:	
	lds	temp, UCSR0A
	sbrs	temp, UDRE0
	rjmp	US1
	ret


	; --------------------------------------------------------
DOSPI:
SPI_SEND:
	out	SPDR, temp
SS1:	
	in	temp, SPSR
	sbrs	temp, SPIF
	rjmp	SS1
	in	temp, SPDR
	ret

	; --------------------------------------------------------

TDELAY250:
	tdelay	250
	ret

MCU_HLT:	
MH1:	rjmp	MH1
