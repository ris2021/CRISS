LAN_CMD:
;	jmp	_LAN_CMD		; exec port cmd command
_LAN_CMD:
	lds	FROMRAM0, HW_FOUND
	sbrs	FROMRAM0, HW_FOUND_LAN
	jmp	SPCMD_notfound

	lds	FROMRAM0, RTC_HW_DISABLE	; check that LAN is enabled
	sbrc	FROMRAM0, HW_DSBL_LAN
	jmp	SPCMD_notfound

	pushw	X
	pushw	Y
	pushw	Z
	push	r19
	push	FROMRAM0
	push	FROMRAM1
	push	FROMRAM2

	; commands that doesn't access chip
	ldi	r19, low(_LAN_CMD_end)
	push	r19	
	ldi	r19, high(_LAN_CMD_end)
	push	r19				; address for RET
        tcbe	2,  _LAN_COPY_RAM_BUF		;!!ok
        tcbe	3,  _LAN_COPY_BUF_RAM		;!!ok
	tcbe	11, _LAN_IP_CRC			;!!ok
	tcbe	15, _LAN_BUILD_USER_ETH_FRAME	;!!ok
	tcbe	12, _LAN_BUILD_USER_IP_FRAME	;!!ok
	tcbe	13, _LAN_BUILD_USER_UDP_FRAME	;!!ok
	tcbe	14, _LAN_BUILD_ARP_RESP		;!!ok
	tcbe	16, _LAN_CHECK_FRAME_TYPE	;!!ok
	tcbe	19, _LAN_GET_UDP_DATA		;!!ok
	tcbe	20, _LAN_BUILD_ARP_REQUEST	;!!ok
	tcbe	22, _LAN_BUILD_PING_REQUEST	;!!ok
	tcbe	23, _LAN_BUILD_PING_RESPONSE	;!!ok
	tcbe	21, _LAN_SEND_UDP		;!!ok		; build and send UDP 
	tcbe	24, _LAN_SEND_TCP		;!!todo!!!; build and send TCP 
	pop	r19
	pop	r19				; clear stack if command didn't match

_LAN_CMD_P2:
	; commands that work with the chip
	ldi	r19, low(_LAN_CMD_ret)
	push	r19	
	ldi	r19, high(_LAN_CMD_ret)
	push	r19				; address for RET

        SPI_INIT SPI_SLAVE_LAN, LAN_SPI_SETTINGS	; SPI_FCK_DIV_4	; start SPI

	tcbe	18, _LAN_PROCESS_MESSAGES	; !!ok
	; internal system commands
	tcbe	119, _LAN_SEND_CON		; send zzC to SERVER CON
	tcbe	120, _LAN_SEND_PR		; send zzC to PR-SRV
	tcbe	121, _LAN_SEND_PRN		; send zzC to PRN-SRV
	tcbe	122, _LAN_SEND_RSD		; send zzC to RSD-SRV

        tcbe	LAN_FUNC_INIT,        _LAN_INIT	;!!ok 0
        tcbe	LAN_FUNC_INIT_CUSTOM, _LAN_INIT_BUF	;!!ok 1
        tcbe	4,  _LAN_GET_ETH_REG		;!!ok
        tcbe	5,  _LAN_GET_MX_REG		;!!ok
	tcbe	8,  _LAN_GET_EPKTCNT		;!!ok
	tcbe	9,  _LAN_UPDATE_REG		;!!ok
	tcbe	10, _LAN_GET_PHY_REG		;!!ok
	tcbe	17, _LAN_GET_ESTAT		;!!ok
        tcbe	6,  _LAN_SEND_USER_PACKET	;!!ok
        tcbe	7,  _LAN_RECEIVE_USER_PACKET	;!!ok
	pop	r19
	pop	r19			; clear stack if wrong command
	ldi	temp, 0xfd		; wrong command
_LAN_CMD_ret:
        SPI_STOP
_LAN_CMD_end:
	sts	PCMD_FE, temp		; store response

	pop	FROMRAM2
	pop	FROMRAM1
	pop	FROMRAM0
        pop	r19
	popw	Z
	popw	Y
	popw	X
	ret


; 10 us delay
LAN_WAIT_10us:
	_LAN_WAIT_10us
	ret


; init LAN chip for default values
_LAN_INIT:
	rcall	_LAN_INIT_DO
	sts	PR_BUF_CNT, zero
	sts	CON_BUF_CNT, zero
	ldi	temp, 0
	ret	; rjmp	_LAN_CMD_ret


;init LAN chip and set MY MAC address
_LAN_INIT_BUF:
	rcall	_LAN_INIT_DO		; base init
	rcall	_LAN_SET_MY_MAC		; set MAC
	ldi	temp, 1
	ret	; rjmp	_LAN_CMD_ret


; copy zRAM to LAN_BUF
_LAN_COPY_RAM_BUF:	
	ldiw	X, LAN_BUF		; address to store to
	ldw	Z, LAN_MBUF_OUT		; address to read from
	ldw	Y, LAN_MBUF_OUT_L	; number of bytes to read from
	call	MCOPY_RAM_AVR_Y
	ret	; rjmp	_LAN_CMD_end


; copy LAN_BUF to zRAM
_LAN_COPY_BUF_RAM:
	ldiw	X, LAN_BUF		; address to store to
	ldw	Z, LAN_MBUF_IN		; address to read from
	ldw	Y, LAN_MBUF_IN_L	; number of bytes to read from
	call	MCOPY_AVR_RAM_Y
	ret	; rjmp	_LAN_CMD_ret


;calculates CRC starting from LAN_BUF+(LAN_PAR) with (LAN_UPD_DATA) length, returns result to (LAN_UPD_DATA)
_LAN_IP_CRC:
	pushw	Y
	ldw	Z, LAN_PAR		; offset
	ldw	Y, LAN_UPD_DATA
	ldi	temp, high(LAN_BUF)
	add	ZH, temp		; convert local address to ram address
					; low(LAN_BUF) === 0
	rcall	_LAN_IPCRC
	stw	LAN_UPD_DATA, Z
	popw	Y
	ret	; rjmp	_LAN_CMD_end


; return chip register value
_LAN_GET_ETH_REG:
	rcall	_LAN_CMD_PAR_PREPARE
	push	temp
	LAN_ETH_REG_READ_S
	ret	; rjmp	_LAN_CMD_ret


; return chip MX register value
_LAN_GET_MX_REG:
	rcall	_LAN_CMD_PAR_PREPARE
	push	temp
	LAN_Mx_REG_READ_S
	ret	; rjmp	_LAN_CMD_ret



_LAN_GET_EPKTCNT:
	rcall	LAN_SELECT_BANK_1
	LAN_ETH_REG_READ LAN_EPKTCNT		; check that there is unread packet
	ret	; rjmp	_LAN_CMD_ret



_LAN_GET_ESTAT:
	LAN_ETH_REG_READ LAN_ESTAT		; check status
	ret	; rjmp	_LAN_CMD_ret



; return chip MX register value
_LAN_GET_PHY_REG:
	rcall	_LAN_CMD_PAR_PREPARE
	push	temp

	LAN_CREG_WRITE_C_S LAN_MIREGADR, LAN_REG_WRITE	; address
	LAN_CREG_WRITE_C LAN_MICMD, 0b00000001, LAN_REG_BFS
	DELAY_10us
;	LAN_ETH_REG_READ LAN_MISTAT
	LAN_CREG_WRITE_C LAN_MICMD, 0b00000001, LAN_REG_BFC
	LAN_ETH_REG_READ LAN_MIRDL
	sts	LAN_UPD_DATA, temp
	LAN_ETH_REG_READ LAN_MIRDH
	sts	LAN_UPD_DATA+1, temp
	ret	; rjmp	_LAN_CMD_ret



_LAN_UPDATE_REG:
	rcall	_LAN_CMD_PAR_PREPARE
	lds	FROMRAM0, LAN_UPD_DATA+1	; operation
	andi	FROMRAM0, 0b11100000		; mask unused bits
	or	temp, FROMRAM0			; make command
        SPI_SELECT
	call	DOSPI
	lds	temp, LAN_UPD_DATA		; value to store
	call	DOSPI
	SPI_DESELECT
	ret	; rjmp	_LAN_CMD_ret


; sends buf0 packet
_LAN_SEND_USER_PACKET:
	rcall	_LAN_SET_USER
	rcall	LAN_SEND_PACKET
	ret	; rjmp	_LAN_CMD_ret


;rceives buf0 packet
_LAN_RECEIVE_USER_PACKET:
	rcall	_LAN_SET_USER
	rcall	LAN_RECEIVE_PACKET
	rcall	LAN_RECEIVE_PACKET_NEXT		; set processed and go to next packet
	ldstt2	LAN_MBUF_IN_L, LAN_OP_BUF_LEN	; store received data length
	ret	; rjmp	_LAN_CMD_ret


; build ETH frame from the RAM (DATA)
_LAN_BUILD_USER_ETH_FRAME:
	ldiw	X, LAN_ETH_DATA		; address to store to (ETH DATA)
	ldw	Z, LAN_MBUF_OUT		; address to read from
	ldw	Y, LAN_MBUF_OUT_L	; number of bytes to read from
	call	MCOPY_RAM_AVR_Y

	rcall	_LAN_SET_USER
_LAN_BUILD_USER_ETH_FRAME_act:
	sts	LAN_OP_ETHTYPE, zero
_LAN_BUILD_USER_ETH_FRAME_act2:
	rcall	LAN_BUILD_ETH_FRAME
	ldstt2	LAN_MBUF_OUT_L, LAN_OP_BUF_LEN
	ret	; rjmp	_LAN_CMD_end


; make ip frame from buf data and lan_block
_LAN_BUILD_USER_IP_FRAME:
	ldiw	X, LAN_IP_DATA		; address to store to (IP DATA)
	ldw	Z, LAN_MBUF_OUT		; address to read from
	ldw	Y, LAN_MBUF_OUT_L	; number of bytes to read from
	call	MCOPY_RAM_AVR_Y

	rcall	_LAN_SET_USER
_LAN_BUILD_USER_IP_FRAME_act:
	rcall	LAN_BUILD_IP_FRAME
	rjmp	_LAN_BUILD_USER_ETH_FRAME_act	; build eth frame
;	rcall	LAN_BUILD_ETH_FRAME
;	ldstt2	LAN_MBUF_OUT_L, LAN_OP_BUF_LEN
;	ret	; rjmp	_LAN_CMD_end


; make udp frame from buf data and lan_block
_LAN_BUILD_USER_UDP_FRAME:
	ldiw	X, LAN_UDP_DATA		; address to store to (IP DATA)
	ldw	Z, LAN_MBUF_OUT		; address to read from
	ldw	Y, LAN_MBUF_OUT_L	; number of bytes to read from
	call	MCOPY_RAM_AVR_Y

	rcall	_LAN_SET_USER
_LAN_BUILD_USER_UDP_FRAME_act:
	ldi	temp, LAN_PROTOCOL_UDP
	sts	LAN_PROTOCOL, temp
	sts	LAN_OP_PROTOCOL, temp		; set UDP
	rcall	LAN_BUILD_UDP_FRAME
	rjmp	_LAN_BUILD_USER_IP_FRAME_act	; Proceed with IP, ETH
;	rcall	LAN_BUILD_IP_FRAME
;	rcall	LAN_BUILD_ETH_FRAME
;	ldstt2	LAN_MBUF_OUT_L, LAN_OP_BUF_LEN
;	ret	; rjmp	_LAN_CMD_end



; make tcp frame from buf data and lan_block
_LAN_BUILD_USER_TCP_FRAME:
	ldiw	X, LAN_TCP_DATA		; address to store to (IP DATA)
	ldw	Z, LAN_MBUF_OUT		; address to read from
	ldw	Y, LAN_MBUF_OUT_L	; number of bytes to read from
	call	MCOPY_RAM_AVR_Y

	rcall	_LAN_SET_USER
_LAN_BUILD_USER_TCP_FRAME_act:
	ldi	temp, LAN_PROTOCOL_TCP
	sts	LAN_PROTOCOL, temp
	sts	LAN_OP_PROTOCOL, temp		; set UDP
	rcall	LAN_BUILD_TCP_FRAME
	rjmp	_LAN_BUILD_USER_IP_FRAME_act	; Proceed with IP, ETH
;	rcall	LAN_BUILD_IP_FRAME
;	rcall	LAN_BUILD_ETH_FRAME
;	ldstt2	LAN_MBUF_OUT_L, LAN_OP_BUF_LEN
;	ret	; rjmp	_LAN_CMD_end



; build and send ARP request to user server
_LAN_BUILD_ARP_REQUEST:
	rcall	_LAN_SET_USER
        rcall	LAN_BUILD_ARP_REQUEST
        lds	temp, 6				; ARP
	sts	LAN_OP_ETHTYPE, temp
	ldstt2	LAN_MBUF_OUT_L, LAN_OP_BUF_LEN
	ret	; rjmp	_LAN_CMD_end
;
;	rjmp	_LAN_BUILD_USER_ETH_FRAME_act2	; build ETH
;	rcall	LAN_BUILD_ETH_FRAME
;	ret	; rjmp	_LAN_CMD_end



_LAN_BUILD_PING_REQUEST:
	ldiw	X, LAN_ICMP_DATA	; address to store to (ETH DATA)
	ldw	Z, LAN_MBUF_OUT		; address to read from
	ldw	Y, LAN_MBUF_OUT_L	; number of bytes to read from
	call	MCOPY_RAM_AVR_Y

	ldi	temp, LAN_PROTOCOL_ICMP
	sts	LAN_PROTOCOL, temp
	rcall	_LAN_SET_USER

	ldi	temp, LAN_PROT_ICMP_PING
	sts	LAN_OP_TYPE, temp	; ping request

	rcall	LAN_BUILD_ICMP_FRAME
	rjmp	_LAN_BUILD_USER_IP_FRAME_act

;	rcall	LAN_BUILD_IP_FRAME
;	rcall	LAN_BUILD_ETH_FRAME
;	ldstt2	LAN_MBUF_OUT_L, LAN_OP_BUF_LEN
;	ret	; rjmp	_LAN_CMD_end


_LAN_BUILD_PING_RESPONSE:
	ldstt2	LAN_MBUF_OUT_L, LAN_MBUF_IN_L	; set output buffer length
	rcall	_LAN_SET_USER
	rcall	LAN_BUILD_PING_RESPONSE
	ldstt2	LAN_MBUF_OUT_L, LAN_OP_BUF_LEN
	ret	; rjmp	_LAN_CMD_end



; make arp response from buf data and lan_block
_LAN_BUILD_ARP_RESP:
	rcall	_LAN_SET_USER
	rcall	LAN_BUILD_ARP_RESPONSE
	ret	; rjmp	_LAN_CMD_end



; prepare and send user UDP message
_LAN_SEND_UDP:
	rcall	_LAN_BUILD_USER_UDP_FRAME
	rcall	__LAN_SEND		; safe send
;	CMD_LAN	LAN_FUNC_SEND		; safe send
	ret	; rjmp	_LAN_CMD_end


; prepare and send user UDP message
_LAN_SEND_TCP:
	rcall	_LAN_BUILD_USER_TCP_FRAME
	rcall	__LAN_SEND		; safe send
;	CMD_LAN	LAN_FUNC_SEND		; safe send
	ret	; rjmp	_LAN_CMD_end


; returns UDP_DATA to zzRAM IN_BUF
_LAN_GET_UDP_DATA:
	lds	YH, LAN_UDP_LEN
	lds	YL, LAN_UDP_LEN+1
	sbiw	Y, LAN_UDP_DATA-LAN_UDP_FRAME	; =8 - UDP header size
	stw	LAN_MBUF_IN_L, Y	; set actual length
	ldiw	X, LAN_UDP_DATA		; address to read from
	ldw	Z, LAN_MBUF_IN		; address to store to
;	ldw	Y, LAN_MBUF_IN_L	; number of bytes to read from
	call	MCOPY_AVR_RAM_Y
	ret	; rjmp	_LAN_CMD_end

	
; check that arp is for us
_LAN_CHECK_ARP_REQ:
	rcall	LAN_CHECK_ARP_REQUEST
	ret	; rjmp	_LAN_CMD_end

_LAN_CHECK_FRAME_TYPE:
	rcall	LAN_CHECK_FRAME_TYPE
	ret	; rjmp	_LAN_CMD_end

_LAN_PROCESS_MESSAGES:
	rcall	LAN_PROCESS_MESSAGES
	ret	; rjmp	_LAN_CMD_end

_LAN_SEND_CON:
	rcall	LAN_SEND_CON			; send byte in zzC to server
	ret	; rjmp	_LAN_CMD_end

_LAN_SEND_PR:
	rcall	LAN_SEND_PR			; send byte in zzC to pr-server
	ret	; rjmp	_LAN_CMD_end

_LAN_SEND_PRN:
	rcall	LAN_SEND_PRN			; send byte in zzC to prn-server
	ret	; rjmp	_LAN_CMD_end

_LAN_SEND_RSD:
	rcall	LAN_SEND_RSD			; send data to rsd -server
	ret	; rjmp	_LAN_CMD_end

/*
; removes UDP headers
_LAN_REMOVE_UDP_HEADER:
	lds	YH, LAN_UDP_LEN
	lds	YL, LAN_UDP_LEN+1
	sbiw	Y, LAN_UDP_DATA-LAN_UDP_FRAME	; =8 - UDP header size
	stw	LAN_MBUF_IN_L, Y	; set actual length
	ldiw	X, LAN_BUF
	ldiw	Z, LAN_UDP_DATA		; offset for data in ip frame (20) including offset in eth frame (14)
	call	LAN_ZXYb		; move Y btes from Z to X backward
	ret	; rjmp	_LAN_CMD_end
		

; set LAN_MBUF_IN_L for UDP DATA length only
_LAN_REMOVE_UDP_HEADER_L:
	lds	YH, LAN_UDP_LEN
	lds	YL, LAN_UDP_LEN+1
	sbiw	Y, LAN_UDP_DATA-LAN_UDP_FRAME	; =8 - UDP header size
	stw	LAN_MBUF_IN_L, Y	; set actual length
	ret	; rjmp	_LAN_CMD_end
*/



; -------------------------------------------------------------------------------------------------------------
; SUBROUTINES

; startup LAN Init
_LAN_INIT_DO: 
        ; system reset
        SPI_SELECT
        ldi	temp, 0xff
	call	DOSPI
        SPI_DESELECT

        DELAY_10us
        DELAY_10us
        DELAY_10us
        DELAY_10us
        DELAY_10us				; 50 us startup delay

        rcall	LAN_SELECT_BANK_0			; select bank 0
        LAN_CREG_WRITE_LH LAN_ERXST, LAN_M_RXSTART	; rx buf start
        LAN_CREG_WRITE_LH LAN_ERXND, LAN_M_RXEND	; rx buf end
        LAN_CREG_WRITE_LH LAN_ERXRDPT, LAN_M_RXSTART	; read ptr

        stiw	LAN_RXDPT, LAN_M_RXSTART		; store active pointer

;	LAN_CREG_WRITE_LH LAN_ETXST, LAN_M_TXSTART	; tx buf start
;	LAN_CREG_WRITE_LH LAN_ETXND, LAN_M_TXEND	; tx buf end
;	LAN_CREG_WRITE_LH LAN_ETXRDPT, LAN_M_TXSTART	; read ptr

        rcall	LAN_SELECT_BANK_2			; select bank 2
;	LAN_CREG_WRITE LAN_MACON2, 0			; clear
	LAN_CREG_WRITE LAN_MACON1, 0b00001101		; TXPAUS RXPAUS MARXEN
	LAN_CREG_WRITE LAN_MACON3, 0b00110011		; PADCFG0 TXCRCEN FRMLNEN FULDPX
	LAN_CREG_WRITE LAN_MACON4, 0b01000000		; DEFER
        LAN_CREG_WRITE_LH LAN_MAMXFL, LAN_M_MAXFRAME	; max frame size
	LAN_CREG_WRITE LAN_MABBIPG, 0x15		; Datasheet
	LAN_CREG_WRITE LAN_MAIPGL, 0x12			; Datasheet
;	LAN_CREG_WRITE LAN_MAIPGH, 0x0c			; Datasheet ?????

        rcall	LAN_SELECT_BANK_3			; select bank 3
	; default MAC address for all devices 43-e8-9f-b3-5f-bc
	LAN_CREG_WRITE LAN_MAADR1, 0x43
	LAN_CREG_WRITE LAN_MAADR2, 0xe8
	LAN_CREG_WRITE LAN_MAADR3, 0x9f
	LAN_CREG_WRITE LAN_MAADR4, 0xb3
	LAN_CREG_WRITE LAN_MAADR5, 0x5f
	LAN_CREG_WRITE LAN_MAADR6, 0xbc

	rcall	LAN_SELECT_BANK_2			; select bank 2
	LAN_WRITE_PHY LAN_PHCON2, 0b0000000100000000	; HDLDIS
	LAN_WRITE_PHY LAN_PHCON1, 0b0000000100000000	; PDPXMD === FULDPX
	LAN_WRITE_PHY LAN_PHLCON, 0b0011010001110010	; Activity

;	LAN_CREG_WRITE_C LAN_ECON2, 0b10000000, LAN_REG_BFS	; AUTOINC
	LAN_CREG_WRITE_C LAN_ECON1, 0b00000100, LAN_REG_BFS	; RXEN
	ret


; SET MAC address
_LAN_SET_MY_MAC:
        lds	temp, 	LAN_MAC_MY+0			; set MAC from BUF data
        push	temp
        lds	temp, 	LAN_MAC_MY+1
        push	temp
        lds	temp, 	LAN_MAC_MY+2
        push	temp
        lds	temp, 	LAN_MAC_MY+3
        push	temp
        lds	temp, 	LAN_MAC_MY+4
        push	temp
        lds	temp, 	LAN_MAC_MY+5
        push	temp

        ; datasheed advises to disable TX during MAC address updating
	LAN_CREG_WRITE_C LAN_ECON1, 0b00000100, LAN_REG_BFC	; RXEN

        rcall	LAN_SELECT_BANK_3			; select bank 2
	LAN_CREG_WRITE_S LAN_MAADR6
	LAN_CREG_WRITE_S LAN_MAADR5
	LAN_CREG_WRITE_S LAN_MAADR4
	LAN_CREG_WRITE_S LAN_MAADR3
	LAN_CREG_WRITE_S LAN_MAADR2
	LAN_CREG_WRITE_S LAN_MAADR1

	LAN_CREG_WRITE_C LAN_ECON1, 0b00000100, LAN_REG_BFS	; RXEN
	ret



LAN_SELECT_BANK_0:
	LAN_CREG_WRITE_C LAN_ECON1, 0x03, LAN_REG_BFC
;	LAN_CREG_WRITE_C LAN_ECON1, LAN_BANK0, LAN_REG_BFS
	ret	

LAN_SELECT_BANK_1:
	LAN_CREG_WRITE_C LAN_ECON1, 0x03, LAN_REG_BFC
	LAN_CREG_WRITE_C LAN_ECON1, LAN_BANK1, LAN_REG_BFS
	ret

LAN_SELECT_BANK_2:
	LAN_CREG_WRITE_C LAN_ECON1, 0x03, LAN_REG_BFC
	LAN_CREG_WRITE_C LAN_ECON1, LAN_BANK2, LAN_REG_BFS
	ret

LAN_SELECT_BANK_3:
;	LAN_CREG_WRITE_C LAN_ECON1, 0x03, LAN_REG_BFC
	LAN_CREG_WRITE_C LAN_ECON1, LAN_BANK3, LAN_REG_BFS
	ret


; select bank and returns reg num in temp
_LAN_CMD_PAR_PREPARE:
	lds	temp, LAN_PAR
	andi	temp, 0x03		; mask unused bits
	push	temp
	LAN_CREG_WRITE_C LAN_ECON1, 0x03, LAN_REG_BFC
	LAN_CREG_WRITE_C_S LAN_ECON1, LAN_REG_BFS
	lds	temp, LAN_PAR+1
	andi	temp, 0x1f		; mask unused bits
	ret


; compute CRC from Z for Y bytes, return CRC in Z big endian 
_LAN_IPCRC:
	push	r17
	push	r18
	push	r19
	push	r20

	clr	r17
	clr	r18
	clr	r19
	clr	r20			; sum will be here

_lan_ipcrc_l2:
	cpi	YH, 0
	brne	_lan_ipcrc_l0
	cpi	YL, 2
	brlo	_lan_ipcrc_l1		; Y>=2 ?
_lan_ipcrc_l0:
        ld	temp, Z+
	add	r19, temp
	adc	r18, zero
	adc	r17, zero		; sum + b<<8 - big endian
        ld	temp, Z+
	add	r20, temp
	adc	r19, zero
	adc	r18, zero
	adc	r17, zero		; sum + b
	sbiw	Y, 2
	rjmp	_lan_ipcrc_l2
_lan_ipcrc_l1:
	cpi	YL, 1
	brne	_lan_ipcrc_l3
        ld	temp, Z+
	add	r19, temp
	adc	r18, zero
	adc	r17, zero		; sum + b<<8

_lan_ipcrc_l3:
	mov	ZH, r17
	mov	ZL, r18
	clr	r17
	clr	r18			; sum &= 0x0ffff
	add	r20, ZL
	adc	r19, ZH			; sum += hiword(sum)
	adc	r18, zero
;	adc	r17, zero
;	cpi	r17, 0
;	brne	_lan_ipcrc_l3
	cpi	r18, 0
	brne	_lan_ipcrc_l3

	mov	ZH, r19
	mov	ZL, r20
	com	ZH
	com	ZL			; complement

	pop	r20
	pop	r19
	pop	r18
	pop	r17
	ret



; ADD address fields, data is preloaded
LAN_BUILD_ETH_FRAME:
	setlop	X, LAN_ETH_FRAME
	ldiw	Z, LAN_OP_DST_MAC
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

;	setlop	X, LAN_ETH_SRCMAC
	ldiw	Z, LAN_MAC_MY
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

;	setlop	X, LAN_ETH_SRCMAC
;	ldiw	Z, LAN_MAC_MY
;	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

;	setlop	X, LAN_ETH_TYPE
	ldi	temp, 0x08		; 
	st	X+, temp
	lds	temp, LAN_OP_ETHTYPE
	st	X+, temp
;	sts	LAN_ETH_TYPE+1, zero
;	stst	LAN_ETH_TYPE, 0x08

	ldw	Y, LAN_OP_BUF_LEN
	adiw	Y, (LAN_ETH_DATA-LAN_ETH_FRAME)
	stw	LAN_OP_BUF_LEN, Y	; for send command
	ret



LAN_BUILD_IP_FRAME:
	setlop	X, LAN_IP_VERS
	ldi	temp, 0x45		; 
	st	X+, temp
;	stst	LAN_IP_VERS, 0x45	;(4<<4) | 5	; IPv4, standard header

;	setlop	X, LAN_IP_TOS
	st	X+, zero
;	stsz	LAN_IP_TOS

	ldw	Y, LAN_OP_BUF_LEN	; adjust length
	adiw	Y, LAN_IP_DATA-LAN_IP_FRAME
	stw	LAN_OP_BUF_LEN, Y	; for ethernet frame

	st	X+, YH
	st	X+, YL
;	stswbe	LAN_IP_LEN, Y
	ldw	Z, LAN_IP_ID
	add	ZL, one
	adc	ZH, zero		; increment ID
	stw	LAN_IP_ID, Z		
	st	X+, ZH
	st	X+, ZL			; Frame ID
;	st	X+, zero
;	stsz	LAN_IP_FRAG
;	st	X+, zero
;	stsz	LAN_IP_FRAG+1
	st	X+, zero
;	stsz	LAN_IP_FLAGS
	st	X+, zero
;	stsz	LAN_IP_FLAGS+1
	ldi	temp, 0x80		; 
	st	X+, temp
;	stst	LAN_IP_LIFE, 64
	lds	temp, LAN_OP_PROTOCOL
	st	X+, temp
;	ldstt	LAN_IP_PROTOCOL, LAN_OP_PROTOCOL
	st	X+, zero
;	stsz	LAN_IP_CS
	st	X+, zero
;	stsz	LAN_IP_CS+1

	ldiw	Z, LAN_IP_MY
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)
;	COPY_IP LAN_IP_SRCIP, LAN_IP_MY
	ldiw	Z, LAN_OP_DST_IP
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)
;	COPY_IP LAN_IP_REMOTE, LAN_OP_DST_IP

	setlop	Z, LAN_IP_FRAME
;	ldiw	Z, LAN_IP_FRAME
	ldiw	Y, LAN_IP_DATA-LAN_IP_FRAME	; length
	rcall	_LAN_IPCRC
	setlop	X, LAN_IP_CS
	st	X+, ZH
	st	X+, ZL
;	stswbe	LAN_IP_CS, Z
	ret



LAN_BUILD_UDP_FRAME:		; for the case when data is loaded to LAN_UDP_DATA
        setlop	X, LAN_UDP_SRCPORT
        ldiw	Z, LAN_OP_SRC_PORT
        rcall	_LAN_COPY_PORT			; copy 2 bytes (X)<-(Z)
;	COPY_PORT LAN_UDP_SRCPORT, LAN_OP_SRC_PORT
;        setlop	X, LAN_UDP_DSTPORT
        ldiw	Z, LAN_OP_DST_PORT
        rcall	_LAN_COPY_PORT			; copy 2 bytes (X)<-(Z)
;	COPY_PORT LAN_UDP_DSTPORT, LAN_OP_DST_PORT

	ldw	Y, LAN_OP_BUF_LEN
	adiw	Y, LAN_UDP_DATA-LAN_UDP_FRAME
	stw	LAN_OP_BUF_LEN, Y	; new length with header

	st	X+, YH
	st	X+, YL
;	stswbe	LAN_UDP_LEN, Y
	st	X+, zero
;	stsz	LAN_UDP_CS
	st	X+, zero
;	stsz	LAN_UDP_CS+1

	ret ;!!!!!!!! DEBUG!!!!! check CRC calculation!!!!!
        
					; fill pseudo-header for crc
        setlop	X, LAN_UDP_PH_START
        ldiw	Z, LAN_OP_SRC_IP
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)
        ldiw	Z, LAN_OP_DST_IP
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)
	st	X+, zero
;	stsz	LAN_UDP_PH_Z
;	lds	temp, LAN_OP_PROTOCOL	;???? preset to UDP?????
	ldi	temp, LAN_PROTOCOL_UDP	; preset to UDP
	st	X+, temp
	st	X+, YH
	st	X+, YL

;					; fill pseudo-header for crc
;	stswbe	LAN_UDP_PH_LEN, Y
;	ldi	temp, LAN_PROTOCOL_UDP	; 17 = UDP protocol ID for IP build
;	sts	LAN_OP_PROTOCOL, temp	; store
;	sts	LAN_UDP_PH_PROTOCOL, temp
;	stsz	LAN_UDP_PH_Z
;	COPY_IP LAN_UDP_PH_DSTIP, LAN_OP_DST_IP
;	COPY_IP LAN_UDP_PH_SRCIP, LAN_IP_MY

        setlop	Z, LAN_UDP_PH_START
;	ldiw	Z, LAN_UDP_PH_START
	ldw	Y, LAN_OP_BUF_LEN
	adiw	Y, LAN_UDP_FRAME-LAN_UDP_PH_START	; add pseudo header
	rcall	_LAN_IPCRC
	setlop	X, LAN_UDP_CS
	st	X+, ZH
	st	X+, ZL
;	stswbe	LAN_UDP_CS, Z		; set checksum
	ret



; Build TCP Frame
LAN_BUILD_TCP_FRAME:		; for the case when data is loaded to LAN_UDP_DATA
        setlop	X, LAN_TCP_SRCPORT
        ldiw	Z, LAN_OP_SRC_PORT
        rcall	_LAN_COPY_PORT		; copy 2 bytes (X)<-(Z)
;	COPY_PORT LAN_UDP_SRCPORT, LAN_OP_SRC_PORT
;        setlop	X, LAN_UDP_DSTPORT
        ldiw	Z, LAN_OP_DST_PORT
        rcall	_LAN_COPY_PORT		; copy 2 bytes (X)<-(Z)
;	COPY_PORT LAN_UDP_DSTPORT, LAN_OP_DST_PORT
        ldiw	Z, LAN_USR_TCP_SN	;!!!!! May be from OP_????
        rcall	_LAN_COPY_DWORD		; copy 4 bytes (X)<-(Z)
        ldiw	Z, LAN_USR_TCP_ACK	;!!!!! May be from OP_????
        rcall	_LAN_COPY_DWORD		; copy 4 bytes (X)<-(Z)

	ldi	temp, 5			; Header Length
	st	X+, temp
	lds	temp, LAN_USR_TCP_FLAGS	;!!!!! May be from OP_????
	st	X+, temp
        ldiw	Z, LAN_USR_TCP_WINDOW	;!!!!! May be from OP_????
        rcall	_LAN_COPY_WORD			; copy 2 bytes (X)<-(Z)

	ldw	Y, LAN_OP_BUF_LEN
	adiw	Y, LAN_TCP_DATA-LAN_TCP_FRAME
	stw	LAN_OP_BUF_LEN, Y	; new length with header

	st	X+, YH
	st	X+, YL			; LAN_UDP_LEN, Y
	st	X+, zero		; LAN_UDP_CS
	st	X+, zero		; LAN_UDP_CS+1

					; fill pseudo-header for crc
        setlop	X, LAN_TCP_PH_START
        ldiw	Z, LAN_OP_SRC_IP
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)
        ldiw	Z, LAN_OP_DST_IP
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)
	st	X+, zero
	ldi	temp, LAN_PROTOCOL_TCP	; preset to UDP
	st	X+, temp
	st	X+, YH
	st	X+, YL

        setlop	Z, LAN_TCP_PH_START
	ldw	Y, LAN_OP_BUF_LEN
	adiw	Y, LAN_TCP_FRAME-LAN_TCP_PH_START	; add pseudo header length
	rcall	_LAN_IPCRC
	setlop	X, LAN_TCP_CS
	st	X+, ZH
	st	X+, ZL
	ret



LAN_BUILD_ICMP_FRAME:		; 
        setlop	X, LAN_ICMP_FRAME
        lds	temp, LAN_OP_TYPE
        st	X+, temp
        st	X+, zero		; CODE
        st	X+, zero		; CS
        st	X+, zero		; CS
        st	X+, zero		; ROH
        st	X+, zero		; ROH
        st	X+, zero		; ROH
        st	X+, zero		; ROH

	ldw	Y, LAN_OP_BUF_LEN
	adiw	Y, LAN_ICMP_DATA-LAN_ICMP_FRAME	; Payload is not accepted!
	stw	LAN_OP_BUF_LEN, Y	; new length with header

        setlop	Z, LAN_ICMP_FRAME
	ldw	Y, LAN_OP_BUF_LEN
	rcall	_LAN_IPCRC
	setlop	X, LAN_ICMP_CS
	st	X+, ZH
	st	X+, ZL
	ret


; build ack response for arp-request
LAN_BUILD_ARP_RESPONSE:
	setlop	X, LAN_ARP_DSTMAC
	setlop	Z, LAN_ARP_SRCMAC
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

	setlop	X, LAN_ARP_SRCMAC
	ldiw	Z, LAN_MAC_MY
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

	setlop	X, LAN_ARP_DSTIP
	setlop	Z, LAN_ARP_SRCIP
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)

	setlop	X, LAN_ARP_SRCIP
	ldiw	Z, LAN_IP_MY
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)

	setlop	X, LAN_ARP_MSGTYPE
	st	X+, zero
	ldi	temp, 2			; ARP_TYPE_RESPONSE
	st	X, temp
;	stsz	LAN_ARP_MSGTYPE 
;	stst	LAN_ARP_MSGTYPE+1, 2	; ARP_TYPE_RESPONSE 

	setlop	X, LAN_ETH_DSTMAC
	setlop	Z, LAN_ETH_SRCMAC
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

	setlop	X, LAN_ETH_SRCMAC
	ldiw	Z, LAN_MAC_MY
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

	ldiw	Y, 28+14		; ARP+ETH blocks, ready to send
	sts	LAN_OP_BUF_LEN, YL	; set buffer length
	sts	LAN_OP_BUF_LEN+1, YH	; set buffer length
	ret



; build USER !!!! ARP request 
LAN_BUILD_ARP_REQUEST:
	setlop	X, LAN_ETH_DSTMAC
;	ldiw	X, LAN_OP_DST_MAC
	st	X+, FF
	st	X+, FF
	st	X+, FF
	st	X+, FF
	st	X+, FF
	st	X+, FF			; brodcast
	
	ldiw	Z, LAN_MAC_MY
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

	ldi	temp, 0x08		; 
	st	X+, temp
	ldi	temp, 0x06		; ARP
	st	X+, temp

	setlop	X, LAN_ARP_HWTYPE
	st	X+, zero
	st	X+, one			; HWTYPE
	ldi	temp, LAN_PROTOCOL_IPH	; 8
	st	X+, temp
	st	X+, zero 		; 0
	ldi	temp, 6			; 6 MAC_LEN
	st	X+, temp
	ldi	temp, 4			; 4 IP_LEN
	st	X+, temp

	st	X+, zero
	st	X+, one			; REEQUEST

	ldiw	Z, LAN_MAC_MY
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

	ldiw	Z, LAN_IP_MY
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)

	st	X+, zero
	st	X+, zero
	st	X+, zero
	st	X+, zero
	st	X+, zero
	st	X+, zero		; DST_MAC

	ldiw	Z, LAN_OP_DST_IP
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)

	ldiw	Y, 28+14 ;+14		; ARP+ETH block
	sts	LAN_OP_BUF_LEN, YL	; set buffer length
	sts	LAN_OP_BUF_LEN+1, YH	; set buffer length
	ret



;check arp request is ok
LAN_CHECK_ARP_REQUEST:
	ldi	r19, 4
	setlop	X, LAN_ARP_DSTIP
	ldiw	Z, LAN_IP_MY
	rcall	LAN_MEM_COMPARE
	brne	_lan_ch_arp_no

	ldi	r19, 10
	setlop	X, LAN_ARP_MSGTYPE
	ld	temp, X+
	cpi	temp, 0x00
	brne	_lan_ch_arp_no

	ld	temp, X
	cpi	temp, 0x01			; request?
	breq	_lan_ch_arp_request
	cpi	temp, 0x02			; response?
	breq	_lan_ch_arp_response
	rjmp	_lan_ch_arp_no			; not response - unknown - decline
_lan_ch_arp_request:
	ldi	temp, 0x81			; request matched!
	rjmp	_lan_ch_arp_ret
_lan_ch_arp_no:
	mov	temp, r19			; error point
_lan_ch_arp_ret:
	ret

_lan_ch_arp_response:
	ldi	r19, 4
	setlop	X, LAN_ARP_SRCIP		; compare dest IP with lan_block
	ldiw	Z, LAN_IP_REMOTE
	rcall	LAN_MEM_COMPARE
	brne	_lan_ch_arp_no 			; not from user server
	
	ldiw	X, LAN_MAC_REMOTE
	setlop	Z, LAN_ARP_SRCMAC
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)
;	ZXYb	LAN_ARP_SRCMAC, LAN_MAC_REMOTE, 6	; store MAC 

	ldi	temp, 0x82			; response received, REMOTE MAC set
	rjmp	_lan_ch_arp_ret
		


LAN_CHECK_ICMP_REQUEST:
	ldi	r19, 4
	setlop	X, LAN_IP_DSTIP			; compare dest IP with lan_block
	ldiw	Z, LAN_IP_MY
	rcall	LAN_MEM_COMPARE
	brne	_ch_icmp_no			; not for USER settings

	setlop	X, LAN_ICMP_TYPE		; compare dest IP with lan_block
	ld	temp, X+

	cpi	temp, LAN_PROT_ICMP_PING
	breq	_ch_icmp_resp			; send reply
	
	cpi	temp, LAN_PROT_ICMP_ECHO
	brne	_ch_icmp_ret			; unsupported command

	ldi	r19, 4
	setlop	X, LAN_IP_SRCIP			; compare dest IP with lan_block
	ldiw	Z, LAN_IP_REMOTE
	rcall	LAN_MEM_COMPARE
	brne	_ch_icmp_no			; not from user server

	lds	temp, LAN_ECHO_CNTR
	inc	temp
	sts	LAN_ECHO_CNTR, temp		; increment counter indicating echo response

	ldi	temp, 0x8b			; Ping echo received
	rjmp	_ch_icmp_ret

_ch_icmp_no:
	ldi	temp, 0				; no match
_ch_icmp_ret:
	ret
_ch_icmp_resp:
	ldi	temp, 0x8a			; Ping request received
	rjmp	_ch_icmp_ret
	



LAN_BUILD_PING_RESPONSE:   				; build ICMP response from request
	setlop	X, LAN_ETH_DSTMAC
	setlop	Z, LAN_ETH_SRCMAC
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

	setlop	X, LAN_ETH_SRCMAC
	ldiw	Z, LAN_MAC_MY
	rcall	_LAN_COPY_MAC		; 6 bytes (x)<-(Z)

	setlop	X, LAN_IP_DSTIP
	setlop	Z, LAN_IP_SRCIP
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)

	setlop	X, LAN_IP_SRCIP
	ldiw	Z, LAN_IP_MY
	rcall	_LAN_COPY_IP		; 4 bytes (x)<-(Z)

	setlop	X, LAN_ICMP_TYPE
	st	X+, zero			; LAN_PROT_ICMP_ECHO
	st	X+, zero			; type + code

        setlop	X, LAN_ICMP_CS
	st	X+, zero			; Clear CS for computattion
	st	X+, zero			; 

        setlop	Z, LAN_ICMP_FRAME
	ldw	Y, LAN_OP_BUF_LEN
	sbiw	Y, (LAN_IP_DATA-LAN_ETH_FRAME)	; correcting length
	rcall	_LAN_IPCRC
	setlop	X, LAN_ICMP_CS
	st	X+, ZH
	st	X+, ZL

;	rcall	LAN_SEND_PACKET			; send response

	ldi	temp, 0x8a			; Ping request - echoed
	rjmp	_ch_icmp_ret			; return





LAN_ARP_MSK: 
	.DB	0x08, 0x06, 0x00, 0x01, 0x08, 0x00, 0x06, 0x04
LAN_CHECK_FRAME_TYPE:
	setlop	X, LAN_ETH_TYPE			; set offset to LAN*_ETH_TYPE data
	ldiw	Z, LAN_ARP_MSK*2		; mask
	ldi	r19, 8
_lan_ch_fr_l5:               			; check ARP mask
	ld	temp, X+
	celpm	FROMRAM0, Z+
	cp	temp, FROMRAM0
	brne	_lan_ch_fr_l1
	dec	r19
	brne	_lan_ch_fr_l5

;	ldi	r19, 0x80+1;			; ARP index
	rcall	LAN_CHECK_ARP_REQUEST
	ret
;	rjmp	_lan_ch_fr_ret			; return response

_lan_ch_fr_l1:
	setlop	X, LAN_ETH_TYPE
;	ldiw	X, LAN_ETH_TYPE
	ld	temp, X+
	cpi	temp, 0x08			; is IP protocol?
	brne	_lan_ch_fr_ret_0
	ld	temp, X+
	cpi	temp, 0x00			; IP frame
	brne	_lan_ch_fr_ret_0

	setlop	X, LAN_IP_PROTOCOL
	ld	temp, X+
_lan_ch_fr_udp:					; UDP packet received
	cpi	temp, LAN_PROTOCOL_UDP		; 17 = udp?	
	brne	_lan_ch_fr_icmp			; goto next check

	ldi	FROMRAM2, 0x00                  ; Erroro point

	ldi	r19, 4
	setlop	X, LAN_IP_DSTIP			; compare dest IP with lan_block
	ldiw	Z, LAN_IP_MY
	rcall	LAN_MEM_COMPARE
	brne	_lan_ch_fr_udp_ret		; not for us, ignore broadcasts
	sbr	FROMRAM2, 1<<0
	; checking packet, on success procedure performs double ret
	rcall	_lan_ch_fr_udp_pr		; check PR
	rcall	_lan_ch_fr_udp_srv		; check SRV
	ldi	temp, 0x83			; UDP return code
	mov	FROMRAM1, temp			; return code
	rcall	_lan_ch_user_srv		; check USER server
_lan_ch_fr_udp_ret:
	mov	temp, FROMRAM2			; set error point to return
        ret

_lan_ch_fr_icmp:
	cpi	temp, LAN_PROTOCOL_ICMP		; 1 = icmp?
	brne	_lan_ch_fr_tcp			; check TCP

	rcall	LAN_CHECK_ICMP_REQUEST		; process ICMP
	ret

_lan_ch_fr_tcp:					; UDP packet received
	cpi	temp, LAN_PROTOCOL_TCP		; 6 = tcp?
	brne	_lan_ch_fr_ret_0		; not supported

	ldi	FROMRAM2, 0x00                  ; Erroro point

	ldi	r19, 4
	setlop	X, LAN_IP_DSTIP			; compare dest IP with lan_block
	ldiw	Z, LAN_IP_MY
	rcall	LAN_MEM_COMPARE
	brne	_lan_ch_fr_tcp_ret		; not for us, ignore broadcasts
	sbr	FROMRAM2, 1<<0
	; checking packet, on success procedure performs double ret
	ldi	temp, 0x86
	mov	FROMRAM1, temp			; return code
	rcall	_lan_ch_user_srv		; check USER server
_lan_ch_fr_tcp_ret:
	mov	temp, FROMRAM2			; set error point to return
        ret

	; placed here to allow relative jump!
_lan_ch_fr_ret_0:				; returns with 0 - not for us or not supported
	ldi	temp, 0
	ret

_lan_ch_user_srv:
	ldi	r19, 4
	setlop	X, LAN_IP_SRCIP			; compare dest IP with lan_block
	ldiw	Z, LAN_IP_REMOTE
	rcall	LAN_MEM_COMPARE
	brne	_lan_ch_fr_ret_0		; not for me
	sbr	FROMRAM2, 1<<1

	setlop	X, LAN_UDP_DSTPORT		; compare dest Iport with lan_block
	ldiw	Z, LAN_PORT_MY
	rcall	LAN_MEM_COMPARE_BEW
	brne	_lan_ch_fr_ret_0
	sbr	FROMRAM2, 1<<2

;	ldi	temp, 0x83			; 
	mov	temp, FROMRAM1			; set return code
	rjmp	_lan_ch_fr_ret_to_main		; return to main

_lan_ch_fr_udp_pr:	
	ldi	r19, 4
	setlop	X, LAN_IP_SRCIP
	ldiw	Z, PR_SRV_IP
	rcall	LAN_MEM_COMPARE
	brne	_lan_ch_fr_ret_0
	sbr	FROMRAM2, 1<<3

	setlop	X, LAN_UDP_DSTPORT
	ldiw	Z, PR_SRV_PORT
	rcall	LAN_MEM_COMPARE_BEW
	brne	_lan_ch_fr_ret_0
	sbr	FROMRAM2, 1<<4

	ldi	temp, 0x84			; UDP message from PR-SRV
	rjmp	_lan_ch_fr_ret_to_main		; return to main
		
_lan_ch_fr_udp_srv:
	ldi	r19, 4
	setlop	X, LAN_IP_SRCIP
	ldiw	Z, RTC_SRV_IP
	rcall	LAN_MEM_COMPARE
	brne	_lan_ch_fr_ret_0_l
	sbr	FROMRAM2, 1<<5

	setlop	X, LAN_UDP_DSTPORT
	ldiw	Z, RTC_SRV_PORT
	rcall	LAN_MEM_COMPARE_BEW
	brne	_lan_ch_fr_ret_0_l
	sbr	FROMRAM2, 1<<6

	ldi	temp, 0x85			; UDP message from SERVER 
	rjmp	_lan_ch_fr_ret_to_main		; return to main

; Placed here to allow local jump!
_lan_ch_fr_ret_0_l:
	rjmp	_lan_ch_fr_ret_0		; returns with 0 - not for us or not supported

_lan_ch_fr_ret_to_main:				; return to main procedure
	pop	FROMRAM2
	pop	FROMRAM2			; clear first level call return
	ret
	



	; set buffer to USER 
_LAN_SET_USER:
	ldstt2	LAN_OP_BUF_LEN, LAN_MBUF_OUT_L
	stiw	LAN_OP_BUF, LAN_BUF
	stiw	LAN_OP_BUF_SIZE, LAN_BUF_SIZE
	COPY_MAC LAN_OP_DST_MAC, LAN_MAC_REMOTE
	COPY_IP  LAN_OP_DST_IP, LAN_IP_REMOTE
	COPY_PORT LAN_OP_DST_PORT, LAN_PORT_REMOTE
	COPY_PORT LAN_OP_SRC_PORT, LAN_PORT_MY
	ldstt	LAN_OP_PROTOCOL, LAN_PROTOCOL
	ret


	; set buffer to HEADER 
_LAN_SET_HDR:
	stiw	LAN_OP_BUF, LAN3_BUF
	stiw	LAN_OP_BUF_SIZE, LAN3_BUF_SIZE
	ret


_LAN_SET_BUF2:
	stiw	LAN_OP_BUF, LAN2_BUF
	stiw	LAN_OP_BUF_SIZE, LAN2_BUF_SIZE
	ret

	; system server
_LAN_SET_SRV:
;	stiw	LAN_OP_BUF_LEN, 1
	stiw	LAN_OP_BUF, LAN2_BUF
	stiw	LAN_OP_BUF_SIZE, LAN2_BUF_SIZE
	COPY_MAC LAN_OP_DST_MAC, RTC_SRV_MAC
	COPY_IP  LAN_OP_DST_IP, RTC_SRV_IP
	COPY_PORT LAN_OP_DST_PORT, RTC_SRV_PORT
	COPY_PORT LAN_OP_SRC_PORT, RTC_SRV_PORT
	stiw	LAN_OP_PROTOCOL, LAN_PROTOCOL_UDP		; UDP
	ret
	

	; Punch/Reader server
_LAN_SET_PR:
	stiw	LAN_OP_BUF_LEN, 1
	stiw	LAN_OP_BUF, LAN2_BUF
	stiw	LAN_OP_BUF_SIZE, LAN2_BUF_SIZE
	COPY_MAC LAN_OP_DST_MAC, PR_SRV_MAC
	COPY_IP  LAN_OP_DST_IP, PR_SRV_IP
	COPY_PORT LAN_OP_DST_PORT, PR_SRV_PORT
	COPY_PORT LAN_OP_SRC_PORT, PR_SRV_PORT
	stiw	LAN_OP_PROTOCOL, LAN_PROTOCOL_UDP		; UDP
	ret

	; System SRV CON port
_LAN_SET_CON:
	rcall	_LAN_SET_SRV
	stiw	LAN_OP_BUF_LEN, 1
	ret

	; System Printer port
_LAN_SET_PRN:
	rcall	_LAN_SET_SRV
	COPY_PORT LAN_OP_DST_PORT, RTC_PRN_PORT
	COPY_PORT LAN_OP_SRC_PORT, RTC_PRN_PORT
	stiw	LAN_OP_BUF_LEN, 1
	ret

	; Remote SD port
	;?????? how to process responce ????
_LAN_SET_RSD:
	rcall	_LAN_SET_SRV
	COPY_PORT LAN_OP_DST_PORT, RTC_SDC_PORT
	COPY_PORT LAN_OP_SRC_PORT, RTC_SDC_PORT
	ret



; process messages
LAN_PROCESS_MESSAGES:
	ldi	temp, 254
	lds	r19, LAN_MAIN_RQST		; check that request is processed
	cpse	r19, zero
	ret

;	rcall	_LAN_SET_HDR			; working with header only
_LAN_PROCESS_start:
	rcall	_LAN_GET_EPKTCNT		; check is there messages waiting
	cpi	temp, 0				; is there packets waiting?
	breq	_LAN_PROCESS_ret

	rcall	_LAN_SET_HDR			; working with header only
	rcall	LAN_RECEIVE_PACKET		; get packet header
	rcall	LAN_CHECK_FRAME_TYPE		; understand what is it

	tcbe	0x81, _LAN_PROCESS_ARP          ; ARP
	tcbe	0x83, _LAN_PROCESS_MAIN		; UDP to main
	tcbe	0x84, _LAN_PROCESS_PRSRV	; UDP to PRSRV
	tcbe	0x85, _LAN_PROCESS_SRV		; UDP to SRV
	tcbe	0x8a, _LAN_PROCESS_PING		; build PING response
_LAN_PROCESS_NEXT:
	rcall	LAN_RECEIVE_PACKET_NEXT		; uncknown packet, ignore it
	rjmp	_LAN_PROCESS_start		; checking next frame
_LAN_PROCESS_RET:
	ret

_LAN_PROCESS_ARP:
	rcall	LAN_BUILD_ARP_RESPONSE		; staying in HDR
	rcall	LAN_SEND_PACKET
	rjmp	_LAN_PROCESS_NEXT		; checking next frame

_LAN_PROCESS_PING:
	;!!! add flag is ping responsed
	rcall	_LAN_SET_BUF2			; ICMP is bigger than 64 byte - using BUF2
	rcall	LAN_RECEIVE_PACKET		; get packet
	rcall	LAN_BUILD_PING_RESPONSE
	rcall	LAN_SEND_PACKET
	rjmp	_LAN_PROCESS_NEXT		; checking next frame

_LAN_PROCESS_PRSRV:
	lds	temp, PR_IOBYTE			; checking do we need it processing
	sbrs	temp, PRIO_IN_LAN
	rjmp	_LAN_PROCESS_NEXT
;	rcall	_LAN_SET_BUF2			; May be bigger than 64 byte - using BUF2 ????
;	rcall	LAN_RECEIVE_PACKET		; get packet
	ldi	temp, BIOS_FUNC_PRBUF_APPEND	; 0xf1
	rjmp	_LAN_PROCESS_BUF

_LAN_PROCESS_SRV:
	lds	temp, CON_IOBYTE		; checking do we need it processing
	sbrs	temp, CON_IN_LAN
	rjmp	_LAN_PROCESS_NEXT
;	rcall	_LAN_SET_BUF2			; May be bigger than 64 byte - using BUF2
;	rcall	LAN_RECEIVE_PACKET		; get packet
	ldi	temp, BIOS_FUNC_CONBUF_APPEND	; 0xf0
	rjmp	_LAN_PROCESS_BUF

_LAN_PROCESS_BUF:
        push	zzC
        lds	r19, LAN_OP_BUF_LEN

.EQU		LAN3_UDP_DATA = LAN3_BUF + (LAN_UDP_DATA-LAN_BUF)
        
        subi	r19, (LAN3_UDP_DATA-LAN3_BUF)	; length of DATA block
        ldiw	Z, LAN3_UDP_DATA		; address of data to get
_LAN_PROCESS_BUF_LOOP:
        cpi	r19, 0
        breq	_LAN_PROCESS_BUF_END
	ld	zzC, Z+				; get data
	pushw	Z
        push	temp
	call	BIOS				; store to buffer
	pop	temp
	popw	Z
	brcs	_LAN_PROCESS_BUF_CANCEL		;!! if C=1 === buffer is overloaded, stop processing until main stream will clear it
	dec	r19
	brne	_LAN_PROCESS_BUF_LOOP	
_LAN_PROCESS_BUF_END:
	pop	zzC
	rjmp	_LAN_PROCESS_NEXT		; set processed and check next frame
_LAN_PROCESS_BUF_CANCEL:
	pop	zzC
	rjmp	_LAN_PROCESS_RET		; buffer is overflowed

_LAN_PROCESS_MAIN:
	;!!! still thinking - load packet or no?? ?????
	; stop processing for now
	sts	LAN_MAIN_RQST, temp		; processing required
	rcall	_LAN_RECEIVE_USER_PACKET	; receive packet to USER buffer
;	rcall	_LAN_SET_USER
;	rcall	LAN_RECEIVE_PACKET		; get packet to user buffer
;	rcall	LAN_RECEIVE_PACKET_NEXT		; set processed
	rjmp	_LAN_PROCESS_RET		; just return, store data

_LAN_PROCESS_RET2:
	ret



	; send system UDP packet
LAN_SEND_SAFE:
	lds	temp, LAN_OP_DST_IP		; check IP address is set
	cpi	temp, 0				; IP starts with 0 == not set = nothing to do
	brne	LAN_SEND_SAFE_do
	rjmp	LAN_SEND_SAFE_ret
LAN_SEND_SAFE_do:
	rcall	LAN_BUILD_UDP_FRAME
	rcall	LAN_BUILD_IP_FRAME
	sts	LAN_OP_ETHTYPE, zero		; IP
	rcall	LAN_BUILD_ETH_FRAME
	rcall	LAN_SEND_PACKET
LAN_SEND_SAFE_ret:
	ret


.EQU		LAN2_UDP_DATA = LAN2_BUF + (LAN_UDP_DATA-LAN_BUF)

	; sending data to system targets
LAN_SEND_CON:
	rcall	_LAN_SET_CON
	sts	LAN2_UDP_DATA, zzC		; store symbol to transmit
	rjmp	LAN_SEND_SAFE

LAN_SEND_PR:
	rcall	_LAN_SET_PR
	sts	LAN2_UDP_DATA, zzC		; store symbol to transmit
	rjmp	LAN_SEND_SAFE

LAN_SEND_PRN:
	rcall	_LAN_SET_PRN
	sts	LAN2_UDP_DATA, zzC		; store symbol to transmit
	rjmp	LAN_SEND_SAFE

	;?????? how to process responce ????
LAN_SEND_RSD:
	rcall	_LAN_SET_RSD
	rjmp	LAN_SEND_SAFE



; send stored packet
LAN_SEND_PACKET:
	rcall	_LAN_SEND_WAIT_TXRTS
_LAN_SEND_PACKET_RESET:
	; reset TX
;	rcall	LAN_SELECT_BANK_2			; select bank 2
;	LAN_WRITE_PHY LAN_PHCON1, 0b0000000100000000	; PDPXMD === FULDPX Reset just for the case

	LAN_CREG_WRITE_C LAN_ECON1, 0b10000000, LAN_REG_BFS	; TXRST - start
	LAN_CREG_WRITE_C LAN_ECON1, 0b10000000, LAN_REG_BFC	; TXRST - stop
	LAN_CREG_WRITE_C LAN_EIR, 0b00001010, LAN_REG_BFC	; clear int flags - ERRATA advise
_LAN_SEND_PACKET_L0:
	rcall	LAN_SELECT_BANK_0
	LAN_CREG_WRITE_LH LAN_EWRPT, LAN_M_TXSTART	; tx buf start

;	pushw	Y					; counter
	ldw	Y, LAN_OP_BUF_LEN	; buffer length
	ldw	Z, LAN_OP_BUF		; address of lan_buffer

	;boundary check	
	lds	temp, LAN_OP_BUF_SIZE
	cp	YL, temp
	lds	temp, LAN_OP_BUF_SIZE+1
	cpc	YH, temp
	brlo	_lan_send_l4
	breq	_lan_send_l4
	rjmp	_LAN_SEND_PACKET_ERR	; error - length exceeds buffer size

_lan_send_l4:
	LAN_TBUF_WRITE Z, Y				; upload buffer to chip

	LAN_CREG_WRITE_LH LAN_ETXST, LAN_M_TXSTART	; tx buf start

	ldiw	Z, LAN_M_TXSTART
	ldw	Y, LAN_OP_BUF_LEN	; buffer length
	add	ZL, YL
	adc	ZH, YH
	LAN_CREG_WRITE_LH_R LAN_ETXND, Z		; tx buf end
;	popw	Y

	LAN_CREG_WRITE_C LAN_ECON1, 0b00001000, LAN_REG_BFS	; TXRTS

;	rcall	_LAN_SEND_WAIT_TXRTS			; wait completion
;	brne	_LAN_SEND_PACKET_OK			; ok, no error
;	rjmp	_LAN_SEND_PACKET_RESET			; clear error and repeat the attempt otherwise

_LAN_SEND_PACKET_OK:
	ldi	temp, 5
	ret
_LAN_SEND_PACKET_ERR:
	ldi	temp, 255		; error with initialization	
	ret




; wait TXRTS clearance
_LAN_SEND_WAIT_TXRTS:
        clr	FROMRAM0
_lan_txrts_l0:
	LAN_ETH_REG_READ LAN_ECON1
	sbrs	temp, 3			; TXRTS
	rjmp	_lan_txrts_l1		; ok - start
	DELAY_10us
	inc	FROMRAM0
	cpi	FROMRAM0, 200		; timeout 2 ms
	brlo	_lan_txrts_l0		; waiting if lower than
	rjmp	_lan_txrts_fault	; error state detected
_lan_txrts_l1:
	LAN_ETH_REG_READ LAN_EIR
	sbrs	temp, 1			; TXERIF
	rjmp	_lan_txrts_ok		; ok - start
	rjmp	_lan_txrts_fault	; error state detected
_lan_txrts_ok:
	clz
	ret
_lan_txrts_fault:
	sez
	ret




; CMDLAN_GET_FRAME receive packet to ram
LAN_RECEIVE_PACKET:
	rcall	LAN_SELECT_BANK_1
	LAN_ETH_REG_READ LAN_EPKTCNT			; check that there is unread packet
	cpi	temp, 0
	brne	_LAN_RECEIVE_PACKET_L0

	sts	LAN_OP_BUF_LEN, zero
	sts	LAN_OP_BUF_LEN+1, zero			; set length=0
	sts	LAN_RXSTATUS, zero
	rjmp	_LAN_RECEIVE_PACKET_ret

_LAN_RECEIVE_PACKET_L0:
	rcall	LAN_SELECT_BANK_0

	ldw	Z, LAN_RXDPT				; current pointer
	LAN_CREG_WRITE_LH_R LAN_ERDPT, Z		; rx buf start
	
	pushw	Y					; counter
	ldw	Z, LAN_OP_BUF				; buffer address
	LAN_TBUF_READ Z, Y				; upload buffer - check for BUF_SIZE is here!
	stw	LAN_OP_BUF_LEN, Y			; store buffer length
	popw	Y

;	ldw	Z, LAN_RXDPT				; current pointer
;	sbiw	Z, 1
;	andi	ZH, high(LAN_M_BUFEND)
;	andi	ZL, low(LAN_M_BUFEND)     		; y = (rxdpt-1) & (buf_len-1)

;	LAN_CREG_WRITE_LH_R LAN_ERXRDPT, Z		; rx buf start - freeing buffer
;	LAN_CREG_WRITE_C LAN_ECON2, 0b01000000, LAN_REG_BFS	; PKTDEC - packet is read

_LAN_RECEIVE_PACKET_ret:
	lds	temp, LAN_RXSTATUS 			; status for return
	ret


; Set packed processed and move to next one
LAN_RECEIVE_PACKET_NEXT:
	ldw	Z, LAN_OP_RXDPT				; current pointer
	stw	LAN_RXDPT, Z				; store permanently
	sbiw	Z, 1
	andi	ZH, high(LAN_M_BUFEND)
	andi	ZL, low(LAN_M_BUFEND)     		; y = (rxdpt-1) & (buf_len-1)

	LAN_CREG_WRITE_LH_R LAN_ERXRDPT, Z		; rx buf start - freeing buffer
	LAN_CREG_WRITE_C LAN_ECON2, 0b01000000, LAN_REG_BFS	; PKTDEC - packet is read
	ret



; compare r19 bytes from (X) and (Z)
LAN_MEM_COMPARE:
	ld	temp, X+
	ld	FROMRAM0, Z+
	cp	FROMRAM0, FF			; FF allows any value
	breq	_lan_mc_l2
	cp	temp, FROMRAM0
	brne	_lan_mc_l1
_lan_mc_l2:
	dec	r19
	brne	LAN_MEM_COMPARE
_lan_mc_l1:
;	cpi	r19, 0
	ret




; compare BEV from (X) and (Z)
LAN_MEM_COMPARE_BEW:
	ld	temp, X+
	ld	r19, X+     			; big endian value
	ld	FROMRAM0, Z+
	cp	r19, FROMRAM0
	brne	_lan_mc_bew_l1
	ld	FROMRAM0, Z+
	cp	temp, FROMRAM0
_lan_mc_bew_l1:
	ret



;COPY 2 Byte (Z)->(X)
_LAN_COPY_2B:
_LAN_COPY_WORD:
	ld	temp, Z+
	st	X+, temp
	ld	temp, Z+
	st	X+, temp
	ret

;COPY 2 Byte (Z)->(X)
_LAN_COPY_PORT:
_LAN_COPY_RWORD:
	ldd	temp, Z+1
	st	X+, temp
	ldd	temp, Z+0
	st	X+, temp
	ret

;COPY 4 Byte (Z)->(X)
_LAN_COPY_IP:
_LAN_COPY_DWORD:
	ld	temp, Z+
	st	X+, temp
	ld	temp, Z+
	st	X+, temp
	ld	temp, Z+
	st	X+, temp
	ld	temp, Z+
	st	X+, temp
	ret

;COPY 6 Byte (Z)->(X)
_LAN_COPY_MAC:
	ld	temp, Z+
	st	X+, temp
	ld	temp, Z+
	st	X+, temp
	ld	temp, Z+
	st	X+, temp
	ld	temp, Z+
	st	X+, temp
	ld	temp, Z+
	st	X+, temp
	ld	temp, Z+
	st	X+, temp
	ret

__LAN_SEND:
	EXEC_LAN_CMD LAN_FUNC_SEND	; safe send
	ret

__LAN_RECEIVE:
	EXEC_LAN_CMD LAN_FUNC_RECEIVE	; safe reveive
	ret
