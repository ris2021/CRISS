FLOAT:

;	ret

	push	r0
	push	r1
	push	r2
	push	r3
	push	r4
	push	r5
	push	r6
	push	r7
	push	r8
	push	r9
	push	r10
	push	r11
	push	r12
	push	r13
	push	r14
	push	r15
	push	r16
	push	r17
	push	r18
	push	r19
	push	r20
	push	r21
	push	r22
	push	r23
	push	r24
	push	r25
	push	r26
	push	r27
	push	r28
	push	r29
;	push	r30
;	push	r31

	in	r28, SPL
	in	r29, SPH
	in	r0, SREG
	sts	FLOATSPL, r28	; store SPL
	sts	FLOATSPH, r29	; store SPH
	sts	FLOATSREG, r0	; store SREG

	; set new stack for float routines
	in	r0, SREG
	ldi	r29, high(FLOATSTACK)
	ldi	r28, low(FLOATSTACK)
	cli
 	out	SPH, r29	
 	out	SREG, r0	
	out	SPL, r28	; new stack for float operations

	lds	r17, FLIB_CMD

	cpi	r17, 16
	brsh	_fl_pr48

	lds	r22, FLOATDATA1+0	
	lds	r23, FLOATDATA1+1
	lds	r24, FLOATDATA1+2
	lds	r25, FLOATDATA1+3

	lds	r18, FLOATDATA2+0
	lds	r19, FLOATDATA2+1
	lds	r20, FLOATDATA2+2
	lds	r21, FLOATDATA2+3
	rjmp	_fl_pr_end
_fl_pr48:
	;!!! code here!!!
_fl_pr_end:

;	sts	FLIB_CMD, one
	clr	r1
	clr	r0
	ori	r17, 0x80		; mark that processed

	cpi	r17, 0x80+0
	brne	_fl_c1
	sts	FLIB_CMD, r17
	rcall	FLOAT_SUM
	rjmp	_fl_done
_fl_c1:
	cpi	r17, 0x80+1
	brne	_fl_c2
	sts	FLIB_CMD, r17
	rcall	FLOAT_SUB
	rjmp	_fl_done
_fl_c2:
	cpi	r17, 0x80+2
	brne	_fl_c3
	sts	FLIB_CMD, r17
	rcall	FLOAT_MUL
	rjmp	_fl_done
_fl_c3:
	cpi	r17, 0x80+3
	brne	_fl_c4
	sts	FLIB_CMD, r17
	rcall	FLOAT_DIV
	rjmp	_fl_done
_fl_c4:
	ldi	r17, 64
	sts	FLIB_CMD, r17		; error
	rjmp	_fl_st_end
	
_fl_done:

	lds	r17, FLIB_CMD
        cbr	r17, 0x80

	cpi	r17, 16
	brsh	_fl_st48
	sts	FLOATDATA3+0, r22
	sts	FLOATDATA3+1, r23
	sts	FLOATDATA3+2, r24
	sts	FLOATDATA3+3, r25
	rjmp	_fl_st_end
_fl_st48:
	;!!! code here
_fl_st_end:
		
	lds	r0, FLOATSREG
	lds	r29, FLOATSPH
	lds	r28, FLOATSPL
	cli
 	out	SPH, r29	
 	out	SREG, r0	
	out	SPL, r28	
	
	pop	r29
	pop	r28
	pop	r27
	pop	r26
	pop	r25
	pop	r24
	pop	r23
	pop	r22
	pop	r21
	pop	r20
	pop	r19
	pop	r18
	pop	r17
	pop	r16
	pop	r15
	pop	r14
	pop	r13
	pop	r12
	pop	r11
	pop	r10
	pop	r9
	pop	r8
	pop	r7
	pop	r6
	pop	r5
	pop	r4
	pop	r3
	pop	r2
	pop	r1
	pop	r0

	ret


FLOAT_zCMD:
	push	zzH
	push	zzL
	push	temp

	LDRAM	zzH, zzL, temp		; load (HL) -> FLOATDATA1
	sts	FLOATDATA1+0, temp
	add	zzL, one
	adc	zzH, zero
	LDRAM	zzH, zzL, temp
	sts	FLOATDATA1+1, temp
	add	zzL, one
	adc	zzH, zero
	LDRAM	zzH, zzL, temp
	sts	FLOATDATA1+2, temp
	add	zzL, one
	adc	zzH, zero
	LDRAM	zzH, zzL, temp
	sts	FLOATDATA1+3, temp

	mov	zzH, zzB
	mov	zzL, zzC

	LDRAM	zzH, zzL, temp		; load (BC) -> FLOATDATA2
	sts	FLOATDATA2+0, temp
	add	zzL, one
	adc	zzH, zero
	LDRAM	zzH, zzL, temp
	sts	FLOATDATA2+1, temp
	add	zzL, one
	adc	zzH, zero
	LDRAM	zzH, zzL, temp
	sts	FLOATDATA2+2, temp
	add	zzL, one
	adc	zzH, zero
	LDRAM	zzH, zzL, temp
	sts	FLOATDATA2+3, temp

	pop	temp
	pop	zzL
	pop	zzH

	sts	FLIB_CMD, temp		; commant to execute
	rcall	FLOAT

	push	zzH
	push	zzL
	push	temp

	lds	temp, FLOATDATA3+0
	STRAM	zzH, zzL, temp
	add	zzL, one
	adc	zzH, zero
	lds	temp, FLOATDATA3+1
	STRAM	zzH, zzL, temp
	add	zzL, one
	adc	zzH, zero
	lds	temp, FLOATDATA3+2
	STRAM	zzH, zzL, temp
	add	zzL, one
	adc	zzH, zero
	lds	temp, FLOATDATA3+3
	STRAM	zzH, zzL, temp

	pop	temp
	pop	zzL
	pop	zzH
	
	ret


#include "flb2.asm"	; float library

