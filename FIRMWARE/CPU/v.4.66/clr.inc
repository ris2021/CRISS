; temp - cmd code, zzC - parameter
; 0 - set default mode/color
; 1 - set user static color
; 2 - set pattern mode
; 3 - set X
; 4 - set Y
; 5 - clear line
; 6 - cler screen
; 7 - scroll
; 8 - goto pattern mode
; 0xff - raw command

CLR_CMD:
	lds	FROMRAM0, HW_FOUND
	sbrs	FROMRAM0, HW_FOUND_EXT
	jmp	SPCMD_notfound

	tcbe	CLR_CMD_RAW,	  _CLR_RAW	; 0xff
	tcbe	CLR_CMD_DEFAULT,  _CLR_DEFAULT	; 0
	tcbe	1,  	_CLR_SET_COLOR
	tcbe	8,  	_CLR_PATTERN_MODE

	cfmem	CRT_SETTINGS, CRT_USE_CLR	; is pattern mode active?
	breq	_clr_cmd_notfound		; no, skip other commands

	tcbe	CLR_CMD_SET_X,	  _CLR_SET_X	; 3
	tcbe	CLR_CMD_SET_Y,    _CLR_SET_Y	; 4
	tcbe	CLR_CMD_PATTERN,  _CLR_PATTERN	; 2
	tcbe	5,  _CLR_CLR_LINE
	tcbe	6,  _CLR_CLR_SCR
	tcbe	7,  _CLR_SCROLL

_clr_cmd_notfound:
	jmp	SPCMD_notfound		; bad command
;	rjmp	_CLR_CMD_ret

_CLR_CMD_EXEC:
	push	zzC
	mov	zzC, temp

_CLR_CMD_EXEC_DO:
;        push   	temp
        ldi	temp, 80		; timeout timer 1s approx
        sts	OCR1AH, temp
        sts	OCR1AL, zero
        sts	TCNT1H, zero
        sts	TCNT1L, zero
        sbi	TIFR1, OCF1A  		; clear oc1a flag
        ldi     temp, (1<<CS12)|(1<<CS10)  	; fclk/1024 
        sts     TCCR1B, temp 		; start timer
;        pop	temp

	; commands that work with chip
        SPI_INIT SPI_SLAVE_CLR, SPI_FCK_DIV_4
	SPI_SELECT

_clr_wait_rtr_0:
	sbis	PINB, PB6
	rjmp	_clr_rtr_0	; MISO is low
	sbic    TIFR1, OCF1A      	
	jmp	_CLR_CMD_EXEC_err	; check timeout, return if no response
	rjmp	_clr_wait_rtr_0
_clr_rtr_0:

        mov	temp, zzC	; byte to send
;        FAST_SPI		; embedded SPI
;        nop
;	nop
;	nop
;	nop        
;	nop
;	nop        
;	nop
;	nop        
        call	DOSPI		; temp contains data to send

	push	temp
	delay3	60
	pop	temp		; delay for the CLR to stop SPI

_CLR_CMD_ret:
        SPI_STOP

_clr_wait_rtr_1:		; wait MISO line release
	sbic	PINB, PB6
	rjmp	_clr_rtr_1	; MISO is low
	sbic    TIFR1, OCF1A      	
	jmp	_CLR_CMD_EXEC_err	; check timeout, return if no response
	rjmp	_clr_wait_rtr_1
_clr_rtr_1:

        cpi	temp, 0		; Busy?
        brne	_CLR_CMD_end	

	delay3	750             ; delay for the CLR to complete request
	mov	temp, zzC	; restore byte to send
	rjmp	_CLR_CMD_EXEC_DO	; repeat request

_CLR_CMD_end:
        sts     TCCR1B, zero 	; stop timer
	sts	PCMD_FE, temp	; store response
	pop	zzC
	ret

_CLR_CMD_EXEC_err:
	pop	zzC

_CLR_CMD_err:	
        SPI_STOP
	jmp	SPCMD_notfound


_CLR_DEFAULT:
        ldi	temp, 0
_CLR_PASSIVE:
	push	temp
	lds	temp, CRT_SETTINGS
	cbr	temp, (1<<CRT_USE_CLR)	; clear active clr flag
	sts	CRT_SETTINGS, temp
	pop	temp
        rjmp	_CLR_CMD_EXEC

_CLR_SET_COLOR:
        ldi	temp, 1
        add	temp, zzC
        rjmp	_CLR_PASSIVE
;        rjmp	_CLR_CMD_EXEC

_CLR_PATTERN:
	ldi	temp, 0x80
	or	temp, zzC
;        ori	zzC, 0x80		; set bit 7
        rjmp	_CLR_CMD_EXEC

_CLR_SET_X:
	cpi	zzC, 80
	brsh	_CLR_CMD_err
        ldi	temp, 17
        add	temp, zzC
        rjmp	_CLR_CMD_EXEC

_CLR_SET_Y:
	cpi	zzC, 24
	brsh	_CLR_CMD_err
        ldi	temp, 97
        add	temp, zzC
        rjmp	_CLR_CMD_EXEC

_CLR_CLR_LINE:
        ldi	temp, 121
        rjmp	_CLR_CMD_EXEC

_CLR_CLR_SCR:
        ldi	temp, 122
        rjmp	_CLR_CMD_EXEC

_CLR_SCROLL:
        ldi	temp, 123
        rjmp	_CLR_CMD_EXEC

_CLR_PATTERN_MODE:
	lds	temp, CRT_SETTINGS
	sbr	temp, (1<<CRT_USE_CLR)	; set active clr flag
	sts	CRT_SETTINGS, temp
        ldi	temp, 127
        rjmp	_CLR_CMD_EXEC

_CLR_RAW:
        mov	temp, zzC
        rjmp	_CLR_CMD_EXEC
