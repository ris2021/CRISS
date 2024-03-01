zCMD_00: ; NOP   
	

	jmp zCMD_start

zCMD_01: ; LD   BC nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzB, FROMRAM1
	mov zzC, FROMRAM2

	jmp zCMD_start

zCMD_02: ; LD   (BC) A
	mov FROMRAM0,zzA

	STRAM zzB,zzC,zzA
	jmp zCMD_start

zCMD_03: ; INC   BC
	INC2 zzB,zzC

	jmp zCMD_start

zCMD_04: ; INC   B
	add zzB,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_05: ; DEC   B
	sub zzB,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_06: ; LD   B n
	LDRAM_PC_NODDR FROMRAM0
	mov zzB,FROMRAM0

	jmp zCMD_start

zCMD_07: ; RLCA  
	bst zzA,7
	rol zzA
	bld zzA,0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_08: ; EX   AF AFe
	EX zzA,zzAe
	EX zzF,zzFe

	jmp zCMD_start

zCMD_09: ; ADD  HL BC
	add zzL,zzC
	adc zzH,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_0a: ; LD   A (BC)
	LDRAM_NODDR zzB,zzC,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMD_0b: ; DEC   BC
	DEC2 zzB,zzC

	jmp zCMD_start

zCMD_0c: ; INC   C
	add zzC,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_0d: ; DEC   C
	sub zzC,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_0e: ; LD   C n
	LDRAM_PC_NODDR FROMRAM0
	mov zzC,FROMRAM0

	jmp zCMD_start

zCMD_0f: ; RRCA  
	bst zzA,0
	ror zzA
	bld zzA,7

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_10: ; DJNZ  s
	LDRAM_PC_NODDR FROMRAM0
	dec zzB
	breq zCMD_10_1
	ADDWS zzPCh,zzPCl,FROMRAM0
	zCMD_10_1:

	jmp zCMD_start

zCMD_11: ; LD   DE nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzD, FROMRAM1
	mov zzE, FROMRAM2

	jmp zCMD_start

zCMD_12: ; LD   (DE) A
	mov FROMRAM0,zzA

	STRAM zzD,zzE,zzA
	jmp zCMD_start

zCMD_13: ; INC   DE
	INC2 zzD,zzE

	jmp zCMD_start

zCMD_14: ; INC   D
	add zzD,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_15: ; DEC   D
	sub zzD,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_16: ; LD   D n
	LDRAM_PC_NODDR FROMRAM0
	mov zzD,FROMRAM0

	jmp zCMD_start

zCMD_17: ; RLA   
	out SREG,zzF
	rol zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_18: ; JR   * s
	LDRAM_PC_NODDR FROMRAM0
	cpse ZERO,ZERO
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMD_19: ; ADD  HL DE
	add zzL,zzE
	adc zzH,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_1a: ; LD   A (DE)
	LDRAM_NODDR zzD,zzE,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMD_1b: ; DEC   DE
	DEC2 zzD,zzE

	jmp zCMD_start

zCMD_1c: ; INC   E
	add zzE,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_1d: ; DEC   E
	sub zzE,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_1e: ; LD   E n
	LDRAM_PC_NODDR FROMRAM0
	mov zzE,FROMRAM0

	jmp zCMD_start

zCMD_1f: ; RRA   
	out SREG,zzF
	ror zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_20: ; JR   NZ s
	LDRAM_PC_NODDR FROMRAM0
	sbrc zzF,zzZF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMD_21: ; LD   HL nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzH, FROMRAM1
	mov zzL, FROMRAM2

	jmp zCMD_start

zCMD_22: ; LD   (ww) HL
	

	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	STRAM FROMRAM1,FROMRAM2,zzL
	INC2 FROMRAM1,FROMRAM2
	STRAM FROMRAM1,FROMRAM2,zzH
	jmp zCMD_start

zCMD_23: ; INC   HL
	INC2 zzH,zzL

	jmp zCMD_start

zCMD_24: ; INC   H
	add zzH,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_25: ; DEC   H
	sub zzH,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_26: ; LD   H n
	LDRAM_PC_NODDR FROMRAM0
	mov zzH,FROMRAM0

	jmp zCMD_start

zCMD_27: ; DAA   
	zzDAA

	jmp zCMD_start

zCMD_28: ; JR   Z s
	LDRAM_PC_NODDR FROMRAM0
	sbrs zzF,zzZF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMD_29: ; ADD  HL HL
	add zzL,zzL
	adc zzH,zzH

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_2a: ; LD   HL (ww)
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzL
	INC2 FROMRAM1,FROMRAM2
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzH
	

	jmp zCMD_start

zCMD_2b: ; DEC   HL
	DEC2 zzH,zzL

	jmp zCMD_start

zCMD_2c: ; INC   L
	add zzL,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_2d: ; DEC   L
	sub zzL,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_2e: ; LD   L n
	LDRAM_PC_NODDR FROMRAM0
	mov zzL,FROMRAM0

	jmp zCMD_start

zCMD_2f: ; CPL   A
	com zzA

	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|_N_|___) ; set flags
	jmp zCMD_start

zCMD_30: ; JR   NC s
	LDRAM_PC_NODDR FROMRAM0
	sbrc zzF,zzCF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMD_31: ; LD   SP nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzSPh, FROMRAM1
	mov zzSPl, FROMRAM2

	jmp zCMD_start

zCMD_32: ; LD   (nn) A
	mov FROMRAM0,zzA

	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	STRAM FROMRAM1,FROMRAM2,zzA
	jmp zCMD_start

zCMD_33: ; INC   SP
	INC2 zzSPh,zzSPl

	jmp zCMD_start

zCMD_34: ; INC   (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	add FROMRAM0,ONE

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_35: ; DEC   (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	sub FROMRAM0,ONE

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_36: ; LD   (HL) n
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMD_37: ; SCF   
	

	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|___|_C_) ; set flags
	jmp zCMD_start

zCMD_38: ; JR   C s
	LDRAM_PC_NODDR FROMRAM0
	sbrs zzF,zzCF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMD_39: ; ADD  HL SP
	add zzL,zzSPl
	adc zzH,zzSPh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_3a: ; LD   A (nn)
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMD_3b: ; DEC   SP
	DEC2 zzSPh,zzSPl

	jmp zCMD_start

zCMD_3c: ; INC   A
	add zzA,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_3d: ; DEC   A
	sub zzA,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_3e: ; LD   A n
	LDRAM_PC_NODDR FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMD_3f: ; CCF   
	andi zzF,(_I_|_S_|_Z_|_V_|_C_)
	bst zzF,zzCF
	bld zzF,zzHF
	ldi zzTmp,1<<zzCF
	eor zzF,zzTmp

	jmp zCMD_start

zCMD_40: ; LD   B B
	mov zzB,zzB

	jmp zCMD_start

zCMD_41: ; LD   B C
	mov zzB,zzC

	jmp zCMD_start

zCMD_42: ; LD   B D
	mov zzB,zzD

	jmp zCMD_start

zCMD_43: ; LD   B E
	mov zzB,zzE

	jmp zCMD_start

zCMD_44: ; LD   B H
	mov zzB,zzH

	jmp zCMD_start

zCMD_45: ; LD   B L
	mov zzB,zzL

	jmp zCMD_start

zCMD_46: ; LD   B (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzB,FROMRAM0

	jmp zCMD_start

zCMD_47: ; LD   B A
	mov zzB,zzA

	jmp zCMD_start

zCMD_48: ; LD   C B
	mov zzC,zzB

	jmp zCMD_start

zCMD_49: ; LD   C C
	mov zzC,zzC

	jmp zCMD_start

zCMD_4a: ; LD   C D
	mov zzC,zzD

	jmp zCMD_start

zCMD_4b: ; LD   C E
	mov zzC,zzE

	jmp zCMD_start

zCMD_4c: ; LD   C H
	mov zzC,zzH

	jmp zCMD_start

zCMD_4d: ; LD   C L
	mov zzC,zzL

	jmp zCMD_start

zCMD_4e: ; LD   C (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzC,FROMRAM0

	jmp zCMD_start

zCMD_4f: ; LD   C A
	mov zzC,zzA

	jmp zCMD_start

zCMD_50: ; LD   D B
	mov zzD,zzB

	jmp zCMD_start

zCMD_51: ; LD   D C
	mov zzD,zzC

	jmp zCMD_start

zCMD_52: ; LD   D D
	mov zzD,zzD

	jmp zCMD_start

zCMD_53: ; LD   D E
	mov zzD,zzE

	jmp zCMD_start

zCMD_54: ; LD   D H
	mov zzD,zzH

	jmp zCMD_start

zCMD_55: ; LD   D L
	mov zzD,zzL

	jmp zCMD_start

zCMD_56: ; LD   D (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzD,FROMRAM0

	jmp zCMD_start

zCMD_57: ; LD   D A
	mov zzD,zzA

	jmp zCMD_start

zCMD_58: ; LD   E B
	mov zzE,zzB

	jmp zCMD_start

zCMD_59: ; LD   E C
	mov zzE,zzC

	jmp zCMD_start

zCMD_5a: ; LD   E D
	mov zzE,zzD

	jmp zCMD_start

zCMD_5b: ; LD   E E
	mov zzE,zzE

	jmp zCMD_start

zCMD_5c: ; LD   E H
	mov zzE,zzH

	jmp zCMD_start

zCMD_5d: ; LD   E L
	mov zzE,zzL

	jmp zCMD_start

zCMD_5e: ; LD   E (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzE,FROMRAM0

	jmp zCMD_start

zCMD_5f: ; LD   E A
	mov zzE,zzA

	jmp zCMD_start

zCMD_60: ; LD   H B
	mov zzH,zzB

	jmp zCMD_start

zCMD_61: ; LD   H C
	mov zzH,zzC

	jmp zCMD_start

zCMD_62: ; LD   H D
	mov zzH,zzD

	jmp zCMD_start

zCMD_63: ; LD   H E
	mov zzH,zzE

	jmp zCMD_start

zCMD_64: ; LD   H H
	mov zzH,zzH

	jmp zCMD_start

zCMD_65: ; LD   H L
	mov zzH,zzL

	jmp zCMD_start

zCMD_66: ; LD   H (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzH,FROMRAM0

	jmp zCMD_start

zCMD_67: ; LD   H A
	mov zzH,zzA

	jmp zCMD_start

zCMD_68: ; LD   L B
	mov zzL,zzB

	jmp zCMD_start

zCMD_69: ; LD   L C
	mov zzL,zzC

	jmp zCMD_start

zCMD_6a: ; LD   L D
	mov zzL,zzD

	jmp zCMD_start

zCMD_6b: ; LD   L E
	mov zzL,zzE

	jmp zCMD_start

zCMD_6c: ; LD   L H
	mov zzL,zzH

	jmp zCMD_start

zCMD_6d: ; LD   L L
	mov zzL,zzL

	jmp zCMD_start

zCMD_6e: ; LD   L (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzL,FROMRAM0

	jmp zCMD_start

zCMD_6f: ; LD   L A
	mov zzL,zzA

	jmp zCMD_start

zCMD_70: ; LD   (HL) B
	mov FROMRAM0,zzB

	in _sreg, SREG
	STRAM zzH,zzL,zzB
	out SREG,_sreg
	jmp zCMD_start

zCMD_71: ; LD   (HL) C
	mov FROMRAM0,zzC

	in _sreg, SREG
	STRAM zzH,zzL,zzC
	out SREG,_sreg
	jmp zCMD_start

zCMD_72: ; LD   (HL) D
	mov FROMRAM0,zzD

	in _sreg, SREG
	STRAM zzH,zzL,zzD
	out SREG,_sreg
	jmp zCMD_start

zCMD_73: ; LD   (HL) E
	mov FROMRAM0,zzE

	in _sreg, SREG
	STRAM zzH,zzL,zzE
	out SREG,_sreg
	jmp zCMD_start

zCMD_74: ; LD   (HL) H
	mov FROMRAM0,zzH

	in _sreg, SREG
	STRAM zzH,zzL,zzH
	out SREG,_sreg
	jmp zCMD_start

zCMD_75: ; LD   (HL) L
	mov FROMRAM0,zzL

	in _sreg, SREG
	STRAM zzH,zzL,zzL
	out SREG,_sreg
	jmp zCMD_start

zCMD_76: ; HALT  
	DEC2 zzPCh,zzPCl

	jmp zCMD_start

zCMD_77: ; LD   (HL) A
	mov FROMRAM0,zzA

	in _sreg, SREG
	STRAM zzH,zzL,zzA
	out SREG,_sreg
	jmp zCMD_start

zCMD_78: ; LD   A B
	mov zzA,zzB

	jmp zCMD_start

zCMD_79: ; LD   A C
	mov zzA,zzC

	jmp zCMD_start

zCMD_7a: ; LD   A D
	mov zzA,zzD

	jmp zCMD_start

zCMD_7b: ; LD   A E
	mov zzA,zzE

	jmp zCMD_start

zCMD_7c: ; LD   A H
	mov zzA,zzH

	jmp zCMD_start

zCMD_7d: ; LD   A L
	mov zzA,zzL

	jmp zCMD_start

zCMD_7e: ; LD   A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMD_7f: ; LD   A A
	mov zzA,zzA

	jmp zCMD_start

zCMD_80: ; ADD  A B
	add zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_81: ; ADD  A C
	add zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_82: ; ADD  A D
	add zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_83: ; ADD  A E
	add zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_84: ; ADD  A H
	add zzA,zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_85: ; ADD  A L
	add zzA,zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_86: ; ADD  A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	add zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_87: ; ADD  A A
	add zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_88: ; ADC  A B
	out SREG,zzF
	adc zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_89: ; ADC  A C
	out SREG,zzF
	adc zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_8a: ; ADC  A D
	out SREG,zzF
	adc zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_8b: ; ADC  A E
	out SREG,zzF
	adc zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_8c: ; ADC  A H
	out SREG,zzF
	adc zzA,zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_8d: ; ADC  A L
	out SREG,zzF
	adc zzA,zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_8e: ; ADC  A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	out SREG,zzF
	adc zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_8f: ; ADC  A A
	out SREG,zzF
	adc zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_90: ; SUB  A B
	sub zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_91: ; SUB  A C
	sub zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_92: ; SUB  A D
	sub zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_93: ; SUB  A E
	sub zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_94: ; SUB  A H
	sub zzA,zzH

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_95: ; SUB  A L
	sub zzA,zzL

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_96: ; SUB  A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	sub zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_97: ; SUB  A A
	sub zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_98: ; SBC  A B
	out SREG,zzF
	sez
	sbc zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_99: ; SBC  A C
	out SREG,zzF
	sez
	sbc zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_9a: ; SBC  A D
	out SREG,zzF
	sez
	sbc zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_9b: ; SBC  A E
	out SREG,zzF
	sez
	sbc zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_9c: ; SBC  A H
	out SREG,zzF
	sez
	sbc zzA,zzH

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_9d: ; SBC  A L
	out SREG,zzF
	sez
	sbc zzA,zzL

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_9e: ; SBC  A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	out SREG,zzF
	sez
	sbc zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_9f: ; SBC  A A
	out SREG,zzF
	sez
	sbc zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_a0: ; AND  A B
	and zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_a1: ; AND  A C
	and zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_a2: ; AND  A D
	and zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_a3: ; AND  A E
	and zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_a4: ; AND  A H
	and zzA,zzH

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_a5: ; AND  A L
	and zzA,zzL

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_a6: ; AND  A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	and zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_a7: ; AND  A A
	and zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_a8: ; XOR  A B
	eor zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_a9: ; XOR  A C
	eor zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_aa: ; XOR  A D
	eor zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_ab: ; XOR  A E
	eor zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_ac: ; XOR  A H
	eor zzA,zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_ad: ; XOR  A L
	eor zzA,zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_ae: ; XOR  A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	eor zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_af: ; XOR  A A
	eor zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_b0: ; OR   A B
	or zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_b1: ; OR   A C
	or zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_b2: ; OR   A D
	or zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_b3: ; OR   A E
	or zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_b4: ; OR   A H
	or zzA,zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_b5: ; OR   A L
	or zzA,zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_b6: ; OR   A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	or zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_b7: ; OR   A A
	or zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_b8: ; CP   A B
	cp zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_b9: ; CP   A C
	cp zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_ba: ; CP   A D
	cp zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_bb: ; CP   A E
	cp zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_bc: ; CP   A H
	cp zzA,zzH

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_bd: ; CP   A L
	cp zzA,zzL

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_be: ; CP   A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	cp zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_bf: ; CP   A A
	cp zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_c0: ; RET   NZ
	sbrc zzF,zzZF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMD_c1: ; POP   BC
	zzPOP zzB,zzC

	jmp zCMD_start

zCMD_c2: ; JP   NZ nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzZF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_c3: ; JP   * nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	cpse ZERO,ZERO
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_c4: ; CALL NZ nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzZF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_c5: ; PUSH  BC
	zzPUSH zzB,zzC

	jmp zCMD_start

zCMD_c6: ; ADD  A n
	LDRAM_PC_NODDR FROMRAM0
	add zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_c7: ; RST   00h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0

	jmp zCMD_start

zCMD_c8: ; RET   Z
	sbrs zzF,zzZF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMD_c9: ; RET   *
	cpse ZERO,ZERO
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMD_ca: ; JP   Z nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzZF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_cb: ; CB*   
	ldi Xh, high(zOPCODE_CB_LBLS_L)
	jmp zCMDP_start

	jmp zCMD_start

zCMD_cc: ; CALL Z nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzZF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_cd: ; CALL * nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	cpse ZERO,ZERO
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_ce: ; ADC  A n
	LDRAM_PC_NODDR FROMRAM0
	out SREG,zzF
	adc zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMD_cf: ; RST   08h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x08

	jmp zCMD_start

zCMD_d0: ; RET   NC
	sbrc zzF,zzCF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMD_d1: ; POP   DE
	zzPOP zzD,zzE

	jmp zCMD_start

zCMD_d2: ; JP   NC nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzCF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_d3: ; OUT  (n) A
	LDRAM_PC_NODDR FROMRAM0
	mov zzTmp,FROMRAM0
	sts CDATA,zzA
	call PORTOUT

	jmp zCMD_start

zCMD_d4: ; CALL NC nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzCF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_d5: ; PUSH  DE
	zzPUSH zzD,zzE

	jmp zCMD_start

zCMD_d6: ; SUB  A n
	LDRAM_PC_NODDR FROMRAM0
	sub zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_d7: ; RST   10h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x10

	jmp zCMD_start

zCMD_d8: ; RET   C
	sbrs zzF,zzCF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMD_d9: ; EXX   
	EX zzH,zzHe
	EX zzL,zzLe
	EX zzB,zzBe
	EX zzC,zzCe
	EX zzD,zzDe
	EX zzE,zzEe
	

	jmp zCMD_start

zCMD_da: ; JP   C nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzCF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_db: ; IN   A (n)
	LDRAM_PC_NODDR FROMRAM0
	mov zzTmp,FROMRAM0
	call PORTIN
	mov zzA,zzTmp

	jmp zCMD_start

zCMD_dc: ; CALL C nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzCF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_dd: ; DD*   
	ldi Xh, high(zOPCODE_DD_LBLS_L)
	jmp zCMDP_start

	jmp zCMD_start

zCMD_de: ; SBC  A n
	LDRAM_PC_NODDR FROMRAM0
	out SREG,zzF
	sez
	sbc zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_df: ; RST   18h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x18

	jmp zCMD_start

zCMD_e0: ; RET   PO
	sbrc zzF,zzPF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMD_e1: ; POP   HL
	zzPOP zzH,zzL

	jmp zCMD_start

zCMD_e2: ; JP   PO nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzPF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_e3: ; EX   (SP) HL
	mov FROMRAM1,zzSPh
	mov FROMRAM2,zzSPl
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	EXR FROMRAM0,zzL
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	INC2 FROMRAM1,FROMRAM2
	LDRAM FROMRAM1,FROMRAM2,FROMRAM0
	EXR FROMRAM0,zzH
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	

	jmp zCMD_start

zCMD_e4: ; CALL PO nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzPF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_e5: ; PUSH  HL
	zzPUSH zzH,zzL

	jmp zCMD_start

zCMD_e6: ; AND  A n
	LDRAM_PC_NODDR FROMRAM0
	and zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_e7: ; RST   20h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x20

	jmp zCMD_start

zCMD_e8: ; RET   PE
	sbrs zzF,zzPF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMD_e9: ; JP   * HL
	cpse ZERO,ZERO
	jmp zCMD_start
	mov zzPCl,zzL
	mov zzPCh,zzH

	jmp zCMD_start

zCMD_ea: ; JP   PE nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzPF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_eb: ; EX   DE HL
	EXR zzD,zzH
	EXR zzE,zzL
	

	jmp zCMD_start

zCMD_ec: ; CALL PE nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzPF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_ed: ; ED*   
	ldi Xh, high(zOPCODE_ED_LBLS_L)
	jmp zCMDP_start

	jmp zCMD_start

zCMD_ee: ; XOR  A n
	LDRAM_PC_NODDR FROMRAM0
	eor zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_ef: ; RST   28h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x28

	jmp zCMD_start

zCMD_f0: ; RET   P
	sbrc zzF,zzSF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMD_f1: ; POP   AF
	zzPOP zzA,FROMRAM0
	ldi Xh,high(FZ2ATABLE)
	mov Xl,FROMRAM0
	ld zzF,X

	jmp zCMD_start

zCMD_f2: ; JP   P nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzSF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_f3: ; DI    
	zzSET zzIFF1,0
	zzSET zzIFF2,0

	jmp zCMD_start

zCMD_f4: ; CALL P nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzSF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_f5: ; PUSH  AF
	ldi Xh,high(FA2ZTABLE)
	mov Xl,zzF
	ld FROMRAM0,X
	zzPUSH zzA,FROMRAM0

	jmp zCMD_start

zCMD_f6: ; OR   A n
	LDRAM_PC_NODDR FROMRAM0
	or zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMD_f7: ; RST   30h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x30

	jmp zCMD_start

zCMD_f8: ; RET   M
	sbrs zzF,zzSF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMD_f9: ; LD   SP HL
	mov zzSPh, zzH
	mov zzSPl, zzL

	jmp zCMD_start

zCMD_fa: ; JP   M nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzSF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_fb: ; EI    
	zzSET zzIFF1,1
	zzSET zzIFF2,1

	jmp zCMD_start

zCMD_fc: ; CALL M nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzSF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMD_fd: ; FD*   
	ldi Xh, high(zOPCODE_FD_LBLS_L)
	jmp zCMDP_start

	jmp zCMD_start

zCMD_fe: ; CP   A n
	LDRAM_PC_NODDR FROMRAM0
	cp zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMD_ff: ; RST   38h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x38

	jmp zCMD_start

zCMDCB_00: ; RLC   B
	bst zzB,7
	lsl zzB
	bld zzB,0
	or zzB,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzB ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_01: ; RLC   C
	bst zzC,7
	lsl zzC
	bld zzC,0
	or zzC,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzC ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_02: ; RLC   D
	bst zzD,7
	lsl zzD
	bld zzD,0
	or zzD,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzD ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_03: ; RLC   E
	bst zzE,7
	lsl zzE
	bld zzE,0
	or zzE,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzE ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_04: ; RLC   H
	bst zzH,7
	lsl zzH
	bld zzH,0
	or zzH,zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzH ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_05: ; RLC   L
	bst zzL,7
	lsl zzL
	bld zzL,0
	or zzL,zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzL ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_06: ; RLC   (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	bst FROMRAM0,7
	lsl FROMRAM0
	bld FROMRAM0,0
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_07: ; RLC   A
	bst zzA,7
	lsl zzA
	bld zzA,0
	or zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_08: ; RRC   B
	bst zzB,0
	lsr zzB
	bld zzB,7
	or zzB,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzB ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_09: ; RRC   C
	bst zzC,0
	lsr zzC
	bld zzC,7
	or zzC,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzC ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_0a: ; RRC   D
	bst zzD,0
	lsr zzD
	bld zzD,7
	or zzD,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzD ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_0b: ; RRC   E
	bst zzE,0
	lsr zzE
	bld zzE,7
	or zzE,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzE ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_0c: ; RRC   H
	bst zzH,0
	lsr zzH
	bld zzH,7
	or zzH,zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzH ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_0d: ; RRC   L
	bst zzL,0
	lsr zzL
	bld zzL,7
	or zzL,zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzL ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_0e: ; RRC   (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	bst FROMRAM0,0
	lsr FROMRAM0
	bld FROMRAM0,7
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_0f: ; RRC   A
	bst zzA,0
	lsr zzA
	bld zzA,7
	or zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_10: ; RL    B
	out SREG,zzF
	rol zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzB ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_11: ; RL    C
	out SREG,zzF
	rol zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzC ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_12: ; RL    D
	out SREG,zzF
	rol zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzD ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_13: ; RL    E
	out SREG,zzF
	rol zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzE ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_14: ; RL    H
	out SREG,zzF
	rol zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzH ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_15: ; RL    L
	out SREG,zzF
	rol zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzL ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_16: ; RL    (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	out SREG,zzF
	rol FROMRAM0

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_17: ; RL    A
	out SREG,zzF
	rol zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_18: ; RR    B
	out SREG,zzF
	ror zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzB ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_19: ; RR    C
	out SREG,zzF
	ror zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzC ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_1a: ; RR    D
	out SREG,zzF
	ror zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzD ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_1b: ; RR    E
	out SREG,zzF
	ror zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzE ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_1c: ; RR    H
	out SREG,zzF
	ror zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzH ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_1d: ; RR    L
	out SREG,zzF
	ror zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzL ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_1e: ; RR    (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	out SREG,zzF
	ror FROMRAM0

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_1f: ; RR    A
	out SREG,zzF
	ror zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_20: ; SLA   B
	lsl zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzB ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_21: ; SLA   C
	lsl zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzC ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_22: ; SLA   D
	lsl zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzD ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_23: ; SLA   E
	lsl zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzE ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_24: ; SLA   H
	lsl zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzH ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_25: ; SLA   L
	lsl zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzL ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_26: ; SLA   (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	lsl FROMRAM0

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_27: ; SLA   A
	lsl zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_28: ; SRA   B
	bst zzB,7
	lsr zzB
	bld zzB,7
	or zzB,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzB ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_29: ; SRA   C
	bst zzC,7
	lsr zzC
	bld zzC,7
	or zzC,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzC ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_2a: ; SRA   D
	bst zzD,7
	lsr zzD
	bld zzD,7
	or zzD,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzD ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_2b: ; SRA   E
	bst zzE,7
	lsr zzE
	bld zzE,7
	or zzE,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzE ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_2c: ; SRA   H
	bst zzH,7
	lsr zzH
	bld zzH,7
	or zzH,zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzH ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_2d: ; SRA   L
	bst zzL,7
	lsr zzL
	bld zzL,7
	or zzL,zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzL ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_2e: ; SRA   (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	bst FROMRAM0,7
	lsr FROMRAM0
	bld FROMRAM0,7
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_2f: ; SRA   A
	bst zzA,7
	lsr zzA
	bld zzA,7
	or zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_30: ; SLL   B
	lsl zzB
	set
	bld zzB,0
	or zzB,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzB ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_31: ; SLL   C
	lsl zzC
	set
	bld zzC,0
	or zzC,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzC ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_32: ; SLL   D
	lsl zzD
	set
	bld zzD,0
	or zzD,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzD ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_33: ; SLL   E
	lsl zzE
	set
	bld zzE,0
	or zzE,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzE ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_34: ; SLL   H
	lsl zzH
	set
	bld zzH,0
	or zzH,zzH

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzH ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_35: ; SLL   L
	lsl zzL
	set
	bld zzL,0
	or zzL,zzL

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzL ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_36: ; SLL   (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	lsl FROMRAM0
	set
	bld FROMRAM0,0
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_37: ; SLL   A
	lsl zzA
	set
	bld zzA,0
	or zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_38: ; SRL   B
	lsr zzB

	in zzF, SREG
	andi zzF, 	(_I_|___|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzB ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_39: ; SRL   C
	lsr zzC

	in zzF, SREG
	andi zzF, 	(_I_|___|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzC ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_3a: ; SRL   D
	lsr zzD

	in zzF, SREG
	andi zzF, 	(_I_|___|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzD ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_3b: ; SRL   E
	lsr zzE

	in zzF, SREG
	andi zzF, 	(_I_|___|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzE ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_3c: ; SRL   H
	lsr zzH

	in zzF, SREG
	andi zzF, 	(_I_|___|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzH ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_3d: ; SRL   L
	lsr zzL

	in zzF, SREG
	andi zzF, 	(_I_|___|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzL ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_3e: ; SRL   (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	lsr FROMRAM0

	in _sreg, SREG
	STRAM zzH,zzL,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|___|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_3f: ; SRL   A
	lsr zzA

	in zzF, SREG
	andi zzF, 	(_I_|___|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDCB_40: ; BIT  0 B
	mov zzTmp,zzB
	andi zzTmp,1<<0
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_41: ; BIT  0 C
	mov zzTmp,zzC
	andi zzTmp,1<<0
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_42: ; BIT  0 D
	mov zzTmp,zzD
	andi zzTmp,1<<0
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_43: ; BIT  0 E
	mov zzTmp,zzE
	andi zzTmp,1<<0
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_44: ; BIT  0 H
	mov zzTmp,zzH
	andi zzTmp,1<<0
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_45: ; BIT  0 L
	mov zzTmp,zzL
	andi zzTmp,1<<0
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_46: ; BIT  0 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<0
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_47: ; BIT  0 A
	mov zzTmp,zzA
	andi zzTmp,1<<0
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_48: ; BIT  1 B
	mov zzTmp,zzB
	andi zzTmp,1<<1
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_49: ; BIT  1 C
	mov zzTmp,zzC
	andi zzTmp,1<<1
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_4a: ; BIT  1 D
	mov zzTmp,zzD
	andi zzTmp,1<<1
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_4b: ; BIT  1 E
	mov zzTmp,zzE
	andi zzTmp,1<<1
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_4c: ; BIT  1 H
	mov zzTmp,zzH
	andi zzTmp,1<<1
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_4d: ; BIT  1 L
	mov zzTmp,zzL
	andi zzTmp,1<<1
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_4e: ; BIT  1 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<1
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_4f: ; BIT  1 A
	mov zzTmp,zzA
	andi zzTmp,1<<1
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_50: ; BIT  2 B
	mov zzTmp,zzB
	andi zzTmp,1<<2
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_51: ; BIT  2 C
	mov zzTmp,zzC
	andi zzTmp,1<<2
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_52: ; BIT  2 D
	mov zzTmp,zzD
	andi zzTmp,1<<2
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_53: ; BIT  2 E
	mov zzTmp,zzE
	andi zzTmp,1<<2
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_54: ; BIT  2 H
	mov zzTmp,zzH
	andi zzTmp,1<<2
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_55: ; BIT  2 L
	mov zzTmp,zzL
	andi zzTmp,1<<2
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_56: ; BIT  2 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<2
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_57: ; BIT  2 A
	mov zzTmp,zzA
	andi zzTmp,1<<2
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_58: ; BIT  3 B
	mov zzTmp,zzB
	andi zzTmp,1<<3
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_59: ; BIT  3 C
	mov zzTmp,zzC
	andi zzTmp,1<<3
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_5a: ; BIT  3 D
	mov zzTmp,zzD
	andi zzTmp,1<<3
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_5b: ; BIT  3 E
	mov zzTmp,zzE
	andi zzTmp,1<<3
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_5c: ; BIT  3 H
	mov zzTmp,zzH
	andi zzTmp,1<<3
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_5d: ; BIT  3 L
	mov zzTmp,zzL
	andi zzTmp,1<<3
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_5e: ; BIT  3 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<3
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_5f: ; BIT  3 A
	mov zzTmp,zzA
	andi zzTmp,1<<3
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_60: ; BIT  4 B
	mov zzTmp,zzB
	andi zzTmp,1<<4
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_61: ; BIT  4 C
	mov zzTmp,zzC
	andi zzTmp,1<<4
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_62: ; BIT  4 D
	mov zzTmp,zzD
	andi zzTmp,1<<4
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_63: ; BIT  4 E
	mov zzTmp,zzE
	andi zzTmp,1<<4
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_64: ; BIT  4 H
	mov zzTmp,zzH
	andi zzTmp,1<<4
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_65: ; BIT  4 L
	mov zzTmp,zzL
	andi zzTmp,1<<4
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_66: ; BIT  4 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<4
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_67: ; BIT  4 A
	mov zzTmp,zzA
	andi zzTmp,1<<4
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_68: ; BIT  5 B
	mov zzTmp,zzB
	andi zzTmp,1<<5
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_69: ; BIT  5 C
	mov zzTmp,zzC
	andi zzTmp,1<<5
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_6a: ; BIT  5 D
	mov zzTmp,zzD
	andi zzTmp,1<<5
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_6b: ; BIT  5 E
	mov zzTmp,zzE
	andi zzTmp,1<<5
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_6c: ; BIT  5 H
	mov zzTmp,zzH
	andi zzTmp,1<<5
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_6d: ; BIT  5 L
	mov zzTmp,zzL
	andi zzTmp,1<<5
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_6e: ; BIT  5 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<5
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_6f: ; BIT  5 A
	mov zzTmp,zzA
	andi zzTmp,1<<5
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_70: ; BIT  6 B
	mov zzTmp,zzB
	andi zzTmp,1<<6
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_71: ; BIT  6 C
	mov zzTmp,zzC
	andi zzTmp,1<<6
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_72: ; BIT  6 D
	mov zzTmp,zzD
	andi zzTmp,1<<6
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_73: ; BIT  6 E
	mov zzTmp,zzE
	andi zzTmp,1<<6
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_74: ; BIT  6 H
	mov zzTmp,zzH
	andi zzTmp,1<<6
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_75: ; BIT  6 L
	mov zzTmp,zzL
	andi zzTmp,1<<6
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_76: ; BIT  6 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<6
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_77: ; BIT  6 A
	mov zzTmp,zzA
	andi zzTmp,1<<6
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_78: ; BIT  7 B
	mov zzTmp,zzB
	andi zzTmp,1<<7
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_79: ; BIT  7 C
	mov zzTmp,zzC
	andi zzTmp,1<<7
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_7a: ; BIT  7 D
	mov zzTmp,zzD
	andi zzTmp,1<<7
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_7b: ; BIT  7 E
	mov zzTmp,zzE
	andi zzTmp,1<<7
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_7c: ; BIT  7 H
	mov zzTmp,zzH
	andi zzTmp,1<<7
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_7d: ; BIT  7 L
	mov zzTmp,zzL
	andi zzTmp,1<<7
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_7e: ; BIT  7 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<7
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_7f: ; BIT  7 A
	mov zzTmp,zzA
	andi zzTmp,1<<7
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDCB_80: ; RES  0 B
	ldi zzTmp,~(1<<0)
	and zzB,zzTmp 

	jmp zCMD_start

zCMDCB_81: ; RES  0 C
	ldi zzTmp,~(1<<0)
	and zzC,zzTmp 

	jmp zCMD_start

zCMDCB_82: ; RES  0 D
	ldi zzTmp,~(1<<0)
	and zzD,zzTmp 

	jmp zCMD_start

zCMDCB_83: ; RES  0 E
	ldi zzTmp,~(1<<0)
	and zzE,zzTmp 

	jmp zCMD_start

zCMDCB_84: ; RES  0 H
	ldi zzTmp,~(1<<0)
	and zzH,zzTmp 

	jmp zCMD_start

zCMDCB_85: ; RES  0 L
	ldi zzTmp,~(1<<0)
	and zzL,zzTmp 

	jmp zCMD_start

zCMDCB_86: ; RES  0 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	cbr zzTmp,1<<0
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_87: ; RES  0 A
	ldi zzTmp,~(1<<0)
	and zzA,zzTmp 

	jmp zCMD_start

zCMDCB_88: ; RES  1 B
	ldi zzTmp,~(1<<1)
	and zzB,zzTmp 

	jmp zCMD_start

zCMDCB_89: ; RES  1 C
	ldi zzTmp,~(1<<1)
	and zzC,zzTmp 

	jmp zCMD_start

zCMDCB_8a: ; RES  1 D
	ldi zzTmp,~(1<<1)
	and zzD,zzTmp 

	jmp zCMD_start

zCMDCB_8b: ; RES  1 E
	ldi zzTmp,~(1<<1)
	and zzE,zzTmp 

	jmp zCMD_start

zCMDCB_8c: ; RES  1 H
	ldi zzTmp,~(1<<1)
	and zzH,zzTmp 

	jmp zCMD_start

zCMDCB_8d: ; RES  1 L
	ldi zzTmp,~(1<<1)
	and zzL,zzTmp 

	jmp zCMD_start

zCMDCB_8e: ; RES  1 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	cbr zzTmp,1<<1
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_8f: ; RES  1 A
	ldi zzTmp,~(1<<1)
	and zzA,zzTmp 

	jmp zCMD_start

zCMDCB_90: ; RES  2 B
	ldi zzTmp,~(1<<2)
	and zzB,zzTmp 

	jmp zCMD_start

zCMDCB_91: ; RES  2 C
	ldi zzTmp,~(1<<2)
	and zzC,zzTmp 

	jmp zCMD_start

zCMDCB_92: ; RES  2 D
	ldi zzTmp,~(1<<2)
	and zzD,zzTmp 

	jmp zCMD_start

zCMDCB_93: ; RES  2 E
	ldi zzTmp,~(1<<2)
	and zzE,zzTmp 

	jmp zCMD_start

zCMDCB_94: ; RES  2 H
	ldi zzTmp,~(1<<2)
	and zzH,zzTmp 

	jmp zCMD_start

zCMDCB_95: ; RES  2 L
	ldi zzTmp,~(1<<2)
	and zzL,zzTmp 

	jmp zCMD_start

zCMDCB_96: ; RES  2 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	cbr zzTmp,1<<2
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_97: ; RES  2 A
	ldi zzTmp,~(1<<2)
	and zzA,zzTmp 

	jmp zCMD_start

zCMDCB_98: ; RES  3 B
	ldi zzTmp,~(1<<3)
	and zzB,zzTmp 

	jmp zCMD_start

zCMDCB_99: ; RES  3 C
	ldi zzTmp,~(1<<3)
	and zzC,zzTmp 

	jmp zCMD_start

zCMDCB_9a: ; RES  3 D
	ldi zzTmp,~(1<<3)
	and zzD,zzTmp 

	jmp zCMD_start

zCMDCB_9b: ; RES  3 E
	ldi zzTmp,~(1<<3)
	and zzE,zzTmp 

	jmp zCMD_start

zCMDCB_9c: ; RES  3 H
	ldi zzTmp,~(1<<3)
	and zzH,zzTmp 

	jmp zCMD_start

zCMDCB_9d: ; RES  3 L
	ldi zzTmp,~(1<<3)
	and zzL,zzTmp 

	jmp zCMD_start

zCMDCB_9e: ; RES  3 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	cbr zzTmp,1<<3
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_9f: ; RES  3 A
	ldi zzTmp,~(1<<3)
	and zzA,zzTmp 

	jmp zCMD_start

zCMDCB_a0: ; RES  4 B
	ldi zzTmp,~(1<<4)
	and zzB,zzTmp 

	jmp zCMD_start

zCMDCB_a1: ; RES  4 C
	ldi zzTmp,~(1<<4)
	and zzC,zzTmp 

	jmp zCMD_start

zCMDCB_a2: ; RES  4 D
	ldi zzTmp,~(1<<4)
	and zzD,zzTmp 

	jmp zCMD_start

zCMDCB_a3: ; RES  4 E
	ldi zzTmp,~(1<<4)
	and zzE,zzTmp 

	jmp zCMD_start

zCMDCB_a4: ; RES  4 H
	ldi zzTmp,~(1<<4)
	and zzH,zzTmp 

	jmp zCMD_start

zCMDCB_a5: ; RES  4 L
	ldi zzTmp,~(1<<4)
	and zzL,zzTmp 

	jmp zCMD_start

zCMDCB_a6: ; RES  4 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	cbr zzTmp,1<<4
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_a7: ; RES  4 A
	ldi zzTmp,~(1<<4)
	and zzA,zzTmp 

	jmp zCMD_start

zCMDCB_a8: ; RES  5 B
	ldi zzTmp,~(1<<5)
	and zzB,zzTmp 

	jmp zCMD_start

zCMDCB_a9: ; RES  5 C
	ldi zzTmp,~(1<<5)
	and zzC,zzTmp 

	jmp zCMD_start

zCMDCB_aa: ; RES  5 D
	ldi zzTmp,~(1<<5)
	and zzD,zzTmp 

	jmp zCMD_start

zCMDCB_ab: ; RES  5 E
	ldi zzTmp,~(1<<5)
	and zzE,zzTmp 

	jmp zCMD_start

zCMDCB_ac: ; RES  5 H
	ldi zzTmp,~(1<<5)
	and zzH,zzTmp 

	jmp zCMD_start

zCMDCB_ad: ; RES  5 L
	ldi zzTmp,~(1<<5)
	and zzL,zzTmp 

	jmp zCMD_start

zCMDCB_ae: ; RES  5 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	cbr zzTmp,1<<5
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_af: ; RES  5 A
	ldi zzTmp,~(1<<5)
	and zzA,zzTmp 

	jmp zCMD_start

zCMDCB_b0: ; RES  6 B
	ldi zzTmp,~(1<<6)
	and zzB,zzTmp 

	jmp zCMD_start

zCMDCB_b1: ; RES  6 C
	ldi zzTmp,~(1<<6)
	and zzC,zzTmp 

	jmp zCMD_start

zCMDCB_b2: ; RES  6 D
	ldi zzTmp,~(1<<6)
	and zzD,zzTmp 

	jmp zCMD_start

zCMDCB_b3: ; RES  6 E
	ldi zzTmp,~(1<<6)
	and zzE,zzTmp 

	jmp zCMD_start

zCMDCB_b4: ; RES  6 H
	ldi zzTmp,~(1<<6)
	and zzH,zzTmp 

	jmp zCMD_start

zCMDCB_b5: ; RES  6 L
	ldi zzTmp,~(1<<6)
	and zzL,zzTmp 

	jmp zCMD_start

zCMDCB_b6: ; RES  6 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	cbr zzTmp,1<<6
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_b7: ; RES  6 A
	ldi zzTmp,~(1<<6)
	and zzA,zzTmp 

	jmp zCMD_start

zCMDCB_b8: ; RES  7 B
	ldi zzTmp,~(1<<7)
	and zzB,zzTmp 

	jmp zCMD_start

zCMDCB_b9: ; RES  7 C
	ldi zzTmp,~(1<<7)
	and zzC,zzTmp 

	jmp zCMD_start

zCMDCB_ba: ; RES  7 D
	ldi zzTmp,~(1<<7)
	and zzD,zzTmp 

	jmp zCMD_start

zCMDCB_bb: ; RES  7 E
	ldi zzTmp,~(1<<7)
	and zzE,zzTmp 

	jmp zCMD_start

zCMDCB_bc: ; RES  7 H
	ldi zzTmp,~(1<<7)
	and zzH,zzTmp 

	jmp zCMD_start

zCMDCB_bd: ; RES  7 L
	ldi zzTmp,~(1<<7)
	and zzL,zzTmp 

	jmp zCMD_start

zCMDCB_be: ; RES  7 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	cbr zzTmp,1<<7
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_bf: ; RES  7 A
	ldi zzTmp,~(1<<7)
	and zzA,zzTmp 

	jmp zCMD_start

zCMDCB_c0: ; SET  0 B
	ldi zzTmp,1<<0
	or zzB,zzTmp

	jmp zCMD_start

zCMDCB_c1: ; SET  0 C
	ldi zzTmp,1<<0
	or zzC,zzTmp

	jmp zCMD_start

zCMDCB_c2: ; SET  0 D
	ldi zzTmp,1<<0
	or zzD,zzTmp

	jmp zCMD_start

zCMDCB_c3: ; SET  0 E
	ldi zzTmp,1<<0
	or zzE,zzTmp

	jmp zCMD_start

zCMDCB_c4: ; SET  0 H
	ldi zzTmp,1<<0
	or zzH,zzTmp

	jmp zCMD_start

zCMDCB_c5: ; SET  0 L
	ldi zzTmp,1<<0
	or zzL,zzTmp

	jmp zCMD_start

zCMDCB_c6: ; SET  0 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	sbr zzTmp,1<<0
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_c7: ; SET  0 A
	ldi zzTmp,1<<0
	or zzA,zzTmp

	jmp zCMD_start

zCMDCB_c8: ; SET  1 B
	ldi zzTmp,1<<1
	or zzB,zzTmp

	jmp zCMD_start

zCMDCB_c9: ; SET  1 C
	ldi zzTmp,1<<1
	or zzC,zzTmp

	jmp zCMD_start

zCMDCB_ca: ; SET  1 D
	ldi zzTmp,1<<1
	or zzD,zzTmp

	jmp zCMD_start

zCMDCB_cb: ; SET  1 E
	ldi zzTmp,1<<1
	or zzE,zzTmp

	jmp zCMD_start

zCMDCB_cc: ; SET  1 H
	ldi zzTmp,1<<1
	or zzH,zzTmp

	jmp zCMD_start

zCMDCB_cd: ; SET  1 L
	ldi zzTmp,1<<1
	or zzL,zzTmp

	jmp zCMD_start

zCMDCB_ce: ; SET  1 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	sbr zzTmp,1<<1
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_cf: ; SET  1 A
	ldi zzTmp,1<<1
	or zzA,zzTmp

	jmp zCMD_start

zCMDCB_d0: ; SET  2 B
	ldi zzTmp,1<<2
	or zzB,zzTmp

	jmp zCMD_start

zCMDCB_d1: ; SET  2 C
	ldi zzTmp,1<<2
	or zzC,zzTmp

	jmp zCMD_start

zCMDCB_d2: ; SET  2 D
	ldi zzTmp,1<<2
	or zzD,zzTmp

	jmp zCMD_start

zCMDCB_d3: ; SET  2 E
	ldi zzTmp,1<<2
	or zzE,zzTmp

	jmp zCMD_start

zCMDCB_d4: ; SET  2 H
	ldi zzTmp,1<<2
	or zzH,zzTmp

	jmp zCMD_start

zCMDCB_d5: ; SET  2 L
	ldi zzTmp,1<<2
	or zzL,zzTmp

	jmp zCMD_start

zCMDCB_d6: ; SET  2 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	sbr zzTmp,1<<2
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_d7: ; SET  2 A
	ldi zzTmp,1<<2
	or zzA,zzTmp

	jmp zCMD_start

zCMDCB_d8: ; SET  3 B
	ldi zzTmp,1<<3
	or zzB,zzTmp

	jmp zCMD_start

zCMDCB_d9: ; SET  3 C
	ldi zzTmp,1<<3
	or zzC,zzTmp

	jmp zCMD_start

zCMDCB_da: ; SET  3 D
	ldi zzTmp,1<<3
	or zzD,zzTmp

	jmp zCMD_start

zCMDCB_db: ; SET  3 E
	ldi zzTmp,1<<3
	or zzE,zzTmp

	jmp zCMD_start

zCMDCB_dc: ; SET  3 H
	ldi zzTmp,1<<3
	or zzH,zzTmp

	jmp zCMD_start

zCMDCB_dd: ; SET  3 L
	ldi zzTmp,1<<3
	or zzL,zzTmp

	jmp zCMD_start

zCMDCB_de: ; SET  3 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	sbr zzTmp,1<<3
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_df: ; SET  3 A
	ldi zzTmp,1<<3
	or zzA,zzTmp

	jmp zCMD_start

zCMDCB_e0: ; SET  4 B
	ldi zzTmp,1<<4
	or zzB,zzTmp

	jmp zCMD_start

zCMDCB_e1: ; SET  4 C
	ldi zzTmp,1<<4
	or zzC,zzTmp

	jmp zCMD_start

zCMDCB_e2: ; SET  4 D
	ldi zzTmp,1<<4
	or zzD,zzTmp

	jmp zCMD_start

zCMDCB_e3: ; SET  4 E
	ldi zzTmp,1<<4
	or zzE,zzTmp

	jmp zCMD_start

zCMDCB_e4: ; SET  4 H
	ldi zzTmp,1<<4
	or zzH,zzTmp

	jmp zCMD_start

zCMDCB_e5: ; SET  4 L
	ldi zzTmp,1<<4
	or zzL,zzTmp

	jmp zCMD_start

zCMDCB_e6: ; SET  4 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	sbr zzTmp,1<<4
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_e7: ; SET  4 A
	ldi zzTmp,1<<4
	or zzA,zzTmp

	jmp zCMD_start

zCMDCB_e8: ; SET  5 B
	ldi zzTmp,1<<5
	or zzB,zzTmp

	jmp zCMD_start

zCMDCB_e9: ; SET  5 C
	ldi zzTmp,1<<5
	or zzC,zzTmp

	jmp zCMD_start

zCMDCB_ea: ; SET  5 D
	ldi zzTmp,1<<5
	or zzD,zzTmp

	jmp zCMD_start

zCMDCB_eb: ; SET  5 E
	ldi zzTmp,1<<5
	or zzE,zzTmp

	jmp zCMD_start

zCMDCB_ec: ; SET  5 H
	ldi zzTmp,1<<5
	or zzH,zzTmp

	jmp zCMD_start

zCMDCB_ed: ; SET  5 L
	ldi zzTmp,1<<5
	or zzL,zzTmp

	jmp zCMD_start

zCMDCB_ee: ; SET  5 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	sbr zzTmp,1<<5
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_ef: ; SET  5 A
	ldi zzTmp,1<<5
	or zzA,zzTmp

	jmp zCMD_start

zCMDCB_f0: ; SET  6 B
	ldi zzTmp,1<<6
	or zzB,zzTmp

	jmp zCMD_start

zCMDCB_f1: ; SET  6 C
	ldi zzTmp,1<<6
	or zzC,zzTmp

	jmp zCMD_start

zCMDCB_f2: ; SET  6 D
	ldi zzTmp,1<<6
	or zzD,zzTmp

	jmp zCMD_start

zCMDCB_f3: ; SET  6 E
	ldi zzTmp,1<<6
	or zzE,zzTmp

	jmp zCMD_start

zCMDCB_f4: ; SET  6 H
	ldi zzTmp,1<<6
	or zzH,zzTmp

	jmp zCMD_start

zCMDCB_f5: ; SET  6 L
	ldi zzTmp,1<<6
	or zzL,zzTmp

	jmp zCMD_start

zCMDCB_f6: ; SET  6 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	sbr zzTmp,1<<6
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_f7: ; SET  6 A
	ldi zzTmp,1<<6
	or zzA,zzTmp

	jmp zCMD_start

zCMDCB_f8: ; SET  7 B
	ldi zzTmp,1<<7
	or zzB,zzTmp

	jmp zCMD_start

zCMDCB_f9: ; SET  7 C
	ldi zzTmp,1<<7
	or zzC,zzTmp

	jmp zCMD_start

zCMDCB_fa: ; SET  7 D
	ldi zzTmp,1<<7
	or zzD,zzTmp

	jmp zCMD_start

zCMDCB_fb: ; SET  7 E
	ldi zzTmp,1<<7
	or zzE,zzTmp

	jmp zCMD_start

zCMDCB_fc: ; SET  7 H
	ldi zzTmp,1<<7
	or zzH,zzTmp

	jmp zCMD_start

zCMDCB_fd: ; SET  7 L
	ldi zzTmp,1<<7
	or zzL,zzTmp

	jmp zCMD_start

zCMDCB_fe: ; SET  7 (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	mov zzTmp,FROMRAM0
	sbr zzTmp,1<<7
	mov FROMRAM0,zzTmp
	STRAM zzH,zzL,FROMRAM0

	jmp zCMD_start

zCMDCB_ff: ; SET  7 A
	ldi zzTmp,1<<7
	or zzA,zzTmp

	jmp zCMD_start

zCMDDD_00: ; NOP   
	

	jmp zCMD_start

zCMDDD_01: ; LD   BC nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzB, FROMRAM1
	mov zzC, FROMRAM2

	jmp zCMD_start

zCMDDD_02: ; LD   (BC) A
	mov FROMRAM0,zzA

	STRAM zzB,zzC,zzA
	jmp zCMD_start

zCMDDD_03: ; INC   BC
	INC2 zzB,zzC

	jmp zCMD_start

zCMDDD_04: ; INC   B
	add zzB,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_05: ; DEC   B
	sub zzB,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_06: ; LD   B n
	LDRAM_PC_NODDR FROMRAM0
	mov zzB,FROMRAM0

	jmp zCMD_start

zCMDDD_07: ; RLCA  
	bst zzA,7
	rol zzA
	bld zzA,0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_08: ; EX   AF AFe
	EX zzA,zzAe
	EX zzF,zzFe

	jmp zCMD_start

zCMDDD_09: ; ADD  IX BC
	add zzIXl,zzC
	adc zzIXh,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_0a: ; LD   A (BC)
	LDRAM_NODDR zzB,zzC,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMDDD_0b: ; DEC   BC
	DEC2 zzB,zzC

	jmp zCMD_start

zCMDDD_0c: ; INC   C
	add zzC,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_0d: ; DEC   C
	sub zzC,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_0e: ; LD   C n
	LDRAM_PC_NODDR FROMRAM0
	mov zzC,FROMRAM0

	jmp zCMD_start

zCMDDD_0f: ; RRCA  
	bst zzA,0
	ror zzA
	bld zzA,7

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_10: ; DJNZ  s
	LDRAM_PC_NODDR FROMRAM0
	dec zzB
	breq zCMDDD_10_1
	ADDWS zzPCh,zzPCl,FROMRAM0
	zCMDDD_10_1:

	jmp zCMD_start

zCMDDD_11: ; LD   DE nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzD, FROMRAM1
	mov zzE, FROMRAM2

	jmp zCMD_start

zCMDDD_12: ; LD   (DE) A
	mov FROMRAM0,zzA

	STRAM zzD,zzE,zzA
	jmp zCMD_start

zCMDDD_13: ; INC   DE
	INC2 zzD,zzE

	jmp zCMD_start

zCMDDD_14: ; INC   D
	add zzD,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_15: ; DEC   D
	sub zzD,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_16: ; LD   D n
	LDRAM_PC_NODDR FROMRAM0
	mov zzD,FROMRAM0

	jmp zCMD_start

zCMDDD_17: ; RLA   
	out SREG,zzF
	rol zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_18: ; JR   * s
	LDRAM_PC_NODDR FROMRAM0
	cpse ZERO,ZERO
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMDDD_19: ; ADD  IX DE
	add zzIXl,zzE
	adc zzIXh,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_1a: ; LD   A (DE)
	LDRAM_NODDR zzD,zzE,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMDDD_1b: ; DEC   DE
	DEC2 zzD,zzE

	jmp zCMD_start

zCMDDD_1c: ; INC   E
	add zzE,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_1d: ; DEC   E
	sub zzE,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_1e: ; LD   E n
	LDRAM_PC_NODDR FROMRAM0
	mov zzE,FROMRAM0

	jmp zCMD_start

zCMDDD_1f: ; RRA   
	out SREG,zzF
	ror zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_20: ; JR   NZ s
	LDRAM_PC_NODDR FROMRAM0
	sbrc zzF,zzZF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMDDD_21: ; LD   IX nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzIXh, FROMRAM1
	mov zzIXl, FROMRAM2

	jmp zCMD_start

zCMDDD_22: ; LD   (ww) IX
	

	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	STRAM FROMRAM1,FROMRAM2,zzIXl
	INC2 FROMRAM1,FROMRAM2
	STRAM FROMRAM1,FROMRAM2,zzIXh
	jmp zCMD_start

zCMDDD_23: ; INC   IX
	INC2 zzIXh,zzIXl

	jmp zCMD_start

zCMDDD_24: ; INC   IXh
	add zzIXh,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_25: ; DEC   IXh
	sub zzIXh,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_26: ; LD   IXh n
	LDRAM_PC_NODDR FROMRAM0
	mov zzIXh,FROMRAM0

	jmp zCMD_start

zCMDDD_27: ; DAA   
	zzDAA

	jmp zCMD_start

zCMDDD_28: ; JR   Z s
	LDRAM_PC_NODDR FROMRAM0
	sbrs zzF,zzZF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMDDD_29: ; ADD  IX IX
	add zzIXl,zzIXl
	adc zzIXh,zzIXh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_2a: ; LD   IX (ww)
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzIXl
	INC2 FROMRAM1,FROMRAM2
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzIXh
	

	jmp zCMD_start

zCMDDD_2b: ; DEC   IX
	DEC2 zzIXh,zzIXl

	jmp zCMD_start

zCMDDD_2c: ; INC   IXl
	add zzIXl,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_2d: ; DEC   IXl
	sub zzIXl,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_2e: ; LD   IXl n
	LDRAM_PC_NODDR FROMRAM0
	mov zzIXl,FROMRAM0

	jmp zCMD_start

zCMDDD_2f: ; CPL   A
	com zzA

	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|_N_|___) ; set flags
	jmp zCMD_start

zCMDDD_30: ; JR   NC s
	LDRAM_PC_NODDR FROMRAM0
	sbrc zzF,zzCF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMDDD_31: ; LD   SP nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzSPh, FROMRAM1
	mov zzSPl, FROMRAM2

	jmp zCMD_start

zCMDDD_32: ; LD   (nn) A
	mov FROMRAM0,zzA

	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	STRAM FROMRAM1,FROMRAM2,zzA
	jmp zCMD_start

zCMDDD_33: ; INC   SP
	INC2 zzSPh,zzSPl

	jmp zCMD_start

zCMDDD_34: ; INC   (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	add FROMRAM0,ONE

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_35: ; DEC   (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	sub FROMRAM0,ONE

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_36: ; LD   (IX+d) n
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDD_37: ; SCF   
	

	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|___|_C_) ; set flags
	jmp zCMD_start

zCMDDD_38: ; JR   C s
	LDRAM_PC_NODDR FROMRAM0
	sbrs zzF,zzCF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMDDD_39: ; ADD  IX SP
	add zzIXl,zzSPl
	adc zzIXh,zzSPh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_3a: ; LD   A (nn)
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMDDD_3b: ; DEC   SP
	DEC2 zzSPh,zzSPl

	jmp zCMD_start

zCMDDD_3c: ; INC   A
	add zzA,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_3d: ; DEC   A
	sub zzA,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_3e: ; LD   A n
	LDRAM_PC_NODDR FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMDDD_3f: ; CCF   
	andi zzF,(_I_|_S_|_Z_|_V_|_C_)
	bst zzF,zzCF
	bld zzF,zzHF
	ldi zzTmp,1<<zzCF
	eor zzF,zzTmp

	jmp zCMD_start

zCMDDD_40: ; LD   B B
	mov zzB,zzB

	jmp zCMD_start

zCMDDD_41: ; LD   B C
	mov zzB,zzC

	jmp zCMD_start

zCMDDD_42: ; LD   B D
	mov zzB,zzD

	jmp zCMD_start

zCMDDD_43: ; LD   B E
	mov zzB,zzE

	jmp zCMD_start

zCMDDD_44: ; LD   B IXh
	mov zzB,zzIXh

	jmp zCMD_start

zCMDDD_45: ; LD   B IXl
	mov zzB,zzIXl

	jmp zCMD_start

zCMDDD_46: ; LD   B (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzB,FROMRAM0

	jmp zCMD_start

zCMDDD_47: ; LD   B A
	mov zzB,zzA

	jmp zCMD_start

zCMDDD_48: ; LD   C B
	mov zzC,zzB

	jmp zCMD_start

zCMDDD_49: ; LD   C C
	mov zzC,zzC

	jmp zCMD_start

zCMDDD_4a: ; LD   C D
	mov zzC,zzD

	jmp zCMD_start

zCMDDD_4b: ; LD   C E
	mov zzC,zzE

	jmp zCMD_start

zCMDDD_4c: ; LD   C IXh
	mov zzC,zzIXh

	jmp zCMD_start

zCMDDD_4d: ; LD   C IXl
	mov zzC,zzIXl

	jmp zCMD_start

zCMDDD_4e: ; LD   C (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzC,FROMRAM0

	jmp zCMD_start

zCMDDD_4f: ; LD   C A
	mov zzC,zzA

	jmp zCMD_start

zCMDDD_50: ; LD   D B
	mov zzD,zzB

	jmp zCMD_start

zCMDDD_51: ; LD   D C
	mov zzD,zzC

	jmp zCMD_start

zCMDDD_52: ; LD   D D
	mov zzD,zzD

	jmp zCMD_start

zCMDDD_53: ; LD   D E
	mov zzD,zzE

	jmp zCMD_start

zCMDDD_54: ; LD   D IXh
	mov zzD,zzIXh

	jmp zCMD_start

zCMDDD_55: ; LD   D IXl
	mov zzD,zzIXl

	jmp zCMD_start

zCMDDD_56: ; LD   D (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzD,FROMRAM0

	jmp zCMD_start

zCMDDD_57: ; LD   D A
	mov zzD,zzA

	jmp zCMD_start

zCMDDD_58: ; LD   E B
	mov zzE,zzB

	jmp zCMD_start

zCMDDD_59: ; LD   E C
	mov zzE,zzC

	jmp zCMD_start

zCMDDD_5a: ; LD   E D
	mov zzE,zzD

	jmp zCMD_start

zCMDDD_5b: ; LD   E E
	mov zzE,zzE

	jmp zCMD_start

zCMDDD_5c: ; LD   E IXh
	mov zzE,zzIXh

	jmp zCMD_start

zCMDDD_5d: ; LD   E IXl
	mov zzE,zzIXl

	jmp zCMD_start

zCMDDD_5e: ; LD   E (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzE,FROMRAM0

	jmp zCMD_start

zCMDDD_5f: ; LD   E A
	mov zzE,zzA

	jmp zCMD_start

zCMDDD_60: ; LD   IXh B
	mov zzIXh,zzB

	jmp zCMD_start

zCMDDD_61: ; LD   IXh C
	mov zzIXh,zzC

	jmp zCMD_start

zCMDDD_62: ; LD   IXh D
	mov zzIXh,zzD

	jmp zCMD_start

zCMDDD_63: ; LD   IXh E
	mov zzIXh,zzE

	jmp zCMD_start

zCMDDD_64: ; LD   IXh IXh
	mov zzIXh,zzIXh

	jmp zCMD_start

zCMDDD_65: ; LD   IXh IXl
	mov zzIXh,zzIXl

	jmp zCMD_start

zCMDDD_66: ; LD   H (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzH,FROMRAM0

	jmp zCMD_start

zCMDDD_67: ; LD   IXh A
	mov zzIXh,zzA

	jmp zCMD_start

zCMDDD_68: ; LD   IXl B
	mov zzIXl,zzB

	jmp zCMD_start

zCMDDD_69: ; LD   IXl C
	mov zzIXl,zzC

	jmp zCMD_start

zCMDDD_6a: ; LD   IXl D
	mov zzIXl,zzD

	jmp zCMD_start

zCMDDD_6b: ; LD   IXl E
	mov zzIXl,zzE

	jmp zCMD_start

zCMDDD_6c: ; LD   IXl IXh
	mov zzIXl,zzIXh

	jmp zCMD_start

zCMDDD_6d: ; LD   IXl IXl
	mov zzIXl,zzIXl

	jmp zCMD_start

zCMDDD_6e: ; LD   L (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzL,FROMRAM0

	jmp zCMD_start

zCMDDD_6f: ; LD   IXl A
	mov zzIXl,zzA

	jmp zCMD_start

zCMDDD_70: ; LD   (IX+d) B
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzB

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDD_71: ; LD   (IX+d) C
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzC

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDD_72: ; LD   (IX+d) D
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzD

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDD_73: ; LD   (IX+d) E
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzE

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDD_74: ; LD   (IX+d) H
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzH

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDD_75: ; LD   (IX+d) L
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzL

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDD_76: ; HALT  
	DEC2 zzPCh,zzPCl

	jmp zCMD_start

zCMDDD_77: ; LD   (IX+d) A
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzA

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDD_78: ; LD   A B
	mov zzA,zzB

	jmp zCMD_start

zCMDDD_79: ; LD   A C
	mov zzA,zzC

	jmp zCMD_start

zCMDDD_7a: ; LD   A D
	mov zzA,zzD

	jmp zCMD_start

zCMDDD_7b: ; LD   A E
	mov zzA,zzE

	jmp zCMD_start

zCMDDD_7c: ; LD   A IXh
	mov zzA,zzIXh

	jmp zCMD_start

zCMDDD_7d: ; LD   A IXl
	mov zzA,zzIXl

	jmp zCMD_start

zCMDDD_7e: ; LD   A (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMDDD_7f: ; LD   A A
	mov zzA,zzA

	jmp zCMD_start

zCMDDD_80: ; ADD  A B
	add zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_81: ; ADD  A C
	add zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_82: ; ADD  A D
	add zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_83: ; ADD  A E
	add zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_84: ; ADD  A IXh
	add zzA,zzIXh

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_85: ; ADD  A IXl
	add zzA,zzIXl

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_86: ; ADD  A (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	add zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_87: ; ADD  A A
	add zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_88: ; ADC  A B
	out SREG,zzF
	adc zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_89: ; ADC  A C
	out SREG,zzF
	adc zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_8a: ; ADC  A D
	out SREG,zzF
	adc zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_8b: ; ADC  A E
	out SREG,zzF
	adc zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_8c: ; ADC  A IXh
	out SREG,zzF
	adc zzA,zzIXh

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_8d: ; ADC  A IXl
	out SREG,zzF
	adc zzA,zzIXl

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_8e: ; ADC  A (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,zzF
	adc zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_8f: ; ADC  A A
	out SREG,zzF
	adc zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_90: ; SUB  A B
	sub zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_91: ; SUB  A C
	sub zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_92: ; SUB  A D
	sub zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_93: ; SUB  A E
	sub zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_94: ; SUB  A IXh
	sub zzA,zzIXh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_95: ; SUB  A IXl
	sub zzA,zzIXl

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_96: ; SUB  A (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	sub zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_97: ; SUB  A A
	sub zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_98: ; SBC  A B
	out SREG,zzF
	sez
	sbc zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_99: ; SBC  A C
	out SREG,zzF
	sez
	sbc zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_9a: ; SBC  A D
	out SREG,zzF
	sez
	sbc zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_9b: ; SBC  A E
	out SREG,zzF
	sez
	sbc zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_9c: ; SBC  A IXh
	out SREG,zzF
	sez
	sbc zzA,zzIXh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_9d: ; SBC  A IXl
	out SREG,zzF
	sez
	sbc zzA,zzIXl

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_9e: ; SBC  A (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,zzF
	sez
	sbc zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_9f: ; SBC  A A
	out SREG,zzF
	sez
	sbc zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_a0: ; AND  A B
	and zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_a1: ; AND  A C
	and zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_a2: ; AND  A D
	and zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_a3: ; AND  A E
	and zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_a4: ; AND  A IXh
	and zzA,zzIXh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_a5: ; AND  A IXl
	and zzA,zzIXl

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_a6: ; AND  A (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	and zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_a7: ; AND  A A
	and zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_a8: ; XOR  A B
	eor zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_a9: ; XOR  A C
	eor zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_aa: ; XOR  A D
	eor zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_ab: ; XOR  A E
	eor zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_ac: ; XOR  A IXh
	eor zzA,zzIXh

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_ad: ; XOR  A IXl
	eor zzA,zzIXl

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_ae: ; XOR  A (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	eor zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_af: ; XOR  A A
	eor zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_b0: ; OR   A B
	or zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_b1: ; OR   A C
	or zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_b2: ; OR   A D
	or zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_b3: ; OR   A E
	or zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_b4: ; OR   A IXh
	or zzA,zzIXh

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_b5: ; OR   A IXl
	or zzA,zzIXl

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_b6: ; OR   A (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	or zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_b7: ; OR   A A
	or zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_b8: ; CP   A B
	cp zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_b9: ; CP   A C
	cp zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_ba: ; CP   A D
	cp zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_bb: ; CP   A E
	cp zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_bc: ; CP   A IXh
	cp zzA,zzIXh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_bd: ; CP   A IXl
	cp zzA,zzIXl

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_be: ; CP   A (IX+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	cp zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_bf: ; CP   A A
	cp zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_c0: ; RET   NZ
	sbrc zzF,zzZF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDDD_c1: ; POP   BC
	zzPOP zzB,zzC

	jmp zCMD_start

zCMDDD_c2: ; JP   NZ nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzZF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_c3: ; JP   * nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	cpse ZERO,ZERO
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_c4: ; CALL NZ nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzZF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_c5: ; PUSH  BC
	zzPUSH zzB,zzC

	jmp zCMD_start

zCMDDD_c6: ; ADD  A n
	LDRAM_PC_NODDR FROMRAM0
	add zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_c7: ; RST   00h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0

	jmp zCMD_start

zCMDDD_c8: ; RET   Z
	sbrs zzF,zzZF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDDD_c9: ; RET   *
	cpse ZERO,ZERO
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDDD_ca: ; JP   Z nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzZF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_cb: ; DDCB  
	LDRAM_PC_NODDR FROMRAM0
	ldi Xh, high(zOPCODE_DDCB_LBLS_L)
	jmp zCMDP_start

	jmp zCMD_start

zCMDDD_cc: ; CALL Z nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzZF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_cd: ; CALL * nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	cpse ZERO,ZERO
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_ce: ; ADC  A n
	LDRAM_PC_NODDR FROMRAM0
	out SREG,zzF
	adc zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDDD_cf: ; RST   08h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x08

	jmp zCMD_start

zCMDDD_d0: ; RET   NC
	sbrc zzF,zzCF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDDD_d1: ; POP   DE
	zzPOP zzD,zzE

	jmp zCMD_start

zCMDDD_d2: ; JP   NC nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzCF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_d3: ; OUT  (n) A
	LDRAM_PC_NODDR FROMRAM0
	mov zzTmp,FROMRAM0
	sts CDATA,zzA
	call PORTOUT

	jmp zCMD_start

zCMDDD_d4: ; CALL NC nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzCF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_d5: ; PUSH  DE
	zzPUSH zzD,zzE

	jmp zCMD_start

zCMDDD_d6: ; SUB  A n
	LDRAM_PC_NODDR FROMRAM0
	sub zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_d7: ; RST   10h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x10

	jmp zCMD_start

zCMDDD_d8: ; RET   C
	sbrs zzF,zzCF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDDD_d9: ; EXX   
	EX zzH,zzHe
	EX zzL,zzLe
	EX zzB,zzBe
	EX zzC,zzCe
	EX zzD,zzDe
	EX zzE,zzEe
	

	jmp zCMD_start

zCMDDD_da: ; JP   C nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzCF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_db: ; IN   A (n)
	LDRAM_PC_NODDR FROMRAM0
	mov zzTmp,FROMRAM0
	call PORTIN
	mov zzA,zzTmp

	jmp zCMD_start

zCMDDD_dc: ; CALL C nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzCF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_de: ; SBC  A n
	LDRAM_PC_NODDR FROMRAM0
	out SREG,zzF
	sez
	sbc zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_df: ; RST   18h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x18

	jmp zCMD_start

zCMDDD_e0: ; RET   PO
	sbrc zzF,zzPF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDDD_e1: ; POP   IX
	zzPOP zzIXh,zzIXl

	jmp zCMD_start

zCMDDD_e2: ; JP   PO nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzPF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_e3: ; EX   (SP) IX
	mov FROMRAM1,zzSPh
	mov FROMRAM2,zzSPl
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	EXR FROMRAM0,zzIXl
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	INC2 FROMRAM1,FROMRAM2
	LDRAM FROMRAM1,FROMRAM2,FROMRAM0
	EXR FROMRAM0,zzIXh
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	

	jmp zCMD_start

zCMDDD_e4: ; CALL PO nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzPF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_e5: ; PUSH  IX
	zzPUSH zzIXh,zzIXl

	jmp zCMD_start

zCMDDD_e6: ; AND  A n
	LDRAM_PC_NODDR FROMRAM0
	and zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_e7: ; RST   20h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x20

	jmp zCMD_start

zCMDDD_e8: ; RET   PE
	sbrs zzF,zzPF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDDD_e9: ; JP   * IX
	cpse ZERO,ZERO
	jmp zCMD_start
	mov zzPCl,zzIXl
	mov zzPCh,zzIXh

	jmp zCMD_start

zCMDDD_ea: ; JP   PE nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzPF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_eb: ; EX   DE IX
	EXR zzD,zzIXh
	EXR zzE,zzIXl
	

	jmp zCMD_start

zCMDDD_ec: ; CALL PE nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzPF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_ee: ; XOR  A n
	LDRAM_PC_NODDR FROMRAM0
	eor zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_ef: ; RST   28h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x28

	jmp zCMD_start

zCMDDD_f0: ; RET   P
	sbrc zzF,zzSF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDDD_f1: ; POP   AF
	zzPOP zzA,FROMRAM0
	ldi Xh,high(FZ2ATABLE)
	mov Xl,FROMRAM0
	ld zzF,X

	jmp zCMD_start

zCMDDD_f2: ; JP   P nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzSF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_f3: ; DI    
	zzSET zzIFF1,0
	zzSET zzIFF2,0

	jmp zCMD_start

zCMDDD_f4: ; CALL P nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzSF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_f5: ; PUSH  AF
	ldi Xh,high(FA2ZTABLE)
	mov Xl,zzF
	ld FROMRAM0,X
	zzPUSH zzA,FROMRAM0

	jmp zCMD_start

zCMDDD_f6: ; OR   A n
	LDRAM_PC_NODDR FROMRAM0
	or zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDD_f7: ; RST   30h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x30

	jmp zCMD_start

zCMDDD_f8: ; RET   M
	sbrs zzF,zzSF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDDD_f9: ; LD   SP IX
	mov zzSPh, zzIXh
	mov zzSPl, zzIXl

	jmp zCMD_start

zCMDDD_fa: ; JP   M nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzSF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_fb: ; EI    
	zzSET zzIFF1,1
	zzSET zzIFF2,1

	jmp zCMD_start

zCMDDD_fc: ; CALL M nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzSF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDDD_fe: ; CP   A n
	LDRAM_PC_NODDR FROMRAM0
	cp zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDD_ff: ; RST   38h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x38

	jmp zCMD_start

zCMDED_00: ; BIOS 0 
	ldi zzTmp, 0x00
	call BIOS

	jmp zCMD_start

zCMDED_01: ; BIOS 1 
	ldi zzTmp, 0x01
	call BIOS

	jmp zCMD_start

zCMDED_02: ; BIOS 2 
	ldi zzTmp, 0x02
	call BIOS

	jmp zCMD_start

zCMDED_03: ; BIOS 3 
	ldi zzTmp, 0x03
	call BIOS

	jmp zCMD_start

zCMDED_04: ; BIOS 4 
	ldi zzTmp, 0x04
	call BIOS

	jmp zCMD_start

zCMDED_05: ; BIOS 5 
	ldi zzTmp, 0x05
	call BIOS

	jmp zCMD_start

zCMDED_06: ; BIOS 6 
	ldi zzTmp, 0x06
	call BIOS

	jmp zCMD_start

zCMDED_07: ; BIOS 7 
	ldi zzTmp, 0x07
	call BIOS

	jmp zCMD_start

zCMDED_08: ; BIOS 8 
	ldi zzTmp, 0x08
	call BIOS

	jmp zCMD_start

zCMDED_09: ; BIOS 9 
	ldi zzTmp, 0x09
	call BIOS

	jmp zCMD_start

zCMDED_0a: ; BIOS 10 
	ldi zzTmp, 0x0a
	call BIOS

	jmp zCMD_start

zCMDED_0b: ; BIOS 11 
	ldi zzTmp, 0x0b
	call BIOS

	jmp zCMD_start

zCMDED_0c: ; BIOS 12 
	ldi zzTmp, 0x0c
	call BIOS

	jmp zCMD_start

zCMDED_0d: ; BIOS 13 
	ldi zzTmp, 0x0d
	call BIOS

	jmp zCMD_start

zCMDED_0e: ; BIOS 14 
	ldi zzTmp, 0x0e
	call BIOS

	jmp zCMD_start

zCMDED_0f: ; BIOS 15 
	ldi zzTmp, 0x0f
	call BIOS

	jmp zCMD_start

zCMDED_10: ; BIOS 16 
	ldi zzTmp, 0x10
	call BIOS

	jmp zCMD_start

zCMDED_11: ; BIOS 17 
	ldi zzTmp, 0x11
	call BIOS

	jmp zCMD_start

zCMDED_12: ; BIOS 18 
	ldi zzTmp, 0x12
	call BIOS

	jmp zCMD_start

zCMDED_13: ; BIOS 19 
	ldi zzTmp, 0x13
	call BIOS

	jmp zCMD_start

zCMDED_14: ; BIOS 20 
	ldi zzTmp, 0x14
	call BIOS

	jmp zCMD_start

zCMDED_15: ; BIOS 21 
	ldi zzTmp, 0x15
	call BIOS

	jmp zCMD_start

zCMDED_16: ; BIOS 22 
	ldi zzTmp, 0x16
	call BIOS

	jmp zCMD_start

zCMDED_17: ; BIOS 23 
	ldi zzTmp, 0x17
	call BIOS

	jmp zCMD_start

zCMDED_18: ; BIOS 24 
	ldi zzTmp, 0x18
	call BIOS

	jmp zCMD_start

zCMDED_19: ; BIOS 25 
	ldi zzTmp, 0x19
	call BIOS

	jmp zCMD_start

zCMDED_1a: ; BIOS 26 
	ldi zzTmp, 0x1a
	call BIOS

	jmp zCMD_start

zCMDED_1b: ; BIOS 27 
	ldi zzTmp, 0x1b
	call BIOS

	jmp zCMD_start

zCMDED_1c: ; BIOS 28 
	ldi zzTmp, 0x1c
	call BIOS

	jmp zCMD_start

zCMDED_1d: ; BIOS 29 
	ldi zzTmp, 0x1d
	call BIOS

	jmp zCMD_start

zCMDED_1e: ; BIOS 30 
	ldi zzTmp, 0x1e
	call BIOS

	jmp zCMD_start

zCMDED_1f: ; BIOS 31 
	ldi zzTmp, 0x1f
	call BIOS

	jmp zCMD_start

zCMDED_20: ; BIOS 32 
	ldi zzTmp, 0x20
	call BIOS

	jmp zCMD_start

zCMDED_21: ; BIOS 33 
	ldi zzTmp, 0x21
	call BIOS

	jmp zCMD_start

zCMDED_22: ; BIOS 34 
	ldi zzTmp, 0x22
	call BIOS

	jmp zCMD_start

zCMDED_23: ; BIOS 35 
	ldi zzTmp, 0x23
	call BIOS

	jmp zCMD_start

zCMDED_24: ; BIOS 36 
	ldi zzTmp, 0x24
	call BIOS

	jmp zCMD_start

zCMDED_25: ; BIOS 37 
	ldi zzTmp, 0x25
	call BIOS

	jmp zCMD_start

zCMDED_26: ; BIOS 38 
	ldi zzTmp, 0x26
	call BIOS

	jmp zCMD_start

zCMDED_27: ; BDOS  
	call BDOS

	jmp zCMD_start

zCMDED_40: ; IN   B (C)
	mov zzTmp,zzC
	call PORTIN
	mov zzB,zzTmp

	jmp zCMD_start

zCMDED_41: ; OUT  (C) B
	mov zzTmp,zzC
	sts CDATA,zzB
	call PORTOUT

	jmp zCMD_start

zCMDED_42: ; SBC  HL BC
	out SREG,zzF
	sbc zzL,zzC
	sbc zzH,zzB
	in zzTmp,SREG
	cbr zzTmp,1<<zzZF
	push zzL
	or zzL,zzH
	brne zzCMDED_42_1
	sbr zzTmp,1<<zzZF
	zzCMDED_42_1:pop zzL
	out SREG,zzTmp

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_43: ; LD   (ww) BC
	

	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	STRAM FROMRAM1,FROMRAM2,zzC
	INC2 FROMRAM1,FROMRAM2
	STRAM FROMRAM1,FROMRAM2,zzB
	jmp zCMD_start

zCMDED_44: ; NEG   A
	neg zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_45: ; RETN  
	lds zzTmp,zzIFF2
	sts zzIFF1,zzTmp
	zzPOP zzPCh,zzPCl
	jmp EXTINTRPOC_RETI

	jmp zCMD_start

zCMDED_46: ; IM    0
	zzSET zzIM,0

	jmp zCMD_start

zCMDED_47: ; LD   I A
	mov FROMRAM0,zzA

	sts zzI,zzA
	jmp zCMD_start

zCMDED_48: ; IN   C (C)
	mov zzTmp,zzC
	call PORTIN
	mov zzC,zzTmp

	jmp zCMD_start

zCMDED_49: ; OUT  (C) C
	mov zzTmp,zzC
	sts CDATA,zzC
	call PORTOUT

	jmp zCMD_start

zCMDED_4a: ; ADC  HL BC
	out SREG,zzF
	adc zzL,zzC
	adc zzH,zzB
	in zzTmp,SREG
	cbr zzTmp,1<<zzZF
	push zzL
	or zzL,zzH
	brne zzCMDED_4a_1
	sbr zzTmp,1<<zzZF
	zzCMDED_4a_1:pop zzL
	out SREG,zzTmp

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDED_4b: ; LD   BC (ww)
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzC
	INC2 FROMRAM1,FROMRAM2
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzB
	

	jmp zCMD_start

zCMDED_4c: ; NEG   A
	neg zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_4d: ; RETI  
	lds zzTmp,zzIFF2
	sts zzIFF1,zzTmp
	zzPOP zzPCh,zzPCl
	jmp EXTINTRPOC_RETI

	jmp zCMD_start

zCMDED_4e: ; IM    3
	zzSET zzIM,3

	jmp zCMD_start

zCMDED_4f: ; LD   R A
	out TCNT0,zzA
	mov zzTmp,zzA
	andi zzTmp,0x80
	sts zzRhb,zzTmp

	jmp zCMD_start

zCMDED_50: ; IN   D (C)
	mov zzTmp,zzC
	call PORTIN
	mov zzD,zzTmp

	jmp zCMD_start

zCMDED_51: ; OUT  (C) D
	mov zzTmp,zzC
	sts CDATA,zzD
	call PORTOUT

	jmp zCMD_start

zCMDED_52: ; SBC  HL DE
	out SREG,zzF
	sbc zzL,zzE
	sbc zzH,zzD
	in zzTmp,SREG
	cbr zzTmp,1<<zzZF
	push zzL
	or zzL,zzH
	brne zzCMDED_52_1
	sbr zzTmp,1<<zzZF
	zzCMDED_52_1:pop zzL
	out SREG,zzTmp

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_53: ; LD   (ww) DE
	

	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	STRAM FROMRAM1,FROMRAM2,zzE
	INC2 FROMRAM1,FROMRAM2
	STRAM FROMRAM1,FROMRAM2,zzD
	jmp zCMD_start

zCMDED_54: ; NEG   A
	neg zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_55: ; RETN  
	lds zzTmp,zzIFF2
	sts zzIFF1,zzTmp
	zzPOP zzPCh,zzPCl
	jmp EXTINTRPOC_RETI

	jmp zCMD_start

zCMDED_56: ; IM    1
	zzSET zzIM,1

	jmp zCMD_start

zCMDED_57: ; LD   A I
	lds zzA,zzI
	andi zzF,~(1<<zzPF)
	lds zzTmp,zzIFF2
	sbrc zzTmp,0
	ori zzF,1<<zzPF
	lds zzA,zzI
	or zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|_V_|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_58: ; IN   E (C)
	mov zzTmp,zzC
	call PORTIN
	mov zzE,zzTmp

	jmp zCMD_start

zCMDED_59: ; OUT  (C) E
	mov zzTmp,zzC
	sts CDATA,zzE
	call PORTOUT

	jmp zCMD_start

zCMDED_5a: ; ADC  HL DE
	out SREG,zzF
	adc zzL,zzE
	adc zzH,zzD
	in zzTmp,SREG
	cbr zzTmp,1<<zzZF
	push zzL
	or zzL,zzH
	brne zzCMDED_5a_1
	sbr zzTmp,1<<zzZF
	zzCMDED_5a_1:pop zzL
	out SREG,zzTmp

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDED_5b: ; LD   DE (ww)
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzE
	INC2 FROMRAM1,FROMRAM2
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzD
	

	jmp zCMD_start

zCMDED_5c: ; NEG   A
	neg zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_5d: ; RETN  
	lds zzTmp,zzIFF2
	sts zzIFF1,zzTmp
	zzPOP zzPCh,zzPCl
	jmp EXTINTRPOC_RETI

	jmp zCMD_start

zCMDED_5e: ; IM    2
	zzSET zzIM,2

	jmp zCMD_start

zCMDED_5f: ; LD   A R
	andi zzF,~(1<<zzPF)
	lds zzTmp,zzIFF2
	sbrc zzTmp,0
	ori zzF,1<<zzPF
	in zzA,TCNT0
	lds zzTmp,zzRhb
	andi zzA,0x7f
	or zzA,zzTmp

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|_V_|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_60: ; IN   H (C)
	mov zzTmp,zzC
	call PORTIN
	mov zzH,zzTmp

	jmp zCMD_start

zCMDED_61: ; OUT  (C) H
	mov zzTmp,zzC
	sts CDATA,zzH
	call PORTOUT

	jmp zCMD_start

zCMDED_62: ; SBC  HL HL
	out SREG,zzF
	sbc zzL,zzL
	sbc zzH,zzH
	in zzTmp,SREG
	cbr zzTmp,1<<zzZF
	push zzL
	or zzL,zzH
	brne zzCMDED_62_1
	sbr zzTmp,1<<zzZF
	zzCMDED_62_1:pop zzL
	out SREG,zzTmp

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_63: ; LD   (ww) HL
	

	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	STRAM FROMRAM1,FROMRAM2,zzL
	INC2 FROMRAM1,FROMRAM2
	STRAM FROMRAM1,FROMRAM2,zzH
	jmp zCMD_start

zCMDED_64: ; NEG   A
	neg zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_65: ; RETN  
	lds zzTmp,zzIFF2
	sts zzIFF1,zzTmp
	zzPOP zzPCh,zzPCl
	jmp EXTINTRPOC_RETI

	jmp zCMD_start

zCMDED_66: ; IM    0
	zzSET zzIM,0

	jmp zCMD_start

zCMDED_67: ; RRD  A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	zzRRD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDED_68: ; IN   L (C)
	mov zzTmp,zzC
	call PORTIN
	mov zzL,zzTmp

	jmp zCMD_start

zCMDED_69: ; OUT  (C) L
	mov zzTmp,zzC
	sts CDATA,zzL
	call PORTOUT

	jmp zCMD_start

zCMDED_6a: ; ADC  HL HL
	out SREG,zzF
	adc zzL,zzL
	adc zzH,zzH
	in zzTmp,SREG
	cbr zzTmp,1<<zzZF
	push zzL
	or zzL,zzH
	brne zzCMDED_6a_1
	sbr zzTmp,1<<zzZF
	zzCMDED_6a_1:pop zzL
	out SREG,zzTmp

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDED_6b: ; LD   HL (ww)
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzL
	INC2 FROMRAM1,FROMRAM2
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzH
	

	jmp zCMD_start

zCMDED_6c: ; NEG   A
	neg zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_6d: ; RETN  
	lds zzTmp,zzIFF2
	sts zzIFF1,zzTmp
	zzPOP zzPCh,zzPCl
	jmp EXTINTRPOC_RETI

	jmp zCMD_start

zCMDED_6e: ; IM    3
	zzSET zzIM,3

	jmp zCMD_start

zCMDED_6f: ; RLD  A (HL)
	LDRAM_NODDR zzH,zzL,FROMRAM0
	zzRLD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDED_71: ; OUT  (C) 0
	mov zzTmp,zzC
	ldi FROMRAM0,0
	sts CDATA,FROMRAM0
	call PORTOUT

	jmp zCMD_start

zCMDED_72: ; SBC  HL SP
	out SREG,zzF
	sbc zzL,zzSPl
	sbc zzH,zzSPh
	in zzTmp,SREG
	cbr zzTmp,1<<zzZF
	push zzL
	or zzL,zzH
	brne zzCMDED_72_1
	sbr zzTmp,1<<zzZF
	zzCMDED_72_1:pop zzL
	out SREG,zzTmp

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_73: ; LD   (ww) SP
	

	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	STRAM FROMRAM1,FROMRAM2,zzSPl
	INC2 FROMRAM1,FROMRAM2
	STRAM FROMRAM1,FROMRAM2,zzSPh
	jmp zCMD_start

zCMDED_74: ; NEG   A
	neg zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_75: ; RETN  
	lds zzTmp,zzIFF2
	sts zzIFF1,zzTmp
	zzPOP zzPCh,zzPCl
	jmp EXTINTRPOC_RETI

	jmp zCMD_start

zCMDED_76: ; IM    1
	zzSET zzIM,1

	jmp zCMD_start

zCMDED_77: ; MUL   
	zMUL

	jmp zCMD_start

zCMDED_78: ; IN   A (C)
	mov zzTmp,zzC
	call PORTIN
	mov zzA,zzTmp

	jmp zCMD_start

zCMDED_79: ; OUT  (C) A
	mov zzTmp,zzC
	sts CDATA,zzA
	call PORTOUT

	jmp zCMD_start

zCMDED_7a: ; ADC  HL SP
	out SREG,zzF
	adc zzL,zzSPl
	adc zzH,zzSPh
	in zzTmp,SREG
	cbr zzTmp,1<<zzZF
	push zzL
	or zzL,zzH
	brne zzCMDED_7a_1
	sbr zzTmp,1<<zzZF
	zzCMDED_7a_1:pop zzL
	out SREG,zzTmp

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDED_7b: ; LD   SP (ww)
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzSPl
	INC2 FROMRAM1,FROMRAM2
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzSPh
	

	jmp zCMD_start

zCMDED_7c: ; NEG   A
	neg zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_7d: ; RETN  
	lds zzTmp,zzIFF2
	sts zzIFF1,zzTmp
	zzPOP zzPCh,zzPCl
	jmp EXTINTRPOC_RETI

	jmp zCMD_start

zCMDED_7e: ; IM    2
	zzSET zzIM,2

	jmp zCMD_start

zCMDED_7f: ; DIV   
	zDIV

	jmp zCMD_start

zCMDED_a0: ; LDI   
	zzLDx INC2

	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|_C_) ; mask old flags
	jmp zCMD_start

zCMDED_a1: ; CPI   
	zzCPI

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|_V_|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_a2: ; INI   
	mov zzTmp,zzC
	call PORTIN
	STRAM zzH,zzL,zzTmp
	INC2 zzH,zzL
	dec zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|_Z_|___|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_a3: ; OUTI  
	mov zzTmp,zzC
	LDRAM_NODDR zzH,zzL,FROMRAM0
	sts CDATA,FROMRAM0
	call PORTOUT
	INC2 zzH,zzL
	dec zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|_Z_|___|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_a4: ; FL32  0
	ldi zzTmp,0
	zFLOAT

	jmp zCMD_start

zCMDED_a5: ; FL32  1
	ldi zzTmp,1
	zFLOAT

	jmp zCMD_start

zCMDED_a6: ; FL32  2
	ldi zzTmp,2
	zFLOAT

	jmp zCMD_start

zCMDED_a7: ; FL32  3
	ldi zzTmp,3
	zFLOAT

	jmp zCMD_start

zCMDED_a8: ; LDD   
	zzLDx DEC2

	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|_C_) ; mask old flags
	jmp zCMD_start

zCMDED_a9: ; CPD   
	zzCPD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|_V_|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_aa: ; IND   
	mov zzTmp,zzC
	call PORTIN
	STRAM zzH,zzL,zzTmp
	DEC2 zzH,zzL
	dec zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|_Z_|___|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_ab: ; OUTD  
	mov zzTmp,zzC
	LDRAM_NODDR zzH,zzL,FROMRAM0
	sts CDATA,FROMRAM0
	call PORTOUT
	DEC2 zzH,zzL
	dec zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|_Z_|___|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_b0: ; LDIR  
	zzCMDED_b0_1:
	zzLDx INC2
	brne zzCMDED_b0_1

	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask old flags
	jmp zCMD_start

zCMDED_b1: ; CPIR  
	zzCMDED_b1_1:
	zzCPI
	breq zzCMDED_b1_2
	sbrc zzF,zzPF
	rjmp zzCMDED_b1_1
	zzCMDED_b1_2:
	

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|_V_|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_b2: ; INIR  
	mov zzTmp,zzC
	zzCMDED_b2_1:
	call PORTIN
	STRAM zzH,zzL,zzTmp
	INC2 zzH,zzL
	dec zzB
	brne zzCMDED_b2_1

	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|_Z_|___|___|_N_|___) ; set flags
	jmp zCMD_start

zCMDED_b3: ; OTIR  
	mov zzTmp,zzC
	zzCMDED_b3_1:
	LDRAM_NODDR zzH,zzL,FROMRAM0
	sts CDATA,FROMRAM0
	call PORTOUT
	INC2 zzH,zzL
	dec zzB
	brne zzCMDED_b3_1

	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|_Z_|___|___|_N_|___) ; set flags
	jmp zCMD_start

zCMDED_b8: ; LDDR  
	zzCMDED_b8_1:
	zzLDx DEC2
	brne zzCMDED_b8_1

	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask old flags
	jmp zCMD_start

zCMDED_b9: ; CPDR  
	zzCMDED_b9_1:
	zzCPD
	breq zzCMDED_b9_2
	sbrc zzF,zzPF
	rjmp zzCMDED_b9_1
	zzCMDED_b9_2:
	

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|___|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|_V_|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDED_ba: ; INDR  
	mov zzTmp,zzC
	zzCMDED_ba_1:
	call PORTIN
	STRAM zzH,zzL,zzTmp
	DEC2 zzH,zzL
	dec zzB
	brne zzCMDED_ba_1

	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|_Z_|___|___|_N_|___) ; set flags
	jmp zCMD_start

zCMDED_bb: ; OTDR  
	mov zzTmp,zzC
	zzCMDED_bb_1:
	LDRAM_NODDR zzH,zzL,FROMRAM0
	sts CDATA,FROMRAM0
	call PORTOUT
	DEC2 zzH,zzL
	dec zzB
	brne zzCMDED_bb_1

	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|_Z_|___|___|_N_|___) ; set flags
	jmp zCMD_start

zCMDFD_00: ; NOP   
	

	jmp zCMD_start

zCMDFD_01: ; LD   BC nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzB, FROMRAM1
	mov zzC, FROMRAM2

	jmp zCMD_start

zCMDFD_02: ; LD   (BC) A
	mov FROMRAM0,zzA

	STRAM zzB,zzC,zzA
	jmp zCMD_start

zCMDFD_03: ; INC   BC
	INC2 zzB,zzC

	jmp zCMD_start

zCMDFD_04: ; INC   B
	add zzB,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_05: ; DEC   B
	sub zzB,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_06: ; LD   B n
	LDRAM_PC_NODDR FROMRAM0
	mov zzB,FROMRAM0

	jmp zCMD_start

zCMDFD_07: ; RLCA  
	bst zzA,7
	rol zzA
	bld zzA,0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_08: ; EX   AF AFe
	EX zzA,zzAe
	EX zzF,zzFe

	jmp zCMD_start

zCMDFD_09: ; ADD  IY BC
	add zzIYl,zzC
	adc zzIYh,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_0a: ; LD   A (BC)
	LDRAM_NODDR zzB,zzC,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMDFD_0b: ; DEC   BC
	DEC2 zzB,zzC

	jmp zCMD_start

zCMDFD_0c: ; INC   C
	add zzC,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_0d: ; DEC   C
	sub zzC,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_0e: ; LD   C n
	LDRAM_PC_NODDR FROMRAM0
	mov zzC,FROMRAM0

	jmp zCMD_start

zCMDFD_0f: ; RRCA  
	bst zzA,0
	ror zzA
	bld zzA,7

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_10: ; DJNZ  s
	LDRAM_PC_NODDR FROMRAM0
	dec zzB
	breq zCMDFD_10_1
	ADDWS zzPCh,zzPCl,FROMRAM0
	zCMDFD_10_1:

	jmp zCMD_start

zCMDFD_11: ; LD   DE nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzD, FROMRAM1
	mov zzE, FROMRAM2

	jmp zCMD_start

zCMDFD_12: ; LD   (DE) A
	mov FROMRAM0,zzA

	STRAM zzD,zzE,zzA
	jmp zCMD_start

zCMDFD_13: ; INC   DE
	INC2 zzD,zzE

	jmp zCMD_start

zCMDFD_14: ; INC   D
	add zzD,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_15: ; DEC   D
	sub zzD,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_16: ; LD   D n
	LDRAM_PC_NODDR FROMRAM0
	mov zzD,FROMRAM0

	jmp zCMD_start

zCMDFD_17: ; RLA   
	out SREG,zzF
	rol zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_18: ; JR   * s
	LDRAM_PC_NODDR FROMRAM0
	cpse ZERO,ZERO
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMDFD_19: ; ADD  IY DE
	add zzIYl,zzE
	adc zzIYh,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_1a: ; LD   A (DE)
	LDRAM_NODDR zzD,zzE,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMDFD_1b: ; DEC   DE
	DEC2 zzD,zzE

	jmp zCMD_start

zCMDFD_1c: ; INC   E
	add zzE,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_1d: ; DEC   E
	sub zzE,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_1e: ; LD   E n
	LDRAM_PC_NODDR FROMRAM0
	mov zzE,FROMRAM0

	jmp zCMD_start

zCMDFD_1f: ; RRA   
	out SREG,zzF
	ror zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|___|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_20: ; JR   NZ s
	LDRAM_PC_NODDR FROMRAM0
	sbrc zzF,zzZF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMDFD_21: ; LD   IY nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzIYh, FROMRAM1
	mov zzIYl, FROMRAM2

	jmp zCMD_start

zCMDFD_22: ; LD   (ww) IY
	

	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	STRAM FROMRAM1,FROMRAM2,zzIYl
	INC2 FROMRAM1,FROMRAM2
	STRAM FROMRAM1,FROMRAM2,zzIYh
	jmp zCMD_start

zCMDFD_23: ; INC   IY
	INC2 zzIYh,zzIYl

	jmp zCMD_start

zCMDFD_24: ; INC   IYh
	add zzIYh,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_25: ; DEC   IYh
	sub zzIYh,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_26: ; LD   IYh n
	LDRAM_PC_NODDR FROMRAM0
	mov zzIYh,FROMRAM0

	jmp zCMD_start

zCMDFD_27: ; DAA   
	zzDAA

	jmp zCMD_start

zCMDFD_28: ; JR   Z s
	LDRAM_PC_NODDR FROMRAM0
	sbrs zzF,zzZF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMDFD_29: ; ADD  IY IY
	add zzIYl,zzIYl
	adc zzIYh,zzIYh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_2a: ; LD   IY (ww)
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzIYl
	INC2 FROMRAM1,FROMRAM2
	LDRAM_NODDR FROMRAM1,FROMRAM2,zzIYh
	

	jmp zCMD_start

zCMDFD_2b: ; DEC   IY
	DEC2 zzIYh,zzIYl

	jmp zCMD_start

zCMDFD_2c: ; INC   IYl
	add zzIYl,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_2d: ; DEC   IYl
	sub zzIYl,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_2e: ; LD   IYl n
	LDRAM_PC_NODDR FROMRAM0
	mov zzIYl,FROMRAM0

	jmp zCMD_start

zCMDFD_2f: ; CPL   A
	com zzA

	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|_N_|___) ; set flags
	jmp zCMD_start

zCMDFD_30: ; JR   NC s
	LDRAM_PC_NODDR FROMRAM0
	sbrc zzF,zzCF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMDFD_31: ; LD   SP nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	mov zzSPh, FROMRAM1
	mov zzSPl, FROMRAM2

	jmp zCMD_start

zCMDFD_32: ; LD   (nn) A
	mov FROMRAM0,zzA

	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	STRAM FROMRAM1,FROMRAM2,zzA
	jmp zCMD_start

zCMDFD_33: ; INC   SP
	INC2 zzSPh,zzSPl

	jmp zCMD_start

zCMDFD_34: ; INC   (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	add FROMRAM0,ONE

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_35: ; DEC   (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	sub FROMRAM0,ONE

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_36: ; LD   (IY+d) n
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFD_37: ; SCF   
	

	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|___|_C_) ; set flags
	jmp zCMD_start

zCMDFD_38: ; JR   C s
	LDRAM_PC_NODDR FROMRAM0
	sbrs zzF,zzCF
	jmp zCMD_start
	ADDWS zzPCh,zzPCl,FROMRAM0

	jmp zCMD_start

zCMDFD_39: ; ADD  IY SP
	add zzIYl,zzSPl
	adc zzIYh,zzSPh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|___|___|_H_|___|___|_C_) ; mask results flags
	andi zzF, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_3a: ; LD   A (nn)
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMDFD_3b: ; DEC   SP
	DEC2 zzSPh,zzSPl

	jmp zCMD_start

zCMDFD_3c: ; INC   A
	add zzA,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_3d: ; DEC   A
	sub zzA,ONE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|___|___|_N_|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_3e: ; LD   A n
	LDRAM_PC_NODDR FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMDFD_3f: ; CCF   
	andi zzF,(_I_|_S_|_Z_|_V_|_C_)
	bst zzF,zzCF
	bld zzF,zzHF
	ldi zzTmp,1<<zzCF
	eor zzF,zzTmp

	jmp zCMD_start

zCMDFD_40: ; LD   B B
	mov zzB,zzB

	jmp zCMD_start

zCMDFD_41: ; LD   B C
	mov zzB,zzC

	jmp zCMD_start

zCMDFD_42: ; LD   B D
	mov zzB,zzD

	jmp zCMD_start

zCMDFD_43: ; LD   B E
	mov zzB,zzE

	jmp zCMD_start

zCMDFD_44: ; LD   B IYh
	mov zzB,zzIYh

	jmp zCMD_start

zCMDFD_45: ; LD   B IYl
	mov zzB,zzIYl

	jmp zCMD_start

zCMDFD_46: ; LD   B (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzB,FROMRAM0

	jmp zCMD_start

zCMDFD_47: ; LD   B A
	mov zzB,zzA

	jmp zCMD_start

zCMDFD_48: ; LD   C B
	mov zzC,zzB

	jmp zCMD_start

zCMDFD_49: ; LD   C C
	mov zzC,zzC

	jmp zCMD_start

zCMDFD_4a: ; LD   C D
	mov zzC,zzD

	jmp zCMD_start

zCMDFD_4b: ; LD   C E
	mov zzC,zzE

	jmp zCMD_start

zCMDFD_4c: ; LD   C IYh
	mov zzC,zzIYh

	jmp zCMD_start

zCMDFD_4d: ; LD   C IYl
	mov zzC,zzIYl

	jmp zCMD_start

zCMDFD_4e: ; LD   C (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzC,FROMRAM0

	jmp zCMD_start

zCMDFD_4f: ; LD   C A
	mov zzC,zzA

	jmp zCMD_start

zCMDFD_50: ; LD   D B
	mov zzD,zzB

	jmp zCMD_start

zCMDFD_51: ; LD   D C
	mov zzD,zzC

	jmp zCMD_start

zCMDFD_52: ; LD   D D
	mov zzD,zzD

	jmp zCMD_start

zCMDFD_53: ; LD   D E
	mov zzD,zzE

	jmp zCMD_start

zCMDFD_54: ; LD   D IYh
	mov zzD,zzIYh

	jmp zCMD_start

zCMDFD_55: ; LD   D IYl
	mov zzD,zzIYl

	jmp zCMD_start

zCMDFD_56: ; LD   D (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzD,FROMRAM0

	jmp zCMD_start

zCMDFD_57: ; LD   D A
	mov zzD,zzA

	jmp zCMD_start

zCMDFD_58: ; LD   E B
	mov zzE,zzB

	jmp zCMD_start

zCMDFD_59: ; LD   E C
	mov zzE,zzC

	jmp zCMD_start

zCMDFD_5a: ; LD   E D
	mov zzE,zzD

	jmp zCMD_start

zCMDFD_5b: ; LD   E E
	mov zzE,zzE

	jmp zCMD_start

zCMDFD_5c: ; LD   E IYh
	mov zzE,zzIYh

	jmp zCMD_start

zCMDFD_5d: ; LD   E IYl
	mov zzE,zzIYl

	jmp zCMD_start

zCMDFD_5e: ; LD   E (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzE,FROMRAM0

	jmp zCMD_start

zCMDFD_5f: ; LD   E A
	mov zzE,zzA

	jmp zCMD_start

zCMDFD_60: ; LD   IYh B
	mov zzIYh,zzB

	jmp zCMD_start

zCMDFD_61: ; LD   IYh C
	mov zzIYh,zzC

	jmp zCMD_start

zCMDFD_62: ; LD   IYh D
	mov zzIYh,zzD

	jmp zCMD_start

zCMDFD_63: ; LD   IYh E
	mov zzIYh,zzE

	jmp zCMD_start

zCMDFD_64: ; LD   IYh IYh
	mov zzIYh,zzIYh

	jmp zCMD_start

zCMDFD_65: ; LD   IYh IYl
	mov zzIYh,zzIYl

	jmp zCMD_start

zCMDFD_66: ; LD   H (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzH,FROMRAM0

	jmp zCMD_start

zCMDFD_67: ; LD   IYh A
	mov zzIYh,zzA

	jmp zCMD_start

zCMDFD_68: ; LD   IYl B
	mov zzIYl,zzB

	jmp zCMD_start

zCMDFD_69: ; LD   IYl C
	mov zzIYl,zzC

	jmp zCMD_start

zCMDFD_6a: ; LD   IYl D
	mov zzIYl,zzD

	jmp zCMD_start

zCMDFD_6b: ; LD   IYl E
	mov zzIYl,zzE

	jmp zCMD_start

zCMDFD_6c: ; LD   IYl IYh
	mov zzIYl,zzIYh

	jmp zCMD_start

zCMDFD_6d: ; LD   IYl IYl
	mov zzIYl,zzIYl

	jmp zCMD_start

zCMDFD_6e: ; LD   L (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzL,FROMRAM0

	jmp zCMD_start

zCMDFD_6f: ; LD   IYl A
	mov zzIYl,zzA

	jmp zCMD_start

zCMDFD_70: ; LD   (IY+d) B
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzB

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFD_71: ; LD   (IY+d) C
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzC

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFD_72: ; LD   (IY+d) D
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzD

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFD_73: ; LD   (IY+d) E
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzE

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFD_74: ; LD   (IY+d) H
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzH

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFD_75: ; LD   (IY+d) L
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzL

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFD_76: ; HALT  
	DEC2 zzPCh,zzPCl

	jmp zCMD_start

zCMDFD_77: ; LD   (IY+d) A
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	mov FROMRAM0,zzA

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFD_78: ; LD   A B
	mov zzA,zzB

	jmp zCMD_start

zCMDFD_79: ; LD   A C
	mov zzA,zzC

	jmp zCMD_start

zCMDFD_7a: ; LD   A D
	mov zzA,zzD

	jmp zCMD_start

zCMDFD_7b: ; LD   A E
	mov zzA,zzE

	jmp zCMD_start

zCMDFD_7c: ; LD   A IYh
	mov zzA,zzIYh

	jmp zCMD_start

zCMDFD_7d: ; LD   A IYl
	mov zzA,zzIYl

	jmp zCMD_start

zCMDFD_7e: ; LD   A (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzA,FROMRAM0

	jmp zCMD_start

zCMDFD_7f: ; LD   A A
	mov zzA,zzA

	jmp zCMD_start

zCMDFD_80: ; ADD  A B
	add zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_81: ; ADD  A C
	add zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_82: ; ADD  A D
	add zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_83: ; ADD  A E
	add zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_84: ; ADD  A IYh
	add zzA,zzIYh

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_85: ; ADD  A IYl
	add zzA,zzIYl

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_86: ; ADD  A (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	add zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_87: ; ADD  A A
	add zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_88: ; ADC  A B
	out SREG,zzF
	adc zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_89: ; ADC  A C
	out SREG,zzF
	adc zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_8a: ; ADC  A D
	out SREG,zzF
	adc zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_8b: ; ADC  A E
	out SREG,zzF
	adc zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_8c: ; ADC  A IYh
	out SREG,zzF
	adc zzA,zzIYh

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_8d: ; ADC  A IYl
	out SREG,zzF
	adc zzA,zzIYl

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_8e: ; ADC  A (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,zzF
	adc zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_8f: ; ADC  A A
	out SREG,zzF
	adc zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_90: ; SUB  A B
	sub zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_91: ; SUB  A C
	sub zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_92: ; SUB  A D
	sub zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_93: ; SUB  A E
	sub zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_94: ; SUB  A IYh
	sub zzA,zzIYh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_95: ; SUB  A IYl
	sub zzA,zzIYl

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_96: ; SUB  A (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	sub zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_97: ; SUB  A A
	sub zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_98: ; SBC  A B
	out SREG,zzF
	sez
	sbc zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_99: ; SBC  A C
	out SREG,zzF
	sez
	sbc zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_9a: ; SBC  A D
	out SREG,zzF
	sez
	sbc zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_9b: ; SBC  A E
	out SREG,zzF
	sez
	sbc zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_9c: ; SBC  A IYh
	out SREG,zzF
	sez
	sbc zzA,zzIYh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_9d: ; SBC  A IYl
	out SREG,zzF
	sez
	sbc zzA,zzIYl

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_9e: ; SBC  A (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,zzF
	sez
	sbc zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_9f: ; SBC  A A
	out SREG,zzF
	sez
	sbc zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_a0: ; AND  A B
	and zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_a1: ; AND  A C
	and zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_a2: ; AND  A D
	and zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_a3: ; AND  A E
	and zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_a4: ; AND  A IYh
	and zzA,zzIYh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_a5: ; AND  A IYl
	and zzA,zzIYl

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_a6: ; AND  A (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	and zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_a7: ; AND  A A
	and zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_a8: ; XOR  A B
	eor zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_a9: ; XOR  A C
	eor zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_aa: ; XOR  A D
	eor zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_ab: ; XOR  A E
	eor zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_ac: ; XOR  A IYh
	eor zzA,zzIYh

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_ad: ; XOR  A IYl
	eor zzA,zzIYl

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_ae: ; XOR  A (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	eor zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_af: ; XOR  A A
	eor zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_b0: ; OR   A B
	or zzA,zzB

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_b1: ; OR   A C
	or zzA,zzC

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_b2: ; OR   A D
	or zzA,zzD

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_b3: ; OR   A E
	or zzA,zzE

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_b4: ; OR   A IYh
	or zzA,zzIYh

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_b5: ; OR   A IYl
	or zzA,zzIYl

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_b6: ; OR   A (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	or zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_b7: ; OR   A A
	or zzA,zzA

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_b8: ; CP   A B
	cp zzA,zzB

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_b9: ; CP   A C
	cp zzA,zzC

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_ba: ; CP   A D
	cp zzA,zzD

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_bb: ; CP   A E
	cp zzA,zzE

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_bc: ; CP   A IYh
	cp zzA,zzIYh

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_bd: ; CP   A IYl
	cp zzA,zzIYl

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_be: ; CP   A (IY+d)
	LDRAM_PC_NODDR FROMRAM0
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	cp zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_bf: ; CP   A A
	cp zzA,zzA

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_c0: ; RET   NZ
	sbrc zzF,zzZF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDFD_c1: ; POP   BC
	zzPOP zzB,zzC

	jmp zCMD_start

zCMDFD_c2: ; JP   NZ nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzZF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_c3: ; JP   * nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	cpse ZERO,ZERO
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_c4: ; CALL NZ nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzZF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_c5: ; PUSH  BC
	zzPUSH zzB,zzC

	jmp zCMD_start

zCMDFD_c6: ; ADD  A n
	LDRAM_PC_NODDR FROMRAM0
	add zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_c7: ; RST   00h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0

	jmp zCMD_start

zCMDFD_c8: ; RET   Z
	sbrs zzF,zzZF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDFD_c9: ; RET   *
	cpse ZERO,ZERO
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDFD_ca: ; JP   Z nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzZF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_cb: ; FDCB  
	LDRAM_PC_NODDR FROMRAM0
	ldi Xh, high(zOPCODE_FDCB_LBLS_L)
	jmp zCMDP_start

	jmp zCMD_start

zCMDFD_cc: ; CALL Z nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzZF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_cd: ; CALL * nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	cpse ZERO,ZERO
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_ce: ; ADC  A n
	LDRAM_PC_NODDR FROMRAM0
	out SREG,zzF
	adc zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask flags
	jmp zCMD_start

zCMDFD_cf: ; RST   08h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x08

	jmp zCMD_start

zCMDFD_d0: ; RET   NC
	sbrc zzF,zzCF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDFD_d1: ; POP   DE
	zzPOP zzD,zzE

	jmp zCMD_start

zCMDFD_d2: ; JP   NC nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzCF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_d3: ; OUT  (n) A
	LDRAM_PC_NODDR FROMRAM0
	mov zzTmp,FROMRAM0
	sts CDATA,zzA
	call PORTOUT

	jmp zCMD_start

zCMDFD_d4: ; CALL NC nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzCF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_d5: ; PUSH  DE
	zzPUSH zzD,zzE

	jmp zCMD_start

zCMDFD_d6: ; SUB  A n
	LDRAM_PC_NODDR FROMRAM0
	sub zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_d7: ; RST   10h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x10

	jmp zCMD_start

zCMDFD_d8: ; RET   C
	sbrs zzF,zzCF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDFD_d9: ; EXX   
	EX zzH,zzHe
	EX zzL,zzLe
	EX zzB,zzBe
	EX zzC,zzCe
	EX zzD,zzDe
	EX zzE,zzEe
	

	jmp zCMD_start

zCMDFD_da: ; JP   C nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzCF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_db: ; IN   A (n)
	LDRAM_PC_NODDR FROMRAM0
	mov zzTmp,FROMRAM0
	call PORTIN
	mov zzA,zzTmp

	jmp zCMD_start

zCMDFD_dc: ; CALL C nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzCF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_de: ; SBC  A n
	LDRAM_PC_NODDR FROMRAM0
	out SREG,zzF
	sez
	sbc zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_df: ; RST   18h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x18

	jmp zCMD_start

zCMDFD_e0: ; RET   PO
	sbrc zzF,zzPF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDFD_e1: ; POP   IY
	zzPOP zzIYh,zzIYl

	jmp zCMD_start

zCMDFD_e2: ; JP   PO nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzPF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_e3: ; EX   (SP) IY
	mov FROMRAM1,zzSPh
	mov FROMRAM2,zzSPl
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	EXR FROMRAM0,zzIYl
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	INC2 FROMRAM1,FROMRAM2
	LDRAM FROMRAM1,FROMRAM2,FROMRAM0
	EXR FROMRAM0,zzIYh
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	

	jmp zCMD_start

zCMDFD_e4: ; CALL PO nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzPF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_e5: ; PUSH  IY
	zzPUSH zzIYh,zzIYl

	jmp zCMD_start

zCMDFD_e6: ; AND  A n
	LDRAM_PC_NODDR FROMRAM0
	and zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|___|___|___) ; mask results flags
	ldi zzF, 	(_I_|___|___|_H_|___|___|___)
	or zzF, zzTmp ; combine flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_e7: ; RST   20h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x20

	jmp zCMD_start

zCMDFD_e8: ; RET   PE
	sbrs zzF,zzPF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDFD_e9: ; JP   * IY
	cpse ZERO,ZERO
	jmp zCMD_start
	mov zzPCl,zzIYl
	mov zzPCh,zzIYh

	jmp zCMD_start

zCMDFD_ea: ; JP   PE nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzPF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_eb: ; EX   DE IY
	EXR zzD,zzIYh
	EXR zzE,zzIYl
	

	jmp zCMD_start

zCMDFD_ec: ; CALL PE nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzPF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_ee: ; XOR  A n
	LDRAM_PC_NODDR FROMRAM0
	eor zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_ef: ; RST   28h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x28

	jmp zCMD_start

zCMDFD_f0: ; RET   P
	sbrc zzF,zzSF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDFD_f1: ; POP   AF
	zzPOP zzA,FROMRAM0
	ldi Xh,high(FZ2ATABLE)
	mov Xl,FROMRAM0
	ld zzF,X

	jmp zCMD_start

zCMDFD_f2: ; JP   P nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzSF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_f3: ; DI    
	zzSET zzIFF1,0
	zzSET zzIFF2,0

	jmp zCMD_start

zCMDFD_f4: ; CALL P nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrc zzF,zzSF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_f5: ; PUSH  AF
	ldi Xh,high(FA2ZTABLE)
	mov Xl,zzF
	ld FROMRAM0,X
	zzPUSH zzA,FROMRAM0

	jmp zCMD_start

zCMDFD_f6: ; OR   A n
	LDRAM_PC_NODDR FROMRAM0
	or zzA,FROMRAM0

	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|___) ; mask flags
	SET_P_FLAG zzA ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFD_f7: ; RST   30h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x30

	jmp zCMD_start

zCMDFD_f8: ; RET   M
	sbrs zzF,zzSF
	jmp zCMD_start
	zzPOP zzPCh,zzPCl

	jmp zCMD_start

zCMDFD_f9: ; LD   SP IY
	mov zzSPh, zzIYh
	mov zzSPl, zzIYl

	jmp zCMD_start

zCMDFD_fa: ; JP   M nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzSF
	jmp zCMD_start
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_fb: ; EI    
	zzSET zzIFF1,1
	zzSET zzIFF2,1

	jmp zCMD_start

zCMDFD_fc: ; CALL M nn
	LDRAM_PC_NODDR FROMRAM2
	LDRAM_PC_NODDR FROMRAM1
	sbrs zzF,zzSF
	jmp zCMD_start
	zzPUSH zzPCh,zzPCl
	mov zzPCl,FROMRAM2
	mov zzPCh,FROMRAM1

	jmp zCMD_start

zCMDFD_fe: ; CP   A n
	LDRAM_PC_NODDR FROMRAM0
	cp zzA,FROMRAM0

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|_H_|_V_|___|_C_) ; mask results flags
	ldi zzF, 	(_I_|___|___|___|___|_N_|___)
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFD_ff: ; RST   38h
	zzPUSH zzPCh,zzPCl
	clr zzPCh
	ldi zzPCl,0x38

	jmp zCMD_start

zCMDDDCB_06: ; RLC   (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	bst FROMRAM0,7
	lsl FROMRAM0
	bld FROMRAM0,0
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDDCB_0e: ; RRC   (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	bst FROMRAM0,0
	lsr FROMRAM0
	bld FROMRAM0,7
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDDCB_16: ; RL    (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,zzF
	rol FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDDCB_1e: ; RR    (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,zzF
	ror FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDDCB_26: ; SLA   (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	lsl FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDDCB_2e: ; SRA   (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	bst FROMRAM0,7
	lsr FROMRAM0
	bld FROMRAM0,7
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDDCB_36: ; SLL   (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	lsl FROMRAM0
	set
	bld FROMRAM0,0
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDDCB_3e: ; SRL   (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	lsr FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|___|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDDDCB_46: ; BIT  0 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<0
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDDCB_4e: ; BIT  1 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<1
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDDCB_56: ; BIT  2 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<2
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDDCB_5e: ; BIT  3 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<3
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDDCB_66: ; BIT  4 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<4
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDDCB_6e: ; BIT  5 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<5
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDDCB_76: ; BIT  6 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<6
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDDCB_7e: ; BIT  7 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<7
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDDDCB_86: ; RES  0 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<0)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_8e: ; RES  1 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<1)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_96: ; RES  2 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<2)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_9e: ; RES  3 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<3)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_a6: ; RES  4 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<4)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_ae: ; RES  5 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<5)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_b6: ; RES  6 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<6)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_be: ; RES  7 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<7)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_c6: ; SET  0 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<0
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_ce: ; SET  1 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<1
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_d6: ; SET  2 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<2
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_de: ; SET  3 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<3
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_e6: ; SET  4 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<4
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_ee: ; SET  5 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<5
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_f6: ; SET  6 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<6
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDDDCB_fe: ; SET  7 (IX+d)
	mov FROMRAM2,zzIXl
	mov FROMRAM1,zzIXh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<7
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_06: ; RLC   (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	bst FROMRAM0,7
	lsl FROMRAM0
	bld FROMRAM0,0
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFDCB_0e: ; RRC   (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	bst FROMRAM0,0
	lsr FROMRAM0
	bld FROMRAM0,7
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFDCB_16: ; RL    (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,zzF
	rol FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFDCB_1e: ; RR    (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,zzF
	ror FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFDCB_26: ; SLA   (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	lsl FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFDCB_2e: ; SRA   (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	bst FROMRAM0,7
	lsr FROMRAM0
	bld FROMRAM0,7
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFDCB_36: ; SLL   (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	lsl FROMRAM0
	set
	bld FROMRAM0,0
	or FROMRAM0,FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|_S_|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFDCB_3e: ; SRL   (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	lsr FROMRAM0

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	in zzF, SREG
	andi zzF, 	(_I_|___|_Z_|___|___|___|_C_) ; mask flags
	SET_P_FLAG FROMRAM0 ;(___|___|___|_P_|___|___) ; set P flag
	jmp zCMD_start

zCMDFDCB_46: ; BIT  0 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<0
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFDCB_4e: ; BIT  1 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<1
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFDCB_56: ; BIT  2 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<2
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFDCB_5e: ; BIT  3 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<3
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFDCB_66: ; BIT  4 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<4
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFDCB_6e: ; BIT  5 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<5
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFDCB_76: ; BIT  6 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<6
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFDCB_7e: ; BIT  7 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	mov zzTmp,FROMRAM0
	andi zzTmp,1<<7
	clv
	in zzTmp,SREG
	sbrc zzTmp,zzZF
	sev

	in zzTmp, SREG
	andi zzTmp, 	(_I_|_S_|_Z_|___|_V_|___|___) ; mask results flags
	andi zzF, 	(_I_|___|___|___|___|___|_C_) ; mask old flags
	ori zzF, 	(_I_|___|___|_H_|___|___|___) ; set flags
	or zzF, zzTmp ; combine flags
	jmp zCMD_start

zCMDFDCB_86: ; RES  0 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<0)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_8e: ; RES  1 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<1)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_96: ; RES  2 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<2)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_9e: ; RES  3 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<3)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_a6: ; RES  4 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<4)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_ae: ; RES  5 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<5)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_b6: ; RES  6 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<6)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_be: ; RES  7 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,~(1<<7)
	and FROMRAM0,zzTmp 

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_c6: ; SET  0 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<0
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_ce: ; SET  1 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<1
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_d6: ; SET  2 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<2
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_de: ; SET  3 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<3
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_e6: ; SET  4 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<4
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_ee: ; SET  5 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<5
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_f6: ; SET  6 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<6
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

zCMDFDCB_fe: ; SET  7 (IY+d)
	mov FROMRAM2,zzIYl
	mov FROMRAM1,zzIYh
	ADDWS FROMRAM1,FROMRAM2,FROMRAM0
	LDRAM_NODDR FROMRAM1,FROMRAM2,FROMRAM0
	ldi zzTmp,1<<7
	or FROMRAM0,zzTmp

	in _sreg, SREG
	STRAM FROMRAM1,FROMRAM2,FROMRAM0
	out SREG,_sreg
	jmp zCMD_start

