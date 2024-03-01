CAN_INIT:
	jmp	__CAN_INIT
CAN_CMD:
	jmp	_CAN_CMD


; standard reset procedure
__CAN_INIT:
	push	temp
	ldi	temp, 0
	rcall	CAN_CMD
	pop	temp
	ret



; init CAN interface from default settings for mask as well
_CAN_INIT:
_CAN_INIT_BUF:
	push	zzC

	CAN_RESET		; reset, enter configuration mode

	ldi	zzC, 0b10000000
	CAN_CALL_WRITE CAN_REG_CANCTRL	; Normal operation mode, SOF signalling enabled

	CAN_READ_REG CAN_REG_CANSTAT
	andi	temp, 0b11100000
	cpi	temp, 0x80
	breq	_CAN_INIT_do
	rjmp	_CAN_INIT_ret	; reset didn't pass

_CAN_INIT_do:
				; start setting bit timing from parameters
	lds	zzC, CAN_BT_SJW
	lsl	zzC
	lsl	zzC
	lsl	zzC
	lsl	zzC
	lsl	zzC
	lsl	zzC
	lds	temp, CAN_BT_BRP
	or	zzC, temp
	CAN_CALL_WRITE CAN_REG_CNF1

	ldi	zzC, 0x80		; BTLMODE = 1
	lds	temp, CAN_BT_PS1
	lsl	temp
	lsl	temp
	lsl	temp
	or	zzC, temp
	lds	temp, CAN_BT_PSEG
	or	zzC, temp
	CAN_CALL_WRITE CAN_REG_CNF2

	ldi	zzC, 0x80		; SOF signalling = 1
	lds	temp, CAN_BT_PS2
	or	zzC, temp
	CAN_CALL_WRITE CAN_REG_CNF3

	lds	zzC, CAN_ID_MY		; setting filter 0 with my ID
	CAN_CALL_WRITE CAN_REG_RXF0SIDH
	lds	zzC, CAN_ID_MY+1
	CAN_CALL_WRITE CAN_REG_RXF0SIDL
	lds	zzC, CAN_ID_MY+2
	CAN_CALL_WRITE CAN_REG_RXF0EID8
	lds	zzC, CAN_ID_MY+3
	CAN_CALL_WRITE CAN_REG_RXF0EID0

	ldi	zzC, 0b11111111		; setting mask for standard messages
	CAN_CALL_WRITE CAN_REG_RXM0SIDH
	ldi	zzC, 0b11100000
	CAN_CALL_WRITE CAN_REG_RXM0SIDL
	ldi	zzC, 0
	CAN_CALL_WRITE CAN_REG_RXM0EID8
	ldi	zzC, 0
	CAN_CALL_WRITE CAN_REG_RXM0EID0

	ldi	zzC, 0b00100000		; Receive only valid messages with standard identifiers that meet filter criteria
					; No pending to BUF1
	CAN_CALL_WRITE CAN_REG_RXB0CTRL

	ldi	zzC, 0b00000100
	CAN_CALL_WRITE CAN_REG_CANCTRL	; Normal operation mode, SOF signalling enabled

        ldi	temp, 0x80	; report success

_CAN_INIT_ret:
	pop	zzC
	rjmp	_CAN_CMD_ret



; returns RX status in temp: bit 6 = message in rxb0
_CAN_GET_RX_STATUS:
        SPI_SELECT
	iSPI	CAN_CMD_RXSTAT
	iSPI	0xff			; read response
        SPI_DESELECT
	rjmp	_CAN_CMD_ret


; returns status in temp
_CAN_GET_STATUS:
        SPI_SELECT
	iSPI	CAN_CMD_STATUS
	iSPI	0xff			; read response
        SPI_DESELECT
	rjmp	_CAN_CMD_ret


_CAN_SET_TX_LEN:
	push	zzC
	lds	zzC, CAN_MBUF_OUT_L
	cpi	zzC, 9 
	brsh	_CAN_SET_TX_LEN_ret	; bad length
	CAN_CALL_WRITE CAN_REG_TXB0DLC	; set outgoing messages length
_CAN_SET_TX_LEN_ret:
	mov	temp,zzC
	pop	zzC
	rjmp	_CAN_CMD_ret


_CAN_SEND_PACKET:
	lds	temp, CAN_MBUF_PAR+1	; TX buf no
	cpi	temp, 0
	brne	_CAN_SEND_PACKET_RX12

	ldi	temp, CAN_CMD_LOADTX0
	rjmp	_CAN_SEND_PACKET_DO

_CAN_SEND_PACKET_RX12:
	cpi	temp, 1
	brne	_CAN_SEND_PACKET_RX12
	ldi	temp, CAN_CMD_LOADTX1
	rjmp	_CAN_SEND_PACKET_DO

_CAN_SEND_PACKET_RX2:
	ldi	temp, CAN_CMD_LOADTX2

_CAN_SEND_PACKET_DO:
	pushw	Y
	push	zzC

        SPI_SELECT
        call	DOSPI
;	iSPI	CAN_CMD_LOADTX0
	ldi	zzC, 4
	ldiw	Y, CAN_ID_REMOTE	; address
_CAN_SEND_PACKET_L4:
	ld	temp, Y+
        call	DOSPI
        dec	zzC
        brne	_CAN_SEND_PACKET_L4

	lds	temp, CAN_MBUF_OUT_L
	cpi	temp, 9 
	brlo	_CAN_SEND_PACKET_L2	; length ok
	ldi	temp, 8			; fix it otherwise
_CAN_SEND_PACKET_L2:
	mov	zzC, temp		; bytes to send
        call	DOSPI			; send DLC

	ldiw	Y, CAN_DATA_BUF
_CAN_SEND_PACKET_L1:
	cpi	zzC, 0
	breq	_CAN_SEND_PACKET_L3
	ld	temp, Y+
	call	DOSPI
	dec	zzC
	brne	_CAN_SEND_PACKET_L1

_CAN_SEND_PACKET_L3:
        SPI_DESELECT

	lds	zzC, CAN_MBUF_PAR+1	; TX buf no
	andi	zzC, 0x03
	ldi	temp, 1
	cpi	zzC, 0
	breq 	_CAN_SEND_PACKET_L5
_CAN_SEND_PACKET_L6:
	lsl	temp
	dec	zzC
	brne	_CAN_SEND_PACKET_L6

_CAN_SEND_PACKET_L5:
	andi	temp, 0x07
	ori	temp, CAN_CMD_RTS
	push	temp
        SPI_SELECT
        pop	temp
        call	DOSPI
;        iSPI	CAN_CMD_RTS0	; send buf0
        SPI_DESELECT

	lds	temp, CAN_MBUF_PAR+1	; TX buf no - success code

_CAN_SEND_PACKET_ret:
	pop	zzC
        popw	Y
	rjmp	_CAN_CMD_ret


_CAN_ABORT_TX:
	CAN_WRITE_REG CAN_REG_TXB0CTRL, 0
	rjmp	_CAN_CMD_ret

	
_CAN_GET_TX_STATUS:
	CAN_READ_REG CAN_REG_TXB0CTRL
	rjmp	_CAN_CMD_ret



;_CAN_RECEIVE_PACKET_RX1:
;	ldi	temp, CAN_CMD_READRX1
;	rjmp	_CAN_RECEIVE_PACKET_DO

; read received packet, no control
_CAN_RECEIVE_PACKET:
	lds	temp, CAN_MBUF_PAR	; RX buf no
	cpi	temp, 0
	brne	_CAN_RECEIVE_PACKET_RX1

	ldi	temp, CAN_CMD_READRX0
	rjmp	_CAN_RECEIVE_PACKET_DO

_CAN_RECEIVE_PACKET_RX1:
	ldi	temp, CAN_CMD_READRX1	; 0 or 1
_CAN_RECEIVE_PACKET_DO:
	push	zzC
	pushw	Z
	ldiw	Z, CAN_MSG_HDR		; place to store
	push	temp
        SPI_SELECT
        pop	temp
        call	DOSPI			; send command
;
;	iSPI	CAN_CMD_READRX0		; read RXB0
	ldi	zzC, 4
_CAN_RECEIVE_PACKET_L3:
	call	DOSPI			; read header
	st	Z+, temp
	dec	zzC
	brne	_CAN_RECEIVE_PACKET_L3	

	ldiw	Z, CAN_DATA_BUF		; place to store
	call	DOSPI			; Read DLC
	mov	zzC, temp
	andi	zzC, 0x0f
	cpi	zzC, 9			; check correct length
	brlo	_CAN_RECEIVE_PACKET_L4
	ldi	zzC, 8			; repair for errors
_CAN_RECEIVE_PACKET_L4:
	sts	CAN_MBUF_IN_L, zzC	; save length
_CAN_RECEIVE_PACKET_L1:
	cpi	zzC, 0
	breq	_CAN_RECEIVE_PACKET_L2
	call	DOSPI			; read reg
	st	Z+, temp
	dec	zzC
	brne	_CAN_RECEIVE_PACKET_L1	
_CAN_RECEIVE_PACKET_L2:
        SPI_DESELECT
_CAN_RECEIVE_PACKET_ret:
	popw	Z
	pop	zzC
	lds	temp, CAN_MBUF_IN_L
	rjmp	_CAN_CMD_ret




_CAN_RESET_CMD:
	CAN_RESET		; reset, enter configuration mode
	rjmp	_CAN_CMD_ret
	



; execute CAN interface command
_CAN_CMD:	
	lds	FROMRAM0, HW_FOUND
	sbrs	FROMRAM0, HW_FOUND_CAN
	jmp	SPCMD_notfound

	pushw	X
	pushw	Y
	pushw	Z
	push	r19

	; commands that doesn't access chip
;	tcbe	2,  _CAN_COPY_RAM_BUF
;	tcbe	3,  _CAN_COPY_BUF_RAM
;	tcbe	11, _CAN_CRC

	; commands that work with chip
        SPI_INIT SPI_SLAVE_CAN, SPI_FCK_DIV_4
	tcbe	0,  _CAN_INIT
	tcbe	1,  _CAN_INIT_BUF
	tcbe	6,  _CAN_SEND_PACKET
	tcbe	7,  _CAN_RECEIVE_PACKET
	tcbe	8,  _CAN_GET_RX_STATUS
	tcbe	17, _CAN_GET_STATUS
	tcbe	21, _CAN_SET_TX_LEN
	tcbe	22, _CAN_ABORT_TX
	tcbe	23, _CAN_GET_TX_STATUS
	tcbe	24, _CAN_RESET_CMD
_CAN_CMD_ret:
        SPI_STOP
_CAN_CMD_end:
	sts	PCMD_FE, temp			; store response
        pop	r19
	popw	Z
	popw	Y
	popw	X
	ret


; write zzC to register temp
CAN_EXEC_WRITE:
	push	zzC
	push	temp
	SPI_SELECT
	iSPI	CAN_CMD_WRITE
	pop	temp
	call	DOSPI		; send address
	pop	temp
	call	DOSPI		; send data
        SPI_DESELECT
	ret
