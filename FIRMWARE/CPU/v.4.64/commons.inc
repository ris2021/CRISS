
; output predefined string to directly to CPD
DO_PUTS:
	elpm	YH, Z+
	elpm	YL, Z+
DPS_CHAR:
	elpm	r19, Z+
	or 	r19, r19
	breq 	DPS_END
	call	DPS_CHAROUT
	rjmp 	DPS_CHAR
DPS_END:
	ret
    

; output single char (r19) to CPD
DPS_CHAROUT:
	mov	temp, YH
	call 	DOSPI 
	mov	temp, YL
	call 	DOSPI
	mov	temp, r19
	call	DOSPI
	adiw	Y, 1
	ret


; outpu in8 as hex (r18)
STR_PUTHEX:
	; higher half-byte
	mov	r19, r18
	lsr	r19
	lsr	r19
	lsr	r19
	lsr	r19			; >>4
	cpi	r19, 10
	brlo  	str_tl_01    
	ldi	temp, 'a'-'0'-10
	add	r19, temp
str_tl_01:
	ldi	temp, '0'
	add   	r19, temp
	call  	DPS_CHAROUT

	; lower half-byte
	mov   	r19, r18
	andi	r19, 0x0f
	cpi	r19, 10
	brlo  	str_tl_02
	ldi	temp, 'a'-'0'-10
	add	r19, temp
str_tl_02:
	ldi	temp, '0'
	add	r19, temp
	call	DPS_CHAROUT

	ret



; ------------------------------------------------------------------------------
STR_OUT: 
        push	temp
	push	r18
STR_OUT_L2: 
	elpm	zzC, Z+
	cpi	zzC, 0
	breq	STR_OUT_L1
;	mov	zzC, temp
	ldi	temp, 0x04
	rcall	COM_BIOS_CMD
	rjmp	STR_OUT_L2
STR_OUT_L1:
	pop	r18
	pop	temp
	ret



; ------------------------------------------------------------------------------
STR_OUT_RAM: 
	ld	temp, Z+
	cpi	temp, 0
	brne	STR_OUT_RAM_L1
	ret
STR_OUT_RAM_L1:
	mov	zzC, temp
	ldi	temp, 0x04
	rcall	COM_BIOS_CMD
	rjmp	STR_OUT_RAM



; ------------------------------------------------------------------------------
; outpu in8 as hex (r18)
STR_HEXOUT:
	; higher half-byte
	mov	r19, r18
	lsr	r19
	lsr	r19
	lsr	r19
	lsr	r19			; >>4
	cpi	r19, 10
	brlo  	str_ho_01    
	ldi	temp, 'a'-'0'-10
	add	r19, temp
str_ho_01:
	ldi	temp, '0'
	add   	r19, temp
	mov	zzC, r19
	ldi	temp, 0x04
	rcall	COM_BIOS_CMD
;	call  	DPS_CHAROUT

	; lower half-byte
	mov   	r19, r18
	andi	r19, 0x0f
	cpi	r19, 10
	brlo  	str_ho_02
	ldi	temp, 'a'-'0'-10
	add	r19, temp
str_ho_02:
	ldi	temp, '0'
	add	r19, temp
	mov	zzC, r19
	ldi	temp, 0x04
	rcall	COM_BIOS_CMD
;	call	DPS_CHAROUT

	ret



; --------------------------------------------------------------------------------------
; send temp via uart1
UART1_SEND:
	push	temp
US1:	
    	lds	temp, UCSR1A
	sbrs	temp, UDRE1
	rjmp	US1
	pop	temp
	sts	UDR1, temp
	ret



; ------------------------------------------------------------------------------
; outpu in8 as hex (temp)
UART1_HEXOUT:
	; higher half-byte
	push	r19
	push	temp
	mov	r19, temp
	lsr	r19
	lsr	r19
	lsr	r19
	lsr	r19			; >>4
	cpi	r19, 10
	brlo  	uart1_ho_01    
	ldi	temp, 'a'-'0'-10
	add	r19, temp
uart1_ho_01:
	ldi	temp, '0'
	add   	temp, r19
	call	UART1_SEND
	; lower half-byte
	pop	r19
	andi	r19, 0x0f
	cpi	r19, 10
	brlo  	uart1_ho_02
	ldi	temp, 'a'-'0'-10
	add	r19, temp
uart1_ho_02:
	ldi	temp, '0'
	add	temp, r19
	call	UART1_SEND
	pop	r19
	ret



SYSTEM_BEEP:
	lds	temp, RTC_HW_DISABLE		; check that buzzer enabled
	sbrc	temp, HW_DSBL_BUZ
	ret

	; setup timeout timer
        ldi     temp, (1<<CS12)|(1<<CS10)  	; fclk/1024 
        sts     TCCR1B, temp 			; start timer

	; init timeout timer, time in ms
        ldi	temp, ((200)*76/1000)
        sts	OCR1AH, temp
        sts	OCR1AL, zero
        sts	TCNT1H, zero
        sts	TCNT1L, zero
        sbi	TIFR1, OCF1A  ; clear oc1a flag

        SPI_INIT SPI_SLAVE_BUZ, SPI_FCK_DIV_16
        SPI_SELECT
SYSTEM_BEEP_W:
        sbis    TIFR1, OCF1A
        rjmp	SYSTEM_BEEP_W
        SPI_STOP
	sts     TCCR1B, zero
	ret


; --------------------------------------------------------------------------------------
; convert BCD to hex
BCD_to_HEX:
        push	zzA
	push	r0
	push	r1
	push	temp
	andi    temp,0xf0    ; Mask the register, as the MSB
	swap    temp         ; Change tetrad places
	ldi     zzA,10       ; Write to the auxiliary register 10 value
	mul     temp,zzA     ; Multiply the value of r16 register 10, the result is stored in the registers r1, r0
	pop     temp         ; get the stored value from the stack
    	andi    temp,0x0f    ; Mask the register r16, as the LSB
    	add     temp,r0      ; Adds the r16 register with register r0, the result is a binary number from 0 to 99
	pop	r1
	pop	r0
	pop	zzA
	ret


; convert HEX to BCD
HEX_to_BCD:
	push	zzA
	clr     zzA            ; clear register help
HEX_to_BCD_l: 
	subi    temp,10        ; temp = temp — 10
	brcs    HEX_to_BCD_2   ; Abort if the transfer set
	inc     zzA            ; Increment r17	
	rjmp    HEX_to_BCD_l   ; We pass on the testing cycle again
HEX_to_BCD_2: 
	subi    temp,-10       ; compensate a negative value in r16
	swap    zzA            ; Change tetrad places
	or	temp,zzA       ; Combine the received values in a packed BCD
	pop	zzA
	ret


; move Y btes from Z to X backward
LAN_ZXYb:
	addw	Z, Y
	addw	X, Y			; start from end
_lan_zxyb_l0:				; moving data block to desirep position
	cpi	YH, 0
	brne	_lan_zxyb_l2
	cpi	YL, 0
	breq	_lan_zxyb_l1
_lan_zxyb_l2:
	ld	temp, -Z
	st	-X, temp
	sbiw	Y, 1
	rjmp	_lan_zxyb_l0
_lan_zxyb_l1:
	ret


	; move Y btes from Z to X
LAN_ZXYf:
_lan_zxyf_l0:				; moving data block to desirep position
	cpi	YH, 0
	brne	_lan_zxyf_l2
	cpi	YL, 0
	breq	_lan_zxyf_l1
_lan_zxyf_l2:
	ld	temp, Z+
	st	X+, temp
	sbiw	Y, 1
	rjmp	_lan_zxyf_l0
_lan_zxyf_l1:
	ret


	; call to BIOS, safe registers
COM_BIOS_CMD:
        pushw	Z
	push	r18
	push	r19
	push	temp
	call	BIOS_CMD
	pop	temp
	pop	r19
	pop	r18
	popw	Z
	ret


	; copy TEMP bytes from X (AVR) to Z (RAM)
MCOPY_AVR_RAM:
	push	zzA
MCOPY_AVR_RAM_L1:
	ld	zzA, X+
	STRAM	ZH, ZL, zzA
	adiw	Z, 1
	dec	temp
	brne	MCOPY_AVR_RAM_L1			; store data to RAM
	pop	zzA
	ret


	; copy Y bytes from X (AVR) to Z (RAM)
MCOPY_AVR_RAM_Y:
	push	zzA
	adiw	Y, 1
	rjmp	MCOPY_AVR_RAM_Y_L2			; check for Y=0
MCOPY_AVR_RAM_Y_L1:
	ld	zzA, X+
	STRAM	ZH, ZL, zzA
	adiw	Z, 1
MCOPY_AVR_RAM_Y_L2:
	sbiw	Y, 1
	brne	MCOPY_AVR_RAM_Y_L1			; store data to RAM
	pop	zzA
	ret


	; copy TEMP bytes from Z (RAM) to X (AVR) 
MCOPY_RAM_AVR:
	push	zzA
MCOPY_RAM_AVR_L1:
        LDRAM   ZH, ZL, zzA
	st	X+, zzA
	adiw	Z, 1
	dec	temp
	brne	MCOPY_RAM_AVR_L1			; store data to AVR
	pop	zzA
	ret


	; copy Y bytes from Z (RAM) to X (AVR) 
MCOPY_RAM_AVR_Y:
	push	zzA
	adiw	Y, 1
	rjmp	MCOPY_RAM_AVR_Y_L2			; check for Y=0
MCOPY_RAM_AVR_Y_L1:
        LDRAM   ZH, ZL, zzA
	st	X+, zzA
	adiw	Z, 1
MCOPY_RAM_AVR_Y_L2:
	sbiw	Y, 1
	brne	MCOPY_RAM_AVR_Y_L1			; store data to AVR
	pop	zzA
	ret


	; sending zzC to RS-232 interface
RS232_SEND:
	nportin cpd_comtc
	cpi	temp, 0
	brne	RS232_SEND		; wait current char is transmitted
	nportout cpd_comtx, zzC		; char to send
	delay3	15
	nportout cpd_comtc, one		; force transmit action
	ret


	; returns data from RS-232 interface, 0 if no data	
RS232_RECEIVE:
	nportin	cpd_comst
	sbrs	temp, 7			; check RXC flag
	rjmp	_RS232_RECEIVE_NO
	nportin	cpd_comrx
;	mov	zzC, temp	
	ret
_RS232_RECEIVE_NO:
	clr	temp
	ret


	; returns in temp char received (if any) of RS-232 interface	
;RS232_STATUS:
;	nportin	cpd_comst
;	sbrs	temp, 7			; check RXC flag
;	ret
;	nportin	cpd_comrx
;	mov	zzC, temp	
;	ret
