.include "m328def.inc"
.include "macro.def"

.include "regs.def"
.include "irq.def"

.CSEG
.ORG 	0
    	rjmp	_START

.ORG INT0addr         		; keyboard pulse received
	in	_sreg, SREG     ; save SREG
	sts	TCNT2, zero     ; clear timeout counter
	inc	kbcntr          ; pulse counter
	cpi	kbcntr, 10
	brsh	L_KBI_01
	lsr	kbdata		; kbdata<<=1
	sbic	PIND, PD4
	sbr	kbdata, 0x80
	rjmp	DO_RETI
L_KBI_01:
    	breq	DO_RETI
    	clr	kbcntr
	mov	kbread, kbdata
DO_RETI:
;	RETI_S
	out	SREG, _sreg
	reti

	; timeout timer overflow
	; keyboard timeout detected
.ORG  OVF2addr
    	mov	kbcntr, zero
    	mov	kbledr, zero	
    	mov	kbread, zero
    	mov	kbdata, zero	; reset keyboard
    	reti

    	; dummy point for rejump
.ORG  	OC0Baddr
_START:
    	jmp   	START

    	; SPI interrupt
.ORG 	SPIaddr
    	in    	_sreg, SREG
.include "cpurequest.inc"
;	RETI_S
	out   	SREG, _sreg
	reti		

;.ORG	INT_VECTORS_SIZE

.ORG	0x200
_RESET:
START:	
.include "init.inc"
.include "startup.inc"

	sei			; start working
	rjmp	VGA_EXEC

.ORG	0x300
MLOOP:
KBL_START:
.include "ps2kbd_leds.inc"

.ORG	0x400
KBL_EXIT:
KBD_START:
.include "ps2kbd.inc"

.ORG	0x500
KBD_EXIT:
VGA_START:
;	lds	tdata, irqfl
;	MEM_HEX 0x0108
.include "vga.inc"

.ORG	0x600
VGA_EXIT:
TWI_START:
.include "i2cext.inc"

.ORG	0x800
TWI_EXIT:
COM_START:
.include "comport.inc"

.ORG	0x900
COM_EXIT:
MUS_START:
.include "melody.inc"

.ORG	0xa00
MUS_EXIT:
TMR_START:
;	lds	tdata, irqfl
;	MEM_HEX 0x010a
.include "timer.inc"

.ORG	0x0b00
TMR_EXIT:
SRP_START:
;	lds	tdata, irqfl
;	MEM_HEX 0x010c

.include "sysr_port.inc"

.ORG	0x0c00
SRP_EXIT:
IRQ_START:
.include "irq.inc"

.ORG	0x0d00
IRQ_EXIT:

	jmp	MLOOP

.include "local.inc"
.include "mice.inc"

; ----------------------------------------------------------------------------------------
; ----------- DATA SECTION ---------------------------------------------------------------

;.ORG	0x0c00;2048
;MISCDATA:
;.ORG    MISCDATA
;SU_DATA:
;.include "startup_data.inc"

.ORG    0x1000;SU_DATA+1024
PS2KBDDATA:
.include "ps2kbd_data.inc"

.ORG    0x1200;decode+128
KBDCHARTABLE:
.include "ps2kbd_charcodes.inc"	; 2048 bytes

.ORG    0x2200;decode+128
MUSMISCDATA:
.include "mus_data.inc"	; 4*256 bytes

; RAM DEFENITION -------------------------------------------------------------------------

.include "ram.def"
