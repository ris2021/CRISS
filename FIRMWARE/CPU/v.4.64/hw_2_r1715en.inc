
HW2_CONIN:
	cpi	zzA, 0x80	; 
	brsh	hw2_conin_stop
	rjmp	HW1_CONIN_DO
	
hw2_conin_stop:	
	clr	zzA		; disabled key, no response
	ret
	


HW2_CONOUT_ESC:
	cpi	FROMRAM2, 3
	breq	HW2_CONOUT_ESC_3		; just for the case
	ret					; proceed otherwise
;	rjmp	HW0_CONOUT_ESC

HW2_CONOUT_ESC_3:
	lds	FROMRAM0, CON_ESC_C1		; get main command

	cpi	FROMRAM0, 0x5F
	breq	HW2_FRAMES			; empty char

HW2_CONOUT_ESC_CONT:
	rjmp	HW1_CONOUT_ESC


HW2_FRAMES:
	cpi	zzC, 0x40
	brlo	HW2_CONOUT_ESC_CONT
	cpi	zzC, 0x6C
	brsh	HW2_CONOUT_ESC_CONT
	subi	zzC, 0x40
	lsr	zzC
	lsr	zzC
	subi	zzC, -0x10			; start position of frame chars
	call	HW1_CONOUT_CHAR_DO		; apply attributes
	call	BIOS_L04_CHAR_L1		; echo char
	sts	CON_ESC, zero
	clr	FROMRAM2
	ret
