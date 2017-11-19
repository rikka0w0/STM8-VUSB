	xref	_usb_tx_count, _usb_tx_buffer_pointer, _USB_ICInit

	xdef	_usb_tx, _USB_SendACK, _USB_SendNACK
	
switch .bss
PID_BUF: ds.w 1	;Buffer for sending ACK, NACK, STALL

switch .text
PID_ACK:	dc.w	$80D2
PID_NACK:	dc.w	$805A
PID_STALL:dc.w	$801E

;Timer1 Register address definations
CCER1:equ $525C
CCMR2:equ $5259
BRK:	equ $526D
OISR: equ $526F
IER:	equ $5254
SR1:	equ $5255


MOE: equ 7

L_Bit0_Idle:
	nop
	nop
	dec		a
	jrne	L_Bit1_Begin
	nop
	nop
	nop
	bcpl CCMR2, #4
	nop
	nop
	ld		a, #$06
	jra		L_Bit1_Begin
	nop
	nop

L_Bit1_Idle:
	nop
	nop
	dec		a
	jrne	L_Bit2_Begin
	nop
	nop
	nop
	bcpl CCMR2, #4
	nop
	nop
	ld		a, #$06
	jra		L_Bit2_Begin
	nop
	nop

L_Bit2_Idle:
	nop
	dec		a
	jrne	L_Bit3_Begin
	nop
	nop
	nop
	nop
	bcpl CCMR2, #4
	nop
	ld		a, #$06
	jra		L_Bit3_Begin
	nop
	nop

L_Bit3_Idle:
	nop
	nop
	nop
	dec		a
	jrne	L_Bit4_Begin
	nop;
	nop
	nop
	bcpl CCMR2, #4
	nop
	nop
	ld		a, #$06
	jra		L_Bit4_Begin
	nop
	nop
	;nop


L_Bit0_Begin:
	rrc		(x)						// 忌我找 0 -> 妊C.C
	jrc		L_Bit0_Idle				// 扭快把快抄找我, 快扼抖我 把忘志快扶 C妊.C = 1
	bcpl CCMR2, #4
	ld		a, #$06					// 快扼抖我 忌抑抖忘 我扶志快把扼我攸, 扼忌把忘扼抑志忘快技
	nop
	nop
	nop
	nop

L_Bit1_Begin:
	rrc		(x)						// 忌我找 0 -> 妊C.C
	jrc		L_Bit1_Idle				// 扭快把快抄找我, 快扼抖我 把忘志快扶 C妊.C = 1
	bcpl CCMR2, #4
	ld		a, #$06
	nop
	nop
	nop
	nop

L_Bit2_Begin:
	rrc		(x)						// 忌我找 0 -> 妊C.C
	jrc		L_Bit2_Idle				// 扭快把快抄找我, 快扼抖我 把忘志快扶 C妊.C = 1
	bcpl CCMR2, #4
	ld		a, #$06
	nop
	nop
	nop
	;nop

L_Bit3_Begin:
	rrc		(x)						// 忌我找 0 -> 妊C.C
	jrc		L_Bit3_Idle				// 扭快把快抄找我, 快扼抖我 把忘志快扶 C妊.C = 1
	nop;
	bcpl CCMR2, #4
	ld		a, #$06
	nop
	nop
	nop
	nop

L_Bit4_Begin:
	rrc		(x)						// 忌我找 0 -> 妊C.C
	jrc		L_Bit4_Idle				// 扭快把快抄找我, 快扼抖我 把忘志快扶 C妊.C = 1
	bcpl CCMR2, #4
	ld		a, #$06
	nop
	nop
	nop
	nop

L_Bit5_Begin:
	rrc		(x)						// 忌我找 0 -> 妊C.C
	jrc		L_Bit5_Idle				// 扭快把快抄找我, 快扼抖我 把忘志快扶 C妊.C = 1
	bcpl CCMR2, #4
	ld		a, #$06
	nop
	nop
	nop
	nop

L_Bit6_Begin:
	rrc		(x)						// 忌我找 0 -> 妊C.C
	jrc		L_Bit6_Idle				// 扭快把快抄找我, 快扼抖我 把忘志快扶 C妊.C = 1
	bcpl CCMR2, #4
	ld		a, #$06
	nop
	nop

L_Bit7_Begin:
	rrc		(x)						// 忌我找 0 -> 妊C.C
	jrc		L_Bit7_Idle				// 扭快把快抄找我, 快扼抖我 把忘志快扶 C妊.C = 1
	nop
	nop
	bcpl CCMR2, #4
	ld		a, #$06

L_Check_End:

	incw	x
	dec		_usb_tx_count
	jrne	L_Bit0_Begin

	nop
L_Tx_End:
	nop
	nop
	nop
	bres BRK, #MOE	;Enter Idle
	
	jra L_Post_Tx



;
;
;

L_Bit4_Idle:
	nop
	nop
	dec		a
	jrne	L_Bit5_Begin
	nop
	nop
	nop
	bcpl CCMR2, #4
	nop
	nop
	ld		a, #$06
	jra		L_Bit5_Begin
	nop

	nop
L_Bit5_Idle:
	nop
	nop
	dec		a
	jrne	L_Bit6_Begin
	nop
	nop
	nop
	bcpl CCMR2, #4
	nop
	nop
	ld		a, #$06
	jra		L_Bit6_Begin
	nop
	nop

L_Bit6_Idle:

	dec		a
	jrne	L_Bit7_Begin
	nop
	nop
	nop
	nop
	nop
	bcpl CCMR2, #4
	ld		a, #$06
	jra		L_Bit7_Begin
	nop
	nop
	nop

L_Bit7_Idle:
	dec		a
	jrne	L_Check_End
	dec		_usb_tx_count
	nop
	incw	x
	nop
	ld		a, #$06
	nop
	bcpl CCMR2, #4
	nop
	tnz		_usb_tx_count
	jrne	L_Bit0_Begin
	jra		L_Tx_End



_usb_tx:
	bres IER, #2	;Disable event generation
	bres CCER1,#4	;Exit capture mode, clear CC2E
	
	bset OISR, #3	; D- CH2N = 1 at idle
	bres OISR, #2	; D+ CH2 = 0 at idle
	
	;Configure as output
	ld a, #$FC
	and a, CCMR2
	ld CCMR2, a

	mov CCMR2, #$40 ; Force D- CH2 low, D+ CH2N high when output enabled
	mov CCER1, #$50 ; CH2, CH2N enabled, active high
	
	bset BRK, #MOE	; Enable diff
	
	
	ldw	x, _usb_tx_buffer_pointer
	ld		a, #$06	
	
	bres OISR, #3	; D- CH2N = 0 at idle	
	
	jra		L_Bit0_Begin


L_Post_Tx:
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop
	nop

	bset OISR, #3	; D- CH2N = 1 at idle
	bres OISR, #2	; D+ CH2 = 0 at idle
	bres CCER1, #4; D- CH2 to input mode, high impedance
	bres CCER1, #6; D- CH2N to input mode, high impedance

	call _USB_ICInit	;Reset CH2 to input capture mode
	mov  SR1, #$FB		;TIM1_ClearFlag(TIM1_FLAG_CC2)
	bset IER, #2 			;TIM1_ITConfig(TIM1_IT_CC2, ENABLE)

	ret


_USB_SendACK:
	ldw x, PID_ACK
	ldw PID_BUF, x
	ldw x, #PID_BUF
	ldw _usb_tx_buffer_pointer, x
	mov _usb_tx_count, #2
	jra _usb_tx
	
_USB_SendNACK:
	ldw x, PID_NACK
	ldw PID_BUF, x
	ldw x, #PID_BUF
	ldw _usb_tx_buffer_pointer, x
	mov _usb_tx_count, #2
	jra _usb_tx	