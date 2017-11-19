xdef _USB_RX, _USB_RX_Count

;0x80 0x2d 0x00 0x10

switch .bss
Buf: ds.b 1
_USB_RX_Count: ds.b 1
Msk: ds.b 32	;Rx data buffer

switch .text
DBG: equ $5000	;GPIOA->ODR
DBG_PIN: equ 3
IDR: equ 20491	;GPIOC->IDR

Bit7_DS:
Bit6_DS:
Bit1_DS:
Bit0_DS:	;Detected six consecutive 1, 0?11 1111
ld a, IDR
and a,#$C0
jreq End_Rx
ld a, Buf
xor a, #$7F ;Reverse prevBit and mask out consecutive 1s
ld Buf, a
ld a, #$01
ld ($10,x), a
jp L_Bit1

End_Rx:
mov		21077,#251
bres	21072,#0
clr		21086
clr		21087

ld a, #$0F
sub a, _USB_RX_Count
ld _USB_RX_Count, a
iret ;Set a break point on this line to watch the received data~

L_Bit6:
bcpl DBG, #DBG_PIN	;Debug output	
ld a, IDR
and a,#$C0
xor a,Buf
srl a
ld Buf, a
and a, #$3F
xor a, #$3F
jrf Bit6_DS
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

L_Bit7:
ld a, #$C0
and a,IDR
xor a,Buf
ld (x), a		;Store a received byte into buffer
rlc (x)			;Store bit0
srl a
ld Buf, a
and a, #$3F
cpl a
jrf Bit7_DS

L_Bit0:
ld a, IDR
and a,#$C0
jreq End_Rx
xor a,Buf
srl a
ld Buf, a
and a, #$3F
cpl a
jrf Bit0_DS

L_Bit1:
incw x
ld a, IDR
and a,#$C0
jreq End_Rx
xor a,Buf
srl a
ld Buf, a
and a, #$3F
cpl a
jrf Bit1_DS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

L_Bit2:
ld a, IDR
and a,#$C0
xor a,Buf
srl a
ld Buf, a
and a, #$3F
cpl a
jrf Bit2_DS


L_Bit3:
dec _USB_RX_Count
jreq End_Rx	;Avoid infinite loop
ld a, IDR
and a,#$C0
xor a,Buf
srl a
ld Buf, a
and a, #$3F
cpl a
jrf Bit3_DS


L_Bit4:
ld a, IDR
and a,#$C0
xor a,Buf
srl a
ld Buf, a
and a, #$3F
cpl a
jrf Bit4_DS

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

L_Bit5:
ld a, #$C0
and a,IDR
xor a,Buf
srl a
ld Buf, a
and a, #$3F
cpl a
jrf Bit5_DS
jp L_Bit6


Bit2_DS:
Bit3_DS:
Bit4_DS:
Bit5_DS:
QAQ:
jp QAQ



_USB_RX:
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

	
L_Delay_End:
	ldw x, #Msk
	ld a, #$00  ;Initial state
	ld Buf, a
	ld a, #$0E	;Maximum count = 15
	ld _USB_RX_Count, a
	jp L_Bit6