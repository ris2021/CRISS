
	; set pattern
APPLY_PATTERN:
;	mov	XH, _zh
	in	XH, TCNT1H
;	mov	XL, _zl		; "old" line here
	in	XL, TCNT1L

;	ldi	XH, high(CATR)
;	ldi	XL, low(CATR)	; old line here

	ldi	ZH, high(PBUF)
	ldi	ZL, low(PBUF)	; new line will be built here

	clr	temp		; start char counter
	clr	temp4		; reset target block counter
_ap_start:
	ld	temp2, X
	PT_GET_LEN temp2	; temp2 = char counter for the block

	mov	temp3, temp	; prev counter
	add	temp3, temp2	; last position

	cp	temp3, pos_x	; reached point to update?
	breq	_ap_s_l1	; block will be skipped
	brsh	_ap_found	; fond block has to be updated

_ap_s_l1:
	ld	temp2, X
	st	Z, temp2	; just copy block
	mov	temp, temp3	; update position
	adiw	Z, 1		; next block
	adiw	X, 1		; next block

	cp	XL, temp6	; end reached?
	brne	_ap_start	; process next block	
	rjmp	_ap_finalize

_ap_found:

	mov	temp2, pos_x
	sub	temp2, temp	; first part of the block
	mov	temp3, temp2	; first part length

;	cpi	temp3, 0
;	breq	_ap_found_l1	; beginning of the block, no first chunk

;	mov	temp5, temp3
	ld	temp5, X	; first chunk
	PT_GET_LEN temp5; temp2 = char counter for the block
	sub	temp5, temp3	; rest of the block length
	
	cpi	temp3, 0
	breq	_ap_found_l1	; beginning of the block, no first chunk

	add	temp, temp3	; update position

	ld	temp2, X	; first chunk
	andi	temp2, 0x87	; color only
	dec	temp3
	lsl	temp3
	lsl	temp3
	lsl	temp3		; temp3 = length of the 1st chunk shifted left
	or	temp2, temp3	; block to store
	rcall	ADDPATTERN

_ap_found_l1:	
;	mov	temp, pos_x	; place to insert new block
;	lds	temp2, PVAL	
	in	temp2, GPIOR2	; PVAL
	rcall	ADDPATTERN	; new block

;	lds	temp2, PVAL	
	in	temp2, GPIOR2	; PVAL
	PT_GET_LEN temp2	; temp2 = char counter for the block
	add	temp, temp2

_ap_found_l3:
	cp	temp5, temp2	; rest compare with new block length
	brsh	_ap_found_l2

	sub	temp2, temp5	; 
	adiw	X, 1		; ignore rest of the block - go to next one
	cp	XL, temp6	; end reached?
	breq	_ap_finalize

;	lds	temp5, PVAL	
;	in	temp5, GPIOR2   ; PVAL	
	ld	temp5, X
	PT_GET_LEN temp5	; temp5 = char counter for the block

	rjmp	_ap_found_l3

_ap_found_l2:
	sub	temp5, temp2	; rest
	breq	_ap_go_cend	; zero length - nothing to store

	add	temp, temp5		; update char counter
	ld	temp2, X	; 
	andi	temp2, 0x87	; color only
	dec	temp5
	lsl	temp5
	lsl	temp5
	lsl	temp5		; 
	or	temp2, temp5	; block to store
	rcall	ADDPATTERN

_ap_go_cend:
	cp	XL, temp6	; end reached?
	breq	_ap_finalize

	cpi	temp, 80
	brsh	_ap_finalize

	adiw	X, 1		; next one

	ld	temp2, X	; current old block
	rcall	ADDPATTERN
	ld	temp2, X	; current old block
	PT_GET_LEN temp2	; temp2 = char counter for the block
	add	temp, temp2

	rjmp	_ap_go_cend	; process next block

_ap_finalize:
_ap_check:
	cpi	temp, 80
	brsh	_ap_end

_ap_repair:
	sbiw	Z,1	; last block
	ld	temp2, Z
	cbr	temp2, 0x80
	lsr	temp2
	lsr	temp2
	lsr	temp2
	inc	temp2	; length of the last block
	subi	temp2, 0x10	; 16 = max length
	neg	temp2	; max chrs to add
	andi	temp2, 0x0f	; no place to add	; 

	mov	temp3, temp
	subi	temp3, 80
	neg	temp3	; chars need to be added
	cp	temp3, temp2
	brsh	_ap_rp_l1
	mov	temp2, temp3	; chars to add
_ap_rp_l1:
	add	temp, temp2	; update char counter
	ld	temp3, Z	; get current value
	lsl	temp2
	lsl	temp2
	lsl	temp2
	add	temp3, temp2	; set new value
	st	Z, temp3	; store new value
	rjmp	_ap_check

_ap_end:
	ret	

; add new pattern in temp2
ADDPATTERN:
	sbr	temp2, 0x80	; just for the case
	st	Z+, temp2	; store new chunk
	inc	temp4		; inc block couter

	cpi	temp4, 1	; first block?
	breq	_ap_ahead	; nothing to check

	mov	tmp0, temp2
	mov	tmp1, temp3	; store for future restore
	sbiw	Z, 2		; AVR doesn't support Z-x :(

	andi	temp2, 0x07	; last color, temp2 is stored to Z-1

	ldd	temp3, Z+0	; get previous pattern from Z-2
	andi	temp3, 0x07	; get color

	cp	temp2, temp3	; is the same color?
	brne	_ap_l1	; not the same - no action

	ldd	temp3, Z+0	; get previous pattern
	ldd	temp2, Z+1	; get last pattern
	andi	temp2, 0x78	; hide color and 7th bit
	subi	temp2, -8	; set +1 to the char counter
	add	temp3, temp2	; try to combine

	brpl	_ap_l2		; overflow - 7th bit was cleared

	std	Z+0, temp3	; no overflow - save combined pattern
	dec	temp4		; block counter
	sbiw	Z, 1		; remove last block

	rjmp	_ap_l1		; proceed

_ap_l2:
	ldd	temp2, Z+0	; get previous pattern
	ori	temp2, 0xF8	; set its length to max
	std	Z+0, temp2	; store it

	mov	temp2, temp3	; get overflowed 
	sbr	temp2, 0x80	; set 7th bit back
	std	Z+1, temp2	; store updated last block

_ap_l1:
	mov	temp2, tmp0
	mov	temp3, tmp1	; restore counters
	adiw	Z, 2		; restore Z

_ap_ahead:
	cpi	temp4, N_BLOCKS
	brlo	_ap_ap_end

	pop	temp4
	pop	temp4		; get out return pointer
	rjmp	_ap_check	; return to check procedure

_ap_ap_end:
	ret	



PATTERN_COPY_LINE_BUF:
	ldi	ZH, high(CATR)
	ldi	ZL, low(CATR)	; copy FROM
	mov	temp, pos_y
	cpi	temp, 0
	breq	_ap_copy
_ap_loop:
	adiw	Z, N_BLOCKS	; 20 blocks count
	dec	temp
	brne	_ap_loop	; goto pos_y string
_ap_copy:
	out	TCNT1H, ZH
	out	TCNT1L, ZL
;	mov	_zh, ZH
;	mov	_zl, ZL		; start address - story for future use

;	ldi	XH, high(PBUF)
;	ldi	XL, low(PBUF)	; copy TO

	mov	temp6, ZL
	ldi	temp, N_BLOCKS
	add	temp6, temp	; end of the active line marker

	ret



PATTERN_COPY_BUF_LINE:
	in	ZH, TCNT1H
;	mov	ZH, _zh
;	mov	ZL, _zl		; restore - copy TO
	in	ZL, TCNT1L

	ldi	XH, high(PBUF)
	ldi	XL, low(PBUF)	; copy FROM

	ld	temp, X+
	std	Z+0, temp
	ld	temp, X+
	std	Z+1, temp
	ld	temp, X+
	std	Z+2, temp
	ld	temp, X+
	std	Z+3, temp
	ld	temp, X+
	std	Z+4, temp
	ld	temp, X+
	std	Z+5, temp
	ld	temp, X+
	std	Z+6, temp
	ld	temp, X+
	std	Z+7, temp
	ld	temp, X+
	std	Z+8, temp
	ld	temp, X+
	std	Z+9, temp
	ld	temp, X+
	std	Z+10, temp
	ld	temp, X+
	std	Z+11, temp
	ld	temp, X+
	std	Z+12, temp
	ld	temp, X+
	std	Z+13, temp
	ld	temp, X+
	std	Z+14, temp
	ld	temp, X+
	std	Z+15, temp
	ld	temp, X+
	std	Z+16, temp
	ld	temp, X+
	std	Z+17, temp
	ld	temp, X+
	std	Z+18, temp
	ld	temp, X+
	std	Z+19, temp

	ret

