.EQU    VSPI_PORT = PORTC
.EQU    VSPI_MISO = PC2
    
.MACRO  VGA_SPI_CLK
	bst	tdata, @0
	bld	vga0, PC2	; set
	out	PORTC, vga0	; clk0
	bld	vga1, PC2	; set
	out	PORTC, vga1	; clk1
	sbic	PINC, PC1
	sbr	temp, 1<<@0	; read bit
.ENDM

  	sbis	EIFR, INTF1     ; check rtr flag
VGA_L0:
	rjmp	VGA_EXIT        ; exit if flag is not set
    
VGA_EXEC:
  	sbi	EIFR, INTF1     ; clear rtr flag

	out   	PORTC, vga0   	; cs and initial condition

    	lds   	temp, vcurl
	cp    	YL, temp
	lds 	temp, vcurh
	cpc 	YH, temp

	ld    	tdata, Y+      	; get next symbol

	brne  	VGA_L1

    	; check action for cursor position
	cpi   	tmrcntr, 50   	; cursor blinking 1Hz
	brsh  	VGA_L1
	
	; clear for timer<50 
	clr   	tdata           ; put symbol 0 to cursor position

VGA_L1:

VGA_SPI_SEND:
	clr	temp
	VGA_SPI_CLK 7
	VGA_SPI_CLK 6
	VGA_SPI_CLK 5
	VGA_SPI_CLK 4
	VGA_SPI_CLK 3
	VGA_SPI_CLK 2
	VGA_SPI_CLK 1
	VGA_SPI_CLK 0
	out	PORTC, vga2     ; pause state

    	cpi   	temp, 'R'
	brne  	VGA_SPI_EXIT	; VGA_EXIT

	ldi   	YH, 1
	ldi   	YL, 0
VGA_SPI_EXIT:
    	rjmp  	VGA_EXIT
