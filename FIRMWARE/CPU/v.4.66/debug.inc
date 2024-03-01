; debug z80 command from main cycle`
DBG_RES: 	rjmp	_DBG_RES
DBG_PORT_IN:	rjmp	_DBG_PORT_IN
DBG_PORT_OUT:	rjmp	_DBG_PORT_OUT
DBG_BDOS:	rjmp	_DBG_BDOS
DBG_BIOS:	rjmp	_DBG_BIOS
DBG_SD: 	rjmp	_DBG_SD
DBG_SDERR: 	rjmp	_DBG_SDERR
DBG_CONOUT:	rjmp	_DBG_CONOUT
DBG_IRQ:	rjmp	_DBG_IRQ
DEBUG_Z80:
DBG_z80:	rjmp	_DBG_z80
DBG_CR: 	rjmp	_DBG_CR		; uDBGcr
DBG_TEMP: 	rjmp	_DBG_TEMP

;_DBG_z80:
;	ret

DBG_ZRAM:
	LDRAM   ZH, ZL, temp
	uDBGh	temp
	ret

; ---------------- send current command and registers to UART
DBG_UART_CMD:
        push	temp
	mov	temp, zzPCh
	call	UART1_SEND
	mov	temp, zzPCl
	call	UART1_SEND
	mov	temp, zzF
	call	UART1_SEND
	mov	temp, zzA
	call	UART1_SEND
	mov	temp, zzB
	call	UART1_SEND
	mov	temp, zzC
	call	UART1_SEND
	mov	temp, zzD
	call	UART1_SEND
	mov	temp, zzE
	call	UART1_SEND
	mov	temp, zzH
	call	UART1_SEND
	mov	temp, zzL
	call	UART1_SEND
;	pushw	Z
;	push	zzA
;	ldi	Zh, 0x6e
;	ldi	Zl, 0x9c
;	LDRAM 	Zh, Zl, zzA
;	mov	temp, zzA
;	call	UART1_SEND
;	pop	zzA
;	popw	Z
	LDRAM 	zzPCh, zzPCl, temp
	call	UART1_SEND
	ldi	temp, 13
	call	UART1_SEND
	pop	temp
	ret

_DBG_RES:
	ret

; output BIOS calls
_DBG_BIOS:
	push	temp
	uDBGcr
	uDBGa	zzPCh, zzPCl
	uDBGc	'B'
	uDBGc	'I'
	uDBGc	'O'
	uDBGc	'S'
	uDBGc	':'
	uDBGc	' '
	lds	temp, BIOS_LAST_CALL
	uDBGh	temp
	uDBGc	' '
	uDBGh	zzB
	uDBGh	zzC
	uDBGc	' '
	uDBGh	zzA
	uDBGc	' '

	rcall	_DBG_CALL_FROM

	uDBGcr
	pop	temp
	ret

; -------------------- debug SD read operations to CON
_DBG_SD:
;	push	temp
	pushw	Z
	uDBGcr
	uDBGc	'S'
	uDBGc	'D'
	uDBGc	':'
	uDBGc	' '
	uDBGh	zzA
	uDBGh	XH
	uDBGh	XL
;	uDBGc	' '
;	uDBGz	zzCURR_DISK_NO
;	uDBGc	' '
;	uDBGz	zzCURR_TRACK_NUM
;	uDBGc	' '
;	uDBGz	zzCURR_SECTOR_NUM
;	uDBGc	' '
;	uDBGcr
	popw	Z
;	pop	temp
	ret

_DBG_SDERR:
	uDBGm	SD_ADDRESS+3
	uDBGm	SD_ADDRESS+2
	uDBGm	SD_ADDRESS+1
	uDBGm	SD_ADDRESS+0
	uDBGc	' '
	uDBGc	'E'
	uDBGm	SD_ERROR
	uDBGcr
;	uDBGc	' '
	ret

_DBG_TEMP:
        lds	temp, DBG_CODE
        uDBGu
	uDBGm	DBG_DATA
	uDBGc	' '
	ret
	
_DBG_CR:
	uDBGcr
	ret

; process debug CON request
_DBG_CONOUT:
	push	temp
	uDBGcr
	uDBGc	'C'
	uDBGc	'O'
	uDBGc	'N'
	uDBGc	':'
	uDBGc	' '
	uDBGh	zzC
	cpi	zzC, 27
	breq	_DBG_CONOUT_L2
	cpi	zzC, ' '
	brlo	_DBG_CONOUT_L1
	uDBGc	' '
	uDBGr	zzC
_DBG_CONOUT_L1:
	uDBGc	'/'
	uDBGm	CON_ESC
	uDBGm	CON_ESC_C1
	uDBGm	CON_ESC_C2
	uDBGm	CON_ESC_C3
	uDBGcr
	pop	temp
	ret
_DBG_CONOUT_L2:
	;!!!! for 1B add RAM addr where is executed !!!!!
	uDBGc	' '
	uDBGc	'E'
	uDBGc	'S'
	uDBGc	'C'
	rjmp	_DBG_CONOUT_L1


; output BDOS calls
_DBG_BDOS:
	push	temp
	uDBGcr
	uDBGa	zzPCh, zzPCl
	uDBGc	'B'
	uDBGc	'D'
	uDBGc	'O'
	uDBGc	'S'
	uDBGc	':'
	uDBGc	' '
;	lds	temp, BDOS_LAST_CALL
;	uDBGh	temp
;	uDBGc	' '
	uDBGh	zzC
	uDBGc	' '
	uDBGh	zzA
	uDBGc	' '
	uDBGw	zzD, zzE
	uDBGc	' '
	uDBGw	zzH, zzL
	uDBGc	' '

	rcall	_DBG_CALL_FROM

	uDBGcr
	pop	temp
	ret

; z80 port access
_DBG_PORT_IN:
	push	temp
	uDBGcr
	uDBGa	zzPCh, zzPCl
	uDBGc	'I'
	uDBGc	'N'
	uDBGc	'P'
	uDBGc	':'
	uDBGc	' '
	uDBGm	CDATA+2
	uDBGcr
	pop	temp
	ret

; z80 port access
_DBG_PORT_OUT:
	push	temp
	uDBGcr
	uDBGa	zzPCh, zzPCl
	uDBGc	'O'
	uDBGc	'U'
	uDBGc	'T'
	uDBGc	':'
	uDBGc	' '
	uDBGm	CDATA+2
	uDBGc	' '
	uDBGm	CDATA	
	uDBGcr
	pop	temp
	ret

_DBG_CALL_FROM:
	uDBGc	'<'
	pushw	Z
	mov	ZH, zzSPh
	mov	ZL, zzSPl
	LDRAM 	ZH, ZL, temp
	push	temp
	adiw	Z, 1
	LDRAM 	ZH, ZL, temp
	mov	ZH, temp
	pop	ZL
	sbiw	Z, 3		; looking for call start "CALL 5"
	uDBGw	Zh, ZL
	uDBGc	'('
	dec	ZH
	uDBGw	Zh, ZL		; addres in COM file
	uDBGc	')'
	popw	Z
	ret

_DBG_IRQ:
	push	temp
	uDBGcr
	uDBGc	'I'
	uDBGc	'R'
	uDBGc	'Q'
	uDBGc	':'
	uDBGc	' '
	in	temp, GPIOR1
	call	UART1_HEXOUT
;	uDBGm	IRQ_CPD_FLAG
	uDBGc	' '
	in	temp, GPIOR0
	call	UART1_HEXOUT
	uDBGc	' '
	uDBGm	INT_MASK
	uDBGc	' '
	uDBGm	INT_MASK+1
	uDBGcr
	pop	temp
	ret
