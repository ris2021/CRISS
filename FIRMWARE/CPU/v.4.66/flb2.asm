
fl_184:	ldi	r26, 0x00	; 0
fl_186:	ldi	r27, 0x00	; 0
fl_188:	ldi	r30, low(fl_190) ;0xC8	; 200
fl_18a:	ldi	r31, high(fl_190) 	; 0
fl_18c:	jmp	fl_abe	;  0xabe
fl_190:	movw	r26, r24
fl_192:	movw	r4, r22
fl_194:	movw	r30, r20
fl_196:	ld	r25, X
fl_198:	cpi	r25, 0x02	; 2
fl_19a:	brcc	fl_19e
fl_19c:	rjmp	fl_410
fl_19e:	movw	r28, r22
fl_1a0:	ld	r24, Y
fl_1a2:	cpi	r24, 0x02	; 2
fl_1a4:	brcc	fl_1a8
fl_1a6:	rjmp	fl_40e
fl_1a8:	cpi	r25, 0x04	; 4
fl_1aa:	brne	fl_1c6
fl_1ac:	cpi	r24, 0x04	; 4
fl_1ae:	breq	fl_1b2
fl_1b0:	rjmp	fl_410
fl_1b2:	adiw	r26, 0x01	; 1
fl_1b4:	ld	r25, X
fl_1b6:	sbiw	r26, 0x01	; 1
fl_1b8:	ldd	r24, Y+1	; 0x01
fl_1ba:	cp	r25, r24
fl_1bc:	brne	fl_1c0
fl_1be:	rjmp	fl_410
fl_1c0:	ldi	r26, 0x00	; 0
fl_1c2:	ldi	r27, 0x01	; 1
fl_1c4:	rjmp	fl_410
fl_1c6:	cpi	r24, 0x04	; 4
fl_1c8:	brne	fl_1cc
fl_1ca:	rjmp	fl_40e
fl_1cc:	cpi	r24, 0x02	; 2
fl_1ce:	brne	fl_1fa
fl_1d0:	cpi	r25, 0x02	; 2
fl_1d2:	breq	fl_1d6
fl_1d4:	rjmp	fl_410
fl_1d6:	movw	r18, r20
fl_1d8:	movw	r20, r26
fl_1da:	ldi	r24, 0x08	; 8
fl_1dc:	movw	r28, r20
fl_1de:	ld	r0, Y+
fl_1e0:	movw	r20, r28
fl_1e2:	movw	r28, r18
fl_1e4:	st	Y+, r0
fl_1e6:	movw	r18, r28
fl_1e8:	subi	r24, 0x01	; 1
fl_1ea:	brne	fl_1dc
fl_1ec:	movw	r28, r4
fl_1ee:	ldd	r24, Y+1	; 0x01
fl_1f0:	adiw	r26, 0x01	; 1
fl_1f2:	ld	r25, X
fl_1f4:	and	r24, r25
fl_1f6:	std	Z+1, r24	; 0x01
fl_1f8:	rjmp	fl_40a
fl_1fa:	cpi	r25, 0x02	; 2
fl_1fc:	brne	fl_200
fl_1fe:	rjmp	fl_40e
fl_200:	adiw	r26, 0x02	; 2
fl_202:	ld	r2, X+
fl_204:	ld	r3, X
fl_206:	sbiw	r26, 0x03	; 3
fl_208:	movw	r28, r22
fl_20a:	ldd	r24, Y+2	; 0x02
fl_20c:	ldd	r25, Y+3	; 0x03
fl_20e:	adiw	r26, 0x04	; 4
fl_210:	ld	r10, X+
fl_212:	ld	r11, X+
fl_214:	ld	r12, X+
fl_216:	ld	r13, X
fl_218:	sbiw	r26, 0x07	; 7
fl_21a:	ldd	r14, Y+4	; 0x04
fl_21c:	ldd	r15, Y+5	; 0x05
fl_21e:	ldd	r16, Y+6	; 0x06
fl_220:	ldd	r17, Y+7	; 0x07
fl_222:	movw	r18, r2
fl_224:	sub	r18, r24
fl_226:	sbc	r19, r25
fl_228:	movw	r22, r18
fl_22a:	sbrs	r19, 7
fl_22c:	rjmp	fl_236
fl_22e:	eor	r22, r22
fl_230:	eor	r23, r23
fl_232:	sub	r22, r18
fl_234:	sbc	r23, r19
fl_236:	cpi	r22, 0x20	; 32
fl_238:	cpc	r23, r1
fl_23a:	brlt	fl_23e
fl_23c:	rjmp	fl_300
fl_23e:	cp	r1, r18
fl_240:	cpc	r1, r19
fl_242:	brge	fl_29e
fl_244:	movw	r6, r14
fl_246:	movw	r8, r16
fl_248:	mov	r0, r22
fl_24a:	rjmp	fl_254
fl_24c:	lsr	r9
fl_24e:	ror	r8
fl_250:	ror	r7
fl_252:	ror	r6
fl_254:	dec	r0
fl_256:	brpl	fl_24c
fl_258:	ldi	r18, 0x01	; 1
fl_25a:	ldi	r19, 0x00	; 0
fl_25c:	ldi	r20, 0x00	; 0
fl_25e:	ldi	r21, 0x00	; 0
fl_260:	rjmp	fl_26a
fl_262:	add	r18, r18
fl_264:	adc	r19, r19
fl_266:	adc	r20, r20
fl_268:	adc	r21, r21
fl_26a:	dec	r22
fl_26c:	brpl	fl_262
fl_26e:	subi	r18, 0x01	; 1
fl_270:	sbci	r19, 0x00	; 0
fl_272:	sbci	r20, 0x00	; 0
fl_274:	sbci	r21, 0x00	; 0
fl_276:	and	r18, r14
fl_278:	and	r19, r15
fl_27a:	and	r20, r16
fl_27c:	and	r21, r17
fl_27e:	cp	r18, r1
fl_280:	cpc	r19, r1
fl_282:	cpc	r20, r1
fl_284:	cpc	r21, r1
fl_286:	breq	fl_290
fl_288:	ldi	r18, 0x01	; 1
fl_28a:	ldi	r19, 0x00	; 0
fl_28c:	ldi	r20, 0x00	; 0
fl_28e:	ldi	r21, 0x00	; 0
fl_290:	movw	r14, r18
fl_292:	movw	r16, r20
fl_294:	or	r14, r6
fl_296:	or	r15, r7
fl_298:	or	r16, r8
fl_29a:	or	r17, r9
fl_29c:	rjmp	fl_316
fl_29e:	or	r18, r19
fl_2a0:	breq	fl_316
fl_2a2:	add	r2, r22
fl_2a4:	adc	r3, r23
fl_2a6:	movw	r6, r10
fl_2a8:	movw	r8, r12
fl_2aa:	mov	r0, r22
fl_2ac:	rjmp	fl_2b6
fl_2ae:	lsr	r9
fl_2b0:	ror	r8
fl_2b2:	ror	r7
fl_2b4:	ror	r6
fl_2b6:	dec	r0
fl_2b8:	brpl	fl_2ae
fl_2ba:	ldi	r18, 0x01	; 1
fl_2bc:	ldi	r19, 0x00	; 0
fl_2be:	ldi	r20, 0x00	; 0
fl_2c0:	ldi	r21, 0x00	; 0
fl_2c2:	rjmp	fl_2cc
fl_2c4:	add	r18, r18
fl_2c6:	adc	r19, r19
fl_2c8:	adc	r20, r20
fl_2ca:	adc	r21, r21
fl_2cc:	dec	r22
fl_2ce:	brpl	fl_2c4
fl_2d0:	subi	r18, 0x01	; 1
fl_2d2:	sbci	r19, 0x00	; 0
fl_2d4:	sbci	r20, 0x00	; 0
fl_2d6:	sbci	r21, 0x00	; 0
fl_2d8:	and	r18, r10
fl_2da:	and	r19, r11
fl_2dc:	and	r20, r12
fl_2de:	and	r21, r13
fl_2e0:	cp	r18, r1
fl_2e2:	cpc	r19, r1
fl_2e4:	cpc	r20, r1
fl_2e6:	cpc	r21, r1
fl_2e8:	breq	fl_2f2
fl_2ea:	ldi	r18, 0x01	; 1
fl_2ec:	ldi	r19, 0x00	; 0
fl_2ee:	ldi	r20, 0x00	; 0
fl_2f0:	ldi	r21, 0x00	; 0
fl_2f2:	movw	r10, r18
fl_2f4:	movw	r12, r20
fl_2f6:	or	r10, r6
fl_2f8:	or	r11, r7
fl_2fa:	or	r12, r8
fl_2fc:	or	r13, r9
fl_2fe:	rjmp	fl_316
fl_300:	cp	r24, r2
fl_302:	cpc	r25, r3
fl_304:	brlt	fl_310
fl_306:	movw	r2, r24
fl_308:	eor	r10, r10
fl_30a:	eor	r11, r11
fl_30c:	movw	r12, r10
fl_30e:	rjmp	fl_316
fl_310:	eor	r14, r14
fl_312:	eor	r15, r15
fl_314:	movw	r16, r14
fl_316:	adiw	r26, 0x01	; 1
fl_318:	ld	r25, X
fl_31a:	movw	r26, r4
fl_31c:	adiw	r26, 0x01	; 1
fl_31e:	ld	r24, X
fl_320:	cp	r25, r24
fl_322:	brne	fl_326
fl_324:	rjmp	fl_3b0
fl_326:	and	r25, r25
fl_328:	breq	fl_338
fl_32a:	movw	r20, r16
fl_32c:	movw	r18, r14
fl_32e:	sub	r18, r10
fl_330:	sbc	r19, r11
fl_332:	sbc	r20, r12
fl_334:	sbc	r21, r13
fl_336:	rjmp	fl_344
fl_338:	movw	r20, r12
fl_33a:	movw	r18, r10
fl_33c:	sub	r18, r14
fl_33e:	sbc	r19, r15
fl_340:	sbc	r20, r16
fl_342:	sbc	r21, r17
fl_344:	sbrc	r21, 7
fl_346:	rjmp	fl_358
fl_348:	std	Z+1, r1	; 0x01
fl_34a:	std	Z+3, r3	; 0x03
fl_34c:	std	Z+2, r2	; 0x02
fl_34e:	std	Z+4, r18	; 0x04
fl_350:	std	Z+5, r19	; 0x05
fl_352:	std	Z+6, r20	; 0x06
fl_354:	std	Z+7, r21	; 0x07
fl_356:	rjmp	fl_392
fl_358:	ldi	r24, 0x01	; 1
fl_35a:	std	Z+1, r24	; 0x01
fl_35c:	std	Z+3, r3	; 0x03
fl_35e:	std	Z+2, r2	; 0x02
fl_360:	eor	r24, r24
fl_362:	eor	r25, r25
fl_364:	movw	r26, r24
fl_366:	sub	r24, r18
fl_368:	sbc	r25, r19
fl_36a:	sbc	r26, r20
fl_36c:	sbc	r27, r21
fl_36e:	std	Z+4, r24	; 0x04
fl_370:	std	Z+5, r25	; 0x05
fl_372:	std	Z+6, r26	; 0x06
fl_374:	std	Z+7, r27	; 0x07
fl_376:	rjmp	fl_392
fl_378:	add	r18, r18
fl_37a:	adc	r19, r19
fl_37c:	adc	r20, r20
fl_37e:	adc	r21, r21
fl_380:	std	Z+4, r18	; 0x04
fl_382:	std	Z+5, r19	; 0x05
fl_384:	std	Z+6, r20	; 0x06
fl_386:	std	Z+7, r21	; 0x07
fl_388:	ldd	r24, Z+2	; 0x02
fl_38a:	ldd	r25, Z+3	; 0x03
fl_38c:	sbiw	r24, 0x01	; 1
fl_38e:	std	Z+3, r25	; 0x03
fl_390:	std	Z+2, r24	; 0x02
fl_392:	ldd	r18, Z+4	; 0x04
fl_394:	ldd	r19, Z+5	; 0x05
fl_396:	ldd	r20, Z+6	; 0x06
fl_398:	ldd	r21, Z+7	; 0x07
fl_39a:	movw	r26, r20
fl_39c:	movw	r24, r18
fl_39e:	sbiw	r24, 0x01	; 1
fl_3a0:	sbc	r26, r1
fl_3a2:	sbc	r27, r1
fl_3a4:	subi	r24, 0xFF	; 255
fl_3a6:	sbci	r25, 0xFF	; 255
fl_3a8:	sbci	r26, 0xFF	; 255
fl_3aa:	sbci	r27, 0x3F	; 63
fl_3ac:	brcs	fl_378
fl_3ae:	rjmp	fl_3c6
fl_3b0:	std	Z+1, r25	; 0x01
fl_3b2:	std	Z+3, r3	; 0x03
fl_3b4:	std	Z+2, r2	; 0x02
fl_3b6:	add	r14, r10
fl_3b8:	adc	r15, r11
fl_3ba:	adc	r16, r12
fl_3bc:	adc	r17, r13
fl_3be:	std	Z+4, r14	; 0x04
fl_3c0:	std	Z+5, r15	; 0x05
fl_3c2:	std	Z+6, r16	; 0x06
fl_3c4:	std	Z+7, r17	; 0x07
fl_3c6:	ldi	r24, 0x03	; 3
fl_3c8:	st	Z, r24
fl_3ca:	ldd	r18, Z+4	; 0x04
fl_3cc:	ldd	r19, Z+5	; 0x05
fl_3ce:	ldd	r20, Z+6	; 0x06
fl_3d0:	ldd	r21, Z+7	; 0x07
fl_3d2:	sbrs	r21, 7
fl_3d4:	rjmp	fl_40a
fl_3d6:	movw	r24, r18
fl_3d8:	eor	r26, r26
fl_3da:	sbrc	r25, 7
fl_3dc:	com	r26
fl_3de:	mov	r27, r26
fl_3e0:	andi	r24, 0x01	; 1
fl_3e2:	andi	r25, 0x00	; 0
fl_3e4:	andi	r26, 0x00	; 0
fl_3e6:	andi	r27, 0x00	; 0
fl_3e8:	lsr	r21
fl_3ea:	ror	r20
fl_3ec:	ror	r19
fl_3ee:	ror	r18
fl_3f0:	or	r24, r18
fl_3f2:	or	r25, r19
fl_3f4:	or	r26, r20
fl_3f6:	or	r27, r21
fl_3f8:	std	Z+4, r24	; 0x04
fl_3fa:	std	Z+5, r25	; 0x05
fl_3fc:	std	Z+6, r26	; 0x06
fl_3fe:	std	Z+7, r27	; 0x07
fl_400:	ldd	r24, Z+2	; 0x02
fl_402:	ldd	r25, Z+3	; 0x03
fl_404:	adiw	r24, 0x01	; 1
fl_406:	std	Z+3, r25	; 0x03
fl_408:	std	Z+2, r24	; 0x02
fl_40a:	movw	r26, r30
fl_40c:	rjmp	fl_410
fl_40e:	movw	r26, r4
fl_410:	movw	r24, r26
fl_412:	in	r28, 0x3d	; 61
fl_414:	in	r29, 0x3e	; 62
fl_416:	ldi	r30, 0x12	; 18
fl_418:	jmp	fl_af6	;  0xaf6

FLOAT_SUB:
fl_41c:	ldi	r26, 0x20	; 32
fl_41e:	ldi	r27, 0x00	; 0
fl_420:	ldi	r30, low(fl_428) ;0x14	; 20
fl_422:	ldi	r31, high(fl_428); 0x02	; 2
fl_424:	jmp	fl_ad6	;  0xad6
fl_428:	std	Y+1, r22	; 0x01
fl_42a:	std	Y+2, r23	; 0x02
fl_42c:	std	Y+3, r24	; 0x03
fl_42e:	std	Y+4, r25	; 0x04
fl_430:	std	Y+5, r18	; 0x05
fl_432:	std	Y+6, r19	; 0x06
fl_434:	std	Y+7, r20	; 0x07
fl_436:	std	Y+8, r21	; 0x08
fl_438:	ldi	r30, 0x09	; 9
fl_43a:	mov	r14, r30
fl_43c:	mov	r15, r1
fl_43e:	add	r14, r28
fl_440:	adc	r15, r29
fl_442:	movw	r24, r28
fl_444:	adiw	r24, 0x01	; 1
fl_446:	movw	r22, r14
fl_448:	call	fl_9ce	;  0x9ce
fl_44c:	movw	r16, r28
fl_44e:	subi	r16, 0xEF	; 239
fl_450:	sbci	r17, 0xFF	; 255
fl_452:	movw	r24, r28
fl_454:	adiw	r24, 0x05	; 5
fl_456:	movw	r22, r16
fl_458:	call	fl_9ce	;  0x9ce
fl_45c:	ldd	r24, Y+18	; 0x12
fl_45e:	ldi	r25, 0x01	; 1
fl_460:	eor	r24, r25
fl_462:	std	Y+18, r24	; 0x12
fl_464:	movw	r24, r14
fl_466:	movw	r22, r16
fl_468:	movw	r20, r28
fl_46a:	subi	r20, 0xE7	; 231
fl_46c:	sbci	r21, 0xFF	; 255
fl_46e:	call	fl_184	;  0x184
fl_472:	call	fl_824	;  0x824
fl_476:	adiw	r28, 0x20	; 32
fl_478:	ldi	r30, 0x06	; 6
fl_47a:	jmp	fl_b0e	;  0xb0e

FLOAT_SUM:
fl_47e:	ldi	r26, 0x20	; 32
fl_480:	ldi	r27, 0x00	; 0
fl_482:	ldi	r30, low(fl_48a) ;0x45	; 69
fl_484:	ldi	r31, high(fl_48a); 0x02	; 2
fl_486:	jmp	fl_ad6	;  0xad6
fl_48a:	std	Y+1, r22	; 0x01
fl_48c:	std	Y+2, r23	; 0x02
fl_48e:	std	Y+3, r24	; 0x03
fl_490:	std	Y+4, r25	; 0x04
fl_492:	std	Y+5, r18	; 0x05
fl_494:	std	Y+6, r19	; 0x06
fl_496:	std	Y+7, r20	; 0x07
fl_498:	std	Y+8, r21	; 0x08
fl_49a:	ldi	r31, 0x09	; 9
fl_49c:	mov	r14, r31
fl_49e:	mov	r15, r1
fl_4a0:	add	r14, r28
fl_4a2:	adc	r15, r29
fl_4a4:	movw	r24, r28
fl_4a6:	adiw	r24, 0x01	; 1
fl_4a8:	movw	r22, r14
fl_4aa:	call	fl_9ce	;  0x9ce
fl_4ae:	movw	r16, r28
fl_4b0:	subi	r16, 0xEF	; 239
fl_4b2:	sbci	r17, 0xFF	; 255
fl_4b4:	movw	r24, r28
fl_4b6:	adiw	r24, 0x05	; 5
fl_4b8:	movw	r22, r16
fl_4ba:	call	fl_9ce	;  0x9ce
fl_4be:	movw	r24, r14
fl_4c0:	movw	r22, r16
fl_4c2:	movw	r20, r28
fl_4c4:	subi	r20, 0xE7	; 231
fl_4c6:	sbci	r21, 0xFF	; 255
fl_4c8:	call	fl_184	;  0x184
fl_4cc:	call	fl_824	;  0x824
fl_4d0:	adiw	r28, 0x20	; 32
fl_4d2:	ldi	r30, 0x06	; 6
fl_4d4:	jmp	fl_b0e	;  0xb0e

FLOAT_MUL:
fl_4d8:	ldi	r26, 0x20	; 32
fl_4da:	ldi	r27, 0x00	; 0
fl_4dc:	ldi	r30, low(fl_4e4);0x72	; 114
fl_4de:	ldi	r31, high(fl_4e4);0x02	; 2
fl_4e0:	jmp	fl_abe	;  0xabe
fl_4e4:	std	Y+1, r22	; 0x01
fl_4e6:	std	Y+2, r23	; 0x02
fl_4e8:	std	Y+3, r24	; 0x03
fl_4ea:	std	Y+4, r25	; 0x04
fl_4ec:	std	Y+5, r18	; 0x05
fl_4ee:	std	Y+6, r19	; 0x06
fl_4f0:	std	Y+7, r20	; 0x07
fl_4f2:	std	Y+8, r21	; 0x08
fl_4f4:	movw	r24, r28
fl_4f6:	adiw	r24, 0x01	; 1
fl_4f8:	movw	r22, r28
fl_4fa:	subi	r22, 0xF7	; 247
fl_4fc:	sbci	r23, 0xFF	; 255
fl_4fe:	call	fl_9ce	;  0x9ce
fl_502:	movw	r24, r28
fl_504:	adiw	r24, 0x05	; 5
fl_506:	movw	r22, r28
fl_508:	subi	r22, 0xEF	; 239
fl_50a:	sbci	r23, 0xFF	; 255
fl_50c:	call	fl_9ce	;  0x9ce
fl_510:	ldd	r25, Y+9	; 0x09
fl_512:	cpi	r25, 0x02	; 2
fl_514:	brcs	fl_538
fl_516:	ldd	r24, Y+17	; 0x11
fl_518:	cpi	r24, 0x02	; 2
fl_51a:	brcs	fl_54e
fl_51c:	cpi	r25, 0x04	; 4
fl_51e:	brne	fl_526
fl_520:	cpi	r24, 0x02	; 2
fl_522:	brne	fl_538
fl_524:	rjmp	fl_52e
fl_526:	cpi	r24, 0x04	; 4
fl_528:	brne	fl_534
fl_52a:	cpi	r25, 0x02	; 2
fl_52c:	brne	fl_54e
fl_52e:	ldi	r24, 0x00	; 0
fl_530:	ldi	r25, 0x01	; 1
fl_532:	rjmp	fl_6c0
fl_534:	cpi	r25, 0x02	; 2
fl_536:	brne	fl_54a
fl_538:	ldi	r18, 0x00	; 0
fl_53a:	ldd	r25, Y+10	; 0x0a
fl_53c:	ldd	r24, Y+18	; 0x12
fl_53e:	cpse	r25, r24
fl_540:	ldi	r18, 0x01	; 1
fl_542:	std	Y+10, r18	; 0x0a
fl_544:	movw	r24, r28
fl_546:	adiw	r24, 0x09	; 9
fl_548:	rjmp	fl_6c0
fl_54a:	cpi	r24, 0x02	; 2
fl_54c:	brne	fl_560
fl_54e:	ldi	r18, 0x00	; 0
fl_550:	ldd	r25, Y+10	; 0x0a
fl_552:	ldd	r24, Y+18	; 0x12
fl_554:	cpse	r25, r24
fl_556:	ldi	r18, 0x01	; 1
fl_558:	std	Y+18, r18	; 0x12
fl_55a:	movw	r24, r28
fl_55c:	adiw	r24, 0x11	; 17
fl_55e:	rjmp	fl_6c0
fl_560:	ldd	r2, Y+13	; 0x0d
fl_562:	ldd	r3, Y+14	; 0x0e
fl_564:	ldd	r4, Y+15	; 0x0f
fl_566:	ldd	r5, Y+16	; 0x10
fl_568:	ldd	r6, Y+21	; 0x15
fl_56a:	ldd	r7, Y+22	; 0x16
fl_56c:	ldd	r8, Y+23	; 0x17
fl_56e:	ldd	r9, Y+24	; 0x18
fl_570:	eor	r14, r14
fl_572:	eor	r15, r15
fl_574:	movw	r16, r14
fl_576:	eor	r10, r10
fl_578:	eor	r11, r11
fl_57a:	movw	r12, r10
fl_57c:	ldi	r20, 0x00	; 0
fl_57e:	ldi	r21, 0x00	; 0
fl_580:	ldi	r22, 0x00	; 0
fl_582:	ldi	r23, 0x00	; 0
fl_584:	ldi	r30, 0x00	; 0
fl_586:	ldi	r31, 0x00	; 0
fl_588:	movw	r24, r2
fl_58a:	andi	r24, 0x01	; 1
fl_58c:	andi	r25, 0x00	; 0
fl_58e:	or	r24, r25
fl_590:	breq	fl_5cc
fl_592:	add	r14, r6
fl_594:	adc	r15, r7
fl_596:	adc	r16, r8
fl_598:	adc	r17, r9
fl_59a:	movw	r18, r20
fl_59c:	movw	r20, r22
fl_59e:	add	r18, r10
fl_5a0:	adc	r19, r11
fl_5a2:	adc	r20, r12
fl_5a4:	adc	r21, r13
fl_5a6:	ldi	r24, 0x00	; 0
fl_5a8:	ldi	r25, 0x00	; 0
fl_5aa:	ldi	r26, 0x00	; 0
fl_5ac:	ldi	r27, 0x00	; 0
fl_5ae:	cp	r14, r6
fl_5b0:	cpc	r15, r7
fl_5b2:	cpc	r16, r8
fl_5b4:	cpc	r17, r9
fl_5b6:	brcc	fl_5c0
fl_5b8:	ldi	r24, 0x01	; 1
fl_5ba:	ldi	r25, 0x00	; 0
fl_5bc:	ldi	r26, 0x00	; 0
fl_5be:	ldi	r27, 0x00	; 0
fl_5c0:	movw	r22, r20
fl_5c2:	movw	r20, r18
fl_5c4:	add	r20, r24
fl_5c6:	adc	r21, r25
fl_5c8:	adc	r22, r26
fl_5ca:	adc	r23, r27
fl_5cc:	add	r10, r10
fl_5ce:	adc	r11, r11
fl_5d0:	adc	r12, r12
fl_5d2:	adc	r13, r13
fl_5d4:	sbrs	r9, 7
fl_5d6:	rjmp	fl_5e8
fl_5d8:	ldi	r24, 0x01	; 1
fl_5da:	ldi	r25, 0x00	; 0
fl_5dc:	ldi	r26, 0x00	; 0
fl_5de:	ldi	r27, 0x00	; 0
fl_5e0:	or	r10, r24
fl_5e2:	or	r11, r25
fl_5e4:	or	r12, r26
fl_5e6:	or	r13, r27
fl_5e8:	adiw	r30, 0x01	; 1
fl_5ea:	cpi	r30, 0x20	; 32
fl_5ec:	cpc	r31, r1
fl_5ee:	breq	fl_602
fl_5f0:	add	r6, r6
fl_5f2:	adc	r7, r7
fl_5f4:	adc	r8, r8
fl_5f6:	adc	r9, r9
fl_5f8:	lsr	r5
fl_5fa:	ror	r4
fl_5fc:	ror	r3
fl_5fe:	ror	r2
fl_600:	rjmp	fl_588
fl_602:	ldd	r31, Y+10	; 0x0a
fl_604:	ldd	r30, Y+18	; 0x12
fl_606:	ldd	r18, Y+19	; 0x13
fl_608:	ldd	r19, Y+20	; 0x14
fl_60a:	ldd	r24, Y+11	; 0x0b
fl_60c:	ldd	r25, Y+12	; 0x0c
fl_60e:	add	r18, r24
fl_610:	adc	r19, r25
fl_612:	subi	r18, 0xFE	; 254
fl_614:	sbci	r19, 0xFF	; 255
fl_616:	rjmp	fl_646
fl_618:	movw	r24, r20
fl_61a:	andi	r24, 0x01	; 1
fl_61c:	andi	r25, 0x00	; 0
fl_61e:	or	r24, r25
fl_620:	breq	fl_63a
fl_622:	lsr	r17
fl_624:	ror	r16
fl_626:	ror	r15
fl_628:	ror	r14
fl_62a:	ldi	r24, 0x00	; 0
fl_62c:	ldi	r25, 0x00	; 0
fl_62e:	ldi	r26, 0x00	; 0
fl_630:	ldi	r27, 0x80	; 128
fl_632:	or	r14, r24
fl_634:	or	r15, r25
fl_636:	or	r16, r26
fl_638:	or	r17, r27
fl_63a:	lsr	r23
fl_63c:	ror	r22
fl_63e:	ror	r21
fl_640:	ror	r20
fl_642:	subi	r18, 0xFF	; 255
fl_644:	sbci	r19, 0xFF	; 255
fl_646:	sbrc	r23, 7
fl_648:	rjmp	fl_618
fl_64a:	rjmp	fl_664
fl_64c:	add	r20, r20
fl_64e:	adc	r21, r21
fl_650:	adc	r22, r22
fl_652:	adc	r23, r23
fl_654:	sbrc	r17, 7
fl_656:	ori	r20, 0x01	; 1
fl_658:	add	r14, r14
fl_65a:	adc	r15, r15
fl_65c:	adc	r16, r16
fl_65e:	adc	r17, r17
fl_660:	subi	r18, 0x01	; 1
fl_662:	sbci	r19, 0x00	; 0
fl_664:	cpi	r20, 0x00	; 0
fl_666:	ldi	r25, 0x00	; 0
fl_668:	cpc	r21, r25
fl_66a:	ldi	r25, 0x00	; 0
fl_66c:	cpc	r22, r25
fl_66e:	ldi	r25, 0x40	; 64
fl_670:	cpc	r23, r25
fl_672:	brcs	fl_64c
fl_674:	std	Y+27, r18	; 0x1b
fl_676:	std	Y+28, r19	; 0x1c
fl_678:	movw	r26, r22
fl_67a:	movw	r24, r20
fl_67c:	andi	r24, 0x7F	; 127
fl_67e:	andi	r25, 0x00	; 0
fl_680:	andi	r26, 0x00	; 0
fl_682:	andi	r27, 0x00	; 0
fl_684:	cpi	r24, 0x40	; 64
fl_686:	cpc	r25, r1
fl_688:	cpc	r26, r1
fl_68a:	cpc	r27, r1
fl_68c:	brne	fl_6a6
fl_68e:	sbrc	r20, 7
fl_690:	rjmp	fl_6a6
fl_692:	cp	r14, r1
fl_694:	cpc	r15, r1
fl_696:	cpc	r16, r1
fl_698:	cpc	r17, r1
fl_69a:	breq	fl_6a6
fl_69c:	subi	r20, 0xC0	; 192
fl_69e:	sbci	r21, 0xFF	; 255
fl_6a0:	sbci	r22, 0xFF	; 255
fl_6a2:	sbci	r23, 0xFF	; 255
fl_6a4:	andi	r20, 0x80	; 128
fl_6a6:	std	Y+26, r1	; 0x1a
fl_6a8:	cp	r31, r30
fl_6aa:	breq	fl_6b0
fl_6ac:	ldi	r24, 0x01	; 1
fl_6ae:	std	Y+26, r24	; 0x1a
fl_6b0:	std	Y+29, r20	; 0x1d
fl_6b2:	std	Y+30, r21	; 0x1e
fl_6b4:	std	Y+31, r22	; 0x1f
fl_6b6:	std	Y+32, r23	; 0x20
fl_6b8:	ldi	r24, 0x03	; 3
fl_6ba:	std	Y+25, r24	; 0x19
fl_6bc:	movw	r24, r28
fl_6be:	adiw	r24, 0x19	; 25
fl_6c0:	call	fl_824	;  0x824
fl_6c4:	adiw	r28, 0x20	; 32
fl_6c6:	ldi	r30, 0x12	; 18
fl_6c8:	jmp	fl_af6	;  0xaf6

FLOAT_DIV:
fl_6cc:	ldi	r26, 0x18	; 24
fl_6ce:	ldi	r27, 0x00	; 0
fl_6d0:	ldi	r30, low(fl_6d8); 0x6C	; 108
fl_6d2:	ldi	r31, high(fl_6d8); 0x03	; 3
fl_6d4:	jmp	fl_ace	;  0xace
fl_6d8:	std	Y+1, r22	; 0x01
fl_6da:	std	Y+2, r23	; 0x02
fl_6dc:	std	Y+3, r24	; 0x03
fl_6de:	std	Y+4, r25	; 0x04
fl_6e0:	std	Y+5, r18	; 0x05
fl_6e2:	std	Y+6, r19	; 0x06
fl_6e4:	std	Y+7, r20	; 0x07
fl_6e6:	std	Y+8, r21	; 0x08
fl_6e8:	ldi	r27, 0x09	; 9
fl_6ea:	mov	r14, r27
fl_6ec:	mov	r15, r1
fl_6ee:	add	r14, r28
fl_6f0:	adc	r15, r29
fl_6f2:	movw	r24, r28
fl_6f4:	adiw	r24, 0x01	; 1
fl_6f6:	movw	r22, r14
fl_6f8:	call	fl_9ce	;  0x9ce
fl_6fc:	movw	r16, r28
fl_6fe:	subi	r16, 0xEF	; 239
fl_700:	sbci	r17, 0xFF	; 255
fl_702:	movw	r24, r28
fl_704:	adiw	r24, 0x05	; 5
fl_706:	movw	r22, r16
fl_708:	call	fl_9ce	;  0x9ce
fl_70c:	ldd	r18, Y+9	; 0x09
fl_70e:	cpi	r18, 0x02	; 2
fl_710:	brcc	fl_714
fl_712:	rjmp	fl_810
fl_714:	ldd	r19, Y+17	; 0x11
fl_716:	cpi	r19, 0x02	; 2
fl_718:	brcc	fl_71e
fl_71a:	movw	r22, r16
fl_71c:	rjmp	fl_816
fl_71e:	ldd	r24, Y+10	; 0x0a
fl_720:	ldd	r25, Y+18	; 0x12
fl_722:	eor	r24, r25
fl_724:	std	Y+10, r24	; 0x0a
fl_726:	cpi	r18, 0x04	; 4
fl_728:	breq	fl_72e
fl_72a:	cpi	r18, 0x02	; 2
fl_72c:	brne	fl_73a
fl_72e:	cp	r18, r19
fl_730:	breq	fl_734
fl_732:	rjmp	fl_810
fl_734:	ldi	r22, 0x00	; 0
fl_736:	ldi	r23, 0x01	; 1
fl_738:	rjmp	fl_816
fl_73a:	cpi	r19, 0x04	; 4
fl_73c:	brne	fl_74c
fl_73e:	std	Y+13, r1	; 0x0d
fl_740:	std	Y+14, r1	; 0x0e
fl_742:	std	Y+15, r1	; 0x0f
fl_744:	std	Y+16, r1	; 0x10
fl_746:	std	Y+12, r1	; 0x0c
fl_748:	std	Y+11, r1	; 0x0b
fl_74a:	rjmp	fl_754
fl_74c:	cpi	r19, 0x02	; 2
fl_74e:	brne	fl_758
fl_750:	ldi	r24, 0x04	; 4
fl_752:	std	Y+9, r24	; 0x09
fl_754:	movw	r22, r14
fl_756:	rjmp	fl_816
fl_758:	ldd	r18, Y+11	; 0x0b
fl_75a:	ldd	r19, Y+12	; 0x0c
fl_75c:	ldd	r24, Y+19	; 0x13
fl_75e:	ldd	r25, Y+20	; 0x14
fl_760:	sub	r18, r24
fl_762:	sbc	r19, r25
fl_764:	std	Y+12, r19	; 0x0c
fl_766:	std	Y+11, r18	; 0x0b
fl_768:	ldd	r14, Y+13	; 0x0d
fl_76a:	ldd	r15, Y+14	; 0x0e
fl_76c:	ldd	r16, Y+15	; 0x0f
fl_76e:	ldd	r17, Y+16	; 0x10
fl_770:	ldd	r10, Y+21	; 0x15
fl_772:	ldd	r11, Y+22	; 0x16
fl_774:	ldd	r12, Y+23	; 0x17
fl_776:	ldd	r13, Y+24	; 0x18
fl_778:	cp	r14, r10
fl_77a:	cpc	r15, r11
fl_77c:	cpc	r16, r12
fl_77e:	cpc	r17, r13
fl_780:	brcc	fl_792
fl_782:	add	r14, r14
fl_784:	adc	r15, r15
fl_786:	adc	r16, r16
fl_788:	adc	r17, r17
fl_78a:	subi	r18, 0x01	; 1
fl_78c:	sbci	r19, 0x00	; 0
fl_78e:	std	Y+12, r19	; 0x0c
fl_790:	std	Y+11, r18	; 0x0b
fl_792:	ldi	r18, 0x00	; 0
fl_794:	ldi	r19, 0x00	; 0
fl_796:	ldi	r20, 0x00	; 0
fl_798:	ldi	r21, 0x00	; 0
fl_79a:	ldi	r24, 0x00	; 0
fl_79c:	ldi	r25, 0x00	; 0
fl_79e:	ldi	r26, 0x00	; 0
fl_7a0:	ldi	r27, 0x40	; 64
fl_7a2:	ldi	r22, 0x00	; 0
fl_7a4:	ldi	r23, 0x00	; 0
fl_7a6:	cp	r14, r10
fl_7a8:	cpc	r15, r11
fl_7aa:	cpc	r16, r12
fl_7ac:	cpc	r17, r13
fl_7ae:	brcs	fl_7c0
fl_7b0:	or	r18, r24
fl_7b2:	or	r19, r25
fl_7b4:	or	r20, r26
fl_7b6:	or	r21, r27
fl_7b8:	sub	r14, r10
fl_7ba:	sbc	r15, r11
fl_7bc:	sbc	r16, r12
fl_7be:	sbc	r17, r13
fl_7c0:	lsr	r27
fl_7c2:	ror	r26
fl_7c4:	ror	r25
fl_7c6:	ror	r24
fl_7c8:	add	r14, r14
fl_7ca:	adc	r15, r15
fl_7cc:	adc	r16, r16
fl_7ce:	adc	r17, r17
fl_7d0:	subi	r22, 0xFF	; 255
fl_7d2:	sbci	r23, 0xFF	; 255
fl_7d4:	cpi	r22, 0x1F	; 31
fl_7d6:	cpc	r23, r1
fl_7d8:	brne	fl_7a6
fl_7da:	movw	r26, r20
fl_7dc:	movw	r24, r18
fl_7de:	andi	r24, 0x7F	; 127
fl_7e0:	andi	r25, 0x00	; 0
fl_7e2:	andi	r26, 0x00	; 0
fl_7e4:	andi	r27, 0x00	; 0
fl_7e6:	cpi	r24, 0x40	; 64
fl_7e8:	cpc	r25, r1
fl_7ea:	cpc	r26, r1
fl_7ec:	cpc	r27, r1
fl_7ee:	brne	fl_808
fl_7f0:	sbrc	r18, 7
fl_7f2:	rjmp	fl_808
fl_7f4:	cp	r14, r1
fl_7f6:	cpc	r15, r1
fl_7f8:	cpc	r16, r1
fl_7fa:	cpc	r17, r1
fl_7fc:	breq	fl_808
fl_7fe:	subi	r18, 0xC0	; 192
fl_800:	sbci	r19, 0xFF	; 255
fl_802:	sbci	r20, 0xFF	; 255
fl_804:	sbci	r21, 0xFF	; 255
fl_806:	andi	r18, 0x80	; 128
fl_808:	std	Y+13, r18	; 0x0d
fl_80a:	std	Y+14, r19	; 0x0e
fl_80c:	std	Y+15, r20	; 0x0f
fl_80e:	std	Y+16, r21	; 0x10
fl_810:	movw	r22, r28
fl_812:	subi	r22, 0xF7	; 247
fl_814:	sbci	r23, 0xFF	; 255
fl_816:	movw	r24, r22
fl_818:	call	fl_824	;  0x824
fl_81c:	adiw	r28, 0x18	; 24
fl_81e:	ldi	r30, 0x0A	; 10
fl_820:	jmp	fl_b06	;  0xb06
fl_824:	push	r13
fl_826:	push	r14
fl_828:	push	r15
fl_82a:	push	r16
fl_82c:	push	r17
fl_82e:	movw	r30, r24
fl_830:	ldd	r14, Z+4	; 0x04
fl_832:	ldd	r15, Z+5	; 0x05
fl_834:	ldd	r16, Z+6	; 0x06
fl_836:	ldd	r17, Z+7	; 0x07
fl_838:	ldd	r13, Z+1	; 0x01
fl_83a:	ld	r24, Z
fl_83c:	cpi	r24, 0x02	; 2
fl_83e:	brcc	fl_852
fl_840:	ldi	r24, 0x00	; 0
fl_842:	ldi	r25, 0x00	; 0
fl_844:	ldi	r26, 0x10	; 16
fl_846:	ldi	r27, 0x00	; 0
fl_848:	or	r14, r24
fl_84a:	or	r15, r25
fl_84c:	or	r16, r26
fl_84e:	or	r17, r27
fl_850:	rjmp	fl_99c
fl_852:	cpi	r24, 0x04	; 4
fl_854:	brne	fl_858
fl_856:	rjmp	fl_996
fl_858:	cpi	r24, 0x02	; 2
fl_85a:	brne	fl_864
fl_85c:	eor	r14, r14
fl_85e:	eor	r15, r15
fl_860:	movw	r16, r14
fl_862:	rjmp	fl_86e
fl_864:	cp	r14, r1
fl_866:	cpc	r15, r1
fl_868:	cpc	r16, r1
fl_86a:	cpc	r17, r1
fl_86c:	brne	fl_874
fl_86e:	ldi	r30, 0x00	; 0
fl_870:	ldi	r31, 0x00	; 0
fl_872:	rjmp	fl_9a0
fl_874:	ldd	r22, Z+2	; 0x02
fl_876:	ldd	r23, Z+3	; 0x03
fl_878:	ldi	r25, 0xFF	; 255
fl_87a:	cpi	r22, 0x82	; 130
fl_87c:	cpc	r23, r25
fl_87e:	brlt	fl_882
fl_880:	rjmp	fl_938
fl_882:	ldi	r18, 0x82	; 130
fl_884:	ldi	r19, 0xFF	; 255
fl_886:	sub	r18, r22
fl_888:	sbc	r19, r23
fl_88a:	cpi	r18, 0x1A	; 26
fl_88c:	cpc	r19, r1
fl_88e:	brlt	fl_89a
fl_890:	ldi	r18, 0x00	; 0
fl_892:	ldi	r19, 0x00	; 0
fl_894:	ldi	r20, 0x00	; 0
fl_896:	ldi	r21, 0x00	; 0
fl_898:	rjmp	fl_8ee
fl_89a:	movw	r22, r16
fl_89c:	movw	r20, r14
fl_89e:	mov	r0, r18
fl_8a0:	rjmp	fl_8aa
fl_8a2:	lsr	r23
fl_8a4:	ror	r22
fl_8a6:	ror	r21
fl_8a8:	ror	r20
fl_8aa:	dec	r0
fl_8ac:	brpl	fl_8a2
fl_8ae:	ldi	r24, 0x01	; 1
fl_8b0:	ldi	r25, 0x00	; 0
fl_8b2:	ldi	r26, 0x00	; 0
fl_8b4:	ldi	r27, 0x00	; 0
fl_8b6:	rjmp	fl_8c0
fl_8b8:	add	r24, r24
fl_8ba:	adc	r25, r25
fl_8bc:	adc	r26, r26
fl_8be:	adc	r27, r27
fl_8c0:	dec	r18
fl_8c2:	brpl	fl_8b8
fl_8c4:	sbiw	r24, 0x01	; 1
fl_8c6:	sbc	r26, r1
fl_8c8:	sbc	r27, r1
fl_8ca:	and	r24, r14
fl_8cc:	and	r25, r15
fl_8ce:	and	r26, r16
fl_8d0:	and	r27, r17
fl_8d2:	sbiw	r24, 0x00	; 0
fl_8d4:	cpc	r26, r1
fl_8d6:	cpc	r27, r1
fl_8d8:	breq	fl_8e2
fl_8da:	ldi	r24, 0x01	; 1
fl_8dc:	ldi	r25, 0x00	; 0
fl_8de:	ldi	r26, 0x00	; 0
fl_8e0:	ldi	r27, 0x00	; 0
fl_8e2:	movw	r18, r20
fl_8e4:	movw	r20, r22
fl_8e6:	or	r18, r24
fl_8e8:	or	r19, r25
fl_8ea:	or	r20, r26
fl_8ec:	or	r21, r27
fl_8ee:	movw	r26, r20
fl_8f0:	movw	r24, r18
fl_8f2:	andi	r24, 0x7F	; 127
fl_8f4:	andi	r25, 0x00	; 0
fl_8f6:	andi	r26, 0x00	; 0
fl_8f8:	andi	r27, 0x00	; 0
fl_8fa:	cpi	r24, 0x40	; 64
fl_8fc:	cpc	r25, r1
fl_8fe:	cpc	r26, r1
fl_900:	cpc	r27, r1
fl_902:	brne	fl_912
fl_904:	sbrs	r18, 7
fl_906:	rjmp	fl_91a
fl_908:	subi	r18, 0xC0	; 192
fl_90a:	sbci	r19, 0xFF	; 255
fl_90c:	sbci	r20, 0xFF	; 255
fl_90e:	sbci	r21, 0xFF	; 255
fl_910:	rjmp	fl_91a
fl_912:	subi	r18, 0xC1	; 193
fl_914:	sbci	r19, 0xFF	; 255
fl_916:	sbci	r20, 0xFF	; 255
fl_918:	sbci	r21, 0xFF	; 255
fl_91a:	ldi	r30, 0x00	; 0
fl_91c:	ldi	r31, 0x00	; 0
fl_91e:	cpi	r18, 0x00	; 0
fl_920:	ldi	r26, 0x00	; 0
fl_922:	cpc	r19, r26
fl_924:	ldi	r26, 0x00	; 0
fl_926:	cpc	r20, r26
fl_928:	ldi	r26, 0x40	; 64
fl_92a:	cpc	r21, r26
fl_92c:	brcs	fl_932
fl_92e:	ldi	r30, 0x01	; 1
fl_930:	ldi	r31, 0x00	; 0
fl_932:	movw	r14, r18
fl_934:	movw	r16, r20
fl_936:	rjmp	fl_986
fl_938:	cpi	r22, 0x80	; 128
fl_93a:	cpc	r23, r1
fl_93c:	brge	fl_996
fl_93e:	movw	r30, r22
fl_940:	subi	r30, 0x81	; 129
fl_942:	sbci	r31, 0xFF	; 255
fl_944:	movw	r26, r16
fl_946:	movw	r24, r14
fl_948:	andi	r24, 0x7F	; 127
fl_94a:	andi	r25, 0x00	; 0
fl_94c:	andi	r26, 0x00	; 0
fl_94e:	andi	r27, 0x00	; 0
fl_950:	cpi	r24, 0x40	; 64
fl_952:	cpc	r25, r1
fl_954:	cpc	r26, r1
fl_956:	cpc	r27, r1
fl_958:	brne	fl_968
fl_95a:	sbrs	r14, 7
fl_95c:	rjmp	fl_978
fl_95e:	ldi	r24, 0x40	; 64
fl_960:	ldi	r25, 0x00	; 0
fl_962:	ldi	r26, 0x00	; 0
fl_964:	ldi	r27, 0x00	; 0
fl_966:	rjmp	fl_970
fl_968:	ldi	r24, 0x3F	; 63
fl_96a:	ldi	r25, 0x00	; 0
fl_96c:	ldi	r26, 0x00	; 0
fl_96e:	ldi	r27, 0x00	; 0
fl_970:	add	r14, r24
fl_972:	adc	r15, r25
fl_974:	adc	r16, r26
fl_976:	adc	r17, r27
fl_978:	sbrs	r17, 7
fl_97a:	rjmp	fl_986
fl_97c:	lsr	r17
fl_97e:	ror	r16
fl_980:	ror	r15
fl_982:	ror	r14
fl_984:	adiw	r30, 0x01	; 1
fl_986:	ldi	r24, 0x07	; 7
fl_988:	lsr	r17
fl_98a:	ror	r16
fl_98c:	ror	r15
fl_98e:	ror	r14
fl_990:	dec	r24
fl_992:	brne	fl_988
fl_994:	rjmp	fl_9a0
fl_996:	eor	r14, r14
fl_998:	eor	r15, r15
fl_99a:	movw	r16, r14
fl_99c:	ldi	r30, 0xFF	; 255
fl_99e:	ldi	r31, 0x00	; 0
fl_9a0:	mov	r22, r30
fl_9a2:	ror	r22
fl_9a4:	eor	r22, r22
fl_9a6:	ror	r22
fl_9a8:	mov	r25, r16
fl_9aa:	andi	r25, 0x7F	; 127
fl_9ac:	ror	r13
fl_9ae:	eor	r13, r13
fl_9b0:	ror	r13
fl_9b2:	mov	r24, r30
fl_9b4:	lsr	r24
fl_9b6:	mov	r20, r25
fl_9b8:	or	r20, r22
fl_9ba:	mov	r21, r24
fl_9bc:	or	r21, r13
fl_9be:	movw	r22, r14
fl_9c0:	movw	r24, r20
fl_9c2:	pop	r17
fl_9c4:	pop	r16
fl_9c6:	pop	r15
fl_9c8:	pop	r14
fl_9ca:	pop	r13
fl_9cc:	ret
fl_9ce:	movw	r30, r24
fl_9d0:	movw	r26, r22
fl_9d2:	ld	r20, Z
fl_9d4:	ldd	r21, Z+1	; 0x01
fl_9d6:	ldd	r18, Z+2	; 0x02
fl_9d8:	mov	r22, r18
fl_9da:	andi	r22, 0x7F	; 127
fl_9dc:	ldi	r23, 0x00	; 0
fl_9de:	adc	r18, r18
fl_9e0:	eor	r18, r18
fl_9e2:	adc	r18, r18
fl_9e4:	ldd	r25, Z+3	; 0x03
fl_9e6:	mov	r24, r25
fl_9e8:	add	r24, r24
fl_9ea:	or	r24, r18
fl_9ec:	mov	r18, r24
fl_9ee:	ldi	r19, 0x00	; 0
fl_9f0:	adc	r25, r25
fl_9f2:	eor	r25, r25
fl_9f4:	adc	r25, r25
fl_9f6:	adiw	r26, 0x01	; 1
fl_9f8:	st	X, r25
fl_9fa:	sbiw	r26, 0x01	; 1
fl_9fc:	cp	r18, r1
fl_9fe:	cpc	r19, r1
fl_a00:	brne	fl_a6c
fl_a02:	cp	r20, r1
fl_a04:	cpc	r21, r1
fl_a06:	cpc	r22, r1
fl_a08:	cpc	r23, r1
fl_a0a:	brne	fl_a10
fl_a0c:	ldi	r24, 0x02	; 2
fl_a0e:	rjmp	fl_a7e
fl_a10:	ldi	r24, 0x82	; 130
fl_a12:	ldi	r25, 0xFF	; 255
fl_a14:	adiw	r26, 0x03	; 3
fl_a16:	st	X, r25
fl_a18:	st	-X, r24
fl_a1a:	sbiw	r26, 0x02	; 2
fl_a1c:	movw	r18, r20
fl_a1e:	movw	r20, r22
fl_a20:	ldi	r22, 0x07	; 7
fl_a22:	add	r18, r18
fl_a24:	adc	r19, r19
fl_a26:	adc	r20, r20
fl_a28:	adc	r21, r21
fl_a2a:	dec	r22
fl_a2c:	brne	fl_a22
fl_a2e:	ldi	r24, 0x03	; 3
fl_a30:	st	X, r24
fl_a32:	rjmp	fl_a4e
fl_a34:	add	r18, r18
fl_a36:	adc	r19, r19
fl_a38:	adc	r20, r20
fl_a3a:	adc	r21, r21
fl_a3c:	adiw	r26, 0x02	; 2
fl_a3e:	ld	r24, X+
fl_a40:	ld	r25, X
fl_a42:	sbiw	r26, 0x03	; 3
fl_a44:	sbiw	r24, 0x01	; 1
fl_a46:	adiw	r26, 0x03	; 3
fl_a48:	st	X, r25
fl_a4a:	st	-X, r24
fl_a4c:	sbiw	r26, 0x02	; 2
fl_a4e:	cpi	r18, 0x00	; 0
fl_a50:	ldi	r24, 0x00	; 0
fl_a52:	cpc	r19, r24
fl_a54:	ldi	r24, 0x00	; 0
fl_a56:	cpc	r20, r24
fl_a58:	ldi	r24, 0x40	; 64
fl_a5a:	cpc	r21, r24
fl_a5c:	brcs	fl_a34
fl_a5e:	adiw	r26, 0x04	; 4
fl_a60:	st	X+, r18
fl_a62:	st	X+, r19
fl_a64:	st	X+, r20
fl_a66:	st	X, r21
fl_a68:	sbiw	r26, 0x07	; 7
fl_a6a:	ret
fl_a6c:	cpi	r18, 0xFF	; 255
fl_a6e:	cpc	r19, r1
fl_a70:	brne	fl_a90
fl_a72:	cp	r20, r1
fl_a74:	cpc	r21, r1
fl_a76:	cpc	r22, r1
fl_a78:	cpc	r23, r1
fl_a7a:	brne	fl_a82
fl_a7c:	ldi	r24, 0x04	; 4
fl_a7e:	st	X, r24
fl_a80:	ret
fl_a82:	sbrs	r22, 4
fl_a84:	rjmp	fl_a8c
fl_a86:	ldi	r24, 0x01	; 1
fl_a88:	st	X, r24
fl_a8a:	rjmp	fl_ab0
fl_a8c:	st	X, r1
fl_a8e:	rjmp	fl_ab0
fl_a90:	subi	r18, 0x7F	; 127
fl_a92:	sbci	r19, 0x00	; 0
fl_a94:	adiw	r26, 0x03	; 3
fl_a96:	st	X, r19
fl_a98:	st	-X, r18
fl_a9a:	sbiw	r26, 0x02	; 2
fl_a9c:	ldi	r24, 0x03	; 3
fl_a9e:	st	X, r24
fl_aa0:	ldi	r24, 0x07	; 7
fl_aa2:	add	r20, r20
fl_aa4:	adc	r21, r21
fl_aa6:	adc	r22, r22
fl_aa8:	adc	r23, r23
fl_aaa:	dec	r24
fl_aac:	brne	fl_aa2
fl_aae:	ori	r23, 0x40	; 64
fl_ab0:	adiw	r26, 0x04	; 4
fl_ab2:	st	X+, r20
fl_ab4:	st	X+, r21
fl_ab6:	st	X+, r22
fl_ab8:	st	X, r23
fl_aba:	sbiw	r26, 0x07	; 7
fl_abc:	ret
fl_abe:	push	r2
fl_ac0:	push	r3
fl_ac2:	push	r4
fl_ac4:	push	r5
fl_ac6:	push	r6
fl_ac8:	push	r7
fl_aca:	push	r8
fl_acc:	push	r9
fl_ace:	push	r10
fl_ad0:	push	r11
fl_ad2:	push	r12
fl_ad4:	push	r13
fl_ad6:	push	r14
fl_ad8:	push	r15
fl_ada:	push	r16
fl_adc:	push	r17
fl_ade:	push	r28
fl_ae0:	push	r29
fl_ae2:	in	r28, 0x3d	; 61
fl_ae4:	in	r29, 0x3e	; 62
fl_ae6:	sub	r28, r26
fl_ae8:	sbc	r29, r27
fl_aea:	in	r0, 0x3f	; 63
fl_aec:	cli
fl_aee:	out	0x3e, r29	; 62
fl_af0:	out	0x3f, r0	; 63
fl_af2:	out	0x3d, r28	; 61
fl_af4:	ijmp
fl_af6:	ldd	r2, Y+18	; 0x12
fl_af8:	ldd	r3, Y+17	; 0x11
fl_afa:	ldd	r4, Y+16	; 0x10
fl_afc:	ldd	r5, Y+15	; 0x0f
fl_afe:	ldd	r6, Y+14	; 0x0e
fl_b00:	ldd	r7, Y+13	; 0x0d
fl_b02:	ldd	r8, Y+12	; 0x0c
fl_b04:	ldd	r9, Y+11	; 0x0b
fl_b06:	ldd	r10, Y+10	; 0x0a
fl_b08:	ldd	r11, Y+9	; 0x09
fl_b0a:	ldd	r12, Y+8	; 0x08
fl_b0c:	ldd	r13, Y+7	; 0x07
fl_b0e:	ldd	r14, Y+6	; 0x06
fl_b10:	ldd	r15, Y+5	; 0x05
fl_b12:	ldd	r16, Y+4	; 0x04
fl_b14:	ldd	r17, Y+3	; 0x03
fl_b16:	ldd	r26, Y+2	; 0x02
fl_b18:	ldd	r27, Y+1	; 0x01
fl_b1a:	add	r28, r30
fl_b1c:	adc	r29, r1
fl_b1e:	in	r0, 0x3f	; 63
fl_b20:	cli
fl_b22:	out	0x3e, r29	; 62
fl_b24:	out	0x3f, r0	; 63
fl_b26:	out	0x3d, r28	; 61
fl_b28:	movw	r28, r26
fl_b2a:	ret
