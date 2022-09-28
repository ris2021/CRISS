      ; timer counter

      	sbis	TIFR0, OCF0A
      	rjmp    TMR_EXIT

      	sbi     TIFR0, OCF0A    ; clear flag

      	; system timer
      	inc     tmrcntr
      	ldi     temp, 100
      	cp      tmrcntr, temp
      	brlo    CTC_L

      	clr     tmrcntr		; count 0..100

	; CTC timer
CTC_L:
	lds	temp, ctcvv
	cp	temp, zero
	breq	MDUR_L		; no request

	dec	temp
	sts	ctcvv, temp
	brne	MDUR_L		; not ready

	sbi	GPIOR0, IRQ_CTC ; int request when counter comes to 0

	; music player counter dec if any
MDUR_L:
	cpse	mpdur, zero
	dec	mpdur

TWITO_CNTR:
	ldi	temp, 0x40	; twistat - bits 7,6 == timeout counter
	cpse	twistat, zero	; ignore if zero = no command processing
	add	twistat, temp

      	rjmp    TMR_EXIT
