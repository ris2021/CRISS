	; ROBOTRON 1715 compatibility

; --------------------------------------------------------------------------------------------------
HW1_CONIN:

	cpi	zzA, 0x1E	; NUMLOCK
	brne	hw1_conin_process
	call	SYSTEM_BEEP
	push	FROMRAM0
	lds	temp, CON_ATTR_XOR
	ldi	FROMRAM0, (1<<CRT_ATTR_S0)
	eor	temp, FROMRAM0
	sts	CON_ATTR_XOR, temp
	pop	FROMRAM0	
;	ldi	temp, BIOS_FUNC_REFRESH_HW
;	call	BIOS		; refresh screen
	clr	zzA		; disabled key, no response
	ret

hw1_conin_process:
;	cpi	zzA, 0x60	; decode Russian symbols
;	lds	temp, CON_ATTR_XOR
;	sbrc	temp, CRT_ATTR_S0
;	rjmp	HW1_CONIN_S1
	
;HW1_CONIN_S0:
	cpi	zzA, 0x7F	; BackSpace
	breq	HW1_CONIN_DO

	cpi	zzA, 0x60	; decode Russian symbols
	brlo	HW1_CONIN_DO
	cpi	zzA, 0x80
	brlo	HW1_CONIN_l1

	ldiw2	Z, HW1_CONIN_DECODER
	subi	zzA, 0x80
;	ldiw2	Z, HW1_CONIN_DECODER
;	subi	zzA, 0x80
;	add	ZL, zzA
;	adc	ZH, zero
;	elpm	zzA, Z		; decoded symbol
;	call	HW1_CONIN_DECODE
;	rjmp	HW1_CONIN_DO
	rjmp	HW1_DECODE_AND_DO

;HW1_CONIN_S1:
;	cpi	zzA, 0x41
;	brlo	HW1_CONIN_DO
;	cpi	zzA, 0x80
;	brsh	HW1_CONIN_S1_L2

;	ldiw2	Z, HW1_CONIN_S1_DECODER_L
;	subi	zzA, 0x40
;	rjmp	HW1_DECODE_AND_DO

;HW1_CONIN_S1_L2:
;	ldiw2	Z, HW1_CONIN_S1_DECODER_R
;	subi	zzA, 0x80

HW1_DECODE_AND_DO:
	call	HW1_CONIN_DECODE
	rjmp	HW1_CONIN_DO
			

HW1_CONIN_l1:
	subi	zzA, 0x20	; lowcase to uppercase

HW1_CONIN_DO:
	nportin cpd_kactk	; key scancode
	HWREPLACE R1715scancodes2, zzA

	mov	zzD, temp       ; scancode

	ldi	temp, 0xe0	; 1 1 1 ? CAPS/LOCK S0/S1 SHIFT CTRL
	mov	zzE, temp	; status code

	mov	zzB, zero
	mov	zzC, zzD
	ret

HW1_CONIN_DECODE:
	add	ZL, zzA
	adc	ZH, zero
	elpm	zzA, Z		; decoded symbol
	ret

HW1_CONIN_DECODER:
	.DB	'a', 'b', 'w', 'g', 'd', 'e', 'v', 'z', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'
	.DB	'r', 's', 't', 'u', 'f', 'h', 'c', '~', '{', '}', 'x', 'y', 'x', '|', '`', 'q'
	.DB	'a', 'b', 'w', 'g', 'd', 'e', 'v', 'z', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'
	.DB	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
	.DB	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
	.DB	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
	.DB	'r', 's', 't', 'u', 'f', 'h', 'c', '~', '{', '}', 'x', 'y', 'x', '|', '`', 'q'
	.DB	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '

HW1_CONIN_S1_DECODER_R:
	.DB	'a', 'b', 'w', 'g', 'd', 'e', 'v', 'z', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p'
	.DB	'r', 's', 't', 'u', 'f', 'h', 'c', '~', '[', ']', 'x', 'y', 'x', '|', '`', 'q'
	.DB	'A', 'B', 'W', 'G', 'D', 'E', 'V', 'Z', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P'
	.DB	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
	.DB	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
	.DB	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
	.DB	'R', 'S', 'T', 'U', 'F', 'H', 'C', '^', '{', '}', 'X', 'Y', 'X',  92, '@', 'Q'
	.DB	' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '

HW1_CONIN_S1_DECODER_L:
	.DB	'@', 'f', 'i', 's', 'w', 'y', 'a', 'p', 'r', '[', 'o', 'l', 'd', 'x', 't', ']'
	.DB	'z', 'j', 'k', 'y', 'e', 'g', 'm', 'c', '~', 'n', 'q', 'h', '|', '|', 'x', '_'
	.DB	'`', 'F', 'I', 'S', 'W', 'Y', 'A', 'P', 'R', '{', 'O', 'L', 'D', 'X', 'T', '}'
	.DB	'Z', 'J', 'K', 'Y', 'E', 'G', 'M', 'C', '^', 'N', 'Q', 'H', '|', '|', 'X', '_'

R1715scancodes2:
	.DB	0x0d, 0x80	;TAB
	.DB	0x66, 0x7f	;DEL
	.DB	0x5a, 0x9e	;Enter
	.DB	0, 0



; --------------------------------------------------------------------------------------------------
HW1_CONOUT_CHAR:
	cpi	zzC, 0x80			; Robotron works with chars 32-127 only
	brsh	HW1_CONOUT_CHAR_80

HW1_CONOUT_CHAR_DO:
	push	FROMRAM0
;	clr	temp
	ldi	temp, BIOS_FUNC_ECON_ATTR_GET
	call	BIOS				; ECON_GET_ATTR			; read attr value (temp)
	lds	FROMRAM0, CON_ATTR_XOR		; default charset s0/s1
;	lds	temp, CON_ESC_C5		; attribute
	eor	temp, FROMRAM0
	sbrc	temp, CRT_ATTR_S0		; alternative znakogen table?
	call	HW1_TRANSLATE_S1		; s1 russian charset
	sbrc	temp, CRT_ATTR_REV		; inverse?
	ori	zzC, 0x80			; select inverse chars
	pop	FROMRAM0
	rjmp	HW1_CONOUT_CHAR_exit
	
HW1_CONOUT_CHAR_80:
	mov	temp, zzC
	ldi	zzC, 0	 			; ret from tcbe will return temp=0
	tcbel	0x83, BIOS_L04_CUROFF		; CURSOR OFF
	tcbel	0x82, BIOS_L04_CURON		; CURSOR ON
	tcbe	0x84, HW1_CHAR_84		; attr
	tcbe	0x85, HW1_CHAR_85		; 
	tcbe	0x86, HW1_CHAR_86		; 
	tcbe	0x87, HW1_CHAR_87		; 
	tcbe	0x90, HW1_CHAR_90		; s0
	tcbe	0x91, HW1_CHAR_91		; s1
	cpi	temp, 0xff
	brne	HW1_CONOUT_CHAR_empty
	ldi	zzC, 0x7f
	rjmp	HW1_CONOUT_CHAR_exit
HW1_CONOUT_CHAR_empty:
	ldi	zzC, ' '			; ignore all char > 0x80 and replace with 0
;	ldi	zzC, ':'			;!!!! debug!!!!!!
HW1_CONOUT_CHAR_exit:
	mov	temp, zzC
HW1_CONOUT_CHAR_ret:
 	ret


HW1_CHAR_84:
	ldi	zzC, 0x40
	rjmp	HW1_ATTRIBUTE2
HW1_CHAR_85:
	ldi	zzC, 0x50
	rjmp	HW1_ATTRIBUTE2
HW1_CHAR_86:
	ldi	zzC, 0x41
	rjmp	HW1_ATTRIBUTE2
HW1_CHAR_87:
	ldi	zzC, 0x51
	rjmp	HW1_ATTRIBUTE2

HW1_ATTRIBUTE2:
	ldi	temp, BIOS_FUNC_CRT_ATTR	; put screen attribute
	call	BIOS
	clr	zzC
	ret


; set default 	;s0
HW1_CHAR_90:
	sts	CON_ATTR_XOR, zero
	rjmp	HW1_CONOUT_CHAR_exit
HW1_CHAR_91:	; s1
	ldi	temp, (1<<CRT_ATTR_S0)
	sts	CON_ATTR_XOR, temp
	rjmp	HW1_CONOUT_CHAR_exit


HW1_TRANSLATE_S1:
	cpi	zzC, 0x40
	breq	_hw1_s1_40
	cpi	zzC, 0x41
	brlo	_hw1_s1_ret
	cpi	zzC, 0x5F+1
	brsh	_hw1_s1_ret
	subi	zzC, 0x40			; lowrcase russian characters
_hw1_s1_ret:
	ret
_hw1_s1_40: 
	ldi	zzC, 0x1f
	ret

; --------------------------------------------------------------------------------------------------
;HW1_CONOUT_SC:
;	mov	temp, zzC
 ;
;	tcbel	0x0d, BIOS_L04_ENTER		; Enter
;	tcbel	0x0a, HW1_BIOS_L04_CR		; CR
;	tcbel	0x08, BIOS_L04_BSP		; BSP
;	tcbel	0x0c, HW1_BIOS_L04_CLRSCR	; CLRSCR
;	tcbel	0x09, BIOS_L04_TAB		; TAB
;	tcbel	0x01, BIOS_L04_HOME		; HOME
;	tcbel	0x07, BIOS_L04_BEEP		; BEEP
;	tcbel	0x15, BIOS_L04_RIGHT		; RIGHT
;	tcbel	0x1a, BIOS_L04_UP		; UP
;	tcbel	0x18, BIOS_L04_CLRLN		; CLRLN
;	tcbel	0x14, BIOS_L04_CLRCUR		; CLRCUR
;	tcbel	0x16, BIOS_L04_CLREOL		; CLREOL
 ;
;HW1_CONOUT_SC_RET:
;        jmp	HW0_CONOUT_SC
;	ret

;HW1_BIOS_L04_CLRSCR:
;	call	BIOS_RESET_2			; clear attr screen
;	rjmp	HW1_CONOUT_SC_RET

;HW1_BIOS_L04_CR:
;	cpmemmem CURSOR_Y, CRT_LINES
;	brlo	HW1_CONOUT_SC_RET
;	call	ECON_ATTR_SCROLL
;	rjmp	HW1_CONOUT_SC_RET


; --------------------------------------------------------------------------------------------------
HW1_CONOUT_ESC:
	cpi	FROMRAM2, 3
	breq	HW1_CONOUT_ESC_3		; just for the case
	ret					; proceed otherwise
;	rjmp	HW0_CONOUT_ESC

HW1_CONOUT_ESC_3:
	lds	FROMRAM0, CON_ESC_C1		; get main command

	cpi	FROMRAM0, 0x5E
	breq	HW1_ATTRIBUTE			; set attribute
	cpi	FROMRAM0, 0x5F
	breq	HW1_FRAMES			; empty char

	cpi	FROMRAM0, 0x6E
	breq	HW1_ATTRIBUTE_HIDDEN		; set attribute, no echo

	call	BIOS04_ESC_ROB_CUR		; otherwise

HW1_CONOUT_ESC_ret:
	sts	CON_ESC, zero
	clr	FROMRAM2
	ret

	rjmp	HW0_CONOUT_ESC

;	cpi	FROMRAM0, 0x80
;	brlo	HW1_CONOUT_ESC_clr		; ignore attribute set commands

;	call	BIOS04_ESC_ROB_CUR		; cursor pos command

;HW1_CONOUT_ESC_clr:
;	clr	FROMRAM1			; stop processing
;HW1_CONOUT_ESC_ret:
;	mov	FROMRAM2, FROMRAM1		; restore - proceed with input
;HW1_CONOUT_ESC_exit:
;	ret


HW1_FRAMES:
	ldi	zzC, '+'
	ldi	temp, BIOS_FUNC_CONOUT
	call	BIOS
	rjmp	HW1_CONOUT_ESC_ret 

HW1_ATTRIBUTE:
	ldi	temp, BIOS_FUNC_CRT_ATTR	; put screen attribute
	call	BIOS
	rjmp	HW1_CONOUT_ESC_ret 

;	ldi	temp, BIOS_FUNC_ECON_ATTR_SET
;	call	BIOS				;ECON_SET_ATTR			; store attribute
;	ldi	zzC, ':'			;!!!! debug!!!!!!
;	ldi	temp, 0xfd
;	call	BIOS				; echo space 
;	sts	CON_ESC_C5, zzC			; store attribute
;	ldi	zzC, ' '			;!!!! debug - decode in future
;HW1_ATTRIBUTE_FILL:
;	ldi	zzC, '+'			;!!!! debug!!!!!!
;	ldi	temp, BIOS_FUNC_CRT_CHAR
;	call	BIOS				; echo space 
;	call	BIOS_L04_CHAR_L1		; echo space
;HW1_ATTRIBUTE_EXIT:
;	sts	CON_ESC, zero
;	clr	FROMRAM2
;	ret

HW1_ATTRIBUTE_HIDDEN:
	ldi	temp, BIOS_FUNC_ECON_ATTR_SET
	call	BIOS				;ECON_SET_ATTR			; store attribute
	rjmp	HW1_CONOUT_ESC_ret
;	sts	CON_ESC_C5, zzC			; store attribute
;	sts	CON_ESC, zero
;	clr	FROMRAM2
;	ret



; --------------------------------------------------------------------------------------------------
HW1_PORTIN:
        lds	temp, CDATA+2		; port requested
	tcbel	0x0c, HW1_PORTIN_0C	; port 12 - keyboard controller
	ret

HW1_PORTIN_0C:
	nportin cpd_kactk	; key scancode
;	HWREPLACE R1715scancodes, zero
	HWREPLACE R1715scancodes, zzA
;	cpse	temp, zero
	ret
;	mov	temp, zzA		; return key code otherwise
;	lds	temp, CON_LAST_CHAR	; return key code otherwise
;	ret
; robotron 1715 replacements ; scan-codes:
R1715scancodes:
	.DB	0x05, 0xd1	;f1
	.DB	0x06, 0xd2	;f2
	.DB	0x04, 0xd3	;f3
	.DB	0x0c, 0xd4	;f4
	.DB	0x03, 0xf5	;f5
	.DB	0x0b, 0xa0	;f6
	.DB	0x02, 0xa1	;f7
	.DB	0x0a, 0xa2	;f8
	.DB	0x01, 0xa3	;f9
	.DB	0x09, 0x83	;f10
	.DB	0x78, 0xc1	;f11
	.DB	0x07, 0xc0	;f12
	.DB	0x0d, 0x80	;TAB
	.DB	0x76, 0x1b	;ESC
	.DB	0x60, 0x82	;INS
	.DB	0x66, 0x7f	;BackSpace
	.DB	0x5f, 0x87	;home
	.DB	0x64, 139; 0x86	;up 134
	.DB	0x67, 0x89	;pgup
	.DB	0x5e, 136; 0x8a	;left  corrected from old program sources
	.DB	0x73, 0x8c	;??? 5
	.DB	0x63, 134; 0x8b	;right
	.DB	0x5c, 0x8e	;end
	.DB	0x62, 138; 0x88	;down
	.DB	0x65, 0x9d	;pgdn
	.DB	0x5a, 0x9e	;Enter
	.DB	0, 0


; --------------------------------------------------------------------------------------------------
HW1_PORTOUT:
        ; ROBOTRON compatibility
        lds	temp, CDATA+2		; port requested
	tcbel	0x0e, HW1_PORTOUT_0E
	tcbel	0x18, HW1_PORTOUT_18             ; crt settings
	tcbel	0x19, HW1_PORTOUT_19		; crt settings
HW1_PORTOUT_RET:
	ret;

HW1_PORTOUT_0E:
	;!!! keyboard for port 12 read -- code here
	ret

HW1_PORTOUT_18:
	lds	temp, HW_DATA
	tcbel	0x01, HW1_PORTOUT_18_L1		; port[19]=80 X
	tcbel	0x02, HW1_PORTOUT_18_L2		; port[19]=80 Y
	tcbel	0x05, HW1_PORTOUT_18_L3		; port[19]=0  1st
	tcbel	0x06, HW1_PORTOUT_18_L4		; port[19]=0  2nd - process it!
	ret

HW1_PORTOUT_18_L3:   				; ignore 1st parameter
	inc	temp
	sts	HW_DATA, temp			; inc (HW_DATA)
	ret

	; set line numbers
HW1_PORTOUT_18_L4:
	sts	HW_DATA, zero
;	nportin cpd_vstat			; read crt settings
;	andi	temp, 0b10000111		; clear lines number
;	push	zzA
;	lds	zzA, CDATA
;	subi	zzA, 63				; PORT[$18]:=64+R-1; R = 1..25
	lds	temp, CDATA
	subi	temp, 63			; PORT[$18]:=64+R-1; R = 1..25
	sts	CRT_LINES, temp			; store lines
;	call	BIOS_SET_VIDEO_MODE		; set display mode
	jmp	BIOS_SET_VIDEO_MODE		; set display mode and return
;	lsl	zzA
;	lsl	zzA
;	lsl	zzA
;	or	temp, zzA			; set new line number
;	pop	zzA
;	nportout cpd_vstat, temp		; store new settings
	ret

HW1_PORTOUT_18_L1:
	lds	temp, CDATA			; pos
	sts	HW_DATA+1, temp
	stst	HW_DATA, 2
	ret

HW1_PORTOUT_18_L2:
	lds	temp, CDATA			; line
	inc	temp
	sts	CURSOR_Y, temp
	lds	temp, HW_DATA+1			; pos
	inc	temp
	sts	CURSOR_X, temp
	call	CURSOR_APPLY_XY
	sts	HW_DATA, zero			; clear port[$19] request
	ret

HW1_PORTOUT_19:
	lds	temp, CDATA			; port value
	tcbel	0x80, HW1_PORTOUT_19_80		; cursor positioning
	tcbel	0x00, HW1_PORTOUT_19_00		; start crt setup
	tcbel	0x20, HW1_PORTOUT_19_20		; end of crt setup - nothing to do
	sts	HW_DATA, zero
	ret

HW1_PORTOUT_19_20:
	sts	HW_DATA, zero
	ret

HW1_PORTOUT_19_00:
	stst	HW_DATA, 5
	ret

HW1_PORTOUT_19_80:
	stst	HW_DATA, 1
	ret


HW1_LST:
	ret
