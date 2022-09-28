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

.MACRO M_READ_CLK
	sez
	sbic	PINC, PC5
	clz				; returns z set if 0
.ENDM

.MACRO M_READ_DATA
	sez
	sbic	PINC, PC4
	clz				; returns z set if 0
.ENDM

.MACRO	___MICE_PS2_CLK_DROP
	rcall	MICE_PS2_CLK_DROP
.ENDM

.MACRO	___MICE_PS2_CLK_DROP_R
	rcall	MICE_PS2_CLK_DROP_R
.ENDM


MICE_PS2_CLK_DROP:
	ldi	temp, 50
MICE_PS2_CLK_DROP_DO:
	sbis	PCIFR, PCIF1
	rjmp	MICE_PS2_CLK_DROP_LC	; check cancellation
	sbi	PCIFR, PCIF1		; clear flag
	sbic	PINC, M_CLK_PIN
;	M_READ_CLK			; read state
	rjmp	MICE_PS2_CLK_DROP_DO	; front, repeat
;	in	temp, PORTC
	clz
	ret
;	rjmp	MICE_PS2_CLK_DROP_END	; no error
;	ret
MICE_PS2_CLK_DROP_LC:
      	sbis	TIFR0, OCF0A
	rjmp	MICE_PS2_CLK_DROP_DO
      	sbi     TIFR0, OCF0A    	; clear flag
	dec	temp
	brne	MICE_PS2_CLK_DROP_DO	; witing approx 10ms for timeout
MICE_PS2_CLK_DROP_END:
	ret


MICE_PS2_CLK_DROP_R:
	ldi	temp, 50
MICE_PS2_CLK_DROPR_DO:
	sbis	PCIFR, PCIF1
	rjmp	MICE_PS2_CLK_DROPR_LC	; check cancellation
	sbi	PCIFR, PCIF1		; clear flar
	sbic	PINC, M_CLK_PIN
;	M_READ_CLK			; read state
	rjmp	MICE_PS2_CLK_DROPR_DO	; front, repeat
	in	temp, PINC
	clz
	ret
;	rjmp	MICE_PS2_CLK_DROP_END	; no error
;	ret
MICE_PS2_CLK_DROPR_LC:
      	sbis	TIFR0, OCF0A
	rjmp	MICE_PS2_CLK_DROPR_DO
      	sbi     TIFR0, OCF0A    	; clear flag
	dec	temp
	brne	MICE_PS2_CLK_DROPR_DO	; witing approx 10ms for timeout
MICE_PS2_CLK_DROPR_END:
	ret

.MACRO MICE_PS2_SEND_BIT
	___MICE_PS2_CLK_DROP
	breq	@0
	rcall	_MICE_PS2_SEND_BIT
	breq	@0
.ENDM


_MICE_PS2_SEND_BIT:
;	breq	MICE_PS2_SEND_BIT_RET
	sbrc	tdata, 0
	rjmp	MICE_PS2_SEND_BIT_1
	M_DATA_LO
	rjmp	MICE_PS2_SEND_BIT_DONE
MICE_PS2_SEND_BIT_1:
	M_DATA_HI
MICE_PS2_SEND_BIT_DONE:
	eor	twistat, tdata
	lsr	tdata
	clz
MICE_PS2_SEND_BIT_RET:
	ret


;MICE_PS2_SEND_ERR2:
;	rjmp	MICE_CLEAR
MICE_PS2_SEND:
	M_CLK_LO
	M_DELAY 110
	M_DATA_LO
	M_CLK_RELEASE
	M_DELAY 5
	clr	twistat			; for crc
	inc	twistat			; start with 1

	MICE_PS2_SEND_BIT MICE_PS2_SEND_ERR
	MICE_PS2_SEND_BIT MICE_PS2_SEND_ERR
	MICE_PS2_SEND_BIT MICE_PS2_SEND_ERR
	MICE_PS2_SEND_BIT MICE_PS2_SEND_ERR
	MICE_PS2_SEND_BIT MICE_PS2_SEND_ERR
	MICE_PS2_SEND_BIT MICE_PS2_SEND_ERR
	MICE_PS2_SEND_BIT MICE_PS2_SEND_ERR
	MICE_PS2_SEND_BIT MICE_PS2_SEND_ERR
	mov	tdata, twistat
	MICE_PS2_SEND_BIT MICE_PS2_SEND_ERR	; send crc
	___MICE_PS2_CLK_DROP
	breq	MICE_PS2_SEND_ERR
	M_DATA_RELEASE
	___MICE_PS2_CLK_DROP_R
	breq	MICE_PS2_SEND_ERR
	sbrc	temp, M_DATA_PIN
;	andi	temp, 1<<M_DATA_PIN
;	M_READ_DATA			; expecting ack
	rjmp	MICE_PS2_SEND_ERR
	clr	twistat
	clz				; no error
	ret
MICE_PS2_SEND_ERR:
	ldi	tdata, 1
	rjmp	MICE_CLEAR
;	ret


.MACRO	MICE_PS2_READ_BIT
	___MICE_PS2_CLK_DROP_R
	breq	@0
	lsr	tdata
	sbrc	temp, M_DATA_PIN
	ori	tdata, 0x80		; it clears z flag
	clz
;	rcall	_MICE_PS2_READ_BIT
;	breq	@0
.ENDM

/*
_MICE_PS2_READ_BIT:
;	breq	MICE_PS2_READ_BIT_RET
	lsr	tdata
	M_READ_DATA
	breq	MICE_PS2_READ_BIT_0
	ori	tdata, 0x80
MICE_PS2_READ_BIT_0:
	clz				; no error
MICE_PS2_READ_BIT_RET:
	ret
*/	

MICE_PS2_READ:
	clr	tdata
	___MICE_PS2_CLK_DROP
	breq	MICE_PS2_READ_ERR
	MICE_PS2_READ_BIT MICE_PS2_READ_ERR
	MICE_PS2_READ_BIT MICE_PS2_READ_ERR
	MICE_PS2_READ_BIT MICE_PS2_READ_ERR
	MICE_PS2_READ_BIT MICE_PS2_READ_ERR
	MICE_PS2_READ_BIT MICE_PS2_READ_ERR
	MICE_PS2_READ_BIT MICE_PS2_READ_ERR
	MICE_PS2_READ_BIT MICE_PS2_READ_ERR
	MICE_PS2_READ_BIT MICE_PS2_READ_ERR
	___MICE_PS2_CLK_DROP
	breq	MICE_PS2_READ_ERR
	___MICE_PS2_CLK_DROP
	breq	MICE_PS2_READ_ERR
	clz
	ret
MICE_PS2_READ_ERR:
	ldi	tdata, 2
	rjmp	MICE_CLEAR
;MICE_PS2_READ_RET:


MICE_INIT_PINS:
        sts	TWCR, zero
	cbi	DDRC, PC4
	cbi	DDRC, PC5
	cbi	PORTC, PC4
	cbi	PORTC, PC5		; reset pins
	ldi	temp, (1<<PCINT13)	; enable pcint flag for CLK
	sts	PCMSK1, temp
	sbi	PCIFR, PCIF1		; clear flag
	clz
	ret

	
	; init mouse
	;???? add 0xff - reset ????
MICE_INIT:
	rcall 	MICE_INIT_PINS
	ldi	tdata, 0xF0		; set mouse to remote mode
	rcall	MICE_PS2_SEND
	breq	MICE_INIT_ERR
	rcall	MICE_PS2_READ		; read response
	breq	MICE_INIT_ERR
	cpi	tdata, 0xFA		; ACK?
	brne	MICE_INIT_ERR
	clz
	jmp	TWI_CMDEx_OK		
;	ret
MICE_INIT_ERR:
	rcall	MICE_CLEAR
	jmp	TWI_CMDEx_OK		
;	rjmp	MICE_CLEAR



MICE_READ:
	rcall 	MICE_INIT_PINS

	lds	twistat, twdti		; old data
	ldi	tdata, 0b00001000
	and	twistat, tdata		; preserve 3th bit == work mode
;	clr	twistat

	ldi	tdata, 0xEB		; 0xEB (Read Data)
	rcall	MICE_PS2_SEND
	breq	MICE_READ_ERR

	rcall	MICE_PS2_READ		; read response
	cpi	tdata, 0xFA		; ACK
	brne	MICE_READ_ERR3

	rcall	MICE_PS2_READ		; read response - buttons
	brne	MICE_READ_ERR4
	andi	tdata, 0x07
	or	twistat, tdata		; buttons

	rcall	MICE_PS2_READ		; read response
	brne	MICE_READ_ERR5
	sbrc	tdata, 7
	sbr	twistat, 0x20		; move X
	andi	tdata, 0x7f
	cpse	tdata, zero
	sbr	twistat, 0x10		; move X

	rcall	MICE_PS2_READ		; read response
	brne	MICE_READ_ERR6
	sbrc	tdata, 7
	sbr	twistat, 0x80		; move X
	andi	tdata, 0x7f
	cpse	tdata, zero
	sbr	twistat, 0x40		; move Y

	mov	tdata, twistat		; report result
	clr	twistat
	
	clz
	jmp	TWI_CMDEx_OK		
MICE_READ_ERR3:
	ldi	tdata, 3
	rjmp	MICE_READ_ERR
MICE_READ_ERR4:
	ldi	tdata, 4
	rjmp	MICE_READ_ERR
MICE_READ_ERR5:
	ldi	tdata, 5
	rjmp	MICE_READ_ERR
MICE_READ_ERR6:
	ldi	tdata, 6
	rjmp	MICE_READ_ERR
MICE_READ_ERR:
;	ldi	tdata, 3
	rcall	MICE_CLEAR
	jmp	TWI_CMDEx_OK		



MICE_CLEAR:
	cbi	DDRC, PC4
	cbi	DDRC, PC5
	cbi	PORTC, PC4
	cbi	PORTC, PC5		; reset pins
	sts	PCMSK1, zero
	clr	twistat
;	clr	tdata
	sez
	ret
