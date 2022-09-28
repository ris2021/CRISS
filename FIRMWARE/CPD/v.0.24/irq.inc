	; generate IRQ to CPU if any

	; CTRL_ALT_SHIFT - ESC check
	sbis	GPIOR0, IRQ_KBD
	rjmp	IRQ_L0

	lds	temp, kactk
	cpi	temp, 0x76		; ESC
	brne	IRQ_L0
	lds	temp, kmodk
	andi	temp, (1<<CTRL)|(1<<ALT)|(1<<SHIFT)
	cpi	temp, (1<<CTRL)|(1<<ALT)|(1<<SHIFT)
	brne	IRQ_L0

IRQ_HW_RESET:
	; ctrl-alt-shift-ESC pressed = system reset pulse
	cbi	PORTD, PD7 		; PD7 = 0
	sbi	DDRD, PD7		; port out
	delay3	210
	cbi	DDRD, PD7
	sbi	PORTD, PD7 		; PD7 = 1
IRQ_HALT:
	rjmp	IRQ_HALT		; waiting for restart

IRQ_L0:
	; check COM status
;	lds	tdata, UCSR0A
;	sts	comst, tdata		; save COM port status value to port
;	ori	tdata, (1<<RXC0)|(1<<TXC0)	; hide unused bits

;	in	temp, GPIOR0
;	or	temp, tdata		; set COM-port state
;	out	GPIOR0, temp

	in	temp, GPIOR0

	lds	tdata, irqfl
	or	tdata, temp
	sts	irqfl, tdata		; set irqfl port value

;	in	temp, GPIOR0
	in	tdata, GPIOR1		; INT mask
	and	temp, tdata

	cpi	temp, 0			; is there unmasqued int?
	breq	IRQ_END			; no interrupt need = clear gpior0 and exit

;	brne	IRQ_DO
;	rjmp	IRQ_EXIT		; nothing to do

IRQ_DO:	; generate irq signal
	; there are requests to process
	cbi	PORTD, PD6
	sbi	DDRD, PD6 		; negative pulse
	delay3	6
	cbi	DDRD, PD6 		; negative pulse end
	sbi	PORTD, PD6

IRQ_END:
	out	GPIOR0, zero		; clear request flags
	rjmp	IRQ_EXIT

