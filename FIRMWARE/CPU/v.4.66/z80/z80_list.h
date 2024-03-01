//typedef uint8_t

uint8_t z80_asm[][3] = {                   // No prefix
  { /* 0x00 */ _nop_,_x_,_x_},    // 00	NOP		       
  { /* 0x01 */ _ld2_,_bc_,_nn_},   // 01	LD	BC,nn	   
  { /* 0x02 */ _ld_,_IbcI_,_a_},  // 02	LD	(BC),A	 
  { /* 0x03 */ _inc2_,_x_,_bc_},   // 03	INC	BC	     
  { /* 0x04 */ _inc_,_x_,_b_},    // 04	INC	B	       
  { /* 0x05 */ _dec_,_x_,_b_},    // 05	DEC	B	       
  { /* 0x06 */ _ld_,_b_,_n_},     // 06	LD	B,n	     
  { /* 0x07 */ _rlca_,_x_,_x_},   // 07	RLCA		     
  { /* 0x08 */ _exaf_,_af_,_afe_},  // 08	EX	AF,AF'	 
  { /* 0x09 */ _add2_,_hl_,_bc_},   // 09	ADD	HL,BC	   
  { /* 0x0a */ _ld_,_a_,_IbcI_},  // 0A	LD	A,(BC)	 
  { /* 0x0b */ _dec2_,_x_,_bc_},   // 0B	DEC	BC	     
  { /* 0x0c */ _inc_,_x_,_c_},    // 0C	INC	C	       
  { /* 0x0d */ _dec_,_x_,_c_},    // 0D	DEC	C	       
  { /* 0x0e */ _ld_,_c_,_n_},     // 0E	LD	C,n	     
  { /* 0x0f */ _rrca_,_x_,_x_},   // 0F	RRCA		     
  { /* 0x10 */ _djnz_,_x_,_s_},   // 10	DJNZ	e	     
  { /* 0x11 */ _ld2_,_de_,_nn_},   // 11	LD	DE,nn	   
  { /* 0x12 */ _ld_,_IdeI_,_a_},  // 12	LD	(DE),A	 
  { /* 0x13 */ _inc2_,_x_,_de_},   // 13	INC	DE	     
  { /* 0x14 */ _inc_,_x_,_d_},    // 14	INC	D	       
  { /* 0x15 */ _dec_,_x_,_d_},    // 15	DEC	D	       
  { /* 0x16 */ _ld_,_d_,_n_},     // 16	LD	D,n	     
  { /* 0x17 */ _rla_,_x_,_x_},    // 17	RLA		       
  { /* 0x18 */ _jr_,_ANY_,_s_},     // 18	JR	e	       
  { /* 0x19 */ _add2_,_hl_,_de_},   // 19	ADD	HL,DE	   
  { /* 0x1a */ _ld_,_a_,_IdeI_},  // 1A	LD	A,(DE)	 
  { /* 0x1b */ _dec2_,_x_,_de_},   // 1B	DEC	DE	     
  { /* 0x1c */ _inc_,_x_,_e_},    // 1C	INC	E	       
  { /* 0x1d */ _dec_,_x_,_e_},    // 1D	DEC	E	       
  { /* 0x1e */ _ld_,_e_,_n_},     // 1E	LD	E,n	     
  { /* 0x1f */ _rra_,_x_,_x_},    // 1F	RRA		       
  { /* 0x20 */ _jr_,_nZ_,_s_},     // 20	JR	NZ,e	   
  { /* 0x21 */ _ld2_,_hl_,_nn_},    // 21	LD	HL,nn	   
  { /* 0x22 */ _ldw_,_IwwI_,_hl_}, // 22	LD	(nn),HL	 
  { /* 0x23 */ _inc2_,_x_,_hl_},    // 23	INC	HL	     
  { /* 0x24 */ _inc_,_x_,_h_},    // 24	INC	H	       
  { /* 0x25 */ _dec_,_x_,_h_},    // 25	DEC	H	       
  { /* 0x26 */ _ld_,_h_,_n_},     // 26	LD	H,n	     
  { /* 0x27 */ _daa_,_x_,_x_},    // 27	DAA		       
  { /* 0x28 */ _jr_,_Z_,_s_},     // 28	JR	Z,e	
  { /* 0x29 */ _add2_,_hl_,_hl_},   // 29	ADD	HL,HL	   
  { /* 0x2a */ _ldw_,_hl_,_IwwI_},  // 2A	LD	HL,(nn)	 
  { /* 0x2b */ _dec2_,_x_,_hl_},    // 2B	DEC	HL	     
  { /* 0x2c */ _inc_,_x_,_l_},    // 2C	INC	L	       
  { /* 0x2d */ _dec_,_x_,_l_},    // 2D	DEC	L	       
  { /* 0x2e */ _ld_,_l_,_n_},     // 2E	LD	L,n	     
  { /* 0x2f */ _cpl_,_x_,_a_},    // 2F	CPL		       
  { /* 0x30 */ _jr_,_nC_,_s_},     // 30	JR	NC,e	   
  { /* 0x31 */ _ld2_,_sp_,_nn_},    // 31	LD	SP,nn	   
  { /* 0x32 */ _ld_,_InnI_,_a_},  // 32	LD	(nn),A	 
  { /* 0x33 */ _inc2_,_x_,_sp_},    // 33	INC	SP	     
  { /* 0x34 */ _inc_,_x_,_IhlI_}, // 34	INC	(HL)	   
  { /* 0x35 */ _dec_,_x_,_IhlI_}, // 35	DEC	(HL)	   
  { /* 0x36 */ _ld_,_IhlI_,_n_},  // 36	LD	(HL),n	     !!!!!!!!
  { /* 0x37 */ _scf_,_x_,_x_},    // 37	SCF		       
  { /* 0x38 */ _jr_,_C_,_s_},     // 38	JR	C,e	     
  { /* 0x39 */ _add2_,_hl_,_sp_},   // 39	ADD	HL,SP	   
  { /* 0x3a */ _ld_,_a_,_InnI_},  // 3A	LD	A,(nn)	 
  { /* 0x3b */ _dec2_,_x_,_sp_},    // 3B	DEC	SP	     
  { /* 0x3c */ _inc_,_x_,_a_},    // 3C	INC	A	       
  { /* 0x3d */ _dec_,_x_,_a_},    // 3D	DEC	A	       
  { /* 0x3e */ _ld_,_a_,_n_},     // 3E	LD	A,n	     
  { /* 0x3f */ _ccf_,_x_,_x_},    // 3F	CCF		       
  { /* 0x40 */ _ld_,_b_,_b_},     // 40	LD	B,B	     
  { /* 0x41 */ _ld_,_b_,_c_},     // 41	LD	B,C	     
  { /* 0x42 */ _ld_,_b_,_d_},     // 42	LD	B,D	     
  { /* 0x43 */ _ld_,_b_,_e_},     // 43	LD	B,E	     
  { /* 0x44 */ _ld_,_b_,_h_},     // 44	LD	B,H	     
  { /* 0x45 */ _ld_,_b_,_l_},     // 45	LD	B,L	     
  { /* 0x46 */ _ld_,_b_,_IhlI_},  // 46	LD	B,(HL)	 
  { /* 0x47 */ _ld_,_b_,_a_},     // 47	LD	B,A	     
  { /* 0x48 */ _ld_,_c_,_b_},     // 48	LD	C,B	     
  { /* 0x49 */ _ld_,_c_,_c_},     // 49	LD	C,C	     
  { /* 0x4a */ _ld_,_c_,_d_},     // 4A	LD	C,D	     
  { /* 0x4b */ _ld_,_c_,_e_},     // 4B	LD	C,E	     
  { /* 0x4c */ _ld_,_c_,_h_},     // 4C	LD	C,H	     
  { /* 0x4d */ _ld_,_c_,_l_},     // 4D	LD	C,L	     
  { /* 0x4e */ _ld_,_c_,_IhlI_},  // 4E	LD	C,(HL)	 
  { /* 0x4f */ _ld_,_c_,_a_},     // 4F	LD	C,A	     
  { /* 0x50 */ _ld_,_d_,_b_},     // 50	LD	D,B	     
  { /* 0x51 */ _ld_,_d_,_c_},     // 51	LD	D,C	     
  { /* 0x52 */ _ld_,_d_,_d_},     // 52	LD	D,D	     
  { /* 0x53 */ _ld_,_d_,_e_},     // 53	LD	D,E	     
  { /* 0x54 */ _ld_,_d_,_h_},     // 54	LD	D,H	     
  { /* 0x55 */ _ld_,_d_,_l_},     // 55	LD	D,L	     
  { /* 0x56 */ _ld_,_d_,_IhlI_},  // 56	LD	D,(HL)	 
  { /* 0x57 */ _ld_,_d_,_a_},     // 57	LD	D,A	     
  { /* 0x58 */ _ld_,_e_,_b_},     // 58	LD	E,B	     
  { /* 0x59 */ _ld_,_e_,_c_},     // 59	LD	E,C	     
  { /* 0x5a */ _ld_,_e_,_d_},     // 5A	LD	E,D	     
  { /* 0x5b */ _ld_,_e_,_e_},     // 5B	LD	E,E	     
  { /* 0x5c */ _ld_,_e_,_h_},     // 5C	LD	E,H	     
  { /* 0x5d */ _ld_,_e_,_l_},     // 5D	LD	E,L	     
  { /* 0x5e */ _ld_,_e_,_IhlI_},  // 5E	LD	E,(HL)	 
  { /* 0x5f */ _ld_,_e_,_a_},     // 5F	LD	E,A	     
  { /* 0x60 */ _ld_,_h_,_b_},     // 60	LD	H,B	     
  { /* 0x61 */ _ld_,_h_,_c_},     // 61	LD	H,C	     
  { /* 0x62 */ _ld_,_h_,_d_},     // 62	LD	H,D	     
  { /* 0x63 */ _ld_,_h_,_e_},     // 63	LD	H,E	     
  { /* 0x64 */ _ld_,_h_,_h_},     // 64	LD	H,H	     
  { /* 0x65 */ _ld_,_h_,_l_},     // 65	LD	H,L	     
  { /* 0x66 */ _ld_,_h_,_IhlI_},  // 66	LD	H,(HL)	 
  { /* 0x67 */ _ld_,_h_,_a_},     // 67	LD	H,A	     
  { /* 0x68 */ _ld_,_l_,_b_},     // 68	LD	L,B	     
  { /* 0x69 */ _ld_,_l_,_c_},     // 69	LD	L,C	     
  { /* 0x6a */ _ld_,_l_,_d_},     // 6A	LD	L,D	     
  { /* 0x6b */ _ld_,_l_,_e_},     // 6B	LD	L,E	     
  { /* 0x6c */ _ld_,_l_,_h_},     // 6C	LD	L,H	     
  { /* 0x6d */ _ld_,_l_,_l_},     // 6D	LD	L,L	     
  { /* 0x6e */ _ld_,_l_,_IhlI_},  // 6E	LD	L,(HL)	 
  { /* 0x6f */ _ld_,_l_,_a_},     // 6F	LD	L,A	     
  { /* 0x70 */ _ld_,_IhlI_,_b_},  // 70	LD	(HL),B	 
  { /* 0x71 */ _ld_,_IhlI_,_c_},  // 71	LD	(HL),C	 
  { /* 0x72 */ _ld_,_IhlI_,_d_},  // 72	LD	(HL),D	 
  { /* 0x73 */ _ld_,_IhlI_,_e_},  // 73	LD	(HL),E	 
  { /* 0x74 */ _ld_,_IhlI_,_h_},  // 74	LD	(HL),H	 
  { /* 0x75 */ _ld_,_IhlI_,_l_},  // 75	LD	(HL),L	 
  { /* 0x76 */ _halt_,_x_,_x_},   // 76	HALT		     
  { /* 0x77 */ _ld_,_IhlI_,_a_},  // 77	LD	(HL),A	 
  { /* 0x78 */ _ld_,_a_,_b_},     // 78	LD	A,B	     
  { /* 0x79 */ _ld_,_a_,_c_},     // 79	LD	A,C	     
  { /* 0x7a */ _ld_,_a_,_d_},     // 7A	LD	A,D	     
  { /* 0x7b */ _ld_,_a_,_e_},     // 7B	LD	A,E	     
  { /* 0x7c */ _ld_,_a_,_h_},     // 7C	LD	A,H	     
  { /* 0x7d */ _ld_,_a_,_l_},     // 7D	LD	A,L	     
  { /* 0x7e */ _ld_,_a_,_IhlI_},  // 7E	LD	A,(HL)	 
  { /* 0x7f */ _ld_,_a_,_a_},     // 7F	LD	A,A	     
  { /* 0x80 */ _add_,_a_,_b_},    // 80	ADD	A,B	     
  { /* 0x81 */ _add_,_a_,_c_},    // 81	ADD	A,C	     
  { /* 0x82 */ _add_,_a_,_d_},    // 82	ADD	A,D	     
  { /* 0x83 */ _add_,_a_,_e_},    // 83	ADD	A,E	     
  { /* 0x84 */ _add_,_a_,_h_},    // 84	ADD	A,H	     
  { /* 0x85 */ _add_,_a_,_l_},    // 85	ADD	A,L	     
  { /* 0x86 */ _add_,_a_,_IhlI_}, // 86	ADD	A,(HL)	 
  { /* 0x87 */ _add_,_a_,_a_},    // 87	ADD	A,A	     
  { /* 0x88 */ _adc_,_a_,_b_},    // 88	ADC	A,B	     
  { /* 0x89 */ _adc_,_a_,_c_},    // 89	ADC	A,C	     
  { /* 0x8a */ _adc_,_a_,_d_},    // 8A	ADC	A,D	     
  { /* 0x8b */ _adc_,_a_,_e_},    // 8B	ADC	A,E	     
  { /* 0x8c */ _adc_,_a_,_h_},    // 8C	ADC	A,H	     
  { /* 0x8d */ _adc_,_a_,_l_},    // 8D	ADC	A,L	     
  { /* 0x8e */ _adc_,_a_,_IhlI_}, // 8E	ADC	A,(HL)	 
  { /* 0x8f */ _adc_,_a_,_a_},    // 8F	ADC	A,A	     
  { /* 0x90 */ _sub_,_a_,_b_},    // 90	SUB	B	       
  { /* 0x91 */ _sub_,_a_,_c_},    // 91	SUB	C	       
  { /* 0x92 */ _sub_,_a_,_d_},    // 92	SUB	D	       
  { /* 0x93 */ _sub_,_a_,_e_},    // 93	SUB	E	       
  { /* 0x94 */ _sub_,_a_,_h_},    // 94	SUB	H	       
  { /* 0x95 */ _sub_,_a_,_l_},    // 95	SUB	L	       
  { /* 0x96 */ _sub_,_a_,_IhlI_}, // 96	SUB	(HL)	   
  { /* 0x97 */ _sub_,_a_,_a_},    // 97	SUB	A	       
  { /* 0x98 */ _sbc_,_a_,_b_},    // 98	SBC	B	       
  { /* 0x99 */ _sbc_,_a_,_c_},    // 99	SBC	C	       
  { /* 0x9a */ _sbc_,_a_,_d_},    // 9A	SBC	D	       
  { /* 0x9b */ _sbc_,_a_,_e_},    // 9B	SBC	E	       
  { /* 0x9c */ _sbc_,_a_,_h_},    // 9C	SBC	H	       
  { /* 0x9d */ _sbc_,_a_,_l_},    // 9D	SBC	L	       
  { /* 0x9e */ _sbc_,_a_,_IhlI_}, // 9E	SBC	(HL)	   
  { /* 0x9f */ _sbc_,_a_,_a_},    // 9F	SBC	A	       
  { /* 0xa0 */ _and_,_a_,_b_},    // A0	AND	B	       
  { /* 0xa1 */ _and_,_a_,_c_},    // A1	AND	C	       
  { /* 0xa2 */ _and_,_a_,_d_},    // A2	AND	D	       
  { /* 0xa3 */ _and_,_a_,_e_},    // A3	AND	E	       
  { /* 0xa4 */ _and_,_a_,_h_},    // A4	AND	H	       
  { /* 0xa5 */ _and_,_a_,_l_},    // A5	AND	L	       
  { /* 0xa6 */ _and_,_a_,_IhlI_}, // A6	AND	(HL)	   
  { /* 0xa7 */ _and_,_a_,_a_},    // A7	AND	A	       
  { /* 0xa8 */ _xor_,_a_,_b_},    // A8	XOR	B	       
  { /* 0xa9 */ _xor_,_a_,_c_},    // A9	XOR	C	       
  { /* 0xaa */ _xor_,_a_,_d_},    // AA	XOR	D	       
  { /* 0xab */ _xor_,_a_,_e_},    // AB	XOR	E	       
  { /* 0xac */ _xor_,_a_,_h_},    // AC	XOR	H	       
  { /* 0xad */ _xor_,_a_,_l_},    // AD	XOR	L	       
  { /* 0xae */ _xor_,_a_,_IhlI_}, // AE	XOR	(HL)	   
  { /* 0xaf */ _xor_,_a_,_a_},    // AF	XOR	A	       
  { /* 0xb0 */ _or_,_a_,_b_},     // B0	OR	B	       
  { /* 0xb1 */ _or_,_a_,_c_},     // B1	OR	C	       
  { /* 0xb2 */ _or_,_a_,_d_},     // B2	OR	D	       
  { /* 0xb3 */ _or_,_a_,_e_},     // B3	OR	E	       
  { /* 0xb4 */ _or_,_a_,_h_},     // B4	OR	H	       
  { /* 0xb5 */ _or_,_a_,_l_},     // B5	OR	L	       
  { /* 0xb6 */ _or_,_a_,_IhlI_},  // B6	OR	(HL)	   
  { /* 0xb7 */ _or_,_a_,_a_},     // B7	OR	A	       
  { /* 0xb8 */ _cp_,_a_,_b_},     // B8	CP	B	       
  { /* 0xb9 */ _cp_,_a_,_c_},     // B9	CP	C	       
  { /* 0xba */ _cp_,_a_,_d_},     // BA	CP	D	       
  { /* 0xbb */ _cp_,_a_,_e_},     // BB	CP	E	       
  { /* 0xbc */ _cp_,_a_,_h_},     // BC	CP	H	       
  { /* 0xbd */ _cp_,_a_,_l_},     // BD	CP	L	       
  { /* 0xbe */ _cp_,_a_,_IhlI_},  // BE	CP	(HL)	   
  { /* 0xbf */ _cp_,_a_,_a_},     // BF	CP	A	       
  { /* 0xc0 */ _ret_,_x_,_nZ_},    // C0	RET	NZ	     
  { /* 0xc1 */ _pop_,_x_,_bc_},   // C1	POP	BC	     
  { /* 0xc2 */ _jp_,_nZ_,_nn_},    // C2	JP	NZ,nn	   
  { /* 0xc3 */ _jp_,_ANY_,_nn_},     // C3	JP	nn	     
  { /* 0xc4 */ _call_,_nZ_,_nn_},  // C4	CALL	NZ,nn	 
  { /* 0xc5 */ _push_,_x_,_bc_},  // C5	PUSH	BC	   
  { /* 0xc6 */ _add_,_a_,_n_},    // C6	ADD	A,n	     
  { /* 0xc7 */ _rst_,_x_,_00h_},   // C7	RST	00H	     
  { /* 0xc8 */ _ret_,_x_,_Z_},    // C8	RET	Z	       
  { /* 0xc9 */ _ret_,_x_,_ANY_},    // C9	RET		       
  { /* 0xca */ _jp_,_Z_,_nn_},    // CA	JP	Z,nn	   
  { /* 0xcb */ _CB_,_x_,_x_},    // CB	#CB		       
  { /* 0xcc */ _call_,_Z_,_nn_},  // CC	CALL	Z,nn	 
  { /* 0xcd */ _call_,_ANY_,_nn_},   // CD	CALL	nn	   
  { /* 0xce */ _adc_,_a_,_n_},    // CE	ADC	A,n	     
  { /* 0xcf */ _rst_,_x_,_08h_},   // CF	RST	08H	     
  { /* 0xd0 */ _ret_,_x_,_nC_},    // D0	RET	NC	     
  { /* 0xd1 */ _pop_,_x_,_de_},   // D1	POP	DE	     
  { /* 0xd2 */ _jp_,_nC_,_nn_},    // D2	JP	NC,nn	   
  { /* 0xd3 */ _out_,_InI_,_a_},  // D3	OUT	(n),A	   
  { /* 0xd4 */ _call_,_nC_,_nn_},  // D4	CALL	NC,nn	 
  { /* 0xd5 */ _push_,_x_,_de_},  // D5	PUSH	DE	   
  { /* 0xd6 */ _sub_,_a_,_n_},    // D6	SUB	n	       
  { /* 0xd7 */ _rst_,_x_,_10h_},   // D7	RST	10H	     
  { /* 0xd8 */ _ret_,_x_,_C_},    // D8	RET	C	       
  { /* 0xd9 */ _exx_,_x_,_x_},    // D9	EXX		       
  { /* 0xda */ _jp_,_C_,_nn_},    // DA	JP	C,nn	   
  { /* 0xdb */ _in_,_a_,_InI_},   // DB	IN	A,(n)	   
  { /* 0xdc */ _call_,_C_,_nn_},  // DC	CALL	C,nn	 
  { /* 0xdd */ _DD_,_x_,_x_},    // DD	#DD		       
  { /* 0xde */ _sbc_,_a_,_n_},    // DE	SBC	A,n	     
  { /* 0xdf */ _rst_,_x_,_18h_},   // DF	RST	18H	     
  { /* 0xe0 */ _ret_,_x_,_pO_},    // E0	RET	PO	     
  { /* 0xe1 */ _pop_,_x_,_hl_},    // E1	POP	HL	     
  { /* 0xe2 */ _jp_,_pO_,_nn_},    // E2	JP	PO,nn	   
  { /* 0xe3 */ _exs_,_IspI_,_hl_}, // E3	EX	(SP),HL	 
  { /* 0xe4 */ _call_,_pO_,_nn_},  // E4	CALL	PO,nn	 
  { /* 0xe5 */ _push_,_x_,_hl_},   // E5	PUSH	HL	   
  { /* 0xe6 */ _and_,_a_,_n_},    // E6	AND	n	       
  { /* 0xe7 */ _rst_,_x_,_20h_},   // E7	RST	20H	     
  { /* 0xe8 */ _ret_,_x_,_pE_},    // E8	RET	PE	     
  { /* 0xe9 */ _jp_,_ANY_,_hl_},  // E9	JP	HL ???????? it was (HL) - CHECK !!!!!
  { /* 0xea */ _jp_,_pE_,_nn_},    // EA	JP	PE,nn	   
  { /* 0xeb */ _ex_,_de_,_hl_},   // EB	EX	DE,HL	   
  { /* 0xec */ _call_,_pE_,_nn_},  // EC	CALL	PE,nn	 
  { /* 0xed */ _ED_,_x_,_x_},    // ED	#ED		       
  { /* 0xee */ _xor_,_a_,_n_},    // EE	XOR	n	       
  { /* 0xef */ _rst_,_x_,_28h_},   // EF	RST	28H	     
  { /* 0xf0 */ _ret_,_x_,_P_},    // F0	RET	P	       
  { /* 0xf1 */ _popaf_,_x_,_af_},   // F1	POP	AF	     
  { /* 0xf2 */ _jp_,_P_,_nn_},    // F2	JP	P,nn	   
  { /* 0xf3 */ _di_,_x_,_x_},     // F3	DI		       
  { /* 0xf4 */ _call_,_P_,_nn_},  // F4	CALL	P,nn	 
  { /* 0xf5 */ _pushaf_,_x_,_af_},  // F5	PUSH	AF	   
  { /* 0xf6 */ _or_,_a_,_n_},     // F6	OR	n	       
  { /* 0xf7 */ _rst_,_x_,_30h_},   // F7	RST	30H	     
  { /* 0xf8 */ _ret_,_x_,_M_},    // F8	RET	M	       
  { /* 0xf9 */ _ld2_,_sp_,_hl_},    // F9	LD	SP,HL	   
  { /* 0xfa */ _jp_,_M_,_nn_},    // FA	JP	M,nn	   
  { /* 0xfb */ _ei_,_x_,_x_},     // FB	EI		       
  { /* 0xfc */ _call_,_M_,_nn_},  // FC	CALL	M,nn	 
  { /* 0xfd */ _FD_,_x_,_x_},    // FD	#FD		       
  { /* 0xfe */ _cp_,_a_,_n_},     // FE	CP	n	       
  { /* 0xff */ _rst_,_x_,_38h_}   // FF	RST	38H	     
};

//  {#cb}
uint8_t z80_asm_CB[][3] =   {                   // CB              
  { /* 0x00 */ _rlc_,_x_,_b_},    // 00	RLC	B	       
  { /* 0x01 */ _rlc_,_x_,_c_},    // 01	RLC	C	       
  { /* 0x02 */ _rlc_,_x_,_d_},    // 02	RLC	D	       
  { /* 0x03 */ _rlc_,_x_,_e_},    // 03	RLC	E	       
  { /* 0x04 */ _rlc_,_x_,_h_},    // 04	RLC	H	       
  { /* 0x05 */ _rlc_,_x_,_l_},    // 05	RLC	L	       
  { /* 0x06 */ _rlc_,_x_,_IhlI_}, // 06	RLC	(HL)	   
  { /* 0x07 */ _rlc_,_x_,_a_},    // 07	RLC	A	       
  { /* 0x08 */ _rrc_,_x_,_b_},    // 08	RRC	B	       
  { /* 0x09 */ _rrc_,_x_,_c_},    // 09	RRC	C	       
  { /* 0x0a */ _rrc_,_x_,_d_},    // 0A	RRC	D	       
  { /* 0x0b */ _rrc_,_x_,_e_},    // 0B	RRC	E	       
  { /* 0x0c */ _rrc_,_x_,_h_},    // 0C	RRC	H	       
  { /* 0x0d */ _rrc_,_x_,_l_},    // 0D	RRC	L	       
  { /* 0x0e */ _rrc_,_x_,_IhlI_}, // 0E	RRC	(HL)	   
  { /* 0x0f */ _rrc_,_x_,_a_},    // 0F	RRC	A	       
  { /* 0x10 */ _rl_,_x_,_b_},     // 10	RL	B	       
  { /* 0x11 */ _rl_,_x_,_c_},     // 11	RL	C	       
  { /* 0x12 */ _rl_,_x_,_d_},     // 12	RL	D	       
  { /* 0x13 */ _rl_,_x_,_e_},     // 13	RL	E	       
  { /* 0x14 */ _rl_,_x_,_h_},     // 14	RL	H	       
  { /* 0x15 */ _rl_,_x_,_l_},     // 15	RL	L	       
  { /* 0x16 */ _rl_,_x_,_IhlI_},  // 16	RL	(HL)	   
  { /* 0x17 */ _rl_,_x_,_a_},     // 17	RL	A	       
  { /* 0x18 */ _rr_,_x_,_b_},     // 18	RR	B	       
  { /* 0x19 */ _rr_,_x_,_c_},     // 19	RR	C	       
  { /* 0x1a */ _rr_,_x_,_d_},     // 1A	RR	D	       
  { /* 0x1b */ _rr_,_x_,_e_},     // 1B	RR	E	       
  { /* 0x1c */ _rr_,_x_,_h_},     // 1C	RR	H	       
  { /* 0x1d */ _rr_,_x_,_l_},     // 1D	RR	L	       
  { /* 0x1e */ _rr_,_x_,_IhlI_},  // 1E	RR	(HL)	   
  { /* 0x1f */ _rr_,_x_,_a_},     // 1F	RR	A	       
  { /* 0x20 */ _sla_,_x_,_b_},    // 20	SLA	B	       
  { /* 0x21 */ _sla_,_x_,_c_},    // 21	SLA	C	       
  { /* 0x22 */ _sla_,_x_,_d_},    // 22	SLA	D	       
  { /* 0x23 */ _sla_,_x_,_e_},    // 23	SLA	E	       
  { /* 0x24 */ _sla_,_x_,_h_},    // 24	SLA	H	       
  { /* 0x25 */ _sla_,_x_,_l_},    // 25	SLA	L	       
  { /* 0x26 */ _sla_,_x_,_IhlI_}, // 26	SLA	(HL)	   
  { /* 0x27 */ _sla_,_x_,_a_},    // 27	SLA	A	       
  { /* 0x28 */ _sra_,_x_,_b_},    // 28	SRA	B	       
  { /* 0x29 */ _sra_,_x_,_c_},    // 29	SRA	C	       
  { /* 0x2a */ _sra_,_x_,_d_},    // 2A	SRA	D	       
  { /* 0x2b */ _sra_,_x_,_e_},    // 2B	SRA	E	       
  { /* 0x2c */ _sra_,_x_,_h_},    // 2C	SRA	H	       
  { /* 0x2d */ _sra_,_x_,_l_},    // 2D	SRA	L	       
  { /* 0x2e */ _sra_,_x_,_IhlI_}, // 2E	SRA	(HL)	   
  { /* 0x2f */ _sra_,_x_,_a_},    // 2F	SRA	A	       
  { /* 0x30 */ _sll_,_x_,_b_},   // 30	SLL     B*		         
  { /* 0x31 */ _sll_,_x_,_c_},   // 31	SLL     C*		         
  { /* 0x32 */ _sll_,_x_,_d_},   // 32	SLL     D*		         
  { /* 0x33 */ _sll_,_x_,_e_},   // 33	SLL     E*		         
  { /* 0x34 */ _sll_,_x_,_h_},   // 34	SLL     H*		         
  { /* 0x35 */ _sll_,_x_,_l_},   // 35	SLL     L*		         
  { /* 0x36 */ _sll_,_x_,_IhlI_}, // 36	SLL     (HL)*		         
  { /* 0x37 */ _sll_,_x_,_a_},   // 37	SLL     A*		         
  { /* 0x38 */ _srl_,_x_,_b_},    // 38	SRL	B	       
  { /* 0x39 */ _srl_,_x_,_c_},    // 39	SRL	C	       
  { /* 0x3a */ _srl_,_x_,_d_},    // 3A	SRL	D	       
  { /* 0x3b */ _srl_,_x_,_e_},    // 3B	SRL	E	       
  { /* 0x3c */ _srl_,_x_,_h_},    // 3C	SRL	H	       
  { /* 0x3d */ _srl_,_x_,_l_},    // 3D	SRL	L	       
  { /* 0x3e */ _srl_,_x_,_IhlI_}, // 3E	SRL	(HL)	   
  { /* 0x3f */ _srl_,_x_,_a_},    // 3F	SRL	A	       
  { /* 0x40 */ _bit_,_0_,_b_},    // 40	BIT	0,B	     
  { /* 0x41 */ _bit_,_0_,_c_},    // 41	BIT	0,C	     
  { /* 0x42 */ _bit_,_0_,_d_},    // 42	BIT	0,D	     
  { /* 0x43 */ _bit_,_0_,_e_},    // 43	BIT	0,E	     
  { /* 0x44 */ _bit_,_0_,_h_},    // 44	BIT	0,H	     
  { /* 0x45 */ _bit_,_0_,_l_},    // 45	BIT	0,L	     
  { /* 0x46 */ _bit_,_0_,_IhlI_}, // 46	BIT	0,(HL)	 
  { /* 0x47 */ _bit_,_0_,_a_},    // 47	BIT	0,A	     
  { /* 0x48 */ _bit_,_1_,_b_},    // 48	BIT	1,B	     
  { /* 0x49 */ _bit_,_1_,_c_},    // 49	BIT	1,C	     
  { /* 0x4a */ _bit_,_1_,_d_},    // 4A	BIT	1,D	     
  { /* 0x4b */ _bit_,_1_,_e_},    // 4B	BIT	1,E	     
  { /* 0x4c */ _bit_,_1_,_h_},    // 4C	BIT	1,H	     
  { /* 0x4d */ _bit_,_1_,_l_},    // 4D	BIT	1,L	     
  { /* 0x4e */ _bit_,_1_,_IhlI_}, // 4E	BIT	1,(HL)	 
  { /* 0x4f */ _bit_,_1_,_a_},    // 4F	BIT	1,A	     
  { /* 0x50 */ _bit_,_2_,_b_},    // 50	BIT	2,B	     
  { /* 0x51 */ _bit_,_2_,_c_},    // 51	BIT	2,C	     
  { /* 0x52 */ _bit_,_2_,_d_},    // 52	BIT	2,D	     
  { /* 0x53 */ _bit_,_2_,_e_},    // 53	BIT	2,E	     
  { /* 0x54 */ _bit_,_2_,_h_},    // 54	BIT	2,H	     
  { /* 0x55 */ _bit_,_2_,_l_},    // 55	BIT	2,L	     
  { /* 0x56 */ _bit_,_2_,_IhlI_}, // 56	BIT	2,(HL)	 
  { /* 0x57 */ _bit_,_2_,_a_},    // 57	BIT	2,A	     
  { /* 0x58 */ _bit_,_3_,_b_},    // 58	BIT	3,B	     
  { /* 0x59 */ _bit_,_3_,_c_},    // 59	BIT	3,C	     
  { /* 0x5a */ _bit_,_3_,_d_},    // 5A	BIT	3,D	     
  { /* 0x5b */ _bit_,_3_,_e_},    // 5B	BIT	3,E	     
  { /* 0x5c */ _bit_,_3_,_h_},    // 5C	BIT	3,H	     
  { /* 0x5d */ _bit_,_3_,_l_},    // 5D	BIT	3,L	     
  { /* 0x5e */ _bit_,_3_,_IhlI_}, // 5E	BIT	3,(HL)	 
  { /* 0x5f */ _bit_,_3_,_a_},    // 5F	BIT	3,A	     
  { /* 0x60 */ _bit_,_4_,_b_},    // 60	BIT	4,B	     
  { /* 0x61 */ _bit_,_4_,_c_},    // 61	BIT	4,C	     
  { /* 0x62 */ _bit_,_4_,_d_},    // 62	BIT	4,D	     
  { /* 0x63 */ _bit_,_4_,_e_},    // 63	BIT	4,E	     
  { /* 0x64 */ _bit_,_4_,_h_},    // 64	BIT	4,H	     
  { /* 0x65 */ _bit_,_4_,_l_},    // 65	BIT	4,L	     
  { /* 0x66 */ _bit_,_4_,_IhlI_}, // 66	BIT	4,(HL)	 
  { /* 0x67 */ _bit_,_4_,_a_},    // 67	BIT	4,A	     
  { /* 0x68 */ _bit_,_5_,_b_},    // 68	BIT	5,B	     
  { /* 0x69 */ _bit_,_5_,_c_},    // 69	BIT	5,C	     
  { /* 0x6a */ _bit_,_5_,_d_},    // 6A	BIT	5,D	     
  { /* 0x6b */ _bit_,_5_,_e_},    // 6B	BIT	5,E	     
  { /* 0x6c */ _bit_,_5_,_h_},    // 6C	BIT	5,H	     
  { /* 0x6d */ _bit_,_5_,_l_},    // 6D	BIT	5,L	     
  { /* 0x6e */ _bit_,_5_,_IhlI_}, // 6E	BIT	5,(HL)	 
  { /* 0x6f */ _bit_,_5_,_a_},    // 6F	BIT	5,A	     
  { /* 0x70 */ _bit_,_6_,_b_},    // 70	BIT	6,B	     
  { /* 0x71 */ _bit_,_6_,_c_},    // 71	BIT	6,C	     
  { /* 0x72 */ _bit_,_6_,_d_},    // 72	BIT	6,D	     
  { /* 0x73 */ _bit_,_6_,_e_},    // 73	BIT	6,E	     
  { /* 0x74 */ _bit_,_6_,_h_},    // 74	BIT	6,H	     
  { /* 0x75 */ _bit_,_6_,_l_},    // 75	BIT	6,L	     
  { /* 0x76 */ _bit_,_6_,_IhlI_}, // 76	BIT	6,(HL)	 
  { /* 0x77 */ _bit_,_6_,_a_},    // 77	BIT	6,A	     
  { /* 0x78 */ _bit_,_7_,_b_},    // 78	BIT	7,B	     
  { /* 0x79 */ _bit_,_7_,_c_},    // 79	BIT	7,C	     
  { /* 0x7a */ _bit_,_7_,_d_},    // 7A	BIT	7,D	     
  { /* 0x7b */ _bit_,_7_,_e_},    // 7B	BIT	7,E	     
  { /* 0x7c */ _bit_,_7_,_h_},    // 7C	BIT	7,H	     
  { /* 0x7d */ _bit_,_7_,_l_},    // 7D	BIT	7,L	     
  { /* 0x7e */ _bit_,_7_,_IhlI_}, // 7E	BIT	7,(HL)	 
  { /* 0x7f */ _bit_,_7_,_a_},    // 7F	BIT	7,A	     
  { /* 0x80 */ _res_,_0_,_b_},    // 80	RES	0,B	     
  { /* 0x81 */ _res_,_0_,_c_},    // 81	RES	0,C	     
  { /* 0x82 */ _res_,_0_,_d_},    // 82	RES	0,D	     
  { /* 0x83 */ _res_,_0_,_e_},    // 83	RES	0,E	     
  { /* 0x84 */ _res_,_0_,_h_},    // 84	RES	0,H	     
  { /* 0x85 */ _res_,_0_,_l_},    // 85	RES	0,L	     
  { /* 0x86 */ _reshl_,_0_,_IhlI_}, // 86	RES	0,(HL)	 
  { /* 0x87 */ _res_,_0_,_a_},    // 87	RES	0,A	     
  { /* 0x88 */ _res_,_1_,_b_},    // 88	RES	1,B	     
  { /* 0x89 */ _res_,_1_,_c_},    // 89	RES	1,C	     
  { /* 0x8a */ _res_,_1_,_d_},    // 8A	RES	1,D	     
  { /* 0x8b */ _res_,_1_,_e_},    // 8B	RES	1,E	     
  { /* 0x8c */ _res_,_1_,_h_},    // 8C	RES	1,H	     
  { /* 0x8d */ _res_,_1_,_l_},    // 8D	RES	1,L	     
  { /* 0x8e */ _reshl_,_1_,_IhlI_}, // 8E	RES	1,(HL)	 
  { /* 0x8f */ _res_,_1_,_a_},    // 8F	RES	1,A	     
  { /* 0x90 */ _res_,_2_,_b_},    // 90	RES	2,B	     
  { /* 0x91 */ _res_,_2_,_c_},    // 91	RES	2,C	     
  { /* 0x92 */ _res_,_2_,_d_},    // 92	RES	2,D	     
  { /* 0x93 */ _res_,_2_,_e_},    // 93	RES	2,E	     
  { /* 0x94 */ _res_,_2_,_h_},    // 94	RES	2,H	     
  { /* 0x95 */ _res_,_2_,_l_},    // 95	RES	2,L	     
  { /* 0x96 */ _reshl_,_2_,_IhlI_}, // 96	RES	2,(HL)	 
  { /* 0x97 */ _res_,_2_,_a_},    // 97	RES	2,A	     
  { /* 0x98 */ _res_,_3_,_b_},    // 98	RES	3,B	     
  { /* 0x99 */ _res_,_3_,_c_},    // 99	RES	3,C	     
  { /* 0x9a */ _res_,_3_,_d_},    // 9A	RES	3,D	     
  { /* 0x9b */ _res_,_3_,_e_},    // 9B	RES	3,E	     
  { /* 0x9c */ _res_,_3_,_h_},    // 9C	RES	3,H	     
  { /* 0x9d */ _res_,_3_,_l_},    // 9D	RES	3,L	     
  { /* 0x9e */ _reshl_,_3_,_IhlI_}, // 9E	RES	3,(HL)	 
  { /* 0x9f */ _res_,_3_,_a_},    // 9F	RES	3,A	     
  { /* 0xa0 */ _res_,_4_,_b_},    // A0	RES	4,B	     
  { /* 0xa1 */ _res_,_4_,_c_},    // A1	RES	4,C	     
  { /* 0xa2 */ _res_,_4_,_d_},    // A2	RES	4,D	     
  { /* 0xa3 */ _res_,_4_,_e_},    // A3	RES	4,E	     
  { /* 0xa4 */ _res_,_4_,_h_},    // A4	RES	4,H	     
  { /* 0xa5 */ _res_,_4_,_l_},    // A5	RES	4,L	     
  { /* 0xa6 */ _reshl_,_4_,_IhlI_}, // A6	RES	4,(HL)	 
  { /* 0xa7 */ _res_,_4_,_a_},    // A7	RES	4,A	     
  { /* 0xa8 */ _res_,_5_,_b_},    // A8	RES	5,B	     
  { /* 0xa9 */ _res_,_5_,_c_},    // A9	RES	5,C	     
  { /* 0xaa */ _res_,_5_,_d_},    // AA	RES	5,D	     
  { /* 0xab */ _res_,_5_,_e_},    // AB	RES	5,E	     
  { /* 0xac */ _res_,_5_,_h_},    // AC	RES	5,H	     
  { /* 0xad */ _res_,_5_,_l_},    // AD	RES	5,L	     
  { /* 0xae */ _reshl_,_5_,_IhlI_}, // AE	RES	5,(HL)	 
  { /* 0xaf */ _res_,_5_,_a_},    // AF	RES	5,A	     
  { /* 0xb0 */ _res_,_6_,_b_},    // B0	RES	6,B	     
  { /* 0xb1 */ _res_,_6_,_c_},    // B1	RES	6,C	     
  { /* 0xb2 */ _res_,_6_,_d_},    // B2	RES	6,D	     
  { /* 0xb3 */ _res_,_6_,_e_},    // B3	RES	6,E	     
  { /* 0xb4 */ _res_,_6_,_h_},    // B4	RES	6,H	     
  { /* 0xb5 */ _res_,_6_,_l_},    // B5	RES	6,L	     
  { /* 0xb6 */ _reshl_,_6_,_IhlI_}, // B6	RES	6,(HL)	 
  { /* 0xb7 */ _res_,_6_,_a_},    // B7	RES	6,A	     
  { /* 0xb8 */ _res_,_7_,_b_},    // B8	RES	7,B	     
  { /* 0xb9 */ _res_,_7_,_c_},    // B9	RES	7,C	     
  { /* 0xba */ _res_,_7_,_d_},    // BA	RES	7,D	     
  { /* 0xbb */ _res_,_7_,_e_},    // BB	RES	7,E	     
  { /* 0xbc */ _res_,_7_,_h_},    // BC	RES	7,H	     
  { /* 0xbd */ _res_,_7_,_l_},    // BD	RES	7,L	     
  { /* 0xbe */ _reshl_,_7_,_IhlI_}, // BE	RES	7,(HL)	 
  { /* 0xbf */ _res_,_7_,_a_},    // BF	RES	7,A	     
  { /* 0xc0 */ _set_,_0_,_b_},    // C0	SET	0,B	     
  { /* 0xc1 */ _set_,_0_,_c_},    // C1	SET	0,C	     
  { /* 0xc2 */ _set_,_0_,_d_},    // C2	SET	0,D	     
  { /* 0xc3 */ _set_,_0_,_e_},    // C3	SET	0,E	     
  { /* 0xc4 */ _set_,_0_,_h_},    // C4	SET	0,H	     
  { /* 0xc5 */ _set_,_0_,_l_},    // C5	SET	0,L	     
  { /* 0xc6 */ _sethl_,_0_,_IhlI_}, // C6	SET	0,(HL)	 
  { /* 0xc7 */ _set_,_0_,_a_},    // C7	SET	0,A	     
  { /* 0xc8 */ _set_,_1_,_b_},    // C8	SET	1,B	     
  { /* 0xc9 */ _set_,_1_,_c_},    // C9	SET	1,C	     
  { /* 0xca */ _set_,_1_,_d_},    // CA	SET	1,D	     
  { /* 0xcb */ _set_,_1_,_e_},    // CB	SET	1,E	     
  { /* 0xcc */ _set_,_1_,_h_},    // CC	SET	1,H	     
  { /* 0xcd */ _set_,_1_,_l_},    // CD	SET	1,L	     
  { /* 0xce */ _sethl_,_1_,_IhlI_}, // CE	SET	1,(HL)	 
  { /* 0xcf */ _set_,_1_,_a_},    // CF	SET	1,A	     
  { /* 0xd0 */ _set_,_2_,_b_},    // D0	SET	2,B	     
  { /* 0xd1 */ _set_,_2_,_c_},    // D1	SET	2,C	     
  { /* 0xd2 */ _set_,_2_,_d_},    // D2	SET	2,D	     
  { /* 0xd3 */ _set_,_2_,_e_},    // D3	SET	2,E	     
  { /* 0xd4 */ _set_,_2_,_h_},    // D4	SET	2,H	     
  { /* 0xd5 */ _set_,_2_,_l_},    // D5	SET	2,L	     
  { /* 0xd6 */ _sethl_,_2_,_IhlI_}, // D6	SET	2,(HL)	 
  { /* 0xd7 */ _set_,_2_,_a_},    // D7	SET	2,A	     
  { /* 0xd8 */ _set_,_3_,_b_},    // D8	SET	3,B	     
  { /* 0xd9 */ _set_,_3_,_c_},    // D9	SET	3,C	     
  { /* 0xda */ _set_,_3_,_d_},    // DA	SET	3,D	     
  { /* 0xdb */ _set_,_3_,_e_},    // DB	SET	3,E	     
  { /* 0xdc */ _set_,_3_,_h_},    // DC	SET	3,H	     
  { /* 0xdd */ _set_,_3_,_l_},    // DD	SET	3,L	     
  { /* 0xde */ _sethl_,_3_,_IhlI_}, // DE	SET	3,(HL)	 
  { /* 0xdf */ _set_,_3_,_a_},    // DF	SET	3,A	     
  { /* 0xe0 */ _set_,_4_,_b_},    // E0	SET	4,B	     
  { /* 0xe1 */ _set_,_4_,_c_},    // E1	SET	4,C	     
  { /* 0xe2 */ _set_,_4_,_d_},    // E2	SET	4,D	     
  { /* 0xe3 */ _set_,_4_,_e_},    // E3	SET	4,E	     
  { /* 0xe4 */ _set_,_4_,_h_},    // E4	SET	4,H	     
  { /* 0xe5 */ _set_,_4_,_l_},    // E5	SET	4,L	     
  { /* 0xe6 */ _sethl_,_4_,_IhlI_}, // E6	SET	4,(HL)	 
  { /* 0xe7 */ _set_,_4_,_a_},    // E7	SET	4,A	     
  { /* 0xe8 */ _set_,_5_,_b_},    // E8	SET	5,B	     
  { /* 0xe9 */ _set_,_5_,_c_},    // E9	SET	5,C	     
  { /* 0xea */ _set_,_5_,_d_},    // EA	SET	5,D	     
  { /* 0xeb */ _set_,_5_,_e_},    // EB	SET	5,E	     
  { /* 0xec */ _set_,_5_,_h_},    // EC	SET	5,H	     
  { /* 0xed */ _set_,_5_,_l_},    // ED	SET	5,L	     
  { /* 0xee */ _sethl_,_5_,_IhlI_}, // EE	SET	5,(HL)	 
  { /* 0xef */ _set_,_5_,_a_},    // EF	SET	5,A	     
  { /* 0xf0 */ _set_,_6_,_b_},    // F0	SET	6,B	     
  { /* 0xf1 */ _set_,_6_,_c_},    // F1	SET	6,C	     
  { /* 0xf2 */ _set_,_6_,_d_},    // F2	SET	6,D	     
  { /* 0xf3 */ _set_,_6_,_e_},    // F3	SET	6,E	     
  { /* 0xf4 */ _set_,_6_,_h_},    // F4	SET	6,H	     
  { /* 0xf5 */ _set_,_6_,_l_},    // F5	SET	6,L	     
  { /* 0xf6 */ _sethl_,_6_,_IhlI_}, // F6	SET	6,(HL)	 
  { /* 0xf7 */ _set_,_6_,_a_},    // F7	SET	6,A	     
  { /* 0xf8 */ _set_,_7_,_b_},    // F8	SET	7,B	     
  { /* 0xf9 */ _set_,_7_,_c_},    // F9	SET	7,C	     
  { /* 0xfa */ _set_,_7_,_d_},    // FA	SET	7,D	     
  { /* 0xfb */ _set_,_7_,_e_},    // FB	SET	7,E	     
  { /* 0xfc */ _set_,_7_,_h_},    // FC	SET	7,H	     
  { /* 0xfd */ _set_,_7_,_l_},    // FD	SET	7,L	     
  { /* 0xfe */ _sethl_,_7_,_IhlI_}, // FE	SET	7,(HL)	 
  { /* 0xff */ _set_,_7_,_a_}    // FF	SET	7,A	     
};

uint8_t z80_asm_DD[][3] =   {                   // DD              
  { /* 0x00 */ _noni_,_x_,_x_},   // 00			         
  { /* 0x01 */ _noni_,_x_,_x_},   // 01			         
  { /* 0x02 */ _noni_,_x_,_x_},   // 02			         
  { /* 0x03 */ _noni_,_x_,_x_},   // 03			         
  { /* 0x04 */ _noni_,_x_,_x_},   // 04			         
  { /* 0x05 */ _noni_,_x_,_x_},   // 05			         
  { /* 0x06 */ _noni_,_x_,_x_},   // 06			         
  { /* 0x07 */ _noni_,_x_,_x_},   // 07			         
  { /* 0x08 */ _noni_,_x_,_x_},   // 08			         
  { /* 0x09 */ _add2_,_ix_,_bc_},   // 09	ADD	IX,BC	   
  { /* 0x0a */ _noni_,_x_,_x_},   // 0A			         
  { /* 0x0b */ _noni_,_x_,_x_},   // 0B			         
  { /* 0x0c */ _noni_,_x_,_x_},   // 0C			         
  { /* 0x0d */ _noni_,_x_,_x_},   // 0D			         
  { /* 0x0e */ _noni_,_x_,_x_},   // 0E			         
  { /* 0x0f */ _noni_,_x_,_x_},   // 0F			         
  { /* 0x10 */ _noni_,_x_,_x_},   // 10			         
  { /* 0x11 */ _noni_,_x_,_x_},   // 11			         
  { /* 0x12 */ _noni_,_x_,_x_},   // 12			         
  { /* 0x13 */ _noni_,_x_,_x_},   // 13			         
  { /* 0x14 */ _noni_,_x_,_x_},   // 14			         
  { /* 0x15 */ _noni_,_x_,_x_},   // 15			         
  { /* 0x16 */ _noni_,_x_,_x_},   // 16			         
  { /* 0x17 */ _noni_,_x_,_x_},   // 17			         
  { /* 0x18 */ _noni_,_x_,_x_},   // 18			         
  { /* 0x19 */ _add2_,_ix_,_de_},   // 19	ADD	IX,DE	   
  { /* 0x1a */ _noni_,_x_,_x_},   // 1A			         
  { /* 0x1b */ _noni_,_x_,_x_},   // 1B			         
  { /* 0x1c */ _noni_,_x_,_x_},   // 1C			         
  { /* 0x1d */ _noni_,_x_,_x_},   // 1D			         
  { /* 0x1e */ _noni_,_x_,_x_},   // 1E			         
  { /* 0x1f */ _noni_,_x_,_x_},   // 1F			         
  { /* 0x20 */ _noni_,_x_,_x_},   // 20			         
  { /* 0x21 */ _ld2_,_ix_,_nn_},    // 21	LD	IX,nn	   
  { /* 0x22 */ _ldw_,_IwwI_,_ix_}, // 22	LD	(nn),IX	 
  { /* 0x23 */ _inc2_,_x_,_ix_},    // 23	INC	IX	     
  { /* 0x24 */ _inc_,_x_,_ixh_},   // 24	INC	IXh*
  { /* 0x25 */ _dec_,_x_,_ixh_},   // 25	DEC	IXh*			         
  { /* 0x26 */ _ld_,_ixh_,_n_},   // 26		LD	IXh, n*
  { /* 0x27 */ _noni_,_x_,_x_},   // 27			         
  { /* 0x28 */ _noni_,_x_,_x_},   // 28			         
  { /* 0x29 */ _add2_,_ix_,_ix_},   // 29	ADD	IX,IX	   
  { /* 0x2a */ _ldw_,_ix_,_IwwI_},  // 2A	LD	IX,(nn)	 
  { /* 0x2b */ _dec2_,_x_,_ix_},    // 2B	DEC	IX	     
  { /* 0x2c */ _inc_,_x_,_ixl_},   // 2C	INC 	IXl*		         
  { /* 0x2d */ _dec_,_x_,_ixl_},   // 2D	DEC	IXl*		         
  { /* 0x2e */ _ld_,_ixl_,_n_},   // 2E		LD	IXl, n		         
  { /* 0x2f */ _noni_,_x_,_x_},   // 2F			         
  { /* 0x30 */ _noni_,_x_,_x_},   // 30			         
  { /* 0x31 */ _noni_,_x_,_x_},   // 31			         
  { /* 0x32 */ _noni_,_x_,_x_},   // 32			         
  { /* 0x33 */ _noni_,_x_,_x_},   // 33			         
  { /* 0x34 */ _inc_,_x_,_IixdI_},// 34	INC	(IX+d)	 
  { /* 0x35 */ _dec_,_x_,_IixdI_},// 35	DEC	(IX+d)	 
  { /* 0x36 */ _ld_,_IixdI_,_n_},   // 36	ld (ix+d) n		         
  { /* 0x37 */ _noni_,_x_,_x_},   // 37			         
  { /* 0x38 */ _noni_,_x_,_x_},   // 38			         
  { /* 0x39 */ _add2_,_ix_,_sp_},   // 39	ADD	IX,SP	   
  { /* 0x3a */ _noni_,_x_,_x_},   // 3A			         
  { /* 0x3b */ _noni_,_x_,_x_},   // 3B			         
  { /* 0x3c */ _noni_,_x_,_x_},   // 3C			         
  { /* 0x3d */ _noni_,_x_,_x_},   // 3D			         
  { /* 0x3e */ _noni_,_x_,_x_},   // 3E			         
  { /* 0x3f */ _noni_,_x_,_x_},   // 3F			         
  { /* 0x40 */ _noni_,_x_,_x_},   // 40			         
  { /* 0x41 */ _noni_,_x_,_x_},   // 41			         
  { /* 0x42 */ _noni_,_x_,_x_},   // 42			         
  { /* 0x43 */ _noni_,_x_,_x_},   // 43			         
  { /* 0x44 */ _ld_,_b_,_ixh_},   // 44		LD	B, IXh*			         
  { /* 0x45 */ _ld_,_b_,_ixl_},   // 45		LD	B, IXl*			         
  { /* 0x46 */ _ld_,_b_,_IixdI_}, // 46		LD	B,(IX+d) 
  { /* 0x47 */ _noni_,_x_,_x_},   // 47			         
  { /* 0x48 */ _noni_,_x_,_x_},   // 48			         
  { /* 0x49 */ _noni_,_x_,_x_},   // 49			         
  { /* 0x4a */ _noni_,_x_,_x_},   // 4A			         
  { /* 0x4b */ _noni_,_x_,_x_},   // 4B			         
  { /* 0x4c */ _ld_,_c_,_ixh_},   // 4C		LD	C, IXh*			         
  { /* 0x4d */ _ld_,_c_,_ixl_},   // 4D		LD	C, IXl*			         
  { /* 0x4e */ _ld_,_c_,_IixdI_}, // 4E	LD	C,(IX+d) 
  { /* 0x4f */ _noni_,_x_,_x_},   // 4F			         
  { /* 0x50 */ _noni_,_x_,_x_},   // 50			         
  { /* 0x51 */ _noni_,_x_,_x_},   // 51			         
  { /* 0x52 */ _noni_,_x_,_x_},   // 52			         
  { /* 0x53 */ _noni_,_x_,_x_},   // 53			         
  { /* 0x54 */ _ld_,_d_,_ixh_},   // 54		LD	D, IXh*			         
  { /* 0x55 */ _ld_,_d_,_ixl_},   // 55		LD	D, IXl*			         
  { /* 0x56 */ _ld_,_d_,_IixdI_}, // 56	LD	D,(IX+d) 
  { /* 0x57 */ _noni_,_x_,_x_},   // 57			         
  { /* 0x58 */ _noni_,_x_,_x_},   // 58			         
  { /* 0x59 */ _noni_,_x_,_x_},   // 59			         
  { /* 0x5a */ _noni_,_x_,_x_},   // 5A			         
  { /* 0x5b */ _noni_,_x_,_x_},   // 5B			         
  { /* 0x5c */ _ld_,_e_,_ixh_},   // 5C		LD	E, IXh*			         
  { /* 0x5d */ _ld_,_e_,_ixl_},   // 5D		LD	E, IXl*			         
  { /* 0x5e */ _ld_,_e_,_IixdI_}, // 5E	LD	E,(IX+d) 
  { /* 0x5f */ _noni_,_x_,_x_},   // 5F			         
  { /* 0x60 */ _ld_,_ixh_,_b_},   // 60		ld	ixh, b   *      
  { /* 0x61 */ _ld_,_ixh_,_c_},   // 61		ld	ixh, c  *       
  { /* 0x62 */ _ld_,_ixh_,_d_},   // 62		ld	ixh, d *       
  { /* 0x63 */ _ld_,_ixh_,_e_},   // 63		ld	ixh, e*         
  { /* 0x64 */ _ld_,_ixh_,_ixh_},   // 64	LD	ixh, IXh*			         
  { /* 0x65 */ _ld_,_ixh_,_ixl_},   // 65	LD	ixh, IXl*	         
  { /* 0x66 */ _ld_,_h_,_IixdI_}, // 66	LD	H,(IX+d) 
  { /* 0x67 */ _ld_,_ixh_,_a_},   // 67		LD ixh, a*			         
  { /* 0x68 */ _ld_,_ixl_,_b_},   // 68		ld ixl,b*			         
  { /* 0x69 */ _ld_,_ixl_,_c_},   // 69		ld ixl,c*			         
  { /* 0x6a */ _ld_,_ixl_,_d_},   // 6A		ld ixl,d*			         
  { /* 0x6b */ _ld_,_ixl_,_e_},   // 6B		id ixl,e*			         
  { /* 0x6c */ _ld_,_ixl_,_ixh_},   // 6C	ld ixl, ixh*		         
  { /* 0x6d */ _ld_,_ixl_,_ixl_},   // 6D	ld ixl, ixl*			         
  { /* 0x6e */ _ld_,_l_,_IixdI_}, // 6E	LD	L,(IX+d) 
  { /* 0x6f */ _ld_,_ixl_,_a_},   // 6F		ld ixl, a*			         
  { /* 0x70 */ _ld_,_IixdI_,_b_}, // 70	LD	(IX+d),B 
  { /* 0x71 */ _ld_,_IixdI_,_c_}, // 71	LD	(IX+d),C 
  { /* 0x72 */ _ld_,_IixdI_,_d_}, // 72	LD	(IX+d),D 
  { /* 0x73 */ _ld_,_IixdI_,_e_}, // 73	LD	(IX+d),E 
  { /* 0x74 */ _ld_,_IixdI_,_h_}, // 74	LD	(IX+d),H 
  { /* 0x75 */ _ld_,_IixdI_,_l_}, // 75	LD	(IX+d),L 
  { /* 0x76 */ _noni_,_x_,_x_},   // 76			         
  { /* 0x77 */ _ld_,_IixdI_,_a_}, // 77	LD	(IX+d),A 
  { /* 0x78 */ _noni_,_x_,_x_},   // 78			         
  { /* 0x79 */ _noni_,_x_,_x_},   // 79			         
  { /* 0x7a */ _noni_,_x_,_x_},   // 7A			         
  { /* 0x7b */ _noni_,_x_,_x_},   // 7B			         
  { /* 0x7c */ _ld_,_a_,_ixh_},   // 7C		ld a,ixh*
  { /* 0x7d */ _ld_,_a_,_ixl_},   // 7D		ld a,ixl*			         
  { /* 0x7e */ _ld_,_a_,_IixdI_}, // 7E	LD	A,(IX+d) 
  { /* 0x7f */ _noni_,_x_,_x_},   // 7F			         
  { /* 0x80 */ _noni_,_x_,_x_},   // 80			         
  { /* 0x81 */ _noni_,_x_,_x_},   // 81			         
  { /* 0x82 */ _noni_,_x_,_x_},   // 82			         
  { /* 0x83 */ _noni_,_x_,_x_},   // 83			         
  { /* 0x84 */ _add_,_a_,_ixh_},   // 84	add ixh*		         
  { /* 0x85 */ _add_,_a_,_ixl_},   // 85	add ixl*		         
  { /* 0x86 */ _add_,_a_,_IixdI_},// 86	ADD	A,(IX+d) 
  { /* 0x87 */ _noni_,_x_,_x_},   // 87			         
  { /* 0x88 */ _noni_,_x_,_x_},   // 88			         
  { /* 0x89 */ _noni_,_x_,_x_},   // 89			         
  { /* 0x8a */ _noni_,_x_,_x_},   // 8A			         
  { /* 0x8b */ _noni_,_x_,_x_},   // 8B			         
  { /* 0x8c */ _adc_,_a_,_ixh_},   // 8C	adc a,ixh*			         
  { /* 0x8d */ _adc_,_a_,_ixl_},   // 8D	adc a,ixl*		         
  { /* 0x8e */ _adc_,_a_,_IixdI_},// 8E	ADC	A,(IX+d) 
  { /* 0x8f */ _noni_,_x_,_x_},   // 8F			         
  { /* 0x90 */ _noni_,_x_,_x_},   // 90			         
  { /* 0x91 */ _noni_,_x_,_x_},   // 91			         
  { /* 0x92 */ _noni_,_x_,_x_},   // 92			         
  { /* 0x93 */ _noni_,_x_,_x_},   // 93			         
  { /* 0x94 */ _sub_,_a_,_ixh_},   // 94	sub ixh*			         
  { /* 0x95 */ _sub_,_a_,_ixl_},   // 95	sub ixl*		         
  { /* 0x96 */ _sub_,_a_,_IixdI_},// 96	SUB	(IX+d)	 
  { /* 0x97 */ _noni_,_x_,_x_},   // 97			         
  { /* 0x98 */ _noni_,_x_,_x_},   // 98			         
  { /* 0x99 */ _noni_,_x_,_x_},   // 99			         
  { /* 0x9a */ _noni_,_x_,_x_},   // 9A			         
  { /* 0x9b */ _noni_,_x_,_x_},   // 9B			         
  { /* 0x9c */ _sbc_,_a_,_ixh_},   // 9C	sbc ixh*			         
  { /* 0x9d */ _sbc_,_a_,_ixl_},   // 9D	sbc ixl*		         
  { /* 0x9e */ _sbc_,_a_,_IixdI_},// 9E	SBC	(IX+d)	 
  { /* 0x9f */ _noni_,_x_,_x_},   // 9F			         
  { /* 0xa0 */ _noni_,_x_,_x_},   // A0			         
  { /* 0xa1 */ _noni_,_x_,_x_},   // A1			         
  { /* 0xa2 */ _noni_,_x_,_x_},   // A2			         
  { /* 0xa3 */ _noni_,_x_,_x_},   // A3			         
  { /* 0xa4 */ _and_,_a_,_ixh_},   // A4	and ixh*		         
  { /* 0xa5 */ _and_,_a_,_ixl_},   // A5	and ixl*		         
  { /* 0xa6 */ _and_,_a_,_IixdI_},// A6	AND	(IX+d)	 
  { /* 0xa7 */ _noni_,_x_,_x_},   // A7			         
  { /* 0xa8 */ _noni_,_x_,_x_},   // A8			         
  { /* 0xa9 */ _noni_,_x_,_x_},   // A9			         
  { /* 0xaa */ _noni_,_x_,_x_},   // AA			         
  { /* 0xab */ _noni_,_x_,_x_},   // AB			         
  { /* 0xac */ _xor_,_a_,_ixh_},   // AC	xor ixh*		         
  { /* 0xad */ _xor_,_a_,_ixl_},   // AD	xor ixl		         
  { /* 0xae */ _xor_,_a_,_IixdI_},// AE	XOR	(IX+d)	 
  { /* 0xaf */ _noni_,_x_,_x_},   // AF			         
  { /* 0xb0 */ _noni_,_x_,_x_},   // B0			         
  { /* 0xb1 */ _noni_,_x_,_x_},   // B1			         
  { /* 0xb2 */ _noni_,_x_,_x_},   // B2			         
  { /* 0xb3 */ _noni_,_x_,_x_},   // B3			         
  { /* 0xb4 */ _or_,_a_,_ixh_},   // B4		or ixh*	         
  { /* 0xb5 */ _or_,_a_,_ixl_},   // B5		or ixl*	         
  { /* 0xb6 */ _or_,_a_,_IixdI_}, // B6	OR	(IX+d)	 
  { /* 0xb7 */ _noni_,_x_,_x_},   // B7			         
  { /* 0xb8 */ _noni_,_x_,_x_},   // B8			         
  { /* 0xb9 */ _noni_,_x_,_x_},   // B9			         
  { /* 0xba */ _noni_,_x_,_x_},   // BA			         
  { /* 0xbb */ _noni_,_x_,_x_},   // BB			         
  { /* 0xbc */ _cp_,_a_,_ixh_},   // BC		cp ixh*	         
  { /* 0xbd */ _cp_,_a_,_ixl_},   // BD		cp ixl*	         
  { /* 0xbe */ _cp_,_a_,_IixdI_}, // BE	CP	(IX+d)	 
  { /* 0xbf */ _noni_,_x_,_x_},   // BF			         
  { /* 0xc0 */ _noni_,_x_,_x_},   // C0			         
  { /* 0xc1 */ _noni_,_x_,_x_},   // C1			         
  { /* 0xc2 */ _noni_,_x_,_x_},   // C2			         
  { /* 0xc3 */ _noni_,_x_,_x_},   // C3			         
  { /* 0xc4 */ _noni_,_x_,_x_},   // C4			         
  { /* 0xc5 */ _noni_,_x_,_x_},   // C5			         
  { /* 0xc6 */ _noni_,_x_,_x_},   // C6			         
  { /* 0xc7 */ _noni_,_x_,_x_},   // C7			         
  { /* 0xc8 */ _noni_,_x_,_x_},   // C8			         
  { /* 0xc9 */ _noni_,_x_,_x_},   // C9			         
  { /* 0xca */ _noni_,_x_,_x_},   // CA			         
  { /* 0xcb */ _DDCB_,_x_,_x_},  // CB	#DDCB		     
  { /* 0xcc */ _noni_,_x_,_x_},   // CC			         
  { /* 0xcd */ _noni_,_x_,_x_},   // CD			         
  { /* 0xce */ _noni_,_x_,_x_},   // CE			         
  { /* 0xcf */ _noni_,_x_,_x_},   // CF			         
  { /* 0xd0 */ _noni_,_x_,_x_},   // D0			         
  { /* 0xd1 */ _noni_,_x_,_x_},   // D1			         
  { /* 0xd2 */ _noni_,_x_,_x_},   // D2			         
  { /* 0xd3 */ _noni_,_x_,_x_},   // D3			         
  { /* 0xd4 */ _noni_,_x_,_x_},   // D4			         
  { /* 0xd5 */ _noni_,_x_,_x_},   // D5			         
  { /* 0xd6 */ _noni_,_x_,_x_},   // D6			         
  { /* 0xd7 */ _noni_,_x_,_x_},   // D7			         
  { /* 0xd8 */ _noni_,_x_,_x_},   // D8			         
  { /* 0xd9 */ _noni_,_x_,_x_},   // D9			         
  { /* 0xda */ _noni_,_x_,_x_},   // DA			         
  { /* 0xdb */ _noni_,_x_,_x_},   // DB			         
  { /* 0xdc */ _noni_,_x_,_x_},   // DC			         
  { /* 0xdd */ _noni_,_x_,_x_},   // DD			         
  { /* 0xde */ _noni_,_x_,_x_},   // DE			         
  { /* 0xdf */ _noni_,_x_,_x_},   // DF			         
  { /* 0xe0 */ _noni_,_x_,_x_},   // E0			         
  { /* 0xe1 */ _pop_,_x_,_ix_},    // E1	POP	IX	     
  { /* 0xe2 */ _noni_,_x_,_x_},   // E2			         
  { /* 0xe3 */ _exs_,_IspI_,_ix_}, // E3	EX	(SP),IX	 
  { /* 0xe4 */ _noni_,_x_,_x_},   // E4			         
  { /* 0xe5 */ _push_,_x_,_ix_},   // E5	PUSH	IX	   
  { /* 0xe6 */ _noni_,_x_,_x_},   // E6			         
  { /* 0xe7 */ _noni_,_x_,_x_},   // E7			         
  { /* 0xe8 */ _noni_,_x_,_x_},   // E8			         
  { /* 0xe9 */ _jp_,_ANY_,_ix_},  // E9	JP	(IX)	   
  { /* 0xea */ _noni_,_x_,_x_},   // EA			         
  { /* 0xeb */ _noni_,_x_,_x_},   // EB			         
  { /* 0xec */ _noni_,_x_,_x_},   // EC			         
  { /* 0xed */ _noni_,_x_,_x_},   // ED			         
  { /* 0xee */ _noni_,_x_,_x_},   // EE			         
  { /* 0xef */ _noni_,_x_,_x_},   // EF			         
  { /* 0xf0 */ _noni_,_x_,_x_},   // F0			         
  { /* 0xf1 */ _noni_,_x_,_x_},   // F1			         
  { /* 0xf2 */ _noni_,_x_,_x_},   // F2			         
  { /* 0xf3 */ _noni_,_x_,_x_},   // F3			         
  { /* 0xf4 */ _noni_,_x_,_x_},   // F4			         
  { /* 0xf5 */ _noni_,_x_,_x_},   // F5			         
  { /* 0xf6 */ _noni_,_x_,_x_},   // F6			         
  { /* 0xf7 */ _noni_,_x_,_x_},   // F7			         
  { /* 0xf8 */ _noni_,_x_,_x_},   // F8			         
  { /* 0xf9 */ _ld2_,_sp_,_ix_},    // F9	LD	SP,IX	   
  { /* 0xfa */ _noni_,_x_,_x_},   // FA			         
  { /* 0xfb */ _noni_,_x_,_x_},   // FB			         
  { /* 0xfc */ _noni_,_x_,_x_},   // FC			         
  { /* 0xfd */ _noni_,_x_,_x_},   // FD			         
  { /* 0xfe */ _noni_,_x_,_x_},   // FE			         
  { /* 0xff */ _noni_,_x_,_x_}   // FF			         
};

uint8_t z80_asm_ED[][3] =   {                   // ED              
  { /* 0x00 */ _bios_,_x_,_x_},   // 00	BIOS CMD + ret
  { /* 0x01 */ _bios_,_x_,_x_},   // 01	
  { /* 0x02 */ _bios_,_x_,_x_},   // 02	
  { /* 0x03 */ _bios_,_x_,_x_},   // 03 
  { /* 0x04 */ _bios_,_x_,_x_},   // 04	
  { /* 0x05 */ _bios_,_x_,_x_},   // 05 
  { /* 0x06 */ _bios_,_x_,_x_},   // 06	
  { /* 0x07 */ _bios_,_x_,_x_},   // 07	
  { /* 0x08 */ _bios_,_x_,_x_},   // 08	
  { /* 0x09 */ _bios_,_x_,_x_},   // 09	
  { /* 0x0a */ _bios_,_x_,_x_},   // 0A	
  { /* 0x0b */ _bios_,_x_,_x_},   // 0B	
  { /* 0x0c */ _bios_,_x_,_x_},   // 0C	
  { /* 0x0d */ _bios_,_x_,_x_},   // 0D	
  { /* 0x0e */ _bios_,_x_,_x_},   // 0E	
  { /* 0x0f */ _bios_,_x_,_x_},   // 0F	
  { /* 0x10 */ _bios_,_x_,_x_},   // 10	
  { /* 0x11 */ _noni_,_x_,_x_},   // 11			         
  { /* 0x12 */ _noni_,_x_,_x_},   // 12			         
  { /* 0x13 */ _noni_,_x_,_x_},   // 13			         
  { /* 0x14 */ _noni_,_x_,_x_},   // 14			         
  { /* 0x15 */ _noni_,_x_,_x_},   // 15			         
  { /* 0x16 */ _noni_,_x_,_x_},   // 16			         
  { /* 0x17 */ _noni_,_x_,_x_},   // 17			         
  { /* 0x18 */ _noni_,_x_,_x_},   // 18			         
  { /* 0x19 */ _noni_,_x_,_x_},   // 19			         
  { /* 0x1a */ _noni_,_x_,_x_},   // 1A			         
  { /* 0x1b */ _noni_,_x_,_x_},   // 1B			         
  { /* 0x1c */ _noni_,_x_,_x_},   // 1C			         
  { /* 0x1d */ _noni_,_x_,_x_},   // 1D			         
  { /* 0x1e */ _noni_,_x_,_x_},   // 1E			         
  { /* 0x1f */ _noni_,_x_,_x_},   // 1F			         
  { /* 0x20 */ _noni_,_x_,_x_},   // 20			         
  { /* 0x21 */ _noni_,_x_,_x_},   // 21			         
  { /* 0x22 */ _noni_,_x_,_x_},   // 22			         
  { /* 0x23 */ _noni_,_x_,_x_},   // 23			         
  { /* 0x24 */ _noni_,_x_,_x_},   // 24			         
  { /* 0x25 */ _noni_,_x_,_x_},   // 25			         
  { /* 0x26 */ _noni_,_x_,_x_},   // 26			         
  { /* 0x27 */ _noni_,_x_,_x_},   // 27			         
  { /* 0x28 */ _noni_,_x_,_x_},   // 28			         
  { /* 0x29 */ _noni_,_x_,_x_},   // 29			         
  { /* 0x2a */ _noni_,_x_,_x_},   // 2A			         
  { /* 0x2b */ _noni_,_x_,_x_},   // 2B			         
  { /* 0x2c */ _noni_,_x_,_x_},   // 2C			         
  { /* 0x2d */ _noni_,_x_,_x_},   // 2D			         
  { /* 0x2e */ _noni_,_x_,_x_},   // 2E			         
  { /* 0x2f */ _noni_,_x_,_x_},   // 2F			         
  { /* 0x30 */ _noni_,_x_,_x_},   // 30			         
  { /* 0x31 */ _noni_,_x_,_x_},   // 31			         
  { /* 0x32 */ _noni_,_x_,_x_},   // 32			         
  { /* 0x33 */ _noni_,_x_,_x_},   // 33			         
  { /* 0x34 */ _noni_,_x_,_x_},   // 34			         
  { /* 0x35 */ _noni_,_x_,_x_},   // 35			         
  { /* 0x36 */ _noni_,_x_,_x_},   // 36			         
  { /* 0x37 */ _noni_,_x_,_x_},   // 37			         
  { /* 0x38 */ _noni_,_x_,_x_},   // 38			         
  { /* 0x39 */ _noni_,_x_,_x_},   // 39			         
  { /* 0x3a */ _noni_,_x_,_x_},   // 3A			         
  { /* 0x3b */ _noni_,_x_,_x_},   // 3B			         
  { /* 0x3c */ _noni_,_x_,_x_},   // 3C			         
  { /* 0x3d */ _noni_,_x_,_x_},   // 3D			         
  { /* 0x3e */ _noni_,_x_,_x_},   // 3E			         
  { /* 0x3f */ _noni_,_x_,_x_},   // 3F			         
  { /* 0x40 */ _in_,_b_,_IcI_},   // 40	IN	B,(C)	   
  { /* 0x41 */ _out_,_IcI_,_b_},  // 41	OUT	(C),B	   
  { /* 0x42 */ _sbc2_,_hl_,_bc_},   // 42	SBC	HL,BC	   
  { /* 0x43 */ _ldw_,_IwwI_,_bc_}, // 43	LD	(nn),BC	 
  { /* 0x44 */ _neg_,_x_,_a_},    // 44	NEG		       
  { /* 0x45 */ _retn_,_x_,_x_},   // 45	RETN		     
  { /* 0x46 */ _im_,_x_,_0_},     // 46	IM	0	       
  { /* 0x47 */ _ld_,_i_,_a_},     // 47	LD	I,A	     
  { /* 0x48 */ _in_,_c_,_IcI_},   // 48	IN	C,(C)	   
  { /* 0x49 */ _out_,_IcI_,_c_},  // 49	OUT	(C),C	   
  { /* 0x4a */ _adc2_,_hl_,_bc_},   // 4A	ADC	HL,BC	   
  { /* 0x4b */ _ldw_,_bc_,_IwwI_}, // 4B	LD	BC,(nn)	 
  { /* 0x4c */ _neg_,_x_,_a_},   // 4C			         
  { /* 0x4d */ _reti_,_x_,_x_},   // 4D	RETI		     
  { /* 0x4e */ _im_,_x_,_3_},   // 4E			  im 0/1       
  { /* 0x4f */ _ldra_,_r_,_a_},     // 4F	LD	R,A	     
  { /* 0x50 */ _in_,_d_,_IcI_},   // 50	IN	D,(C)	   
  { /* 0x51 */ _out_,_IcI_,_d_},  // 51	OUT	(C),D	   
  { /* 0x52 */ _sbc2_,_hl_,_de_},   // 52	SBC	HL,DE	   
  { /* 0x53 */ _ldw_,_IwwI_,_de_}, // 53	LD	(nn),DE	 
  { /* 0x54 */ _neg_,_x_,_a_},   // 54		neg*		         
  { /* 0x55 */ _retn_,_x_,_x_},   // 55		retn*			         
  { /* 0x56 */ _im_,_x_,_1_},     // 56	IM	1	       
  { /* 0x57 */ _lda_,_a_,_i_},     // 57	LD	A,I	     
  { /* 0x58 */ _in_,_e_,_IcI_},   // 58	IN	E,(C)	   
  { /* 0x59 */ _out_,_IcI_,_e_},  // 59	OUT	(C),E	   
  { /* 0x5a */ _adc2_,_hl_,_de_},   // 5A	ADC	HL,DE	   
  { /* 0x5b */ _ldw_,_de_,_IwwI_}, // 5B	LD	DE,(nn)	 
  { /* 0x5c */ _neg_,_x_,_a_},   // 5C		neg*	         
  { /* 0x5d */ _retn_,_x_,_x_},   // 5D		retn*			         
  { /* 0x5e */ _im_,_x_,_2_},     // 5E	IM	2	       
  { /* 0x5f */ _ldar_,_a_,_r_},     // 5F	LD	A,R	     
  { /* 0x60 */ _in_,_h_,_IcI_},   // 60	IN	H,(C)	   
  { /* 0x61 */ _out_,_IcI_,_h_},  // 61	OUT	(C),H	   
  { /* 0x62 */ _sbc2_,_hl_,_hl_},   // 62	SBC	HL,HL	   
  { /* 0x63 */ _ldw_,_IwwI_,_hl_},   // 63			         
  { /* 0x64 */ _neg_,_x_,_a_},   // 64			         
  { /* 0x65 */ _retn_,_x_,_x_},   // 65			         
  { /* 0x66 */ _im_,_x_,_0_},   // 66		im 0*	         
  { /* 0x67 */ _rrd_,_a_,_IhlI_},    // 67	RRD		       
  { /* 0x68 */ _in_,_l_,_IcI_},   // 68	IN	L,(C)	   
  { /* 0x69 */ _out_,_IcI_,_l_},  // 69	OUT	(C),L	   
  { /* 0x6a */ _adc2_,_hl_,_hl_},   // 6A	ADC	HL,HL	   
  { /* 0x6b */ _ldw_,_hl_,_IwwI_},   // 6B			         
  { /* 0x6c */ _neg_,_x_,_a_},   // 6C			         
  { /* 0x6d */ _retn_,_x_,_x_},   // 6D			         
  { /* 0x6e */ _im_,_x_,_3_},   // 6E			         
  { /* 0x6f */ _rld_,_a_,_IhlI_},    // 6F	RLD		       
  { /* 0x70 */ _noni_,_x_,_x_},   // 70			         
  { /* 0x71 */ _outc_,_IcI_,_0_},   // 71			         
  { /* 0x72 */ _sbc2_,_hl_,_sp_},   // 72	SBC	HL,SP	   
  { /* 0x73 */ _ldw_,_IwwI_,_sp_}, // 73	LD	(nn),SP	 
  { /* 0x74 */ _neg_,_x_,_a_},   // 74			         
  { /* 0x75 */ _retn_,_x_,_x_},   // 75			         
  { /* 0x76 */ _im_,_x_,_1_},   // 76			         
  { /* 0x77 */ _noni_,_x_,_x_},   // 77			         
  { /* 0x78 */ _in_,_a_,_IcI_},   // 78	IN	A,(C)	   
  { /* 0x79 */ _out_,_IcI_,_a_},  // 79	OUT	(C),A	   
  { /* 0x7a */ _adc2_,_hl_,_sp_},   // 7A	ADC	HL,SP	   
  { /* 0x7b */ _ldw_,_sp_,_IwwI_},  // 7B	LD	SP,(nn)	 
  { /* 0x7c */ _neg_,_x_,_a_},   // 7C			         
  { /* 0x7d */ _retn_,_x_,_x_},   // 7D			         
  { /* 0x7e */ _im_,_x_,_2_},   // 7E			         
  { /* 0x7f */ _noni_,_x_,_x_},   // 7F			         
  { /* 0x80 */ _noni_,_x_,_x_},   // 80	
  { /* 0x81 */ _noni_,_x_,_x_},   // 81			         
  { /* 0x82 */ _noni_,_x_,_x_},   // 82			         
  { /* 0x83 */ _noni_,_x_,_x_},   // 83			         
  { /* 0x84 */ _noni_,_x_,_x_},   // 84			         
  { /* 0x85 */ _noni_,_x_,_x_},   // 85			         
  { /* 0x86 */ _noni_,_x_,_x_},   // 86			         
  { /* 0x87 */ _noni_,_x_,_x_},   // 87			         
  { /* 0x88 */ _noni_,_x_,_x_},   // 88			         
  { /* 0x89 */ _noni_,_x_,_x_},   // 89			         
  { /* 0x8a */ _noni_,_x_,_x_},   // 8A			         
  { /* 0x8b */ _noni_,_x_,_x_},   // 8B			         
  { /* 0x8c */ _noni_,_x_,_x_},   // 8C			         
  { /* 0x8d */ _noni_,_x_,_x_},   // 8D			         
  { /* 0x8e */ _noni_,_x_,_x_},   // 8E			         
  { /* 0x8f */ _noni_,_x_,_x_},   // 8F			         
  { /* 0x90 */ _noni_,_x_,_x_},   // 90			         
  { /* 0x91 */ _noni_,_x_,_x_},   // 91			         
  { /* 0x92 */ _noni_,_x_,_x_},   // 92			         
  { /* 0x93 */ _noni_,_x_,_x_},   // 93			         
  { /* 0x94 */ _noni_,_x_,_x_},   // 94			         
  { /* 0x95 */ _noni_,_x_,_x_},   // 95			         
  { /* 0x96 */ _noni_,_x_,_x_},   // 96			         
  { /* 0x97 */ _noni_,_x_,_x_},   // 97			         
  { /* 0x98 */ _noni_,_x_,_x_},   // 98			         
  { /* 0x99 */ _noni_,_x_,_x_},   // 99			         
  { /* 0x9a */ _noni_,_x_,_x_},   // 9A			         
  { /* 0x9b */ _noni_,_x_,_x_},   // 9B			         
  { /* 0x9c */ _noni_,_x_,_x_},   // 9C			         
  { /* 0x9d */ _noni_,_x_,_x_},   // 9D			         
  { /* 0x9e */ _noni_,_x_,_x_},   // 9E			         
  { /* 0x9f */ _noni_,_x_,_x_},   // 9F			         
  { /* 0xa0 */ _ldi_,_x_,_x_},    // A0	LDI		       
  { /* 0xa1 */ _cpi_,_x_,_x_},    // A1	CPI		       
  { /* 0xa2 */ _ini_,_x_,_x_},    // A2	INI		       
  { /* 0xa3 */ _outi_,_x_,_x_},   // A3	OUTI		     
  { /* 0xa4 */ _noni_,_x_,_x_},   // A4			         
  { /* 0xa5 */ _noni_,_x_,_x_},   // A5			         
  { /* 0xa6 */ _noni_,_x_,_x_},   // A6			         
  { /* 0xa7 */ _noni_,_x_,_x_},   // A7			         
  { /* 0xa8 */ _ldd_,_x_,_x_},    // A8	LDD		       
  { /* 0xa9 */ _cpd_,_x_,_x_},    // A9	CPD		       
  { /* 0xaa */ _ind_,_x_,_x_},    // AA	IND		       
  { /* 0xab */ _outd_,_x_,_x_},   // AB	OUTD		     
  { /* 0xac */ _noni_,_x_,_x_},   // AC			         
  { /* 0xad */ _noni_,_x_,_x_},   // AD			         
  { /* 0xae */ _noni_,_x_,_x_},   // AE			         
  { /* 0xaf */ _noni_,_x_,_x_},   // AF			         
  { /* 0xb0 */ _ldir_,_x_,_x_},   // B0	LDIR		     
  { /* 0xb1 */ _cpir_,_x_,_x_},   // B1	CPIR		     
  { /* 0xb2 */ _inir_,_x_,_x_},   // B2	INIR		     
  { /* 0xb3 */ _otir_,_x_,_x_},   // B3	OTIR		     
  { /* 0xb4 */ _noni_,_x_,_x_},   // B4			         
  { /* 0xb5 */ _noni_,_x_,_x_},   // B5			         
  { /* 0xb6 */ _noni_,_x_,_x_},   // B6			         
  { /* 0xb7 */ _noni_,_x_,_x_},   // B7			         
  { /* 0xb8 */ _lddr_,_x_,_x_},   // B8	LDDR		     
  { /* 0xb9 */ _cpdr_,_x_,_x_},   // B9	CPDR		     
  { /* 0xba */ _indr_,_x_,_x_},   // BA	INDR		     
  { /* 0xbb */ _otdr_,_x_,_x_},   // BB	OTDR		     
  { /* 0xbc */ _noni_,_x_,_x_},   // BC			         
  { /* 0xbd */ _noni_,_x_,_x_},   // BD			         
  { /* 0xbe */ _noni_,_x_,_x_},   // BE			         
  { /* 0xbf */ _noni_,_x_,_x_},   // BF			         
  { /* 0xc0 */ _noni_,_x_,_x_},   // C0		// BDOS here !!!	         
  { /* 0xc1 */ _noni_,_x_,_x_},   // C1			         
  { /* 0xc2 */ _noni_,_x_,_x_},   // C2			         
  { /* 0xc3 */ _noni_,_x_,_x_},   // C3			         
  { /* 0xc4 */ _noni_,_x_,_x_},   // C4			         
  { /* 0xc5 */ _noni_,_x_,_x_},   // C5			         
  { /* 0xc6 */ _noni_,_x_,_x_},   // C6			         
  { /* 0xc7 */ _noni_,_x_,_x_},   // C7			         
  { /* 0xc8 */ _noni_,_x_,_x_},   // C8			         
  { /* 0xc9 */ _noni_,_x_,_x_},   // C9			         
  { /* 0xca */ _noni_,_x_,_x_},   // CA			         
  { /* 0xcb */ _noni_,_x_,_x_},   // CB			         
  { /* 0xcc */ _noni_,_x_,_x_},   // CC			         
  { /* 0xcd */ _noni_,_x_,_x_},   // CD			         
  { /* 0xce */ _noni_,_x_,_x_},   // CE			         
  { /* 0xcf */ _noni_,_x_,_x_},   // CF			         
  { /* 0xd0 */ _noni_,_x_,_x_},   // D0			         
  { /* 0xd1 */ _noni_,_x_,_x_},   // D1			         
  { /* 0xd2 */ _noni_,_x_,_x_},   // D2			         
  { /* 0xd3 */ _noni_,_x_,_x_},   // D3			         
  { /* 0xd4 */ _noni_,_x_,_x_},   // D4			         
  { /* 0xd5 */ _noni_,_x_,_x_},   // D5			         
  { /* 0xd6 */ _noni_,_x_,_x_},   // D6			         
  { /* 0xd7 */ _noni_,_x_,_x_},   // D7			         
  { /* 0xd8 */ _noni_,_x_,_x_},   // D8			         
  { /* 0xd9 */ _noni_,_x_,_x_},   // D9			         
  { /* 0xda */ _noni_,_x_,_x_},   // DA			         
  { /* 0xdb */ _noni_,_x_,_x_},   // DB			         
  { /* 0xdc */ _noni_,_x_,_x_},   // DC			         
  { /* 0xdd */ _noni_,_x_,_x_},   // DD			         
  { /* 0xde */ _noni_,_x_,_x_},   // DE			         
  { /* 0xdf */ _noni_,_x_,_x_},   // DF			         
  { /* 0xe0 */ _noni_,_x_,_x_},   // E0			         
  { /* 0xe1 */ _noni_,_x_,_x_},   // E1			         
  { /* 0xe2 */ _noni_,_x_,_x_},   // E2			         
  { /* 0xe3 */ _noni_,_x_,_x_},   // E3			         
  { /* 0xe4 */ _noni_,_x_,_x_},   // E4			         
  { /* 0xe5 */ _noni_,_x_,_x_},   // E5			         
  { /* 0xe6 */ _noni_,_x_,_x_},   // E6			         
  { /* 0xe7 */ _noni_,_x_,_x_},   // E7			         
  { /* 0xe8 */ _noni_,_x_,_x_},   // E8			         
  { /* 0xe9 */ _noni_,_x_,_x_},   // E9			         
  { /* 0xea */ _noni_,_x_,_x_},   // EA			         
  { /* 0xeb */ _noni_,_x_,_x_},   // EB			         
  { /* 0xec */ _noni_,_x_,_x_},   // EC			         
  { /* 0xed */ _noni_,_x_,_x_},   // ED			         
  { /* 0xee */ _noni_,_x_,_x_},   // EE			         
  { /* 0xef */ _noni_,_x_,_x_},   // EF			         
  { /* 0xf0 */ _noni_,_x_,_x_},   // F0			         
  { /* 0xf1 */ _noni_,_x_,_x_},   // F1			         
  { /* 0xf2 */ _noni_,_x_,_x_},   // F2			         
  { /* 0xf3 */ _noni_,_x_,_x_},   // F3			         
  { /* 0xf4 */ _noni_,_x_,_x_},   // F4			         
  { /* 0xf5 */ _noni_,_x_,_x_},   // F5			         
  { /* 0xf6 */ _noni_,_x_,_x_},   // F6			         
  { /* 0xf7 */ _noni_,_x_,_x_},   // F7			         
  { /* 0xf8 */ _noni_,_x_,_x_},   // F8			         
  { /* 0xf9 */ _noni_,_x_,_x_},   // F9			         
  { /* 0xfa */ _noni_,_x_,_x_},   // FA			         
  { /* 0xfb */ _noni_,_x_,_x_},   // FB			         
  { /* 0xfc */ _noni_,_x_,_x_},   // FC			         
  { /* 0xfd */ _noni_,_x_,_x_},   // FD			         
  { /* 0xfe */ _noni_,_x_,_x_},   // FE			         
  { /* 0xff */ _noni_,_x_,_x_}   // FF			         
};

uint8_t z80_asm_FD[][3] =   {                   // FD              
  { /* 0x00 */ _noni_,_x_,_x_},   // 00			         
  { /* 0x01 */ _noni_,_x_,_x_},   // 01			         
  { /* 0x02 */ _noni_,_x_,_x_},   // 02			         
  { /* 0x03 */ _noni_,_x_,_x_},   // 03			         
  { /* 0x04 */ _noni_,_x_,_x_},   // 04			         
  { /* 0x05 */ _noni_,_x_,_x_},   // 05			         
  { /* 0x06 */ _noni_,_x_,_x_},   // 06			         
  { /* 0x07 */ _noni_,_x_,_x_},   // 07			         
  { /* 0x08 */ _noni_,_x_,_x_},   // 08			         
  { /* 0x09 */ _add2_,_iy_,_bc_},   // 09	ADD	IY,BC	   
  { /* 0x0a */ _noni_,_x_,_x_},   // 0A			         
  { /* 0x0b */ _noni_,_x_,_x_},   // 0B			         
  { /* 0x0c */ _noni_,_x_,_x_},   // 0C			         
  { /* 0x0d */ _noni_,_x_,_x_},   // 0D			         
  { /* 0x0e */ _noni_,_x_,_x_},   // 0E			         
  { /* 0x0f */ _noni_,_x_,_x_},   // 0F			         
  { /* 0x10 */ _noni_,_x_,_x_},   // 10			         
  { /* 0x11 */ _noni_,_x_,_x_},   // 11			         
  { /* 0x12 */ _noni_,_x_,_x_},   // 12			         
  { /* 0x13 */ _noni_,_x_,_x_},   // 13			         
  { /* 0x14 */ _noni_,_x_,_x_},   // 14			         
  { /* 0x15 */ _noni_,_x_,_x_},   // 15			         
  { /* 0x16 */ _noni_,_x_,_x_},   // 16			         
  { /* 0x17 */ _noni_,_x_,_x_},   // 17			         
  { /* 0x18 */ _noni_,_x_,_x_},   // 18			         
  { /* 0x19 */ _add2_,_iy_,_de_},   // 19	ADD	IY,DE	   
  { /* 0x1a */ _noni_,_x_,_x_},   // 1A			         
  { /* 0x1b */ _noni_,_x_,_x_},   // 1B			         
  { /* 0x1c */ _noni_,_x_,_x_},   // 1C			         
  { /* 0x1d */ _noni_,_x_,_x_},   // 1D			         
  { /* 0x1e */ _noni_,_x_,_x_},   // 1E			         
  { /* 0x1f */ _noni_,_x_,_x_},   // 1F			         
  { /* 0x20 */ _noni_,_x_,_x_},   // 20			         
  { /* 0x21 */ _ld2_,_iy_,_nn_},    // 21	LD	IY,nn	   
  { /* 0x22 */ _ldw_,_IwwI_,_iy_}, // 22	LD	(nn),IY	 
  { /* 0x23 */ _inc2_,_x_,_iy_},    // 23	INC	IY	     
  { /* 0x24 */ _inc_,_x_,_iyh_},   // 24	inc iyh*
  { /* 0x25 */ _dec_,_x_,_iyl_},   // 25	dec iyh*		         
  { /* 0x26 */ _ld_,_iyh_,_n_},   // 26		ld iyh,n*			         
  { /* 0x27 */ _noni_,_x_,_x_},   // 27			         
  { /* 0x28 */ _noni_,_x_,_x_},   // 28			         
  { /* 0x29 */ _add2_,_iy_,_iy_},   // 29	ADD	IY,IY	   
  { /* 0x2a */ _ldw_,_iy_,_IwwI_},  // 2A	LD	IY,(nn)	 
  { /* 0x2b */ _dec2_,_x_,_iy_},    // 2B	DEC	IY	     
  { /* 0x2c */ _inc_,_x_,_iyl_},   // 2C	inc iyl*		         
  { /* 0x2d */ _dec_,_x_,_iyl_},   // 2D	dec iyl*		         
  { /* 0x2e */ _ld_,_iyl_,_n_},   // 2E		*			         
  { /* 0x2f */ _noni_,_x_,_x_},   // 2F			         
  { /* 0x30 */ _noni_,_x_,_x_},   // 30			         
  { /* 0x31 */ _noni_,_x_,_x_},   // 31			         
  { /* 0x32 */ _noni_,_x_,_x_},   // 32			         
  { /* 0x33 */ _noni_,_x_,_x_},   // 33			         
  { /* 0x34 */ _inc_,_x_,_IiydI_},// 34	INC	(IY+d)	 
  { /* 0x35 */ _dec_,_x_,_IiydI_},// 35	DEC	(IY+d)	 
  { /* 0x36 */ _ld_,_IiydI_,_n_},   // 36			         
  { /* 0x37 */ _noni_,_x_,_x_},   // 37			         
  { /* 0x38 */ _noni_,_x_,_x_},   // 38			         
  { /* 0x39 */ _add2_,_iy_,_sp_},   // 39	ADD	IY,SP	   
  { /* 0x3a */ _noni_,_x_,_x_},   // 3A			         
  { /* 0x3b */ _noni_,_x_,_x_},   // 3B			         
  { /* 0x3c */ _noni_,_x_,_x_},   // 3C			         
  { /* 0x3d */ _noni_,_x_,_x_},   // 3D			         
  { /* 0x3e */ _noni_,_x_,_x_},   // 3E			         
  { /* 0x3f */ _noni_,_x_,_x_},   // 3F			         
  { /* 0x40 */ _noni_,_x_,_x_},   // 40			         
  { /* 0x41 */ _noni_,_x_,_x_},   // 41			         
  { /* 0x42 */ _noni_,_x_,_x_},   // 42			         
  { /* 0x43 */ _noni_,_x_,_x_},   // 43			         
  { /* 0x44 */ _ld_,_b_,_iyh_},   // 44		ld b, iyh*			         
  { /* 0x45 */ _ld_,_b_,_iyh_},   // 45		ld b, iyl*	         
  { /* 0x46 */ _ld_,_b_,_IiydI_}, // 46	LD	B,(IY+d) 
  { /* 0x47 */ _noni_,_x_,_x_},   // 47			         
  { /* 0x48 */ _noni_,_x_,_x_},   // 48			         
  { /* 0x49 */ _noni_,_x_,_x_},   // 49			         
  { /* 0x4a */ _noni_,_x_,_x_},   // 4A			         
  { /* 0x4b */ _noni_,_x_,_x_},   // 4B			         
  { /* 0x4c */ _ld_,_c_,_iyh_},   // 4C		ld c, iyh*	         
  { /* 0x4d */ _ld_,_c_,_iyl_},   // 4D		ld c, iyl*	         
  { /* 0x4e */ _ld_,_c_,_IiydI_}, // 4E	LD	C,(IY+d) 
  { /* 0x4f */ _noni_,_x_,_x_},   // 4F			         
  { /* 0x50 */ _noni_,_x_,_x_},   // 50			         
  { /* 0x51 */ _noni_,_x_,_x_},   // 51			         
  { /* 0x52 */ _noni_,_x_,_x_},   // 52			         
  { /* 0x53 */ _noni_,_x_,_x_},   // 53			         
  { /* 0x54 */ _ld_,_d_,_iyh_},   // 54		ld d, iyh*	         
  { /* 0x55 */ _ld_,_d_,_iyl_},   // 55		ld d, iyl	         
  { /* 0x56 */ _ld_,_d_,_IiydI_}, // 56	LD	D,(IY+d) 
  { /* 0x57 */ _noni_,_x_,_x_},   // 57			         
  { /* 0x58 */ _noni_,_x_,_x_},   // 58			         
  { /* 0x59 */ _noni_,_x_,_x_},   // 59			         
  { /* 0x5a */ _noni_,_x_,_x_},   // 5A			         
  { /* 0x5b */ _noni_,_x_,_x_},   // 5B			         
  { /* 0x5c */ _ld_,_e_,_iyh_},   // 5C		ld e, iyh*	         
  { /* 0x5d */ _ld_,_e_,_iyl_},   // 5D		ld e, iyl*	         
  { /* 0x5e */ _ld_,_e_,_IiydI_}, // 5E	LD	E,(IY+d) 
  { /* 0x5f */ _noni_,_x_,_x_},   // 5F			         
  { /* 0x60 */ _ld_,_iyh_,_b_},   // 60		*	         
  { /* 0x61 */ _ld_,_iyh_,_c_},   // 61		*	         
  { /* 0x62 */ _ld_,_iyh_,_d_},   // 62		*	         
  { /* 0x63 */ _ld_,_iyh_,_e_},   // 63		*	         
  { /* 0x64 */ _ld_,_iyh_,_iyh_},   // 64	*		         
  { /* 0x65 */ _ld_,_iyh_,_iyl_},   // 65	ld lyh, iyl*		         
  { /* 0x66 */ _ld_,_h_,_IiydI_}, // 66	LD	H,(IY+d) 
  { /* 0x67 */ _ld_,_iyh_,_a_},   // 67		*	         
  { /* 0x68 */ _ld_,_iyl_,_b_},   // 68		*	         
  { /* 0x69 */ _ld_,_iyl_,_c_},   // 69		*	         
  { /* 0x6a */ _ld_,_iyl_,_d_},   // 6A		*	         
  { /* 0x6b */ _ld_,_iyl_,_e_},   // 6B		*	         
  { /* 0x6c */ _ld_,_iyl_,_iyh_},   // 6C	*		         
  { /* 0x6d */ _ld_,_iyl_,_iyl_},   // 6D	*		         
  { /* 0x6e */ _ld_,_l_,_IiydI_}, // 6E	LD	L,(IY+d) 
  { /* 0x6f */ _ld_,_iyl_,_a_},   // 6F			         
  { /* 0x70 */ _ld_,_IiydI_,_b_}, // 70	LD	(IY+d),B 
  { /* 0x71 */ _ld_,_IiydI_,_c_}, // 71	LD	(IY+d),C 
  { /* 0x72 */ _ld_,_IiydI_,_d_}, // 72	LD	(IY+d),D 
  { /* 0x73 */ _ld_,_IiydI_,_e_}, // 73	LD	(IY+d),E 
  { /* 0x74 */ _ld_,_IiydI_,_h_}, // 74	LD	(IY+d),H 
  { /* 0x75 */ _ld_,_IiydI_,_l_}, // 75	LD	(IY+d),L 
  { /* 0x76 */ _noni_,_x_,_x_},   // 76			         
  { /* 0x77 */ _ld_,_IiydI_,_a_}, // 77	LD	(IY+d),A 
  { /* 0x78 */ _noni_,_x_,_x_},   // 78			         
  { /* 0x79 */ _noni_,_x_,_x_},   // 79			         
  { /* 0x7a */ _noni_,_x_,_x_},   // 7A			         
  { /* 0x7b */ _noni_,_x_,_x_},   // 7B			         
  { /* 0x7c */ _ld_,_a_,_iyh_},   // 7C		*			         
  { /* 0x7d */ _ld_,_a_,_iyl_},   // 7D		*	         
  { /* 0x7e */ _ld_,_a_,_IiydI_}, // 7E	LD	A,(IY+d) 
  { /* 0x7f */ _noni_,_x_,_x_},   // 7F			         
  { /* 0x80 */ _noni_,_x_,_x_},   // 80			         
  { /* 0x81 */ _noni_,_x_,_x_},   // 81			         
  { /* 0x82 */ _noni_,_x_,_x_},   // 82			         
  { /* 0x83 */ _noni_,_x_,_x_},   // 83			         
  { /* 0x84 */ _add_,_a_,_iyh_},   // 84	*		         
  { /* 0x85 */ _add_,_a_,_iyl_},   // 85	*		         
  { /* 0x86 */ _add_,_a_,_IiydI_},// 86	ADD	A,(IY+d) 
  { /* 0x87 */ _noni_,_x_,_x_},   // 87			         
  { /* 0x88 */ _noni_,_x_,_x_},   // 88			         
  { /* 0x89 */ _noni_,_x_,_x_},   // 89			         
  { /* 0x8a */ _noni_,_x_,_x_},   // 8A			         
  { /* 0x8b */ _noni_,_x_,_x_},   // 8B			         
  { /* 0x8c */ _adc_,_a_,_iyh_},   // 8C	*		         
  { /* 0x8d */ _adc_,_a_,_iyl_},   // 8D	*		         
  { /* 0x8e */ _adc_,_a_,_IiydI_},// 8E	ADC	A,(IY+d) 
  { /* 0x8f */ _noni_,_x_,_x_},   // 8F			         
  { /* 0x90 */ _noni_,_x_,_x_},   // 90			         
  { /* 0x91 */ _noni_,_x_,_x_},   // 91			         
  { /* 0x92 */ _noni_,_x_,_x_},   // 92			         
  { /* 0x93 */ _noni_,_x_,_x_},   // 93			         
  { /* 0x94 */ _sub_,_a_,_iyh_},   // 94	*			         
  { /* 0x95 */ _sub_,_a_,_iyl_},   // 95	*		         
  { /* 0x96 */ _sub_,_a_,_IiydI_},// 96	SUB	(IY+d)	 
  { /* 0x97 */ _noni_,_x_,_x_},   // 97			         
  { /* 0x98 */ _noni_,_x_,_x_},   // 98			         
  { /* 0x99 */ _noni_,_x_,_x_},   // 99			         
  { /* 0x9a */ _noni_,_x_,_x_},   // 9A			         
  { /* 0x9b */ _noni_,_x_,_x_},   // 9B			         
  { /* 0x9c */ _sbc_,_a_,_iyh_},   // 9C	*		         
  { /* 0x9d */ _sbc_,_a_,_iyl_},   // 9D	*		         
  { /* 0x9e */ _sbc_,_a_,_IiydI_},// 9E	SBC	(IY+d)	 
  { /* 0x9f */ _noni_,_x_,_x_},   // 9F			         
  { /* 0xa0 */ _noni_,_x_,_x_},   // A0			         
  { /* 0xa1 */ _noni_,_x_,_x_},   // A1			         
  { /* 0xa2 */ _noni_,_x_,_x_},   // A2			         
  { /* 0xa3 */ _noni_,_x_,_x_},   // A3			         
  { /* 0xa4 */ _and_,_a_,_iyh_},   // A4	*		         
  { /* 0xa5 */ _and_,_a_,_iyl_},   // A5	*		         
  { /* 0xa6 */ _and_,_a_,_IiydI_},// A6	AND	(IY+d)	 
  { /* 0xa7 */ _noni_,_x_,_x_},   // A7			         
  { /* 0xa8 */ _noni_,_x_,_x_},   // A8			         
  { /* 0xa9 */ _noni_,_x_,_x_},   // A9			         
  { /* 0xaa */ _noni_,_x_,_x_},   // AA			         
  { /* 0xab */ _noni_,_x_,_x_},   // AB			         
  { /* 0xac */ _xor_,_a_,_iyh_},   // AC	*		         
  { /* 0xad */ _xor_,_a_,_iyl_},   // AD	*		         
  { /* 0xae */ _xor_,_a_,_IiydI_},// AE	XOR	(IY+d)	 
  { /* 0xaf */ _noni_,_x_,_x_},   // AF			         
  { /* 0xb0 */ _noni_,_x_,_x_},   // B0			         
  { /* 0xb1 */ _noni_,_x_,_x_},   // B1			         
  { /* 0xb2 */ _noni_,_x_,_x_},   // B2			         
  { /* 0xb3 */ _noni_,_x_,_x_},   // B3			         
  { /* 0xb4 */ _or_,_a_,_iyh_},   // B4		*	         
  { /* 0xb5 */ _or_,_a_,_iyl_},   // B5		*	         
  { /* 0xb6 */ _or_,_a_,_IiydI_}, // B6	OR	(IY+d)	 
  { /* 0xb7 */ _noni_,_x_,_x_},   // B7			         
  { /* 0xb8 */ _noni_,_x_,_x_},   // B8			         
  { /* 0xb9 */ _noni_,_x_,_x_},   // B9			         
  { /* 0xba */ _noni_,_x_,_x_},   // BA			         
  { /* 0xbb */ _noni_,_x_,_x_},   // BB			         
  { /* 0xbc */ _cp_,_a_,_iyh_},   // BC		*	         
  { /* 0xbd */ _cp_,_a_,_iyl_},   // BD		*	         
  { /* 0xbe */ _cp_,_a_,_IiydI_}, // BE	CP	(IY+d)	 
  { /* 0xbf */ _noni_,_x_,_x_},   // BF			         
  { /* 0xc0 */ _noni_,_x_,_x_},   // C0			         
  { /* 0xc1 */ _noni_,_x_,_x_},   // C1			         
  { /* 0xc2 */ _noni_,_x_,_x_},   // C2			         
  { /* 0xc3 */ _noni_,_x_,_x_},   // C3			         
  { /* 0xc4 */ _noni_,_x_,_x_},   // C4			         
  { /* 0xc5 */ _noni_,_x_,_x_},   // C5			         
  { /* 0xc6 */ _noni_,_x_,_x_},   // C6			         
  { /* 0xc7 */ _noni_,_x_,_x_},   // C7			         
  { /* 0xc8 */ _noni_,_x_,_x_},   // C8			         
  { /* 0xc9 */ _noni_,_x_,_x_},   // C9			         
  { /* 0xca */ _noni_,_x_,_x_},   // CA			         
  { /* 0xcb */ _FDCB_,_x_,_x_},  // CB	#FDCB		     
  { /* 0xcc */ _noni_,_x_,_x_},   // CC			         
  { /* 0xcd */ _noni_,_x_,_x_},   // CD			         
  { /* 0xce */ _noni_,_x_,_x_},   // CE			         
  { /* 0xcf */ _noni_,_x_,_x_},   // CF			         
  { /* 0xd0 */ _noni_,_x_,_x_},   // D0			         
  { /* 0xd1 */ _noni_,_x_,_x_},   // D1			         
  { /* 0xd2 */ _noni_,_x_,_x_},   // D2			         
  { /* 0xd3 */ _noni_,_x_,_x_},   // D3			         
  { /* 0xd4 */ _noni_,_x_,_x_},   // D4			         
  { /* 0xd5 */ _noni_,_x_,_x_},   // D5			         
  { /* 0xd6 */ _noni_,_x_,_x_},   // D6			         
  { /* 0xd7 */ _noni_,_x_,_x_},   // D7			         
  { /* 0xd8 */ _noni_,_x_,_x_},   // D8			         
  { /* 0xd9 */ _noni_,_x_,_x_},   // D9			         
  { /* 0xda */ _noni_,_x_,_x_},   // DA			         
  { /* 0xdb */ _noni_,_x_,_x_},   // DB			         
  { /* 0xdc */ _noni_,_x_,_x_},   // DC			         
  { /* 0xdd */ _noni_,_x_,_x_},   // DD			         
  { /* 0xde */ _noni_,_x_,_x_},   // DE			         
  { /* 0xdf */ _noni_,_x_,_x_},   // DF			         
  { /* 0xe0 */ _noni_,_x_,_x_},   // E0			         
  { /* 0xe1 */ _pop_,_x_,_iy_},    // E1	POP	IY	     
  { /* 0xe2 */ _noni_,_x_,_x_},   // E2			         
  { /* 0xe3 */ _exs_,_IspI_,_iy_}, // E3	EX	(SP),IY	 
  { /* 0xe4 */ _noni_,_x_,_x_},   // E4			         
  { /* 0xe5 */ _push_,_x_,_iy_},   // E5	PUSH	IY	   
  { /* 0xe6 */ _noni_,_x_,_x_},   // E6			         
  { /* 0xe7 */ _noni_,_x_,_x_},   // E7			         
  { /* 0xe8 */ _noni_,_x_,_x_},   // E8			         
  { /* 0xe9 */ _jp_,_ANY_,_iy_},  // E9	JP	(IY)	   
  { /* 0xea */ _noni_,_x_,_x_},   // EA			         
  { /* 0xeb */ _noni_,_x_,_x_},   // EB			         
  { /* 0xec */ _noni_,_x_,_x_},   // EC			         
  { /* 0xed */ _noni_,_x_,_x_},   // ED			         
  { /* 0xee */ _noni_,_x_,_x_},   // EE			         
  { /* 0xef */ _noni_,_x_,_x_},   // EF			         
  { /* 0xf0 */ _noni_,_x_,_x_},   // F0			         
  { /* 0xf1 */ _noni_,_x_,_x_},   // F1			         
  { /* 0xf2 */ _noni_,_x_,_x_},   // F2			         
  { /* 0xf3 */ _noni_,_x_,_x_},   // F3			         
  { /* 0xf4 */ _noni_,_x_,_x_},   // F4			         
  { /* 0xf5 */ _noni_,_x_,_x_},   // F5			         
  { /* 0xf6 */ _noni_,_x_,_x_},   // F6			         
  { /* 0xf7 */ _noni_,_x_,_x_},   // F7			         
  { /* 0xf8 */ _noni_,_x_,_x_},   // F8			         
  { /* 0xf9 */ _ld2_,_sp_,_iy_},    // F9	LD	SP,IY	   
  { /* 0xfa */ _noni_,_x_,_x_},   // FA			         
  { /* 0xfb */ _noni_,_x_,_x_},   // FB			         
  { /* 0xfc */ _noni_,_x_,_x_},   // FC			         
  { /* 0xfd */ _noni_,_x_,_x_},   // FD			         
  { /* 0xfe */ _noni_,_x_,_x_},   // FE			         
  { /* 0xff */ _noni_,_x_,_x_}   // FF			         
};

uint8_t z80_asm_DDCB[][3] =   {                   // DDCB              
  { /* 0x00 */ _noni_,_x_,_x_},   // 00			         
  { /* 0x01 */ _noni_,_x_,_x_},   // 01			         
  { /* 0x02 */ _noni_,_x_,_x_},   // 02			         
  { /* 0x03 */ _noni_,_x_,_x_},   // 03			         
  { /* 0x04 */ _noni_,_x_,_x_},   // 04			         
  { /* 0x05 */ _noni_,_x_,_x_},   // 05			         
  { /* 0x06 */ _rlc_,_x_,_IixdI_},// 06	RLC	(IX+d)	 
  { /* 0x07 */ _noni_,_x_,_x_},   // 07			         
  { /* 0x08 */ _noni_,_x_,_x_},   // 08			         
  { /* 0x09 */ _noni_,_x_,_x_},   // 09			         
  { /* 0x0a */ _noni_,_x_,_x_},   // 0A			         
  { /* 0x0b */ _noni_,_x_,_x_},   // 0B			         
  { /* 0x0c */ _noni_,_x_,_x_},   // 0C			         
  { /* 0x0d */ _noni_,_x_,_x_},   // 0D			         
  { /* 0x0e */ _rrc_,_x_,_IixdI_},// 0E	RRC	(IX+d)	 
  { /* 0x0f */ _noni_,_x_,_x_},   // 0F			         
  { /* 0x10 */ _noni_,_x_,_x_},   // 10			         
  { /* 0x11 */ _noni_,_x_,_x_},   // 11			         
  { /* 0x12 */ _noni_,_x_,_x_},   // 12			         
  { /* 0x13 */ _noni_,_x_,_x_},   // 13			         
  { /* 0x14 */ _noni_,_x_,_x_},   // 14			         
  { /* 0x15 */ _noni_,_x_,_x_},   // 15			         
  { /* 0x16 */ _rl_,_x_,_IixdI_}, // 16	RL	(IX+d)	 
  { /* 0x17 */ _noni_,_x_,_x_},   // 17			         
  { /* 0x18 */ _noni_,_x_,_x_},   // 18			         
  { /* 0x19 */ _noni_,_x_,_x_},   // 19			         
  { /* 0x1a */ _noni_,_x_,_x_},   // 1A			         
  { /* 0x1b */ _noni_,_x_,_x_},   // 1B			         
  { /* 0x1c */ _noni_,_x_,_x_},   // 1C			         
  { /* 0x1d */ _noni_,_x_,_x_},   // 1D			         
  { /* 0x1e */ _rr_,_x_,_IixdI_}, // 1E	RR	(IX+d)	 
  { /* 0x1f */ _noni_,_x_,_x_},   // 1F			         
  { /* 0x20 */ _noni_,_x_,_x_},   // 20			         
  { /* 0x21 */ _noni_,_x_,_x_},   // 21			         
  { /* 0x22 */ _noni_,_x_,_x_},   // 22			         
  { /* 0x23 */ _noni_,_x_,_x_},   // 23			         
  { /* 0x24 */ _noni_,_x_,_x_},   // 24			         
  { /* 0x25 */ _noni_,_x_,_x_},   // 25			         
  { /* 0x26 */ _sla_,_x_,_IixdI_},// 26	SLA	(IX+d)	 
  { /* 0x27 */ _noni_,_x_,_x_},   // 27			         
  { /* 0x28 */ _noni_,_x_,_x_},   // 28			         
  { /* 0x29 */ _noni_,_x_,_x_},   // 29			         
  { /* 0x2a */ _noni_,_x_,_x_},   // 2A			         
  { /* 0x2b */ _noni_,_x_,_x_},   // 2B			         
  { /* 0x2c */ _noni_,_x_,_x_},   // 2C			         
  { /* 0x2d */ _noni_,_x_,_x_},   // 2D			         
  { /* 0x2e */ _sra_,_x_,_IixdI_},// 2E	SRA	(IX+d)	 
  { /* 0x2f */ _noni_,_x_,_x_},   // 2F			         
  { /* 0x30 */ _noni_,_x_,_x_},   // 30			         
  { /* 0x31 */ _noni_,_x_,_x_},   // 31			         
  { /* 0x32 */ _noni_,_x_,_x_},   // 32			         
  { /* 0x33 */ _noni_,_x_,_x_},   // 33			         
  { /* 0x34 */ _noni_,_x_,_x_},   // 34			         
  { /* 0x35 */ _noni_,_x_,_x_},   // 35			         
  { /* 0x36 */ _sll_,_x_,_IixdI_},// 36	SLL	(IX+d)*	         
  { /* 0x37 */ _noni_,_x_,_x_},   // 37			         
  { /* 0x38 */ _noni_,_x_,_x_},   // 38			         
  { /* 0x39 */ _noni_,_x_,_x_},   // 39			         
  { /* 0x3a */ _noni_,_x_,_x_},   // 3A			         
  { /* 0x3b */ _noni_,_x_,_x_},   // 3B			         
  { /* 0x3c */ _noni_,_x_,_x_},   // 3C			         
  { /* 0x3d */ _noni_,_x_,_x_},   // 3D			         
  { /* 0x3e */ _srl_,_x_,_IixdI_},// 3E	SRL	(IX+d)	 
  { /* 0x3f */ _noni_,_x_,_x_},   // 3F			         
  { /* 0x40 */ _noni_,_x_,_x_},   // 40			         
  { /* 0x41 */ _noni_,_x_,_x_},   // 41			         
  { /* 0x42 */ _noni_,_x_,_x_},   // 42			         
  { /* 0x43 */ _noni_,_x_,_x_},   // 43			         
  { /* 0x44 */ _noni_,_x_,_x_},   // 44			         
  { /* 0x45 */ _noni_,_x_,_x_},   // 45			         
  { /* 0x46 */ _bit_,_0_,_IixdI_},// 46	BIT	0,(IX+d) 
  { /* 0x47 */ _noni_,_x_,_x_},   // 47			         
  { /* 0x48 */ _noni_,_x_,_x_},   // 48			         
  { /* 0x49 */ _noni_,_x_,_x_},   // 49			         
  { /* 0x4a */ _noni_,_x_,_x_},   // 4A			         
  { /* 0x4b */ _noni_,_x_,_x_},   // 4B			         
  { /* 0x4c */ _noni_,_x_,_x_},   // 4C			         
  { /* 0x4d */ _noni_,_x_,_x_},   // 4D			         
  { /* 0x4e */ _bit_,_1_,_IixdI_},// 4E	BIT	1,(IX+d) 
  { /* 0x4f */ _noni_,_x_,_x_},   // 4F			         
  { /* 0x50 */ _noni_,_x_,_x_},   // 50			         
  { /* 0x51 */ _noni_,_x_,_x_},   // 51			         
  { /* 0x52 */ _noni_,_x_,_x_},   // 52			         
  { /* 0x53 */ _noni_,_x_,_x_},   // 53			         
  { /* 0x54 */ _noni_,_x_,_x_},   // 54			         
  { /* 0x55 */ _noni_,_x_,_x_},   // 55			         
  { /* 0x56 */ _bit_,_2_,_IixdI_},// 56	BIT	2,(IX+d) 
  { /* 0x57 */ _noni_,_x_,_x_},   // 57			         
  { /* 0x58 */ _noni_,_x_,_x_},   // 58			         
  { /* 0x59 */ _noni_,_x_,_x_},   // 59			         
  { /* 0x5a */ _noni_,_x_,_x_},   // 5A			         
  { /* 0x5b */ _noni_,_x_,_x_},   // 5B			         
  { /* 0x5c */ _noni_,_x_,_x_},   // 5C			         
  { /* 0x5d */ _noni_,_x_,_x_},   // 5D			         
  { /* 0x5e */ _bit_,_3_,_IixdI_},// 5E	BIT	3,(IX+d) 
  { /* 0x5f */ _noni_,_x_,_x_},   // 5F			         
  { /* 0x60 */ _noni_,_x_,_x_},   // 60			         
  { /* 0x61 */ _noni_,_x_,_x_},   // 61			         
  { /* 0x62 */ _noni_,_x_,_x_},   // 62			         
  { /* 0x63 */ _noni_,_x_,_x_},   // 63			         
  { /* 0x64 */ _noni_,_x_,_x_},   // 64			         
  { /* 0x65 */ _noni_,_x_,_x_},   // 65			         
  { /* 0x66 */ _bit_,_4_,_IixdI_},// 66	BIT	4,(IX+d) 
  { /* 0x67 */ _noni_,_x_,_x_},   // 67			         
  { /* 0x68 */ _noni_,_x_,_x_},   // 68			         
  { /* 0x69 */ _noni_,_x_,_x_},   // 69			         
  { /* 0x6a */ _noni_,_x_,_x_},   // 6A			         
  { /* 0x6b */ _noni_,_x_,_x_},   // 6B			         
  { /* 0x6c */ _noni_,_x_,_x_},   // 6C			         
  { /* 0x6d */ _noni_,_x_,_x_},   // 6D			         
  { /* 0x6e */ _bit_,_5_,_IixdI_},// 6E	BIT	5,(IX+d) 
  { /* 0x6f */ _noni_,_x_,_x_},   // 6F			         
  { /* 0x70 */ _noni_,_x_,_x_},   // 70			         
  { /* 0x71 */ _noni_,_x_,_x_},   // 71			         
  { /* 0x72 */ _noni_,_x_,_x_},   // 72			         
  { /* 0x73 */ _noni_,_x_,_x_},   // 73			         
  { /* 0x74 */ _noni_,_x_,_x_},   // 74			         
  { /* 0x75 */ _noni_,_x_,_x_},   // 75			         
  { /* 0x76 */ _bit_,_6_,_IixdI_},// 76	BIT	6,(IX+d) 
  { /* 0x77 */ _noni_,_x_,_x_},   // 77			         
  { /* 0x78 */ _noni_,_x_,_x_},   // 78			         
  { /* 0x79 */ _noni_,_x_,_x_},   // 79			         
  { /* 0x7a */ _noni_,_x_,_x_},   // 7A			         
  { /* 0x7b */ _noni_,_x_,_x_},   // 7B			         
  { /* 0x7c */ _noni_,_x_,_x_},   // 7C			         
  { /* 0x7d */ _noni_,_x_,_x_},   // 7D			         
  { /* 0x7e */ _bit_,_7_,_IixdI_},// 7E	BIT	7,(IX+d) 
  { /* 0x7f */ _noni_,_x_,_x_},   // 7F			         
  { /* 0x80 */ _noni_,_x_,_x_},   // 80			         
  { /* 0x81 */ _noni_,_x_,_x_},   // 81			         
  { /* 0x82 */ _noni_,_x_,_x_},   // 82			         
  { /* 0x83 */ _noni_,_x_,_x_},   // 83			         
  { /* 0x84 */ _noni_,_x_,_x_},   // 84			         
  { /* 0x85 */ _noni_,_x_,_x_},   // 85			         
  { /* 0x86 */ _res_,_0_,_IixdI_},// 86	RES	0,(IX+d) 
  { /* 0x87 */ _noni_,_x_,_x_},   // 87			         
  { /* 0x88 */ _noni_,_x_,_x_},   // 88			         
  { /* 0x89 */ _noni_,_x_,_x_},   // 89			         
  { /* 0x8a */ _noni_,_x_,_x_},   // 8A			         
  { /* 0x8b */ _noni_,_x_,_x_},   // 8B			         
  { /* 0x8c */ _noni_,_x_,_x_},   // 8C			         
  { /* 0x8d */ _noni_,_x_,_x_},   // 8D			         
  { /* 0x8e */ _res_,_1_,_IixdI_},// 8E	RES	1,(IX+d) 
  { /* 0x8f */ _noni_,_x_,_x_},   // 8F			         
  { /* 0x90 */ _noni_,_x_,_x_},   // 90			         
  { /* 0x91 */ _noni_,_x_,_x_},   // 91			         
  { /* 0x92 */ _noni_,_x_,_x_},   // 92			         
  { /* 0x93 */ _noni_,_x_,_x_},   // 93			         
  { /* 0x94 */ _noni_,_x_,_x_},   // 94			         
  { /* 0x95 */ _noni_,_x_,_x_},   // 95			         
  { /* 0x96 */ _res_,_2_,_IixdI_},// 96	RES	2,(IX+d) 
  { /* 0x97 */ _noni_,_x_,_x_},   // 97			         
  { /* 0x98 */ _noni_,_x_,_x_},   // 98			         
  { /* 0x99 */ _noni_,_x_,_x_},   // 99			         
  { /* 0x9a */ _noni_,_x_,_x_},   // 9A			         
  { /* 0x9b */ _noni_,_x_,_x_},   // 9B			         
  { /* 0x9c */ _noni_,_x_,_x_},   // 9C			         
  { /* 0x9d */ _noni_,_x_,_x_},   // 9D			         
  { /* 0x9e */ _res_,_3_,_IixdI_},// 9E	RES	3,(IX+d) 
  { /* 0x9f */ _noni_,_x_,_x_},   // 9F			         
  { /* 0xa0 */ _noni_,_x_,_x_},   // A0			         
  { /* 0xa1 */ _noni_,_x_,_x_},   // A1			         
  { /* 0xa2 */ _noni_,_x_,_x_},   // A2			         
  { /* 0xa3 */ _noni_,_x_,_x_},   // A3			         
  { /* 0xa4 */ _noni_,_x_,_x_},   // A4			         
  { /* 0xa5 */ _noni_,_x_,_x_},   // A5			         
  { /* 0xa6 */ _res_,_4_,_IixdI_},// A6	RES	4,(IX+d) 
  { /* 0xa7 */ _noni_,_x_,_x_},   // A7			         
  { /* 0xa8 */ _noni_,_x_,_x_},   // A8			         
  { /* 0xa9 */ _noni_,_x_,_x_},   // A9			         
  { /* 0xaa */ _noni_,_x_,_x_},   // AA			         
  { /* 0xab */ _noni_,_x_,_x_},   // AB			         
  { /* 0xac */ _noni_,_x_,_x_},   // AC			         
  { /* 0xad */ _noni_,_x_,_x_},   // AD			         
  { /* 0xae */ _res_,_5_,_IixdI_},// AE	RES	5,(IX+d) 
  { /* 0xaf */ _noni_,_x_,_x_},   // AF			         
  { /* 0xb0 */ _noni_,_x_,_x_},   // B0			         
  { /* 0xb1 */ _noni_,_x_,_x_},   // B1			         
  { /* 0xb2 */ _noni_,_x_,_x_},   // B2			         
  { /* 0xb3 */ _noni_,_x_,_x_},   // B3			         
  { /* 0xb4 */ _noni_,_x_,_x_},   // B4			         
  { /* 0xb5 */ _noni_,_x_,_x_},   // B5			         
  { /* 0xb6 */ _res_,_6_,_IixdI_},// B6	RES	6,(IX+d) 
  { /* 0xb7 */ _noni_,_x_,_x_},   // B7			         
  { /* 0xb8 */ _noni_,_x_,_x_},   // B8			         
  { /* 0xb9 */ _noni_,_x_,_x_},   // B9			         
  { /* 0xba */ _noni_,_x_,_x_},   // BA			         
  { /* 0xbb */ _noni_,_x_,_x_},   // BB			         
  { /* 0xbc */ _noni_,_x_,_x_},   // BC			         
  { /* 0xbd */ _noni_,_x_,_x_},   // BD			         
  { /* 0xbe */ _res_,_7_,_IixdI_},// BE	RES	7,(IX+d) 
  { /* 0xbf */ _noni_,_x_,_x_},   // BF			         
  { /* 0xc0 */ _noni_,_x_,_x_},   // C0			         
  { /* 0xc1 */ _noni_,_x_,_x_},   // C1			         
  { /* 0xc2 */ _noni_,_x_,_x_},   // C2			         
  { /* 0xc3 */ _noni_,_x_,_x_},   // C3			         
  { /* 0xc4 */ _noni_,_x_,_x_},   // C4			         
  { /* 0xc5 */ _noni_,_x_,_x_},   // C5			         
  { /* 0xc6 */ _set_,_0_,_IixdI_},// C6	SET	0,(IX+d) 
  { /* 0xc7 */ _noni_,_x_,_x_},   // C7			         
  { /* 0xc8 */ _noni_,_x_,_x_},   // C8			         
  { /* 0xc9 */ _noni_,_x_,_x_},   // C9			         
  { /* 0xca */ _noni_,_x_,_x_},   // CA			         
  { /* 0xcb */ _noni_,_x_,_x_},   // CB			         
  { /* 0xcc */ _noni_,_x_,_x_},   // CC			         
  { /* 0xcd */ _noni_,_x_,_x_},   // CD			         
  { /* 0xce */ _set_,_1_,_IixdI_},// CE	SET	1,(IX+d) 
  { /* 0xcf */ _noni_,_x_,_x_},   // CF			         
  { /* 0xd0 */ _noni_,_x_,_x_},   // D0			         
  { /* 0xd1 */ _noni_,_x_,_x_},   // D1			         
  { /* 0xd2 */ _noni_,_x_,_x_},   // D2			         
  { /* 0xd3 */ _noni_,_x_,_x_},   // D3			         
  { /* 0xd4 */ _noni_,_x_,_x_},   // D4			         
  { /* 0xd5 */ _noni_,_x_,_x_},   // D5			         
  { /* 0xd6 */ _set_,_2_,_IixdI_},// D6	SET	2,(IX+d) 
  { /* 0xd7 */ _noni_,_x_,_x_},   // D7			         
  { /* 0xd8 */ _noni_,_x_,_x_},   // D8			         
  { /* 0xd9 */ _noni_,_x_,_x_},   // D9			         
  { /* 0xda */ _noni_,_x_,_x_},   // DA			         
  { /* 0xdb */ _noni_,_x_,_x_},   // DB			         
  { /* 0xdc */ _noni_,_x_,_x_},   // DC			         
  { /* 0xdd */ _noni_,_x_,_x_},   // DD			         
  { /* 0xde */ _set_,_3_,_IixdI_},// DE	SET	3,(IX+d) 
  { /* 0xdf */ _noni_,_x_,_x_},   // DF			         
  { /* 0xe0 */ _noni_,_x_,_x_},   // E0			         
  { /* 0xe1 */ _noni_,_x_,_x_},   // E1			         
  { /* 0xe2 */ _noni_,_x_,_x_},   // E2			         
  { /* 0xe3 */ _noni_,_x_,_x_},   // E3			         
  { /* 0xe4 */ _noni_,_x_,_x_},   // E4			         
  { /* 0xe5 */ _noni_,_x_,_x_},   // E5			         
  { /* 0xe6 */ _set_,_4_,_IixdI_},// E6	SET	4,(IX+d) 
  { /* 0xe7 */ _noni_,_x_,_x_},   // E7			         
  { /* 0xe8 */ _noni_,_x_,_x_},   // E8			         
  { /* 0xe9 */ _noni_,_x_,_x_},   // E9			         
  { /* 0xea */ _noni_,_x_,_x_},   // EA			         
  { /* 0xeb */ _noni_,_x_,_x_},   // EB			         
  { /* 0xec */ _noni_,_x_,_x_},   // EC			         
  { /* 0xed */ _noni_,_x_,_x_},   // ED			         
  { /* 0xee */ _set_,_5_,_IixdI_},// EE	SET	5,(IX+d) 
  { /* 0xef */ _noni_,_x_,_x_},   // EF			         
  { /* 0xf0 */ _noni_,_x_,_x_},   // F0			         
  { /* 0xf1 */ _noni_,_x_,_x_},   // F1			         
  { /* 0xf2 */ _noni_,_x_,_x_},   // F2			         
  { /* 0xf3 */ _noni_,_x_,_x_},   // F3			         
  { /* 0xf4 */ _noni_,_x_,_x_},   // F4			         
  { /* 0xf5 */ _noni_,_x_,_x_},   // F5			         
  { /* 0xf6 */ _set_,_6_,_IixdI_},// F6	SET	6,(IX+d) 
  { /* 0xf7 */ _noni_,_x_,_x_},   // F7			         
  { /* 0xf8 */ _noni_,_x_,_x_},   // F8			         
  { /* 0xf9 */ _noni_,_x_,_x_},   // F9			         
  { /* 0xfa */ _noni_,_x_,_x_},   // FA			         
  { /* 0xfb */ _noni_,_x_,_x_},   // FB			         
  { /* 0xfc */ _noni_,_x_,_x_},   // FC			         
  { /* 0xfd */ _noni_,_x_,_x_},   // FD			         
  { /* 0xfe */ _set_,_7_,_IixdI_},// FE	SET	7,(IX+d) 
  { /* 0xff */ _noni_,_x_,_x_}   // FF			         
};

uint8_t z80_asm_FDCB[][3] =   {                   // FDCB              
  { /* 0x00 */ _noni_,_x_,_x_},   // 00			         
  { /* 0x01 */ _noni_,_x_,_x_},   // 01			         
  { /* 0x02 */ _noni_,_x_,_x_},   // 02			         
  { /* 0x03 */ _noni_,_x_,_x_},   // 03			         
  { /* 0x04 */ _noni_,_x_,_x_},   // 04			         
  { /* 0x05 */ _noni_,_x_,_x_},   // 05			         
  { /* 0x06 */ _rlc_,_x_,_IiydI_},// 06	RLC	(IY+d)	 
  { /* 0x07 */ _noni_,_x_,_x_},   // 07			         
  { /* 0x08 */ _noni_,_x_,_x_},   // 08			         
  { /* 0x09 */ _noni_,_x_,_x_},   // 09			         
  { /* 0x0a */ _noni_,_x_,_x_},   // 0A			         
  { /* 0x0b */ _noni_,_x_,_x_},   // 0B			         
  { /* 0x0c */ _noni_,_x_,_x_},   // 0C			         
  { /* 0x0d */ _noni_,_x_,_x_},   // 0D			         
  { /* 0x0e */ _rrc_,_x_,_IiydI_},// 0E	RRC	(IY+d)	 
  { /* 0x0f */ _noni_,_x_,_x_},   // 0F			         
  { /* 0x10 */ _noni_,_x_,_x_},   // 10			         
  { /* 0x11 */ _noni_,_x_,_x_},   // 11			         
  { /* 0x12 */ _noni_,_x_,_x_},   // 12			         
  { /* 0x13 */ _noni_,_x_,_x_},   // 13			         
  { /* 0x14 */ _noni_,_x_,_x_},   // 14			         
  { /* 0x15 */ _noni_,_x_,_x_},   // 15			         
  { /* 0x16 */ _rl_,_x_,_IiydI_}, // 16	RL	(IY+d)	 
  { /* 0x17 */ _noni_,_x_,_x_},   // 17			         
  { /* 0x18 */ _noni_,_x_,_x_},   // 18			         
  { /* 0x19 */ _noni_,_x_,_x_},   // 19			         
  { /* 0x1a */ _noni_,_x_,_x_},   // 1A			         
  { /* 0x1b */ _noni_,_x_,_x_},   // 1B			         
  { /* 0x1c */ _noni_,_x_,_x_},   // 1C			         
  { /* 0x1d */ _noni_,_x_,_x_},   // 1D			         
  { /* 0x1e */ _rr_,_x_,_IiydI_}, // 1E	RR	(IY+d)	 
  { /* 0x1f */ _noni_,_x_,_x_},   // 1F			         
  { /* 0x20 */ _noni_,_x_,_x_},   // 20			         
  { /* 0x21 */ _noni_,_x_,_x_},   // 21			         
  { /* 0x22 */ _noni_,_x_,_x_},   // 22			         
  { /* 0x23 */ _noni_,_x_,_x_},   // 23			         
  { /* 0x24 */ _noni_,_x_,_x_},   // 24			         
  { /* 0x25 */ _noni_,_x_,_x_},   // 25			         
  { /* 0x26 */ _sla_,_x_,_IiydI_},// 26	SLA	(IY+d)	 
  { /* 0x27 */ _noni_,_x_,_x_},   // 27			         
  { /* 0x28 */ _noni_,_x_,_x_},   // 28			         
  { /* 0x29 */ _noni_,_x_,_x_},   // 29			         
  { /* 0x2a */ _noni_,_x_,_x_},   // 2A			         
  { /* 0x2b */ _noni_,_x_,_x_},   // 2B			         
  { /* 0x2c */ _noni_,_x_,_x_},   // 2C			         
  { /* 0x2d */ _noni_,_x_,_x_},   // 2D			         
  { /* 0x2e */ _sra_,_x_,_IiydI_},// 2E	SRA	(IY+d)	 
  { /* 0x2f */ _noni_,_x_,_x_},   // 2F			         
  { /* 0x30 */ _noni_,_x_,_x_},   // 30			         
  { /* 0x31 */ _noni_,_x_,_x_},   // 31			         
  { /* 0x32 */ _noni_,_x_,_x_},   // 32			         
  { /* 0x33 */ _noni_,_x_,_x_},   // 33			         
  { /* 0x34 */ _noni_,_x_,_x_},   // 34			         
  { /* 0x35 */ _noni_,_x_,_x_},   // 35			         
  { /* 0x36 */ _sll_,_x_,_IiydI_},// 36 SLL	(IY+d)*			         
  { /* 0x37 */ _noni_,_x_,_x_},   // 37			         
  { /* 0x38 */ _noni_,_x_,_x_},   // 38			         
  { /* 0x39 */ _noni_,_x_,_x_},   // 39			         
  { /* 0x3a */ _noni_,_x_,_x_},   // 3A			         
  { /* 0x3b */ _noni_,_x_,_x_},   // 3B			         
  { /* 0x3c */ _noni_,_x_,_x_},   // 3C			         
  { /* 0x3d */ _noni_,_x_,_x_},   // 3D			         
  { /* 0x3e */ _srl_,_x_,_IiydI_},// 3E	SRL	(IY+d)	 
  { /* 0x3f */ _noni_,_x_,_x_},   // 3F			         
  { /* 0x40 */ _noni_,_x_,_x_},   // 40			         
  { /* 0x41 */ _noni_,_x_,_x_},   // 41			         
  { /* 0x42 */ _noni_,_x_,_x_},   // 42			         
  { /* 0x43 */ _noni_,_x_,_x_},   // 43			         
  { /* 0x44 */ _noni_,_x_,_x_},   // 44			         
  { /* 0x45 */ _noni_,_x_,_x_},   // 45			         
  { /* 0x46 */ _bit_,_0_,_IiydI_},// 46	BIT	0,(IY+d) 
  { /* 0x47 */ _noni_,_x_,_x_},   // 47			         
  { /* 0x48 */ _noni_,_x_,_x_},   // 48			         
  { /* 0x49 */ _noni_,_x_,_x_},   // 49			         
  { /* 0x4a */ _noni_,_x_,_x_},   // 4A			         
  { /* 0x4b */ _noni_,_x_,_x_},   // 4B			         
  { /* 0x4c */ _noni_,_x_,_x_},   // 4C			         
  { /* 0x4d */ _noni_,_x_,_x_},   // 4D			         
  { /* 0x4e */ _bit_,_1_,_IiydI_},// 4E	BIT	1,(IY+d) 
  { /* 0x4f */ _noni_,_x_,_x_},   // 4F			         
  { /* 0x50 */ _noni_,_x_,_x_},   // 50			         
  { /* 0x51 */ _noni_,_x_,_x_},   // 51			         
  { /* 0x52 */ _noni_,_x_,_x_},   // 52			         
  { /* 0x53 */ _noni_,_x_,_x_},   // 53			         
  { /* 0x54 */ _noni_,_x_,_x_},   // 54			         
  { /* 0x55 */ _noni_,_x_,_x_},   // 55			         
  { /* 0x56 */ _bit_,_2_,_IiydI_},// 56	BIT	2,(IY+d) 
  { /* 0x57 */ _noni_,_x_,_x_},   // 57			         
  { /* 0x58 */ _noni_,_x_,_x_},   // 58			         
  { /* 0x59 */ _noni_,_x_,_x_},   // 59			         
  { /* 0x5a */ _noni_,_x_,_x_},   // 5A			         
  { /* 0x5b */ _noni_,_x_,_x_},   // 5B			         
  { /* 0x5c */ _noni_,_x_,_x_},   // 5C			         
  { /* 0x5d */ _noni_,_x_,_x_},   // 5D			         
  { /* 0x5e */ _bit_,_3_,_IiydI_},// 5E	BIT	3,(IY+d) 
  { /* 0x5f */ _noni_,_x_,_x_},   // 5F			         
  { /* 0x60 */ _noni_,_x_,_x_},   // 60			         
  { /* 0x61 */ _noni_,_x_,_x_},   // 61			         
  { /* 0x62 */ _noni_,_x_,_x_},   // 62			         
  { /* 0x63 */ _noni_,_x_,_x_},   // 63			         
  { /* 0x64 */ _noni_,_x_,_x_},   // 64			         
  { /* 0x65 */ _noni_,_x_,_x_},   // 65			         
  { /* 0x66 */ _bit_,_4_,_IiydI_},// 66	BIT	4,(IY+d) 
  { /* 0x67 */ _noni_,_x_,_x_},   // 67			         
  { /* 0x68 */ _noni_,_x_,_x_},   // 68			         
  { /* 0x69 */ _noni_,_x_,_x_},   // 69			         
  { /* 0x6a */ _noni_,_x_,_x_},   // 6A			         
  { /* 0x6b */ _noni_,_x_,_x_},   // 6B			         
  { /* 0x6c */ _noni_,_x_,_x_},   // 6C			         
  { /* 0x6d */ _noni_,_x_,_x_},   // 6D			         
  { /* 0x6e */ _bit_,_5_,_IiydI_},// 6E	BIT	5,(IY+d) 
  { /* 0x6f */ _noni_,_x_,_x_},   // 6F			         
  { /* 0x70 */ _noni_,_x_,_x_},   // 70			         
  { /* 0x71 */ _noni_,_x_,_x_},   // 71			         
  { /* 0x72 */ _noni_,_x_,_x_},   // 72			         
  { /* 0x73 */ _noni_,_x_,_x_},   // 73			         
  { /* 0x74 */ _noni_,_x_,_x_},   // 74			         
  { /* 0x75 */ _noni_,_x_,_x_},   // 75			         
  { /* 0x76 */ _bit_,_6_,_IiydI_},// 76	BIT	6,(IY+d) 
  { /* 0x77 */ _noni_,_x_,_x_},   // 77			         
  { /* 0x78 */ _noni_,_x_,_x_},   // 78			         
  { /* 0x79 */ _noni_,_x_,_x_},   // 79			         
  { /* 0x7a */ _noni_,_x_,_x_},   // 7A			         
  { /* 0x7b */ _noni_,_x_,_x_},   // 7B			         
  { /* 0x7c */ _noni_,_x_,_x_},   // 7C			         
  { /* 0x7d */ _noni_,_x_,_x_},   // 7D			         
  { /* 0x7e */ _bit_,_7_,_IiydI_},// 7E	BIT	7,(IY+d) 
  { /* 0x7f */ _noni_,_x_,_x_},   // 7F			         
  { /* 0x80 */ _noni_,_x_,_x_},   // 80			         
  { /* 0x81 */ _noni_,_x_,_x_},   // 81			         
  { /* 0x82 */ _noni_,_x_,_x_},   // 82			         
  { /* 0x83 */ _noni_,_x_,_x_},   // 83			         
  { /* 0x84 */ _noni_,_x_,_x_},   // 84			         
  { /* 0x85 */ _noni_,_x_,_x_},   // 85			         
  { /* 0x86 */ _res_,_0_,_IiydI_},// 86	RES	0,(IY+d) 
  { /* 0x87 */ _noni_,_x_,_x_},   // 87			         
  { /* 0x88 */ _noni_,_x_,_x_},   // 88			         
  { /* 0x89 */ _noni_,_x_,_x_},   // 89			         
  { /* 0x8a */ _noni_,_x_,_x_},   // 8A			         
  { /* 0x8b */ _noni_,_x_,_x_},   // 8B			         
  { /* 0x8c */ _noni_,_x_,_x_},   // 8C			         
  { /* 0x8d */ _noni_,_x_,_x_},   // 8D			         
  { /* 0x8e */ _res_,_1_,_IiydI_},// 8E	RES	1,(IY+d) 
  { /* 0x8f */ _noni_,_x_,_x_},   // 8F			         
  { /* 0x90 */ _noni_,_x_,_x_},   // 90			         
  { /* 0x91 */ _noni_,_x_,_x_},   // 91			         
  { /* 0x92 */ _noni_,_x_,_x_},   // 92			         
  { /* 0x93 */ _noni_,_x_,_x_},   // 93			         
  { /* 0x94 */ _noni_,_x_,_x_},   // 94			         
  { /* 0x95 */ _noni_,_x_,_x_},   // 95			         
  { /* 0x96 */ _res_,_2_,_IiydI_},// 96	RES	2,(IY+d) 
  { /* 0x97 */ _noni_,_x_,_x_},   // 97			         
  { /* 0x98 */ _noni_,_x_,_x_},   // 98			         
  { /* 0x99 */ _noni_,_x_,_x_},   // 99			         
  { /* 0x9a */ _noni_,_x_,_x_},   // 9A			         
  { /* 0x9b */ _noni_,_x_,_x_},   // 9B			         
  { /* 0x9c */ _noni_,_x_,_x_},   // 9C			         
  { /* 0x9d */ _noni_,_x_,_x_},   // 9D			         
  { /* 0x9e */ _res_,_3_,_IiydI_},// 9E	RES	3,(IY+d) 
  { /* 0x9f */ _noni_,_x_,_x_},   // 9F			         
  { /* 0xa0 */ _noni_,_x_,_x_},   // A0			         
  { /* 0xa1 */ _noni_,_x_,_x_},   // A1			         
  { /* 0xa2 */ _noni_,_x_,_x_},   // A2			         
  { /* 0xa3 */ _noni_,_x_,_x_},   // A3			         
  { /* 0xa4 */ _noni_,_x_,_x_},   // A4			         
  { /* 0xa5 */ _noni_,_x_,_x_},   // A5			         
  { /* 0xa6 */ _res_,_4_,_IiydI_},// A6	RES	4,(IY+d) 
  { /* 0xa7 */ _noni_,_x_,_x_},   // A7			         
  { /* 0xa8 */ _noni_,_x_,_x_},   // A8			         
  { /* 0xa9 */ _noni_,_x_,_x_},   // A9			         
  { /* 0xaa */ _noni_,_x_,_x_},   // AA			         
  { /* 0xab */ _noni_,_x_,_x_},   // AB			         
  { /* 0xac */ _noni_,_x_,_x_},   // AC			         
  { /* 0xad */ _noni_,_x_,_x_},   // AD			         
  { /* 0xae */ _res_,_5_,_IiydI_},// AE	RES	5,(IY+d) 
  { /* 0xaf */ _noni_,_x_,_x_},   // AF			         
  { /* 0xb0 */ _noni_,_x_,_x_},   // B0			         
  { /* 0xb1 */ _noni_,_x_,_x_},   // B1			         
  { /* 0xb2 */ _noni_,_x_,_x_},   // B2			         
  { /* 0xb3 */ _noni_,_x_,_x_},   // B3			         
  { /* 0xb4 */ _noni_,_x_,_x_},   // B4			         
  { /* 0xb5 */ _noni_,_x_,_x_},   // B5			         
  { /* 0xb6 */ _res_,_6_,_IiydI_},// B6	RES	6,(IY+d) 
  { /* 0xb7 */ _noni_,_x_,_x_},   // B7			         
  { /* 0xb8 */ _noni_,_x_,_x_},   // B8			         
  { /* 0xb9 */ _noni_,_x_,_x_},   // B9			         
  { /* 0xba */ _noni_,_x_,_x_},   // BA			         
  { /* 0xbb */ _noni_,_x_,_x_},   // BB			         
  { /* 0xbc */ _noni_,_x_,_x_},   // BC			         
  { /* 0xbd */ _noni_,_x_,_x_},   // BD			         
  { /* 0xbe */ _res_,_7_,_IiydI_},// BE	RES	7,(IY+d) 
  { /* 0xbf */ _noni_,_x_,_x_},   // BF			         
  { /* 0xc0 */ _noni_,_x_,_x_},   // C0			         
  { /* 0xc1 */ _noni_,_x_,_x_},   // C1			         
  { /* 0xc2 */ _noni_,_x_,_x_},   // C2			         
  { /* 0xc3 */ _noni_,_x_,_x_},   // C3			         
  { /* 0xc4 */ _noni_,_x_,_x_},   // C4			         
  { /* 0xc5 */ _noni_,_x_,_x_},   // C5			         
  { /* 0xc6 */ _set_,_0_,_IiydI_},// C6	SET	0,(IY+d) 
  { /* 0xc7 */ _noni_,_x_,_x_},   // C7			         
  { /* 0xc8 */ _noni_,_x_,_x_},   // C8			         
  { /* 0xc9 */ _noni_,_x_,_x_},   // C9			         
  { /* 0xca */ _noni_,_x_,_x_},   // CA			         
  { /* 0xcb */ _noni_,_x_,_x_},   // CB			         
  { /* 0xcc */ _noni_,_x_,_x_},   // CC			         
  { /* 0xcd */ _noni_,_x_,_x_},   // CD			         
  { /* 0xce */ _set_,_1_,_IiydI_},// CE	SET	1,(IY+d) 
  { /* 0xcf */ _noni_,_x_,_x_},   // CF			         
  { /* 0xd0 */ _noni_,_x_,_x_},   // D0			         
  { /* 0xd1 */ _noni_,_x_,_x_},   // D1			         
  { /* 0xd2 */ _noni_,_x_,_x_},   // D2			         
  { /* 0xd3 */ _noni_,_x_,_x_},   // D3			         
  { /* 0xd4 */ _noni_,_x_,_x_},   // D4			         
  { /* 0xd5 */ _noni_,_x_,_x_},   // D5			         
  { /* 0xd6 */ _set_,_2_,_IiydI_},// D6	SET	2,(IY+d) 
  { /* 0xd7 */ _noni_,_x_,_x_},   // D7			         
  { /* 0xd8 */ _noni_,_x_,_x_},   // D8			         
  { /* 0xd9 */ _noni_,_x_,_x_},   // D9			         
  { /* 0xda */ _noni_,_x_,_x_},   // DA			         
  { /* 0xdb */ _noni_,_x_,_x_},   // DB			         
  { /* 0xdc */ _noni_,_x_,_x_},   // DC			         
  { /* 0xdd */ _noni_,_x_,_x_},   // DD			         
  { /* 0xde */ _set_,_3_,_IiydI_},// DE	SET	3,(IY+d) 
  { /* 0xdf */ _noni_,_x_,_x_},   // DF			         
  { /* 0xe0 */ _noni_,_x_,_x_},   // E0			         
  { /* 0xe1 */ _noni_,_x_,_x_},   // E1			         
  { /* 0xe2 */ _noni_,_x_,_x_},   // E2			         
  { /* 0xe3 */ _noni_,_x_,_x_},   // E3			         
  { /* 0xe4 */ _noni_,_x_,_x_},   // E4			         
  { /* 0xe5 */ _noni_,_x_,_x_},   // E5			         
  { /* 0xe6 */ _set_,_4_,_IiydI_},// E6	SET	4,(IY+d) 
  { /* 0xe7 */ _noni_,_x_,_x_},   // E7			         
  { /* 0xe8 */ _noni_,_x_,_x_},   // E8			         
  { /* 0xe9 */ _noni_,_x_,_x_},   // E9			         
  { /* 0xea */ _noni_,_x_,_x_},   // EA			         
  { /* 0xeb */ _noni_,_x_,_x_},   // EB			         
  { /* 0xec */ _noni_,_x_,_x_},   // EC			         
  { /* 0xed */ _noni_,_x_,_x_},   // ED			         
  { /* 0xee */ _set_,_5_,_IiydI_},// EE	SET	5,(IY+d) 
  { /* 0xef */ _noni_,_x_,_x_},   // EF			         
  { /* 0xf0 */ _noni_,_x_,_x_},   // F0			         
  { /* 0xf1 */ _noni_,_x_,_x_},   // F1			         
  { /* 0xf2 */ _noni_,_x_,_x_},   // F2			         
  { /* 0xf3 */ _noni_,_x_,_x_},   // F3			         
  { /* 0xf4 */ _noni_,_x_,_x_},   // F4			         
  { /* 0xf5 */ _noni_,_x_,_x_},   // F5			         
  { /* 0xf6 */ _set_,_6_,_IiydI_},// F6	SET	6,(IY+d) 
  { /* 0xf7 */ _noni_,_x_,_x_},   // F7			         
  { /* 0xf8 */ _noni_,_x_,_x_},   // F8			         
  { /* 0xf9 */ _noni_,_x_,_x_},   // F9			         
  { /* 0xfa */ _noni_,_x_,_x_},   // FA			         
  { /* 0xfb */ _noni_,_x_,_x_},   // FB			         
  { /* 0xfc */ _noni_,_x_,_x_},   // FC			         
  { /* 0xfd */ _noni_,_x_,_x_},   // FD			         
  { /* 0xfe */ _set_,_7_,_IiydI_},// FE	SET	7,(IY+d) 
  { /* 0xff */ _noni_,_x_,_x_}   // FF			         
};
