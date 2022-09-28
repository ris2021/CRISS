; process system port data commands
	
	lds	temp, sysrq
	sbrs	temp, 7
	rjmp	SRP_MOUSE_LED

;	pushw	Z
	ldi	ZH, 0
	lds	ZL, sysaa

	cbr	temp, 0b11110000	; hide unused flags
	cpi	temp, 0x01		; read reg
	breq	SRP_REG_READ
	cpi	temp, 0x02		; write reg
	breq	SRP_REG_WRITE
	cpi	temp, 0x03		; write w-reg
	breq	SRP_REG_WRITE_W
	cpi	temp, 0x0E		; return CPD version
	breq	SRP_REG_VERSION
	cpi	temp, 0x0F		; hardware reset
	breq	SRP_REG_RESET

	rjmp	SRP_END

SRP_REG_READ:
	ld	tdata, Z                ; read reg value
	sts	sysvv, tdata            ; store to port var
	rjmp	SRP_END

SRP_REG_WRITE:
	lds	tdata, sysvv		; value to write
	st	Z, tdata		; set reg value
	rjmp	SRP_END

SRP_REG_WRITE_W:
	lds	tdata, sysvv		; value to write
	std	Z+1, zero		; set H reg value
	st	Z, tdata		; set L reg value - force write
	rjmp	SRP_END

SRP_REG_VERSION:
	ldi	tdata, 0
	sts	sysaa, tdata		;!!! major version
	ldi	tdata, 24
	sts	sysvv, tdata		;!!! minor version
	rjmp	SRP_END

SRP_REG_RESET:
	jmp	IRQ_HW_RESET		; hard reset

SRP_END:
;	popw	Z
	lds	temp, sysrq
	cbr	temp, 0b10001111	;
	sts	sysrq, temp 		; clear request flag, processing/processed
	rjmp	SRP_EXIT



SRP_MOUSE_LED:
	sbrs	temp, 5			; check change keyboard leds request
	rjmp	SRP_EXIT
	
	cpse	kbledr, zero
	rjmp	SRP_EXIT

	cbr	temp, 0b00100000	; clear change led request
	sts	sysrq, temp 		; 

  	inc	kbledr			; request to change led state
	ldi	temp, 0xed		; data to send
	mov	kbldata, temp
	rjmp	SRP_EXIT



