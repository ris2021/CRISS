#include "m1284def.inc"

#include "flags.def"
#include "macro.def"
#include "regs.def"
#include "commons.def"
#include "bios.def"
#include "bdos.def"

;.MACRO	IRQ_INT
;	sbi	GPIOR0, 7
;	sbi	GPIOR0, @0
;	reti
;.ENDM

.ORG 	0
	rjmp	RESET

.ORG	PCI3addr
	rjmp	PCI3_INT

.ORG	OC2Aaddr
	rjmp	TMR_10MS_INC

.ORG	URXC1addr
	rjmp	URXC1_INT

.ORG	UDRE1addr
	sbi	GPIOR0, IRQ_V_TTX
	rjmp	INT_RETI

#include "spi.def"
#include "lan.def"
#include "lan_local.def"		; settings for CRISS project
#include "can.def"

.ORG    INT_VECTORS_SIZE

TMR_10MS_INC:				; inc timer counter
	push	temp
	in	temp, SREG
	push	temp
	lds	temp, TMR_10MS
	inc	temp
	sts	TMR_10MS, temp
	pop	temp
	out	SREG, temp
	pop	temp
	reti

PCI3_INT:
        sbic	PIND, 7
	sbi	GPIOR0, IRQ_V_LAN
        sbic	PIND, 6
	sbi	GPIOR0, IRQ_V_RTC
        sbic	PIND, 0
	sbi	GPIOR0, IRQ_V_CPD
	rjmp	INT_RETI			; response any interrupt, set up via enble/disable specifiq INT

URXC1_INT:
	sbi	GPIOR0, IRQ_V_TRX

INT_RETI:
	push	temp
	ldi	temp, high(IRQOPCODES)	; next command will execute IRQ handler
	out	GPIOR2, temp		; !!!!! restore!!!!!
	pop	temp
	reti

; standard SPI output: in in temp, out to temp
DOSPI:
	out	SPDR, temp
DOSPI_L1:	
	in	temp, SPSR
	sbrs	temp, SPIF
	rjmp	DOSPI_L1
	in	temp, SPDR
	ret

; output to videoram
VIDEO:
	nop
	ret

RESET:
  	_outw	SPL, SPH, RAMEND	; init stack pointer
	call	INITPROC
	call	HW_INIT
    	call	z80INITPROC
    	call	DOSTART    		; welcome and initial tests
	rjmp	z80_start

#include "z80.def"
#include "ports.def"                    ; i/o ports defines

#include "debug.def"                    ; debug defines

.ORG  0x200              ; 04

z80_START:
zCMD_NONI: ; NONI == zCMDstart
zCMD_start:

;	sbic	GPIOR0, 7		; check interrupt request
;	call	EXTINTRPOC		; call if any	
;	call	DEBUG_Z80
;	call	DBG_UART_CMD
;	ldi Xh, high(zOPCODE__LBLS_L)
	in 	Xh, GPIOR2		; high(zOPCODE__LBLS_L)
zCMDP_start:
	LDRAM_PC Xl			; command OPCODE

zCMDP_decode:
	ld Zl, 	X			; decoding processor pointer
	inc Xh
	ld Zh, 	X

	ijmp				; goto command processing

.ORG  0x300                ; 06

#include "z80/z80_asm_cseg.asm"		; interrupts disabled block
zCMD_END:	nop

;.ORG  0x4000
;iz80_START:
;izCMD_NONI: ; NONI == zCMDstart
;izCMD_start:
;	sbic	GPIOR0, 7		; check interrupt request
;	call	EXTINTRPOC
;#include "z80/z80_asm_icseg.asm"       ; interrupts enabled block
;izCMD_END:	nop

.ORG  0x7000                ; E0

#include "extirq.inc"

DBG_NONE:
	ret


; --------------------- BDOS, BIOS, PORTS -------------------------------

.ORG  0x7200            ; E4

BIOS:		jmp	BIOS_START
BIOS_CMD:       jmp	BIOS_CMD_START
BDOS:		jmp	BDOS_START
PORTIN: 	jmp	PORTIN_CMD
PORTOUT:	jmp	PORTOUT_CMD
CPDPORTOUT:	jmp	CPDPORTOUT_CMD
CPDPORTIN:	jmp	CPDPORTIN_CMD

;.ORG ...
_BIOS_START:
#include "bios.inc"			; BIOS extended commands
BIOS_END:

;.ORG ...
_BDOS_START:
#include "bdos.inc"			; BDOS extended commands
BDOS_END:

;.ORG ...
PORTS_START:
#include "ports.inc"                    ; i/o ports processing commands
;#include "svideo.inc" 			; svideo-adapter ports processing commands
PORTS_END:

; --------------------- WELCOME, TOOLS --------------------

.ORG 0x08800		; 1 10

INITPROC:	jmp	INITPROC_CMD
z80INITPROC:	jmp	z80INITPROC_CMD
DOSTART:	jmp	DOSTART_CMD

INITPROC_START:
#include  "init.inc"			; initializing
#include  "z80init.inc"			; initializing z80 data
INITPROC_END:

;.ORG ...
COMMONS:
#include "commons.inc"                  ; misc procedures for start.inc
COMMONS_END:

;.ORG ...
DOSTART_START:
#include "start.inc"			; welcome screen and startup testing
START_END:

#include "start_msg.inc"		; startup messages
#include "bios_mice_data.inc"		; automouse settings
#include "bios_misc_data.inc"		; misc bios data

; --------------------- onboard devices ---------------------------------------

; --------------------- SD --------------------

.ORG 0x09000            ; 1 20-26
SD_START:
#include "sd.inc"			; sd card routines
;#include "sd_cmd.inc"
SD_END:

; !!! Ethernet !!!
.ORG 0x09400            ; 1 28-47
LAN_START:
#include "lan.inc"			; lan access routines
LAN_END:
;	nop

.ORG 0x0a400		; 1 48
CAN_START:
#include "can.inc"			; can access routines
CAN_END:

.ORG 0x0b000            ; 1 60
DEBUG_START:
#include "debug.inc"			; 
#include "debug_z80.inc"			; 
DEBUG__END:

.ORG 0x0b300            ; 1 66
EEPROM_START:
#include "eeprom.inc"			; eeprom access routines
#include "rtc.inc"			; rtc access routines
EEPROM__END:

;HALT:	rjmp	HALT			; dummy STOP


; --------------------- HW compatibility layer -------------------------------

.ORG 0x0b500            ; 1 6a-..
HWC_START:
#include "hw_layer.inc"			; hw compatibility routines
HWC_END:

FE_USER_START:
#include "user_port_fe.inc"		; fe cmd port user routines
FE_USER_END:

FLOAT_START:
#include "float.asm"			; float point co-processor library
FLOAT_END:


; --------------------  system console ----------------------------------------

.ORG 0x0c400            ; 1 8a-9f
CAD_START:
#include "CtrlAltDel.inc"		; Ctrl-Alt-Del NMI
CAD_END:


; z80 data settings ----------------------------------------
; DATA here MUST be aligned!!!

.ORG 0x0d000		;1 a0-		; Data area
ROMDATA:
#include "z80/z80_asm_ecseg.asm"	; 14*256

;iROMDATA:
;#include "z80/z80_asm_iecseg.asm"

#include "z80/z80_asm_pftdata.asm"      ; 256
#include "z80/z80_flagtranslate.asm"    ; 2*256
#include "z80/z80_daadata.asm"          ; 4096

; -------------------------- RAM ---------------------------

.DSEG

#include "ram.def"

