; input from native CPD port, in/out via temp
CPDPORTIN_CMD:
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT
	andi	temp, 0x3f	; just for the case clear 7,6 bits
	call 	DOSPI		; send port number
	delay3	45		; !!!!!! decrease !!!!!!
	ldi	temp, 0xff
	call	DOSPI		; get port value into temp
	SPI_STOP
	ret


; output to native CPD port
; temp - port, value = (CDATA+1) 	
CPDPORTOUT_CMD:
        cpi	temp, 214	; MUSIC port
        brne	_CPDPORTOUT_CMD_DO
        push	FROMRAM0
        lds	FROMRAM0, RTC_HW_DISABLE
        andi	FROMRAM0, (1<<HW_DSBL_MUS)
        pop	FROMRAM0
        breq	_CPDPORTOUT_CMD_DO	; ok - not disabled
        ret			; MUS is disabled, no output
_CPDPORTOUT_CMD_DO:
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT
        ori	temp, (1<<6)	; set PORTWRITE flag
	call 	DOSPI		; send port number
	delay3	15
	lds	temp, CDATA+1	; read data from CDATA+1 (data to output)
	call 	DOSPI		; send value to store
	SPI_STOP
	ret

	

; temp - port, return to temp
; >0xf4 - CPU local, >0xd0 - CPD, <0xd0 - processed by HW
PORTIN_CMD:
        cpi	temp, 0xf4
        brsh	CPU_SPECIAL_IN 	; CPU system port
        cpi	temp, 0xd0
        brsh	CPD_PORTIN_CMD 	; CPD system port

        sts	CDATA+2, temp
	push	temp
	lds	temp, SYS_NOTIFY	
	sbrc	temp, 1		; debug ESCAPE
	call	DBG_PORT_IN
	pop	temp

        jmp	HW_PORTIN	; Z80 port from HW

        ret


CPD_PORTIN_CMD:
	subi	temp, 0xd0
        rjmp	CPDPORTIN_CMD


; special CPU ports
CPU_SPECIAL_IN:
	ldi	ZH, 0x08
	mov	ZL, temp
	ld	temp, Z			; temp = z = port value

        cpi	ZL, low(PCMD_FE)
        brsh	CPU_SPECIAL_IN_RET	; cmd ports returns value

	sbrs	ZL, 0			; check that data is accessed
;CPU_SPECIAL_IN_PTR:
CPU_SPECIAL_IN_RET:
	ret				; no - return current ptr
CPU_SPECIAL_IN_DATA:
	dec	ZL			; choose ptr port (-1)
	ld	temp, Z			; z = ptr to data in BUF

	inc	temp 
	st	Z, temp			; store incremented value
	dec	temp			; restore original value

        cpi	ZL, low(PSVR_RQ)
        breq	CPU_SPECIAL_IN_SVR 	; CPU system port SVR access
        cpi	ZL, low(PVAR_RQ)
        breq	CPU_SPECIAL_IN_VAR 	; CPU system port VAR access
        cpi	ZL, low(PCAN_RQ)
        breq	CPU_SPECIAL_IN_CAN 	; CPU system port CAN access
        cpi	ZL, low(PLAN_RQ)
        breq	CPU_SPECIAL_IN_LAN 	; CPU system port LAN access
;        ret

CPU_SPECIAL_IN_SPI:
        cpi	temp, PSPI_BUF_MAXLEN
        brsh	CPU_SPECIAL_IN_OVF
        ldiw	Z, PSPI_BUF
;        rjmp	CPU_SPECIAL_IN_READ_BUF
CPU_SPECIAL_IN_READ_BUF:
	add	ZL, temp
	adc	ZH, zero
	ld	temp, Z			; read data from buffer
	ret

CPU_SPECIAL_IN_OVF:
	st	Z, temp			; restore original value
	ldi	temp, 0			; return 0 on overflow
	ret

CPU_SPECIAL_IN_VAR:
        cpi	temp, SHARABLE_MAXLEN
        brsh	CPU_SPECIAL_IN_OVF
        ldiw	Z, SHARABLE
        rjmp	CPU_SPECIAL_IN_READ_BUF

CPU_SPECIAL_IN_SVR:
        cpi	temp, SV_DATABLOCK_END-SV_DATABLOCK+1
        brsh	CPU_SPECIAL_IN_OVF
        ldiw	Z, SV_DATABLOCK
        rjmp	CPU_SPECIAL_IN_READ_BUF

CPU_SPECIAL_IN_CAN:
        cpi	temp, CAN_DATABLOCK_END-CAN_DATABLOCK+1
        brsh	CPU_SPECIAL_IN_OVF
        ldiw	Z, CAN_DATABLOCK
        rjmp	CPU_SPECIAL_IN_READ_BUF

CPU_SPECIAL_IN_LAN:
        cpi	temp, LAN_DATABLOCK_END-LAN_DATABLOCK+1
        brsh	CPU_SPECIAL_IN_OVF
        ldiw	Z, LAN_DATABLOCK
        rjmp	CPU_SPECIAL_IN_READ_BUF



; temp - port, value = (CDATA)
PORTOUT_CMD:
        cpi	temp, 0xf4
        brsh	CPU_SPECIAL_OUT	; CPU system port
        cpi	temp, 0xd0
        brsh	CPD_PORTOUT_CMD	; CPD system port

        sts	CDATA+2, temp
	push	temp
	lds	temp, SYS_NOTIFY	
	sbrc	temp, 1		; debug ESCAPE
	call	DBG_PORT_OUT
	pop	temp

        jmp	HW_PORTOUT	; Z80 port from HW
        ret


CPD_PORTOUT_CMD:
	subi	temp, 0xd0
	push	temp
	lds	temp, CDATA
	sts	CDATA+1, temp	; set value for output
	pop	temp
        rjmp	CPDPORTOUT_CMD


; special CPU ports
CPU_SPECIAL_OUT:
        cpi	temp, low(PCMD_FE)
        breq	CPU_SPECIAL_OUT_CMD_FE	; cmd ports works only for out
        cpi	temp, low(PCMD_FF)
        breq	CPU_SPECIAL_OUT_CMD_FF	; cmd ports works only for out

	ldi	ZH, 0x08
	mov	ZL, temp
	lds	temp, CDATA		; get data
	st	Z, temp			; set port value

	sbrs	ZL, 0			; check that data is accessed
	ret				; no - return current ptr
CPU_SPECIAL_OUT_DATA:
	dec	ZL			; choose ptr port (-1)
	ld	temp, Z			; z = ptr to data in BUF

	inc	temp 
	st	Z, temp			; store incremented value
	dec	temp			; restore original value

        cpi	ZL, low(PSVR_RQ)
        breq	CPU_SPECIAL_OUT_SVR 	; CPU system port SVR access
        cpi	ZL, low(PVAR_RQ)
        breq	CPU_SPECIAL_OUT_VAR 	; CPU system port VAR access
        cpi	ZL, low(PCAN_RQ)
        breq	CPU_SPECIAL_OUT_CAN 	; CPU system port CAN access
        cpi	ZL, low(PLAN_RQ)
        breq	CPU_SPECIAL_OUT_LAN 	; CPU system port LAN access

CPU_SPECIAL_OUT_SPI:
        cpi	temp, PSPI_BUF_MAXLEN
        brsh	CPU_SPECIAL_OUT_OVF
        ldiw	Z, PSPI_BUF

CPU_SPECIAL_OUT_WRITE_BUF:
	add	ZL, temp
	adc	ZH, zero
	lds	temp, CDATA		; get data
	st	Z, temp			; write data to buffer
	ret

CPU_SPECIAL_OUT_OVF:
	st	Z, temp			; restore original value
;	ldi	temp, 0			; return 0 on overflow
	ret

CPU_SPECIAL_OUT_VAR:
        cpi	temp, SHARABLE_MAXLEN
        brsh	CPU_SPECIAL_OUT_OVF
        ldiw	Z, SHARABLE
        rjmp	CPU_SPECIAL_OUT_WRITE_BUF

CPU_SPECIAL_OUT_SVR:
        cpi	temp, SV_DATABLOCK_END-SV_DATABLOCK+1
        brsh	CPU_SPECIAL_OUT_OVF
        ldiw	Z, SV_DATABLOCK
        rjmp	CPU_SPECIAL_OUT_WRITE_BUF

CPU_SPECIAL_OUT_CAN:
        cpi	temp, CAN_DATABLOCK_END-CAN_DATABLOCK+1
        brsh	CPU_SPECIAL_OUT_OVF
        ldiw	Z, CAN_DATABLOCK
        rjmp	CPU_SPECIAL_OUT_WRITE_BUF

CPU_SPECIAL_OUT_LAN:
        cpi	temp, LAN_DATABLOCK_END-LAN_DATABLOCK+1
        brsh	CPU_SPECIAL_OUT_OVF
        ldiw	Z, LAN_DATABLOCK
        rjmp	CPU_SPECIAL_OUT_WRITE_BUF


        ; special commands with external devices
CPU_SPECIAL_OUT_CMD_FE:
        rjmp	_CPU_SPECIAL_OUT_CMD_FE


        ; special commands logic
CPU_SPECIAL_OUT_CMD_FF:
        rcall	_CPU_SPECIAL_OUT_CMD_FF
        sts	PCMD_FF, temp
        ret


        ; special commands with external devices
_CPU_SPECIAL_OUT_CMD_FE:
        lds	temp, CDATA
	cpi	temp, fe_spi_base	; 0
	brne	_CPU_SPECIAL_OUT_CMD_FE_l0	
	rjmp	SPCMD_EXEC_SPI
_CPU_SPECIAL_OUT_CMD_FE_l0:
	cpi	temp, fe_sd_base	; 1
	breq	SPCMD_SD_INIT
	cpi	temp, fe_can_base	;16
	brlo	SPCMD_EEPROM
	cpi	temp, fe_lan_base	;48
	brlo	SPCMD_CAN
	cpi	temp, fe_rtc_base	;80
	brlo	SPCMD_LAN
	cpi	temp, fe_res_base	;96
	brlo	SPCMD_RTC
	jmp	USER_PORT_FE		; for commands >0x80 user exit
;	ret;


SPCMD_SD_INIT:
	call	SD_INIT
	lds	temp, SD_TYPE
	sts	PCMD_FE, temp
	ret


	; EEPROM access shares SPI buffer
	;.EQU	ROM_BUF_ADDR_ROM = PSPI_BUF
	;.EQU	ROM_BUF_ADDR_RAM = PSPI_BUF+2
	;.EQU	ROM_BUF_ADDR_LENGTH = PSPI_BUF+2
SPCMD_EEPROM:
	subi	temp, fe_eeprom_base
;	cfmem	HW_FOUND, HW_FOUND_ROM
;	breq	SPCMD_notfound
	jmp	EEPROM_CMD


SPCMD_CAN:
	subi	temp, fe_can_base
;	cfmem	HW_FOUND, HW_FOUND_CAN
;	breq	SPCMD_notfound
	jmp	CAN_CMD


SPCMD_LAN:
	subi	temp, fe_lan_base
;	cfmem	HW_FOUND, HW_FOUND_LAN
;	breq	SPCMD_notfound
	jmp	LAN_CMD


SPCMD_RTC:
	subi	temp, fe_rtc_base
;	cfmem	HW_FOUND, HW_FOUND_RTC
;	breq	SPCMD_notfound
	jmp	RTC_CMD



SPCMD_notfound:
	sts	PCMD_FE, FF		; error mark
	ret




SPCMD_EXEC_SPI:
	lds	temp, PSPI_SPEED
	push	temp
	lds	temp, PSPI_ADDR
;	push	temp
	SPI_INIT_STACK			; init SPI Macros

	; access pre-selected SPI module
	push	zzA
	lds	zzA, PSPI_RQ		; buf length (set after buffer fill outs)
	subi	zzA, 2			; remove addr and prescaler from data block
	ldiw	Z, PSPI_BUF_DATA	; select SPI buffer
	SPI_SELECT			; select device
CSP_SPI_EXEC_L1:
	cpi	zzA, 0
	breq	CSP_SPI_EXEC_END
	dec	zzA
	ld	temp, Z
	call	DOSPI
	st	Z+, temp		; store response
	rjmp	CSP_SPI_EXEC_L1
CSP_SPI_EXEC_END:
	sts	PCMD_FE, temp		; last received value as port value
	SPI_STOP
	pop	zzA
	ret



_CPU_SPECIAL_OUT_CMD_FF:
        lds	temp, CDATA

	lds	FROMRAM0, PORT_FF_CCMD	; command is processed?
	cpi	FROMRAM0, 32
	breq	_pReg
	sts	PORT_FF_CCMD, zero

;        sts	PCMD_FF, temp
        cpi	temp, 32
        brlo	_pfloat			; floating point operation
        cpi	temp, 32
        breq	_pff_start_ccmd
	ret

_pff_start_ccmd:
	sts	PORT_FF_CCMD, temp
	ret

_pff_stop_ccmd:
	sts	PORT_FF_CCMD, zero
	ret
	

_pfloat:
	sts	FLIB_CMD, temp
	jmp	FLOAT

_pReg:
	mov	ZL, temp
	ldi	ZH, 0
	ld	temp, Z
	rjmp	_pff_stop_ccmd

