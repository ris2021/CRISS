; --------------------------------------------------------------------------------------------------

HW3_CONOUT_CHAR:
	andi	zzC, 0x7f
	ldi	temp, BIOS_FUNC_ECON_ATTR_GET
	call	BIOS				; ECON_GET_ATTR			; read attr value (temp)
;	lds	temp, CON_ESC_C5		; attributes
	sbrc	temp, 4				; inverse
	ori	zzC, 0x80			; select inverted chars
	ret



HW3_CONOUT_SC:
	mov	temp, zzC

	tcbel	0x0c, BIOS_L04_RIGHT		; RIGHT
	tcbel	0x0b, BIOS_L04_UP		; UP
	tcbel	0x17, BIOS_L04_CLRCUR		; CLRCUR
	tcbel	0x18, BIOS_L04_CLREOL		; CLREOL
	tcbel	0x1a, BIOS_L04_CLRSCR		; CLRSCR
	tcbel	0x1e, BIOS_L04_HOME		; HOME

	jmp	HW0_CONOUT_SC




HW3_CONOUT_ESC:
	cpi	FROMRAM2, 3
	breq	HW3_CONOUT_ESC_3		; just for the case
	rjmp	HW0_CONOUT_ESC

HW3_CONOUT_ESC_3:
	lds	FROMRAM0, CON_ESC_C1		; get main command

	cpi	FROMRAM0, 'B'
	breq	HW3_ATTRIBUTE_B			; set attribute
	cpi	FROMRAM0, 'C'
	breq	HW3_ATTRIBUTE_C			; empty char

HW3_CONOUT_ESC_exit:
	rjmp	HW0_CONOUT_ESC

HW3_CONOUT_ESC_stop:
	sts	CON_ESC, zero
	clr	FROMRAM2
	ret

HW3_ATTRIBUTE_B:
        cpi	zzC, '0'
	brlo	HW3_CONOUT_ESC_exit
        cpi	zzC, '4'
	brsh	HW3_CONOUT_ESC_exit

        cpi	zzC, '0'
	brne	HW3_CONOUT_ESC_stop

	ldi	zzC, (1<<CRT_ATTR_REV)
	ldi	temp, BIOS_FUNC_CRT_ATTR	; put screen attribute
	call	BIOS
	clr	zzC
;	ret
;	ldi	temp, 1<<4
;	sts	CON_ESC_C5, temp		; store attribute
	rjmp	HW3_CONOUT_ESC_stop


HW3_ATTRIBUTE_C:
        cpi	zzC, '0'
	brlo	HW3_CONOUT_ESC_exit
        cpi	zzC, '4'
	brsh	HW3_CONOUT_ESC_exit

        cpi	zzC, '0'
	brne	HW3_CONOUT_ESC_stop

	ldi	zzC, 0
	ldi	temp, BIOS_FUNC_CRT_ATTR	; put screen attribute
	call	BIOS
	clr	zzC
;	sts	CON_ESC_C5, zero		; store attribute
	rjmp	HW3_CONOUT_ESC_stop



