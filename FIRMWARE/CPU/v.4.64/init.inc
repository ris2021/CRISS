INITPROC_CMD:
    	; PORT directions

	; D: bus decoder,  buzzer, RAM WE, OE
	_out	PORTD, 0xFF 	  			; spi disabled, memory not selected
	_out	DDRD, (1<<PD1)|(1<<PD4)|(1<<PD5)	; SPIE, WE, OE

    	; address bus to out
	_out	DDRA, 0xff        	; low adress bus
	_out	DDRC, 0xff        	; high address bus

	_out	DDRB, 0           	; data port to in

	_out	RAMPZ, 1		; elpm reads from high memory

	; external interrupts settings
	_outm	PCMSK3, (1<<PCINT30)|(1<<PCINT31)|(1<<PCINT26)	; ext interrupts: D7- LAN, D6 - RTC, D0 - CPD
	_outm	PCICR, (1<<PCIE3)	;

	; power save settings
	_outm	PRR0, (1<<PRTWI)|(1<<PRADC)|(1<<PRUSART0)	; Power reduction: disable TWI, UART0, ADC

	; mesage from CPD
;	_outm	UBRR0H, 0
;	_outm	UBRR0L, 21		; 21 = 57600 at 20MHz 
;	_outm	UCSR0C, (1<<UCSZ01) | (1<<UCSZ00)	; 8 bit no parity 1 stop bit
;	_outm	UCSR0B, (1<<RXEN0) | (1<<RXCIE0)	; Rx and RxInt enabled

	; external incoming UART
	_outm	UBRR1H, 0
	_outm	UBRR1L, 10		; 21 = 57600 at 20MHz 10=115200
	_outm	UCSR1C, (1<<UCSZ11) | (1<<UCSZ10)	; 8 bit no parity 1 stop bit
	_outm	UCSR1B, (1<<RXEN1) | (1<<TXEN1) | (1<<RXCIE1)	; Rx and RxInt enabled

	_ldi	RAMOE, 	~(1<<PD4)	; /OE
	_ldi	RAMWE,  ~(1<<PD5)	; /WE
	_ldi	SPIMODE,~(1<<PD1) 	; /SPIE
	_ldi	ZERO, 	0		; 0
	_ldi	ONE, 	1		; 1
	_ldi	FF, 	0xff		; Videoram start for cp
	_ldi	VIDEORAM, 0xf8

	; init AVR RAM with 0
	ldi	YH, 1
	ldi	YL, 0 
	clr	zero
	ldi	temp, high(STACK)
L_INIT_4:
	st	Y+, zero
	cpi	YL, low(STACK)
	cpc	YH, temp
	brne	L_INIT_4


	sts	CURSOR_X, one           ; cursor X position, 1-80
	sts	CURSOR_Y, one		; cursor Y position, 1-25
	sts	CURSOR_STATUS, zero     ; =0 if cursor is on, 0x80 if is off

	ldi	temp, 24
	sts	CRT_LINES, temp
	ldi	temp, 80
	sts	CRT_CHARS, temp
	sts	CRT_SETTINGS, zero	

	ldi	temp, low(0x100+24*80)
	sts	VIDEO_END, temp
	ldi	temp, high(0x100+24*80)
	sts	VIDEO_END+1, temp	; end of video ram starting from 0x100	

	sts	VIDEO_CURSOR, zero
	sts	VIDEO_CURSOR+1, one	; cursor position in videoram = 0x100

	sts	BIOS_DISK, zero	
	sts	BIOS_TRACK, zero
	sts	BIOS_SECTOR, zero
	sts	BIOS_DMA, zero

	sts	CON_ESC, zero		; count chars in ESC-sequence
;	sts	CON_ESC_C5, zero	; ATTRIBUTES

	ldi	temp, (1<<CON_OUT_CON) | (1<<CON_IN_CON)
	sts	CON_IOBYTE, temp	; IOBYTE xxxx0000 = outputs, 0000xxxx = inputs
	sts	PR_IOBYTE, zero

	ldi	temp, (1<<LST_OUT_LST)
	sts	RTC_DEV_IOBYTE, temp	; LST channel

	ldi	temp, (1<<SDC_SRC_SDC)
	sts	RTC_DEV_IOBYTE, temp	; SDC channel

	sts	INT_MASK, zero		; interrupt mask
	sts	INT_MASK+1, zero	; interrupt mask

	sts	HW_FLAG, zero		; CRISS

	call	BIOS_MOUSE_INIT		; init automouse settings

;	ldi	temp, 0x11		; CON only output
;	sts	CON_IOBYTE, temp
;	sts	PR_IOBYTE, zero

;	_outm	TWBR, 0x88		; used as internal IOBYTE
	out	GPIOR0, zero		; IRQ handling - IRQ flags for CPU IRQs
	out	GPIOR1, zero            ; IRQ handling - IRQ flags for CPU IRQs - stored CPD requests
;	out	GPIOR2, zero		; opcode table pointer z80_init.inc

        ; internal timer accessible from z-prog
	_outm	ASSR, 0
	_outm	OCR2A, 192		; 0.01 s
	_outm	TCCR2A, (1<<WGM21)	; CTC mode
	_outm	TIMSK2, (1<<OCIE2A)	; oerflow interrupt
	_outm	TCCR2B, (1<<CS20)|(1<<CS21)|(1<<CS22)		; timer 2 fclk/1024
	_outm	TCNT2, 0

	; init RAM with ' '
	ldi	YH, 0
	ldi	YL, 0 
	ldi	r18, ' '
L_INIT_3:
	_STRAM	YH, YL, r18
	adiw	Y, 1
	cp	YL, zero
	cpc	YH, zero
	brne	L_INIT_3

	clr	YL
	clr	YH
	clr	r18

	ret
