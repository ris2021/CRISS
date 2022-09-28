	; processing COM-port transaction
	
	lds	tdata, UCSR0A		; check COM status
	lds	temp, comst
	or	temp, tdata
	sts	comst, temp		; store comst port: COM-port status |= UCSR0A

	sbrs	tdata, RXC0		; check that RxC flag is active
	rjmp	L_COM_TXC		; if now skip it

	sbi	GPIOR0, IRQ_COM_RX	; set IRQ flag request

	lds	temp, UDR0
	sts	comrx, temp		; read data and store to comrx port

L_COM_TXC:
	sbrs	tdata, TXC0		; check TxC flag
	rjmp	L_COM_RTS		; proceed if none
	
	sbi	GPIOR0, IRQ_COM_TX	; set IRQ flag request

        lds	temp, UCSR0A
	ori	temp, (1<<TXC0)
	sts	UCSR0A, temp		; clear TXC flag

L_COM_RTS:
	lds	temp, comtc
	cpi	temp, 0			; is there send request?
	breq	L_COM_END

	sbrs	tdata, UDRE0		; check ready to send status
	rjmp	L_COM_END

	lds	tdata, comtx
	sts	UDR0, tdata		; transmit data from comtx port

	dec	temp
	sts	comtc, temp		; decrease conter

L_COM_END:
	rjmp	COM_EXIT
