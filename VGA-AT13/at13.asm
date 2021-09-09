.include "tn13def.inc"

.include "../macro.inc"

.MACRO lldi
		ldi		temp, @1
		mov		@0, temp
.ENDM

.MACRO 	putchar
		out		PORTB, ldoff
		nop
		nop
		out		PORTB, ldon
.ENDM

.MACRO	put10chars
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
.ENDM

.MACRO	put79chars			// =316
		put10chars			// +40
		put10chars			// +40
		put10chars			// +40
		put10chars			// +40
		put10chars			// +40
		put10chars			// +40
		put10chars			// +40
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
		putchar				// +4
.ENDM


		.EQU	HSPIN=0
		.EQU	VSPIN=1
		.EQU	OEPIN=2
		.EQU	LDPIN=4

// program part
.CSEG
		// var definition
		.DEF	zero	 =r3
		.DEF	ldon	 =r4
		.DEF	ldoff	 =r5
		.DEF	oeon 	 =r6
		.DEF	idle 	 =r7
		.DEF	hson 	 =r8
		.DEF	vson 	 =r9
		.DEF	ldoeon 	 =r10

		.DEF	temp	 =r17
		.DEF	two 	 =r18
		.DEF	one 	 =r19
		.DEF	sline	 =r22
		.DEF	stroke	 =r23
		.DEF	line	 =r24

.ORG 	0
		rjmp		RESET		;Reset Handle

.ORG	INT_VECTORS_SIZE

// ---------------------------------------------------------------------------
RESET:	
		_out	SPL, RAMEND

		ldi		stroke, 0
		ldi		sline, 0
		ldi		line, 0

		lldi	ldoeon,(1<<LDPIN)|(1<<HSPIN)|(1<<VSPIN)|(1<<OEPIN)
		lldi	ldon,  (1<<LDPIN)|(1<<HSPIN)|(1<<VSPIN)|(1<<OEPIN)
		lldi	ldoff, (0<<LDPIN)|(1<<HSPIN)|(1<<VSPIN)|(1<<OEPIN)
		lldi	oeon,  (0<<LDPIN)|(1<<HSPIN)|(1<<VSPIN)|(1<<OEPIN)
		lldi	idle,  (0<<LDPIN)|(1<<HSPIN)|(1<<VSPIN)|(0<<OEPIN)
		lldi	hson,  (0<<LDPIN)|(0<<HSPIN)|(1<<VSPIN)|(0<<OEPIN)
		lldi	vson,  (0<<LDPIN)|(1<<HSPIN)|(0<<VSPIN)|(0<<OEPIN)

		ldi		one, 1
		ldi		two, 2

		out		PORTB, 	idle
		_out	DDRB, 	0b00010111

		sei				// enable interrupts
	
		ldi		ZH, 0		// +1
		ldi		ZL, 0		// +1

MLOOP:	// main loop				// +2
		adiw	Z, 1				// +2

		cpi		ZL, 480-256			// +1
		cpc		ZH,	one				// +1
		brlo	DATALINE			// +2/+1

		cpi		ZL, 490-256			// +1		// +7
		cpc		ZH,	one				// +1
		breq	VSONLINE			// +2/+1

		cpi		ZL, 492-256			// +1		// +10
		cpc		ZH,	one				// +1
		breq	VSOFFLINE			// +2/+1

		cpi		ZL, 525-256*2		// +1		// +13
		cpc		ZH,	two				// +1
		brne	ELINE				// +2/+1

		ldi		ZH, 0				// +1		// +16
		ldi		ZL, 0				// +1
		rjmp	ELINE4				// +2

ELINE:								// +17
		nop							// +1
		nop							// +1
		nop							// +1

ELINE4:											// +20
		delay3	327					// +327
		nop							// +1
		nop							// +1	//+329
			
		rjmp	HS					// +2	=351

VSONLINE:	// 						// +11
		lldi	hson,  (0<<LDPIN)|(0<<HSPIN)|(0<<VSPIN)|(0<<OEPIN)	// +3
		lldi	idle,  (0<<LDPIN)|(1<<HSPIN)|(0<<VSPIN)|(0<<OEPIN)	// +3

		out		PORTB, vson			// +1	= 18

		delay3	333					// +333

		rjmp	HS					// +2	=351

VSOFFLINE:	// 						// +14
		lldi	idle,  (0<<LDPIN)|(1<<HSPIN)|(1<<VSPIN)|(0<<OEPIN)	// +3
		out		PORTB, idle			// +1	= 18
		lldi	hson,  (0<<LDPIN)|(0<<HSPIN)|(1<<VSPIN)|(0<<OEPIN)	// +3

		delay3	330					// +330

		rjmp	HS					// +2	=351

DATALINE:							// +8
		delay3	15					// +15
		out		PORTB, ldoeon		// +1	= +24

		put79chars					// 316
		out		PORTB, ldoff		// +1
		nop							// +1
		nop							// +1
		nop							// +1
		out		PORTB, idle			// +1	= +321

		delay3	6					// +6		
									// 	   	= 351

HS:
		out		PORTB, hson			// +1	
			
		delay3	45					// +45
		nop							// +1
		nop							// +1
		out		PORTB, idle			// +1	= +49
				
		rjmp 	MLOOP
