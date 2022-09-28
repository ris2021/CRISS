; z80-related init procedures

z80INITPROC_CMD:
	; load opcodes jumps and other data data into the RAM
	ldi	Xl, low(RAMOPCODES)
	ldi 	Xh, high(RAMOPCODES)
	ldi	Zl, 0
;	ldi 	Zh, 0
	ldi 	Zh, high(ROMDATA*2)
INIT_ML1LOOP:
	elpm	temp, Z+
	st	X+, temp
	cpi	Xl, low(RAMOPCODESEND)
	ldi	temp, high(RAMOPCODESEND)
	cpc 	Xh, temp
	brne 	INIT_ML1LOOP

	; load irq calls
	ldi	Xl, low(IRQOPCODES)
	ldi 	Xh, high(IRQOPCODES)
	ldi	temp, low(EXTINTRPOC)
INIT_ML2LOOP:
	st	X+, temp
	cpi	Xl, 0
	brne 	INIT_ML2LOOP

	ldi	temp, high(EXTINTRPOC)
INIT_ML2LOOP_l:
	st	X+, temp
	cpi	Xl, 0
	brne 	INIT_ML2LOOP_l

	ldi	temp, high(zOPCODE__LBLS_L)
	out	GPIOR2, temp		; GPIOR2 contains high pointer to decode table

	; reset z80 registers
	_ldi	zzA, 0
	_ldi	zzF, 0
	_ldi	zzB, 0
	_ldi	zzC, 0
	_ldi	zzD, 0
	_ldi	zzE, 0
	_ldi	zzH, 0
	_ldi	zzL, 0
	_ldi	zzIXl, 0
	_ldi	zzIXh, 0
	_ldi	zzIYl, 0
	_ldi	zzIYh, 0

	; reset memory stored registers
	sts	zzI, zero
	sts	zzAe, zero
	sts	zzFe, zero
	sts	zzBe, zero
	sts	zzCe, zero
	sts	zzDe, zero
	sts	zzEe, zero
	sts	zzHe, zero
	sts	zzLe, zero
	sts	zzIFF1, zero
	sts	zzIFF2, zero
	sts	zzIM, zero
	sts	zzRhb, zero

	_out	TCCR0B, (1<<CS01)		; timer for zzR fclk/8

	ret
