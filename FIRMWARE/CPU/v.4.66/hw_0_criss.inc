HW0_CONIN:
        call	HW1_CONIN_DO			; same as for Robotron 1715, but no decode
	ret


; --------------------------------------------------------------------------------------------------
HW0_CONOUT_CHAR:
;	mov	temp, zzC
	cpi	zzC, 0xff
	brne	HW0_CONOUT_CHAR_ret
	ldi	zzC, 0x7f
HW0_CONOUT_CHAR_ret:
	ret





HW0_CONOUT_SC:
	mov	temp, zzC

	tcbel	0x0d, BIOS_L04_ENTER		; Enter
	tcbel	0x0a, BIOS_L04_CR		; CR
	tcbel	0x08, BIOS_L04_BSP		; LEFT
	tcbel	0x0c, BIOS_L04_CLRSCR		; CLRSCR
	tcbel	0x09, BIOS_L04_TAB		; TAB
	tcbel	0x01, BIOS_L04_HOME		; HOME
	tcbel	0x07, BIOS_L04_BEEP		; BEEP
	tcbel	0x15, BIOS_L04_RIGHT		; RIGHT
	tcbel	0x1a, BIOS_L04_UP		; UP
	tcbel	0x18, BIOS_L04_CLRLN		; CLRLN
	tcbel	0x14, BIOS_L04_CLRCUR		; CLRCUR
	tcbel	0x16, BIOS_L04_CLREOL		; CLREOL

	tcbel	0x0e, BIOS_L04_SCRLOFF		; SCROLL OFF
	tcbel	0x0f, BIOS_L04_SCRLON		; SCROLL ON

	tcbel	0x1e, BIOS_L04_CUROFF		; CURSOR OFF
	tcbel	0x1f, BIOS_L04_CURON		; CURSOR ON

HW0_CONOUT_SC_RET:
	ret





HW0_CONOUT_ESC:
	lds	FROMRAM0, CON_ESC_C1		; getting main command
	clr	temp				; return 0 if processed

	cpi	FROMRAM2, 2			; FROMRAM2 = number of 
	brne	HW0_CONOUT_ESC_3

	clr	FROMRAM2
	tcbel0	'0', BIOS_L04_CUROFF
	tcbel0	'1', BIOS_L04_CURON
	tcbel0	'j', BIOS_L04_CLRSCR
	tcbel0	'H', BIOS_L04_HOME
	tcbel0	'J', BIOS_L04_CLRCUR
	tcbel0	'K', BIOS_L04_CLREOL
	tcbel0	'R', BIOS_ESC_KAYPRO_R		; delete line - error in manual
	tcbel0	'E', BIOS_ESC_KAYPRO_E		; insert line - error in manual
	rjmp	HW0_CONOUT_ESC_ret

HW0_CONOUT_ESC_3:	
	cpi	FROMRAM2, 3
	brne	HW0_CONOUT_ESC_4

	clr	FROMRAM2
	tcbel0	'B', BIOS04_ESC_KAYPRO_B	; 4/6/S
;	tcbel0	'B', BIOS04_ESC_KAYPRO_B
	tcbel0	'C', BIOS04_ESC_KAYPRO_C	; 4/6/S
	tcbel0	 9 , BIOS04_ESC_CRISS_09	; set x position
	tcbel0	'^', HW0_CONOUT_ESC_exit	; ignore
	tcbel0	'_', HW0_CONOUT_ESC_exit	; ignore
	tcbel0	'Z', BIOS04_ESC_CRISS_ZG	; select lines and char set
	tcbel0	'G', BIOS04_ESC_TRS_GRMODE	; set screen mode
	tcbel0	92,  BIOS04_ESC_CRISS_OUT	; '\' - output char as is for #1..#30
	tcbel0	'|', BIOS04_ESC_CRISS_VGA_OUT	; '|' - direct output char to screen not to VRAM
	tcbel0	'k', BIOS04_ESC_CRISS_SET_CON	; 'k' # - send char to CON input
	tcbel0	'w', BIOS04_ESC_CRISS_WIN_CTRLS	; clear/fill/scroll window
	tcbel0	'm', BIOS04_ESC_CRISS_MELODY	; plays music #1 #2 .. #n 0x04 CMD
	tcbel0	'q', BIOS04_ESC_CRISS_CLR_RAW	; CLR raw command
	tcbel0	'r', BIOS04_ESC_CRISS_CLR_CMD	; CLR Clrscr, clrLn, Scroll
HW0_CONOUT_ESC_3_RB_XY:
	cpi	FROMRAM0, 0x80
	brsh	HW0_CONOUT_ESC_3_l0
	rjmp	HW0_CONOUT_ESC_ret		; HW0_CONOUT_ESC_3_ret
HW0_CONOUT_ESC_3_l0:
	call	BIOS04_ESC_ROB_CUR
	rjmp	HW0_CONOUT_ESC_stop

HW0_CONOUT_ESC_4:	
	cpi	FROMRAM2, 4
	brne	HW0_CONOUT_ESC_5

	clr	FROMRAM2
	tcbel0	'=', BIOS04_ESC_KAYPRO_CUR
	tcbel0	'Y', BIOS04_ESC_TRS_CUR
	tcbel0	'y', BIOS04_ESC_CRISS_CUR_WIN	; cursor relative to output window
	tcbel0	'*', BIOS04_ESC_KAYPRO_PUTPIX
	tcbel0	' ', BIOS04_ESC_KAYPRO_CLRPIX
	tcbel0	'#', BIOS04_ESC_CRISS_TGLPIX
	tcbel0	'S', BIOS04_ESC_CRISS_SWP	; ??? no code
	tcbel0	'g', BIOS04_ESC_CRISS_GPIO	; output char to GPIO
	tcbel0	's', BIOS04_ESC_CRISS_CLR_OUT	; CLR output colored
	rjmp	HW0_CONOUT_ESC_ret

HW0_CONOUT_ESC_5:	
	cpi	FROMRAM2, 5
	brne	HW0_CONOUT_ESC_6

	clr	FROMRAM2
;	tcbel0	'f', BIOS04_ESC_CRISS_F
;	tcbel0	'F', BIOS04_ESC_CRISS_DF
;	tcbel0	'V', BIOS04_ESC_CRISS_VP
;	tcbel0	'e', BIOS04_ESC_CRISS_CLR
	rjmp	HW0_CONOUT_ESC_ret

HW0_CONOUT_ESC_6:
	cpi	FROMRAM2, 6
	brne	HW0_CONOUT_ESC_7

	clr	FROMRAM2
	tcbel0	'c', BIOS04_ESC_CRISS_CIRCLE
	tcbel0	'L', BIOS04_ESC_KAYPRO_PUTLN
	tcbel0	'D', BIOS04_ESC_KAYPRO_CLRLN
	tcbel0	'x', BIOS04_ESC_CRISS_INVLN
	tcbel0	'W', BIOS04_ESC_CRISS_WIN	; set output limits
	rjmp	HW0_CONOUT_ESC_ret

HW0_CONOUT_ESC_7:
	rjmp	HW0_CONOUT_ESC_stop		; too long seq, no match = consider as error, stop processing

HW0_CONOUT_ESC_stop:
	clr	FROMRAM2
	ret
;	rjmp	HW0_CONOUT_ESC_exit
HW0_CONOUT_ESC_ret:
	mov	FROMRAM2, FROMRAM1		; restore - proceed with input
HW0_CONOUT_ESC_exit:
	ret



HW0_PORTIN:
	call	HW1_PORTIN	; Ports from Robotron 1715
	ret


HW0_PORTOUT:
	call	HW1_PORTOUT	; Ports from Robotron 1715
	ret


HW0_LST:
	ret
