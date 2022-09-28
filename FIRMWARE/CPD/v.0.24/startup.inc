	; fill ram with startup screen

	; fill ram with spaces
	ldi	XH, 1
	ldi	XL, 0		; start point in ram
	ldi	temp, ' '
L0:
	st	X+, temp
	cpi	XL, low(0x100+25*80)
	ldi	tdata, high(0x100+25*80)
	cpc	XH, tdata
	brne	L0

	; fill ram from eeprom
	ldi	tdata, 0
	ldi	YH, 0
	ldi	YL, 0		; start point in EEPROM

L3:	ldi	XH, 1
	ldi	XL, 0		; start point in RAM

	; calculate beginning of tdata position
	mov	temp, tdata
L2:	or	temp, temp	; check for temp==0
	breq	L1
	adiw	X, 40
	adiw	X, 40
	dec	temp
	rjmp	L2

L1:	; X is set to tdata start
	out	EEARH, YH
	out	EEARL, YL	; Address to read

	sbi 	EECR, EERE	; read request
	in 	temp, EEDR	; read char from eeprom

	cpi	temp, 0x1F
	breq	L4		; ^Z = end of data

	adiw	Y, 1		; incrementing EEAR

	cpi	temp, 0x0D
	brne	L5		; NL = new tdata
	inc	tdata
	rjmp	L3
		
L5:	st	X+, temp	; store char in RAM
	rjmp	L1
	; end memory fill	---------------------------------------------------
	
L4:
	; fill rest with 0
     	ldi	XH, high(PORTS)
        ldi     XL, low(PORTS)    ; start point in memory
SU_L1:
        clr   	temp
        st    	X+, temp
        cpi   	XL, 0
        brne  	SU_L1

        ; init keyboard vriables
        clr   	kbmdkey
        clr   	kbdata
        clr   	kbcntr
        clr   	kbread
        clr   	kbledr
        clr   	zero
        clr	twistat
	clr	mpcnt
	clr	mpdur
	clr	mnstp

;	sts	mpcmd, zero		; set port ready

      	_ldi	vga0, (0<<PC0)|(0<<PC2)|(0<<PC3)|(1<<PC1)	; pause state = clk0
      	_ldi	vga1, (1<<PC0)|(0<<PC2)|(0<<PC3)|(1<<PC1)	; clk1
      	_ldi	vga2, (0<<PC0)|(0<<PC2)|(1<<PC3)|(1<<PC1)	; deselected state

        ldi   	XH, 0
        ldi   	XL, 0

        ldi   	YH, 1
        ldi   	YL, 0

        sts	vcurh, YH			; cursor

        ; vga settings
        ldi   	temp, (24<<3)    		; 24 lines 0 codepage
        sts   	vstat, temp

        ; joistic to nutral position
;        ldi   temp, 128
;        sts  jstkx, temp
;        sts  jstky, temp

	; SPI main
	_out	SPCR, (1<<SPIE)|(1<<SPE)	; SPI enable (Slave) and Int allowed

	; TWI for GPIO
	_outm	TWSR, 0				; prescaler = 1
	_outm 	TWBR, 92			; 100 kHz for PCF8574

    	; External interrupts
	_outm	EICRA, (1<<ISC11)|(1<<ISC01) 	; falling edges for INT1 (VGA) and INT0 (KBD)
        _out    EIMSK, (1<<INT0)		; Interrupt for the keyboard

	; UART
	_outm	UBRR0H, 0
	_outm	UBRR0L, 129			; 9600 bod 
    	_outm	UCSR0C, (1<<UCSZ01)|(1<<UCSZ00)	; 8 bit no parity 1 stop bit
	_outm	UCSR0B, (1<<RXEN0)|(1<<TXEN0)	; UART: receive, transmit 

        ; timer/counter 0 - system timer
        _out	TCCR0A, (1<<WGM01)  ; CTC mode
        _out	OCR0A, 195          ; 0.01s
;        _out	OCR0B, 195          ; 0.01s
        _out	TCCR0B, (1<<CS02)|(1<<CS00) ; f_cpu/1024

        ; timer/counter 1 - audio
;        _outm	TCCR1A, (1<<COM1A0)     	; Toggle OC1A on Compare Match  
        .EQU	TCNT1TCCR1B = (1<<WGM12)
;        _outm	TCCR1B, TCNT1TCCR1B		;(1<<WGM12)      	; CTC mode, count to OC1A
	sts	TCCR1B, zero			; stop timer
	sts	TCNT1H, zero
	sts	TCNT1L, zero			; clear counter

        ; timer/counter 2 - keyboard timeout
        _outm	OCR2A, 3         		; 120 us for led control
        _outm	TCCR2A, 0  			; Normal mode
        _outm	TCCR2B, (1<<CS22)|(1<<CS21)|(1<<CS20) ; f_cpu/1024
        _outm  	TCNT2, 0                	; reset counter
        _outm	ASSR, 0
        _outm	TIMSK2, (1<<TOIE2)		; timer overflow - keyboard reset interrupt

        sbi	EIFR, INTF0			; clear first pulse for the keyboard

        out	GPIOR0, zero			; irq internal flags
        out	GPIOR1, zero                    ; irq mask
        out	GPIOR2, zero

;	sbi	DDRD, (1<<PD5)			; RESET pin for VGA high - EXTERNAL pull-up!!!!

	; hide leds in the case of restart
  	inc	kbledr				; request to change led state
	ldi	temp, 0xed			; data to send
	mov	kbldata, temp
