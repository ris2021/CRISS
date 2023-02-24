BIOS04_ESC_KAYPRO_B:
	mov	temp, zzC
	tcbe	'4', BIOS_L04_CURON		; B4 cursor on
	tcbe	'6', BIOS04_ESC_KAYPRO_B6	; store cursor popsition
	tcbe	'S', BIOS04_ESC_CRISS_BS	; store screen to VIDEOBUF
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
	tcbe	'6', BIOS04_ESC_KAYPRO_C6	; restore cursor position
	tcbe	'S', BIOS04_ESC_CRISS_CS	; restore screen from videobuf
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
        cpmem	zzC, CRT_CHARS
;	cpi	zzC, 81
	breq	_bios4_09_l1
	brsh	BIOS04_ESC_CRISS_09_ret
_bios4_09_l1:
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
        cpmem	temp, CRT_LINES
        breq	_bios4_cur_set_l2
;	cpi	temp, 26
	brsh	BIOS04_ESC_ROB_CUR_ret
_bios4_cur_set_l2:
        cpmem	zzC, CRT_CHARS
        breq	_bios4_cur_set_l1
;	cpi	zzC, 81
	brsh	BIOS04_ESC_ROB_CUR_ret
_bios4_cur_set_l1:
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
	rcall	_bios_cw_err		; reset CRISS frame window
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
	
; sends char to standard CON input
BIOS04_ESC_CRISS_SET_CON:
	call	BIOS_Lf0
	ret

; save screen to VIDEOBUF
BIOS04_ESC_CRISS_BS:
	pushw	Z
	pushw	X
	ldiw	Z, VIDEOBUF
	ldiw	X, 0xF800			; start of videoram
_bios04_bs_l1:
	LDRAM	XH, XL, temp
	st	Z+, temp
	adiw	X, 1
	cpi	ZL, low(VIDEOBUF_END)
	brne	_bios04_bs_l1
	cpi	ZH, high(VIDEOBUF_END)
	brne	_bios04_bs_l1
	popw	X
	popw	Z
	ret

; load screen from VIDEOBUF
BIOS04_ESC_CRISS_CS:
	pushw	Z
	pushw	X
	ldiw	Z, VIDEOBUF
	ldiw	X, 0xF800			; start of videoram
_bios04_cs_l1:
	ld	temp, Z+
	STRAM	XH, XL, temp
	adiw	X, 1
	cpi	ZL, low(VIDEOBUF_END)
	brne	_bios04_cs_l1
	cpi	ZH, high(VIDEOBUF_END)
	brne	_bios04_cs_l1
	popw	X
	popw	Z
	ret


; set screen output limits (output window)
BIOS04_ESC_CRISS_WIN:
	lds	temp, CON_ESC_C2
	cpi	temp, 1
	brlo	_bios_cw_err
	cpmem	temp, CRT_CHARS
	breq	_bios_cw_x0
	brsh	_bios_cw_err
_bios_cw_x0:
	sts	CON_WIN_X0, temp

	lds	temp, CON_ESC_C3
	cpi	temp, 1
	brlo	_bios_cw_err
	cpmem	temp, CRT_LINES
	breq	_bios_cw_y0
	brsh	_bios_cw_err
_bios_cw_y0:
	sts	CON_WIN_Y0, temp

	lds	temp, CON_ESC_C4
	cpmem	temp, CON_WIN_X0
	brlo	_bios_cw_err
	cpmem	temp, CRT_CHARS
	breq	_bios_cw_x1
	brsh	_bios_cw_err
_bios_cw_x1:
	sts	CON_WIN_X1, temp

	lds	temp, CON_ESC_C5
	cpmem	temp, CON_WIN_Y0
	brlo	_bios_cw_err
	cpmem	temp, CRT_LINES
	breq	_bios_cw_y1
	brsh	_bios_cw_err
_bios_cw_y1:
	sts	CON_WIN_Y1, temp

	sts	CON_WIN_CUR_X, one
	sts	CON_WIN_CUR_Y, one
	ret
_bios_cw_err:
	sts	CON_WIN_X0, zero
	sts	CON_WIN_X1, zero
	sts	CON_WIN_Y0, zero
	sts	CON_WIN_Y1, zero
	ret


; output window controls
BIOS04_ESC_CRISS_WIN_CTRLS:
	lds	temp, CON_WIN_X0
	cpi	temp, 0
	brne	_bios04_w_l1			; check that window is set
	ret
_bios04_w_l1:
	pushw	Z
	pushw	X
	pushw	Y
	push	FROMRAM0
	push	FROMRAM1
	push	zzA
	mov	temp, zzC
	tcbe	'C', BIOS_L04_WIN_CLR		; clear window (spaces)
	tcbe	'U', BIOS_L04_WIN_SCROLL_UP	; scroll window UP
;	tcbe	'D', BIOS_L04_WIN_SCROLL_DOWN	; 
;	tcbe	'R', BIOS_L04_WIN_SCROLL_RIGHT	; 
;	tcbe	'L', BIOS_L04_WIN_SCROLL_LEFT	; 
	tcbe	'F', BIOS_L04_WIN_DFRAME	; double frame
	tcbe	'f', BIOS_L04_WIN_SFRAME	; single frame
_bios04_w_ret:
	pop	zzA
	pop	FROMRAM1
	pop	FROMRAM0
	popw	Y
	popw	X
	popw	Z
	ret


; write to RAM
_bios_04_w_stram_x_a:
	push	temp
        STRAM	XH, XL, zzA
        pop	temp
	ret

; get frame start position in memory in X
_bios04_w_set_start:
	ldiw	X, 0xF800		; video RAM
	lds	temp, CON_WIN_Y0
	cpi	temp, 0
	breq	_bios04_wss_ret
_bios04_wss_l2:
	dec	temp
	breq	_bios04_wss_l1
	rcall	_bios04_w_lf		; goto next line
	rjmp	_bios04_wss_l2
_bios04_wss_l1:
	lds	temp, CON_WIN_X0
	cpi	temp, 0
	breq	_bios04_wss_ret
	dec	temp
	add	XL, temp
	adc	XH, zero		; start point
_bios04_wss_ret:
	ret	

; set next line position in memory
_bios04_w_lf:
	push	temp
	lds	temp, CRT_CHARS
	add	XL, temp
	adc	XH, zero
	pop	temp
	ret
_bios04_w_lf_y:
	push	temp
	lds	temp, CRT_CHARS
	add	YL, temp
	adc	YH, zero
	pop	temp
	ret


; fill temp bytes from X with zzA
_bios04_w_fill:
        pushw	X
        rcall	__bios04_w_fill
	popw	X
	ret
__bios04_w_fill:
        rcall	_bios_04_w_stram_x_a	; STRAM	XH, XL, zzA
	add	XL, one
	adc	XH, zero		; inc
	dec	temp
	brne	__bios04_w_fill
	ret

; move temp bytes from Y to X 
_bios04_w_copy:
	cpi	temp, 0
	breq	_bios04_wc_ret
	pushw	X
	pushw	Y
        push	zzA
_bios04_wc_l3:
        LDRAM	YH, YL, zzA
        rcall	_bios_04_w_stram_x_a	; STRAM	XH, XL, zzA
	add	XL, one
	adc	XH, zero		; inc
	add	YL, one
	adc	YH, zero		; inc
	dec	temp
	brne	_bios04_wc_l3
	pop	zzA
	popw	Y
	popw	X
_bios04_wc_ret:
	ret

; get w width
_bios04_w_getw:
        push	zzA
	lds	temp, CON_WIN_X1
	lds	zzA, CON_WIN_X0
	sub	temp, zzA
	inc 	temp
	pop	zzA
	ret

; get w height
_bios04_w_geth:
        push	zzA
	lds	temp, CON_WIN_Y1
	lds	zzA, CON_WIN_Y0
	sub	temp, zzA
	inc 	temp
	pop	zzA
	ret


; clear window
BIOS_L04_WIN_CLR:
	ldi	zzA, 32			; char to fill window
	rcall	_bios04_w_set_start
        rcall	_bios04_w_geth
        cpi	temp, 0
        breq	_bios04_wclr_l4
_bios04_wclr_l1:
        push 	temp
        rcall	_bios04_w_getw
        rcall	_bios04_w_fill
	rcall	_bios04_w_lf
	pop	temp
	dec	temp
	brne	_bios04_wclr_l1
_bios04_wclr_l4:
	rjmp	_bios04_w_ret		; return


;!!! moved to bios_misc_data.inc
;BIOS_L04_DFRAME_SYMBS:	.DB 201,205,187, 186,32,186, 200,205,188, 0
;BIOS_L04_SFRAME_SYMBS:	.DB 218,196,191, 179,32,179, 192,196,217, 0

; clear window
BIOS_L04_WIN_DFRAME:
	ldiw2	Z, BIOS_L04_DFRAME_SYMBS
	rjmp	BIOS_L04_WIN_FRAME

BIOS_L04_WIN_SFRAME:
	ldiw2	Z, BIOS_L04_SFRAME_SYMBS
	rjmp	BIOS_L04_WIN_FRAME

BIOS_L04_WIN_FRAME:
	rcall	_bios04_w_set_start
        rcall	_bios04_w_geth
        cpi	temp, 0
	breq	_bios04_wfr_l4		; wrong settings
        rcall	_bios04_wfr_line	; first line
        dec	temp
	breq	_bios04_wfr_l4
        dec	temp
	breq	_bios04_wfr_l3
_bios04_wfr_l2:
        pushw	Z
        rcall	_bios04_w_lf		; goto next line
        rcall	_bios04_wfr_line	; body line
	popw	Z
        dec	temp
        brne	_bios04_wfr_l2
_bios04_wfr_l3:
	adiw	Z, 3			; skip body line settings
        rcall	_bios04_w_lf		; goto next line
        rcall	_bios04_wfr_line	; last line
_bios04_wfr_l4:
	rjmp	_bios04_w_ret		; return


_bios04_wfr_line:
	pushw	X
	push	temp
        elpm	zzA, Z+
        rcall	_bios_04_w_stram_x_a	; STRAM	XH, XL, zzA
        add	XL, one
        adc	XH, zero		; goto next char
        rcall	_bios04_w_getw
        dec	temp
        dec	temp
        elpm	zzA, Z+
        rcall	__bios04_w_fill		; fill space
        elpm	zzA, Z+
        rcall	_bios_04_w_stram_x_a	; STRAM	XH, XL, zzA
        pop	temp
        popw	X
	ret

; scroll window UP
BIOS_L04_WIN_SCROLL_UP:
	rcall	_bios04_w_set_start
;        rcall	_bios04_w_getw
;        mov	FROMRAM1, temp
        rcall	_bios04_w_geth
        cpi	temp, 0
        breq	_bios04_wsu_ret
        dec	temp
        breq	_bios04_wsu_l3
        movw	Y, X
        lds	FROMRAM0, CRT_CHARS
_bios04_wsu_l2:
        movw	X, Y
        rcall	_bios04_w_lf_y		; goto next line
;	add	YL, FROMRAM0		; goto next line
;	adc	YH, zero
	push	temp
;	mov	temp, FROMRAM1
        rcall	_bios04_w_getw
        rcall	_bios04_w_copy		; copy line
        pop	temp
        dec	temp			; lines counter
        brne	_bios04_wsu_l2
_bios04_wsu_l3:
;	mov	temp, FROMRAM1
        movw	X, Y
        rcall	_bios04_w_getw
	ldi	zzA, 32			; char to fill
        rcall	_bios04_w_fill
_bios04_wsu_ret:
	rjmp	_bios04_w_ret		; return


; set relative cursor to output window
BIOS04_ESC_CRISS_CUR_WIN:
	lds	temp, CON_WIN_X0
	cpi	temp, 0
	brne	_bios04_y_l1		; check that window is set
	ret
_bios04_y_l1:
	push	zzA

	lds	zzA, CON_ESC_C2		; y position 1..n
	cpi	zzA, 1
	brlo	_bios04_y_ret
        rcall	_bios04_w_geth
        cp	zzA, temp
        breq	_bios04_y_l2
        brsh	_bios04_y_ret
_bios04_y_l2:

	mov	zzA, zzC		; x position 1..n
	cpi	zzA, 1
	brlo	_bios04_y_ret
        rcall	_bios04_w_getw
        cp	zzA, temp
        breq	_bios04_y_l3
        brsh	_bios04_y_ret
_bios04_y_l3:

	lds	temp, CON_ESC_C2
	sts	CON_WIN_CUR_Y, temp
	sts	CON_WIN_CUR_X, zzC
	lds	zzA, CON_WIN_Y0
	dec	zzA
	add	temp, zzA		; screen y position
	lds	zzA, CON_WIN_X0
	dec	zzA
	add	zzC, zzA		; screen x position
	rcall	BIOS04_ESC_CUR_SET	; set cusor
_bios04_y_ret:
	pop	zzA
	ret


; plays melody
BIOS04_ESC_CRISS_MELODY:
	lds	temp, CON_ESC_PAR	; load par
	cpi	temp, 0xff
	breq	_bios_04_melody_exec
_bios_04_melody_note:
	cpi	temp, 16
	brsh	_bios_04_melody_l1
	inc	temp
	sts	CON_ESC_PAR, temp
;	dec	temp
	subi	temp, -(cpd_mpbuf-1)	; temp+=cpd_mpbuf
	nportout_r temp, zzC		; save note
_bios_04_melody_l1:
	cpi	zzC, 0x04		; check for melody end code
	brne	_bios_04_melody_proceed
	sts	CON_ESC_PAR, FF	; next byte is command
_bios_04_melody_proceed:
	mov	FROMRAM2, FROMRAM1	; proceed with ESC processing
	ret	
_bios_04_melody_exec:
	nportout cpd_mpcmd, zzC		; sends command and stop processing
	ret
	