	; reset bios and celar attr screens
BIOS_RESET:
        push	temp
        push	FROMRAM0
        push	r0
        push	r1
        pushw	Z
	lds	temp, HW_FLAG		; current platform
	ldi	FROMRAM0, 24		; hw descriptor block length
	mul	temp, FROMRAM0
	ldiw2	Z, HW_OPTIONS
	add	ZL, r0
	adc	ZH, r1                  ; select HW platform descriptor address
	adiw	Z, 16			; skip title, goto parameters
	elpm	temp, Z+
	sts	CRT_LINES, temp		; codepage after restore
	elpm	temp, Z+
	sts	CRT_CHARS, temp		; codepage after restore
	elpm	temp, Z+
	sts	CRT_SETTINGS, temp	; codepage after restore
	popw	Z
	pop	r1
	pop	r0
	pop	FROMRAM0
	pop	temp

	sts	CON_ESC, zero
	sts	CON_ATTR_XOR, zero
	sts	CON_ATTR_OR, zero
	sts	CURSOR_STATUS, zero	; show cursor
;	sts	CURSOR_X, one
;	sts	CURSOR_Y, one		; cursor home p
	rcall	BIOS_SET_VIDEO_MODE
	; proceed to ECON_ATTR_CLRSCR


ECON_ATTR_CLRSCR:
	pushw	Z
	ldiw	Z, VIDEOBUF
	rcall	ECON_ATTR_CLR_Z
	popw	Z
	ret



BIOS_ATTR_CLR_Z_L1:
	st	Z+, zero
ECON_ATTR_CLR_Z:
	cpi	ZL, low(VIDEOBUF_END)
	brne	BIOS_ATTR_CLR_Z_L1
	cpi	ZH, high(VIDEOBUF_END)
	brne	BIOS_ATTR_CLR_Z_L1
	ret



	; set attr value in zzC for current char
ECON_SET_ATTR:
	pushw	Z
	push	temp
	ldw	Z, VIDEO_CURSOR
	ori	zzC, 0x80		; set 7th bit == attr start point
	st	Z+, zzC			; set attribute
	andi	zzC, 0x7f		; clear 7th bit
	rjmp	ECON_SET_ATTR_L2

ECON_SET_ATTR_L1:
	ld	temp, Z			; check attr value
	andi	temp, 0x80		; new attr?
	brne 	ECON_SET_ATTR_L3	; yes = stop
	st	Z+, zzC		; set attribute
ECON_SET_ATTR_L2:
	cpi	ZL, low(VIDEOBUF_END)
	brne	ECON_SET_ATTR_L1
	cpi	ZH, high(VIDEOBUF_END)
	brne	ECON_SET_ATTR_L1

ECON_SET_ATTR_L3:
	pop	temp
	popw	Z
	ret




	; check that char replces attrribute
ECON_ATTR_CHAR:
	pushw	Z
	push	temp
	ldw	Z, VIDEO_CURSOR
	ld	temp, Z
	andi	temp, 0x80		; is there active attribute?
	breq	ECON_CHAR_ATTR_RET	; no - no attention
	st	Z, zero			; clear attr
	rjmp	ECON_CHAR_ATTR_L2
ECON_CHAR_ATTR_L1:
;	st	Z-, zero
	ld	temp, -Z		; check attr
	andi	temp, 0x80
	brne	ECON_CHAR_ATTR_L3	; attribute found - process it!
ECON_CHAR_ATTR_L2:
	cpi	ZL, low(VIDEOBUF)
	brne	ECON_CHAR_ATTR_L1
	cpi	ZH, high(VIDEOBUF)
	brne	ECON_CHAR_ATTR_L1
	ldi	temp, 0

ECON_CHAR_ATTR_L3:
	pushw	Y
	push	zzC
	mov	zzC, temp
	ldw	Y, VIDEO_CURSOR		; save cursor
	stw	VIDEO_CURSOR, Z
	rcall	ECON_SET_ATTR
	stw	VIDEO_CURSOR, Y		; restore cursor
	pop	zzC
	popw	Y

ECON_CHAR_ATTR_RET:
	pop	temp
	popw	Z
	ret



	; return attr in temp
ECON_GET_ATTR:
	pushw	Z
	ldw	Z, VIDEO_CURSOR
	ld	temp, Z
	sbrc	temp, 7			; attr starts here? yes - return previous
	rjmp	ECON_GET_ATTR_L1
ECON_GET_ATTR_ret:
	popw	Z
	ret
ECON_GET_ATTR_L1:
	cpi	ZH, high(VIDEOBUF)
	brne	ECON_GET_ATTR_L2
	cpi	ZL, low(VIDEOBUF)
	brne	ECON_GET_ATTR_L2
	clr	temp			; first char - clear attributes
	rjmp	ECON_GET_ATTR_ret
ECON_GET_ATTR_L2:
	ld	temp, -Z
	rjmp	ECON_GET_ATTR_ret	; return previous char


	; scroll attr screen
ECON_ATTR_SCROLL:
	pushw	Z
	pushw	Y
	pushw	X
	push	temp
	push	zzC
	ZXYf	VIDEOBUF+80, VIDEOBUF, 24*80	; scroll attributes

	ldi	temp, 80
	ldiw	Z, VIDEOBUF+24*80-1
	ld	zzC, Z+				; get attr value for last line
ECON_SCROLL_L1:
	st	Z+, zzC
	dec	temp
	brne	ECON_SCROLL_L1			; fill last line

	pop	zzC
	pop	temp
	popw	X
	popw	Y
	popw	Z
	ret



ECON_CRT_ATTR:
	rcall	ECON_SET_ATTR			; set attr
	ldi	zzC, ':'			;!!!! debug!!!!!!
	rcall	BIOS_L04_CHAR_CHAROUT		; echo special char on the place of attribute
	ret


/*
ECON_REFRESH_SCREEN:
	pushw	Z
	push	zzC
	push	temp
	ldiw	Z, VIDEOBUF
	subi	ZH, -0xf7
ECON_REFRESH_SCREEN_L2:
	LDRAM	ZH, ZL, zzC			; get screen symbol
	push	zzC
	call	HW_CONOUT_CHAR
	pop	temp
	cp	temp, zzC
	breq	ECON_REFRESH_SCREEN_L1
	STRAM	ZH, ZL, zzC			; replace symbol
ECON_REFRESH_SCREEN_L1:
	add	ZL, one
	adc	ZH, zero
	cpi	ZL, low(VIDEOBUF_END)
	brne	ECON_REFRESH_SCREEN_L2
	cpi	ZH, high(VIDEOBUF_END)
	brne	ECON_REFRESH_SCREEN_L2
	pop	temp
	pop	zzC
	popw	Z
	ret

*/