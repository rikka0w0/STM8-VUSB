	xref	_usb_rx_count, _usb_rx_buffer, _usb_rx_ok, _usb_init

	xdef	_usb_rx

L_Bit0_Begin:
	cpl		($14,y)					; 同步信号
	srl		($01, SP)
	ld		a,(y)
	jreq	L_End_Rx				; 输出，如果输入=0（数据包结束）
	xor		a, ($01, SP)
	ld		($01, SP),a
	nop

L_Bit1_Begin:
	cpl		($14,y)					; сигнал синхронизации
	srl		($01, SP)
	ld		a,(y)
	jreq	L_End_Rx				; выход, если input = 0 (конец пакета)
	xor		a, ($01, SP)
	ld		($01, SP),a
	incw	x
	nop

L_Bit2_Begin:
	cpl		($14,y)					; сигнал синхронизации
	srl		($01, SP)
	ld		a,(y)
	jreq	L_End_Rx				; выход, если input = 0 (конец пакета)
	xor		a, ($01, SP)
	ld		($01, SP),a
	nop
	nop

L_Bit3_Begin:
	cpl		($14,y)					; сигнал синхронизации
	srl		($01, SP)
	ld		a,(y)
	jreq	L_End_Rx				; выход, если input = 0 (конец пакета)
	xor		a, ($01, SP)
	ld		($01, SP),a
	nop

L_Bit4_Begin:
	cpl		($14,y)					; сигнал синхронизации
	srl		($01, SP)
	ld		a,(y)
	jreq	L_End_Rx				; выход, если input = 0 (конец пакета)
	xor		a, ($01, SP)
	ld		($01, SP),a
	nop

L_Bit5_Begin:
	cpl		($14,y)					; сигнал синхронизации
	srl		($01, SP)
	ld		a,(y)
	jreq	L_End_Rx				; выход, если input = 0 (конец пакета)
	xor		a, ($01, SP)
	ld		($01, SP),a
	dec		($02,SP)
	jreq	L_End_Rx

L_Bit6_Begin:
	cpl		($14,y)					; сигнал синхронизации
	srl		($01, SP)
	ld		a,(y)
	jreq	L_End_Rx				; выход, если input = 0 (конец пакета)
	xor		a, ($01, SP)
	ld		($01, SP),a
	nop

L_Bit7_Begin:
	cpl		($14,y)					; сигнал синхронизации
	srl		($01, SP)
	ld		a,(y)
	jreq	L_End_Rx				; выход, если input = 0 (конец пакета)
	xor		a, ($01, SP)
	ld		($01, SP),a

	ld		(x),a					; сохраняем принятый байт
	rlc   	(x)

	cpl		($14,y)					; сигнал синхронизации
	srl		($01, SP)
	ld		a,(y)
	jreq	L_End_Rx				; выход, если input = 0 (конец пакета)
	xor		a, ($01, SP)
	ld		($01, SP),a

	jra		L_Bit1_Begin

	nop
	nop
	nop

L_End_Rx:

	pop		a
	pop		a
	ld		_usb_rx_count,a

	call	_usb_rx_ok

	clr		20495					; PD->ODR ???

	mov		21077,#251 				; 复位定时器中断标志

	bres	21072,#0				; 停止定时器
	clr		21086					; 重置计数器寄存器
	clr		21087					;

	iret

;
;
;

_usb_rx:
	ldw		x, #L_Delay_Begin	; 表的起始地址的延迟
	addw	x, 21086			; + 偏移量（定时器）
	cpw		x, #L_Delay_End		; 对于表格边框检查输出（zaschita!）
	jruge	L_Error
	jp		(x)					; 跳表的延误
	
L_Error:

	iret ; 紧急输出

L_Delay_Begin:
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
	nop
	nop
	nop
	nop
	nop
	nop

L_Delay_End:

	ldw		x, #_usb_rx_buffer		; 启动该缓冲器的地址
	ldw		y, #20491 				; 地址输入
	ld		a, #$0E					; 收到的最大字节数（zaschita!）
	push	a
	ld		a, #$80
	push	a

	jra		L_Bit0_Begin
