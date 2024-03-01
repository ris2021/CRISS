	; external interrupts processing
EXTINTRPOC_RETI:				; entry point for reti
	sts	IRQ_CMD, zero
	rjmp	EXTINTRPOC_START
EXTINTRPOC:
	NOTIFY	NOTIFY_IRQ, DBG_IRQ
;	rjmp	_extint_exit

	DEC2	zzPCh, zzPCl			; restore oroginal PC for correct return
	sts	IRQ_CMD, one			; irq start

EXTINTRPOC_START:				; entry point
;	rjmp	_extint_exit;!!!! debug !!!!!

	; checking sources - CPD first

;	lds	temp, IRQ_CPD_FLAG		; process prevously stored first
	in	temp, GPIOR1

_extint_check_cpd_flags:			; GPIOR1
	sbrc	temp, IRQ_V_KBD
	rjmp	_extint_exec0
	sbrc	temp, IRQ_V_GPO
	rjmp	_extint_exec1
	sbrc	temp, IRQ_V_CTC
	rjmp	_extint_exec2
	sbrc	temp, IRQ_V_MUS
	rjmp	_extint_exec3
	sbrc	temp, IRQ_V_R1
	rjmp	_extint_exec4
	sbrc	temp, IRQ_V_R2
	rjmp	_extint_exec5
	sbrc	temp, IRQ_V_CTX
	rjmp	_extint_exec6
	sbrc	temp, IRQ_V_CRX
	rjmp	_extint_exec7

;	rjmp	_extint_exit;!!!! debug !!!!!

;_extint_l0:
	in	FROMRAM2, GPIOR0		; GPIOR0 = int requests for CPU
	lds	temp, INT_MASK+1		; interrupts from other devices
	and	temp, FROMRAM2

	sbrc	temp, IRQ_V_LAN 
	rjmp	_extint_exec8
	sbrc	temp, IRQ_V_CAN 
	rjmp	_extint_exec9
	sbrc	temp, IRQ_V_RTC
	rjmp	_extint_exec10
	sbrc	temp, IRQ_V_CPD
	rjmp	_extint_exec11
	sbrc	temp, IRQ_V_R4 
	rjmp	_extint_exec12
	sbrc	temp, IRQ_V_TTX
	rjmp	_extint_exec14
	sbrc	temp, IRQ_V_TRX
	rjmp	_extint_exec15
	sbrc	temp, IRQ_V_DEBUG 		; z80 debug is processing last
	rjmp	_extint_exec13

_extint_exit:
	out	GPIOR0, temp			; clear 
	; all requests are processed, return to normal operation
	ldi	temp, high(zOPCODE__LBLS_L)
	out	GPIOR2, temp			; GPIOR2 contains high pointer to decode table
	jmp	zCMD_start
;	in 	Xh, GPIOR2			; high(zOPCODE__LBLS_L)
;	jmp	zCMDP_decode
	


_extint_exec0:
	cbr	temp, 1<<IRQ_V_KBD
	ldi	FROMRAM0, IRQ_V_KBD
	rjmp	_extint_exec_clf
_extint_exec1:
	cbr	temp, 1<<IRQ_V_GPO
	ldi	FROMRAM0, IRQ_V_GPO
	rjmp	_extint_exec_clf
_extint_exec2:
	cbr	temp, 1<<IRQ_V_CTC
	ldi	FROMRAM0, IRQ_V_CTC
	rjmp	_extint_exec_clf
_extint_exec3:
	cbr	temp, 1<<IRQ_V_MUS
	ldi	FROMRAM0, IRQ_V_MUS
	rjmp	_extint_exec_clf
_extint_exec4:
	cbr	temp, 1<<IRQ_V_R1
	ldi	FROMRAM0, IRQ_V_R1
	rjmp	_extint_exec_clf
_extint_exec5:
	cbr	temp, 1<<IRQ_V_R2
	ldi	FROMRAM0, IRQ_V_R2
	rjmp	_extint_exec_clf
_extint_exec6:
	cbr	temp, 1<<IRQ_V_CTX
	ldi	FROMRAM0, IRQ_V_CTX
	rjmp	_extint_exec_clf
_extint_exec7:
	cbr	temp, 1<<IRQ_V_CRX
	ldi	FROMRAM0, IRQ_V_CRX
	rjmp	_extint_exec_clf


_extint_exec8:
	cbi	GPIOR0, IRQ_V_LAN
	ldi	FROMRAM0, 8+IRQ_V_LAN
	rjmp	_extint_exec_clf0
_extint_exec9:
	cbi	GPIOR0, IRQ_V_CAN
	ldi	FROMRAM0, 8+IRQ_V_CAN
	rjmp	_extint_exec_clf0
_extint_exec10:
	cbi	GPIOR0, IRQ_V_RTC
	ldi	FROMRAM0, 8+IRQ_V_RTC
	rjmp	_extint_exec_clf0
_extint_exec11:                 		; CPD init, need to clarify
	cbi	GPIOR0, IRQ_V_CPD
	lds	FROMRAM2, INT_MASK+0		; interrupts from CPD
	nportin cpd_irqfl
	and	temp, FROMRAM2			; check that allowed interrupt has occur, clear-on-read port
	out	GPIOR1, temp
;	sts	IRQ_CPD_FLAG, temp		; store for next processing loop
	rjmp	_extint_check_cpd_flags
_extint_exec12:
	cbi	GPIOR0, IRQ_V_R4
	ldi	FROMRAM0, 8+IRQ_V_R4
	rjmp	_extint_exec_clf0
_extint_exec13:
        ; Z80 debugging
	call	DEBUG_Z80			; PC -> next command
	ldi	temp, high(zOPCODE__LBLS_L)
	mov 	Xh, temp
	jmp	zCMDP_start			; command execute from zRAM

_extint_exec14:
	cbi	GPIOR0, IRQ_V_TTX
	ldi	FROMRAM0, 8+IRQ_V_TTX
	rjmp	_extint_exec_clf
_extint_exec15:
	cbi	GPIOR0, IRQ_V_TRX
	ldi	FROMRAM0, 8+IRQ_V_TRX
	rjmp	_extint_exec_clf0


_extint_exec_clf:
	out	GPIOR1, temp
;	sts	IRQ_CPD_FLAG, temp		; store cleared for next processing loop

_extint_exec_clf0:
_extint_exec:
	ldiw	Z, RTC_IRQ_BASE
	add	ZL, FROMRAM0
	adc	ZH, zero			; irq cmd
	ld	FROMRAM0, Z			; loaded	= IRQ vector

	cpi	FROMRAM0, 0xdd			; NMI vector
	breq	_extint_exec_nmi
	rjmp	_extint_exec_mi

_extint_exec_nmi:
	lds	temp, zzIFF1			; NMI int procedure
	sts	zzIFF2, temp
	sts	zzIFF1, zero

	zzPUSH 	zzPCh, zzPCl
	ldi 	zzPCl, 0x66
	ldi 	zzPCh, 0x00			; jmpt to 0x0066
	rjmp	_extint_exit

_extint_exec_mi:	
	lds	temp, zzIFF1			; MI int procedure
	cpi	temp, 0
	brne	_extint_exec_mi_enabled	
	rjmp	EXTINTRPOC_RETI			; interrupts disabled - process and clear all requests for NMI

_extint_exec_mi_enabled:
	sts	zzIFF1, zero			; set INT processing state
	sts	zzIFF2, zero

	lds	temp, zzIM			; check int mode
	cpi	temp, 2
	breq	_extint_exec_im2
	cpi	temp, 1
	breq	_extint_exec_im1

_extint_exec_im0:
	mov	XL, FROMRAM0			; data from IRQ VECTOR TABLE
_extint_exec_xl:
	ldi	temp, high(zOPCODE__LBLS_L)
	mov 	Xh, temp
	out	GPIOR2, temp			; GPIOR2 contains high pointer to decode table
	jmp	zCMDP_decode			; process command in XL - execute opcode

_extint_exec_im1:
	ldi	XL, 0xFF			; RST 38 command
	rjmp	_extint_exec_xl

_extint_exec_im2:
	zzPUSH 	zzPCh, zzPCl

	mov	ZL, FROMRAM0
	lds	ZH, zzI         		; Interrupt vector table ptr 
	LDRAM	ZH, ZL, FROMRAM2
	adiw	Z, 1
	LDRAM	ZH, ZL, FROMRAM1
	mov 	zzPCl, FROMRAM2
	mov 	zzPCh, FROMRAM1

	rjmp	_extint_exit



;EXTINTRPOC_RETI:

;EXTINTRPOC_RETN:
