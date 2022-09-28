        ; MELODY routines

	lds	temp, mpcmd		; get command from port
	; checking request
	cpse	temp, zero
	rjmp	MUS_CMD                 ; active
	sts	TCCR1B, zero		; stop timer and music
MUS_BR_EXIT:
	rjmp	MUS_EXIT		; no pending requests
	
MUS_CMD:	; active command
	cpi	temp, 0b11100000+1	; special command ?
	brlo	MUS_PLAYER

	cpi	temp, 0xff		; special command  - stop playing
	brne	MUS_SPECIAL
	rjmp	MUS_STOP_NI

; special commands: 0x80 - 0x8f = read system melody 0-16 from EPROM
MUS_SPECIAL:
	cpi	temp, 0xfe	; play first note until 0xff
	brne	MUS_SPECIAL2

	cpse	mpcnt, zero
	rjmp	MUS_EXIT	; not zero === playing is in progress
	inc	mpcnt		; set to 1 === mark "playing"
	ldi	tdata, (1<<COM1A0)     	; Toggle OC1A on Compare Match
        sts	TCCR1A, tdata		; set timer to toggle mode
	sts	TCNT1H, zero
	sts	TCNT1L, zero	; clear counter
	lds	tdata, mpbuf	; note to play
	rjmp	MUS_OUT		; start playing note


MUS_SPECIAL2:

;	andi	temp, 0x7f	; clear 7th bith
	sts	mpcmd, zero	; clear request

MUS_S_00:
;	sbrs	temp, 4		; check read 
;	cpi	temp, 0x0f+1	; read melody?
;	brsh	MUS_S_01        ; no, check next

	; load melody from EPROM
	andi	temp, 0x0f	; select melody number
	swap	temp		; temp = temp*16
	ldi	tdata, 0x01
	out	EEARH, tdata	; base = 0x0100
	out	EEARL, temp	; Address to read
	sbi 	EECR, EERE	; read request
	in 	tdata, EEDR	; read char from eeprom
	sts	mpcmd, tdata	; set command to play

	inc	temp		; next byte
	ldi	tdata, 15	; notes to read
	mov	mpcnt, tdata	; counter
	ldi	ZH, high(mpbuf)
	ldi	ZL, low(mpbuf)	; pointer to read distanation
MUS_S_00_L1:
	out	EEARL, temp	; Address to read
	sbi 	EECR, EERE	; read request
	in 	tdata, EEDR	; read char from eeprom
	st	Z+, tdata	; store data in RAM
	inc	temp            ; inc read address
	dec	mpcnt		; dec counter
	brne	MUS_S_00_L1	; loop 15 times
	ldi	temp, 0x04
	st	Z, temp		; stop command
	clr	mpcnt
	rjmp	MUS_EXIT	; next loop will start playing
;	rjmp	MUS_STOP_NI	; stop playing and clear all vars without IRQ
; -------------------------------------------------------------------------------------------

MUS_PLAYER:
	; checking playing
	cpse	mpcnt, zero
	rjmp	MUS_PLAYING		; there is an active command

	; new request - initial playing state
	ldi	tdata, (1<<COM1A0)     	; Toggle OC1A on Compare Match
        sts	TCCR1A, tdata		; set timer to toggle mode
	sts	TCNT1H, zero
	sts	TCNT1L, zero		; clear counter
MUS_PLAYER_NEW:
	ldi	tdata, low(mpbuf)-1	; start buf address in RAM (-1)
	mov	mpcnt, tdata		; note to play
;	clr	mpdur
	rjmp	MUS_l4

MUS_PLAYING:	; playing note
	cpse	mpdur, mnstp		; check stop condition
	rjmp	MUS_l2			; no - skip

	sts	TCCR1B, zero		; stop timer
	sts	TCNT1H, zero
	sts	TCNT1L, zero		; clear counter

MUS_l2:	
	cpse	mpdur, zero		; playing complete ?
	rjmp	MUS_EXIT		; nothing to do if !=0

MUS_l4:
	inc	mpcnt			; next note
	sbrc	mpcnt, 4		; out of buffer?		
	rjmp	MUS_STOP		; end of melody if so

	ldi	ZH, high(mpbuf)		; notes buffer
	mov	ZL, mpcnt
	ld	tdata, Z		; tdata = note to play

	cpi	tdata, 0x04             ; end of melody (note == 01)?
	breq	MUS_STOP_NI		; end of melody forced = no interrupt occured
	cpi	tdata, 0x05             ; repeat melody
	breq	MUS_PLAYER_NEW		; restart melody

	; computing duration
;	clr	mpdur
	mov	mpdur, temp
	ldi	ZL, 0b00011111
	and	mpdur, ZL		; basic duration

	mov	ZL, tdata
	andi	ZL, 0x03 		; note length
;	cpi	ZL, 0
	breq	MUS_l1			; length = 0 duration = basic
MUS_l0:
	lsl	mpdur			; mpdur *=2
	dec	ZL
	brne	MUS_l0
MUS_l1:
	andi	temp, 0b11100000	; interval value masked
	swap	temp
	lsr	temp			; temp = interval between notes selected
	clr	mnstp
	sbrs	tdata, 2		; bit suppressing intervals between notes
	mov	mnstp, temp		; otherwise set stop at value
	
;	ldi	ZH, high(MUS_MUL*2)	; multiplication table
;	mov	ZL, tdata
;	andi	ZL, 0x0 		; note length
;	or	ZL, temp		; add basic duration
;	ld	mpdur, Z		; duration to play from table
MUS_OUT:	
	ldi	ZH, high(MUS_DATA*2)
	mov	ZL, tdata
	andi	ZL, 0xf8 		; note index
	lsr	ZL			; = index*4
	lpm	tdata, Z+
	sts	OCR1AH, tdata
	lpm	tdata, Z+
	sts	OCR1AL, tdata		; OCR value set
	lpm	tdata, Z+
	ori	tdata, TCNT1TCCR1B	; set CTC mode
	sts	TCCR1B, tdata		; TCCR1B value - prescaler
		
	rjmp	MUS_EXIT

MUS_STOP:	; STOP PLAYING
	sbi	GPIOR0, IRQ_MUSIC	; set irq flag

MUS_STOP_NI:
	clr	mpcnt
	clr	mpdur
	sts	mpcmd, zero		; set port ready
MUS_STOP_TMR:
        sts	TCCR1A, zero     	; detach OC1A pin  
	sts	TCCR1B, zero		; stop timer
	sts	TCNT1H, zero
	sts	TCNT1L, zero		; clear counter
	cbi	PORTB, PB1
;	sbi	DDRB, PB1		; pull pin to zero
	rjmp	MUS_EXIT

;MUS_EXEC:
;;
;	rjmp	MUS_EXIT


;MUS_S_01:
	; !!! next command will be here if any

MUS_S_END:
;	sts	mpcmd, zero
	rjmp	MUS_EXIT
