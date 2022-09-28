	.EQU	CTRL	= 0
	.EQU	SHIFT	= 1
	.EQU	SCRLOCK = 2
	.EQU	CAPSLOCK= 3
	.EQU	ALT	= 4
	
	.EQU  	EV_E0   = 5
	.EQU  	EV_F0   = 6

	.EQU  	READING = 7

; ps/2 keyboard processing

	or    	kbread, kbread          ; kbread==0?
	brne  	KBD_L1              	; data ready

;	lds	temp, kmodk
;	cbr	temp, (1<<READING)
;	cpse	kbcntr, zero
;	sbr	temp, (1<<READING)
;	sts	kmodk, temp		; set flag that key is processed
	
	rjmp	KBD_EXIT           	; proceed, no reason to pay attention

KBD_L1:                      		; data ready
    	mov   	tdata, kbread      	; store for processing
    	clr   	kbread             	; set processed

;  	cpi	tdata, 0xfa		; check ACK
;	brne	KBD_not_fa          

	sbrs	kbledr, 7		; check that kdledr is processing
    	rjmp	KBD_E1            	; continue if no

      	lds	temp, kmodk
      	clr	tdata
      	sbrc	temp, SCRLOCK
      	sbr	tdata, (1<<0)
      	sbrc	temp, CAPSLOCK
      	sbr	tdata, (1<<2)		; led state data to send

      	lds	temp, sysrq
      	sbrc	temp, 6			; mouse on flag
      	sbr	tdata, (1<<1)		; NUMLOCK led

      	mov	kbldata, tdata		; byte to send

      	ldi	temp, 0x81
	mov	kbledr, temp		; send second byte for led control

    	rjmp	KBD_EXIT            	; exit

KBD_E1:
  	cpi	tdata, 0xfa		; check ACK
	brne	KBD_not_fa          
    	rjmp	KBD_EXIT            	; exit
	
KBD_not_fa:
  	cpi	tdata, 0xfe		; RESEND REQUEST
	brne	KBD_not_fe          

  	clr	kbledr
  	inc	kbledr			; resend led set command
	ldi	temp, 0xed		; data to send
	mov	kbldata, temp
    	rjmp	KBD_EXIT            	; exit

KBD_not_fe:
  	cpi	tdata, 0xe1
	brne	KBD_not_e1          
    	rjmp	KBD_EXIT		; ignore, exit

KBD_not_e1:
	cpi	tdata, 0xe0
	brne	KBD_not_e0          
    	sbr   	kbmdkey, (1<<EV_E0)	; set ev_e0 flag and exit
    	rjmp	KBD_EXIT

KBD_not_e0:
	cpi	tdata, 0xf0
	brne	KBD_not_f0          
    	sbr   	kbmdkey, (1<<EV_F0)	; set ev_f0 flag and exit
    	rjmp	KBD_EXIT

KBD_not_f0:				; key code arrived

  	sbrs	kbmdkey, EV_F0		 ; check e0 state
	rjmp	KBD_check_e0       

    	; key released
  	cpi	tdata, 0x59       ; == SHIFT1 ?
    	brne  	KBD_L2_01          ; no = skip
  	cbr	kbmdkey, (1<<SHIFT)	 ; clear shift modkey flag
    	rjmp  	KBD_CLEAR
KBD_L2_01:
	cpi	tdata, 0x12       ; == SHIFT2 ?
    	brne  	KBD_L2_02
	cbr	kbmdkey, (1<<SHIFT)	 ; clear shift modkey flag
    	rjmp  	KBD_CLEAR
KBD_L2_02:
	cpi	tdata, 0x14       ; == CTRL ?
    	brne  	KBD_L2_03
	cbr	kbmdkey, (1<<CTRL)	 ; clear control modkey flag
    	rjmp  	KBD_CLEAR
KBD_L2_03:
	cpi	tdata, 0x11       ; == ALT ?
    	brne  	KBD_L2_04
	cbr	kbmdkey, (1<<ALT)	 ; clear control modkey flag
;    	rjmp  	KBD_CLEAR
KBD_L2_04:
    	rjmp  	KBD_CLEAR

KBD_check_e0:

	sbrs	kbmdkey, EV_E0		; check e0 state
	rjmp	KBD_L4			; goto _l4 if no

    	; decode e0 * keys
	cpi	tdata, 0x69       	; check char 0x69<=char<=0x7d
	brlo	KBD_L4
	cpi	tdata, 0x7d+1
	brsh	KBD_L4
                             		; range detected - decoding
	ldi	ZH, high(2*e0decode)	; read data from the decode table
	mov	ZL, tdata
	subi	ZL, 0x69
	lpm	tdata, Z		; read decoded e0 code

KBD_L4:
	; process key press
    	cbr   	kbmdkey, (1<<EV_E0) 	; clear all flags

	cpi	tdata, 0x83       	; ==F7 key?
    	brne  	KBD_L4_1
	ldi	tdata, 0x02		; process F7 exception

KBD_L4_1:
	cpi	tdata, 0x59
	brne  	KBD_L4_01           	; shift
    	sbr   	kbmdkey, (1<<SHIFT)
    	rjmp  	KBD_CLEAR
KBD_L4_01:
	cpi	tdata, 0x12
	brne  	KBD_L4_02           	; shift
    	sbr   	kbmdkey, (1<<SHIFT)
    	rjmp  	KBD_CLEAR
KBD_L4_02:
	cpi	tdata, 0x14        	; ctrl
	brne  	KBD_L4_03          
    	sbr   	kbmdkey, (1<<CTRL)
    	rjmp  	KBD_CLEAR
KBD_L4_03:
	cpi	tdata, 0x11        	; ALT
	brne  	KBD_L4_04          
    	sbr   	kbmdkey, (1<<ALT)
    	rjmp  	KBD_CLEAR

KBD_L4_04:
;KBD_L4_not_alt:
	cpi	tdata, 0x58
	brne	KBD_L4_4          	; capslock
 	ldi	temp, 1<<CAPSLOCK
 	eor	kbmdkey, temp     	; toggle capslock
    	rjmp  	KBD_KBM_CLEAR

KBD_L4_4:
	cpi 	tdata, 0x7e
	brne	KBD_L4_5		; scrollock
	ldi	temp, 1<<SCRLOCK
	eor	kbmdkey, temp		
   	rjmp  	KBD_KBM_CLEAR

KBD_L4_5:   ; normal key pressed
            ; not modkey, decode and store
        andi	tdata, 0x7f		; clear 7th bit just for the case
	ldi	ZH, high(2*KBCHARS)
	mov	ZL, tdata
	sbrc	kbmdkey, CTRL
	sbr	ZL, 0x80
	sbrc	kbmdkey, SHIFT
	inc	ZH
	ldi	temp, 2
	sbrc	kbmdkey, SCRLOCK
	add	ZH, temp
	ldi	temp, 4
	sbrc	kbmdkey, ALT
	add	ZH, temp
	lpm	temp, Z			; char code

	sbrs	kbmdkey, CAPSLOCK
	rjmp	KBD_L4_no_capslock	; no CAPSLOCK

	ldi	ZH, high(2*CLtranslate) ; decoding CAPSLOCK
	mov	ZL, temp
	lpm	temp, Z                 ; char code

KBD_L4_no_capslock:
	sts	kmodk, kbmdkey   	; store modkeys
  	sts	kactk, tdata		; store scancode
	sts	kchar, temp		; store char

  	sbi	GPIOR0, IRQ_KBD		; set keyboard irq
;  	ldi	temp, 0x81
;  	ori	temp, (1<<IRQ_KBD)|(1<<IRQ_REQUEST)	; keyboard interrupt
;  	sts	irqfl, temp

;	lds	tdata, irqfl
;	MEM_HEX 0x0106

    	rjmp  	KBD_CLEAR

KBD_KBM_CLEAR:
	sts	kmodk, kbmdkey   	; store modkeys
  	inc	kbledr			; request to change led state
	ldi	temp, 0xed		; data to send
	mov	kbldata, temp

KBD_CLEAR:
    	cbr   	kbmdkey, (1<<EV_E0)|(1<<EV_F0)

;	lds	tdata, irqfl
;	MEM_HEX 0x010e
  	
  	rjmp	KBD_EXIT

KBD_END:                     		; dummy jump
	rjmp	KBD_EXIT


