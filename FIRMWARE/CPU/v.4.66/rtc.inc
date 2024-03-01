RTC_INIT:	
	rjmp	_RTC_START
RTC_CMD:
	rjmp	_RTC_CMD


_RTC_SELECT:
	push	temp
	SPI_SELECT
	delay3	30
	pop	temp
	ret

_RTC_START:
	; start clock
	SPI_INIT SPI_SLAVE_RTC, SPI_FCK_DIV_16_CPHA	; /16, RTC supports fck till 2 MHz
	rcall	_RTC_SELECT
	iSPI	0x8F			; write control register
	iSPI	0x03			; activate ints for alarms and start RTC
	SPI_STOP
	ret



_RTC_READ_DO:
    	; access RTC chip
;	SPI_INIT SPI_SLAVE_RTC, SPI_FCK_DIV_16		; /16, RTC supports fck till 2 MHz
	pushw	X

	rcall	_RTC_SELECT
;	SPI_SELECT

	ldiw	X, RTC_SBUF
	mov	temp, r18
	call	DOSPI			; base address
_rtc_init_l8:
	iSPI	0xff
	st	X+, temp
	dec	r19
	brne  	_rtc_init_l8

	SPI_DESELECT
;    	SPI_STOP		    	; stop RTC access
	popw	X
	ret


_RTC_READ:
	ldi	r18, 0x00		; read control registers
	ldi	r19, 0x07		; read control registers
_RTC_READ_L0:
	rcall	_RTC_READ_DO
;	pushw	X
;	pushw	Y
;	pushw	Z
;	ZXYb	RTC_BUF, RTC_SECS, 7	; copy actual time to time buffer
;	popw	Z
;	popw	Y
;	popw	X

	rjmp	_RTC_CMD_ret


_RTC_ALARM0_READ:
	ldi	r18, 0x07		; read control registers
	ldi	r19, 0x04		; read control registers
	rjmp	_RTC_READ_L0


_RTC_ALARM1_READ:
	ldi	r18, 0x0b		; read control registers
	ldi	r19, 0x04		; read control registers
	rjmp	_RTC_READ_L0


_RTC_SET_TIME:
	rcall	_RTC_SELECT
;	SPI_SELECT
	iSPI	0x80
	lds	temp, RTC_SECS
	call	DOSPI
	lds	temp, RTC_MINS
	call	DOSPI
	lds	temp, RTC_HOURS
	call	DOSPI
	rjmp	_RTC_CMD_ret


_RTC_SET_DATE:
	rcall	_RTC_SELECT
;	SPI_SELECT
	iSPI	0x83
	lds	temp, RTC_DAY
	call	DOSPI
	lds	temp, RTC_DATE
	call	DOSPI
	lds	temp, RTC_MONTH
	call	DOSPI
	lds	temp, RTC_YEAR
	call	DOSPI
	rjmp	_RTC_CMD_ret


_RTC_SET_ROM:
	pushw	Z
	push	r19
	ldiw	Z, RTC_RAM
	ldi	r19, 96
	rcall	_RTC_SELECT
;	SPI_SELECT
	iSPI	0xa0
_ret_set_rom_l0:
	ld	temp, Z+
	call	DOSPI
	dec	r19
	brne	_ret_set_rom_l0
	pop	r19
	popw	Z
	rjmp	_RTC_CMD_ret


_RTC_READ_STATUS:
	rcall	_RTC_SELECT
;	SPI_SELECT
	iSPI	0x10
	iSPI	0xff
	rjmp	_RTC_CMD_ret
	

_RTC_LOAD_ROM:
	pushw	Z
	push	r19
	ldiw	Z, RTC_RAM
	ldi	r19, 96
	rcall	_RTC_SELECT
;	SPI_SELECT
	iSPI	0x20			; base address
_rtc_load_rom_l0:
	iSPI	0xff
	st	Z+, temp
	dec	r19
	brne  	_rtc_load_rom_l0
	pop	r19
	popw	Z
	rjmp	_RTC_CMD_ret



_RTC_CMD:
	lds	FROMRAM0, HW_FOUND
	sbrs	FROMRAM0, HW_FOUND_RTC
	jmp	SPCMD_notfound

	push	r18
	push	r19
	SPI_INIT SPI_SLAVE_RTC, SPI_FCK_DIV_16_CPHA		; /16, RTC supports fck till 2 MHz
        tcbe	0, _RTC_READ
        tcbe	1, _RTC_SET_TIME
        tcbe	2, _RTC_SET_DATE
        tcbe	3, _RTC_SET_ROM
        tcbe	4, _RTC_ALARM0_READ
        tcbe	5, _RTC_ALARM1_READ
        tcbe	6, _RTC_READ_STATUS
        tcbe	7, _RTC_LOAD_ROM
_RTC_CMD_ret:
	sts	PCMD_FE, temp			; store response
        SPI_STOP
	pop	r19
	pop	r18
	ret

	