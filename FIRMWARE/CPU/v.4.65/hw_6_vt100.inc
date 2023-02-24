; --------------------------------------------------------------------------------------------------


; --------------------------------------------------------------------------------------------------
HW6_CONOUT_CHAR:
;	ret
;	mov	temp, zzC
	cpi	zzC, 0xff
	brne	HW6_CONOUT_CHAR_L2
	ldi	zzC, 0x7f
	ret
HW6_CONOUT_CHAR_L2:
	cpi	zzC, 0x80
	brlo	HW6_CONOUT_CHAR_ret		; no translation required

	andi	zzC, 0x7f
	cpi	zzC, 0x60
	brlo	HW6_CONOUT_CHAR_ret		; no decoding required

	subi	zzC, 0x60
	pushw	Z
	ldiw2	Z, HW6_CONOUT_DECODER
	rcall	HW6_C_DECODE			; decode symbol
	popw	Z

HW6_CONOUT_CHAR_ret:
	ret


HW6_C_DECODE:
	add	ZL, zzC
	adc	ZH, zero
	elpm	zzC, Z		; decoded symbol
	ret

HW6_CONOUT_DECODER:
	.DB	 ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',0x13,0x11,0x10,0x12,0x0a,0x08
	.DB	0x08,0x08,0x08,0x08,0x06,0x05,0x07,0x04,0x09, ' ', ' ', ' ', ' ', ' ', ' ', ' '


HW6_CONOUT_DECODER_SC:
	.DB	 ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
	.DB	0x1b,0x1c, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',0x1d,0x1e

HW6_CONOUT_SC:
	mov	temp, zzC

	tcbel	0x0a, VT100_LF			; VT100 LF
	tcbel	0x0b, VT100_LF			; VT100 LF
	tcbel	0x0c, VT100_LF			; VT100 LF
	tcbel	0x0d, BIOS_L04_ENTER		; CR
	tcbel	0x07, BIOS_L04_BEEP		; VT100 custom tab
	tcbel	0x09, VT100_TAB			; VT100 custom tab
	tcbel	0x0e, VT100_G1			; VT100 G1
	tcbel	0x0f, VT100_G2			; VT100 G2
;	tcbel	0x17, BIOS_L04_CLRCUR		; CLRCUR
	tcbel	0x18, BIOS_ESC_CANCEL		; VT100 cancel ESC sequence
	tcbel	0x1b, BIOS_ESC_CANCEL		; VT100 cancel ESC sequence

	pushw	Z
	ldiw2	Z, HW6_CONOUT_DECODER_SC
	rcall	HW6_C_DECODE			; decode symbol
	popw	Z
	jmp	BIOS04_ESC_CRISS_OUT		; just output char
;	rjmp	BIOS_L04_CHAR_L1		; just output char
;	BIOS_L04_CHAR_L1
;	BIOS_CALL BIOS_FUNC_CONOUT		; output ^C symbol
;	
;	clr	temp				; no other codes available
;	ret




HW6_CONOUT_ESC:
	lds	FROMRAM0, CON_ESC_C1		; getting main command
	clr	temp				; return 0 if processed

	cpi	FROMRAM2, 2			; FROMRAM2 = number of 
	breq	HW6_CONOUT_ESC_2
	rjmp	HW6_CONOUT_ESC_3

HW6_CONOUT_ESC_2:
	clr	FROMRAM2
	;!!!!add optional table depending on HW_DATA[0] byte - current mode!!!!!
	tcbel0	 24, BIOS_ESC_CANCEL
	tcbel0	 25, BIOS_ESC_CANCEL
	tcbel0	'A', BIOS_L04_UP
	tcbel0	'B', BIOS_L04_ENTER
	tcbel0	'C', BIOS_L04_RIGHT
	tcbel0	'D', BIOS_L04_BSP		;!!! scroll in ANSI !!!!
	tcbel0	'F', BIOS_ESC_CANCEL		;!!! graph char set
	tcbel0	'G', BIOS_ESC_CANCEL		;!!! ASCII char set
	tcbel0	'H', BIOS_L04_HOME		;!!! TAB set in ANSI
	tcbel0	'I', BIOS_ESC_CANCEL		;!!! Reverse line feed ????
	tcbel0	'J', BIOS_L04_CLRCUR
	tcbel0	'K', BIOS_L04_CLREOL
	tcbel0	'=', BIOS_ESC_CANCEL		;!!! Enter alternate keypad mode
	tcbel0	'>', BIOS_ESC_CANCEL		;!!! Exit alternate keypad mode
	tcbel0	'<', VT100_ANSI			;!!! Enter ANSI mode
	tcbel0	'7', BIOS04_ESC_CUR_STORE
	tcbel0	'8', BIOS04_ESC_CUR_RESTORE
	tcbel0	's', BIOS04_ESC_CUR_STORE
	tcbel0	'u', BIOS04_ESC_CUR_RESTORE
	tcbel0	'c', VT100_RESET

	rjmp	HW0_CONOUT_ESC_ret


HW6_CONOUT_ESC_3:
	cpi	FROMRAM2, 3			; FROMRAM2 = number of 
	brne	HW6_CONOUT_ESC_4

	clr	FROMRAM2
	tcbel0	'[', VT100_ANSI_BR
	rjmp	HW0_CONOUT_ESC_ret

HW6_CONOUT_ESC_4:
	cpi	FROMRAM2, 4			; FROMRAM2 = number of 
	brne	HW6_CONOUT_ESC_5

	clr	FROMRAM2
	tcbel0	'Y', BIOS04_ESC_KAYPRO_CUR
	tcbel0	'[', VT100_ANSI_BR
	tcbel0	'(', VT100_CHARSET		;!!! char set
	tcbel0	')', VT100_CHARSET		;!!! char set

	rjmp	HW0_CONOUT_ESC_ret

HW6_CONOUT_ESC_5:	
	cpi	FROMRAM2, 5			; FROMRAM2 = number of 
	brne	HW6_CONOUT_ESC_6

	clr	FROMRAM2
	tcbel0	'[', VT100_ANSI_BR
	rjmp	HW0_CONOUT_ESC_ret

HW6_CONOUT_ESC_6:	
	cpi	FROMRAM2, 6			; FROMRAM2 = number of 
	brne	HW6_CONOUT_ESC_7

	clr	FROMRAM2
	tcbel0	'[', VT100_ANSI_BR
	rjmp	HW0_CONOUT_ESC_ret

HW6_CONOUT_ESC_7:	
	cpi	FROMRAM2, 7			; FROMRAM2 = number of 
	brne	HW6_CONOUT_ESC_8

	clr	FROMRAM2
	tcbel0	'[', VT100_ANSI_BR
	rjmp	HW0_CONOUT_ESC_ret

HW6_CONOUT_ESC_8:	
	cpi	FROMRAM2, 8			; FROMRAM2 = number of 
	brne	HW6_CONOUT_ESC_9

	clr	FROMRAM2
	tcbel0	'[', VT100_ANSI_BR
	rjmp	HW0_CONOUT_ESC_ret

HW6_CONOUT_ESC_9:	
VT100_IGNORE:
	jmp	BIOS_ESC_CANCEL			; stop processing


; process complex parameters
VT100_ANSI_BR:
        ;!!! check letter and process parameters here!
        cpi	zzC, 'A'
        brsh	VT100_ANSI_BR_PARS		; command received - process it!
        rjmp	HW0_CONOUT_ESC_ret		; not command yet, still parameter

VT100_ANSI_BR_PARS:				; decoding parameters
        pushw	Z
        pushw	Y
        push	zzA
        push	FROMRAM1
        ldi	FROMRAM0, 0			; parameters count
        ldiw	Z, CON_ESC_C2			; parameters area starts here
        ldiw	Y, CON_ESC_C1			; where results will be stored
;        st	Y, one				; just for the case: if no parameter than set=1 for A..C commands
VT100_ANSI_BR_L3:
        clr	zzA				; current parameter value
VT100_ANSI_BR_L2:
        ld	temp, Z+			; get next char
        cpi	temp, ';'			; check delimeter?
        brne	VT100_ANSI_BR_L4
        st	Y+, zzA				; store parameter
        inc	FROMRAM0			; inc praameter counter
        rjmp	VT100_ANSI_BR_L3		; start with next one

VT100_ANSI_BR_L4:
        cpi	temp, 'A'			; end of parameters list, command reached
        brsh	VT100_ANSI_BR_L1
        cpi	temp, '0'			; check for '0'..'9' range
        brlo	VT100_ANSI_BR_L2		; error - ignore and go to next char
        cpi	temp, '9'+1			; 
        brsh	VT100_ANSI_BR_L2		; error - ignore and go to next char
        subi	temp, '0'			; covert single char to number
        add	zzA, zzA			; need to mul zzA*10 and add new value, a=a*2 for the beginning
        mov	FROMRAM1, zzA
        add	zzA, zzA			; A=A*4
        add	zzA, zzA			; A=A*8
        add	zzA, FROMRAM1			; A=8*A+2*A = 10*A
        add	zzA, temp			; add decoded decimal value, zzA=actual value
        rjmp	VT100_ANSI_BR_L2		; goto next char

VT100_ANSI_BR_L1:
        st	Y+, zzA				; store last parameter
        inc	FROMRAM0			; inc praameter counter

	pop	FROMRAM1
        pop	zzA
        popw	Y
        popw	Z
VT100_ANSI_BR_CMD:				; FROMRAM0 = number of parameters, CON_ESC_C1..CON_ESC_C4 - decoded values
	clr	FROMRAM2			; indicates that command is processed
	ccbel0	'A', VT100_BR_A
	ccbel0	'B', VT100_BR_B
	ccbel0	'C', VT100_BR_C
	ccbel0	'D', VT100_BR_D
	ccbel0	'K', VT100_CLR_K
	ccbel0	'J', VT100_CLR_J
	ccbel0	'H', VT100_CUR
	ccbel0	'f', VT100_CUR
	ccbel0	'm', VT100_ATTR
	ccbel0	'q', VT100_LEDS
	ccbel0	'h', VT100_CMD_h
	ccbel0	'l', VT100_CMD_l
VT100_ANSI_BR_RET:
	ret					; unknown command

		
VT100_CUR:
	cpi	FROMRAM0, 2
	brlo	VT100_ANSI_BR_RET		; not enough parameters - ignore
	lds	temp, CON_ESC_C1
	cpi	temp, 24			;????? check is Y from 0 or from 1?
	brsh	VT100_ANSI_BR_RET		; bad parameters - ignore
	lds	temp, CON_ESC_C2
	cpi	temp, 80
	brsh	VT100_ANSI_BR_RET		; bad parameters - ignore
	lds	temp, CON_ESC_C1
	sts	CURSOR_Y, temp
	lds	temp, CON_ESC_C2
	sts	CURSOR_X, temp
	jmp	CURSOR_APPLY_XY			; set cursor and return

VT100_BR_DEF1:					; set default parameter=1 if not specified
	lds	FROMRAM0, CON_ESC_C1
	cpse	FROMRAM0, zero
	ret
	inc	FROMRAM0
	ret

VT100_BR_A:					; cursor up for Pn lines
	lds	temp, CURSOR_Y
	rcall	VT100_BR_DEF1
;	lds	FROMRAM0, CON_ESC_C1
	sub	temp, FROMRAM0
	cpi	temp, 24
	brsh	VT100_ANSI_BR_RET		; bad parameters - ignore
	sts	CURSOR_Y, temp
	jmp	CURSOR_APPLY_XY			; set cursor and return

VT100_BR_B:
	lds	temp, CURSOR_Y
	rcall	VT100_BR_DEF1
;	lds	FROMRAM0, CON_ESC_C1
	add	temp, FROMRAM0
	cpi	temp, 24
	brsh	VT100_ANSI_BR_RET		; bad parameters - ignore
	sts	CURSOR_Y, temp
	jmp	CURSOR_APPLY_XY			; set cursor and return

VT100_BR_C:
	lds	temp, CURSOR_X
	rcall	VT100_BR_DEF1
;	lds	FROMRAM0, CON_ESC_C1
	add	temp, FROMRAM0
	cpi	temp, 80
	brsh	VT100_ANSI_BR_RET		; bad parameters - ignore
	sts	CURSOR_X, temp
	jmp	CURSOR_APPLY_XY			; set cursor and return

VT100_BR_D:
	lds	temp, CURSOR_X
	rcall	VT100_BR_DEF1
;	lds	FROMRAM0, CON_ESC_C1
	sub	temp, FROMRAM0
	cpi	temp, 80
	brsh	VT100_ANSI_BR_RET		; bad parameters - ignore
	sts	CURSOR_X, temp
	jmp	CURSOR_APPLY_XY			; set cursor and return

VT100_CLR_K:
	lds	temp, CON_ESC_C1		; subcommand
	tcbel	0, BIOS_L04_CLREOL
	tcbel	1, BIOS_L04_CLRBOL
	tcbel	2, BIOS_L04_CLRLN
	ret

VT100_CLR_J:
	lds	temp, CON_ESC_C1		; subcommand
	tcbel	0, BIOS_L04_CLRCUR
	tcbel	1, BIOS_L04_CLR_BOS		; clear from the beginning of the screen to cursor
	tcbel	2, BIOS_L04_CLRSCR
	ret

VT100_TAB:
VT100_G1:
VT100_G2:
VT100_ATTR:
VT100_LEDS:
VT100_RESET:
VT100_CMD_h:
VT100_CMD_l:
VT100_CHARSET:
	ret

VT100_LF: 
	;!!!!!write code here!!!! depends on settings!!!!
	jmp	BIOS_L04_CR

VT100_ANSI:
	sts	HW_DATA, one			; indicates ANSI mode!
	ret
