.EQU	M_CLK_PIN = PC5
.EQU	M_DATA_PIN = PC4

.MACRO	M_CLK_LO
	sbi	DDRC, PC5
.ENDM

.MACRO	M_CLK_HI
	cbi	DDRC, PC5
.ENDM

.MACRO	M_CLK_RELEASE
	cbi	DDRC, PC5
.ENDM

.MACRO	M_DATA_LO
	sbi	DDRC, PC4
.ENDM

.MACRO	M_DATA_HI
	cbi	DDRC, PC4
.ENDM

.MACRO	M_DATA_RELEASE
	cbi	DDRC, PC4
.ENDM

.MACRO M_DELAY
	ldi	temp, @0
	call	delay_us
.ENDM


.MACRO M_WAIT_CLK_HI
	ldi temp, 10
__l1:
	sbic	PINC, M_CLK_PIN
	rjmp	__l2
      	sbic	TIFR0, OCF0A
	rcall	M_TIMEOUT
	rjmp	__l1
__l2:
.ENDM

.MACRO M_WAIT_CLK_LO
	ldi temp, 10
__l1:
	sbis	PINC, M_CLK_PIN
	rjmp	__l2
      	sbic	TIFR0, OCF0A
	rcall	M_TIMEOUT
	rjmp	__l1
__l2:
.ENDM

.MACRO M_WAIT_CLK_PULSE
	M_WAIT_CLK_HI
	M_WAIT_CLK_LO
.ENDM

.MACRO M_SEND_PUSH_BIT
	sbrc	tdata, 0
	rjmp	MICE_PS2_SEND_BIT_1
	M_DATA_LO
	rjmp	MICE_PS2_SEND_BIT_DONE
MICE_PS2_SEND_BIT_1:
	M_DATA_HI
MICE_PS2_SEND_BIT_DONE:
	eor	twistat, tdata
	lsr	tdata
.ENDM
	
.MACRO __M_PS2_SEND
	M_CLK_LO			; init transfer
	M_DELAY 110
	M_DATA_LO
	M_CLK_RELEASE
	M_DELAY 5
	clr	twistat			; for crc
	inc	twistat			; start with 1

	M_WAIT_CLK_PULSE
	M_SEND_PUSH_BIT
	M_WAIT_CLK_PULSE
	M_SEND_PUSH_BIT
	M_WAIT_CLK_PULSE
	M_SEND_PUSH_BIT
	M_WAIT_CLK_PULSE
	M_SEND_PUSH_BIT
	M_WAIT_CLK_PULSE
	M_SEND_PUSH_BIT
	M_WAIT_CLK_PULSE
	M_SEND_PUSH_BIT
	M_WAIT_CLK_PULSE
	M_SEND_PUSH_BIT
	M_WAIT_CLK_PULSE
	M_SEND_PUSH_BIT
	mov	tdata, twistat
	M_WAIT_CLK_PULSE
	M_SEND_PUSH_BIT
	M_WAIT_CLK_PULSE
	M_WAIT_CLK_PULSE
.ENDM

_M_PS2_SEND:
	__M_PS2_SEND
	ret

.MACRO M_PS2_SEND
	rcall	_M_PS2_SEND
.ENDM


.MACRO M_READ_POP_BIT
	sbic	PINC, M_DATA_PIN
	ori	tdata, 1<<@0
.ENDM



.MACRO __M_PS2_READ
	clr	tdata
	M_WAIT_CLK_PULSE
	M_WAIT_CLK_PULSE
	M_READ_POP_BIT 0
	M_WAIT_CLK_PULSE
	M_READ_POP_BIT 1
	M_WAIT_CLK_PULSE
	M_READ_POP_BIT 2
	M_WAIT_CLK_PULSE
	M_READ_POP_BIT 3
	M_WAIT_CLK_PULSE
	M_READ_POP_BIT 4
	M_WAIT_CLK_PULSE
	M_READ_POP_BIT 5
	M_WAIT_CLK_PULSE
	M_READ_POP_BIT 6
	M_WAIT_CLK_PULSE
	M_READ_POP_BIT 7
	M_WAIT_CLK_PULSE
	M_WAIT_CLK_PULSE
.ENDM

_M_PS2_READ:
	__M_PS2_READ
	ret

.MACRO M_PS2_READ
	cpse	kbread, zero
	rjmp	MICE_ARB		; keyboard data - stop mouse procesing
	rcall _M_PS2_READ
	cpse	kbread, zero
	rjmp	MICE_ARB		; keyboard data - stop mouse procesing
.ENDM


MICE_RESET:
	sts	TWCR, zero		; reset TWI interface
	cbi	DDRC, PC4
	cbi	DDRC, PC5
	cbi	PORTC, PC4
	cbi	PORTC, PC5		; reset pins
;	sts	PCMSK1, zero
	clr	twistat
;	clr	tdata
;	sez
	ret


MICE_ERROR:
	rcall	MICE_RESET
	sez
	jmp	TWI_CMDEx_OK		



MICE_STOP:
	rcall	MICE_RESET		; release pins
	clz
	jmp	TWI_CMDEx_OK		


	
MICE_ARB:
	rcall	MICE_RESET		; release pins
	lds	tdata, twdti
	cbr	tdata, 0x08		; clear bit 3 and don't change the result
	clz
	jmp	TWI_CMDEx_OK		


	
	; hw reset mouse
MICE_FF:
	ldi	tdata, 0xFF		; set mouse to Reset mode
	rcall	MICE_RESET
	M_PS2_SEND
	clz
	jmp	TWI_CMDEx_OK		
	


MICE_INIT:
	ldi	tdata, 0xF0		; set mouse to remote mode
	rcall	MICE_RESET
	M_PS2_SEND
	M_PS2_READ
	cpi	tdata, 0xFA		; ACK?
	brne	MICE_INIT_ERR
	clz
;	jmp	TWI_CMDEx_OK		
	sts	mousx, zero
	sts	mousy, zero
	jmp	TWI_E0_INIT_DONE
MICE_INIT_ERR:
	rjmp	MICE_ERROR		; error and received ACK as value


MICE_READ:
	rcall	MICE_RESET
	ldi	tdata, 0xEB		; 0xEB (Read Data)
	M_PS2_SEND
	lds	twistat, twdti		; old data
	swap	twistat
	ldi	tdata, 0b11110000
	and	twistat, tdata		; save old state in bits 4-7

	M_PS2_READ
	cpi	tdata, 0xFA		; ACK?
	brne	MICE_READ_ERR

	M_PS2_READ
	andi	tdata, 0x07
	or	twistat, tdata		; actual buttons

	M_PS2_READ
	lds	temp, mousx
	add	temp, tdata
	sts	mousx, temp
;	sbrs	tdata, 7
;	rjmp	_M_READ_X_L1
;	sbr	twistat, 0x20		; move X
;	neg	tdata			; tdata=-tdata
;_M_READ_X_L1:
;	lds	temp, mousx
;	inc	temp
;	cp	tdata, temp
;	brlo	_M_READ_Y
;	cpse	tdata, zero
;	sbr	twistat, 0x10		; move X

_M_READ_Y:
	M_PS2_READ
	lds	temp, mousy
	add	temp, tdata
	sts	mousy, temp
;	sbrs	tdata, 7
;	rjmp	_M_READ_Y_L1
;	sbr	twistat, 0x80		; move Y
;	neg	tdata
;_M_READ_Y_L1:
;	lds	temp, mousy
;	inc	temp
;	cp	tdata, temp
;	brlo	_M_READ_E
;	cpse	tdata, zero
;	sbr	twistat, 0x40		; move Y

_M_READ_E:
	mov	tdata, twistat		; report result
;	clr	twistat
	clz
	jmp	TWI_CMDEx_OK		
MICE_READ_ERR:
	rjmp	MICE_ERROR		; error and received ACK as value


	; check timeout and escapes in the case of error
M_TIMEOUT:
;      	sbis	TIFR0, OCF0A
;	ret
	dec	temp
	breq	M_TIMEOUT_ERROR
      	sbi     TIFR0, OCF0A    	; clear flag
	ret
M_TIMEOUT_ERROR:			; return to error handler
	pop	temp
	pop	temp			; remove old return address
	pop	temp
	pop	temp			; remove old return address - 2 levels!!!
	ldi	tdata, 2		; timeout error flag
	rjmp	MICE_ERROR
