#include "tn84def.inc"

.EQU	N_BLOCKS = 20

; RAM definitions --------------------------------------------------------------
.DSEG
.ORG	0x60
CATR:	.BYTE	24*N_BLOCKS	; attributes
CATR_END:
PBUF:	.BYTE	N_BLOCKS	; buffer area for the block processing
PBUF_END:
TMPVAR:
;PVAL:	.BYTE	1		; new pattern is stored here
STACK:	.BYTE	RAMEND-PBUF_END	; stack

.CSEG
	.ORG	0	; PAGE 1 - Main program Int vector
START:	rjmp	BOOTLOADER

	.ORG 	32
BOOTLOADER:

; Main Code Interrupt Vector ----------------------------------------------------------
	.ORG	0x100	; Main program Int vector
M_RST:	rjmp	MAIN	; reset
M_INT0:	rjmp	P_INT0	; CS
M_PCI0:	rjmp	P_PCI0	; VS
M_PCI1:	rjmp	P_PCI1	; HS
M_WDT:	rjmp	MAIN	
M_ICP1:	rjmp	MAIN	
M_OC1A:	rjmp	P_OC1A	; RTR timer
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


	; registers definition
	.DEF	tmp0	 =r0	; 
	.DEF	tmp1	 =r1	; aux temp vars

	.DEF	zero	 =r2	; 0

	.DEF	_xh	 =r3	; store xh here
	.DEF	_xl	 =r4	; store xl here

	.DEF	defclr	 =r5	; default color

	.DEF	charsize =r6	; 20
	.DEF	linesno	 =r7	; 24

	.DEF	pos_y	 =r8    ; line
	.DEF	pos_x	 =r9	; char

	.DEF	_sreg	 =r10   ; store sreg in interrupts

	.DEF	DataS	 =r11	; Status Sent to master
	.DEF	dataR	 =r12	; return to master data

  	.DEF	temp6	 =r13

; 	.DEF	_usidr	 =r14	; 
;	.DEF	_zl	 =r15	; store Z register

	.DEF	temp2	 =r16
	.DEF	temp	 =r17
	.DEF	line	 =r18	; totasl line counter from the VS
	.DEF	temp4	 =r19	; target block counter
	.DEF	lmode 	 =r20
	.DEF	itemp	 =r21

	.DEF	sline	 =r22
	.DEF	stroke	 =r23
	.DEF	temp3 	 =r24	; block counter for pattern update
	.DEF	temp5 	 =r25
;	X - RAM current ptr (interrupt)
;	Y - RAM stored ptr  (interrupt)
;	Z - 


; Interrupt Ruotines Start Here --------------------------------------------------------
	.ORG	0x120	; PAGE 2 - Main part code starts here


; SPI CS signal
P_INT0:	
	mov	DataS, DataR	; data sent to master
;	bld	DataS, 5

	brtc	_int0_spi_l1	; BUSY?
	mov 	DataS, zero	; return BUSY value
_int0_spi_l1:
	out	USIDR, DataS	; Send response

	ldi 	itemp, (1<<USIOIF)
	out 	USISR, itemp	; clear overflow flag

	sbi	DDRA, PA5			; +2 - MISO pin to out
	ldi 	itemp, (1<<USIWM0)|(1<<USICS1)	; +1 - start SPI
	out 	USICR, itemp			; +1

_int0_spi_loop:
	in 	itemp, USISR
	sbrs 	itemp, USIOIF
	rjmp 	_int0_spi_loop	; waiting for data received

	cbi	DDRA, PA5	; MISO pin to in
	out 	USICR, zero	; stop SPI

;	in	_usidr, USIDR	; read last received data	

	cpse	DataS, zero
	set			; flag that data ready if sent code != 0
	reti



; PCINT7 - VS
P_PCI0: 
	sbic	PINA, PA7
	reti			; check for correct front

;	in	_sreg, SREG
	mov 	line, zero
;	mov	stroke, zero
;	mov	sline, zero
	ldi	lmode, 1	; new frame
;	ldi	YH, high(CATR)
;	ldi	YL, low(CATR)	; getting pattern for the first line
;	out	SREG, _sreg
	reti



; PCINT9 - HS
P_PCI1: 
	sbic	PINB, PB1
	rjmp	_hs_dataline

CHECK_SPI:
	sbic	PINB, PB2	; check CS pin
	reti

	mov	DataS, DataR	; data sent to master
;	bld	DataS, 5
	brtc	_check_spi_l1	; Not BUSY?
	mov 	DataS, zero	; return BUSY value
_check_spi_l1:
	out	USIDR, DataS	; Send response

	sbi	DDRA, PA5			; +2 - MISO pin to out
	ldi 	itemp, (1<<USIWM0)|(1<<USICS1)	; +1 - start SPI
	out 	USICR, itemp			; +1

	reti
	
_hs_dl_l1:
	nop
;	nop
	rjmp	_hs_dl_l2	; +2

_hs_dataline:
	in	_sreg, SREG

	sbis	USICR, USIWM0	; +1/2
	rjmp	_hs_dl_l1	; +2 no SPI active  	

;	in	_usidr, USIDR	; read last received data	
	out 	USICR, zero	; +1 stop SPI
	cbi	DDRA, PA5	; +2 MISO pin to in
	ldi	itemp, (1<<6)	; T-bit mask
	cpse	DataS, zero
	or	_sreg, itemp	; set T-bit
				; flag that data ready if sent code != 0

_hs_dl_l2:			; +6 after SREG store

	cpi	lmode, 0	; +1
	breq	DATALINE	; +2/+1

	cpi	lmode, 2	; +1
	breq	ENDI		; +2/+1

	; waiting for data frame
	inc	line		; +1
	cpi	line, 35	; +1	; VS back porche (33) + sync pulse (2)
	brne	ENDI
;	breq	BEREADY		; +2/+1

	ldi	lmode, 0	; +1 dataline mode
	mov	stroke, zero
	mov	sline, zero
	ldi	YH, high(CATR)
	ldi	YL, low(CATR)	; getting pattern for the first line

ENDI:	
	out	SREG, _sreg
	reti

;BEREADY: ; next line should be sent to output
;	ldi	lmode, 0	; +1 dataline mode
;    	out 	SREG, _sreg  	; restore SREG
;	reti

DATALINE:
	; data line
	; back porche		; +7 on entrance

	inc	stroke		; +1

;    	nop     ; +1    +2
;  	nop	; +1    +3
;    	nop	; +1    +4
;  	nop
;   	nop	; 
;    	nop	; 
   	nop	; 
    	nop
   	nop
;    	nop	; 
    	nop	; +14	it was 15 in previous version, -1 due to _sreg
;   	nop
;    	nop
;   	nop
;    	nop
	mov	_xh, XH
	mov	_xl, XL		; save for restore
	mov	XH, YH
	mov	XL, YL		; pattern pointer restore

DRAWLN:
#include "line.inc"

DATALINE80END:
	cp	stroke, charsize; +1
	breq	ENDOFLINE	; +2

;	mov	XH, YH
;	mov	XL, YL		; +2 pattern pointer restore

	mov	XH, _xh
	mov	XL, _xl		; restore X
    	out 	SREG, _sreg   	; +1 restore SREG
	reti

ENDOFLINE:
	inc	sline		; +1	; inc sline
	clr	stroke		; +1	; reset stroke counter

	cp	sline, linesno	; +1
	breq	ENDOFDATA	; +2/+1	; end of lines reached

	adiw	Y, N_BLOCKS	; 20		; +2 goto next line pattern
;	mov	XH, YH
;	mov	XL, YL		; +@ active pattern pointer set

	mov	XH, _xh
	mov	XL, _xl		; restore X
    	out 	SREG, _sreg   	; restore SREG
	reti

ENDOFDATA:
	ldi	lmode, 2	; +1 ignore till VS reset

	mov	XH, _xh
	mov	XL, _xl		; restore X
    	out 	SREG, _sreg   	; restore SREG
	reti



; RTR timer - not used
P_OC1A: reti

#include "macro.def"


; Main Program Starts Here -------------------------------------------------------------
MAIN:
	cbi	DDRA, PA5	; MISO pin to in

	ldi	temp, low(RAMEND)
	out	SPL, temp
	ldi	temp, high(RAMEND)
	out	SPH, temp	; stack

	clr	zero		; set to 0

	out	DDRA, zero
	out 	DDRB, zero	; all pins to input

	clr	pos_x
	clr	pos_y

	ldi	temp, 20
	mov	charsize, temp	; symbol height
	ldi	temp, 24
	mov	linesno, temp	; lines per screen
	ldi	temp, 2
	mov	lmode, temp	; wait for VS

	out	PORTA, zero	; 

	cli
	ldi	temp, (1<<ISC01)
	out	MCUCR, temp	; The falling edge of INT0 generates an interrupt request.
	ldi	temp, (1<<PCINT7)
	out	PCMSK0, temp	; VS
	ldi	temp, (1<<PCINT9)
	out	PCMSK1, temp	; HS

EEPROM_read:	; Wait for completion of previous write
	sbic 	EECR, EEPE
	rjmp 	EEPROM_read
	ldi	temp, high(512-1)
	out 	EEARH, temp
	ldi	temp, low(512-1)
	out 	EEARL, temp	; Set up address in address registers
	sbi 	EECR, EERE	; Start eeprom read by writing EERE
	in 	temp, EEDR	; eprclr Read data from data register
	out	GPIOR1, temp	; eprclr

	mov	defclr, temp	; eprclr

;	sts	TMPVAR, defclr	;!!!!!debug!!!!
	mov	DataR, zero	; Busy state
;	mov	DataS, zero	; Not ready state
	out	USICR, zero	; stop SPI
	set
	cbi	PORTA, PA5	; MISO low by default

	rcall	MODE_SET_0	; set single color default mode and sei
	
	sbi	DDRA, PA2
	sbi	DDRA, PA1
	sbi	DDRA, PA0	; color setting pins set to output

	rjmp	_ml_clear_screen	; fust for the case clear screen before start


MAIN_LOOP:

;_wait_spi_off:
;	in	temp2, USICR
;	cpi	temp2, 0
;	brne	_wait_spi_off

	mov	temp2, defclr	; return code - default color
	sbr	temp2, 0x10	; ensure that DataR != 0
	mov	DataR, temp2	; Report current state 
	clt			; clear T flag == RTR

;	lds	temp, TMPVAR	;!!!!!debug!!!!
;	cp	temp, zero	;!!!!!debug!!!!
;	brne	_ml_tmp_l1	;!!!!!debug!!!!
;	mov	temp, temp2	;!!!!!debug!!!!
;_ml_tmp_l1:	
;	mov	DataR, temp		;!!!!!debug!!!!

;	ldi 	temp2, (1<<USIOIF)
;	out 	USISR, temp2	; clear overflow flag - ready for next 

_ml_wait_spi_data:
	brtc	_ml_wait_spi_data	; wait data ready T-flag == 1

;	in 	temp2, USISR
;	sbrs 	temp2, USIOIF
;	rjmp	_ml_wait_spi_data	; wait data received
;_ml_wait_dataS:
;	cp 	DataS, zero
;	breq	_ml_wait_spi_data	; wait DataS !=0

	in	temp, USIDR	; read last received data	
;	mov	temp, _usidr	; read last received data	

	sbrc	temp, 7		; bit 7th is set == pattern
	rjmp	_ml_set_pattern

	ldi	ZH, high(JMP_TBL*2)
	mov	ZL, temp
	lsl	ZL
	lpm	temp2, Z+
	lpm	ZH, Z
	mov	ZL, temp2
	ijmp

	rjmp	MAIN_LOOP


_ml_function_125:
	rjmp	MAIN_LOOP	; !!! reserved


_ml_toggle_video:
	mov	temp, defclr
	sbr	temp, (1<<PA3)	; disable video
	sbi	DDRA, PA3	; pin to output
	rcall	MODE_SET_USER
	rjmp	MAIN_LOOP


_ml_clear_line:
	ldi	ZH, high(CATR)
	ldi	ZL, low(CATR)
	mov	temp, pos_y
	cpi	temp, 0
	breq	_ml_cl_fill
_ml_cl_loop:
	adiw	Z, N_BLOCKS	; 20 blocks count
	dec	temp
	brne	_ml_cl_loop
_ml_cl_fill:
	FILL_LINE_Z
	rjmp	MAIN_LOOP


_ml_clear_screen:
	ldi	ZH, high(CATR)
	ldi	ZL, low(CATR)
	ldi	temp2, 24
_ml_cs_loop:
	FILL_LINE_Z
	dec	temp2
	brne	_ml_cs_loop
	rjmp	MAIN_LOOP


_ml_set_wmode_pattern:
	rcall	MODE_SET_PATTERN
	rjmp	_ml_clear_screen
;	rjmp	MAIN_LOOP


_ml_set_def_pattern:
	rcall	MODE_SET_DEFAULT_PATTERN
	rjmp	MAIN_LOOP


_ml_set_def:
	rcall	MODE_SET_0
	rjmp	_ml_clear_screen
;	rjmp	MAIN_LOOP


_ml_set_user:
	subi	temp, 1
	rcall	MODE_SET_USER
	rjmp	_ml_clear_screen
;	rjmp	MAIN_LOOP


_ml_set_eeprom:
	subi	temp, 9
EEPROM_write:
	sbic 	EECR, EEPE
	rjmp 	EEPROM_write	; Wait for completion of previous write

	ldi 	temp2, (0<<EEPM1)|(0<<EEPM0)
	out 	EECR, temp2	; Set Programming mode
	ldi	temp2, high(512-1)
	out 	EEARH, temp2
	ldi	temp2, low(512-1)
	out 	EEARL, temp2	; Set up address in address registers
	out 	EEDR, temp	; Write data to data register
	cli
	sbi 	EECR, EEMPE	; Write logical one to EEMPE
	sbi 	EECR, EEPE	; Start eeprom write by setting EEPE
	sei

;	mov	eprclr, temp	; update eeprom color
	out	GPIOR1, temp

	rjmp	MAIN_LOOP


_ml_set_char:
	subi	temp, 17
	cpi	temp, 80
	brsh	_ml_set_char_ret
	mov	pos_x, temp
_ml_set_char_ret:
	rjmp	MAIN_LOOP


_ml_set_line:
	subi	temp, 97
	cpi	temp, 24
	brsh	_ml_set_line_ret
	mov	pos_y, temp	; set y position
_ml_set_line_ret:
	rjmp	MAIN_LOOP


_ml_scroll_screen:
	ldi	ZH, high(CATR)
	ldi	ZL, low(CATR)
_ml_ss_loop:
	ldd	temp, Z+N_BLOCKS	; 20 blocks max
	st	Z+, temp
	cpi	ZH, high(CATR_END-N_BLOCKS)	; 20
	brne	_ml_ss_loop
	cpi	ZL, low(CATR_END-N_BLOCKS)	; 20
	brne	_ml_ss_loop
_ml_ss_fill:
	FILL_LINE_Z	; fill line
	rjmp	MAIN_LOOP


_ml_set_pattern:
	; pattern processing
_ml_wait_ora:
;	sts	PVAL, temp	; store pattern
	out	GPIOR2, temp	; PVAL

	rcall	PATTERN_COPY_LINE_BUF
	rcall	APPLY_PATTERN

	;compare pos_y with the current line
_ml_wait_line:
	mov	temp, sline
	cp	pos_y, temp
	breq	_ml_wait_line	;!!! test version
	brlo	_ml_wait_l1
	inc	temp
	cp	pos_y, temp
	breq	_ml_wait_line	;!!! test version

_ml_wait_l1:
;	cp	pos_y, sline
;	breq	_ml_wait_line	;!!! test version

	rcall	PATTERN_COPY_BUF_LINE
	rjmp	MAIN_LOOP


MODE_SET_0:
;	mov	temp, eprclr	; set default color	
	in	temp, GPIOR1	; eprclr
MODE_SET_USER:	
	cli

        sbrs    temp, PA3
        cbi	DDRA, PA3	; disable output if no request	

	andi	temp, 0x0f	; just for the case
	out	PORTA, temp	; set  color 

	mov	defclr, temp	; store default color
	ldi	sline, 0x80	; set line counter greater than pos_y

	ldi	temp, (1<<INTF0)
	out	GIFR, temp	; clear flags
	ldi	temp, (1<<INT0)	; INT0 CS interrupt enabled
	out	GIMSK, temp	; INT0 CS interrupt enabled

	mov	DataR, zero	; busy
;	mov	DataS, zero	; busy
;	out	GPIOR0, zero	; busy
	set

	sei			; enable interrupts
	ret


MODE_SET_PATTERN:
MODE_SET_PATTERN_INT:
	cli

	mov	temp, defclr
	cbr	temp, (1<<PA3)
	mov	defclr, temp

        cbi	DDRA, PA3	; disable PA3 - enable video

	ldi	lmode, 2	; ignore HS till VS reset
	clr	sline		; reset lime counter

	ldi	temp, (1<<PCIF0)|(1<<PCIF1)
	out	GIFR, temp		; clear flags
	ldi	temp, (1<<PCIE1)|(1<<PCIE0)	; Pin change interrupts enabled
	out	GIMSK, temp	; Pin change interrupts enabled

	mov	DataR, zero	; busy
;	mov	DataS, zero	; busy
;	out	GPIOR0, zero	; busy
	set

	sei				; enable interrupts
	ret



MODE_SET_DEFAULT_PATTERN:
	; load default pattern to the RAM
	ldi	XH, high(CATR)
	ldi	XL, low(CATR)	; start point in ram
	ldi	ZH, 0
	ldi	ZL, 0		; start point in EEPROM
_m_set_def_L1:			; 
	out	EEARH, ZH
	out	EEARL, ZL	; Address to read
	sbi 	EECR, EERE	; read request
	in 	temp, EEDR	; read char from eeprom
	st	X+, temp	; store char in RAM
	adiw	Z, 1
	cpi	XL, low(PBUF)
	brne	_m_set_def_L1
	cpi	XH, high(PBUF)
	brne	_m_set_def_L1

;	ldi	temp, 2
	rjmp	MODE_SET_PATTERN_INT





#include "pattern.inc"

.ORG	0x600
#include "jmp_table.inc"
