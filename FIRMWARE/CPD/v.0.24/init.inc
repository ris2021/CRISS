	; Stack pointer settings --------------------------------------
	_outw	SPL, SPH, RAMEND

	; Init I/O ports
	_out	PORTB, 0
	_out	DDRB, (1<<PB4)|(1<<PB1)		; MISO, AUDIO

	_out	PORTC, (1<<PC1)                 ; VGA MISO pull-up
	_out	DDRC, (1<<PC0)|(1<<PC2)|(1<<PC3); VSCK, VDO, VSS

	_out	PORTD, (1<<PD5)|(1<<PD6)|(1<<PD7)|(1<<PD2)|(1<<PD4)  ; VRST, INTR, MCPU, KB_CLK, KB_DATA Pull-ups
	_out	DDRD, 0

