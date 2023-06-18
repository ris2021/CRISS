#include "tn84def.inc"

; RAM definitions ---------------------------------------------------------------------
	.DSEG
	.ORG	0x100
pr_buf:	.BYTE	64

; General Interrupt Vector ------------------------------------------------------------
        .CSEG
	.ORG	0
	rjmp	BOOTLOADER	; Reset
	rjmp	M_INT0		; INT0 - CS
	rjmp	M_PCI0		; PCINT0
	rjmp	M_PCI1		; PCINT1
	rjmp	M_WDT		; WDT ???
	rjmp	M_ICP1		; Timer/Counter1 Capture Event
	rjmp	M_OC1A		; Timer/Counter1 Compare Match A
	rjmp	M_OC1B		; Timer/Counter1 Compare Match B
	rjmp	M_OVF1		; Timer/Counter1 Overflow
	rjmp	M_OC0A		; Timer/Counter0 Compare Match A
	rjmp	M_OC0B		; Timer/Counter0 Compare Match B
	rjmp	M_OVF0		; Timer/Counter0 Overflow
	rjmp	M_ACI		; Analog Comparator
	rjmp	M_ADCC		; ADC Conversion Complete
	rjmp	M_ERDY		; EEPROM Ready
	rjmp	M_USIS		; USI START
	rjmp	M_USIO		; USI Overflow

; Registers names --------------------------------------------------------------------
	.DEF	zero 	= r2	; 0
	.DEF	temp 	= r16
	.DEF	lmode 	= r17

; wait SPMEN=0 == until operation completed
.MACRO 	WAIT_SPMEN
	spm
wait_spmen:
	in	temp, SPMCSR
	sbrc	temp, SPMEN
	rjmp	wait_spmen
.ENDM

; Bootloader -------------------------------------------------------------------------
	.CSEG
	.ORG 	32

;l_halt:	rjmp	l_halt		; trap the case of broken firmware

BOOTLOADER:
init:
        ldi	temp, high(RAMEND)
	out	SPH, temp	; set/restore stack
        ldi	temp, low(RAMEND)
	out	SPL, temp	; set/restore stack

        clr   	zero		; set =0

        out	DDRA, zero
        out	DDRB, zero

        out	TCCR1A, zero
        ldi	temp, (1<<CS12)|(1<<CS10)	; /1024 prescaler
        out	TCCR1B, temp	; start timer
        ldi	temp, 15
        out	OCR1AH, temp
        out	OCR1AL, zero	; 1/20 s interval

BL_LOOP:
BLS:
;	rcall	SPI_STOP
	out 	USICR, zero	; stop SPI
;	ldi	temp, 0
	out	DDRA, zero	; release bus
;	ldi	temp, 0
	out	DDRB, zero	; all pins to input

w_cs_1:	sbis	PINB, PB2
	rjmp	w_cs_1		; wait CS hi

	out	TCNT1H, zero
	out	TCNT1L, zero	; reset timer
	sbi	TIFR1, OCF1A	; clear OCF flag

w_cs_0:	sbis	PINB, PB2	; wait for cs==low
	rjmp	w_cs_received	; CS is low - start SPI
	sbic    TIFR1, OCF1A	; check timeout
	rjmp	RET_TO_MAIN	; start main program if timeout detected
	rjmp	w_cs_0		; loop

w_cs_received:

;	rcall	SPI_START	; start SPI engine
	ldi 	temp, (1<<USIWM0)|(1<<USICS1)	; start SPI
	out 	USICR, temp
;	ldi	temp, (1<<PA4)|(1<<PA5)		; DO and USCK pins are enabled as outputs in DDRA
	sbi	DDRA, PA5	; DO is enabled as output in DDRA

	ldi	temp, 'C'
	rcall	SPI		; Send Clear

	ldi	temp, 'C'
	rcall	SPI		; read command

	cpi	temp, 0x80	; start command?
	brne	_n_80

RET_TO_MAIN:

	out 	USICR, zero	; stop SPI
        out	TCCR1B, zero	; stop timer
	rjmp	M_RST		; Start Main Routine


_n_80:	mov 	lmode, temp	; Store write mode
	ldi	temp, 'A'
	rcall	SPI		; read page addrress
	mov	ZH, temp	; Store page index
	        	
	ldi	XH, 1
	ldi	XL, 0		; memory buffer address

	; getting 64 byte buffer ----------------------------
BL5:	
	ldi	temp, 'W'
	rcall	SPI		; read byte
	st	X+, temp
	cpi	XL, 64
	brlo	BL5		; loading 64 bytes of data

	; Prepare to write ----------------------------------
	ldi	XH, 1
	ldi	XL, 0		; restore memory buffer address

	cpi	lmode, '7'
	breq	BL6		; CSEG overwrite requested

	cpi	lmode, '8'
	breq	BL8		; ESEG overwrite requested

	rjmp	BLS		; Bad command

BL6:	; writing to memory
	clr	ZL
	lsr	ZH
	ror	ZL		; move page number to 12:5 bits of PCPAGE (12:1 bits of Z)
	lsr	ZH
	ror	ZL		; move page number to 12:5 bits of PCPAGE (12:1 bits of Z)
;	mov	YH, ZH
;	mov	YL, ZL		; store value for next operations
;	ldi	XH, 1
;	ldi	XL, 0		; memory buffer address
	cpi	ZH, 0		; 0th page is protected
	breq	BL_LOOP
	cpi	ZH, high(M_RST*2)	; protection against corrupting bootloader itself
	brlo	BL_LOOP

fill_page:
	mov	YH, ZH
	mov	YL, ZL		; store value for next operations
        ldi	XH, 1		
        ldi	XL, 0           ; reset sram ptr
fill_page_loop:
	ld	r0, X+
	ld	r1, X+
	ldi	temp, 0b00000001; write tmp buf
	out	SPMCSR, temp
	WAIT_SPMEN
	adiw	Z, 2		; go to next word
	cpi	XL, 64		; next RAM word
	brne	fill_page_loop

erase_page:
	mov	ZL, YL
	mov	ZH, YH		; restore Z pointer
	ldi	temp, 0b00000011; erase page
	out	SPMCSR, temp
	WAIT_SPMEN

write_page:
	mov	ZL, YL
	mov	ZH, YH		; restore Z pointer
	ldi	temp, 0b00000101; write page command
	out	SPMCSR, temp
	WAIT_SPMEN

write_complete:
;	mov	ZL, YL
;	mov	ZH, YH		; restore Z pointer
;	adiw	Z, 32
;	adiw	Z, 32		; goto next page

;	cpi	ZH, high(BOOTLOADER*2)	; protection against corrupting bootloader itself
;halt:	brsh	halt		; just halt in this case, no idea what to do else

	rjmp	BL_LOOP		; loop until no more data and start signal received

; storing buffer in EEPROM -------------------------------
BL8:	
	clr	ZL
	lsr	ZH
	ror	ZL		; move page number to 12:5 bits of PCPAGE (12:1 bits of Z)
	lsr	ZH
	ror	ZL		; move page number to 12:5 bits of PCPAGE (12:1 bits of Z)

;	mov	YH, ZH
;	mov	YL, ZL		; store value for next operations
        ldi	XH, 1		
        ldi	XL, 0           ; reset sram ptr

BL10:
BL9:	sbic 	EECR, EEPE
	rjmp 	BL9		; Waiting for completion of previous write

	out	EEARH, ZH
	out	EEARL, ZL	; write address

	ld	temp, X+	; get next byte

	out 	EEDR, temp	; Write data to Data Register
	sbi 	EECR, EEMPE	; Write logical one to EEMPE
	sbi 	EECR, EEPE	; Start eeprom write by setting EEPE

	adiw 	Z, 1		; goto next byte
	cpi	XL, 64		; all data written?
	brne	BL10		; loop for all 64 bytes

	rjmp	BL_LOOP		; Wait for next block
	
;SPI_START:
;	ldi 	temp, (1<<USIWM0)|(1<<USICS1)	; start SPI
;	out 	USICR, temp
;	ldi	temp, (1<<PA4)|(1<<PA5)		; DO and USCK pins are enabled as outputs in DDRA
;	ldi	temp, (1<<PA5)	; DO is enabled as outputs in DDRA
;	out	DDRA, temp
;	ret

;SPI_STOP:
;	ldi 	temp, 0		; stop SPI
;	out 	USICR, zero
;	ldi	temp, 0		; DO and USCK pins are disabled as outputs in DDRA
;	out	DDRA, zero
;	ret

SPI:
	sbic	PINB, PB2	; check that CS=low
	rjmp	BOOTLOADER	; full restart if CS==hi
SlaveSPITransfer:
	out 	USIDR, temp
	ldi 	temp, (1<<USIOIF)
	out 	USISR, temp
SlaveSPITransfer_loop:
	in 	temp, USISR
	sbrs 	temp, USIOIF
	rjmp 	SlaveSPITransfer_loop
	in 	temp, USIDR
	ret

BOOTLOADER_END:
	nop

; Main Code Interrupt Vector ----------------------------------------------------------
	.ORG	0x100	; PAGE 1 - Main program Int vector
M_RST:	rjmp	MAIN	; reset
M_INT0:	rjmp	MAIN	
M_PCI0:	rjmp	MAIN	
M_PCI1:	rjmp	MAIN	
M_WDT:	rjmp	MAIN	
M_ICP1:	rjmp	MAIN	
M_OC1A:	rjmp	MAIN	
M_OC1B:	rjmp	MAIN	
M_OVF1:	rjmp	MAIN	
M_OC0A:	rjmp	MAIN	
M_OC0B:	rjmp	MAIN	
M_OVF0:	rjmp	MAIN	
M_ACI:	rjmp	MAIN	
M_ADCC:	rjmp	MAIN	
M_ERDY:	rjmp	MAIN	
M_USIS:	rjmp	MAIN
M_USIO:	rjmp	MAIN

	.ORG	M_RST+32	; PAGE 1 - Main part code starts here
MAIN:	rjmp	MAIN

