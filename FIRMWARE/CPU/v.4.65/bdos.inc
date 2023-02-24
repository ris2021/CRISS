BDOS_START:
        sts	BDOS_LAST_CALL, zzC
	NOTIFY	NOTIFY_BDOS, DBG_BDOS

	; decode function no in zzC, using ccbe macro
	ccbe	BDOS_0B_CONSTA, BDOS_0B_CONSTA_F
	ccbe	BDOS_06_DCONIO, BDOS_06_DCONIO_F

	ldi	zzPCh, 0xCA
	ldi	zzPCl, 0xBF		;!!!! just for the beginning and trap bdos calls !!!!
	ret



;CONSOLE STAT   NONE            LSB(A)=1 IF CHAR READY
BDOS_0B_CONSTA_F:
	BIOS_CALL BIOS_FUNC_CONST
	cpse	zzA, zero
	ldi	zzA, 0x01		; must return 01 if char is ready
	ret



; DIRECT CON I/O  Œ»-7 CHAR IN E  I/O STATUS IN A
; IF E=0FEH,
; INPUT IF E=0FFH
BDOS_06_DCONIO_F:
	cp	zzE, FF
	breq	BDOS_06_DCONIO_F_L1

	push	zzC
	mov	zzC, zzE
	BIOS_CALL BIOS_FUNC_CONOUT	; output char
	pop	zzC
	rjmp	BDOS_06_DCONIO_F_RET

BDOS_06_DCONIO_F_L1:
	BIOS_CALL BIOS_FUNC_CONST	; check char
	cp	zzA, zero
	breq	BDOS_06_DCONIO_F_RET
	BIOS_CALL BIOS_FUNC_CONIN	; read char

BDOS_06_DCONIO_F_RET:
	ret
