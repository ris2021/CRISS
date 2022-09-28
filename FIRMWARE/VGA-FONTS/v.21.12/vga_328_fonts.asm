.include "m328def.inc"


; program part -----------------------------------------------------------------------------------------
.CSEG
.ORG	0
	nop

.ORG	0x400			; 10-37
CP_DATA_START:
.include "CP0_font8x20-256.asm" ; 10-37
.include "CP1_font8x20-256.asm"	; 38-5f
.include "CP2_font8x20-256.asm"	; 60-87
.include "CP3_font8x20-256.asm"	; 88-af
.include "CP4_font8x20-256.asm"	; b0-d7
;.include "CP5_font8x20-256.asm"

;.ORG	0x3f0
LB:	.DB	0x00, 0x00

