.MACRO	mMSG
	.DB	high(0xf800+((@1)-1)*80+((@0)-1)), low(0xf800+((@1)-1)*80+((@0)-1)), @2, 0
.ENDM

.MACRO 	m_puts
	ldi	zh, high((@0)*2)    
	ldi	zl, low((@0)*2)
	rcall	CAD_PUTS_XY
.ENDM

.MACRO 	m_puts_block
	ldi	r19, @1
	ldi	zh, high((@0)*2)    
	ldi	zl, low((@0)*2)
	rcall	CAD_PUT_MSG_BLOCK
.ENDM

.MACRO 	m_puts_c
	ldi	zh, high((@0)*2)    
	ldi	zl, low((@0)*2)
	rcall	CAD_PUTS
.ENDM

; copy (@0) -> @1, @2 bytes
.MACRO	ldir
    	ldiw	Y, @0	
_l4:
    	ld	temp, Y+
    	st	@1, temp
	cpi	YL, low(@0+@2+1)	
	brne	_l4
.ENDM

; copy (@0) -> @1, @2 bytes
.MACRO	sdir
    	ldiw	Y, @0	
_l4:
    	ld	temp, @1
    	st	Y+, temp
	cpi	YL, low(@0+@2+1)	
	brne	_l4
.ENDM


	; process NMI Ctrl-Alt-Del
	; ctr-alt-del pressed
CAD_CMD:
	rjmp	_CAD_CMD
CTRLALTDEL:
	rjmp	_CTRLALTDEL

CAD_STORE_STATE:
;	pushw	X
;	pushw	Y
;	pushw	Z
;	push	r19
;       push	zzA
;	push	temp

;	nportin cpd_vstat		; read crt settings
;	sts	DBG_DATA, temp		; store codepage

;	ldiw	X, 8			; pointer in RAM
	ldiw	Z, HW_DATA		; pointer in HWDATA
	st	Z+, zzA
	st	Z+, zzF
	st	Z+, zzB
	st	Z+, zzC
	st	Z+, zzD
	st	Z+, zzE
	st	Z+, zzH
	st	Z+, zzL
	st	Z+, zzIXl
	st	Z+, zzIXh
	st	Z+, zzIYl
	st	Z+, zzIYh
	st	Z+, zzSPl
	st	Z+, zzSPh
	st	Z+, zzPCl
	st	Z+, zzPCh
;	ldi	temp, 26
;_cad_store_loop:
;	ld	temp, X+
;	st	Z+, temp
;	cpi	XL, 32-6		; till r25
;	brlo	_cad_store_loop
;	st	Z+, YH
;	st	Z+, YL
	ret


_CTRLALTDEL:
	ldi	temp, (25<<3)|0
	nportout cpd_vstat, temp	; set standard video mode

	rcall	CAD_STORE_STATE

	call	SYSTEM_BEEP		; welcome beep
	nportout cpd_kchar, zero	; clear char just for the case

CAD_MAIN:
	rcall	CAD_CLRSCR

	m_puts_block CAD_MSG_WC, 9

;	m_puts CAD_MSG_WC
;	m_puts CAD_MSG_M1
;	m_puts CAD_MSG_M2
;	m_puts CAD_MSG_M3
;	m_puts CAD_MSG_M4
;	m_puts CAD_MSG_M5
;	m_puts CAD_MSG_M6
;	m_puts CAD_MSG_MA
;	m_puts CAD_MSG_M7		; screen messages

	lds	temp, HW_FOUND
	sbrs	temp, HW_FOUND_RTC	; check that RTC found
	rjmp	_cad_l1

;	m_puts_block CAD_MSG_M10, 2
	m_puts CAD_MSG_M10
;	m_puts CAD_MSG_M11
_cad_l1:	

	lds	temp, HW_FOUND
	sbrs	temp, HW_FOUND_ROM	; check that EEPROM found
	rjmp	_cad_l0
	m_puts CAD_MSG_M9
_cad_l0:	

;	m_puts CAD_MSG_M8		; screen messages
	m_puts_block CAD_MSG_M13, 2	; VRAM HALT
;	m_puts CAD_MSG_M14		; HALT

;	m_puts CAD_MSG_MS
	m_puts CAD_MSG_RM
;	rcall	CAD_CURSOR

CAD_COMMAND:
	rcall	CAD_CONIN

	tcbe	27, CAD_EXIT
	tcbe	'A', CAD_SET_IMAGE
	tcbe	'B', CAD_SET_IMAGE
	tcbe	'C', CAD_SET_IMAGE
	tcbe	'D', CAD_SET_IMAGE
	tcbe	'S', CAD_INIT_SD
	tcbe	'I', CAD_SET_IOBYTE
	tcbe	'U', CAD_SET_DEBUG
	tcbe	'E', CAD_SET_EEPROM
	tcbe	'H', CAD_SET_HW
	tcbe	'R', CAD_SET_RTC
	tcbe	'V', CAD_VRAM
	tcbe	'Z', CAD_HALT

	call	SYSTEM_BEEP
	rjmp	CAD_COMMAND

CAD_EXIT:
;	lds	temp, DBG_DATA		; load codepage
;	nportout cpd_vstat, temp	; restore video mode
	
	rcall	CAD_RSTSCR

;	pop	temp
CAD_EXIT_NO_CRT:
;        push	temp			; START enters here with temp=0x61

	ldi	temp, BIOS_FUNC_CRT_RESET
	call	BIOS			; restore video mode and reset BIOS
;	call	BIOS_SETCPDCURSOR

CAD_EXIT_NO_CRT_2:

        ; restoring registers
	ldiw	Z, HW_DATA		; pointer in HWDATA
	ld	zzA, Z+
	ld	zzF, Z+
	ld	zzB, Z+
	ld	zzC, Z+
	ld	zzD, Z+
	ld	zzE, Z+
	ld	zzH, Z+
	ld	zzL, Z+
	ld	zzIXl, Z+
	ld	zzIXh, Z+
	ld	zzIYl, Z+
	ld	zzIYh, Z+
	ld	zzSPl, Z+
	ld	zzSPh, Z+
	ld	zzPCl, Z+
	ld	zzPCh, Z+
	
;	ldiw	X, 8			; pointer in RAM
;	ldiw	Z, HW_DATA		; pointer in HWDATA
;_cad_restore_loop:
;	ld	temp, Z+
;	st	X+, temp
;	cpi	XL, 32-6		; till r25
;	brlo	_cad_restore_loop
;	ld	YH, Z+			; restore YH:YL
;	ld	YL, Z+

CAD_EXIT_NO_CRT_3:
	; refill hw_data with zeros!
	ldiw	Z, HW_DATA		; pointer in HW_DATA
	ldi	temp, 32
_cad_restore_hw_loop:
	st	Z+, zero
	dec	temp
	brne	_cad_restore_hw_loop

;	pop	temp
;	pop	zzA
;	pop	r19
;	popw	Z
;	popw	Y
;	popw	X

	nportout cpd_kchar, zero	; clear keyboard buffer
	sts	CON_ESC, zero

	ret




; ------------------------------------------------------------------------------------------
; HALT current program
CAD_HALT:
	ldi	temp, 0x02		; after -2 it will jump to the 0000 address
	sts	HW_DATA+14, temp
	sts	HW_DATA+15, zero
;	sts	CURSOR_STATUS, zero	; show cursor
	call	SYSTEM_BEEP
	rjmp	CAD_MAIN




; ------------------------------------------------------------------------------------------
; Echo SVRAM to screen
CAD_VRAM:
	rcall	CAD_CLRSCR
	STR_GOTOXY 1,1
	ldiw	Z, VIDEOBUF
CAD_VRAM_L1:
	ld	r19, Z+
	rcall	CAD_PUTC
	cpi	ZL, low(VIDEOBUF+24*80)
	brne	CAD_VRAM_L1
	cpi	ZH, high(VIDEOBUF+24*80)
	brne	CAD_VRAM_L1
	rcall	CAD_CONIN
	rjmp	CAD_MAIN



; ------------------------------------------------------------------------------------------
; Init SD card - no responce
CAD_INIT_SD:
	call	SD_INIT
	call	SYSTEM_BEEP
	rjmp	CAD_MAIN



; ------------------------------------------------------------------------------------------
; select image for drive
CAD_SET_IMAGE:
;	push	zzA
	mov	zzA, temp
	subi	zzA, 'A'		; zzA = drive to change 0..

	rcall	CAD_CLRSCR
	m_puts CAD_MSG_WC

	; output disk content
	m_puts CAD_MSG_SD
	sts	SD_ADDRESS, zero
	ldi	temp, 0x08
	sts	SD_ADDRESS+1, temp
	sts	SD_ADDRESS+2, zero
	sts	SD_ADDRESS+3, zero
	call	SD_READ_DO		; load SD card name

	ldiw	Z, SD_BUF
	rcall	CAD_PUTS_RAM

	STR_GOTOXY 1,5

	ldi	r19, 0x01
CAD_SD_IMG_L1:
	pushw	Y			; store cursor position

	push	r19
	subi	r19,-('A'-1)
	rcall	CAD_PUTC		; show index
	adiw	Y, 1
	ldi	r19,'['
	rcall	CAD_PUTC		; show selected
	adiw	Y, 1
	ldi	r19,']'
	rcall	CAD_PUTC		; show selected
	adiw	Y, 1
	pop	r19

	sts	SD_ADDRESS, r19
	ldi	temp, 0x08
	sts	SD_ADDRESS+1, temp
	sts	SD_ADDRESS+2, zero
	sts	SD_ADDRESS+3, zero
	call	SD_READ_DO		; load SD card name

	ldiw	Z, SD_BUF
	rcall	CAD_PUTS_RAM

	popw	Y
	adiw	Y, 40			; position for next name

	inc	r19
	cpi	r19, 31
	brlo	CAD_SD_IMG_L1		; loop

CAD_SD_IMG_MARK_SELECTED:	
	ldiw	Z, SD_FDD_BASE
	add	ZL, zzA
	adc	ZH, zero
	ld	temp, Z			; current image index
	push	r18
	push	r19
	STR_GOTOXY 4,5
	ldi	r18, 0x01		; index starts from 1
CAD_SD_IMG_L7:
	cp	r18, temp
	ldi	r19, ' '
	brne	CAD_SD_IMG_L6
	ldi	r19, '*'
CAD_SD_IMG_L6:
	rcall	CAD_PUTC		; show selected
	adiw	Y, 39
	inc	r18
	cpi	r18, 31
	brlo	CAD_SD_IMG_L7		; loop
	pop	r19
	pop	r18

	m_puts CAD_MSG_SS		; echo select option
        mov	r19, zzA
        subi	r19, -'A'
	rcall	CAD_PUTC		; show drive letter
	m_puts_c CAD_MSG_SE		; echo select option

CAD_SD_IMG_L2:
	rcall	CAD_CONIN
	tcbe	27, CAD_SD_IMG_END
	cpi	temp, 'A'
	brlo	CAD_SD_IMG_L3
	cpi	temp, 'A'+32
	brsh	CAD_SD_IMG_L3

	ldiw	Z, SD_FDD_BASE
	add	ZL, zzA
	adc	ZH, zero		; this data block is alined just for the case
	subi	temp, 'A'-1		; index starts s 0x01
	st	Z, temp			; store image index

	rjmp	CAD_SD_IMG_MARK_SELECTED

CAD_SD_IMG_L3:
	call	SYSTEM_BEEP
	rjmp	CAD_SD_IMG_L2

CAD_SD_IMG_END:
	call	SD_LAST_RESET
;	sts	SD_LASTADDRESS+3, FF
;	sts	SD_LASTADDRESS+2, FF
;	sts	SD_LASTADDRESS+1, FF
;	sts	SD_LASTADDRESS, FF

;	pop	zzA
	rjmp	CAD_MAIN




; ------------------------------------------------------------------------------------------
; set HW platform compatability 
CAD_SET_HW:
	rcall	CAD_CLRSCR
	m_puts 	CAD_MSG_WC
	m_puts 	CAD_MSG_H1

CAD_SET_HW_LOOKUP_START:
	ldiw2	Z, HW_OPTIONS
	ldi	temp, 0
	STR_GOTOXY 1,5

CAD_SET_HW_LOOKUP:			; out as 0 = [ ] Name
	elpm	r19, Z
	cpi	r19, 0
	breq	CAD_SET_HW_CMD		; no more options

	pushw	Y
	ldi	r19, '0'
	add	r19, temp
	rcall	CAD_PUTC		; show hw index
;	inc	YL			; space
;	ldi	r19,'='
;	rcall	CAD_PUTC		; =
	inc	YL			; space
	ldi	r19,'['
	rcall	CAD_PUTC		; =

	lds	r19, HW_FLAG
	cp	r19, temp
	ldi	r19, '*'
	breq	_cad_hw_l0		; = active option??
	ldi	r19, ' '		; no, no mark

_cad_hw_l0:
	rcall	CAD_PUTC		; mark

	ldi	r19,']'
	rcall	CAD_PUTC		; =
	adiw	Y, 1			; space

	ldi	zzA, 16
_cad_hw_putname:
	elpm	r19, Z+
	rcall	CAD_PUTC		; =
	dec	zzA
	brne	_cad_hw_putname

;	ldi	r19,' '
;	rcall	CAD_PUTC		; =
	adiw	Y, 4			; space

	ldi	zzA, 8
_cad_hw_putpar:
	elpm	r19, Z+
	rcall	CAD_PUTHEX		; 
;	ldi	r19,' '
;	rcall	CAD_PUTC		; 
	adiw	Y, 1			; space
	dec	zzA
	brne	_cad_hw_putpar

	popw	Y
	adiw	Y, 40
	adiw	Y, 40
;	adiw	Y, 40 + (40-16-4-4-4-8*3)
;	adiw	Y, 40-16-4-4-4-8*3	; position for next name

;	adiw	Z, 8			; skip parameters
;					;!!!! add display of parameters !!!!

	inc	temp
	rjmp	CAD_SET_HW_LOOKUP

;	mov	r19, zzA
;	rcall	CAD_PUTHEX		; 

CAD_SET_HW_CMD:
	ldi	zzA, '0'
	add	zzA, temp		; last index available

CAD_SET_HW_CMD_LOOP:
	m_puts 	CAD_MSG_DM
	
	rcall	CAD_CONIN
	cpi	temp, 27
	breq	CAD_SET_HW_END
	cpi	temp, '0'
	brlo	CAD_SET_HW_CMD_LOOP
	cp	temp, zzA
	brsh	CAD_SET_HW_CMD_LOOP

	subi	temp, '0'
	sts	HW_FLAG, temp		; save hw_flag
	ldiw2	Z, HW_OPTIONS+8		; params for hw_index == 0
	cpi	temp, 0
	breq	CAD_SET_HW_SET_L0
CAD_SET_HW_SET_L1:
	adiw	Z, 16+8
	dec	temp
	brne	CAD_SET_HW_SET_L1
CAD_SET_HW_SET_L0:	         	; Z->parameters
	elpm	temp, Z+
	sts	CRT_LINES, temp		; codepage after restore
	elpm	temp, Z+
	sts	CRT_CHARS, temp		; codepage after restore
	elpm	temp, Z+
	sts	CRT_SETTINGS, temp	; codepage after restore
					;!!!! add other parameters!!!!
;	sts	CON_ESC_C4, zero
;	sts	CON_ESC_C5, zero

;	call	SYSTEM_BEEP
	rjmp	CAD_SET_HW_LOOKUP_START

CAD_SET_HW_END:
	rjmp	CAD_MAIN



; ------------------------------------------------------------------------------------------
; set CRISS IOBYTE
CAD_SET_IOBYTE:
	rcall	CAD_CLRSCR
	m_puts CAD_MSG_WC

	m_puts_block CAD_MSG_I0, 9
	
CAD_SET_IOBYTE_L2:

	STR_GOTOXY 14,4			; out IOBYTE value
	ldiw	Z, CON_IOBYTE
	rcall	CAD_PUT_IOBYTE

	STR_GOTOXY 14,8			; out IOBYTE value
	ldiw	Z, PR_IOBYTE
	rcall	CAD_PUT_IOBYTE

	STR_GOTOXY 14,12		; out IOBYTE value
	ldiw	Z, DEV_IOBYTE
	rcall	CAD_PUT_IOBYTE

	m_puts CAD_MSG_IM
	
	rcall	CAD_CONIN
	tcbe	27, CAD_SET_IOBYTE_END
	cpi	temp, 'A'
	brlo	CAD_SET_IOBYTE_L3
	cpi	temp, 'H'+1
	brlo	CAD_SET_IOBYTE_L6	; con_io
	cpi	temp, 'P'+1
	brlo	CAD_SET_IOBYTE_L7	; pr_io
	cpi	temp, 'X'+1
	brlo	CAD_SET_IOBYTE_L9	; LST_IO
;	cpi	temp, 'X'+1
;	brlo	CAD_SET_IOBYTE_LA	; SD_IO
	rjmp	CAD_SET_IOBYTE_L3

CAD_SET_IOBYTE_L9:
	subi	temp, 'Q'		; A = 0..7		
	ldiw	Z, DEV_IOBYTE
	rjmp	CAD_SET_IOBYTE_L8
	
;CAD_SET_IOBYTE_LA:
;	subi	temp, 'U'		; A = 0..7		
;	ldiw	Z, SD_IOBYTE
;	rjmp	CAD_SET_IOBYTE_L8	

CAD_SET_IOBYTE_L7:
	subi	temp, 'I'		; A = 0..7		
	ldiw	Z, PR_IOBYTE
	rjmp	CAD_SET_IOBYTE_L8

CAD_SET_IOBYTE_L6:
	subi	temp, 'A'		; A = 0..7		
	ldiw	Z, CON_IOBYTE

CAD_SET_IOBYTE_L8:
	ldi	r19,1			; bit to xor
	cpi	temp, 0
	breq	CAD_SET_IOBYTE_L4
CAD_SET_IOBYTE_L5:
	lsl	r19
	dec	temp
	brne	CAD_SET_IOBYTE_L5

CAD_SET_IOBYTE_L4:
	ld	temp, Z
	eor	temp, r19
	st	Z, temp
	rjmp	CAD_SET_IOBYTE_L2	; loop until ESC

CAD_SET_IOBYTE_L3:			; input error
	call	SYSTEM_BEEP
	rjmp	CAD_SET_IOBYTE_L2
CAD_SET_IOBYTE_END:
	lds	temp, CON_IOBYTE
	sts	RTC_IOBYTE, temp
	lds	temp, PR_IOBYTE
	sts	RTC_PR_IOBYTE, temp
	lds	temp, DEV_IOBYTE
	sts	RTC_DEV_IOBYTE, temp
;	lds	temp, SD_IOBYTE
;	sts	RTC_SD_IOBYTE, temp

	ldi	temp, 3			; write ROM command
	call	RTC_CMD			; store PR_IOBYTE

CAD_SET_IOBYTE_END2:
	rjmp	CAD_MAIN


; ------------------------------------------------------------------------------------------
; set CRISS DEBUG 
;	lds	temp, SYS_NOTIFY	

CAD_SET_DEBUG:
	rcall	CAD_CLRSCR
	m_puts CAD_MSG_WC

	m_puts_block CAD_MSG_D1, 18
		
CAD_SET_DBG_L2:

	STR_GOTOXY 4,5			; out current value
	lds	r19, SYS_NOTIFY	
	rcall	CAD_PUT_V_FLAGS

	STR_GOTOXY 38,5			; out current value
	lds	r19, DBG_OPTIONS	
	rcall	CAD_PUT_V_FLAGS

	STR_GOTOXY 57, 11
	lds	r19, DBG_BREAK+1
	rcall	CAD_PUTHEX
	lds	r19, DBG_BREAK
	rcall	CAD_PUTHEX

;	ldi	temp, 1<<0              ; bit to test
;CAD_DBG_0:
;	lds	r19, SYS_NOTIFY	
;	and	r19, temp
;	ldi	r19, ' '
;	breq	CAD_DBG_1
;	ldi	r19, '*'
;CAD_DBG_1:
;	push	temp
;	rcall	CAD_PUTC		; set value mark
;	pop	temp
;	lsl	temp
;	adiw	Y,40			
;	adiw	Y,39			; go to next box
;	cpi	temp, 0
;	brne	CAD_DBG_0

	m_puts CAD_MSG_DM
	rcall	CAD_CONIN

	tcbe	27, CAD_SET_DBG_END
	cpi	temp, 'A'
	brlo	CAD_SET_DBG_L3
	cpi	temp, 'A'+8
	brlo	CAD_SET_DBG_B1
	cpi	temp, 'I'+16
	brlo	CAD_SET_DBG_B2
	cpi	temp, 'Q'
	breq	CAD_SET_DBG_B3

;	rjmp	CAD_SET_DBG_L3
CAD_SET_DBG_L3:				; input error
	call	SYSTEM_BEEP
	rjmp	CAD_SET_DBG_L2

CAD_SET_DBG_B1:
	subi	temp, 'A'		; A = 0..7		
	ldiw	Z, SYS_NOTIFY
CAD_SET_DBG_B1_L1:
	rcall	CAD_SET_FLAG
	rjmp	CAD_SET_DBG_L2		; loop until ESC

CAD_SET_DBG_B2:
	subi	temp, 'I'		; A = 0..7		
	ldiw	Z, DBG_OPTIONS
	rjmp	CAD_SET_DBG_B1_L1

CAD_SET_DBG_B3:
	STR_GOTOXY 57, 11
	rcall	CAD_READ_HEX2
	sts	DBG_BREAK+1, temp
	rcall	CAD_READ_HEX2
	sts	DBG_BREAK, temp
	rjmp	CAD_SET_DBG_L2		; loop until ESC

;	ldi	r19,1			; bit to xor
;	subi	temp, 'A'		; A = 0..7		
;	breq	CAD_SET_DBG_L4
;CAD_SET_DBG_L5:
;	lsl	r19
;	dec	temp
;	brne	CAD_SET_DBG_L5

;CAD_SET_DBG_L4:
;	lds	temp, SYS_NOTIFY	
;	eor	temp, r19
;	sts	SYS_NOTIFY, temp
;	rjmp	CAD_SET_DBG_L2		; loop until ESC

;CAD_SET_DBG_L3:				; input error
;	call	SYSTEM_BEEP
;	rjmp	CAD_SET_DBG_L2
CAD_SET_DBG_END:
	lds	temp, SYS_NOTIFY
	sbrs	temp, NOTIFY_Z80
	rjmp	CAD_SET_DBG_NO_Z80

	ldi	temp, high(IRQOPCODES)	; next command will execute IRQ handler
	out	GPIOR2, temp		; GPIOR2 contains high pointer to decode table
	in	temp, GPIOR0		; GPIOR0 = int requests for CPU
	sbr	temp, (1<<IRQ_V_DEBUG)
	out	GPIOR0, temp		; SET irq flag

	rjmp	CAD_MAIN

CAD_SET_DBG_NO_Z80:
	ldi	temp, high(zOPCODE__LBLS_L)
	out	GPIOR2, temp		; GPIOR2 contains high pointer to decode table
	in	temp, GPIOR0		; GPIOR0 = int requests for CPU
	cbr	temp, (1<<IRQ_V_DEBUG)
	out	GPIOR0, temp		; clear IRQ flag
	rjmp	CAD_MAIN
		


CAD_PUT_V_FLAGS:
	ldi	temp, 1<<0              ; bit to test
CAD_DBG_0:
;	lds	r19, SYS_NOTIFY	
	push	r19
	and	r19, temp
	ldi	r19, ' '
	breq	CAD_DBG_1
	ldi	r19, '*'
CAD_DBG_1:
	push	temp
	rcall	CAD_PUTC		; set value mark
	pop	temp
	pop	r19
	lsl	temp
	adiw	Y,40			
	adiw	Y,39			; go to next box
	cpi	temp, 0
	brne	CAD_DBG_0
	ret


; set flags, Z->var, r19=flag
CAD_SET_FLAG:
	ldi	r19,1			; bit to xor
	cpi	temp, 0
;	subi	temp, 'A'		; A = 0..7		
	breq	CAD_SET_DBG_L4
CAD_SET_DBG_L5:
	lsl	r19
	dec	temp
	brne	CAD_SET_DBG_L5

CAD_SET_DBG_L4:
	ld	temp, Z	
	eor	temp, r19
	st	Z, temp
	ret
;	rjmp	CAD_SET_DBG_L2		; loop until ESC



; ------------------------------------------------------------------------------------------
; set CRISS EEPROM 
;	lds	temp, SYS_NOTIFY	
CAD_SET_EEPROM:
;        pushw	Z
	rcall	CAD_CLRSCR
	m_puts CAD_MSG_WC

	m_puts_BLOCK CAD_MSG_R1, 10

;	m_puts CAD_MSG_R1		; screen messages
;	m_puts CAD_MSG_R2
;	m_puts CAD_MSG_R3
;	m_puts CAD_MSG_R4
;	m_puts CAD_MSG_R5
;	m_puts CAD_MSG_R6
;	m_puts CAD_MSG_R7
;	m_puts CAD_MSG_R8
;	m_puts CAD_MSG_R9
;	m_puts CAD_MSG_RM

CAD_SET_EEPROM_CMD:
	rcall	CAD_CONIN
	tcbe	27, CAD_SET_EEPROM_END
	tcbe	'A', CAD_SET_EEPROM_A
	tcbe	'B', CAD_SET_EEPROM_B
	tcbe	'C', CAD_SET_EEPROM_C
	tcbe	'D', CAD_SET_EEPROM_D
	tcbe	'E', CAD_SET_EEPROM_E
	tcbe	'F', CAD_SET_EEPROM_F
	tcbe	'G', CAD_SET_EEPROM_G
	tcbe	'H', CAD_SET_EEPROM_H

	rjmp	CAD_SET_EEPROM_CMD

CAD_SET_EEPROM_DONE:
	call	SYSTEM_BEEP
	call	SD_LAST_RESET
;	sts	SD_LASTADDRESS+3, FF
;	sts	SD_LASTADDRESS+2, FF
;	sts	SD_LASTADDRESS+1, FF
;	sts	SD_LASTADDRESS+0, FF		; clear last_access - sdbuf was used
	rjmp	CAD_SET_EEPROM;_CMD

CAD_SET_EEPROM_END:
;	popw	Z
	rjmp	CAD_MAIN



CAD_SET_EEPROM_A:
	ldi	zzA, 0
	rjmp	CAD_SET_EEPROM_RAM_ROM
CAD_SET_EEPROM_D:
	ldi	zzA, 1
	rjmp	CAD_SET_EEPROM_RAM_ROM

CAD_SET_EEPROM_B:
	ldi	zzA, 0
	rjmp	CAD_SET_EEPROM_ROM_RAM
CAD_SET_EEPROM_E:
	ldi	zzA, 1
	rjmp	CAD_SET_EEPROM_ROM_RAM

CAD_SET_EEPROM_C:
	ldi	zzA, 0
	rjmp	CAD_SET_EEPROM_SWAP
CAD_SET_EEPROM_F:
	ldi	zzA, 1
	rjmp	CAD_SET_EEPROM_SWAP


; swap ROM and RAM
CAD_SET_EEPROM_SWAP:
	rcall	CAD_SET_EEPROM_SWAP_PROC
	rjmp	CAD_SET_EEPROM_DONE

CAD_SET_EEPROM_SWAP_PROC:
	ldiw	Z, 0
_cadr2e_l9:
	rcall	CAD_SET_EEPROM_READ_RAM_BUF
	rcall	CAD_SET_EEPROM_READ_BUF
	rcall	CAD_SET_EEPROM_WRITE_RAM_BUF
	rcall	CAD_SET_EEPROM_WRITE_BUF
	inc	ZH
	brne	_cadr2e_l9

	rcall	CAD_SET_EEPROM_STORE_REGS
	ldi	ZH, 0xff
	rcall	CAD_SET_EEPROM_WRITE_BUF; rewrite last block

	ldiw	X, SD_BUF+512
	rcall	CAD_SET_EEPROM_RESTORE_REGS

;	rjmp	CAD_SET_EEPROM_DONE
	ret


; read ROM to RAM
CAD_SET_EEPROM_ROM_RAM:
	rcall	CAD_SET_EEPROM_ROM_RAM_PROC
	rjmp	CAD_SET_EEPROM_DONE

CAD_SET_EEPROM_ROM_RAM_PROC:		; to be able to use from START routine
	ldiw	Z, 0
_cadr2e_l7:
	rcall	CAD_SET_EEPROM_READ_BUF
	rcall	CAD_SET_EEPROM_WRITE_RAM_BUF
	inc	ZH
	brne	_cadr2e_l7

	rcall	CAD_SET_EEPROM_RESTORE_REGS
;	ldi	ZH, 0xff
;	rcall	CAD_SET_EEPROM_WRITE_BUF; rewrite last block

;        pop	zzA
;	rjmp	CAD_SET_EEPROM_DONE
	ret


CAD_SET_EEPROM_RAM_ROM:
	rcall	CAD_SET_EEPROM_RAM_ROM_PROC
	rjmp	CAD_SET_EEPROM_DONE

CAD_SET_EEPROM_RAM_ROM_PROC:
;        push	zzA
;        mov	zzA, temp
	ldiw	Z, 0
_cadr2e_l2:
	rcall	CAD_SET_EEPROM_READ_RAM_BUF
	rcall	CAD_SET_EEPROM_WRITE_BUF
	inc	ZH
	brne	_cadr2e_l2

	rcall	CAD_SET_EEPROM_STORE_REGS
	ldi	ZH, 0xff
	rcall	CAD_SET_EEPROM_WRITE_BUF; rewrite last block

;        pop	zzA
;	rjmp	CAD_SET_EEPROM_DONE
	ret

CAD_SET_EEPROM_STORE_REGS:
	ldir	HW_DATA, -X, 16		; reg z-registers
	ldir	0x0900, -X, 14		; ram z-registers
	ldir	CRT_SETTINGS, -X, 10	; crt settings
	ldir	SHARABLE, -X, 2		; hw and iobyte
	ret


CAD_SET_EEPROM_RESTORE_REGS:
	sdir	HW_DATA, -X, 16		; reg z-registers
	sdir	0x0900, -X, 14		; ram z-registers
	sdir	CRT_SETTINGS, -X, 10	; crt settings
	sdir	SHARABLE, -X, 2		; hw and iobyte
	ret


CAD_SET_EEPROM_WAIT_WIP:
	SPI_SELECT
	iSPI	0b00000101		; RDSR
	iSPI	0xff
	SPI_DESELECT
	sbrc	temp, 0			; check Write-In-Process (WIP)
	rjmp	CAD_SET_EEPROM_WAIT_WIP
	ret

; write 256 bytes from SDBUF to zzA:ZH:00
CAD_SET_EEPROM_WRITE_BUF:
	SPI_INIT SPI_SLAVE_ROM, SPI_FCK_DIV_4

	rcall	CAD_SET_EEPROM_WAIT_WIP
;CAD_SET_EEPROM_WRITE_BUF_L0:
;	SPI_SELECT
;	iSPI	0b00000101		; RDSR
;	iSPI	0xff
;	SPI_DESELECT
;	sbrc	temp, 0			; check Write-In-Process (WIP)
;	rjmp	CAD_SET_EEPROM_WRITE_BUF_L0

	SPI_SELECT
	iSPI	0b00000110		; WREN
	SPI_DESELECT

	ldiw	X, SD_BUF		; buffer
	SPI_SELECT
	iSPI	0b00000010		; WRITE
	rSPI	zzA
	rSPI	ZH
	rSPI	ZL
_cadr2e_l1:
	ld	temp, X+
	call	DOSPI
	inc	ZL
	brne	_cadr2e_l1
;	SPI_DESELECT
    	SPI_STOP		    	; stop access
	ret


; write 256 bytes from SDBUF to zzA:ZH:00
CAD_SET_EEPROM_READ_BUF:
	SPI_INIT SPI_SLAVE_ROM, SPI_FCK_DIV_4

	rcall	CAD_SET_EEPROM_WAIT_WIP
	
	ldiw	X, SD_BUF+256		; buffer 2nd half
	SPI_SELECT
	iSPI	0b00000011		; READ
	rSPI	zzA
	rSPI	ZH
	rSPI	ZL
_cadr2e_l4:
	call	DOSPI
	st	X+, temp
	inc	ZL
	brne	_cadr2e_l4
;	SPI_DESELECT
    	SPI_STOP		    	; stop access
	ret


; read 256 bytes from RAM ZH:00
CAD_SET_EEPROM_READ_RAM_BUF:
	ldiw	X, SD_BUF		; read RAM to buffer
_cadr2e_l0:
	LDRAM	ZH, ZL, temp
	st	X+, temp
	inc	ZL
	brne	_cadr2e_l0
	ret


; save 256 bytes from RAM ZH:00
CAD_SET_EEPROM_WRITE_RAM_BUF:
	ldiw	X, SD_BUF+256		; read RAM to buffer
_cadr2e_l6:
	ld	temp, X+
	STRAM	ZH, ZL, temp
	inc	ZL
	brne	_cadr2e_l6
	ret


; clear EEPROM 64k bank
CAD_SET_EEPROM_G:
	ldi	zzA, 0
	rjmp	CAD_SET_EEPROM_CLR64
CAD_SET_EEPROM_H:
	ldi	zzA, 1
CAD_SET_EEPROM_CLR64:
;	push	zzA
;	mov	zzA, temp
	SPI_INIT SPI_SLAVE_ROM, SPI_FCK_DIV_4

	ldiw	Z, 0
_cadeec_l0:
	SPI_SELECT
	iSPI	0b00000110		; WREN
	SPI_DESELECT

	SPI_SELECT
	iSPI	0b00000010		; PAGE WRITE SEQUENCE
	rSPI	zzA
	rSPI	ZH
	rSPI	ZL
_cadeec_l1:
	iSPI	0
	adiw	Z, 1
	cpi	ZL, 0
	brne	_cadeec_l1
	SPI_DESELECT
	cpi	ZH, 0
	brne	_cadeec_l0

    	SPI_STOP		    	; stop access
;	pop	zzA
	rjmp	CAD_SET_EEPROM_DONE




.MACRO	CAD_PUT_MAC6
	STR_GOTOXY 12, @0
	ldiw	Z, @1
	call	CAD_PUT_MAC
.ENDM

.MACRO	CAD_PUT_IP4
	STR_GOTOXY 12, @0
	ldiw	Z, @1
	call	CAD_PUT_IP
.ENDM

.MACRO	CAD_PUT_BCD2
	lds	r19, @0
	rcall	CAD_PUTHEX
	adiw	Y, 1
;	rcall	CAD_PUTBCD
.ENDM

.MACRO	CAD_PUT_PORT5
        adiw	Y, 2
	ldiw	Z, @0
	call	CAD_PUT_PORT
.ENDM

; ------------------------------------------------------------------------------------------
; set CRISS RTC
CAD_SET_RTC:
;        pushw	Z
	rcall	CAD_CLRSCR
	m_puts CAD_MSG_WC

	m_puts_block CAD_MSG_C1, 2

	lds	temp, HW_FOUND
	sbrs	temp, HW_FOUND_LAN	; check that LAN found
	rjmp	_cad_set_rtc_l5	
	
;	m_puts_block CAD_MSG_C3, 14	; LAN settings
	m_puts_block CAD_MSG_C3, 10	; LAN settings

_cad_set_rtc_l5:

	m_puts_block CAD_MSG_C12, 13	; hw disable

	m_puts_block CAD_MSG_C27, 17	; irq vestors

CAD_SET_RTC_CMD:
	ldi	temp, 0
	call	RTC_CMD			; reload date and time
	ldi	temp, 7
	call	RTC_CMD			; reload ROM

	STR_GOTOXY 12, 5
	CAD_PUT_BCD2 RTC_HOURS
	CAD_PUT_BCD2 RTC_MINS
	CAD_PUT_BCD2 RTC_SECS
	
	STR_GOTOXY 12, 6
	CAD_PUT_BCD2 RTC_DATE
	CAD_PUT_BCD2 RTC_MONTH
	CAD_PUT_BCD2 RTC_YEAR
	adiw	Y, 2
	CAD_PUT_BCD2 RTC_DAY

	lds	temp, HW_FOUND
	sbrs	temp, HW_FOUND_LAN	; check that LAN found
	rjmp	_cad_set_rtc_l7	

	CAD_PUT_MAC6 8, RTC_LAN_MY_MAC
	CAD_PUT_IP4 9,  RTC_LAN_MY_IP
;	CAD_PUT_IP4 10, RTC_LAN_GATE
;	CAD_PUT_IP4 11, RTC_LAN_MASK

	CAD_PUT_MAC6 13, RTC_SRV_MAC
	CAD_PUT_IP4 14,  RTC_SRV_IP
	CAD_PUT_PORT5    RTC_SRV_PORT

	STR_GOTOXY 28,15
	CAD_PUT_PORT5    RTC_PRN_PORT
	STR_GOTOXY 28,16
	CAD_PUT_PORT5    RTC_SDC_PORT

	CAD_PUT_MAC6 18, RTC_PNC_MAC
	CAD_PUT_IP4 19,  RTC_PNC_IP
	CAD_PUT_PORT5    RTC_PNC_PORT

;	CAD_PUT_MAC6 21, RTC_TMS_MAC
;	CAD_PUT_IP4 22,  RTC_TMS_IP
;	CAD_PUT_PORT5    RTC_TMS_PORT

_cad_set_rtc_l7:

	STR_GOTOXY RSC2Y+11, 17
	lds	r19, RTC_MODBUS_ID
	rcall	CAD_PUTHEX

	STR_GOTOXY RSC2Y+11, 18
	lds	r19, RTC_CAN_ID
	rcall	CAD_PUTHEX

;	STR_GOTOXY 12, 3
;	lds	temp, RTC_AUTO
;	ldi	r19, ' '
;	sbrc	temp, AUTO_CLOCK
;	ldi	r19, '*'
;	rcall	CAD_PUTC

	; HW_DISABLE
	push	r18
	ldi	r18, 8				; bits to display
	STR_GOTOXY RSC2Y+3, 5
	lds	temp, RTC_HW_DISABLE
_cad_set_rtc_l1:
	ldi	r19, ' '
	sbrc	temp, 0		
	ldi	r19, '*'
	rcall	CAD_PUTC
	adiw	Y, 40
	adiw	Y, 39				; next line
	lsr	temp
	dec 	r18
	brne	_cad_set_rtc_l1
	pop	r18

	STR_GOTOXY RSC2Y+15, 14
	ldiw	Z, RTC_SEC_PIN
	call	CAD_PUT_PORT	

	STR_GOTOXY RSC2Y+15, 15
	ldiw	Z, RTC_CAD_PIN
	call	CAD_PUT_PORT	

	STR_GOTOXY RSC3Y+10, 5 			; write IRQ vectors
	ldi	temp, 16
	ldiw	Z, RTC_IRQ_BASE
_cad_set_rtc_l6:
	ld	r19, Z+
	call	CAD_PUTHEX
	adiw	Y, 40
	adiw	Y, 40-2
	dec	temp
	brne	_cad_set_rtc_l6

	m_puts CAD_MSG_RM
	rcall	CAD_CONIN

	tcbe	27, CAD_SET_RTC_END
	tcbe	'A', CAD_SET_RTC_A
	tcbe	'B', CAD_SET_RTC_B
	tcbe	'C', CAD_SET_RTC_C
	tcbe	'D', CAD_SET_RTC_D
;	tcbe	'E', CAD_SET_RTC_E
;	tcbe	'F', CAD_SET_RTC_F
	tcbe	'G', CAD_SET_RTC_G
	tcbe	'H', CAD_SET_RTC_H
	tcbe	'I', CAD_SET_RTC_I
	tcbe	'J', CAD_SET_RTC_J
	tcbe	'K', CAD_SET_RTC_K
	tcbe	'L', CAD_SET_RTC_L
;	tcbe	'W', CAD_SET_RTC_W
;	tcbe	'X', CAD_SET_RTC_X
	tcbe	'U', CAD_SET_RTC_PWD
	tcbe	'Y', CAD_SET_RTC_CAD_PWD
;	tcbe	'V', CAD_SET_RTC_AUTOCLOCK
	tcbe	'P'-0x40, CAD_SET_RTC_CP
	tcbe	'S'-0x40, CAD_SET_RTC_CS

	cpi	temp, 17
	brlo	CAD_SET_RTC_IRQ

	cpi	temp, 'U'
	brsh	_cad_set_rtc_l4
	cpi	temp, 'M'
	brlo	_cad_set_rtc_l4

	ldi	r19, 1
	subi	temp, 'M'
	breq	_cad_set_rtc_l2
_cad_set_rtc_l3:
	lsl	r19
	dec	temp
	brne	_cad_set_rtc_l3
_cad_set_rtc_l2:
	lds	temp, RTC_HW_DISABLE
	eor	temp, r19
	sts	RTC_HW_DISABLE, temp
	rjmp	CAD_SET_RTC_DONE3	; store RAM

_cad_set_rtc_l4:
	rjmp	CAD_SET_RTC_CMD

CAD_SET_RTC_DONE3:
	ldi	temp, 3
CAD_SET_RTC_DONE:
	call	RTC_CMD			; update time
	rjmp	CAD_SET_RTC_CMD

CAD_SET_RTC_END:
	rjmp	CAD_MAIN



CAD_SET_RTC_IRQ:
	STR_GOTOXY RSC3Y+10, 5 			; write IRQ vectors
	ldiw	Z, RTC_IRQ_BASE
	dec	temp
	breq	_cad_set_rtc_irq_l1
_cad_set_rtc_irq_l5:
	adiw	Z, 1
	adiw	Y, 40
	adiw	Y, 40
	dec	temp
	brne	_cad_set_rtc_irq_l5
_cad_set_rtc_irq_l1:
	call	CAD_READ_HEX2
	st	Z, temp
	rjmp	CAD_SET_RTC_DONE3
	


;CAD_SET_RTC_AUTOCLOCK:
;	lds	temp, RTC_AUTO
;	ldi	r19, 1
;	eor	temp, r19
;	sts	RTC_AUTO, temp
;	rjmp	CAD_SET_RTC_DONE3
	

; set time
CAD_SET_RTC_A:
	STR_GOTOXY 12, 5
	rcall	CAD_READ_DEC2_BCD
	sts	RTC_HOURS, temp
	adiw	Y, 1
	rcall	CAD_READ_DEC2_BCD
	sts	RTC_MINS, temp
	adiw	Y, 1
	rcall	CAD_READ_DEC2_BCD
	sts	RTC_SECS, temp
	ldi	temp, 1
	rjmp	CAD_SET_RTC_DONE


; set date
CAD_SET_RTC_B:
	STR_GOTOXY 12, 6
	rcall	CAD_READ_DEC2_BCD
	sts	RTC_DATE, temp
	adiw	Y, 1
	rcall	CAD_READ_DEC2_BCD
	sts	RTC_MONTH, temp
	adiw	Y, 1
	rcall	CAD_READ_DEC2_BCD
	sts	RTC_YEAR, temp
	adiw	Y, 3
	rcall	CAD_READ_DEC2_BCD
	sts	RTC_DAY, temp
	ldi	temp, 2
	rjmp	CAD_SET_RTC_DONE


; set MAC
CAD_SET_RTC_C:
	STR_GOTOXY 12, 8
	ldiw	Z, RTC_LAN_MY_MAC
	rcall	CAD_READ_MAC
	rjmp	CAD_SET_RTC_DONE3


; set MAC
CAD_SET_RTC_D:
	STR_GOTOXY 12, 9
	ldiw	Z, RTC_LAN_MY_IP
	rcall	CAD_READ_IP
	rjmp	CAD_SET_RTC_DONE3


; set Gate
;CAD_SET_RTC_E:
;	STR_GOTOXY 12, 10
;	ldiw	Z, RTC_LAN_GATE
;	rcall	CAD_READ_IP
;	rjmp	CAD_SET_RTC_DONE3


; set Mask
;CAD_SET_RTC_F:
;	STR_GOTOXY 12, 11
;	ldiw	Z, RTC_LAN_MASK
;	rcall	CAD_READ_IP
;	rjmp	CAD_SET_RTC_DONE3


CAD_SET_RTC_G:
	STR_GOTOXY 12, 13
	ldiw	Z, RTC_SRV_MAC
	rcall	CAD_READ_MAC
	rjmp	CAD_SET_RTC_DONE3

; set IP
CAD_SET_RTC_H:
	STR_GOTOXY 12, 14
	ldiw	Z, RTC_SRV_IP
	rcall	CAD_READ_IP
	adiw	Y, 2
	ldiw	Z, RTC_SRV_PORT
	rcall	CAD_READ_PORT
	rjmp	CAD_SET_RTC_DONE3

; PRN port	
CAD_SET_RTC_CP:
	STR_GOTOXY 30, 15
	ldiw	Z, RTC_PRN_PORT
	rcall	CAD_READ_PORT
	rjmp	CAD_SET_RTC_DONE3

; SDC port
CAD_SET_RTC_CS:
	STR_GOTOXY 30, 16
	ldiw	Z, RTC_SDC_PORT
	rcall	CAD_READ_PORT
	rjmp	CAD_SET_RTC_DONE3

; set P-MAC
CAD_SET_RTC_I:
	STR_GOTOXY 12, 18
	ldiw	Z, RTC_PNC_MAC
	rcall	CAD_READ_MAC
	rjmp	CAD_SET_RTC_DONE3


; set P-IP
CAD_SET_RTC_J:
	STR_GOTOXY 12, 19
	ldiw	Z, RTC_PNC_IP
	rcall	CAD_READ_IP
	adiw	Y, 2
	ldiw	Z, RTC_PNC_PORT
	rcall	CAD_READ_PORT
	rjmp	CAD_SET_RTC_DONE3


;CAD_SET_RTC_W:
;	STR_GOTOXY 12, 21
;	ldiw	Z, RTC_TMS_MAC
;	rcall	CAD_READ_MAC
;	rjmp	CAD_SET_RTC_DONE3


; set IP
;CAD_SET_RTC_X:
;	STR_GOTOXY 12, 22
;	ldiw	Z, RTC_TMS_IP
;	rcall	CAD_READ_IP
;	adiw	Y, 2
;	ldiw	Z, RTC_TMS_PORT
;	rcall	CAD_READ_PORT
;	rjmp	CAD_SET_RTC_DONE3


CAD_SET_RTC_K:
	STR_GOTOXY RSC2Y+11, 17
	rcall	CAD_READ_HEX2
	sts	RTC_MODBUS_ID, temp
	rjmp	CAD_SET_RTC_DONE3


CAD_SET_RTC_L:
	STR_GOTOXY RSC2Y+11, 18
	rcall	CAD_READ_HEX2
	sts	RTC_CAN_ID, temp
	rjmp	CAD_SET_RTC_DONE3


CAD_SET_RTC_PWD:
	STR_GOTOXY RSC2Y+15, 14
	ldiw	Z, RTC_SEC_PIN
	rcall	CAD_READ_PORT
	rjmp	CAD_SET_RTC_DONE3

CAD_SET_RTC_CAD_PWD:
	STR_GOTOXY RSC2Y+15, 15
	ldiw	Z, RTC_CAD_PIN
	rcall	CAD_READ_PORT
	rjmp	CAD_SET_RTC_DONE3

CAD_PUT_PORT:
        pushw	X
	ld	XL, Z+
	ld	XH, Z			; port number
	ldiw	Z, 10000
	call	CAD_PUT_DEC_WORD
	ldiw	Z, 1000
	call	CAD_PUT_DEC_WORD
	ldiw	Z, 100
	call	CAD_PUT_DEC_WORD
	ldiw	Z, 10
	call	CAD_PUT_DEC_WORD
	mov	r19, XL
	call	_cad_put_dec_w_l0	; out r19+'0'
	popw	X
	ret


; put X/r17:r18
CAD_PUT_DEC_WORD:
	ldi	r19, 0
_cad_put_dec_w_l1:
	cp	XL, ZL
	cpc	XH, ZH
	brlo	_cad_put_dec_w_l0
	inc	r19
	sub	XL, ZL
	sbc	XH, ZH
	rjmp	_cad_put_dec_w_l1
_cad_put_dec_w_l0:
	subi	r19, -'0'
	call	CAD_PUTC
	ret



CAD_PUT_MAC:
        ldi	FROMRAM0, 6
_cad_put_mac_l0:
	ld	r19, Z+
	rcall	CAD_PUTHEX
	adiw	Y, 1
	dec	FROMRAM0
	brne	_cad_put_mac_l0
;	ld	r19, Z+
;	rcall	CAD_PUTHEX
;	adiw	Y, 1
;	ld	r19, Z+
;	rcall	CAD_PUTHEX
;	adiw	Y, 1
;	ld	r19, Z+
;	rcall	CAD_PUTHEX
;	adiw	Y, 1
;	ld	r19, Z+
;	rcall	CAD_PUTHEX
;	adiw	Y, 1
;	ld	r19, Z+
;	rcall	CAD_PUTHEX
	ret


CAD_PUT_IP:
        ldi	FROMRAM0, 4
_cad_put_ip_l0:
	ld	r19, Z+
	rcall	CAD_PUT_DEC3
	adiw	Y, 1
	dec	FROMRAM0
	brne	_cad_put_ip_l0

;	ld	r19, Z+
;	rcall	CAD_PUT_DEC3
;	adiw	Y, 1
;	ld	r19, Z+
;	rcall	CAD_PUT_DEC3
;	adiw	Y, 1
;	ld	r19, Z+
;	rcall	CAD_PUT_DEC3
	ret


CAD_PUT_DEC3:
	mov	temp, r19
	ldi	r19, 0
_cad_put_dec3_l1:
	cpi	temp, 100
	brlo	_cad_put_dec3_l0
	subi	temp, 100
	inc	r19	
	rjmp	_cad_put_dec3_l1
_cad_put_dec3_l0:
	subi	r19, -'0'
	rcall	CAD_PUTC
	ldi	r19, 0
_cad_put_dec3_l3:
	cpi	temp, 10
	brlo	_cad_put_dec3_l2
	subi	temp, 10
	inc	r19	
	rjmp	_cad_put_dec3_l3
_cad_put_dec3_l2:
	subi	r19, -'0'
	rcall	CAD_PUTC
	mov	r19, temp
	subi	r19, -'0'
	rcall	CAD_PUTC
	ret



CAD_READ_PORT:
        push	r0
        push	r1
        push	r18
        pushw	X

_cad_read_port_l1:
;        ldi	FROMRAM0, 6
;_cad_read_port_l4:
        rcall	CAD_READ_DEC1
        push	temp
;	dec	FROMRAM0
;	brne	_cad_read_port_l4
        rcall	CAD_READ_DEC1
        push	temp
        rcall	CAD_READ_DEC1
        push	temp
        rcall	CAD_READ_DEC1
        push	temp
        rcall	CAD_READ_DEC1
; 	pop	temp

        mov	XL, temp
        ldi	XH, 0			; value = r19

        pop	temp			; dozens
	ldi	r18, 10
	mul	temp, r18		; r0:r1 = dozens
	add	XL, r0			; overflow impossible!
	adc	XH, r1

        pop	temp			; dozens
	ldi	r18, 100
	mul	temp, r18		; r0:r1 = hundreds
	add	XL, r0			; overflow impossible!
	adc	XH, r1

        pop	temp			; thousands
	ldi	r18, 250
	mul	temp, r18		; r0:r1 = hundreds
	lsl	r0
	rol	r1
	lsl	r0
	rol	r1			; *4
	add	XL, r0			; overflow impossible!
	adc	XH, r1

        pop	r19			; tens of thousands
	clr	r18
	cpi	r19, 0
	breq	_cad_read_port_l2
_cad_read_port_l3:
	ldi	temp, low(10000)
	add	XL, temp
	ldi	temp, high(10000)
	adc	XH, temp
	adc	r18, zero
	dec	r19
	brne	_cad_read_port_l3

_cad_read_port_l2:
	cp	r18, zero		
	brne	_cad_read_port_l0	; result > maxint?
	st	Z+, XL
	st	Z, XH			; store result
	popw	X
        pop	r18
        pop	r1
        pop	r0
	ret
_cad_read_port_l0:
	call	SYSTEM_BEEP
	sbiw	Y, 5
	rjmp	_cad_read_port_l1



; read 6 hex2 digits and store to Z
CAD_READ_MAC:
        ldi	FROMRAM0, 6
_cad_read_mac_l0:
	rcall	CAD_READ_HEX2
	st	Z+, temp
	adiw	Y, 1
	dec	FROMRAM0
	brne	_cad_read_mac_l0
;	rcall	CAD_READ_HEX2
;	st	Z+, temp
;	adiw	Y, 1
;	rcall	CAD_READ_HEX2
;	st	Z+, temp
;	adiw	Y, 1
;	rcall	CAD_READ_HEX2
;	st	Z+, temp
;	adiw	Y, 1
;	rcall	CAD_READ_HEX2
;	st	Z+, temp
;	adiw	Y, 1
;	rcall	CAD_READ_HEX2
;	st	Z+, temp
	ret


CAD_READ_IP:
        ldi	FROMRAM0, 4
_cad_read_ip_l0:
	rcall	CAD_READ_DEC3
	st	Z+, temp
	adiw	Y, 1
	dec	FROMRAM0
	brne	_cad_read_ip_l0
;	rcall	CAD_READ_DEC3
;	st	Z+, temp
;	adiw	Y, 1
;	rcall	CAD_READ_DEC3
;	st	Z+, temp
;	adiw	Y, 1
;	rcall	CAD_READ_DEC3
;	st	Z+, temp
;	adiw	Y, 1
	ret


; echo iobyte addr in Z
CAD_PUT_IOBYTE:
	pushw	Y			; store start position
	ldi	temp, 1<<0              ; bit to test
CAD_IO_0:
	ld	r19, Z
	and	r19, temp
	ldi	r19, ' '
	breq	CAD_IO_1
	ldi	r19, '*'
CAD_IO_1:
	push	temp
	rcall	CAD_PUTC		; set value mark
	pop	temp
	lsl	temp
	adiw	Y,12			; go to next box
	cpi	temp, 1<<4		; next line??
	brne	CAD_IO_2
	popw	Y
;	adiw	Y,40
;	adiw	Y,40			; next line
	adiw	Y,40
	adiw	Y,40			; next line
CAD_IO_2:
	cpi	temp, 0
	brne	CAD_IO_0
	ret

; read and return 3-digit
CAD_READ_DEC3:
        push	r0
        push	r1
        push	r18

_cad_read_dec3_l1:
        rcall	CAD_READ_DEC1
        push	temp
        rcall	CAD_READ_DEC1
        push	temp
        rcall	CAD_READ_DEC1

        mov	r19, temp		; r19 = units
        pop	temp			; dozens
	ldi	r18, 10
	mul	temp, r18		; r0:r1 = dozens
	add	r19, r0			; overflow impossible!
        pop	temp			; hunderds
	ldi	r18, 100
	mul	temp, r18
	add	r19, r0
	adc	r1, zero

	cp	r1, zero		
	brne	_cad_read_dec3_l0	; result > 255?
	mov	temp, r19		; value to return
        pop	r18
        pop	r1
        pop	r0
	ret
_cad_read_dec3_l0:
	call	SYSTEM_BEEP
	sbiw	Y, 3
	rjmp	_cad_read_dec3_l1


CAD_READ_HEX2:
        rcall	CAD_READ_HEX1
        swap	temp
        push	temp
        rcall	CAD_READ_HEX1
	pop	r19
	or	temp, r19
	ret


; read and return 2-digit as BCD
CAD_READ_DEC2_BCD:
        rcall	CAD_READ_DEC1
        swap	temp
        push	temp
        rcall	CAD_READ_DEC1
	pop	r19
	or	temp, r19
	ret


; read decimal from input with echo
CAD_READ_DEC1:
;	rcall	CAD_CURSOR
_cad_read_d1_l0:
	rcall	CAD_CONIN
	cpi	temp, '0'
	brlo	CAD_READ_DEC1_BAD
	cpi	temp, '9'+1
	brsh	CAD_READ_DEC1_BAD
	mov	r19, temp
	rcall	CAD_PUTC
        subi	temp, '0'
	ret	
CAD_READ_DEC1_BAD:
	call	SYSTEM_BEEP
	rjmp	_cad_read_d1_l0



; read decimal from input with echo
CAD_READ_HEX1:
;	rcall	CAD_CURSOR
_cad_read_h1_l0:
	rcall	CAD_CONIN
	cpi	temp, '0'
	brlo	CAD_READ_HEX1_BAD
	cpi	temp, '9'+1
	brsh	_cad_read_h1_l1
	mov	r19, temp
	rcall	CAD_PUTC
        subi	temp, '0'
	ret	
_cad_read_h1_l1:
	cpi	temp, 'A'
	brlo	CAD_READ_HEX1_BAD
	cpi	temp, 'F'+1
	brsh	CAD_READ_HEX1_BAD
	mov	r19, temp
	rcall	CAD_PUTC
        subi	temp, 'A'-10
	ret	
CAD_READ_HEX1_BAD:
	call	SYSTEM_BEEP
	rjmp	_cad_read_h1_l0

/*
; output bcd value from temp to screen position Y
CAD_PUTBCD:
	push	r19
	swap	r19
	andi	r19, 0x0f
	subi	r19, -'0'
	rcall	CAD_PUTC
	pop	r19
	andi	r19, 0x0f
	subi	r19, -'0'
	rcall	CAD_PUTC
	adiw	Y, 1
	ret	
*/
; ------------------------------------------------------------------------------------------
CAD_CURSOR:
	push	YH
	subi	YH, 0xf7
	nportout cpd_vcurh, YH
	nportout cpd_vcurl, YL	
	pop	YH
	ret


; ------------------------------------------------------------------------------------------
CAD_PUTS_XY:
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT
	call	DO_PUTS
	SPI_STOP
	ret


; ------------------------------------------------------------------------------------------
CAD_PUTS:
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT
	call	DPS_CHAR
	SPI_STOP
	ret

; ------------------------------------------------------------------------------------------
; echo char from r19
CAD_PUTC:
        push	temp
        lds	temp, CAD_CMD_FLAG
        cpse	temp, zero
        ldi	r19, '*'
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT
	call	DPS_CHAROUT
	SPI_STOP
	pop	temp
	ret

; ------------------------------------------------------------------------------------------
; echo char from r19
CAD_PUTHEX:
        push	temp
        push	r18
        mov	r18, r19
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT
	call	STR_PUTHEX
	SPI_STOP
	pop	r18
	pop	temp
	ret


; ------------------------------------------------------------------------------------------
; output line from RAM (Z) to screen (Y) till 0
CAD_PUTS_RAM:
	push	r19
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT
CAD_PR_L1:
	ld	r19, Z+
	cpi	r19, 0
	breq 	CAD_PR_END
	call	DPS_CHAROUT
	cpi	YH, 0xFF
	brne 	CAD_PR_L1
	cpi	YL, 0xd0
	brne 	CAD_PR_L1
;	rjmp 	CAD_PR_L1
CAD_PR_END:
	SPI_STOP
	pop	r19
	ret



; ------------------------------------------------------------------------------------------
; get char from keyboard
CAD_CONIN:
	rcall	CAD_CURSOR
_cad_conin_l1:
        nportin cpd_kchar
	cpi	temp, 0
	breq	_cad_conin_l1			; wait for char received
	push	temp
	nportout cpd_kchar, zero
	pop	temp
	cpi	temp, 128
	brsh	_cad_conin_l0			; russian chars - not allowed
	cpi	temp, 'a'
	brlo	_cad_conin_ret
	cpi	temp, 'z'+1
	brsh	_cad_conin_ret
	subi	temp, 32			; uppercase
_cad_conin_ret:
	ret
_cad_conin_l0:
	call	SYSTEM_BEEP
	rjmp	_cad_conin_l1



; ------------------------------------------------------------------------------------------
; clear screen
CAD_CLRSCR:
	pushw	Y
	push	r19
	ldi	YH, 0xF8
	ldi	YL, 0
	ldi	r19, ' '

	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT

CAD_CLRSCR_L1:
	call	DPS_CHAROUT
	cpi	YH, 0xFF
	brne	CAD_CLRSCR_L1
	cpi	YL, 0xd0
	brne	CAD_CLRSCR_L1

	SPI_STOP

	pop	r19
	popw	Y
	ret


; ------------------------------------------------------------------------------------------
; restore screen from zRAM
CAD_RSTSCR:
	pushw	Y
	push	r19
	ldi	YH, 0xF8
	ldi	YL, 0
	ldi	r19, ' '
CAD_RSTSCR_L1:
	LDRAM   YH, YL, temp
	mov	r19, temp

	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT
	call	DPS_CHAROUT
	SPI_STOP

	cpi	YH, 0xFF
	brne	CAD_RSTSCR_L1
	cpi	YL, 0xd0
	brne	CAD_RSTSCR_L1
	pop	r19
	popw	Y
	ret


CAD_PUT_MSG_BLOCK:
	push	r18
	mov	r18, r19
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT
_cad_pu_msgb_l2:
	elpm	temp, Z        		; skip zeros
_cad_pu_msgb_l1:	
	cpi	temp, 0
	brne	_cad_pu_msgb_l0
	elpm	temp, Z+
	rjmp	_cad_pu_msgb_l1	
_cad_pu_msgb_l0:	
	call	DO_PUTS
	dec	r18
	brne	_cad_pu_msgb_l2
	SPI_STOP
	pop	r18
	ret


; ------------------------------------ special commands ------------------------------------
_CAD_CMD:
	pushw	X
	pushw	Y
	pushw	Z
	push	r19
        tcbe	1, _cad_cmd_pwd		; 1 = request password
_CAD_CMD_ret:
        pop	r19
        popw	Z
        popw	Y
        popw	X
	nportout cpd_kchar, zero	; clear char just for the case
	ret

_cad_cmd_pwd:
	call	SYSTEM_BEEP		; welcome beep
	nportout cpd_kchar, zero	; clear char just for the case
	rcall	CAD_CLRSCR
	m_puts CAD_MSG_RM
	sts	CAD_CMD_FLAG, one
	STR_GOTOXY 41, 15
	ldiw	Z, CAD_CMD_PIN
	rcall	CAD_READ_PORT
	rcall	CAD_RSTSCR
	rjmp	_CAD_CMD_ret
		
; ------------------------------------------------------------------------------------------
; ------------------------------------------------------------------------------------------

CAD_MSG_WC: MMSG 1,1, "CRISS CP/M SYSTEM CONSOLE V. 0.12c:"

CAD_MSG_M1: MMSG 1,3, "A = DRIVE A"
CAD_MSG_M2: MMSG 1,4, "B = DRIVE B"
CAD_MSG_M3: MMSG 1,5, "C = DRIVE C"
CAD_MSG_M4: MMSG 1,6, "D = DRIVE D"
CAD_MSG_M5: MMSG 1,7, "S = REINIT SD"
CAD_MSG_M6: MMSG 1,8, "I = IOBYTE "
CAD_MSG_M7: MMSG 1,9, "U = DEBUG OPTIONS"
CAD_MSG_MA: MMSG 1,10,"H = HARDWARE PLATFORM"
CAD_MSG_M10:MMSG 1,11,"R = RTC AND S-ROM"
CAD_MSG_M9: MMSG 1,12,"E = EEPROM "
CAD_MSG_M13:MMSG 1,13,"V = VRAM "
CAD_MSG_M14:MMSG 1,14,"Z = HALT PROGRAM "

CAD_MSG_SD: MMSG 1,3, "SD-CARD: "
CAD_MSG_SS: MMSG 1,24,"SELECT IMAGE FOR DRIVE "
CAD_MSG_SE: .DB ": ESC TO EXIT: ",0
;CAD_MSG_SS: MMSG 1,22,"PLEASE SELECT IMAGE, ESC TO EXIT:"

CAD_MSG_I0: MMSG 1,3, "CONSOLE: "
CAD_MSG_I1: MMSG 1,4, "OUTPUTS:  A [ ] CON:   B [ ] TTY:   C [ ] LAN:   D [ ] LST:"
CAD_MSG_I2: MMSG 1,5, "INPUTS:   E [ ] CON:   F [ ] TTY:   G [ ] LAN:   H [ ] LST:"

CAD_MSG_I3: MMSG 1,7, "PUNCH/READER:"
CAD_MSG_I4: MMSG 1,8, "OUTPUTS:  I [ ] SYS:   J [ ] TTY:   K [ ] LAN:   L [ ] LST:"
CAD_MSG_I5: MMSG 1,9, "INPUTS:   M [ ] SYS:   N [ ] TTY:   O [ ] LAN:   P [ ] LST:"

CAD_MSG_I9: MMSG 1,11,"DEVICES: "
CAD_MSG_I6: MMSG 1,12,"LIST:     Q [ ] LPT:   R [ ] TTY:   S [ ] LAN:   T [ ] LST:"
CAD_MSG_I7: MMSG 1,13,"SD:       U [ ] SDC:   V [ ] TTY:   W [ ] LAN:   X [ ] LST:"

CAD_MSG_I8: MMSG 1,15,"MOUSE:    Y [ ] KEYB "

CAD_MSG_IM: MMSG 1,24,"SELECT OPTION TO CHANGE, ESC TO EXIT:"

CAD_MSG_D1: MMSG 1,3, "NOTIFY TO TTY: "
CAD_MSG_D2: MMSG 1,5, "A [ ] RESERVED "
CAD_MSG_D3: MMSG 1,6, "B [ ] Z80 PORT IN/OUT REQUEST"
CAD_MSG_D4: MMSG 1,7, "C [ ] BDOS CALL"
CAD_MSG_D5: MMSG 1,8, "D [ ] BIOS CALL"
CAD_MSG_D6: MMSG 1,9, "E [ ] BIOS SD ACCESS "
CAD_MSG_D7: MMSG 1,10,"F [ ] BIOS CON CHAR CODES"
CAD_MSG_D8: MMSG 1,11,"G [ ] IRQ"
CAD_MSG_D9: MMSG 1,12,"H [ ] Z80 TRACE"

CAD_MSG_Z1: MMSG 35,3, "Z80 DEBUG: "
CAD_MSG_Z2: MMSG 35,5, "I [ ] ADDRESS"
CAD_MSG_Z3: MMSG 35,6, "J [ ] OPCODE "
CAD_MSG_Z4: MMSG 35,7, "K [ ] AF "
CAD_MSG_Z5: MMSG 35,8, "L [ ] BC DE HL "
CAD_MSG_Z6: MMSG 35,9, "M [ ] IX IY SP "
CAD_MSG_Z7: MMSG 35,10,"N [ ] MNEMONIC "
CAD_MSG_Z8: MMSG 35,11,"O [ ] BREAK AT   Q = [    ]"
CAD_MSG_Z9: MMSG 35,12,"P [ ] STEP "

CAD_MSG_DM: MMSG 1,24,"SELECT OPTION, ESC TO EXIT:"

CAD_MSG_R1: MMSG 1,3, "EEPROM:"
CAD_MSG_R2: MMSG 1,5, "A = RAM -> ROM #1"
CAD_MSG_R3: MMSG 1,6, "B = RAM <- ROM #1" 
CAD_MSG_R4: MMSG 1,7, "C = RAM <-> ROM #1 "
CAD_MSG_R5: MMSG 1,8, "D = RAM -> ROM #2"
CAD_MSG_R6: MMSG 1,9, "E = RAM <- ROM #2"
CAD_MSG_R7: MMSG 1,10,"F = RAM <-> ROM #2 "
CAD_MSG_R8: MMSG 1,11,"G = ERASE ROM #1 "
CAD_MSG_R9: MMSG 1,12,"H = ERASE ROM #2 "

CAD_MSG_RM: MMSG 1,24,"SELECT COMMAND, ESC TO EXIT: "

CAD_MSG_H1: MMSG 1,3, "HARDWARE PLATFORM: "

CAD_MSG_C1: MMSG 1,3, "RTC: "
CAD_MSG_C2: MMSG 1,5, "A = TIME: [  :  :  ] "
CAD_MSG_C3: MMSG 1,6, "B = DATE: [  .  .  ] [  ]" 

CAD_MSG_C5: MMSG 1,8, "C = MAC:  [  :  :  :  :  :  ]"
CAD_MSG_C4: MMSG 1,9, "D = IP:   [   .   .   .   ]" 
;CAD_MSG_C6: MMSG 1,10,"E = GATE: [   .   .   .   ]"
;CAD_MSG_C7: MMSG 1,11,"F = MASK: [   .   .   .   ]"

CAD_MSG_C8: MMSG 1,13,"G = SMAC: [  :  :  :  :  :  ]"
CAD_MSG_C9: MMSG 1,14,"H = S-IP: [   .   .   .   ]:[     ]"
CAD_MSG_CA: MMSG 1,15,"^P =                    PRN:[     ]"
CAD_MSG_CB: MMSG 1,16,"^S =                    SDC:[     ]"

CAD_MSG_C10:MMSG 1,18,"I = PMAC: [  :  :  :  :  :  ]"
CAD_MSG_C11:MMSG 1,19,"J = P-IP: [   .   .   .   ]:[     ]"

;CAD_MSG_C24:MMSG 1,21,"W = TMAC: [  :  :  :  :  :  ]"
;CAD_MSG_C25:MMSG 1,22,"X = T-IP: [   .   .   .   ]:[     ]"

	.EQU RSC2Y=41
CAD_MSG_C12: MMSG RSC2Y,17,"K = MBID: [  ] "
CAD_MSG_C13: MMSG RSC2Y,18,"L = CNID: [  ] "

CAD_MSG_C14: MMSG RSC2Y,3, "DISABLE: "
CAD_MSG_C15: MMSG RSC2Y,5, "M [ ] BUZZER "
CAD_MSG_C16: MMSG RSC2Y,6, "N [ ] TTY"
CAD_MSG_C17: MMSG RSC2Y,7, "O [ ] LST"
CAD_MSG_C18: MMSG RSC2Y,8, "P [ ] MUSIC"
CAD_MSG_C19: MMSG RSC2Y,9, "Q [ ] ROM"
CAD_MSG_C20: MMSG RSC2Y,10,"R [ ] LAN"
CAD_MSG_C21: MMSG RSC2Y,11,"S [ ] CAN"
CAD_MSG_C22: MMSG RSC2Y,12,"T [ ] SD-CARD"

CAD_MSG_C23: MMSG RSC2Y,14,"U = PASSWORD: [     ]"
CAD_MSG_C26: MMSG RSC2Y,15,"Y = BIOS PWD: [     ]"

	.EQU RSC3Y=65
CAD_MSG_C27: MMSG RSC3Y,3,  "IRQ VECTORS: "
CAD_MSG_C43: MMSG RSC3Y,5,  "^A = KBD [  ]"
CAD_MSG_C28: MMSG RSC3Y,6,  "^B = GPO [  ]"
CAD_MSG_C29: MMSG RSC3Y,7,  "^C = CTC [  ]"
CAD_MSG_C30: MMSG RSC3Y,8,  "^D = MUS [  ]"
CAD_MSG_C31: MMSG RSC3Y,9,  "^E = RS1 [  ]"
CAD_MSG_C32: MMSG RSC3Y,10, "^F = RS2 [  ]"
CAD_MSG_C33: MMSG RSC3Y,11, "^G = CTX [  ]"
CAD_MSG_C34: MMSG RSC3Y,12, "^H = CRX [  ]"
CAD_MSG_C35: MMSG RSC3Y,13, "^I = LAN [  ]"
CAD_MSG_C36: MMSG RSC3Y,14, "^J = CAN [  ]"
CAD_MSG_C37: MMSG RSC3Y,15, "^K = RTC [  ]"
CAD_MSG_C38: MMSG RSC3Y,16, "^L = RS3 [  ]"
CAD_MSG_C39: MMSG RSC3Y,17, "^M = RS4 [  ]"
CAD_MSG_C40: MMSG RSC3Y,18, "^N = RS5 [  ]"
CAD_MSG_C41: MMSG RSC3Y,19, "^O = TTX [  ]"
CAD_MSG_C42: MMSG RSC3Y,20, "^P = TRX [  ]"

CAD_MSG_PIN: MMSG 35,15,"PIN: [     ] "
	