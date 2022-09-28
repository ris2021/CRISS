; control keyboard leds

.EQU	KBL_RESTART = KBL_START
;	rjmp    KBL_EXIT

	sbrs	kbledr, 0
	rjmp	KBL_END1		; no active request

	cpi	kbcntr, 0
	brne	KBL_END1		; no action if data is transmitting

	sbrc	kbledr, 5
	rjmp	KBL_DATA   		; sending data

KBL_PULSE: ; generating start pulse
	mov	temp, kbledr
	andi	temp, 0x7f
	cpi	temp, 1
	brne	KBL_S1_L1

	cbi	EIMSK, INT0		; disable keyboard interrupt

	cbi	PORTD, PD2
	sbi	DDRD, PD2		; pull PD2 (CLOCK) low

	sts	TCNT2, zero
	sbi	TIFR2, OCF2A		; clear compare flag

	ldi	temp, 0x1F		; wait till first compare
	or	kbledr, temp		; start 20ms conter from 10 to 16
KBL_END1:
	rjmp    KBL_EXIT

KBL_S1_L1:
      	sbis    TIFR2, OCF2A
      	rjmp    KBL_EXIT                ; waiting for 150 us

	inc	kbledr
	inc	kbledr			; +=2

	cbi	PORTD, PD4
	sbi	DDRD, PD4		; pull PD4 (DATA) low

	cbi	DDRD, PD2		; release PD2 (CLOCK)

	clr	kblpb			; var for Parity Bit
	inc	kblpb			; start from 1

	rjmp	KBL_EXIT


KBL_DATA: ; sending data
	; waiting for clocks: 0/1, use bit 6 to understand what we're waiting
	sbrc	kbledr, 6
	rjmp	KBL_DATA_HI

KBL_DATA_LOW: ; looking for 0
	sbic	PIND, PD2		; waiting CLOCK low
      	rjmp    KBL_RESTART		; not yet
;      	rjmp    KBL_EXIT                ; not yet

KBL_DATA_LOW_SEND:
      	mov	temp, kbledr
        sbrc	temp, 4
        rjmp	KBL_DATA_LOW_SEND_PB	; send parity etc after 8th bit

KBL_DATA_LOW_SEND_DATA:
	eor	kblpb, kbldata		; parity bit calculation in kbcntr

	sbrs	kbldata, 0
	rjmp	KBL_DLSDATA_l3
KBL_DLSDATA_l4:
	cbi	DDRD, PD4		; send 1 - port to in, pull-up makes 1
	rjmp 	KBL_DATA_LOW_SEND_END
KBL_DLSDATA_l3:
	sbi	DDRD, PD4		; send 0 - set port to out
	rjmp	KBL_DATA_LOW_SEND_END
	
KBL_DATA_LOW_SEND_PB:
      	andi	temp, 0x1e		; counter
      	lsr	temp
      	cpi	temp, 9
      	brlo	KBL_DATA_LOW_SEND_PB_l1 ; parity bit (==8)
      	breq	KBL_DLSDATA_l4          ; stop-bit   (==9)
;      	breq	KBL_DATA_LOW_SEND_PB_l3	; stop-bit   (==9)
	rjmp	KBL_DATA_LOW_SEND_END	; ACK bit - ignore

KBL_DATA_LOW_SEND_PB_l3:
;      	ldi	tdata, 0x01		; stop-bit
;	rjmp	KBL_DLSDATA_l4		; send 1

KBL_DATA_LOW_SEND_PB_l1:		; send parity bit
	sbrs	kblpb, 0
	rjmp	KBL_DLSDATA_l3		; send 0
	cbi	DDRD, PD4		; send 1 - port to in, pull-up makes 1

KBL_DATA_LOW_SEND_END:
        lsr	kbldata                 ; shift for next bit

      	mov	temp, kbledr
      	sbr	temp, (1<<6)
      	mov	kbledr, temp		; set bit 6 - waiting for 1

      	rjmp    KBL_RESTART

KBL_DATA_HI: ; waiting 1
	sbis	PIND, PD2		; waiting CLOCK high
      	rjmp    KBL_RESTART

;      	;!!! check completion
      	inc	kbledr
      	inc	kbledr			; inc bit counter

      	mov	temp, kbledr
      	andi	temp, 0x1e		; counter
      	lsr	temp

      	cpi	temp, 10		; last data pulse
	brne	KBL_DATA_HI_not10

	; pulse 10
	cbi	DDRD, PD4		; release data bus
      	rjmp    KBL_DATA_HI_not11	; waiting for ACK pulse

KBL_DATA_HI_not10:
      	cpi	temp, 11		; end of processing
	brne	KBL_DATA_HI_not11

	; pulse 11 - end of processing
      	ldi	temp, 0x80
      	and	kbledr, temp		; clear state
      	add	kbledr, temp            ; goto next byte if any

	sbi	EIMSK, INT0		; reenable keyboard interrupt
	sts   	TCNT2, zero		; reset timer
        sbi	EIFR, INTF0		; clear first pulse for the keyboard if any
        clr	kbcntr
        clr	kbdata
      	rjmp    KBL_EXIT
	      	
KBL_DATA_HI_not11:
      	mov	temp, kbledr
      	cbr	temp, (1<<6)
      	mov	kbledr, temp		; clear bit 6 - waiting for next pulse low
      	rjmp    KBL_RESTART
	
KBL_END:
      	rjmp    KBL_EXIT
