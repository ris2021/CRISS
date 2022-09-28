BIOS_MOUSE_ONOFF:
	lds	temp, MS_MODE
	cpse	temp, zero
	rjmp	BIOS_MOUSE_OFF
	rjmp	BIOS_MOUSE_ON
	ret



BIOS_MOUSE_ON:
	nportin	cpd_sysrq
	sbrc	temp, CPD_SYSRQ_MICE	; is mouse active?
	ret				; if active just ignore
	nportout_t cpd_twcmd, 0xE0	; mice init command
	rcall	delay_5ms
;	rcall	delay_2ms
	nportin	cpd_sysrq
	sbrs	temp, CPD_SYSRQ_MICE	; is mouse active?
	ret				; no mouse detected - just ignore
	sts	MS_MODE, one		; set mouse active
	nportout_t cpd_twdti, 0		; clear button state
	nportout_t cpd_micex, 0		; clear pos
	nportout_t cpd_micey, 0		; clear pos
	call	SYSTEM_BEEP		; welcome beep
	ret



BIOS_MOUSE_OFF:
;	call	SYSTEM_BEEP		; welcome beep
	nportout_t cpd_twcmd, 0xE4	; mice stop command
	sts	MS_MODE, zero		; set mouse inactive
	ret


;MS_MODE:	.BYTE	1		; Mouse settings for auto mode
;MS_STEP_X:	.BYTE	1
;MS_STEP_Y:	.BYTE	1
;MS_MOVE_UP:	.BYTE	1		; shift up returns this character
;MS_MOVE_DOWN:	.BYTE	1
;MS_MOVE_RIGHT:	.BYTE	1
;MS_MOVE_LEFT:	.BYTE	1
;MS_BTN_LEFT_P:	.BYTE	1		; left button returns character
;MS_BTN_LEFT_U:	.BYTE	1		; left button returns character
;MS_BTN_MID_P:	.BYTE	1		; mid button returns character
;MS_BTN_MID_U:	.BYTE	1		; mid button returns character
;MS_BTN_RIGHT_P:	.BYTE	1		; right button returns character
;MS_BTN_RIGHT_U:	.BYTE	1		; right button returns character

BIOS_MOUSE_INIT:
	pushw	Z
	pushw	X
	push	FROMRAM0
	ldiw	X, MOUSE_SETTINGS
	ldiw	Z, BIOS_MOUSE_INIT_DATA*2
	ldi	temp, 13
_BIOS_MOUSE_INIT_LOOP:
	elpm	FROMRAM0, Z+
	st	X+, FROMRAM0
	dec	temp
	brne	_BIOS_MOUSE_INIT_LOOP
	pop	FROMRAM0
	popw	X
	popw	Z
	ret



BIOS_MOUSE_AUTOMODE:
	lds	temp, MS_MODE
	cpse	temp, one
	ret				; no mouse activated

	nportin	cpd_sysrq		; check that mouse is active
	sbrs	temp, CPD_SYSRQ_MICE	; is mouse active?
	rjmp	BIOS_MOUSE_OFF		; mouse read error - stop mouse

;_BIOS_MOUSE_AUTOMODE_CHECK_KBD:
;	nportin	cpd_kmodk		; check that keyboard is not processed
;	sbrc	temp, 7
;	rjmp	_BIOS_MOUSE_AUTOMODE_CHECK_KBD
					
	nportout_t cpd_twcmd, 0xE1	; mice read command
	rcall	delay_5ms
	rcall	delay_5ms
	rcall	delay_5ms
	nportin	cpd_twcmd
	cpse	temp, zero
	rjmp	BIOS_MOUSE_OFF		; mouse read error - stop mouse

	; process auto mouse
	push	zzC
	push	zzA

_ms_amode_check_x:
	nportin	cpd_micex
	mov	zzA, temp
	sbrc	zzA, 7			; is negative?
	neg	temp			; abs(temp)
	lds	zzC, MS_STEP_X
	cp	temp, zzC
	brlo	_ms_amode_check_y	; not exceed tolerance
	mov	temp, zzA		; restore temp
	sbrc	zzA, 7			; is negative?
	neg	zzC
	sub	temp, zzC
	nportout cpd_micex, temp	; store updated value
	lds	zzC, MS_MOVE_LEFT
	sbrc	zzA, 7			; is negative?
	lds	zzC, MS_MOVE_RIGHT
	BIOS_CALL BIOS_FUNC_CONBUF_APPEND

_ms_amode_check_y:
	nportin	cpd_micey
	mov	zzA, temp
	sbrc	zzA, 7			; is negative?
	neg	temp			; abs(temp)
	lds	zzC, MS_STEP_Y
	cp	temp, zzC
	brlo	_ms_amode_check_btn	; not exceed tolerance
	mov	temp, zzA		; restore temp
	sbrc	zzA, 7			; is negative?
	neg	zzC
	sub	temp, zzC
	nportout cpd_micey, temp	; store updated value
	lds	zzC, MS_MOVE_UP
	sbrc	zzA, 7			; is negative?
	lds	zzC, MS_MOVE_DOWN
	BIOS_CALL BIOS_FUNC_CONBUF_APPEND

_ms_amode_check_btn:
	nportin	cpd_twdti		; read buttons
	mov	zzA, temp
	swap	zzA
	eor	zzA, temp		; get btns state change

_ms_amode_check_btn_0:
	sbrs	zzA, 0			; left button
	rjmp	_ms_amode_check_btn_1
	lds	zzC, MS_BTN_LEFT_P
	sbrs	temp, 0			; is pressed
	lds	zzC, MS_BTN_LEFT_U
	BIOS_CALL BIOS_FUNC_CONBUF_APPEND
_ms_amode_check_btn_1:
	sbrs	zzA, 1			; left button
	rjmp	_ms_amode_check_btn_2
	lds	zzC, MS_BTN_RIGHT_P
	sbrs	temp, 1			; is pressed
	lds	zzC, MS_BTN_RIGHT_U
	BIOS_CALL BIOS_FUNC_CONBUF_APPEND
_ms_amode_check_btn_2:
	sbrs	zzA, 2			; left button
	rjmp	_ms_amode_check_ret
	lds	zzC, MS_BTN_MID_P
	sbrs	temp, 2			; is pressed
	lds	zzC, MS_BTN_MID_U
	BIOS_CALL BIOS_FUNC_CONBUF_APPEND

_ms_amode_check_ret:
	pop	zzA
	pop	zzC
	ret


	; temp = temp
_MS_AMODE_ADJ:
	or	temp, temp
	

DELAY_25US:
	push	temp
	delay3	498
	pop	temp
	ret

DELAY_5MS:
	ldi	temp, 200
_DELAY_MS_LOOP:
	rcall	delay_25us
	dec	temp
	brne 	_DELAY_MS_LOOP
	ret
