.include "m328def.inc"

;запись в регистр (через temp)
.MACRO	_ldi
	ldi	temp, @1
	mov	@0, temp
.ENDM

;запись в порт (через temp)
.MACRO	_out
	ldi	temp, @1
	out	@0, temp
.ENDM

;запись в порт (через temp2)
.MACRO	_out2
	ldi	temp2, @1
	out	@0, temp2
.ENDM

;запись в порт (через temp)
.MACRO	_outm
	ldi	temp, @1
	sts	@0, temp
.ENDM

;запись в порт (через temp)
.MACRO	_rclr
	out	@0, zero
.ENDM


;запись WORD в порт (через temp) RL, RH, VAL
.MACRO	_outw
	_out	@1, high(@2)
	_out	@0, low(@2)
.ENDM

;запись WORD в порт (через temp) RL, RL, VAL
.MACRO	_outwm
	_outm	@1, high(@2)
	_outm	@0, low(@2)
.ENDM


	; delay for 3,6,9,12,... cycles
.MACRO 	delay3 ; 1=3 2=1+1*3+2
	ldi	temp, @0/3	; +1
_dlloop:
	dec	temp		;+1
	brne	_dlloop		;+2/1
.ENDM

.MACRO 	putchar
	ld	ZL, X+		; +2
	lpm	temp, Z		; +3
	out	PORTD, temp 	; +1
.ENDM

.MACRO	put8chars
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
.ENDM

.MACRO	put7chars
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
.ENDM

.MACRO	put6chars
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
.ENDM

.MACRO	put4chars
		putchar				// +6
		putchar				// +6
		putchar				// +6
		putchar				// +6
.ENDM

.MACRO	put3chars
		putchar				// +6
		putchar				// +6
		putchar				// +6
.ENDM

; send pulse to request data from PMCU
.MACRO	sync_pulse
	cbi	PORTC, PC0	; rtr active
	nop
	nop
	nop
	sbi	PORTC, PC0	
.ENDM


; program part -----------------------------------------------------------------------------------------
.CSEG
	; var definition
	.DEF	zero	 =r3	; 0
	.DEF	maxslH	 =r4
	.DEF	maxslL	 =r5

	.DEF	charsize =r6	; 19 or 20
	.DEF	linesno	 =r7	; 24 or 25

	.DEF	cpptrH	 =r8    ;
	.DEF	cpptrL	 =r9	; codepage pointer

	.DEF	_sreg	 =r10   ; store sreg in interrupts

	.DEF	cbyte	 =r11
  	.DEF	dataR	 =r12

  	.DEF	vmode	 =r13

 	.DEF	swidth	 =r14	; screen witdh 64 or 80 bytes
;	.DEF	startln	 =r15	; starting line

	.DEF	temp2	 =r16
	.DEF	temp	 =r17
	.DEF	line	 =r18
	.DEF	inchar	 =r19
	.DEF	lmode 	 =r20
	.DEF	temp3	 =r21

	.DEF	sline	 =r22
	.DEF	stroke	 =r23
	.DEF	RPTR 	 =r24
	.DEF	RPTRH 	 =r25
;	X - screen ptr
;	Y - RAM ptr
;	Z - char ptr


.ORG 	0
	rjmp	RESET		;Reset Handle

.ORG	PCI0addr
	rjmp	NEWLINE

.ORG	PCI1addr
	rjmp	NEWFRAME

.ORG	INT_VECTORS_SIZE

;.ORG  128

NEWFRAME:
	sbis	PINC, PC3	; check front
	reti

;	mov	stroke, vmode
;	cpi	stroke, 0x07	; check for the special mode
;	brne	NEWFRAME_L1	; no, just use predefined
;	ldi	XL, low(0x100+24*80)	; 25th line
;	ldi	XH, low(0x100+24*80)	; 25th line - it contains codepages for each line
;	ld	stroke, X		; codepage index
;	andi	stroke, 0x07
;	ldi	ZL, low(2*CP_LOC_TABLE)
;	ldi	ZH, high(2*CP_LOC_TABLE)
;	add	ZL, stroke
;	ld	cpptrH, Z	; required codepage pointer
;NEWFRAME_L1:
	ldi 	line, 0
	ldi	stroke, 0
	ldi	sline, 0
	ldi	lmode, 1
	ldi	RPTRH, 1
	ldi	RPTR, 0
	ldi	XH, high(video_cp)
	ldi	XL, low(video_cp)	; getting codepage for the next line
	ld	ZH, X
	ldi	XH, 1
	ldi	XL, 0
;	mov	ZH, cpptrH
	reti

	; new line started
NEWLINE:
	sbis	PINB, PB0	; +2/+1// check front
	reti

    	in    	_sreg, SREG   	; +1

	cpi	lmode, 0	; +1
	breq	DATALINE	; +2/+1

	cpi	lmode, 2	; +1
	breq	ENDI		; +2/+1

	; waiting for data frame
	inc	line		; +1
	cpi	line, 33	; +1
;	cpc	lineh, zero		// +1
	breq	BEREADY		; +2/+1

	out	PORTD, zero	; +1

ENDI:	
    	out 	SREG, _sreg   	; restore SREG
    	reti

BEREADY: ; next line should be output
	ldi	lmode, 0	; dataline mode
    	out 	SREG, _sreg  	; restore SREG
	reti

DATALINE:
	; data line
	; back porche		// +7 on entrance

	inc	stroke		// +1

;	nop					// +1
;	nop					// +1
;	nop					// +1

;LINECHAR: 				; +11 on enter
    	nop
   	nop
	delay3	9			; +14		it was 15 in previous version, -1 due to _sreg
;	delay3	12			; +14		it was 15 in previous version, -1 due to _sreg

	sbrs	swidth, 4		; +1/2		if w=80 switdh=01010000b
	rjmp	DATALINE64		; +2

	nop

DATALINE80:

	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
  	putchar				// +1
	putchar				// +1
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
  	put3chars			// +18

DATALINE80END:
	cp	stroke, charsize; +1
	breq	ENDOFLINE	; +2

	inc	ZH		; +1 // go to next stroke
	movw	X, RPTR		; +2	// reset line pointer	

;	out	PORTD, zero	; +1
    	out 	SREG, _sreg   	; restore SREG
	reti

ELINE:	; empty line after symbol block	
;	cpi	stroke, 19	; +1
;	breq	ENDOFLINE
;	reti

ENDOFLINE:
	inc	sline		; +1	// inc sline

	ldi	XH, high(video_cp)
	ldi	XL, low(video_cp)	; getting codepage for the next line
	add	XL, sline
	ld	ZH, X

;	mov	stroke, vmode
;	cpi	stroke, 0x07	; check for the special mode
;	brne	ENDOFLINE_SET_ZH	; no, just use predefined
;	ldi	XL, low(0x100+24*80)	; 25th line
;	ldi	XH, low(0x100+24*80)	; 25th line - it contains codepages for each line
;	add	XL, sline		; select right value
;	adc	XH, zero	;???? check!!!
;	ld	stroke, X		; codepage index
;	andi	stroke, 0x07
;	ldi	ZL, low(2*CP_LOC_TABLE)
;	ldi	ZH, high(2*CP_LOC_TABLE)
;	add	ZL, stroke
;	ld	cpptrH, Z	; required codepage pointer
;ENDOFLINE_SET_ZH:
;	mov	ZH, cpptrH 	; +1 // reset ZH to 0 stroke
	clr	stroke		; +1	// reset stroke counter

	cp	sline, linesno	; +1
	breq	ENDOFDATA	; +2/+1	// end of lines reached

	add	RPTR, swidth
	adc	RPTRH, zero

;	adiw	RPTR, 40	; +2 // next line on the screen
;	adiw	RPTR, 40	; +2 // next line y+=80
	movw	X, RPTR		; +1 // pointer to read with inrement

    	out 	SREG, _sreg   	; restore SREG
	reti

ENDOFDATA:
	ldi	lmode, 2	; ignore till VS reset
    	out 	SREG, _sreg   	; restore SREG
	reti


DATALINE64:

	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
	put3chars			// +18
	nop					// +1
  	putchar				// +1
	out	PORTD, zero 	; +1
  	rjmp	DATALINE80END


;.ORG  0x200
; ---------------------------------------------------------------------------
; ---------------------------------------------------------------------------
RESET:	
	; IO ports settings -------------------------------------------

	_out	PORTC, (1<<PC0)
	_out	DDRC, (1<<PC0)|(1<<PC1)|(1<<PC2) ; rtr signal=1 + CLR + reset control for at13
	
	_out	PORTD, 0
	_out	DDRD, 0xff	; D = data out

	_out	DDRB, (1<<PB4)|(1<<PB1)	; MISO + error pin

	; Stack pointer settings --------------------------------------
	_outw	SPL, SPH, RAMEND

	; fill ram from eeprom
;	ldi	line, 0
	ldi	YH, 0
	ldi	YL, 0		; start point in EEPROM
	out	EEARH, YH
	out	EEARL, YL	; Address to read
	sbi 	EECR, EERE	; read request
	in 	cbyte, EEDR	; read char from eeprom - start settings

	; start memory fill -------------------------------------------
	; fill ram with spaces
	ldi	XH, 1
	ldi	XL, 0		; start point in ram
	mov	inchar, cbyte
	andi	inchar, 0x07	; codepage
	ldi	temp, 0
	cpi	inchar, 1	; graphic codepage?
	breq	L0		; spaces
	ldi	temp, ' '	; non-graphis modes
L0:
	st	X+, temp
	cpi	XL, low(0x100+25*80)
	ldi	temp2, high(0x100+25*80)
	cpc	XH, temp2
	brne	L0

	; fill ram from eeprom
	ldi	line, 0
	ldi	YH, 0
	ldi	YL, 1		; start point in EEPROM

;	out	EEARH, YH
;	out	EEARL, YL	; Address to read
;	sbi 	EECR, EERE	; read request
;	in 	cbyte, EEDR	; read char from eeprom - start settings
;	adiw	Y, 1

L3:	ldi	XH, 1
	ldi	XL, 0		; start point in RAM

	; calculate beginning of line position
	mov	temp, line
L2:	or	temp, temp	; check for temp==0
	breq	L1
	adiw	X, 40
	adiw	X, 40
	dec		temp
	rjmp	L2
L1:				; X is set to line start
	out	EEARH, YH
	out	EEARL, YL	; Address to read
	sbi 	EECR, EERE	; read request
	in 	inchar, EEDR	; read char from eeprom

	cpi	inchar, 0x1F
	breq	L4		; ^Z = end of data

	adiw	Y, 1		; incrementing EEAR

	cpi	inchar, 0x09
	breq	L6		; TAB

	cpi	inchar, 0x0D
	breq	L5		; NL = new line

	st	X+, inchar	; store char in RAM
	rjmp	L1

L5:
	inc	line
	rjmp	L3		; need to recompute X

L6:
	ori	XL, 0x07	; goto next TAB position
	adiw	X, 1

	cpi	XL, low(0x100+24*80)
	ldi	temp2, high(0x100+24*80)
	cpc	XH, temp2
	
	brne	L1		; next char
		
	; end memory fill	---------------------------------------------------

L4:
	; initialize variables
	clr 	zero		; =0

	ldi	RPTRH, 1
	ldi	RPTR, 0
	ldi	XH, 1
	ldi	XL, 0
	ldi	stroke, 0
	ldi	sline, 0

;	clr	startln

;	ldi	ZH, high(2*CP_DATA_START)  ; znakogen start point
;	mov	temp2, cbyte
;	mov	vmode, cbyte	; save current vmode
;	rcall	GET_CT_ADDR
;	andi	temp2, 0x07
;	breq	L4_1
;L4_2:
;	subi	ZH, -20
;	dec	inchar
;	brne	L4_2

;	mov	cpptrH, temp2	; codepage decoded
;	mov	ZH, temp2	; set codepage pointer

;L4_1:
;	ldi	ZL, 0
;	ldi 	line, 0
;	ldi 	lmode, 2

;	mov	inchar, cbyte
;	lsr	inchar
;	lsr	inchar
;	lsr	inchar
;	cpi	inchar, 25
;	breq	L4_3
;	_ldi	charsize, 20	; start with 24*80 mode 
;	_ldi	linesno, 24   	; lines = 24
;	rjmp	L4_4
;L4_3:
;	_ldi	charsize, 19	; start with 24*80 mode 
;	_ldi	linesno, 25   	; lines = 25
L4_4:
	_ldi	maxslH, high(25*80+0x100)
	_ldi	maxslL, low(25*80+0x100)

	; initialize interrupts
	_outm	PCICR, (1<<PCIE1)|(1<<PCIE0)	; Pin change interrupts enabled
	_outm	PCMSK0, (1<<PCINT0)		; hsync PB0
	_outm	PCMSK1, (1<<PCINT11)		; vsync PC3
		
	sei			; enabling interrupts
	cbi	DDRC, PC2	; enabling HS VS generation PC2=1 pulling hi RESET AT13
        clr	vmode
	rcall	DECODECBYTE_PROC
    	rjmp  	DATAREFRESH     ; goto data refresh block
;    	rjmp	DECODECBYTE

HALT:   rjmp 	HALT


	; send/receive byte via SPI
.MACRO  DOSPI
	ldi	inchar, @0
	out	SPDR, inchar    ; return value

	cbi	PORTC, PC0	; rtr active
	nop
	nop
	nop
	sbi	PORTC, PC0	; generate rtr pulse
;	sync_pulse              ; generate rtr pulse
DS_L0:
	in	inchar, SPSR
	sbrs	inchar, SPIF
	rjmp	DS_L0		; waiting for data
	in	@1, SPDR	; get data
.ENDM


; ---------------------------------------------------------------------------------------
; Code starts here
.ORG  0x300
DATAREFRESH:
	_out2	SPCR, (1<<SPE)	; SPI enable Slave mode
	cbi	PORTB, PB1	; clear error pin

	; start syncyng
        DOSPI   'R', inchar     ; request to start from zero, ignore response
;	rjmp	DECODECBYTE	; set preloaded settings

	; main loop - reading RAM from SPI (if any)
SPILOOP:
        ldi     YH, 1
        ldi     YL, 0           ; reset memory point
		
INLOOP:
        DOSPI   0xff, inchar    ; reading data
        st      Y+, inchar      ; store in memory

  	cp	YL, maxslL
	cpc	YH, maxslH
        brlo    INLOOP          ; next char if <MAX

  	sbi	PORTB, PB1	; set error pin - notify R is sending
        DOSPI   'R', cbyte      ; getting control byte and sending request to restart
  	cbi	PORTB, PB1	; clear error pin

;	rcall	DECODECBYTE
;	rjmp	SPILOOP		; 

;        rjmp	SPILOOP		;!!!!!! temp!!!!

;	st	Y, cbyte	; store code byte after video data
;	rjmp	L15		;!!!!  temp!!!

DECODECBYTE:
	cp	cbyte, vmode	; check that mode is changed
	brne	DECODECBYTE_DO	; new code	
	
	mov	temp2, cbyte
	andi	temp2, 0x07
	cpi	temp2, 0x07	; special mode - refill codepages each loop
	brne	SPILOOP		; not special mode - no action
	rcall	GET_CT_ADDR	; special mode == fill cp table
DECODECBYTE_ret:
	rjmp	SPILOOP		; 

DECODECBYTE_DO:
	rcall	DECODECBYTE_PROC
	rjmp	SPILOOP		; 


DECODECBYTE_PROC:
	cp	cbyte, zero	; check sleep mode request
	brne	DECODECBYTE_L0

	; sleep mode
	cbi	PORTC, PC2	; disable VGA sync
	sbi	DDRC, PC2	; disable VGA sync - STOP AT13
	out	PORTD, zero	; clear output
	ret
;	rjmp	SPILOOP

DECODECBYTE_L0:
	cbi	DDRC, PC2	; enable VGA sync

 	; decoding sync byte
	mov	temp2, cbyte	; setting codepage
	rcall	GET_CT_ADDR	; decode codepage

	mov	vmode, cbyte	; store vmode

L15:	; decoding lines number
	mov	temp2, cbyte	; start setting line numbers
;        andi    temp2, 0x7f     ; mask bit 7
	lsr	temp2
	lsr	temp2
	lsr	temp2		; temp2 = line numbers (sync >> 3)
;	mov	linesno, temp2	; linesno set

	cpi	temp2, 31	; 31 lines?
	brsh	L_CS31	

	cpi	temp2, 30	; 30 lines?
	brsh	L_CS30	

	cpi	temp2, 25	; 25 lines?
	brsh	L_CS25	
				
L_CS24:                         ; 24 for other cases
	_ldi    charsize, 20    ; for <25 lines 20 strokes mode applied 
	_ldi	swidth, 80	; set 80 chars
	_ldi	linesno, 24	; linesno set
;	clr	startln
	ret
;
L_CS25:
	_ldi	charsize, 19    ; for 25 lines 19 strokes mode applied
	_ldi	linesno, 25	; not more than 25 lines can be set
	_ldi	swidth, 80	; set 80 chars
;	clr	startln
	ret
;
L_CS31:
	_ldi	charsize, 15    ; for 31 lines 15 strokes mode applied
	_ldi	swidth, 64	; set 64 chars
	_ldi	linesno, 31	; not more than 25 lines can be set
;	_ldi	startln, 2
	ret
;	rjmp	SPILOOP

L_CS30:
	_ldi	charsize, 16    ; for  lines 19 strokes mode applied
	_ldi	swidth, 64	; set 64 chars
	_ldi	linesno, 30	; not more than 25 lines can be set
;	_ldi	startln, 2
	ret
;	rjmp	SPILOOP

;L14:    nop
		


GET_CT_ADDR:
	andi	temp2, 0x07
	cpi	temp2, 1
	breq 	GET_CT_ADDR_1
	cpi	temp2, 2
	breq 	GET_CT_ADDR_2
	cpi	temp2, 3
	breq 	GET_CT_ADDR_3
	cpi	temp2, 4
	breq 	GET_CT_ADDR_4
	cpi	temp2, 5
	breq 	GET_CT_ADDR_5
	cpi	temp2, 6
	breq 	GET_CT_ADDR_6
	cpi	temp2, 7
	breq 	GET_CT_ADDR_7
GET_CT_ADDR_0:
	ldi	temp2, high(CP0_CHARPIXTABLE*2)
	rjmp	GET_CT_ADDR_FILL_S
GET_CT_ADDR_1:
	ldi	temp2, high(CP1_CHARPIXTABLE*2)
	rjmp	GET_CT_ADDR_FILL_S
GET_CT_ADDR_2:
	ldi	temp2, high(CP2_CHARPIXTABLE*2)
	rjmp	GET_CT_ADDR_FILL_S
GET_CT_ADDR_3:
	ldi	temp2, high(CP3_CHARPIXTABLE*2)
	rjmp	GET_CT_ADDR_FILL_S
GET_CT_ADDR_4:
	ldi	temp2, high(CP4_CHARPIXTABLE*2)
	rjmp	GET_CT_ADDR_FILL_S
GET_CT_ADDR_5:
	ldi	temp2, high(CP0_CHARPIXTABLE*2)
	inc	temp2
	inc	temp2
	rjmp	GET_CT_ADDR_FILL_S
GET_CT_ADDR_6:
	ldi	temp2, high(CP4_CHARPIXTABLE*2)
	inc	temp2
	inc	temp2
	rjmp	GET_CT_ADDR_FILL_S
GET_CT_ADDR_7:
	mov	cbyte, temp2
	ldi	temp3, (24<<3) + 7	; forcing 24 lines mode
	mov	cbyte, temp3
	ldi	temp3, 24		; lines to store 0..24
GET_CT_ADDR_7_LOOP:
	ldi	YL, low(video25)
	ldi	YH, high(video25)	; cp list
	add	YL, temp3
	ld	temp2, Y		; codepage for line no temp3
	andi	temp2, 0x07
	cpi	temp2, 1
	breq 	GET_CT_ADDR_S_1
	cpi	temp2, 2
	breq 	GET_CT_ADDR_S_2
	cpi	temp2, 3
	breq 	GET_CT_ADDR_S_3
	cpi	temp2, 4
	breq 	GET_CT_ADDR_S_4
GET_CT_ADDR_S_0:
	ldi	temp2, high(CP0_CHARPIXTABLE*2)
	rjmp	GET_CT_ADDR_SET_S
GET_CT_ADDR_S_1:
	ldi	temp2, high(CP1_CHARPIXTABLE*2)
	rjmp	GET_CT_ADDR_SET_S
GET_CT_ADDR_S_2:
	ldi	temp2, high(CP2_CHARPIXTABLE*2)
	rjmp	GET_CT_ADDR_SET_S
GET_CT_ADDR_S_3:
	ldi	temp2, high(CP3_CHARPIXTABLE*2)
	rjmp	GET_CT_ADDR_SET_S
GET_CT_ADDR_S_4:
	ldi	temp2, high(CP4_CHARPIXTABLE*2)
	rjmp	GET_CT_ADDR_SET_S
GET_CT_ADDR_SET_S:
	ldi	YL, low(video_cp)
	ldi	YH, high(video_cp)	; cp list
	add	YL, temp3
	st	Y, temp2		; high of address of CP*_char...
	dec	temp3
	brmi	GET_CT_ADDR_7_RET	; stop on -1
	rjmp	GET_CT_ADDR_7_LOOP	; loop 0..24
GET_CT_ADDR_7_RET:	
;	lds	temp2, video_cp
;	sts	video_cp+25, temp2
	ret
	  
GET_CT_ADDR_FILL_S:
	sts	video_cp, temp2
	sts	video_cp+0, temp2
	sts	video_cp+1, temp2
	sts	video_cp+2, temp2
	sts	video_cp+3, temp2
	sts	video_cp+4, temp2
	sts	video_cp+5, temp2
	sts	video_cp+6, temp2
	sts	video_cp+7, temp2
	sts	video_cp+8, temp2
	sts	video_cp+9, temp2
	sts	video_cp+10, temp2
	sts	video_cp+11, temp2
	sts	video_cp+12, temp2
	sts	video_cp+13, temp2
	sts	video_cp+14, temp2
	sts	video_cp+15, temp2
	sts	video_cp+16, temp2
	sts	video_cp+17, temp2
	sts	video_cp+18, temp2
	sts	video_cp+19, temp2
	sts	video_cp+20, temp2
	sts	video_cp+21, temp2
	sts	video_cp+22, temp2
	sts	video_cp+23, temp2
	sts	video_cp+24, temp2
	sts	video_cp+25, temp2
	sts	video_cp+26, temp2
	sts	video_cp+27, temp2
	sts	video_cp+28, temp2
	sts	video_cp+29, temp2
	sts	video_cp+30, temp2
	sts	video_cp+31, temp2
	ret
    

CP_LOC_TABLE:
	.db	high(CP0_CHARPIXTABLE*2), \
		high(CP1_CHARPIXTABLE*2), \
		high(CP2_CHARPIXTABLE*2), \
		high(CP3_CHARPIXTABLE*2), \
		high(CP4_CHARPIXTABLE*2), \
		high(CP0_CHARPIXTABLE*2), \
		high(CP0_CHARPIXTABLE*2), \
		high(CP0_CHARPIXTABLE*2)
    
; znakogen block
.ORG	0x400
CP_DATA_START:
.include "CP0_font8x20-256.asm"
.include "CP1_font8x20-256.asm"
.include "CP2_font8x20-256.asm"
.include "CP3_font8x20-256.asm"
.include "CP4_font8x20-256.asm"
;.include "CP5_font8x20-256.asm"

;.ORG	0x3f0
LB:	.DB	0x00, 0x00

.include "ram.def"
