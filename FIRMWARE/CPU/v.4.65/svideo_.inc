CSP_VIDEO_CMD_IN:
	ret

CSP_VIDEO_CMD_OUT:
	ret











/*	
	andi	temp, 0x3f	; mask high bits
	cpi	temp, 0x0f
	brlo	CSP_RTC_READ_BCD ; 0x00 - 0x0e = RTC commands with BCD output
	cpi	temp, 0x20
	brlo	CSP_RTC_READ_VAL ; 0x0f - 0x20 = RTC commands with hex output
	tcbe	0x30, CSP_IRQ_STATUS	; get interrupt status
	tcbe	0x31, CSP_DBG_STATUS	; get debug status
	tcbe	0x32, CSP_R2_STATUS	; get R2 status
	tcbe	0x33, CSP_SD_TYPE	; get SD type
	ret

CSP_RTC_READ_BCD:
        sts	CDATA+2, temp
        _outm	CDATA+3, 0xff
        rjmp	CPU_RTC_READ	; read port from RTC and return

CSP_RTC_READ_VAL:
	subi	temp, 0x0f
	call    CSP_RTC_READ_BCD
	rjmp	BCD_to_HEX	; convert to hex and exit

CSP_IRQ_STATUS:
	in	temp, GPIOR0
	ret

CSP_DBG_STATUS:
	lds	temp, GPIOR1
	ret

CSP_R2_STATUS:
        ;!! write code here, hw_layer selector read to temp
	ret

CSP_SD_TYPE:
	lds	temp, SD_TYPE
	ret

; -------------------------- CPU port out functions ----------------------------------
CPU_SPECIAL_OUT:
	andi	temp, 0x3f	; mask high bits
	cpi	temp, 0x0f
	brlo	CSP_RTC_WRITE_BCD ; 0x00 - 0x0e = RTC commands with BCD output
	cpi	temp, 0x20
	brlo	CSP_RTC_WRITE_VAL ; 0x0f - 0x20 = RTC commands with hex output
	cpi	temp, 0x28
	brlo	CSP_VIDEO_CMD ; 0x20 - 0x27 = VIDEO commands
	tcbe	0x33, CSP_SD_INIT ; init SD type
	tcbe	0x3f, CSP_SPI_SELECT ; Send SPI SELECT for 100ms
	ret

CSP_SPI_SELECT:
	;!!!!! write code here!!!!!!
	ret

CSP_VIDEO_CMD:
	rjmp	CSP_VIDEO_CMD_DO

CSP_RTC_WRITE_BCD:
	ori	temp, 0x80	; write to register flag
        sts	CDATA+2, temp
        lds	temp, CDATA
        sts	CDATA+3, temp   ; data to write
        rjmp	CPU_RTC_READ	; write port from RTC and return

CSP_RTC_WRITE_VAL:
	subi	temp, 0x0f
        push	temp
        lds	temp, CDATA
	call	HEX_to_BCD      ; convert to hex
	sts	CDATA, temp
	pop	temp
	rjmp    CSP_RTC_WRITE_BCD

CSP_SD_INIT:
	jmp	SD_INIT

; access RTC register
CPU_RTC_READ:
	SPI_INIT SPI_SLAVE_RTC, SPI_FCK_DIV_16		; /16, RTC supports fck till 2 MHz
	SPI_SELECT
	lds	temp, CDATA+2
	call	DOSPI			; address
	lds	temp, CDATA+3
	call	DOSPI			; address
	SPI_STOP
	ret

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

; special video command processing
CSP_VIDEO_CMD_DO:
	subi	temp, 0x20
	breq	CSP_VIDEO_CMD_EXEC

	; store data for future use
	pushw	X
	ldi	XH, high(SV_DATABLOCK)
	ldi	XL, low(SV_DATABLOCK)
	add	XL, temp
	adc	XH, zero
	lds	temp, CDATA
	st	X, temp
	popw	X
	ret

CSP_VIDEO_CMD_EXEC:
	pushw	X
	pushw	Y
	pushw	Z
	push	zzA
	push	zzC
	lds	temp, CDATA
	tcbe	0x00, CSP_V0 	; vram -> svram
	tcbe	0x01, CSP_V1 	; svram -> vram
	tcbe	0x02, CSP_V2 	; svram -> crt
	tcbe	0x03, CSP_V3 	; clr svram
	tcbe	0x04, CSP_V4 	; fill svram froom mem
	tcbe	0x05, CSP_V5 	; mask svram (vram->crt)
	tcbe	0x06, CSP_V6 	; mask svram (vram->crt)
	tcbe	0x07, CSP_V7 	; fill svram (data->svram)
	tcbe	0x08, CSP_V8	; make svram transparent (spaces->0)
	tcbe	0x09, CSP_V9	; swap blocks

;	tcbe	0x0a, CSP_Va	; text out from RAM

	tcbe	0x0e, CSP_V10	; draw window to vram
	tcbe	0x0f, CSP_V10	; draw window to svram
	tcbe	0x10, CSP_V10	; draw window to crt

CSP_VIDEO_END:
	pop	zzC
	pop	zzA
	popw	Z
	popw	Y
	popw	X
	ret

	; vram->svram
CSP_V0: ldiw	Z, CSP_V0_CB
	rjmp	CSP_V_STD
CSP_V0_CB:
	LDRAM	YH, YL, temp
	st	X, temp
	ret

	; svram->vram
CSP_V1: ldiw	Z, CSP_V1_CB
	rjmp	CSP_V_STD
CSP_V1_CB:
        ld	temp, X
        cpi	temp, 0		; skip zeros
        breq	CSP_V1_CB_l1
	STRAM	YH, YL, temp
CSP_V1_CB_l1:
	ret

	; svram->crt
CSP_V2: ldiw	Z, CSP_V2_CB
	rjmp	CSP_V_STD
CSP_V2_CB:
        ld	temp, X
        cpi	temp, 0		; skip zeros
        breq	CSP_V2_CB_l1
	call	CRTOUT_Y_X	
CSP_V2_CB_l1:
	ret

	; clr svram
CSP_V3: ldiw	Z, CSP_V3_CB
	rjmp	CSP_V_STD
CSP_V3_CB:
        st	X, zero
	ret

CSP_V4:	; fill svram from mem
	push	zzPCh
	push	zzPCl
	lds	zzPCl, SV_PTR
	lds	zzPCh, SV_PTR+1	; start of RAM buffer
	ldiw	Z, CSP_V4_CB
	call	CSP_V_STD
	pop	zzPCl
	pop	zzPCh
CSP_V4_CB:
	LDRAM_PC temp
	st	X, temp
	ret

	; mask svram (vram->crt)
CSP_V5: ldiw	Z, CSP_V5_CB
	rjmp	CSP_V_STD
CSP_V5_CB:
        ld	temp, X
        cpi	temp, 0		; skip zeros
        breq	CSP_V5_CB_l1
        LDRAM	YH, YL, temp
	call	CRTOUT_Y_temp
CSP_V5_CB_l1:
	ret

; !!!!!! write V6 here !!!!!!!!
CSP_V6:	; send block from mem to crt
	push	zzPCh
	push	zzPCl
	lds	zzPCl, SV_PTR
	lds	zzPCh, SV_PTR+1	; start of RAM buffer
	ldiw	Z, CSP_V6_CB
	call	CSP_V_STD
	pop	zzPCl
	pop	zzPCh
CSP_V6_CB:
	LDRAM_PC temp
	call	CRTOUT_Y_temp
	ret

	; fill svram (data->svram)
CSP_V7: ldiw	Z, CSP_V7_CB
	rjmp	CSP_V_STD
CSP_V7_CB:
        lds	temp, SV_DATA
        st	X, temp		; fill with
CSP_V7_CB_l1:
	ret

	; make svram transparent (spaces->0)
CSP_V8: ldiw	Z, CSP_V8_CB
	rjmp	CSP_V_STD
CSP_V8_CB:
        ld	temp, X
        cpi	temp, 0x20	; skip zeros
        brne	CSP_V8_CB_l1
        st	X, zero		; replace space with 0
CSP_V8_CB_l1:
	ret

CSP_V9:	; swap blocks
	pushw	X
	pushw	Y
	push	zzA
	push	zzC
CSP_V9_l1:
	ldiw	X, SV_DATABLOCK
	ldiw	Y, SV_S_DATABLOCK
	ldi	temp, 8
	ld	zzA, X
	ld	zzC, Y
	st	X+, zzC
	st	Y+, zzA
	dec	temp
	brne	CSP_V9_l1
	pop	zzC
	pop	zzA
	popw	Y
	popw	X
	ret

	; frame window to crt
CSP_V10:
	sts	HW_DATA, temp	; command to do
	ldiw	Z, CSP_V10_CB
	rjmp	CSP_V_STD
CSP_V10_CB:
	cp	zzC, zzH
	breq	CSP_V10_CB_l_1
	cp	zzH, one
	breq	CSP_V10_CB_l_e

	cp	zzA, zzL
	breq	CSP_V10_CB_l_m1
	cp	zzL, one
	breq	CSP_V10_CB_l_m1
	ldi	temp, ' '      ; space
	rjmp	CSP_V10_CB_l_out	

CSP_V10_CB_l_1:	; 1st line
	cp	zzA, zzL
	breq	CSP_V10_CB_l_11
	cp	zzL, one
	breq	CSP_V10_CB_l_1e
	ldi	temp, 0xcd      ; =
	rjmp	CSP_V10_CB_l_out	
CSP_V10_CB_l_11:
	ldi	temp, 0xc9      ; ,,=
	rjmp	CSP_V10_CB_l_out	
CSP_V10_CB_l_1e:
	ldi	temp, 0xbb      ; =,,
	rjmp	CSP_V10_CB_l_out	

CSP_V10_CB_l_E:	; LAST line
	cp	zzA, zzL
	breq	CSP_V10_CB_l_e1
	cp	zzL, one
	breq	CSP_V10_CB_l_ee
	ldi	temp, 0xcd      ; =
	rjmp	CSP_V10_CB_l_out	
CSP_V10_CB_l_e1:
	ldi	temp, 0xc8      ; "=
	rjmp	CSP_V10_CB_l_out	
CSP_V10_CB_l_ee:
	ldi	temp, 0xbc      ; ="
	rjmp	CSP_V10_CB_l_out	

CSP_V10_CB_l_m1:
	ldi	temp, 0xba      ; ||
	rjmp	CSP_V10_CB_l_out	

CSP_V10_CB_l_out:
	lds	temp, HW_DATA
	cpi	temp, 0x10
	brne	CSP_V10_CB_l_out_l1
	call	CRTOUT_Y_temp
	ret
CSP_V10_CB_l_out_l1:
	cpi	temp, 0x0e
	brne	CSP_V10_CB_l_out_l2
	STRAM	YH, YL, temp
	ret
CSP_V10_CB_l_out_l2:
	cpi	temp, 0x0d
	brne	CSP_V10_CB_l_out_l3
	st	X, temp
	ret
CSP_V10_CB_l_out_l3:
	ret


; standard routime passes thru all bytes, calls callback in Z, address in svram - X, in ram - Y
CSP_V_STD:
        push	zzH
        push	zzL
        lds	zzL, SV_X2
        lds	zzH, SV_Y2      ; right corner
	ldiw	X, SV_X1	; left corner
	sub	zzL, XL		; bytes to transfer
	sub	zzH, XH		; lines to transfer
	mov	zzC, zzH	; lines - store
	mov	zzA, zzL	; bytes in line - store
	call	XY_to_PTR	; X -> svram x1,y1
CSP_V0_l3:
	pushw	X
	movw	Y, X
	ldi	temp, 0xf7
	add	YH, temp	; Z -> RAM
	mov	zzL, zzA
CSP_V0_l1:
	icall			; call call-back
	adiw	X, 1
	adiw	Y, 1
	dec	zzL              ; check x counter
	brne	CSP_V0_l1
	dec	zzH              ; check lines conter
	breq	CSP_V0_l2
	popw	X
	adiw	X, 40
	adiw	X, 40		; goto nex line
	rjmp	CSP_V0_l3
CSP_V0_l2:
	pop	zzL
	pop	zzH
	rjmp	CSP_VIDEO_END


; converts (X),(X+1) to 0100... pointer
XY_to_PTR:
	ld	temp, X+
	push	temp
	ld	temp, X
	push	r0
	push	r1
	push	zzA
	ldi	zzA, 80
	mul	temp, zzA
	mov	XL, r0
	mov	XH, r1
	pop	temp
	add	XL, temp
	adc	XH, one
	pop	zzA
	pop	r1
	pop	r0
	ret

;out to crt (X) to position Y
CRTOUT_Y_X:
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4		
	SPI_SELECT
	mov	temp, YL
	call	DOSPI
	delay3	15		;!!!! decrease!!!!
	mov	temp, YH
	call	DOSPI
	delay3	15              ;!!!! decrease!!!!
        ld	temp, X
	call	DOSPI
	SPI_STOP
	ret

;out to crt (X) to position Y
CRTOUT_Y_temp:
	push	temp
	SPI_INIT SPI_SLAVE_CPD, SPI_FCK_DIV_4		
	SPI_SELECT
	mov	temp, YL
	call	DOSPI
	delay3	15		;!!!! decrease!!!!
	mov	temp, YH
	call	DOSPI
	delay3	15              ;!!!! decrease!!!!
        pop	temp
	call	DOSPI
	SPI_STOP
	ret

*/