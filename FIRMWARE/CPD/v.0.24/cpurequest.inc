; SPI slave mode Data processing    

;    	in    	_sreg, SREG

    	in    	itemp, SPDR     ; read data from SPI
    	st    	X+, itemp       ; store in registers 0,1,2

;    sts   700, r0
;    sts   701, r1
;    sts   702, r2
;    ldi   itemp, '0'
;    add   itemp, xl
;    sts   703, itemp

;    mov   itemp, r0
;    subi  itemp, 0xf8-'0'
;    sts   704, itemp

;    ldi   itemp, '0'
;    add   itemp, r1
;    sts   705, itemp

;    cpi   XL, 3
;    brsh  CR_END


    	sbrc  	r0, 7
    	rjmp  	CR_VIDEO

    	sbrc  	r0, 6
    	rjmp  	CR_WRITEPORT

CR_READPORT:
        ; read port block
        cpi   	XL, 2
        brsh  	CR_END       	; value sent - exit

        ldi   	XH, high(PORTS)
        ldi   	XL, low(PORTS)

        add   	XL, r0       	; r0 = port number
        
        ld    	itemp, X    	; read port value
        out   	SPDR, itemp 	; value to transmit

	sbrc	r0, 5		; for regs>16 clear value after read
	st	X, zero		; clear variable
        
        ldi   	XH, 0
        ldi   	XL, 1		; read 0xff data expected

;    	ldi	itemp, 13
;    	cp	r0, itemp
;    	brne	CR_RETI
;    	sts	irqfl, zero	; clear after read - exception!

    	rjmp  	CR_RETI
;    	RETI_S

;    ldi   XH, 0
;    ldi   XL, 0    
;    reti

CR_VIDEO:
    	mov   	itemp, r0
    	cpi   	itemp, 0x80
    	breq  	CR_END        ; sync mode
    
    	cpi   	XL, 3  
    	brlo  	CR_RETI
    	mov   	XH, r0
    	andi  	XH, 0x07   ; mask $f8
    	inc 	XH
    	mov	XL, r1

    	ldi	itemp, high(0x100+25*80+1)
    	cpi	XL, low(0x100+25*80) 	; check that videoram is accessed
    	cpc	XH, itemp
    	brlo	CR_V_ST 		; store
    	rjmp  	CR_END
;	ldi   	XH, 0
;	ldi   	XL, 0    
;	RETI_S

CR_V_ST:
    	st    	X, r2
    	rjmp  	CR_END
;	ldi   	XH, 0
;	ldi   	XL, 0    
;	RETI_S

CR_WRITEPORT:
	cpi   	XL, 2
	brlo  	CR_RETI

    	ldi   	XH, high(PORTS)
    	ldi   	XL, low(PORTS)
    	ldi   	itemp, 0x3f
    	and   	r0, itemp   ; mask bit 6    
    	add   	XL, r0       ; r0 = port number
    	st    	X, r1

CR_END:
	ldi   	XH, 0
	ldi   	XL, 0    
CR_RETI:
;	out   	SREG, _sreg
;    	reti

    