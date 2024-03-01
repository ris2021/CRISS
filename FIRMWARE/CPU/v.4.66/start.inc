; ---------------------------------------------------------------------------------------------------------------
; STARTUP welcome and BAT 
; called as subroutine, must be ended with ret
; ---------------------------------------------------------------------------------------------------------------

.MACRO 	SET_FOUND
	lds	temp, HW_FOUND
	sbr	temp, 1<<@0
	sts	HW_FOUND, temp
.ENDM

DOSTART_CMD:
; ------- START DELAY approx 500 ms

	SPI_INIT  SPI_SLAVE_LED, SPI_FCK_DIV_4		; System LED on
	SPI_SELECT
							; start delay to init PDC
	_outm  	TCNT1H, 0
	_outm  	TCNT1L, 0
	_outm  	TCCR1B, (1<<CS12)|(1<<CS10)
L1:
	lds	temp, TCNT1L
	lds	temp, TCNT1H
	cpi	temp, 0x80
	brlo  	L1

	_outm  	TCCR1B, 0
	SPI_STOP					; System LED off

; --------  output sync sequence

	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4
	SPI_SELECT
	ldi	r19, 30
L2:
	ldi	temp, 0x80 			; sync request
	call	DOSPI 
	dec	r19
	brne	L2
	SPI_STOP

; ---------- check CPD and debug mode (if ESC key pressed during startup)

	nportin	cpd_kchar
	mov	zzF, temp			; save CPD state
	cpi	temp, 0xFF			; CPD NOT present?
	breq	_dostart_normal			; start in TTY control mode

;_dostart_cpd_ok:	
;	lds	temp, CON_IOBYTE
;	sbr	temp, (1<<CON_OUT_CON) | (1<<CON_IN_CON)	; if CPD installed CON I/O is always ON
;	sts	CON_IOBYTE, temp
_dostart_esc_mode:
	SET_FOUND HW_FOUND_CPD			; set CPD found

	cpi	temp, 27			; check debug mode start request
	brne	_dostart_normal

_dostart_tty_mode:
	lds	temp, CON_IOBYTE
	sbr	temp, (1<<CON_OUT_TTY) | (1<<CON_IN_TTY)	; using UART for 
;	cbr	temp, (1<<CON_OUT_CON) | (1<<CON_IN_CON)	; if CPD not installed CON I/O is always OFF
	sts	CON_IOBYTE, temp

_dostart_normal:
; output welcome message from MCU

	con_puts MSG_WELCOME0


STARTLOOP:

; -------- RAM test

	con_puts MSG_RAMTEST

	; RAM test starts here
	ldi	YH, 0
	ldi	YL, 0 
	ldi	r19, 0

L3:
	STRAM	YH, YL, YL
	_out	DDRB, 0			; Data port to in
	mov	temp, YL
	com	temp              	; inv temp
	out	PORTB, temp		; to change pullups

	LDRAM	YH, YL, temp

	cp	YL, temp                ; check that read value = written one
	breq  	L4			; proceed if ok
	ldi	r19, 1			; set error flag
L4:
	adiw	Y,1
	cpi	YH, 0xf8
	brlo	L3			; do not corrupt videram

	cpi	r19, 0			; check error flag == 0
	breq  	L5
	con_puts MSG_FAILED
	rjmp  	L6
L5:
	con_puts MSG_PASSED

	lds	temp, HW_FOUND
	sbr	temp, 1<<HW_FOUND_RAM
	sts	HW_FOUND, temp
L6:


/*
; ----------- check IRQ controller status
	con_puts MSG_IRQCTRL

    	; access IRQ controller chip
	SPI_INIT SPI_SLAVE_IRQ, SPI_FCK_DIV_4		; 
	SPI_SELECT
	iSPI 	0b01000001	; address byte
	iSPI	0x05		; IOCON
	iSPI	0xff		; for read op
    	SPI_STOP		; stop IRQ access

    	cpi	temp, 0xff
    	brne	L_STR_IRQFOUND          ; ok, data read

	con_puts MSG_IRQNOTFOUND
	rjmp	L_STR_IRQCHECK_END

L_STR_IRQFOUND:
	con_puts MSG_IRQFOUND	

;	mov    	r18, temp
;	call	STR_HEXOUT		; output revid
;	con_puts MSG_LANINITING

	lds	temp, HW_FOUND
	sbr	temp, 1<<HW_FOUND_IRQ
	sts	HW_FOUND, temp

;	call	IRQ_INIT
L_STR_IRQCHECK_END:
; -----------------------------------------
*/


; ----------- check EXT controller status
	con_puts MSG_EXTCTRL

;	cbi	DDRD, PD6	; pin to input
;l_ext_wait_d6:
;	sbis	PIND, PD6
;	rjmp	l_ext_wait_d6	; wait RTC int clear just for the case

	lds	temp, HW_FOUND
	sbr	temp, 1<<HW_FOUND_EXT
	sts	HW_FOUND, temp	; pretend that CLR is installed

	ldi	temp, CLR_CMD_DEFAULT
	call	CLR_CMD		; trying to reset CLR MCU
	lds	temp, PCMD_FE	; check response

    	; access IRQ controller chip
;	SPI_INIT SPI_SLAVE_EXT, SPI_FCK_DIV_4		; select channel
;	SPI_SELECT
;	nop
;	nop
;	nop
;	nop
;	in	temp, PIND	; read status
;   	SPI_STOP		; stop EXT check access

;    	sbrs	temp, 6
	cpi	temp, 0xFF	; 0xFF == error, no response
	breq	L_STR_EXT_NOT_FOUND

	sbrs	temp, 4		; bit 4 always on check valid response
	rjmp	L_STR_EXT_NOT_FOUND
    	
	sbrc	temp, 3		; bits 3, 5,6,7 must be 0 - check valid response
	rjmp	L_STR_EXT_NOT_FOUND
    	
	sbrc	temp, 5		; check valid response
	rjmp	L_STR_EXT_NOT_FOUND
    	
	sbrc	temp, 6		; check valid response
	rjmp	L_STR_EXT_NOT_FOUND
    	
	sbrc	temp, 7		; check valid response
	rjmp	L_STR_EXT_NOT_FOUND
    	
	cpi	temp, 0x10	; 0x10 == error, black default color is not allowed
	breq	L_STR_EXT_NOT_FOUND

    	rjmp	L_STR_EXTFOUND	; Ok, EXT CLR version

L_STR_EXT_NOT_FOUND:
	lds	temp, HW_FOUND
	cbr	temp, 1<<HW_FOUND_EXT
	sts	HW_FOUND, temp

	con_puts MSG_EXTNOTFOUND
	rjmp	L_STR_EXTCHECK_END


L_STR_EXTFOUND:
	con_puts MSG_EXTFOUND	

	lds	temp, HW_FOUND
	sbr	temp, 1<<HW_FOUND_EXT
	sts	HW_FOUND, temp

;	call	IRQ_INIT
L_STR_EXTCHECK_END:
; -----------------------------------------



; ----------- check CPD status
L_STR_CPDCHECK:
	lds	temp, HW_FOUND
	sbrs	temp, HW_FOUND_CPD
	rjmp	L_STR_RTCCHECK
	con_puts MSG_CPDFOUND



; ----------- check RTC status
L_STR_RTCCHECK:
	con_puts MSG_RTCDATA

    	; access RTC chip
	SPI_INIT SPI_SLAVE_RTC, SPI_FCK_DIV_16_CPHA	; /16, RTC supports fck till 2 MHz
	SPI_SELECT
	delay3	30			; 1us delay	
	iSPI	0x0f
	call	DOSPI			; read control register
;	SPI_DESELECT
    	SPI_STOP		    	; stop RTC access

    	cpi	temp, 0xff
    	brne	L_STR_RTCFOUND          ; ok, data read

    	SPI_STOP		    	; stop RTC access
    	con_puts MSG_RTCNOTFOUND        ; not foud message
;    	ldi	temp, (1<<CON_OUT_CON) | (1<<CON_IN_CON)
 ;   	sts	RTC_IOBYTE, temp

    	ldi	temp, (1<<LST_OUT_LST)
 	sts	RTC_DEV_IOBYTE, temp
   	
    	rjmp	L_STR_RTCCHECK_END

L_STR_RTCFOUND:				; display control registers
        push	temp

	lds	temp, HW_FOUND
	sbr	temp, 1<<HW_FOUND_RTC
	sts	HW_FOUND, temp

	pop	temp
        push	temp

	andi	temp, 0x80		; check that RTC stopped = first run
	breq	_str_rtc_L10

	ldi	temp, 3
	call	RTC_CMD			; clear RTC ROM

_str_rtc_L10:
        pop	r18
	call	STR_HEXOUT		; echo control register
	con_putc ' '

	call	RTC_INIT		; start clock

        ldi	temp, 0
        call	RTC_CMD			; read date/time

	ldiw	X, RTC_SECS
	ldi	r20, 7
_str_rtc_L9:
	ld    	r18, X+
	call	STR_HEXOUT		; echo date/time
	con_putc ':'
	dec	r20
	brne  	_str_rtc_L9

        ldi	temp, 7
        call	RTC_CMD			; read ROM

	con_puts MSG_RTCLOADED		; ram loaded message

;	ldstt	CON_IOBYTE, RTC_IOBYTE
;	ldstt	PR_IOBYTE,  RTC_PR_IOBYTE

	ZXYf	RTC_LAN_MY_MAC, LAN_MAC_MY, 6
	ZXYf	RTC_LAN_MY_IP, LAN_IP_MY, 4
	ZXYf	RTC_PNC_MAC, PR_SRV_MAC, 6+4+2	
;	ZXYf	RTC_PRN_PORT, PRN_SRV_PORT, 4	; RND and RSD ports
	
L_STR_RTCCHECK_END:



; ----------  get LAN controller status
L_STR_LANCHECK:
	con_puts MSG_LANSTATUS		; display message

	SPI_INIT SPI_SLAVE_LAN, SPI_FCK_DIV_4
	LAN_CREG_WRITE LAN_ECON1, LAN_BANK3
	LAN_ETH_REG_READ LAN_EREVID
    	SPI_STOP		    	; stop LAN access

    	cpi	temp, 0xff
    	brne	L_STR_LANFOUND          ; ok, data read

	con_puts MSG_RTCNOTFOUND
	rjmp	L_STR_LANCHECK_END

L_STR_LANFOUND:
        push	temp

	lds	temp, HW_FOUND
	sbr	temp, 1<<HW_FOUND_LAN
	sts	HW_FOUND, temp

	con_puts MSG_LANPRES	

	pop    	r18
	call	STR_HEXOUT		; output revid

	con_puts MSG_LANINITING

	ldi	temp, LAN_FUNC_INIT	; 0
	lds	r18, HW_FOUND
	sbrc	r18, HW_FOUND_RTC
	ldi	temp, LAN_FUNC_INIT_CUSTOM	; 1
	call	LAN_CMD			; init LAN

L_STR_LANCHECK_END:   



; ----------  get CAN controller status
L_STR_CANCHECK:
	SPI_INIT SPI_SLAVE_CAN, SPI_FCK_DIV_4
        SPI_SELECT
	iSPI	CAN_CMD_RXSTAT
	iSPI	0xff			; read response
        SPI_DESELECT
    	SPI_STOP		    	; stop LAN access

    	cpi	temp, 0xff
    	breq	L_STR_CANCHECK_END	; no CAN

	con_puts MSG_CAN

	lds	temp, HW_FOUND
	sbr	temp, 1<<HW_FOUND_CAN
	sts	HW_FOUND, temp

L_STR_CANCHECK_END:



; ---------- get EEPROM status
L_STR_ROMCHECK:

	con_puts MSG_ROMCHECK

	SPI_INIT SPI_SLAVE_ROM, SPI_FCK_DIV_4
	SPI_SELECT
	iSPI	0b00000101		; RDSR
	iSPI	0xff                    ; READ
    	SPI_STOP		    	; stop access

    	cpi	temp, 0xff
    	brne	L_STR_ROMFOUND          ; ok, data read

	con_puts MSG_RTCNOTFOUND
	rjmp	L_STR_ROMCHECK_END

L_STR_ROMFOUND:
        push	temp
	con_puts MSG_ROMFOUND

	pop    	r18
	call	STR_HEXOUT		; output revid
	con_putc 13
	con_putc 10

	lds	temp, HW_FOUND
	sbr	temp, 1<<HW_FOUND_ROM
	sts	HW_FOUND, temp
L_STR_ROMCHECK_END:



; ---------- get sd controller status
L_STR_SDCHECK:

	con_puts MSG_SDSTATUS
	
	call  SD_INIT			; trying to init SD card

	mov	r18, temp
	call  	STR_HEXOUT            	; show response
	con_putc ' '
	lds	r18, SD_TYPE
	call  	STR_HEXOUT            	; show response
	con_putc ' '
	lds	r18, SD_RSP
	call  	STR_HEXOUT            	; show response
	lds	r18, SD_RSP+1
	call  	STR_HEXOUT            	; show response
	lds	r18, SD_RSP+2
	call  	STR_HEXOUT            	; show response
	lds	r18, SD_RSP+3
	call  	STR_HEXOUT            	; show response
	  
	con_putc 13
	con_putc 10

;	lds	temp, SD_TYPE
;	cpi	temp, 0
;	brne	



; ------------- select OS load source
L_STR_OSLOAD:
        lds	temp, HW_FOUND
        sbrs	temp, HW_FOUND_RAM
        rjmp	L_STR_OSLOAD_NOOS	; No RAM, no booting

        andi	temp, (1<<HW_FOUND_ROM)
	lds	r20, SD_TYPE
	or	temp, r20		; check that any boot sources are available
	brne	L_STR_OSLOAD_GO

L_STR_OSLOAD_NOOS:
	con_puts MSG_NOOS		; screen message
L_STR_OSLOAD_NOOS_PROMPT:
	ldi	temp, 3
	call	BIOS_CMD		; CONIN
	cpi	temp, 0
	breq	L_STR_OSLOAD_NOOS_PROMPT; BIOS(3) sets zzPC-=2 and returns

	rjmp	L_STR_ROMCHECK		; recheck SD and ROM

L_STR_OSLOAD_GO:	
	con_puts MSG_SELECTOS		; screen message

	lds	temp, HW_FOUND
	sbrs	temp, HW_FOUND_ROM
	rjmp	L_STR_OSLOAD_CHECK_SD

	con_puts MSG_BOOTROM		; ROM present - boot option screen message

L_STR_OSLOAD_CHECK_SD:
	lds	temp, SD_TYPE
	cpi	temp, 0x00
	brne	L_STR_OSLOAD_START

;	lds	temp, HW_FOUND
;	cbr	temp, 1<<HW_FOUND_SDC	; set that SD card is not found
;	sts	HW_FOUND, temp
	
	rjmp	L_STR_KP		; No card inserted

L_STR_OSLOAD_START:

;	lds	temp, HW_FOUND
;	sbr	temp, 1<<HW_FOUND_SDC	; set that SD card is found
;	sts	HW_FOUND, temp

	ldi	temp, 0x00
;	add	temp, r20		;!!!!!!! check !!!!!!!
	sts	SD_ADDRESS, temp
	ldi	temp, 0x08
	sts	SD_ADDRESS+1, temp
	ldi	temp, 0x00
	sts	SD_ADDRESS+2, temp
	ldi	temp, 0x00
	sts	SD_ADDRESS+3, temp
	call	SD_READ_DO		; load SD card name

	con_puts MSG_SDFOUND

	con_puts_ram SD_BUF		; display PB name	
	con_putc 13
	con_putc 10

	ldi	r20, 255
	clr	r19			; counter for number of images available
L_STR_SDPL:
	inc	r20
	cpi	r20, 9+1		; # of boot image - 0..9 range
	brlo	L_STR_SDPL_L1
	rjmp	L_STR_KP

L_STR_SDPL_L1:
	ldi	temp, 0xF0
	add	temp, r20
	sts	SD_ADDRESS, temp
	ldi	temp, 0x08
	sts	SD_ADDRESS+1, temp
	ldi	temp, 0x00
	sts	SD_ADDRESS+2, temp
	ldi	temp, 0x00
	sts	SD_ADDRESS+3, temp
	call	SD_READ_DO

	cpi	temp, 0
	brne	L_STR_KP

	lds	temp, SD_BUF
	cpi	temp, 0
	breq	L_STR_SDPL		; no preload block

	inc	r19			; increment counter
	mov	r8, r20			; store no for the "single choice"
	con_putc ' '
	ldi	temp, '0' 
	mov	zzC, temp
	add	zzC, r20
	ldi	temp, 0x04
	call	BIOS_CMD		; out n = 
	con_putc ' '
	con_putc '='
	con_putc ' '

	con_puts_ram SD_BUF		; display PB name	
	con_putc 13
	con_putc 10
	rjmp	L_STR_SDPL
	; options from SD

L_STR_KP:
        lds	temp, HW_FOUND
        sbrc	temp, HW_FOUND_CPD
        rjmp	L_STR_OSLOAD_STD	; CPD presents, standard bootinig

	cpi	r19, 1			; only 1 option available?
	breq	L_STR_OSLOAD_SD_ONLY_1_DO
        sbrs	temp, HW_FOUND_ROM
	rjmp	L_STR_ROMCHECK		; recheck SD and ROM
L_STR_START_ROM_A:
	ldi	r19, 'A'		; select bank A
	rjmp	L_STR_KP_6		; Boot from the ROM#A
	
L_STR_OSLOAD_STD:
	lds	temp, HW_FOUND
	sbrc	temp, HW_FOUND_ROM
	rjmp	L_STR_QUERY		; ROM presents - request in any case

L_STR_OSLOAD_SD_ONLY_1:
	cpi	r19, 1			; only 1 option available?
	brne	L_STR_QUERY

L_STR_OSLOAD_SD_ONLY_1_DO:
	con_puts MSG_ONLYIMG		; display message

	ldi	r19, '0'
	add	r19, r8			; r19 = selected option
	rjmp	L_STR_KP_3		; process it!

L_STR_QUERY:
;	lds	temp, HW_FOUND
;	sbrc	temp, HW_FOUND_SDC	; when ROM is available but SD is absent start from ROM#A
;	rjmp	L_STR_QUERY_L1

L_STR_QUERY_L1:	
	con_puts MSG_SELKEY
	clr	r19			; buffer for command

L_STR_KP_2:
	ldi	temp, 3
	call	BIOS_CMD		; CONIN

	cpi	temp, 0
	breq	L_STR_KP_2		; BIOS(3) sets zzPC-=2 and returns

;	cpi	temp, 32
;	brlo	L_STR_KP_2

	cpi	temp, 13
	breq	L_STR_KP_3

	cpi	r19, 0
	breq	L_STR_KP_4		; no symbol entered

	cpi	temp, 8			; Backspace
	brne	L_STR_KP_2		; ignore if no

	con_putc 8
	con_putc ' '
	con_putc 8			; clear char
	ldi	r19, 0		

	rjmp	L_STR_KP_2

L_STR_KP_4:
	cpi	temp, ' '
	brlo	L_STR_KP_2

	mov	r19, temp

	mov	zzC, temp
	ldi	temp, 0x04
	call	BIOS_CMD      		; echo input
	rjmp	L_STR_KP_2

L_STR_KP_3:
	con_putc 13			; CR
	con_putc 10			; LF

	cpi	r19, '0'
	brsh	L_STR_KP_5
	rjmp	L_STR_SDCHECK           ; reload and reinit SD

L_STR_KP_5:

	cpi	r19, 'a'
	breq	L_STR_KP_6_1_1
	cpi	r19, 'b'
	breq	L_STR_KP_6_1_1
	cpi	r19, 'A'
	breq	L_STR_KP_6_1
	cpi	r19, 'B'
	breq	L_STR_KP_6_1

	cpi	r19, '9'
	brlo	L_STR_KP_7

	con_puts MSG_LOADBAD
	rjmp	L_STR_KP

L_STR_KP_6_1_1:
	subi	r19, 0x20		; upcase
L_STR_KP_6_1:
	rjmp	L_STR_KP_6  		; to provide relative jump


L_STR_KP_7:		
	lds	temp, SD_TYPE
	cpi	temp, 0x00
	brne	L_STR_KP_8		; No card inserted
L_STR_KP_7_1:
	con_puts MSG_LOADNOSD
	rjmp	L_STR_SDCHECK		;L_STR_KP

	; load from SD card
L_STR_KP_8:				; load from SD-card		
	con_puts MSG_LOADING
	mov	zzC, r19
	ldi	temp, 0x04
	call	BIOS_CMD      		; echo
	con_puts MSG_LOADSD

	subi	r19, '0'		; block address starts from 0 now
	ldiw	Y, 0x0900		; start address of preloads on SD
;	ldi	r18, 0x80		; sector number increment
	cpi	r19,0
	breq	L_STR_KP_9
L_STR_KP_10:
        ldi	temp, 0x80
	add	YL, temp
	adc	YH, zero
	dec	r19
	brne	L_STR_KP_10		; Y = Y+0x80*r19
L_STR_KP_9:		
        ldi	r19, 0x80-4		; blocks to read (except videoram)
        ldiw	Z, 0			; start address in zRAM

L_STR_KP_12:		
	sts	SD_ADDRESS, YL
	sts	SD_ADDRESS+1, YH
	sts	SD_ADDRESS+2, zero
	sts	SD_ADDRESS+3, zero
	call	SD_READ_DO           	; read block
;	call	SD_READ           	; read block

	ldi	XL, low(SD_BUF)
	ldi	XH, high(SD_BUF)
L_STR_KP_11:		   		; strore buf in RAM
	ld	temp, X+
	STRAM	ZH, ZL, temp
	adiw	Z, 1
	cpi	XL, low(SD_BUF_END)		
	ldi	temp, high(SD_BUF_END)
	cpc	XH, temp
	brlo	L_STR_KP_11

	mov	temp, r19
	andi	temp, 0x03
	brne	L_STR_KP_13
	con_putc '.'			; display progress
L_STR_KP_13:

;	ldi	temp, 0x80
;	add     YL, temp
	add     YL, one
	adc	YH, zero		; Y++ = next block
	dec	r19
	breq	L_STR_LOADED
	rjmp	L_STR_KP_12		; read next block if not END

L_STR_KP_6:		
;        con_puts MSG_LOADEPROM		; screen message
	;reading from EPROM 

	subi	r19, 'A'		; select eeprom bank
	mov	zzA, r19
	call	CAD_SET_EEPROM_ROM_RAM_PROC	; read ROM to RAM and restore registers
	call	SD_LAST_RESET
	call	CAD_EXIT_NO_CRT		; start, no CRT restore
	sbiw	zzPCl, 2		; repeat BIOS 2 command 
	rjmp	L_STR_PREPARE
;	ret

L_STR_LOADED:
        con_puts MSG_STARTING

        ldi	temp, BIOS_FUNC_SET_VIDEOMODE
        call	BIOS			; set display mode
        ldi	temp, BIOS_FUNC_CRT_RESET
        call	BIOS			; reset attr buffer

L_STR_START_100:
	mov	zzSPh, one
	mov	zzSPl, zero
	mov	zzPCH, one
	mov	zzPCl, zero		; starting from 0x100
	clr	zzA
	clr	zzC
	clr	zzD
	clr	zzF

L_STR_PREPARE:	
	; set IObytes
	lds	FROMRAM0, CON_IOBYTE
	lds	temp, RTC_IOBYTE	; RTC settings
	or	FROMRAM0, temp		; combine with RTC settings
	lds	temp, HW_FOUND
	sbrs	temp, HW_FOUND_CPD
	cbr	FROMRAM0, ((1<<CON_IN_CON)|(1<<CON_OUT_CON))	; clear std i/o channels if no CPD
	sts	CON_IOBYTE, FROMRAM0

	ldstt	PR_IOBYTE,  RTC_PR_IOBYTE
	ldstt	DEV_IOBYTE,  RTC_DEV_IOBYTE

	nportout cpd_kchar, zero	; clear input

	sbi	PCIFR, PCIF3		; clear interrupt request if any
	sei				; enable interrupts

	ldi	temp, high(zOPCODE__LBLS_L)
	out	GPIOR2, temp		; GPIOR2 contains high pointer to decode table

	ret				; return back from the call


