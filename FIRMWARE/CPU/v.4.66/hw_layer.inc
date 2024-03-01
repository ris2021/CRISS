HW_CONIN:	
	rjmp	_HW_CONIN
HW_CONOUT_CHAR:
	rjmp	_HW_CONOUT_CHAR
HW_CONOUT_SC:
	rjmp	_HW_CONOUT_SC
HW_CONOUT_ESC:
	rjmp	_HW_CONOUT_ESC
HW_PORTIN:
	rjmp	_HW_PORTIN
HW_PORTOUT:
	rjmp	_HW_PORTOUT
HW_LST:
	rjmp	_HW_LST
HW_INIT:
	rjmp	_HW_INIT

.EQU	HW_DESCRIPTOR_SIZE = 24
HW_OPTIONS:
	.DB	"CRISS CP/M V3.x "
	.DB	24, 80, 0, 0, 0, 0, 0, 0		; parameters: lines, chars, codepage, crt
	.DB	"ROBOTRON 1715 RU"
	.DB	24, 80, (1<<CRT_USE_ATTR)|2, 0, 0, 0, 0, 0		; parameters
	.DB	"ROBOTRON 1715 EN"
	.DB	24, 80, (1<<CRT_USE_ATTR)|3, 0, 0, 0, 0, 0		; parameters
	.DB	"KAYPRO CP/M     "
	.DB	24, 80, 3, 0, 0, 0, 0, 0		; parameters
	.DB	"TRS-80 CP/M     "
	.DB	24, 80, 3, 0, 0, 0, 0, 0		; parameters
	.DB	"KAYPRO CP/M 8bit"
	.DB	24, 80, 0, 0, 0, 0, 0, 0		; parameters
	.DB	"VT100/ANSI/VT52 "
	.DB	24, 80, (1<<CRT_USE_ATTR)|3, 0, 0, 0, 0, 0		; parameters
	.DB	0,0


_HW_CONIN:
	lds	temp, HW_FLAG
;	tcbe	0, HW0_CONIN
	tcbe	1, HW1_CONIN
	tcbe	2, HW2_CONIN
;	tcbe	3, HW0_CONIN
	rjmp	HW0_CONIN
;	ret

_HW_CONOUT_CHAR:
	lds	temp, HW_FLAG
;	tcbe	0, HW0_CONOUT_CHAR
	tcbe	1, HW1_CONOUT_CHAR
	tcbe	2, HW1_CONOUT_CHAR
	tcbe	3, HW3_CONOUT_CHAR
	tcbe	4, HW4_CONOUT_CHAR
	tcbe	6, HW6_CONOUT_CHAR	; ascii + lines + inv
;HW_CONOUT_DEFAULT:
	rjmp	HW0_CONOUT_CHAR
;	ret

_HW_CONOUT_SC:
	lds	temp, HW_FLAG
;	tcbe	0, HW0_CONOUT_SC
;	tcbe	1, HW1_CONOUT_SC
;	tcbe	2, HW1_CONOUT_SC
	tcbe	3, HW3_CONOUT_SC
;	tcbe	4, HW3_CONOUT_SC
	tcbe	5, HW3_CONOUT_SC
	tcbe	6, HW6_CONOUT_SC
;_HW_CONOUT_SC_DEFAULT:
	rjmp	HW0_CONOUT_SC
;	ret

_HW_CONOUT_ESC:
	lds	temp, HW_FLAG
;	tcbe	0, HW0_CONOUT_ESC
	tcbe	1, HW1_CONOUT_ESC
	tcbe	2, HW2_CONOUT_ESC
	tcbe	3, HW3_CONOUT_ESC
	tcbe	5, HW3_CONOUT_ESC
	tcbe	6, HW6_CONOUT_ESC
	rjmp	HW0_CONOUT_ESC
;	ret

_HW_PORTIN:
	lds	temp, HW_FLAG
;	tcbe	0, HW0_PORTIN
	tcbe	1, HW1_PORTIN
	tcbe	2, HW1_PORTIN
	rjmp	HW0_PORTIN
;	ret

_HW_PORTOUT:
	lds	temp, HW_FLAG
;	tcbe	0, HW1_PORTOUT
	tcbe	1, HW1_PORTOUT
	tcbe	2, HW1_PORTOUT
	rjmp	HW0_PORTOUT
;	ret

_HW_LST:
	lds	temp, HW_FLAG
	tcbe	1, HW1_LST
;	tcbe	2, HW1_LST
	rjmp	HW0_LST
;	ret

_HW_INIT:
	sts	HW_DATA, zero
	sts	HW_DATA+1, zero
	sts	HW_DATA+2, zero
	sts	HW_DATA+3, zero
;	ret


.MACRO  HWREPLACE
	pushw	Z
	push	zzA
	ldi	ZH, high((@0)*2)
	ldi	ZL, low((@0)*2)
HWREPLACE_l0:
	elpm	zzA, Z+
	cpi	zzA, 0
	breq	HWREPLACE_notfound	
	cp	zzA, temp
	breq	HWREPLACE_found
	adiw 	Z, 1
	rjmp	HWREPLACE_l0
HWREPLACE_found:
	elpm	temp, Z
	rjmp	HWREPLACE_end
HWREPLACE_notfound:
	pop	zzA
	push	zzA
	mov	temp, @1
HWREPLACE_end:
	pop	zzA
	popw	Z
.ENDM

#include "hw_0_criss.inc"		; CRISS
#include "hw_1_r1715.inc"		; Robotron 1715
#include "hw_2_r1715en.inc"		; Robotron 1715en
#include "hw_3_kaypro.inc"		; Kaypro
#include "hw_4_trs80.inc"		; microbee
#include "hw_6_vt100.inc"		; vt100
