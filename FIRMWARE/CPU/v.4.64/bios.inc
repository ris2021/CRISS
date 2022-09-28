.MACRO  CURSOR_SET
        ldi	temp, @0
	sts	CURSOR_X, temp
        ldi	temp, @1
	sts	CURSOR_Y, temp
	rcall	CURSOR_APPLY_XY
.ENDM

.MACRO  CURSOR_SET2
	sts	CURSOR_X, @0
	sts	CURSOR_Y, @1
	rcall	CURSOR_APPLY_XY
.ENDM

;.EQU 	zzCURR_DISK_NO 		=	0xF2C8
;.EQU 	zzCURR_TRACK_NUM 	=	0xF2C9
;.EQU 	zzCURR_SECTOR_NUM 	=	0xF2CB
;.EQU 	zzCURR_DMA_BUFER_ADDR 	=	0xF2CC
;.EQU 	zzCURR_DPH_ADDR 	=	0xF2CE
.EQU 	zzDPH0			=	0xDEA0 
;.EQU 	zzDPH1			=	0xDEB0 
;.EQU 	zzDPH2 			=	0xDEC0 
;.EQU 	zzDPH3 			=	0xDED0 
;.EQU 	zzDBP0 			=	0xDEE0 

.EQU 	zzKBD_BUF_COUNT		=	0xE188
.EQU 	zzKBD_BUF_PTR		=	0xE189
.EQU 	zzKBD_CURRCHAR		=	0xE18B

BIOS_START:
        sts	BIOS_LAST_CALL, temp
	NOTIFY	NOTIFY_BIOS, DBG_BIOS

BIOS_CMD_START:
	tcbe	0x00, BIOS_L00
	tcbe	0x01, BIOS_L01
	tcbe	0x02, BIOS_L02		; CONST
	tcbe	0x03, BIOS_L03		; CONIN
	tcbe	0x04, BIOS_L04		; CONOUT
	tcbe	0x05, BIOS_L05		; LIST
	tcbe	0x06, BIOS_L06		; PUNCH
	tcbe	0x07, BIOS_L07		; READER
	tcbe	0x08, BIOS_L08		; HOME
	tcbe	0x09, BIOS_L09		; SELDISK
	tcbe	0x0a, BIOS_L0A		; SETTRK
	tcbe	0x0b, BIOS_L0B		; SETSEC
	tcbe	0x0c, BIOS_L0C		; SETDMA
	tcbe	0x0d, BIOS_L0D		; READ
	tcbe	0x0e, BIOS_L0E		; WRITE
	tcbe	0x0f, BIOS_L0F		; LISTST
	tcbe	0x10, BIOS_L10		; SECTRN
	
	;!!! internal only calls !!!
	tcbe	0xf0, BIOS_Lf0		; CRISS: append to con buffer
	tcbe	0xf1, BIOS_Lf1		; CRISS: append to pr buffer
;	tcbe	0xf8, ECON_REFRESH_SCREEN	; refresh screen via HW
	tcbe	0xf9, BIOS_L04_CHAR_CHAROUT	; echo symbol without attr clear
	tcbe	0xfa, _ECON_CRT_ATTR	; CRISS: put attribute
	tcbe	0xfb, _ECON_GET_ATTR	; get attribute for curr char, return to temp
	tcbe	0xfc, _ECON_SET_ATTR	; set attribute in zzC
	tcbe	0xfd, BIOS_CRT_CHAR	; raw send char to CRT
	tcbe	0xfe, BIOS_SET_VIDEO_MODE ; SET VIDEO MODE
	tcbe	0xff, _BIOS_RESET	; RESET
	ret

	; BOOT
BIOS_L00:
	ret


	; WBOOT
BIOS_L01:
	ret


	; CONST -------------------------------------------------------------------------
	; returns 0 if no char in CON, FF if char is ready
BIOS_L02:
	;checking inputs / CON_IOBYTE
	rcall	CON_GET_INPUTS

	lds	temp, CON_BUF_CNT
	cpi	temp, 0
	brne	BIOS_L02_2

        lds	temp, CON_IOBYTE
        andi	temp, (1<<CON_IN_CON)		; check that CON is avilable - set Z flag if no
	breq	BIOS_L02_1			; temp=0 if CON is disabled, return no char state
        
BIOS_L02_CON:
        nportin cpd_kchar
	cpi	temp, 0
	breq	BIOS_L02_1
BIOS_L02_2:
	ldi	temp, 0xff			; there is a char in the input
BIOS_L02_1:
	mov	zzA, temp			; 0 if no char
	ret


	; CONIN  -------------------------------------------------------------------------
	; returns char from CON, wait if none
BIOS_L03:
	;checking inputs / CON_IOBYTE
	rcall	CON_GET_INPUTS

	; !!!!! need to add initial setting of this bit!!!!
;	sbrs	temp, CON_IN			; CON out requested?
;	rjmp	BIOS_L03_L3

        rcall	CON_BUF_READ
        cpse	zzA, zero
        ret					; char received not from the keyboard - return just zzA!

        lds	temp, CON_IOBYTE
        andi	temp, (1<<CON_IN_CON)		; check that CON is avilable - set Z flag if no
	breq	BIOS_L03_L3			; 

        nportin cpd_kchar
	cpse	temp, zero
	rjmp	BIOS_L03_L1			; char from keyboard received

        lds	temp, MS_MODE			; check mouse if any
        cpse	temp, zero
;	rcall	__delay_15ms
        call	BIOS_MOUSE_AUTOMODE		; if automode is on get mouse state - 10ms!!!!!
;        nop

BIOS_L03_L3:
        sbiw	zzPCl, 2			; repeat command - required for correct IRQ processing
        ret

;__delay_15ms:
;       call	delay_5ms
;        call	delay_5ms
;        call	delay_5ms
;	ret

BIOS_L03_L1:
	sts	CON_LAST_CHAR, temp		; store last char read

	nportin cpd_kactk
	sts	CON_LAST_KACT, temp		; store last char read

	nportin cpd_kmodk
	sts	CON_LAST_MODK, temp		; store last char read

	; check Ctrl-Alt-Del and process if any
	andi	temp, (1<<CTRL)|(1<<SHIFT)|(1<<ALT)
	cpi	temp, (1<<CTRL)|(1<<ALT)
	brne	BIOS_L03_L2

	lds	temp, CON_LAST_KACT
	cpi	temp, 0x61			; DEL scan=97
	breq	BIOS_L03_L2_CAD
	cpi	temp, 0x05			; F1 scan=0x05
	breq	BIOS_L03_L2_F1F2
	cpi	temp, 0x06			; F2 scan=0x06
	breq	BIOS_L03_L2_F1F2
	cpi	temp, 0x77			; F10 scan=0x77
	breq	BIOS_L03_L2_NUMLOCK

	rjmp	BIOS_L03_L2

BIOS_L03_L2_CAD:
	call	CTRLALTDEL			; Ctrl-Alt-Del pressed
BIOS_L03_AFTER_CAD:
	nportout cpd_kchar, zero                ; set kchar as read
	rjmp	BIOS_L03_L3			; proceed with input

BIOS_L03_L2_F1F2:				; switch user session
        cfmem	HW_FOUND, HW_FOUND_ROM		; check that ROM presents
	breq	BIOS_L03_AFTER_CAD		; ignore - no ROM

	subi	temp, 0x05			; select eeprom bank
	breq	BIOS_L03_L2_F1F2_l1
	push	zero
	push	one
	rjmp	BIOS_L03_L2_F1F2_l2

BIOS_L03_L2_F1F2_l1:
	push	one
	push	zero

BIOS_L03_L2_F1F2_l2:
	call	CAD_STORE_STATE
;	call	CAD_SET_EEPROM_SWAP_PROC
	pop	zzA
	call	CAD_SET_EEPROM_RAM_ROM_PROC	; store RAM to ROM 
	pop	zzA
	call	CAD_SET_EEPROM_ROM_RAM_PROC	; read ROM to RAM and restore registers
	call	CAD_EXIT_NO_CRT			; start, no CRT restore
;	sbiw	zzPCl, 2			; repeat BIOS 2 command 

	call	SD_LAST_RESET
;	sts	SD_LASTADDRESS+3, FF
;	sts	SD_LASTADDRESS+2, FF
;	sts	SD_LASTADDRESS+1, FF
;	sts	SD_LASTADDRESS+0, FF		; clear last_access - sdbuf was used

;	;!!! write code here!!!
	rjmp	BIOS_L03_AFTER_CAD		; clear and proceed with input

BIOS_L03_L2_NUMLOCK:				; mouse auto mode
	call	BIOS_MOUSE_ONOFF		; start/stop mouse
;	;!!! write code here!!!
	rjmp	BIOS_L03_AFTER_CAD		; clear and proceed with input

BIOS_L03_L2:
	lds	temp, CON_LAST_CHAR

	mov	zzA, temp			; store to return
        call	HW_CONIN			; invoke hw compatibility processor

        nportout cpd_kchar, zero                ; set kchar as read
	mov	temp, zzA

	cpse	temp, zero
	ret
	rjmp	BIOS_L03			; if hw_conin returns 0 = forbidden key



	; CONOUT -------------------------------------------------------------------------
	; char from zzC to CON
BIOS_L04:
	NOTIFY	NOTIFY_CON, DBG_CONOUT

        push	r20
	lds	r20, CON_IOBYTE			; check internal IOBYTE
	sbrc	r20, CON_OUT_TTY		; TTY out requested?
	rcall	BIOS_L04_TTY_OUT
	sbrc	r20, CON_OUT_LAN		; LAN out requested?
	rcall	BIOS_L04_LAN_OUT
	sbrc	r20, CON_OUT_LST		; LST out requested?
	call	RS232_SEND			; was BIOS_L05
	andi	r20, (1<<CON_OUT_CON)		; check that CON is avilable
	pop	r20

	brne	BIOS_L04_CON			; flag is set - proceed with CON out
	ret					; otherwise return

	;!!!!! need to add initial setting of this bit!!!!
;	sbrs	temp, CON_OUT_CON		; CON out requested?
;	ret

BIOS_L04_CON:
	lds	temp, CON_ESC			; check that ESC seq is processing
	cpse	temp, zero
	rjmp	BIOS04_PROCESS_ESC

	mov	temp, zzC
	cpi	temp, 32
	brsh	BIOS_L04_CHAR

	cpi	temp, 27
	brne	BIOS_L04_SC			; special char
	rjmp	BIOS_L04_ESC			; start esc sequence processing
	
BIOS_L04_SC:
	jmp	HW_CONOUT_SC			; hw-dependent processing only

;	rjmp	BIOS_L04_SPECIAL		; special char

BIOS_L04_CHAR:
;        mov	temp, zzC
        call	HW_CONOUT_CHAR			; process via HW layer first
	
	cpi	zzC, 0
	brne	BIOS_L04_CHAR_L1
	ret					; if hw returns 0 stop processing
		
BIOS_L04_CHAR_L1:
	cfmem	CRT_SETTINGS, CRT_USE_ATTR
	breq	BIOS_L04_CHAR_L2
	call	ECON_ATTR_CHAR			; process attributes if required

BIOS_L04_CHAR_L2:
BIOS_L04_CHAR_CHAROUT:
	rcall	BIOS_CRT_CHAR			; echo char
	lds	temp, CURSOR_X
	cpmem 	temp, CRT_CHARS			; last position?
	brlo	BIOS_L04_CHAR_L3		; no - just increment

	rjmp	BIOS_L04_CRLF			; next line

BIOS_L04_CHAR_L3:
	pushw	Z
	ldw	Z, VIDEO_CURSOR
	adiw	Z, 1				; forward 1 char
	rcall	BIOS_ASSIGN_CURSOR
	popw	Z
	ret

BIOS_L04_ESC:	; ESC-codes - starting!
	sts	CON_ESC, one
	ret



	; LIST ----------------------------------------------------------------------------
	; char from C to LST/LPT
BIOS_L05:
	push	r20
	lds	r20, DEV_IOBYTE
	sbrc	r20, LST_OUT_LPT
	rcall	BIOS_L05_LPT
	sbrc	r20, LST_OUT_TTY
	rcall	BIOS_L05_TTY
	sbrc	r20, LST_OUT_LAN
	rcall	BIOS_L05_LAN
	sbrc	r20, LST_OUT_LST
	call	RS232_SEND
	pop	r20
	ret

;	lds	temp, RTC_HW_DISABLE	; check that LST is enabled
;	sbrc	temp, HW_DSBL_LST
;	ret

;	nportin cpd_comtc
;	cpi	temp, 0
;	brne	BIOS_L05		; wait current char is transmitted
;	nportout cpd_comtx, zzC		; char to send
;	delay3	15
;	nportout cpd_comtc, one		; force transmit action
;	ret


	; PUNCH ----------------------------------------------------------------------------
	; char from C to punch - out to UART1
BIOS_L06:
	push	r20
	lds	r20, PR_IOBYTE
	sbrc	r20, PRIO_OUT_CAN
	rcall	BIOS_L06_CAN
	sbrc	r20, PRIO_OUT_TTY
	rcall	BIOS_L06_TTY
	sbrc	r20, PRIO_OUT_LAN
	rcall	BIOS_L06_LAN
	sbrc	r20, PRIO_OUT_LST
	call	RS232_SEND
;	rcall	BIOS_L05		; LIST command
	pop	r20
	ret


	; READER ----------------------------------------------------------------------------
	; read char from punch
BIOS_L07:
	push	r20
	lds	r20, PR_IOBYTE
	sbrc	r20, PRIO_IN_CAN
	rcall	BIOS_L07_CAN
	sbrc	r20, PRIO_IN_TTY
	rcall	BIOS_L07_TTY
	sbrc	r20, PRIO_IN_LAN
	rcall	BIOS_L07_LAN
	sbrc	r20, PRIO_IN_LST
	rcall	BIOS_L07_LST		; LIST command
	pop	r20

	rcall	PR_BUF_READ
_BIOS_L07_ret:
	ret


	; HOME ----------------------------------------------------------------------------
	; Nothing to do
BIOS_L08:
	ret


	; SELDSK
	; select disk from zzC, zzHL
BIOS_L09:
	sts	BIOS_DISK, zzC
	mov	zzA, zzC		; undocumented

	pushw	Z
;	ldiw	Z, zzCURR_DISK_NO
;	STRAM	ZH, ZL, zzC

	ldiw	Z, zzDPH0
	mov	temp, zzC
	or	temp, temp
	breq	BIOS_L09_L1
BIOS_L09_L2:
	adiw	Z, 16
	dec	temp
	brne	BIOS_L09_L2		; Z = DPH0+16*C

BIOS_L09_L1:
	mov	zzH, ZH
	mov	zzL, ZL			; HL = DPH

;	ldiw	Z, zzCURR_DPH_ADDR
;	STRAM	ZH, ZL, zzL
;	adiw	Z, 1
;	STRAM	ZH, ZL, zzH	
	popw	Z

	ret


	; SETTRK -------------------------------------------------------------------------------------------
	; Set track from zzBC
BIOS_L0A:
	sts	BIOS_TRACK, zzB
	sts	BIOS_TRACK+1, zzC

;	pushw	Z
;	ldiw	Z, zzCURR_TRACK_NUM
;	STRAM	ZH, ZL, zzC
;	adiw	Z, 1
;	STRAM	ZH, ZL, zzB
;	popw	Z
	ret


	; SETSEC -------------------------------------------------------------------------------------------
	; Set sector from zzC
BIOS_L0B:
	sts	BIOS_SECTOR, zzC
	mov	zzA, zzC			; undocumented

;	pushw	Z
;	ldiw	Z, zzCURR_SECTOR_NUM
;	STRAM	ZH, ZL, zzC
;	popw	Z
	ret


	; SETDMA -------------------------------------------------------------------------------------------
	; Set DMA address from zzBC
BIOS_L0C:
	sts	BIOS_DMA, zzB
	sts	BIOS_DMA+1, zzC

;	pushw	Z
;	ldiw	Z, zzCURR_DMA_BUFER_ADDR
;	STRAM	ZH, ZL, zzC
;	adiw	Z, 1
;	STRAM	ZH, ZL, zzB
;	popw	Z
	ret


	; READ  -------------------------------------------------------------------------------------------
	; read sector, return error code to zzA
BIOS_L0D:
	lds	temp, SD_TYPE
	cpse	temp, zero
;	brne
;	lds	temp, HW_FOUND
;	sbrc	temp, HW_FOUND_SDC	; when ROM is available but SD is absent start from ROM#A
	rjmp	BIOS_L0D_SDOK
	ldi	temp, 0x02		; device is not eady
	rjmp	BIOS_L0D_RET		; return
		
BIOS_L0D_SDOK:
	rcall	BIOS_SD_SETADDR

	pushw	Z
	pushw	X	
;BIOS_L0D_STORE:
	ldiw	X, SD_BUF			; 512 bytes buffer address

	andi	temp, 0x03			; sector index 0-3
	breq	BIOS_L0D_TRANSFER
BIOS_L0D_L4:
	adiw	X, 32
	adiw	X, 32
	adiw	X, 32                           ; X+=128
	adiw	X, 32				; calculating start position to get data
	dec	temp
	brne	BIOS_L0D_L4

BIOS_L0D_TRANSFER:	
	lds	ZH, BIOS_DMA
	lds	ZL, BIOS_DMA+1
	
;	ldiw	Z, zzCURR_DMA_BUFER_ADDR
;	LDRAM   ZH, ZL, temp
;	push	temp	
;	ldiw	Z, zzCURR_DMA_BUFER_ADDR+1
;	LDRAM   ZH, ZL, temp
;	mov	ZH, temp
;	push	temp	
;	pop	ZH
;	pop	ZL				; RAM address of DMA buffer

	;!!!!!!! rewirite with MCOPY!!!!
	push	zzA
	ldi	temp, 128			; bytes to transfer
BIOS_L0D_L3:
	ld	zzA, X+
	STRAM	ZH, ZL, zzA
	adiw	Z, 1
	dec	temp
	brne	BIOS_L0D_L3			; store sector to RAM
	pop	zzA

	ldi	temp, 0				; success

BIOS_L0D_NOSD:
;        pop	zzA
	popw	X
	popw	Z

BIOS_L0D_RET:
	NOTIFY	NOTIFY_SD, DBG_SDERR

	mov	zzA, temp			; error code
	ret


	; WRITE -------------------------------------------------------------------------------------------
	; write sector to disk, return error code to zzA
BIOS_L0E:
;	lds	temp, HW_FOUND
;	sbrc	temp, HW_FOUND_SDC	; when ROM is available but SD is absent start from ROM#A
	lds	temp, SD_TYPE
	cpse	temp, zero
	rjmp	BIOS_L0E_SDOK
	ldi	temp, 0x02		; device is not eady
	rjmp	BIOS_L0E_RET		; return

BIOS_L0E_SDOK:
	rcall	BIOS_SD_SETADDR

	pushw	Z
	pushw	X

	ldiw	X, SD_BUF
	andi	temp, 0x03			; sector index 0-3
	breq	BIOS_L0E_TRANSFER
BIOS_L0E_L4:
	adiw	X, 32
	adiw	X, 32
	adiw	X, 32                           ; X+=128
	adiw	X, 32				; calculating start position to get data
	dec	temp
	brne	BIOS_L0E_L4

BIOS_L0E_TRANSFER:	
	lds	ZH, BIOS_DMA
	lds	ZL, BIOS_DMA+1

;	ldiw	Z, zzCURR_DMA_BUFER_ADDR
;	LDRAM   ZH, ZL, temp
;	push	temp	
;	ldiw	Z, zzCURR_DMA_BUFER_ADDR+1
;	LDRAM   ZH, ZL, temp
;	mov	ZH, temp
;	push	temp	
;	pop	ZH
;	pop	ZL				; RAM address of DMA buffer


	;!!!!!!! rewirite with MCOPY!!!!
	push	zzA
	ldi	temp, 128			; bytes to transfer
BIOS_L0E_L3:
        LDRAM   ZH, ZL, zzA
	st	X+, zzA
	adiw	Z, 1
	dec	temp
	brne	BIOS_L0E_L3			; store sector to RAM
	pop	zzA

	ldi	temp, 0				; success
	call	SD_WRITE_DO			; store 512 bytes buffer

BIOS_L0E_NOSD:
	popw	X
	popw	Z

BIOS_L0E_RET:
	NOTIFY	NOTIFY_SD, DBG_SDERR

	mov	zzA, temp			; error code
	ret


	; LISTST -------------------------------------------------------------------------------------------
	; printer status: always returns 0xff, also reads char from LST channel, it is stored in [LST_LAST_CHAR]
	;???? think carefully !!!
BIOS_L0F:
	push	r20
	lds	r20, DEV_IOBYTE
	sbrc	r20, LST_OUT_LPT
	rcall	BIOS_L0F_LPT
	sbrc	r20, LST_OUT_TTY
	rcall	BIOS_L0F_TTY
	sbrc	r20, LST_OUT_LAN
	rcall	BIOS_L0F_LAN
	sbrc	r20, LST_OUT_LST
	rcall	BIOS_L0F_LST
	pop	r20
;	ret

;        call	RS232_RECEIVE
	ldi	zzA, 0xff	
	sts	LST_LAST_CHAR, temp

;	nportin	cpd_comst
;	clr	zzA
;	sbrs	temp, 7		; check RXC flag
;	ret
;	nportin	cpd_comrx
;	mov	zzC, temp	
;	ldi	zzA, 0xff	
;	sts	LST_LAST_CHAR, zzC
	ret


	; SECTRN -------------------------------------------------------------------------------------------
	; sectro translation
BIOS_L10:
	;HL = BC; no translation
	mov	zzH, zzB
	mov	zzL, zzC
	ret


_BIOS_RESET:
	rjmp	BIOS_RESET


BIOS_CRT_CHAR:
	pushw	Z
	ldw	Z, VIDEO_CURSOR
	ldi	temp, 0xf7			; RAM F8** address
	add	ZH, temp
	STRAM	ZH, ZL, zzC			; store in RAM and send to CPD
	popw	Z
	ret



; store zzC to con buf
BIOS_Lf0:
CON_BUF_ADD:
	cpi	zzC, 0
	breq	XXX_BUF_ADD_0
	lds	temp, CON_BUF_CNT
	cpi	temp, CON_BUF_LEN
	brsh	XXX_BUF_ADD_ovf		; buffer is overflowed, ignore
	ldiw	Z, CON_BUF
	add	ZL, temp
	adc	ZH, zero
	inc	temp
	sts	CON_BUF_CNT, temp
;	lds	temp, LAN_UDP_DATA	; only 1 byte message allowed
	st	Z, zzC
XXX_BUF_ADD_1:
	clc				; 1 char stored
	clz
	ret
XXX_BUF_ADD_ovf:
	sec				; c==1 == overflow state 
	ret
XXX_BUF_ADD_0:
	clc				; no data stored 
	sez				; 
	ret

; store zzC to PR buf
BIOS_Lf1:
PR_BUF_ADD:
	cpi	zzC, 0
	breq	XXX_BUF_ADD_0
	lds	temp, PR_BUF_CNT
	cpi	temp, PR_BUF_LEN
	brsh	XXX_BUF_ADD_ovf		; buffer is overflowed, ignore
	ldiw	Z, PR_BUF
	add	ZL, temp
	adc	ZH, zero
	inc	temp
	sts	PR_BUF_CNT, temp
;	lds	temp, LAN_UDP_DATA              ; only 1 byte message allowed
	st	Z, zzC
	rjmp	XXX_BUF_ADD_1
;PR_BUF_ADD_ret:
;	ret


_ECON_CRT_ATTR:
	jmp	ECON_CRT_ATTR


_ECON_GET_ATTR:
	rjmp	ECON_GET_ATTR	; get attribute for curr char, return to temp

_ECON_SET_ATTR:	; set attribute in zzC
	rjmp	ECON_SET_ATTR	; set attribute in zzC

;_BIOS_CRT_CHAR:	; raw send char to CRT
;	rjmp	BIOS_CRT_CHAR	; raw send char to CRT



; read data from PR buffer
PR_BUF_READ:
	ldi	zzA, 0

	lds	temp, PR_BUF_CNT
	cpi	temp, 0
	breq	PR_BUF_READ_ret		; get from buffer

	ldiw	Z, PR_BUF
	ld	zzA, Z			; get data
	dec	temp
	sts	PR_BUF_CNT, temp
	breq	PR_BUF_READ_ret		; get from buffer
;	ldi	temp, PR_BUF_LEN-1
PR_BUF_READ_l1:
	ldd	FROMRAM0, Z+1
;	sbiw	Z, 1			; goto previous char
	st	Z+, FROMRAM0
;	adiw	Z, 2			; go ahead +2
	dec	temp
	brne	PR_BUF_READ_l1
PR_BUF_READ_ret:
	ret


; -------------------------------------------------------------------------------------------------------
	; scroll screen down 1 line
SCREEN_SCROOL_DOWN_RAM:
	pushw	X
	pushw	Y
	pushw	Z
	push	r19

	ldw	Y, VIDEO_END
	ldi	temp, 0xf7
	add	YH, temp

	ldiw	X, 0xF800			; start of videoram
	ldiw	Z, 0xF800;+80			; starting from second line
	lds	temp, CRT_CHARS
	add	ZL, temp
	adc	ZH, zero
;	LDRAM 	ZH, ZL, temp			; read char from zRAM

;SCREEN_SCROOL_DOWN_RAM_DO:
SSD_L1:
	LDRAM 	ZH, ZL, temp			; read char from zRAM
	STRAM	XH, XL, temp
	adiw	X, 1
	adiw	Z, 1

;	cpi	XH, 0xfa ;!!!
;	breq	SSD_L2 ;!!!

	cp	ZL, YL
	cpc	ZH, YH
	brlo	SSD_L1				; loop

	ldi	r19, ' '			; fill last line with spaces
SSD_L2:
	STRAM	XH, XL, r19
	adiw	X, 1
	cp	XL, YL
	cpc	XH, YH
	brlo	SSD_L2				; loop

	pop	r19
	popw	Z
	popw	Y
	popw	X                               ; restore registers

	ret


; -------------------------------------------------------------------------------------



CURSOR_XY_PTR:
	pushw	Z
	push	FROMRAM0
	push	r0
	push	r1
	push	temp

	lds	temp, CURSOR_Y
	dec	temp
;	ldi	FROMRAM0, 80
	lds	FROMRAM0, CRT_CHARS
	mul	temp, FROMRAM0			; y*80

	ldi	ZH, 1
	lds	ZL, CURSOR_X
	dec	ZL				; pointer starts from 0
	add	ZL, r0
	adc	ZH, r1

	sts	VIDEO_CURSOR, ZL
	sts	VIDEO_CURSOR+1, ZH

	pop	temp
	pop	r1
	pop	r0
	pop	FROMRAM0
	popw	Z
	ret

; -------------------------------------------------------------------------------------
	; must be called after setting CURSOR_* in memory
CURSOR_APPLY_XY:
	rcall	CURSOR_XY_PTR
;	pushw	Z
;	ldi	ZH, 1
;	lds	ZL, CURSOR_X
;	dec	ZL				; pointer starts from 0
;	lds	temp, CURSOR_Y
;MCS_L02:
;	cpi	temp, 1
;	breq	MCS_L01
;	adiw	Z, 40
;	adiw	Z, 40				; next line
;	dec	temp
;	rjmp	MCS_L02
;MCS_L01:
;	sts	VIDEO_CURSOR, ZL
;	sts	VIDEO_CURSOR+1, ZH

	rcall	BIOS_SETCPDCURSOR		; send cursor ro CPD and ret
;	popw	Z
	ret


	/*
; -------------------------------------------------------------------------------------
	; send local videoram to CPD
SCREEN_SEND_CPD:
	pushw	Y
	pushw	Z
	ldw	Y, VIDEO_END
	ldiw	Z, 0x100
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4		
	SPI_SELECT
SSC_L1:
	ld	temp, Z
	cpi	temp, 32
	brlo	SSC_L2				; ignore non-printed chars

	ldi	temp, 0xf7
	add	temp, ZH
	call	DOSPI				; f8
	mov	temp, ZL
	call	DOSPI				; xx
	ld	temp, Z
	call	DOSPI				; char
SSC_L2:
	adiw	Z, 1
	cp	YL, ZL
	cpc	YH, ZH
	brne	SSC_L1				; send all videoram
	SPI_STOP
	popw	Z
	popw	Y
	ret
*/	

;---------------------------------------------------------------------------------------
	; store cursor position, current CP ram ptr in ZH, ZL
BIOS_ASSIGN_CURSOR:
	sts	VIDEO_CURSOR, ZL
	sts	VIDEO_CURSOR+1, ZH              ; store new cursor pointer

	; calculating new line and pos
	push 	r18
	pushw	Y                               ; save registers
	ldi	YH, 1
	ldi	YL, 0
;	ldi	temp, 80
	lds	temp, CRT_CHARS
	; calculating line
	clr	r18				; r18=0
BIOS_AC_L01:
	inc	r18                             ; lines in cursor position start from 1
	add	YL, temp
	adc	YH, zero	
	cp	YL, ZL
	cpc	YH, ZH
	brlo	BIOS_AC_L01			; while Y<Z Y+=80

	sts	CURSOR_Y, r18                   ; store new cursor positions

	sub	YL, temp
	sbc	YH, zero
;	sbiw	Y, 40
;	sbiw	Y, 40

	; calculating position
	sub	ZL, YL
	sbc	ZH, YH				; zl = Z-Y
	inc	ZL
	sts	CURSOR_X, ZL			; store new cursor positions
	popw	Y
	pop	r18				; restore registers
;	ret
	; calculating position
;	clr	r18
;BIOS_AC_L02:
;	inc	r18                             ; lines in cursor position start from 1
;	add	YL, one
;	adc	YH, zero	
;	cp	YL, ZL
;	cpc	YH, ZH
;	brlo	BIOS_AC_L02			; while Y<Z Y+=80

;	sts	CURSOR_X, r18			; store new cursor positions
;	popw	Y
;	pop	r18				; restore registers

	; cursor position is in Z
BIOS_SETCPDCURSOR:
	pushw	Z
	push	temp
        lds	ZL, VIDEO_CURSOR
        lds	ZH, VIDEO_CURSOR+1
	lds	temp, CURSOR_STATUS             ; take cursor status
	or	temp, ZH			; return bit 7 set if cursor is off to hide it
	nportout cpd_vcurh, temp
	nportout cpd_vcurl, ZL
	pop	temp
	popw	Z
	ret



; -------------------------------------------------------------------------------------
	; fill videoram with zzA
SCREEN_CLEAR_A:
/*
	push	FROMRAM0
	push	FROMRAM1
	push	zzC
	ldiw	X, 0xF800			; start of videoram
	lds	FROMRAM0, CRT_LINES
	lds	FROMRAM1, CRT_CHARS
_sc_clr_l1:
	ldi	zzC, 0
_sc_clr_l3:
;	cp	zzC, FROMRAM1
;	brsh	_sc_clr_l2			; end of line reached
	STRAM	XH, XL, zzA
_sc_clr_l2:
	adiw	X, 1
	inc	zzC
	cpi	zzC, FROMRAM1 ;80
	brne	_sc_clr_l3
	dec	FROMRAM0
	brne	_sc_clr_l1

	pop	zzC
	pop	FROMRAM1	
	pop	FROMRAM0
	ret
*/
	
	pushw	x
	pushw	Y
	ldw	Y, VIDEO_END
	ldi	temp, 0xf7
	add	YH, temp
	ldiw	X, 0xF800			; start of videoram
SC_CLR_L1:
	STRAM	XH, XL, zzA
	adiw	X, 1
	cp	XL, YL
	cpc	XH, YH
	brlo	SC_CLR_L1			; loop
	popw	Y
	popw	X
	ret



; -------------------------------------------------------------------------------------
	; fill videoram with spaces
SCREEN_CLEAR:
	push	zzA
	lds	zzA, CRT_SETTINGS
	andi	zzA, 0x07			; active codepage
	cpi	zzA, 1				; graph mode?
	brne	_screen_clear_l1
	ldi	zzA, 0          		; for graph mode fill with 0
	rjmp	_screen_clear_l2
_screen_clear_l1:
	ldi	zzA, ' '			; text mode - fill with spaces
_screen_clear_l2:
	rcall	SCREEN_CLEAR_A
	pop	zzA
	ret


; ----------------- process ESC code -------------------------
BIOS04_PROCESS_ESC:
        cpi	temp, 9
        brlo	BIOS04_PROCESS_ESC_L0
        sts	CON_ESC, zero			; stop processing = error, no processor!
        ret

BIOS04_PROCESS_ESC_L0:	
	ldiw	Z, CON_ESC
	add	ZL, temp
	adc	ZH, zero
	st	Z, zzC				; store char to (CON_ESC+temp)

	inc	temp				; total number of chars in the sequence
	mov	FROMRAM2, temp			; save for restore
	mov	FROMRAM1, temp			; save for restore
;	sts	CON_ESC, zero			; for the case when call
	call	HW_CONOUT_ESC
	sts	CON_ESC, FROMRAM2		; call returns 0 if request is processed
	ret



;--------------------------------------------------------------------------------
; set SD_ADDRESS, read block if required, returns sector_num in temp
BIOS_SD_SETADDR:
	pushw	Z
	pushw	X
	push	zzA

	lds	zzA, BIOS_DISK

;	ldiw	Z, zzCURR_DISK_NO
;	LDRAM   ZH, ZL, zzA		; zzA = selected disk 0 .. 15
	ldiw	X, SD_FDD_BASE
	add	XL, zzA
	adc	XH, zero
	ld	zzA, X			; zzA = disk index 01..ff
	clr	XH
	clr	XL			; X = 0
	lsr	zzA			; shifting low zzA tetrade to high XH tetrade
	ror	XH
	lsr	zzA
	ror	XH
	lsr	zzA
	ror	XH
	lsr	zzA
	ror	XH			; start block addr: zzA XH XL

;	lds	temp, BIOS_TRACK
	lds	temp, BIOS_TRACK+1

;	ldiw	Z, zzCURR_TRACK_NUM
;	LDRAM   ZH, ZL, temp
	cpi	temp, 0
	breq	BIOS_SD_SETADDR_L1
BIOS_SD_SETADDR_L2:
	adiw	X, 20			; 20 SDblocks per track
	dec	temp
	brne	BIOS_SD_SETADDR_L2

BIOS_SD_SETADDR_L1:
	lds	temp, BIOS_SECTOR

;	ldiw	Z, zzCURR_SECTOR_NUM
;	LDRAM   ZH, ZL, temp
	push	temp			; store sector to return
	lsr	temp
	lsr	temp			; /4 - 512 sector address
	add	XL, temp
	adc	XH, zero

	NOTIFY	NOTIFY_SD, DBG_SD
;	lds	temp, SYS_NOTIFY	
;	sbrc	temp, 4				;!!! debug request
;	call	DBG_SDREAD

	lds	temp, SD_LASTADDRESS    ; check that block is last accessed
	cp	temp, XL
	brne	BIOS_SD_SETADDR_READ512
	lds	temp, SD_LASTADDRESS+1
	cp	temp, XH
	brne	BIOS_SD_SETADDR_READ512
	lds	temp, SD_LASTADDRESS+2
	cp	temp, zzA
	brne	BIOS_SD_SETADDR_READ512
	lds	temp, SD_LASTADDRESS+3
	cp	temp, zero
	brne	BIOS_SD_SETADDR_READ512

;	ret
	rjmp	BIOS_SD_SETADDR_READY	; buffer already has been read!

BIOS_SD_SETADDR_READ512:
	sts	SD_ADDRESS, XL		; set block address
	sts	SD_ADDRESS+1, XH	
	sts	SD_ADDRESS+2, zzA
	sts	SD_ADDRESS+3, zero
	call	SD_READ_DO           	; read 512 SDblock
	
	lds	temp, SD_ERROR
	NOTIFYt	NOTIFY_SD, '<'
	;!!! add error check!!!

BIOS_SD_SETADDR_READY:
	sts	SD_ADDRESS, XL		; set block address for the use
	sts	SD_ADDRESS+1, XH	
	sts	SD_ADDRESS+2, zzA
	sts	SD_ADDRESS+3, zero

;BIOS_SD_SETADDR_READY:
	pop	temp
	pop	zzA
	popw	X
	popw	Z
	ret


; --------------------------------------------------
; set video mode from active sttings
BIOS_SET_VIDEO_MODE:
	push	FROMRAM0
	push	temp
	lds	FROMRAM0, CRT_SETTINGS	
        lds	temp, CRT_LINES
        lsl	temp
        lsl	temp
        lsl	temp
        andi	FROMRAM0, 0x07		; codepage
        or	temp, FROMRAM0
	nportout cpd_vstat, temp	; set new settings

	ldi	temp, 0x80
        cpse	FROMRAM0, one		; is graphic mode?
	ldi	temp, 0			; enable cursor if not
	sts	CURSOR_STATUS, temp	; cursor status
	rcall	CURSOR_APPLY_XY		; set cursor

	;set VIDEO_END
	push	r0
	push	r1
	lds	temp, CRT_LINES
;	ldi	FROMRAM0, 80
	lds	FROMRAM0, CRT_CHARS
	mul	temp, FROMRAM0		; y*80
	inc	r1			; +0x100
	sts	VIDEO_END, r0		; low
	sts	VIDEO_END+1, r1		; high
	pop	r1
	pop	r0

	sts	CON_WIN_X0, one		; reset active window
	ldstt	CON_WIN_X1, CRT_CHARS
	sts	CON_WIN_Y0, one
	ldstt	CON_WIN_Y1, CRT_LINES

	;???? add CLRSCR ????

	pop	temp
	pop	FROMRAM0
	ret



; CON: write to 
BIOS_L04_TTY_OUT:
; LST write to punch device
BIOS_L05_TTY:
; PUNCH write to punch device
BIOS_L06_TTY:
	mov	temp, zzC
	call 	UART1_SEND
	ret

; CON: write to 
;BIOS_L04_TTY_OUT:
;	mov	temp, zzC
;	call	UART1_SEND
;	ret



BIOS_L06_CAN:
	;!!!! code here
	ret


BIOS_L05_LAN:
	EXEC_LAN_CMD LAN_FUNC_SEND_PRN	; CMDLAN_SEND_PR
	ret


BIOS_L06_LAN:
	EXEC_LAN_CMD LAN_FUNC_SEND_PR	; CMDLAN_SEND_PR
	ret


; READER read data from 
BIOS_L07_TTY:
        lds	temp, UCSR1A
        sbrs	temp, RXC1
        ret
        lds	zzC, UDR1
        rcall	PR_BUF_ADD
	ret

BIOS_L07_CAN:
	;!!!! code here
	ret


BIOS_L03_LAN:
BIOS_L07_LAN:
	EXEC_LAN_CMD LAN_FUNC_PROCESS	; CMDLAN_PROCESS
	ret

; read data from LST
BIOS_L07_LST:			
	call	RS232_RECEIVE
;	nportin	cpd_comst
;	sbrs	temp, 7			; check RXC flag
;	ret
;	nportin	cpd_comrx
	mov	zzC, temp	
        rcall	PR_BUF_ADD
	ret


; CONIN input
BIOS_L03_TTY:
        lds	temp, UCSR1A
        sbrs	temp, RXC1
        ret
        lds	zzC, UDR1
        rcall	CON_BUF_ADD
	ret

; read data from LST
BIOS_L03_LST:			
	nportin	cpd_comst
	sbrs	temp, 7			; check RXC flag
	ret
	nportin	cpd_comrx
	mov	zzC, temp	
        rcall	CON_BUF_ADD
	ret


; conout write to 
BIOS_L04_LAN_OUT:
	EXEC_LAN_CMD LAN_FUNC_SEND_SRV	; CMDLAN_SEND_SERVER
	ret

BIOS_L04_CAN_OUT:
	;!!!! code here
	ret

; conout write to 
BIOS_L05_LAN_OUT:
	EXEC_LAN_CMD LAN_FUNC_SEND_PRN	; CMDLAN_SEND_PRN
	ret


	;!!!!!! write output to LPT
BIOS_L05_LPT:
	nportout_t cpd_twdti, 0b00000001	; strobe hi
	nportout_t cpd_twcmd, 0b01110000	; write to DD1
	rcall	GPIO_WAIT
	brne	_bios_l05_lpt_ret

	nportout cpd_twdti, zzC		; data
	nportout_t cpd_twcmd, 0b01110010	; write to DD2
	rcall	GPIO_WAIT
	brne	_bios_l05_lpt_ret

	nportout_t cpd_twdti, 0b00000000	; strobe low
	nportout_t cpd_twcmd, 0b01110000	; write to DD1
	rcall	GPIO_WAIT
	brne	_bios_l05_lpt_ret

	nportout_t cpd_twdti, 0b00000001	; strobe hi
	nportout_t cpd_twcmd, 0b01110000	; write to DD1
	rcall	GPIO_WAIT

;	;!!!! code here !!!!!
_bios_l05_lpt_ret:
	ret


	; sends zzC to port temp
GPIO_SEND:
	; wait GPIO operation complete
	nportout cpd_twdti, zzC		; data
	nportout cpd_twcmd, temp	; write
GPIO_WAIT:
	nportin	cpd_twcmd
	cpi	temp, 0x02
	brsh	GPIO_WAIT		; wait
	cp	temp, zero		; set flag z if success
	ret



	; read printer status from TTY
BIOS_L0F_LPT:
;	nportout_t cpd_twdti, 0b00000001	; strobe hi
	nportout_t cpd_twcmd, 0b01110101	; READ DD3
	rcall	GPIO_WAIT
	nportin cpd_twdti
	ret
	

BIOS_L0F_TTY:
        lds	temp, UCSR1A
        sbrs	temp, RXC1
        rjmp	_l0f_tty_l1
        lds	temp, UDR1
        ret
_l0f_tty_l1:
	ldi	temp, 0
	ret


BIOS_L0F_LAN:	
	ldi	temp, 0
	ret

BIOS_L0F_LST:
        call	RS232_RECEIVE
        ret


	; read data from CON buffer
CON_BUF_READ:
	ldi	zzA, 0

	lds	temp, CON_BUF_CNT
	cpi	temp, 0
	breq	CON_BUF_READ_ret	; get from buffer

	ldiw	Z, CON_BUF
	ld	zzA, Z			; get data
	dec	temp
	sts	CON_BUF_CNT, temp
	breq	CON_BUF_READ_ret	; get from buffer
;	ldi	temp, CON_BUF_LEN-1
CON_BUF_READ_l1:
	ldd	FROMRAM0, Z+1
;	sbiw	Z, 1			; goto CONevious char
	st	Z+, FROMRAM0
;	adiw	Z, 2			; go ahead +2
	dec	temp
	brne	CON_BUF_READ_l1
CON_BUF_READ_ret:
;	mov	temp, zzA
	ret


	; get CON input data from available sources
CON_GET_INPUTS:
        push	zzC
        push	r20
	lds	r20, CON_IOBYTE		; check internal IOBYTE
	sbrc	r20, CON_IN_TTY		; TTY out requested?
	rcall	BIOS_L03_TTY
	sbrc	r20, CON_IN_LAN		; LAN out requested?
	rcall	BIOS_L03_LAN
	sbrc	r20, CON_IN_LST		; LST out requested?
	rcall	BIOS_L03_LST
;	andi	r20, (1<<CON_IN_CON)	; check that CON is avilable - set Z flag if no
        pop	r20
	pop	zzC
	ret


#include "bios_sc.inc"
#include "bios_attr.inc"
#include "bios_esc.inc"
#include "bios_mice.inc"

