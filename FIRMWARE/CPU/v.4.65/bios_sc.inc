BIOS_L04_CRLF:   ; CRLF
        sts	CURSOR_X, one
	rjmp	BIOS_L04_LF



BIOS_L04_ENTER:   ; CR
        sts	CURSOR_X, one
	rjmp	CURSOR_APPLY_XY
;	ret


BIOS_L04_LF:
BIOS_L04_CR:   ; LF
	lds	temp, CURSOR_Y
	cpmem	temp, CRT_LINES
	brlo	BIOS_L04_CR_DN

	cfmem	CRT_SETTINGS, CRT_SCROLL_DSBL	; check scroll enabled
	brne	BIOS_L04_CR_ret			; bit set = scroll disabled!

;	push	temp
	rcall	SCREEN_SCROOL_DOWN_RAM		; just scroll, cursor lets the same

	cfmem	CRT_SETTINGS, CRT_USE_ATTR
	breq	BIOS_L04_CR_ret
	rcall	ECON_ATTR_SCROLL		; process attributes if required
;	pop	temp
BIOS_L04_CR_ret:
	rjmp	CURSOR_APPLY_XY			; set cursor
;	ret

BIOS_L04_CR_DN:
	inc	temp
	sts	CURSOR_Y, temp
	rjmp	CURSOR_APPLY_XY			; next line
;	ret



BIOS_L04_BSP: 	; BackSpace
	lds	temp, CURSOR_X
	cpi	temp, 2
	brsh	BIOS_L04_BSP_DO
	ret
BIOS_L04_BSP_DO:
	dec	temp
	sts	CURSOR_X, temp
	rjmp	CURSOR_APPLY_XY
;	ret



BIOS_L04_CLRSCR:   ; CLR SCR ^L
	rcall	SCREEN_CLEAR

	cfmem	CRT_SETTINGS, CRT_USE_ATTR
	breq	BIOS_L04_HOME
	rcall	ECON_ATTR_CLRSCR		; process attributes if required

BIOS_L04_HOME:	; Corsor HOME
	CURSOR_SET2 one, one
	rjmp	CURSOR_APPLY_XY
;	ret



BIOS_L04_BEEP:	; BEEP
	call	SYSTEM_BEEP
	ret



BIOS_L04_RIGHT: ; RIGHT
	lds	temp, CURSOR_X
	cpmem	temp, CRT_CHARS
	brlo	BIOS_L04_RIGHT_DO
	ret
BIOS_L04_RIGHT_DO:
	inc	temp
	sts	CURSOR_X, temp
	rjmp	CURSOR_APPLY_XY
;	rcall	CURSOR_APPLY_XY
;	ret



BIOS_L04_UP: 	; UP
	lds	temp, CURSOR_Y
	cpi	temp, 2
	brsh	BIOS_L04_UP_DO
	ret
BIOS_L04_UP_DO:
	dec	temp
	sts	CURSOR_Y, temp
	rjmp	CURSOR_APPLY_XY
;	rcall	CURSOR_APPLY_XY
;	ret



BIOS_L04_CLRLN:	; clear current string
	sts	CURSOR_X, one
	rcall	CURSOR_APPLY_XY			; goto pos = 1
	rjmp	BIOS_L04_CLREOL			; clear till the end of line



BIOS_L04_CLRCUR:	; clear till end of screen
	pushw	Z				
	pushw	X
	ldi	temp, 0xf7			; RAM F8** address
	ldw	Z, VIDEO_CURSOR				
	add	ZH, temp
	ldw	X, VIDEO_END
	add	XH, temp
BIOS_L04_CLRCUR_CL:
	ldi	temp, ' '                       ; char to fill
	STRAM	ZH, ZL, temp
	adiw	Z, 1
	cp	ZL, XL
	cpc	ZH, XH
	brlo	BIOS_L04_CLRCUR_CL
	popw	X
	popw	Z

	cfmem	CRT_SETTINGS, CRT_USE_ATTR
	breq	BIOS_L04_CLRCUR_L2
	pushw	Z
	ldw	Z, VIDEO_CURSOR				
	rcall	ECON_ATTR_CLR_Z			; clear attributes
	rcall	ECON_ATTR_CHAR			; set/restore attributes
	popw	Z

BIOS_L04_CLRCUR_L2:	
	ret



BIOS_L04_CLREOL:	; clear till end of line
	pushw	Y				
	pushw	Z				
	push	zzC

	ldi	temp, 0xf7			; RAM F8** address
	ldw	Z, VIDEO_CURSOR
	ldw	Y, VIDEO_CURSOR			; for ECON VIDEOBUF
	add	ZH, temp
	lds	zzC, CURSOR_X
	dec	zzC				; for correct compare, zz=0..79

BIOS_L04_CLREOL_CL:
	ldi	temp, ' '
	STRAM	ZH, ZL, temp			; char to fill

	cfmem	CRT_SETTINGS, CRT_USE_ATTR
	breq	BIOS_L04_CLREOL_L2
	st	Y+, zero			; clear attribute

BIOS_L04_CLREOL_L2:	
	adiw	Z, 1
	inc	zzC
	cpmem	zzC, CRT_CHARS			; CON_CHARS
	brlo	BIOS_L04_CLREOL_CL

	cfmem	CRT_SETTINGS, CRT_USE_ATTR
	breq	BIOS_L04_CLREOL_L3
	rcall	ECON_ATTR_CHAR			; set/restore attributes

BIOS_L04_CLREOL_L3:	
	pop	zzC
	popw	Z
	popw	Y
	ret


BIOS_L04_CLRBOL:	; clear from start of line to cursor
	pushw	Y				
	pushw	Z				
	push	zzC

	ldi	temp, 0xf7			; RAM F8** address
	ldw	Z, VIDEO_CURSOR
	ldw	Y, VIDEO_CURSOR			; for ECON VIDEOBUF
	add	ZH, temp
	lds	zzC, CURSOR_X
;	dec	zzC				; for correct compare, zz=0..79
BIOS_L04_CLRBOL_CL:
	ldi	temp, ' '
	STRAM	ZH, ZL, temp			; char to fill

	cfmem	CRT_SETTINGS, CRT_USE_ATTR
	breq	BIOS_L04_CLRBOL_L2
	st	Y, zero			; clear attribute
	sbiw	Y, 1

BIOS_L04_CLRBOL_L2:	
	sbiw	Z, 1
	dec	zzC
;	cpmem	zzC, CRT_CHARS			; CON_CHARS
	brne	BIOS_L04_CLRBOL_CL

	cfmem	CRT_SETTINGS, CRT_USE_ATTR
	breq	BIOS_L04_CLRBOL_L3
	rcall	ECON_ATTR_CHAR			; set/restore attributes

BIOS_L04_CLRBOL_L3:	
	pop	zzC
	popw	Z
	popw	Y
	ret



BIOS_L04_CLR_BOS:	; clear from start of the screen to cursor
	pushw	Y				
	pushw	Z				
;	push	zzC

	ldi	temp, 0xf7			; RAM F8** address
	ldw	Z, VIDEO_CURSOR
	ldw	Y, VIDEO_CURSOR			; for ECON VIDEOBUF
	add	ZH, temp
;	lds	zzC, CURSOR_X
;	dec	zzC				; for correct compare, zz=0..79
BIOS_L04_CLRBOS_CL:
	ldi	temp, ' '
	STRAM	ZH, ZL, temp			; char to fill

	cfmem	CRT_SETTINGS, CRT_USE_ATTR
	breq	BIOS_L04_CLRBOS_L2
	st	Y, zero			; clear attribute
	sbiw	Y, 1

BIOS_L04_CLRBOS_L2:	
	sbiw	Z, 1
;	dec	zzC
;	cpmem	zzC, CRT_CHARS			; CON_CHARS
	cpi	ZH, 0xf7			; at the beginning of the screen here Z=f7FF
	brne	BIOS_L04_CLRBOS_CL

	cfmem	CRT_SETTINGS, CRT_USE_ATTR
	breq	BIOS_L04_CLRBOS_L3
	rcall	ECON_ATTR_CHAR			; set/restore attributes

BIOS_L04_CLRBOS_L3:	
;	pop	zzC
	popw	Z
	popw	Y
	ret




BIOS_L04_TAB:	; TAB
	ldi	temp, ' '
	mov	zzC, temp
	rcall	BIOS_L04_CHAR			; output ' '
	lds	temp, CURSOR_X
	dec	temp
	andi	temp, 0x07                      ; check that TAB position reached
;	cpi	temp, 0x07
	brne	BIOS_L04_TAB
	ret




BIOS_L04_CUROFF:	; cursor off
        ststs	CURSOR_STATUS, 0x80
	rjmp 	BIOS_SETCPDCURSOR
;	ret




BIOS_L04_CURON:	; cursor on
	sts	CURSOR_STATUS, zero
	rjmp 	BIOS_SETCPDCURSOR
;	ret

