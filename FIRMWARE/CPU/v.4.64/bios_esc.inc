BIOS04_ESC_KAYPRO_B:
	mov	temp, zzC
	tcbe	'4', BIOS_L04_CURON		; B4 cursor on
	tcbe	'6', BIOS04_ESC_KAYPRO_B6
	ret

BIOS04_ESC_CUR_STORE:
BIOS04_ESC_KAYPRO_B6:
	lds	temp, CURSOR_X
	sts	CON_CPPOS_X, temp
	lds	temp, CURSOR_Y
	sts	CON_CPPOS_Y, temp
	ret

BIOS04_ESC_KAYPRO_C:
	mov	temp, zzC
	tcbe	'4', BIOS_L04_CUROFF		; B4 cursor off
	tcbe	'6', BIOS04_ESC_KAYPRO_C6
	ret

BIOS04_ESC_CUR_RESTORE:
BIOS04_ESC_KAYPRO_C6:
	lds	temp, CON_CPPOS_X
	sts	CURSOR_X, temp
	lds	temp, CON_CPPOS_Y
	sts	CURSOR_Y, temp
	rjmp	CURSOR_APPLY_XY
;	ret

	; #9 x = set x position
BIOS04_ESC_CRISS_09:
	cpi	zzC, 81
	brsh	BIOS04_ESC_CRISS_09_ret
	sts	CURSOR_X, zzC
	rjmp	CURSOR_APPLY_XY
BIOS04_ESC_CRISS_09_ret:
	ret

	; '\' char - out char from #1..#30
BIOS04_ESC_CRISS_OUT:
	jmp	BIOS_L04_CHAR_L1		; just output char
;	ret

	; 127+y, 127+x = cursor positioning
BIOS04_ESC_ROB_CUR:
	lds	temp, CON_ESC_C1
	subi	temp, 0x7f
	subi	zzC, 0x7f

BIOS04_ESC_CUR_SET:				; temp = y, zzC = x
	cpi	temp, 26
	brsh	BIOS04_ESC_ROB_CUR_ret
	cpi	zzC, 81
	brsh	BIOS04_ESC_ROB_CUR_ret
	sts	CURSOR_Y, temp
	sts	CURSOR_X, zzC
	rjmp	CURSOR_APPLY_XY
BIOS04_ESC_ROB_CUR_ret:
	ret

	; = row+32 col+32 = cursor positioning
BIOS04_ESC_KAYPRO_CUR:
	lds	temp, CON_ESC_C2
	subi	temp, 31
	subi	zzC, 31
	rjmp	BIOS04_ESC_CUR_SET



	; Y line col - Position cursor
BIOS04_ESC_TRS_CUR:
	lds	temp, CON_ESC_C2
	inc	temp
	inc	zzC
	rjmp	BIOS04_ESC_CUR_SET




BIOS_ESC_KAYPRO_E:			; insert line
        lds	temp, CURSOR_X
        push	temp			; save to restore
	sts	CURSOR_X, one
	rcall	CURSOR_XY_PTR		; make pointer
			
	pushw	X
	pushw	Y
	pushw	Z
	push	r19

        lds	temp, CURSOR_Y
        cpmem	temp, CRT_LINES
        brlo	_bios_esc_b_L4
        rjmp	_bios_esc_b_L3		; last line - just clear last ine

_bios_esc_b_L4:
	ldi	temp, 0xf7

	ldw	Y, VIDEO_CURSOR
	add	YH, temp
;	sbiw	Y, 1			; for correct brsh

	ldw	Z, VIDEO_END		; copy to (backward)
	add	ZH, temp

	ldw	X, VIDEO_END		; 
	add	XH, temp
	lds	temp, CRT_CHARS
	sub	XL, temp
	sbc	XH, zero		; copy from
;	sbiw	X, 40
;	sbiw	X, 40			; copy from

_bios_esc_b_L1:
	sbiw	X, 1
	sbiw	Z, 1
	cp	XL, YL
	cpc	XH, YH
	brlo	_bios_esc_b_L3
	LDRAM 	XH, XL, r19		; read char from zRAM
	STRAM	ZH, ZL, r19
	rjmp	_bios_esc_b_L1		; loop

_bios_esc_b_L3:
        rcall	BIOS_L04_CLREOL		; clr line

BIOS_ESC_B_RE_RET:	
	pop	r19
	popw	Z
	popw	Y
	popw	X                       ; restore registers

	pop	temp
	sts	CURSOR_X, temp
	rjmp	CURSOR_XY_PTR		; just restore pointer, position not changed
	
;	ret



BIOS_ESC_KAYPRO_R:			; delete line
        lds	temp, CURSOR_X
        push	temp			; save to restore
	sts	CURSOR_X, one
	rcall	CURSOR_XY_PTR		

	pushw	X
	pushw	Y
	pushw	Z
	push	r19

        lds	temp, CURSOR_Y
        cpmem	temp, CRT_LINES
        brlo	_bios_esc_e_L4
        rjmp	_bios_esc_e_L3		; last line - just clear, for the case pf 25th line

_bios_esc_e_L4:
	ldi	temp, 0xf7

	ldw	Y, VIDEO_END		; end point for compare
	add	YH, temp
	adiw	Y, 1			; for correst brsh

	ldw	X, VIDEO_CURSOR		; copy to
	add	XH, temp

	ldw	Z, VIDEO_CURSOR		; 
	add	ZH, temp
	lds	temp, CRT_CHARS
	sub	XL, temp
	sbc	XH, zero		; copy from
;	adiw	Z, 40
;	adiw	Z, 40			; copy from next line

_bios_esc_e_L1:
	cp	ZL, YL
	cpc	ZH, YH
	brsh	_bios_esc_e_L3
	LDRAM 	ZH, ZL, r19		; read char from zRAM
	STRAM	XH, XL, r19
	adiw	X, 1
	adiw	Z, 1
	rjmp	_bios_esc_e_L1

_bios_esc_e_L3:
        lds	temp, CURSOR_Y
        push	temp
        lds	temp, CRT_LINES
        sts	CURSOR_Y, temp
	rcall	CURSOR_XY_PTR		

        rcall	BIOS_L04_CLREOL		; clr line

        pop	temp
        sts	CURSOR_Y, temp		; restore cursor position

	rjmp	BIOS_ESC_B_RE_RET	; clear last line


	; Z * - set mode, zzC = mode
BIOS04_ESC_CRISS_ZG:
	push	temp
        push	zzC
        lsr	zzC
        lsr	zzC
        lsr	zzC
	sts	CRT_LINES, zzC	; store lines no
	sts	CRT_CHARS, zzA	; store chars no
	pop	zzC
	andi	zzC, 0x07
;	lds	temp, CRT_SETTINGS
;	andi	temp, 0b01000000	; preserve attr option
	sts	CRT_SETTINGS, zzC	; store codepage
;	nportout cpd_vstat, zzC	; change display mode

	CURSOR_SET2 one, one		; home cursor
	rcall	SCREEN_CLEAR		; clear screen

	rcall	BIOS_SET_VIDEO_MODE	; set video mode
	pop	temp
	ret



.MACRO  SGM
        cpi	temp, @0
        brne	_sgm_not
        ldi	zzA, @2
	ldi	zzC, ((@1)<<3)|(@3) 
;	rcall 	BIOS04_ESC_CRISS_ZG
_sgm_not:
.ENDM

	; G 0-3 - set ZG page 0,2,3,4
	; G 4 - set graph mode
	; G 5 - set 25 lines / 0
	; G S - set 24 lines special mode
	; G 6,7 - set 30*64 lines
	; G 8,9 - set 31*64 lines
	; G N - default text mode
BIOS04_ESC_TRS_GRMODE:
        push	zzA
        mov	temp, zzC
        ldi	zzA, 0
	SGM	'0', 24, 80, 0
	SGM	'1', 24, 80, 2
	SGM	'2', 24, 80, 3
	SGM	'3', 24, 80, 4
	SGM	'4', 24, 80, 1		; graph mode
	SGM	'5', 25, 80, 0		; 25 lines
	SGM	'S', 24, 80, 7		; special mode!
	SGM	'6', 30, 64, 0		; 30 lines 64 chars
	SGM	'7', 30, 64, 4		; 30 lines 64 chars
	SGM	'8', 31, 64, 0		; 31 lines 64 chars
	SGM	'9', 31, 64, 4		; 31 lines 64 chars
	cpse	zzA, zero
	rcall	BIOS04_ESC_CRISS_ZG
	pop	zzA

        cpi	temp, 'N'		; set default text mode = reset
        brne	_etgrm_ret

	push	zzA
	ldi	zzA, ' '		; fill with spaces in text mode
	rcall	SCREEN_CLEAR_A
	pop	zzA
	sts	CURSOR_STATUS, zero	; show cursor
	sts	CURSOR_X, one
	sts	CURSOR_Y, one
        rjmp	BIOS_RESET
_etgrm_ret:
	ret


;---------------------------------------------------------------
BIOS04_ESC_GETPIX:
	push	r0
	push	r1

	lds	temp, CON_ESC_C2	; y
	cpi	temp, 97		; y<=96
	brsh	_gpi_err

	ldi	ZH, 0xf8		; videram
;	ldi	ZL, 80                  ; chars per line
	lds	ZL, CRT_CHARS           ; chars per line
	lsr	temp
	lsr	temp			; div 4 - line received 
	mul	temp, ZL
	add	ZH, r1
	mov	ZL, r0			; Y = y,0

	mov	temp, zzC		; x
	cpi	temp, 161		; x<=160
	brsh	_gpi_err

	lsr	temp			; div 2 - pos received
	add	ZL, temp
	adc	ZH, zero		; Y = pixel byte

	ldi	zzA, 1
	lds	temp, CON_ESC_C2	; y
	andi	temp, 0x03		; y mod 4
	lsl	temp			; temp *= 2
;	inc	temp
	sbrc	zzC, 0			; zzC mod 2
	inc	temp			; temp = bit number ; font > 1.12 !!!

	cpi	temp, 0
	breq	_gpi_l1
_gpi_l2:
	lsl	zzA
	dec	temp
	brne	_gpi_l2
_gpi_l1:				; zzA = 1<<temp
	LDRAM   ZH, ZL, temp		; load byte from RAM to temp
_gpi_exit:				; zzA = 1<<temp
	pop	r1
	pop	r0
	ret
_gpi_err:
	ldi	ZH, 0
	rjmp	_gpi_exit
;---------------------------------------------------------------


BIOS04_ESC_SETPIX:
	cpi	ZH, 0xF8
	brlo	_spix_l0		; check that address is correct
	STRAM   ZH, ZL, temp		; get byte to temp
_spix_l0:
	ret


; --------------------------------------------------
; set pixel YH = y, YL = x, FROMRAM2 = mode: L=set,x=toggle,D=clear
CRISS_PUTPIX_Y:
;	call gmln_debug
	; putpixel

	push	temp
	push	zzA
	pushw	Z
	sts	CON_ESC_C2, YH		; y
	mov	zzC, YL			; x
	rcall	BIOS04_ESC_GETPIX

	; set/change point
	cpi	FROMRAM2, 'L'		; set?
	brne	_gmln_l8
	or	temp, zzA
	rjmp	_gmln_l10
_gmln_l8:
	cpi	FROMRAM2, 'x'		; invert?
	brne	_gmln_l9
	eor	temp, zzA
	rjmp	_gmln_l10
_gmln_l9:
;	cpi	FROMRAM2, 'D'		; clear?
;	brne	_gmln_l9
	com	zzA
	and	temp, zzA
;	rjmp	_gmln_l10
_gmln_l10:
	rcall	BIOS04_ESC_SETPIX
	popw	Z
	pop	zzA
	pop	temp
	ret

;GR_PIX_ORDER:	.DB	2,1,8,4,32,16,128,64

	; * line col - put pixel
BIOS04_ESC_KAYPRO_PUTPIX:
	pushw	Z
	push	zzA
	rcall	BIOS04_ESC_GETPIX
	or	temp, zzA
	rcall	BIOS04_ESC_SETPIX
	pop	zzA
	popw	Z
	ret
	
	; ' ' line col - put pixel
BIOS04_ESC_KAYPRO_CLRPIX:
	pushw	Z
	push	zzA
	rcall	BIOS04_ESC_GETPIX
	com	zzA
	and	temp, zzA
	rcall	BIOS04_ESC_SETPIX
	pop	zzA
	popw	Z
	ret

	; '#' line col - toggle pixel
BIOS04_ESC_CRISS_TGLPIX:
	pushw	Z
	push	zzA
	rcall	BIOS04_ESC_GETPIX
	eor	temp, zzA
	rcall	BIOS04_ESC_SETPIX
	pop	zzA
	popw	Z
	ret


BIOS04_ESC_CRISS_SWP:
	ret

	; windows and frames
BIOS04_ESC_CRISS_F:
BIOS04_ESC_CRISS_DF:
BIOS04_ESC_CRISS_VP:
BIOS04_ESC_CRISS_CLR:
	ret
	

BIOS04_ESC_KAYPRO_PUTLN:
BIOS04_ESC_KAYPRO_CLRLN:
BIOS04_ESC_CRISS_INVLN:
	push	zzA
	push	FROMRAM0
	push	FROMRAM2
	push	r0
	push	r1
	pushw	X
	pushw	Y
	pushw	Z
	lds	YH, CON_ESC_C2		; v1
	lds	YL, CON_ESC_C3		; h1
	lds	XH, CON_ESC_C4		; v2
	lds	XL, CON_ESC_C5		; h2

;	sts	CON_ESC, zero
;	lds	zzC, CON_ESC_C1		; command to do
;	ldi	temp, BIOS_FUNC_CONOUT
;	call	BIOS
;	rjmp	_gmln_end

	cp	YH, XH
	brlo	_gmln_l1
	breq	_gmln_l2
	mov	temp, YH		; YH>XH
	sub	temp, XH
	ldi	XH, -1			; IX=-1
	rjmp	_gmln_l3
_gmln_l1:
	mov	temp, XH		; YH<XH
	sub	temp, YH
	ldi	XH, 1			; IX=1
	rjmp	_gmln_l3
_gmln_l2:
	ldi	temp, 0			; XH=YH
	ldi	XH, 0			; IX=0
_gmln_l3:
	mov	r1, temp		; DY

	cp	YL, XL			; X1,Y1
	brlo	_gmln_l4
	breq	_gmln_l5
	mov	temp, YL		; YL>XL
	sub	temp, XL
	ldi	XL, -1			; IY = -1
	rjmp	_gmln_l6
_gmln_l4:
	mov	temp, XL		; XL<YL
	sub	temp, YL
	ldi	XL, 1			; IX = 1
	rjmp	_gmln_l6
_gmln_l5:
	ldi	temp, 0			; XL==YL
	ldi	XL, 0			; IY = 0
_gmln_l6:
	mov	r0, temp		; DX

	cp	r0, r1 			; DY, DX
	mov	temp, r1
	brlo	_gmln_l7                ; DY<DX
	mov	temp, r0
_gmln_l7:
	mov	FROMRAM0, temp		; D
	inc	temp			; temp = D+1 = counter

	lds	FROMRAM2, CON_ESC_C1	; command to do
	clr	ZH			; YR
	clr	ZL			; XR

_gmln_loop:	
	push	temp
	rcall	CRISS_PUTPIX_Y

	; calculate next pixel
	add	ZH, r1			; YR:=YR+DY;
	add	ZL, r0			; XR:=XR+DX;
	
	cp	ZH, FROMRAM0
	brlo	_gmln_l11		; skip if less then
	sub	ZH, FROMRAM0		; YR:=YR-D
	add	YH, XH			; Y1:=Y1+IY
_gmln_l11:

	cp	ZL, FROMRAM0
	brlo	_gmln_l12		; skip if less then
	sub	ZL, FROMRAM0		; XR:=XR-D
	add	YL, XL			; X1:=X1+IX
_gmln_l12:

	pop	temp
	dec	temp
	brne	_gmln_loop

_gmln_end:
	popw	Z
	popw	Y
	popw	X
	pop	r1
	pop	r0
	pop	FROMRAM2
	pop	FROMRAM0
	pop	zzA
	ret


	; Z = DY:DX
CRISS_CIRCLE_CPLOT:
	pushw	Y
	lds	YH, CON_ESC_C3	; y0
	add	YH, ZH
	lds	YL, CON_ESC_C4	; x0
	add	YL, ZL
	rcall	CRISS_PUTPIX_Y
	popw	Y
	ret	

CRISS_CIRCLE_CPLOT8:
	mov	ZH, XH
	mov	ZL, XL
	sbrc	FROMRAM0, 0
	rcall	CRISS_CIRCLE_CPLOT
	mov	ZH, XH
	neg	ZH
	mov	ZL, XL
	sbrc	FROMRAM0, 1
	rcall	CRISS_CIRCLE_CPLOT
	mov	ZH, XH
	mov	ZL, XL
	neg	ZL
	sbrc	FROMRAM0, 2
	rcall	CRISS_CIRCLE_CPLOT
	mov	ZH, XH
	neg	ZH
	mov	ZL, XL
	neg	ZL
	sbrc	FROMRAM0, 3
	rcall	CRISS_CIRCLE_CPLOT
	mov	ZH, XL
	mov	ZL, XH
	sbrc	FROMRAM0, 4
	rcall	CRISS_CIRCLE_CPLOT
	mov	ZH, XL
	neg	ZH
	mov	ZL, XH
	sbrc	FROMRAM0, 5
	rcall	CRISS_CIRCLE_CPLOT
	mov	ZH, XL
	mov	ZL, XH
	neg	ZL
	sbrc	FROMRAM0, 6
	rcall	CRISS_CIRCLE_CPLOT
	mov	ZH, XL
	neg	ZH
	mov	ZL, XH
	neg	ZL
	sbrc	FROMRAM0, 7
	rcall	CRISS_CIRCLE_CPLOT
	ret

	; draw circle mask v h r
BIOS04_ESC_CRISS_CIRCLE:
	push	zzA
	push	FROMRAM0
	push	FROMRAM2
;	push	r0
;	push	r1
	pushw	X
	pushw	Y
	pushw	Z

	ldi	FROMRAM2, 'L'		; command to put pixel
	lds	FROMRAM0, CON_ESC_C2	; mask
;	lds	YH, CON_ESC_C3		; v
;	lds	YL, CON_ESC_C4		; h
	lds	XH, CON_ESC_C5		; Y:=R
	ldi	XL, 0			; X:=0

	mov	temp, XH
	add	temp, temp		; *2
	ldi	YH, 3
	sub	YH, temp		; D:=3-2*R;

_criss_circle_while:
	;call	gmln_debug
	
	cp	XL, XH           	; WHILE X<Y DO BEGIN
	brlo	_criss_circle_do
	rjmp	_criss_circle_compl

_criss_circle_do:
	rcall	CRISS_CIRCLE_CPLOT8

	or	YH, YH			; check D
	brmi	_criss_circle_l1
	mov	temp, XL		; X
	sub	temp, XH		; X-Y
	lsl	temp
	lsl	temp			; *4
	add	YH, temp
	subi	YH, -6 			; D:=D+4*(X-Y)+10
	dec	XH			; Y:=Y-1
	rjmp	_criss_circle_l2

_criss_circle_l1:
	mov	temp, XL		; X
	lsl	temp
	lsl	temp			; X*4
	add	YH, temp
	subi	YH, -6 			; D:=D+4*X+6

_criss_circle_l2:
	inc	XL
	rjmp	_criss_circle_while

_criss_circle_compl:
	cpi	XH, 0			; IF Y=0 THEN CPLOT(X,Y,XC,YC);
	brne	_criss_circle_end
	rcall	CRISS_CIRCLE_CPLOT8

_criss_circle_end:
	popw	Z
	popw	Y
	popw	X
;	pop	r1
;	pop	r0
	pop	FROMRAM2
	pop	FROMRAM0
	pop	zzA
	ret

/*
gmln_debug:
	push	temp
	uDBGh	YH
	uDBGh	YL
	uDBGh	XH
	uDBGh	XL
	uDBGh	ZH
	uDBGh	ZL
	uDBGh	r1
	uDBGh	r0
	uDBGh	FROMRAM0
	uDBGh	FROMRAM2
	uDBGcr
	pop	temp
	ret
*/

; disable scrolling
BIOS_L04_SCRLOFF:
	lds	temp, CRT_SETTINGS
	sbr	temp, 1<<CRT_SCROLL_DSBL
	sts	CRT_SETTINGS, temp
	ret

; enable scrolling
BIOS_L04_SCRLON:
	lds	temp, CRT_SETTINGS
	cbr	temp, 1<<CRT_SCROLL_DSBL
	sts	CRT_SETTINGS, temp
	ret

; stop processing ESC seq
BIOS_ESC_CANCEL:
	sts	CON_ESC, zero
	clr	FROMRAM2		; if is called from the processor
	ret

BIOS04_ESC_CRISS_GPIO:
	lds	temp, CON_ESC_C2	; mask
	rcall	GPIO_SEND		; send to GPIO
	ret
	