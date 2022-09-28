.MACRO	CHECK_TWSR
        lds	tdata, TWSR		; check error
	andi 	tdata, 0xF8		; mask prescaler
        cpi	tdata, @0		; check valid responce
        breq	_l0
        rjmp	TWI_ERROR
_l0:
.ENDM

.MACRO	CHECK_TWSR_tdata
        lds	ZH, TWSR		; check error
	andi 	ZH, 0xF8		; mask prescaler
        cp	tdata, ZH		; check valid responce
        breq	_l0
        mov	tdata, twistat		; for error code reporting
        rjmp	TWI_ERROR
_l0:
	ldi	ZH, high(mpbuf)		; restore ZH value
.ENDM
        
        ; TWI GPIO routines

	; check request
	lds	temp, twcmd
	andi	temp, 0xf0		; check CMD
;	cpi	temp, 2			; 0 = ready, 1 = error
	brne	TWI_CMD			; CMD must not be = 0!
TWI_GO_EXTT:
	rjmp	TWI_EXIT		; nothing to do

	
TWI_CMD:
	cpi	temp, 0xf0		; system request?
	breq	TWI_CMD_Fx
	cpi	temp, 0xe0		; mouse?
	breq	TWI_CMD_Ex
	rjmp	TWI_CMD_I2C


	; ----------------- SYSTEM: RESET, ... ------------
TWI_CMD_Fx:
	lds	temp, twcmd
	cpi	temp, 0xfe		; RESET TWI line
	breq	TWI_FE	
	cpi	temp, 0xfd		; Extended TWI mode
	breq	TWI_FD	
TWI_CMD_Fx_OK:
	sts	twcmd, zero
	rjmp	TWI_EXIT		; nothing to do

TWI_FD: 
	rjmp	TWI_I2C_PRO		; PRO mode

TWI_FE:
	sts	twcmd, zero		; done

TWI_RESET:
;	sts	twdti, zero		; store ststus code
;	sts	twcmd, zero		; indicate error state
	mov	twistat, zero
	ldi	temp, 0x80		; clear INT flag if any
	sts	TWCR, temp		; reset TWI interface
	sts	TWSR, zero
	cbi	DDRC, PC4
	cbi	DDRC, PC5
	cbi	PORTC, PC4
	cbi	PORTC, PC5		; release pins
;	rjmp	TWI_CMD_Fx_OK		; exit
	rjmp	TWI_EXIT		; exiting


	; ----------------- MICE ---------------------------
TWI_CMD_Ex:
	lds	temp, twcmd
	cpi	temp, 0xe0		; INIT mouse
	breq	TWI_E0	
	cpi	temp, 0xe1		; READ mouse
	breq	TWI_E1	
	cpi	temp, 0xe2		; HW RESET mouse
	breq	TWI_E2	
	cpi	temp, 0xe4		; STOP mouse
	breq	TWI_E4	
;TWI_CMD_Ex_DONE:
	sts	twcmd, zero
	rjmp	TWI_EXIT		; nothing to do

TWI_CMDEx_OK:
	mov	twistat, zero		; clear status
	brne	TWI_CMDEx_OK_OK		; if z flag is set == error has occured
TWI_CMDEx_ERR:
	ldi	temp, 1
	sts	twcmd, temp		; indicate error flag
	sts	twdti, tdata		; report result
	rjmp	TWI_EXIT		; exit
TWI_CMDEx_OK_OK:
	sts	twcmd, zero
	sts	twdti, tdata		; report result
	rjmp	TWI_EXIT		; exit
TWI_E0:
	jmp	MICE_INIT		; init mouse
TWI_E0_INIT_DONE:
;	breq	TWI_CMDEx_OK		; error
	lds	temp, sysrq
	sbr	temp, 0b01100000	; set mouse on flag + set mouse led flag
	sts	sysrq, temp 		; clear request flag, processing/processed
	clz
	rjmp	TWI_CMDEx_OK
TWI_E1:
	jmp	MICE_READ		; read state
TWI_E2:
	jmp	MICE_FF			; Reset mouse
TWI_E4:
	lds	temp, sysrq
	cbr	temp, 0b01000000	; clear mouse on flag
	sbr	temp, 0b00100000	; set mouse set led
	sts	sysrq, temp 		; clear request flag, processing/processed
	jmp	MICE_STOP		; STOP mouse


	; ----------------- I2C DEVICE -------------------------
TWI_CMD_I2C:
	cpse	twistat, zero
	rjmp	TWI_EXEC		; there is an active command

;TWI_CMD3:
	ldi	temp, 1<<3		; START request
        mov	twistat, temp
	rjmp	TWI_EXEC_DO

	; start command execution

TWI_EXEC:
	mov	temp, twistat
	andi	temp, 0xc0		; timeout counter
	cpi	temp, 0xc0 		; timeout state?
	brne	TWI_EXEC_NO_TOMEOUT
	rjmp	TWI_TIMEOUT

TWI_EXEC_NO_TOMEOUT:
	lds	temp, TWCR
	sbrs	temp, TWINT		; TWINT is set - do next command
	rjmp	TWI_EXIT		; continue otherwise

TWI_EXEC_DO:
;	mov	temp, twistat		; 3 = START
					; 2 = SLA
					; 1 = DATA
					; 0 = STOP
	lds	temp, twcmd

TWI_b3:
	sbrs	twistat, 3		; START?
	rjmp	TWI_b2                  ; NO
TWI_b3_start:
	ldi	tdata, (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
;	sts	TWCR, tdata		; START condition
	rjmp	TWI_out


TWI_b2:
	sbrs	twistat, 2		; SLA?
	rjmp	TWI_b1                  ; NO

        lds	tdata, TWSR		; check error
	andi 	tdata, 0xF8		; mask prescaler
        cpi	tdata, 0x08		; A START condition has been transmitted
        breq	TWI_b2_do
        rjmp	TWI_ERROR
TWI_b2_do:

;	lds	tdata, twcmd
;	sts	TWDR, tdata		; SLA + R/W
	sts	TWDR, temp		; SLA + R/W
	ldi	tdata, (1<<TWINT)|(1<<TWEN)
;	sts	TWCR, tdata		; execute
	rjmp	TWI_out

TWI_b1:
	sbrs	twistat, 1		; DATA?
	rjmp	TWI_b0                  ; NO

        lds	tdata, TWSR		; check error
	andi 	tdata, 0xF8		; mask prescaler
;	lds	temp, twcmd
	sbrs	temp, 0			; check is it read or write request
	rjmp	TWI_b1_write
TWI_b1_read:
        cpi	tdata, 0x40		; SLA+R has been transmitted; ACK has been received
        breq	TWI_b1_do_read
        rjmp	TWI_ERROR
TWI_b1_do_read:
	ldi	tdata, (1<<TWINT)|(1<<TWEN)
;	sts	TWCR, tdata		; execute
	rjmp	TWI_out

TWI_b1_write:
        cpi	tdata, 0x18		; SLA+W has been transmitted; ACK has been received
        breq	TWI_b1_do_write
        rjmp	TWI_ERROR
TWI_b1_do_write:
	lds	tdata, twdti		; 
	sts	TWDR, tdata		; data for write
	ldi	tdata, (1<<TWINT)|(1<<TWEN)
;	sts	TWCR, tdata		; execute
	rjmp	TWI_out

TWI_b0:
;	sbrs	temp, 0                 ; STOP
;	rjmp	TWI_b			; NO

        lds	tdata, TWSR		; check error
	andi 	tdata, 0xF8		; mask prescaler

	sbrs	temp, 0			; check is it read or write request
	rjmp	TWI_b0_write
TWI_b0_read:
        cpi	tdata, 0x58		; Data byte has been received; NACK has been returned
        breq	TWI_b0_do_read
        rjmp	TWI_ERROR
TWI_b0_do_read:
	lds	tdata, TWDR		; 
	sts	twdti, tdata		; Store returned value
	rjmp	TWI_b0_do_stop

TWI_b0_write:
        cpi	tdata, 0x28		; Data byte has been transmitted; ACK has been received
        breq	TWI_b0_do_write
        rjmp	TWI_ERROR
TWI_b0_do_write:
	; nothing to do

TWI_b0_do_stop:
	;!!!!!!! check that STOP condition is succesfull ???? !!!!
	ldi	tdata, (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)	; STOP
;	sts	TWCR, tdata		; STOP condition
	sts	twcmd, zero		; set cmd executed!
;	rjmp	TWI_out

TWI_out:
	sts	TWCR, tdata		; Set TWI bus command

	ldi	temp, 0x3f
	and	twistat, temp		; clear timeout counter
	lsr	twistat			; twistat >>= 1 - go to next command
	rjmp	TWI_EXIT		; continue

TWI_TIMEOUT:
	ldi	tdata, 0xff		; timeout error code
TWI_ERROR:
	sts	twdti, tdata		; store status code
	ldi	tdata, 1		; bus error state
	sts	twcmd, tdata		; indicate error state
	rjmp	TWI_RESET		; reset bus
;	clr	twistat
;	sts	TWCR, zero		; reset interface
;	rjmp	TWI_EXIT		; exit

;TWI_DONE:
;	sts	twdti, tdata		; store result
;TWI_DONE2:;
;	sts	twcmd, zero
;	rjmp	TWI_EXIT		; exit


TWI_I2C_PRO:
	cpse	twistat, zero
	rjmp	TWI_PRO_EXEC		; is processing

					; first entrance
	ldi	temp, 0x10		; processing flag 
	mov	twistat, temp		; start processing
;	ldi	ZH, high(mpbuf)
;	ldi	ZL, 1			; pointer to read distanation
	rjmp	TWI_PRO_START		; first start executing

TWI_PRO_EXEC:
	mov	temp, twistat
	andi	temp, 0xc0		; timeout counter
	cpi	temp, 0xc0 		; timeout state?
	brne	TWI_PRO_NO_TOMEOUT
	rjmp	TWI_TIMEOUT		; timeout detected

TWI_PRO_NO_TOMEOUT:
	lds	temp, TWCR
	sbrs	temp, TWINT		; TWINT is set - do next command
	rjmp	TWI_EXIT		; continue otherwise

TWI_PRO_DO:
	mov	temp, twistat
	andi	temp, 0x3f		; clear timeout
	mov	twistat, temp

	sbrs	temp, 4			; overflow in commands - bit 4 goes clear
	rjmp	TWI_PRO_STOP		; force STOP condition

TWI_PRO_DO2:
	andi	temp, 0x0f		; counter only
	ldi	ZH, high(mpbuf)
	ldi	ZL, low(mpbuf)
	add	ZL, temp		; pointer to read distanation

;	sbrc	temp, 0			; data byte? skip read command
;	dec	ZL			; next to start command
        andi	ZL, 0xfe		; point to command/responce
	ld	tdata, Z+		; command to execute == responce expected

	cpi	tdata, 0x00		; END - STOP 
	breq	TWI_PRO_STOP
	cpi	tdata, 0x10		; RESTART - no responce check!
	breq	_TWI_PRO_l0
	cpi	tdata, 0x08		; RESTART - no responce check!
	breq	_TWI_PRO_l0

        lds	ZH, TWSR		; check error
	andi 	ZH, 0xF8		; mask prescaler
        cp	tdata, ZH		; check valid responce
        mov	tdata, ZH		; for error code reporting
	ldi	ZH, high(mpbuf)		; restore ZH value
        breq	_TWI_PRO_l0
        dec	ZL
        st	Z, tdata
        mov	tdata, twistat		; error pointer for error code reporting
        rjmp	TWI_ERROR
_TWI_PRO_l0:
	
	sbrc	temp, 0			; data byte? ceparate jumps table 
	rjmp	TWI_PRO_DO_CMD2

	cpi	tdata, 0x08
	breq	TWI_PRO_START
	cpi	tdata, 0x10
	breq	TWI_PRO_RESTART
	cpi	tdata, 0x18
	breq	TWI_PRO_WRITE
	cpi	tdata, 0x20
	breq	TWI_PRO_WRITE
	cpi	tdata, 0x28
	breq	TWI_PRO_WRITE
	cpi	tdata, 0x40
	breq	TWI_PRO_READ_RQ
	cpi	tdata, 0x50
	breq	TWI_PRO_READ_ACK
	cpi	tdata, 0x58
	breq	TWI_PRO_READ_NACK
_TWI_PRO_l1:
	rjmp	TWI_PRO_STOP		; any other command

TWI_PRO_DO_CMD2:
	cpi	tdata, 0x08
	breq	TWI_PRO_SLA
	cpi	tdata, 0x10
	breq	TWI_PRO_SLA
;	cpi	tdata, 0x40
;	breq	TWI_PRO_READ
;	cpi	tdata, 0x50
;	breq	TWI_PRO_READ
;	cpi	tdata, 0x58
;	breq	TWI_PRO_READ

	rjmp	TWI_PRO_STOP		; any other command

	; STOP condition
TWI_PRO_STOP:
	ldi	tdata, (1<<TWINT)|(1<<TWSTO)|(1<<TWEN)	; STOP
	sts	twdti, twistat		; step where process stopped
	sts	twcmd, zero		; set cmd successfully executed
	mov	twistat, zero		; clear processing variable
	sts	TWCR, tdata		; Set TWI bus command
	rjmp	TWI_EXIT		; continue

TWI_PRO_START:
	ldi	temp, 0x80		; clear INT flag if any
	sts	TWCR, temp		; reset TWI interface
	sts	TWSR, zero
TWI_PRO_RESTART:
	ldi	tdata, (1<<TWINT)|(1<<TWSTA)|(1<<TWEN)
	rjmp	TWI_PRO_END_1		; next step will send SLA

	; data read from slave - request after SLA
TWI_PRO_READ_RQ:
	ldi	tdata, (1<<TWINT)|(1<<TWEN)
	rjmp	TWI_PRO_END_2

	; data read from slave
TWI_PRO_READ_ACK:
	lds	tdata, TWDR		; 
;	dec	ZL
	st	Z, tdata		; Store returned value to previous cell
	rjmp	TWI_PRO_READ_RQ		; continue

	; data read from slave
TWI_PRO_READ_NACK:
	lds	tdata, TWDR		; 
;	dec	ZL
	st	Z, tdata		; Store returned value to previous cell
        inc	twistat			; go to next command
        inc	twistat			; go to next command
	rjmp	TWI_EXIT		; continue

	; after START/RESTART command
TWI_PRO_SLA:
	dec	twistat			; to ensure +2
TWI_PRO_WRITE:
	ld	temp, Z			; data to write
	sts	TWDR, temp		; data or SLA + R/W
	ldi	tdata, (1<<TWINT)|(1<<TWEN)
	rjmp	TWI_PRO_END_2

TWI_PRO_END_2: 
        inc	twistat
TWI_PRO_END_1: 
        inc	twistat
	sts	TWCR, tdata		; Set TWI bus command
	
	rjmp	TWI_EXIT		; continue
