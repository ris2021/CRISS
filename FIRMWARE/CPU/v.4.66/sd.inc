SD_INIT:
	jmp	_SD_INIT
SD_READ:
	jmp	_SD_READ
SD_READ_DO:
	jmp	_SD_READ_DO
SD_WRITE:
	jmp	_SD_WRITE
SD_WRITE_DO:
	jmp	_SD_WRITE_DO
SD_LAST_RESET:
	sts	SD_LASTADDRESS+3, FF
	sts	SD_LASTADDRESS+2, FF
	sts	SD_LASTADDRESS+1, FF
	sts	SD_LASTADDRESS+0, FF
        ret

.MACRO  SD_CMD
        ldi     ZH, high((@0)*2)
        ldi     ZL, low((@0)*2)
        call	SD_EXEC_CMD
.ENDM

; init timeout timer, time in ms
.MACRO  SD_INTT_TIMER
        push   	temp
        ldi	temp, ((@0)*76/1000)
        sts	OCR1AH, temp
        sts	OCR1AL, zero
        sts	TCNT1H, zero
        sts	TCNT1L, zero
        sbi	TIFR1, OCF1A  ; clear oc1a flag
        pop	temp
.ENDM

; send SD single command, retry till timeout
.MACRO  SD_S_CMD
;        call  SD_WAKEUP
;        SPI_INIT SPI_SLAVE_SD, SPI_FCK_DIV_16
        SPI_SELECT
        SD_INTT_TIMER  @0      		; timeout
SD_I_L1:
        SD_CMD  @1
        sbic    TIFR1, OCF1A      	
        rjmp    @2                      ; timeout occured
        sbrc    temp, 7
        rjmp    SD_I_L1

        SPI_DESELECT
;        SPI_STOP
.ENDM

; send SD single command, retry till timeout
.MACRO  SD_S_CMD_E
;        call  SD_WAKEUP
;        SPI_INIT SPI_SLAVE_SD, SPI_FCK_DIV_16
        SPI_SELECT
        SD_INTT_TIMER  @0      		; timeout
SD_I_L1:
        SD_CMD  @1
        sbic    TIFR1, OCF1A      	
        rjmp    @2                      ; timeout occured
;        sbrc    temp, 7
;        rjmp    SD_I_L1

	cpi	temp, @3
	brne	SD_I_L1

        SPI_DESELECT
;        SPI_STOP
.ENDM


; send SD A command, retry till timeout
.MACRO  SD_A_CMD
;        call  SD_WAKEUP
;        SPI_INIT SPI_SLAVE_SD, SPI_FCK_DIV_16
        SPI_SELECT
        SD_INTT_TIMER    @0      	; timeout
SD_I_L1:
        SD_CMD  CMD55
        sbic    TIFR1, OCF1A      	; timeout occured
        rjmp    @2
        cpi     temp, 1
        brne    SD_I_L1

SD_I_L2:
        SD_CMD  @1
        sbic    TIFR1, OCF1A      	; timeout occured
        rjmp    @2
        cpi     temp, 0
        brne    SD_I_L1

        SPI_DESELECT
;        SPI_STOP
.ENDM


; ------------------------------------------------  initial reset
SD_WAKEUP:        
        ldi	temp, 0xff
        call	DOSPI
        ldi	temp, 0xff
        call	DOSPI
        ldi	temp, 0xff
        call	DOSPI
        ldi	temp, 0xff
        call	DOSPI
        ldi	temp, 0xff
        call	DOSPI
        ldi	temp, 0xff
        call	DOSPI
        ldi	temp, 0xff
        call	DOSPI
        ldi	temp, 0xff
        call	DOSPI
        ldi	temp, 0xff
        call	DOSPI
        ldi	temp, 0xff
        call	DOSPI
        ret

; ------------------------------------------------  INIT SD CARD
_SD_INIT:        

	; reset base addresses for disks
	pushw	Z
	ldi	temp, 1
	ldiw	Z, SD_FDD_BASE
SD_BASE_L1:
	st	Z+, temp
	inc 	temp
	cpi	temp, 17
	brne	SD_BASE_L1
	popw	Z

	; setup timeout timer
        ldi     temp, (1<<CS12)|(1<<CS10)  	; fclk/1024 
        sts     TCCR1B, temp 			; start timer

        SPI_INIT SPI_SLAVE_SD, SPI_FCK_DIV_16
        call	SD_WAKEUP                       ; 80 pulses to start

        sts	SD_RSP, zero
        sts	SD_RSP+1, zero
        sts	SD_RSP+2, zero
        sts	SD_RSP+3, zero

        sts	SD_TYPE, zero

;__l1:   SD_S_CMD 500, CMD00, __l1		; DEBUG!!!!
        SD_S_CMD 500, CMD00, SD_INIT_END	; GO_IDLE_STATE

        SD_S_CMD 700, CMD08, SD_INIT_END        ; SEND_IF_COND

	sts	SD_TYPE, temp			; store card type: 1 = SD2, 4 or 5 = SD1, error otherwise

	tcbe	0x01, SD_START_OK
	tcbe	0x04, SD_START_OK
	tcbe	0x05, SD_START_OK

;        cpi     temp, 0x01
;	breq    SD_SD2				; SD type 2

;	cpi     temp, 0x04
;	breq    SD_SD1				; unknown command == SD type 1
;	cpi     temp, 0x05
;	breq    SD_SD1				; unknown command == SD type 1

	sts	SD_TYPE, zero			; No valid SD card present
	rjmp    SD_INIT_END        		; ERROR = no valid card

SD_START_OK:
        SD_S_CMD 200, CMD58, SD_INIT_END        ; SEND_IF_COND
        SD_A_CMD 1000, ACMD41, SD_INIT_END	; SD_SEND_OP_COND
        SD_S_CMD 200, CMD58, SD_INIT_END        ; SEND_IF_COND
	lds	temp, SD_RSP
	sts	SD_CCS, temp			; store for CCS bit
;        SD_A_CMD 500, ACMD410, SD_INIT_END	; SD_SEND_OP_COND
        rjmp    SD_INIT_OK
/*
SD_SD1:
        SD_S_CMD 200, CMD58, SD_INIT_END        ; SEND_IF_COND
        SD_A_CMD 500, ACMD410, SD_INIT_END	; SD_SEND_OP_COND
        rjmp    SD_INIT_OK

SD_SD2:
        SD_S_CMD 200, CMD58, SD_INIT_END        ; SEND_IF_COND
        SD_A_CMD 1000, ACMD41, SD_INIT_END	; SD_SEND_OP_COND
;        ldi	temp, 0x42
        rjmp    SD_INIT_OK
*/
; SD init OK
SD_INIT_OK:

; SD init Failed
SD_INIT_END:
        SPI_STOP
        sts   	TCCR1B, zero

        rjmp	SD_LAST_RESET

;	sts	SD_LASTADDRESS+3, FF
;	sts	SD_LASTADDRESS+2, FF
;	sts	SD_LASTADDRESS+1, FF
;	sts	SD_LASTADDRESS, FF
 
;       ret
; -----------------------------------------------------------------------------------------------------




; read from SD card -----------------------------------------------------------------------------------
_SD_READ:
	call	SD_INIT
	cpi	temp, 0x00
	breq	_SD_READ_DO
	ldi	temp, 0xff			; error code
	ret

_SD_READ_DO:
	pushw	X
	push	r19

	lds	temp, SD_ADDRESS+3 
	sts	SD_LASTADDRESS+3, temp
	lds	temp, SD_ADDRESS+2 
	sts	SD_LASTADDRESS+2, temp
	lds	temp, SD_ADDRESS+1 
	sts	SD_LASTADDRESS+1, temp
	lds	temp, SD_ADDRESS 
	sts	SD_LASTADDRESS, temp		; storing last access address

	lds	temp, SD_CCS
	sbrs	temp, 6				; CCS bit from OCR register
	call	SD_ADDRESS_SHIFT                ; Not HDC card, address translation required

	NOTIFYt NOTIFY_SD, 'r'

SD_READ_L1:
        ldi     temp, (1<<CS12)|(1<<CS10)  	; fclk/1024 
        sts     TCCR1B, temp 			; start timer

        SPI_INIT SPI_SLAVE_SD, SPI_FCK_DIV_16
        SPI_SELECT

	ldi	temp, 0x40+17			; read command
	call	DOSPI
	lds	temp, SD_ADDRESS+3 
	call	DOSPI
	lds	temp, SD_ADDRESS+2
	call	DOSPI
	lds	temp, SD_ADDRESS+1
	call	DOSPI
	lds	temp, SD_ADDRESS+0
	call	DOSPI
	ldi	temp, 0xff			; CRC
	call	DOSPI

	; read R1 response
        ldi	r19, 255
SD_READ_L2:
        ldi     temp, 0xff
        call    DOSPI
        sbrs    temp, 7
        rjmp    SD_READ_L3             		; response received
        dec     r19
        brne    SD_READ_L2
SD_READ_L3:
	NOTIFYt NOTIFY_SD, 'b'
        
        cpi	temp, 0
        breq	SD_READ_L4

;        ldi	temp, 0xfe			; error code
        rjmp	SD_READ_END

	; waiting for 0xfe
SD_READ_L4:
	SD_INTT_TIMER 1000
SD_READ_L5:
        ldi     temp, 0xff
        call    DOSPI
        cpi	temp, 0xfe
        breq	SD_READ_L6
        sbic    TIFR1, OCF1A      	
        rjmp    SD_READ_ERR             	; timeout - error
        rjmp	SD_READ_L5

SD_READ_L6:
	ldi	XL, low(SD_BUF)
	ldi	XH, high(SD_BUF)
SD_READ_L7:
        ldi     temp, 0xff
        call    DOSPI
	st	X+, temp
;	adiw	X, 1
	cpi	XL, low(SD_BUF_END)
	ldi	temp, high(SD_BUF_END)
	cpc	XH, temp
	brlo	SD_READ_L7			; read 512 bytes

;	jmp	SD_READ_END

        ldi     temp, 0xff
        call    DOSPI
        ldi     temp, 0xff
        call    DOSPI				; read CRC

        ldi	temp, 0
        rjmp	SD_READ_END			; OK, exiting

SD_READ_ERR:
	ldi	temp, 0xfd			; error code

SD_READ_END:
	SPI_STOP
        sts   	TCCR1B, zero

        sts	SD_ERROR, temp
	clr	temp				;!!! DEBUG !!!!! doesn't report error to CPM

        pop	r19
	popw	X
	ret
; -----------------------------------------------------------------------------------------------------




; write to SD card ------------------------------------------------------------------------------------
_SD_WRITE:
	call	SD_INIT
	cpi	temp, 0x00
	breq	_SD_WRITE_DO
	ldi	temp, 0xff			; error code
	ret

_SD_WRITE_DO:
	pushw	X
	push	r19

	lds	temp, SD_ADDRESS+3 
	sts	SD_LASTADDRESS+3, temp
	lds	temp, SD_ADDRESS+2 
	sts	SD_LASTADDRESS+2, temp
	lds	temp, SD_ADDRESS+1 
	sts	SD_LASTADDRESS+1, temp
	lds	temp, SD_ADDRESS 
	sts	SD_LASTADDRESS, temp		; storing last access address

	lds	temp, SD_CCS
	sbrs	temp, 6				; CCS bit from OCR register
	call	SD_ADDRESS_SHIFT                ; Not HDC card, address translation required

	NOTIFYt NOTIFY_SD, 'w'

        ldi     temp, (1<<CS12)|(1<<CS10)  	; fclk/1024 
        sts     TCCR1B, temp 			; start timer

        SPI_INIT SPI_SLAVE_SD, SPI_FCK_DIV_16
        SPI_SELECT

	ldi	temp, 0x40+24			; single block write command
	call	DOSPI
	lds	temp, SD_ADDRESS+3 
	call	DOSPI
	lds	temp, SD_ADDRESS+2
	call	DOSPI
	lds	temp, SD_ADDRESS+1
	call	DOSPI
	lds	temp, SD_ADDRESS+0
	call	DOSPI
	ldi	temp, 0xff			; CRC
	call	DOSPI

	; read R1 response
        ldi	r19, 255
SD_WRITE_L2:
        ldi     temp, 0xff
        call    DOSPI
        sbrs    temp, 7
        rjmp    SD_WRITE_L3            		; response received
        dec     r19
        brne    SD_WRITE_L2

SD_WRITE_L3:
	NOTIFYt NOTIFY_SD, 'b'

        cpi	temp, 0
        breq	SD_WRITE_L5

        rjmp	SD_WRITE_END                    ; temp = error code

SD_WRITE_L5:
        ldi     temp, 0xfe			; data start token
        call    DOSPI
SD_WRITE_L6:
	ldi	XL, low(SD_BUF)
	ldi	XH, high(SD_BUF)
SD_WRITE_L7:
	ld	temp, X+
        call    DOSPI
	cpi	XL, low(SD_BUF_END)
	ldi	temp, high(SD_BUF_END)
	cpc	XH, temp
	brlo	SD_WRITE_L7			; send 512 bytes

        ldi     temp, 0xff
        call    DOSPI
        ldi     temp, 0xff
        call    DOSPI				; send CRC

	; waiting for the response
	SD_INTT_TIMER 1000
SD_WRITE_L8:
        ldi     temp, 0xff
        call    DOSPI
        sbrs	temp, 4   			; Resp: 00101 = ok, 01011 - crc error, 01101 - write error
        rjmp	SD_WRITTEN
        sbic    TIFR1, OCF1A      	
        rjmp    SD_WRITE_ERR             	; timeout - error
        rjmp	SD_WRITE_L8

SD_WRITTEN:

	NOTIFYt NOTIFY_SD, 'c'
	
	andi	temp, 0x0e
	cpi	temp, 0x04
	brne	SD_WRITE_ERR			; write error

	; waiting for the busy state expires
	SD_INTT_TIMER 1000
SD_WRITE_L9:
        ldi     temp, 0xff
        call    DOSPI
        cpse	temp, zero   			; Resp: 0 = busy, ff = completed
        rjmp	SD_WRITTEN2
        sbic    TIFR1, OCF1A      	
        rjmp    SD_WRITE_ERR             	; timeout - error
        rjmp	SD_WRITE_L9

SD_WRITTEN2:
	NOTIFYt NOTIFY_SD, 'd'

        ldi	temp, 0
        ;!!!! add write check (CMD13) command execution !!!
        rjmp	SD_WRITE_END			; OK, exiting

SD_WRITE_ERR:
	ldi	temp, 0xfd			; error code

SD_WRITE_END:
	SPI_STOP
        sts   	TCCR1B, zero

        sts	SD_ERROR, temp
	clr	temp				;!!!!! DEBUG !!!!! doesn't report error to CPM

        pop	r19
	popw	X
	ret
; -----------------------------------------------------------------------------------------------------


; SD-card Library SUBROUTINES


; ----------------- address << 9 ------------------------------------------
SD_ADDRESS_SHIFT:
	push	temp
	lds	temp, SD_ADDRESS+2
	sts	SD_ADDRESS+3, temp
	lds	temp, SD_ADDRESS+1
	sts	SD_ADDRESS+2, temp
	lds	temp, SD_ADDRESS
	sts	SD_ADDRESS+1, temp
	sts	SD_ADDRESS, zero		; <<8

	lds	temp, SD_ADDRESS+1
	lsl	temp
	sts	SD_ADDRESS+1, temp
	lds	temp, SD_ADDRESS+2
	rol	temp
	sts	SD_ADDRESS+2, temp
	lds	temp, SD_ADDRESS+3
	rol	temp
	sts	SD_ADDRESS+3, temp		; <<1

	pop 	temp            		
	ret


; ----------------------------------- execute prepared command, address in Z
SD_EXEC_CMD:
        push	r18
        push	r19

        elpm	r18, Z+            	; get number of retries
SDE_L4:
        ; send command
        elpm	temp, Z+
        call    DOSPI
        elpm    temp, Z+
        call    DOSPI
        elpm    temp, Z+
        call    DOSPI
        elpm    temp, Z+
        call    DOSPI
        elpm    temp, Z+
        call    DOSPI
        elpm    temp, Z+
        call    DOSPI

        elpm    r19, Z+			; get number of chars to wait response
SDE_L2:
        ldi     temp, 0xff
        call    DOSPI
        sbrs    temp, 7
        rjmp    SDE_L1             	; response received
        dec     r19
        brne    SDE_L2

        sbiw    Z, 7      		; rewind pointer
        dec     r18
        brne    SDE_L4

        rjmp    SDE_END

        ; response received, read additional data if any
SDE_L1: 
        cpi	temp, 2			; skip additional data if error
        brsh    SDE_END

        elpm	r19, Z+
        or      r19, r19    		; =0?
        breq    SDE_END
        push    temp            	; save temp
        push    XL            	
        push    XH
        ldi	XH, high(SD_RSP)            	
        ldi	XL, low(SD_RSP)            	
SDE_L3:
        ldi     temp, 0xff
        call    DOSPI      		; read response
        st	X+, temp
        dec     r19
        brne    SDE_L3

        pop	XH
        pop	XL
        pop     temp			; restore temp = R1 response

SDE_END:
	push 	temp
        ldi	r19, 128		; dummy FFs to let SD card time to prepare itself
SDE_L5:
        ldi     temp, 0xff
        call    DOSPI      		
        dec     r19
        brne    SDE_L5
	pop 	temp

        pop     r19
        pop     r18
        ret


; -------------------------------------- COMMANDS ------------------------------------------------------------

.EQU	SD_R0	= 0
.EQU	SD_R2	= 1
.EQU	SD_R7	= 4
.EQU	SD_R3	= 4

       ; number of retries, ;timeout value (OCRH=n/76 s), 5*data, chars wait responce, length of valid response, 
CMD00:  	.DB    32,  0x40+0 , 0x00, 0x00, 0x00, 0x00, 0x95, 255, SD_R0, 0
CMD08:  	.DB    4,   0x40+8 , 0x00, 0x00, 0x01, 0xaa, 0x87, 255, SD_R7, 0
CMD13:  	.DB    128, 0x40+13, 0x00, 0x00, 0x00, 0x00, 0x87, 255, SD_R2, 0
CMD01:  	.DB    128, 0x40+1 , 0x00, 0x00, 0x00, 0x00, 0x87, 255, SD_R0, 0
CMD55:  	.DB    128, 0x40+55, 0x00, 0x00, 0x00, 0x00, 0x87, 255, SD_R0, 0
CMD58:  	.DB    16,  0x40+58, 0x00, 0x00, 0x00, 0x00, 0x87, 255, SD_R3, 0
ACMD41:  	.DB    128, 0x40+41, 0x40, 0x00, 0x00, 0x00, 0x87, 255, SD_R0, 0
ACMD410: 	.DB    128, 0x40+41, 0x00, 0x00, 0x00, 0x00, 0x87, 255, SD_R0, 0
