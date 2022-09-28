; delay temp us for 8 MHz clock (1 us = 8 ticks)
DELAY_US:
	dec	temp
	breq	DELAY_US_RET
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	rjmp	DELAY_US
DELAY_US_RET:
	ret

	/*
DELAY_MS:
	dec	temp
	breq	DELAY_MS_RET
	push	temp
	ldi	temp, 250
	rcall	DELAY_US
	ldi	temp, 250
	rcall	DELAY_US
	ldi	temp, 250
	rcall	DELAY_US
	ldi	temp, 250
	rcall	DELAY_US
	pop	temp
	rjmp	DELAY_MS	
DELAY_MS_RET:
	ret
	*/