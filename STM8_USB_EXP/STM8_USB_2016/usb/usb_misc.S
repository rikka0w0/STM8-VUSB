	xdef _USB_ICInit

;Timer1 Register address definations
CCER1:equ $525C
CCMR2:equ $5259
BRK:	equ $526D
OISR: equ $526F

;TIM1_ICInit(TIM1_CHANNEL_2, TIM1_ICPOLARITY_RISING, TIM1_ICSELECTION_DIRECTTI, TIM1_ICPSC_DIV1, 0x02);
_USB_ICInit:
	;Disable the Channel 2: Reset the CCE Bit
	bres CCER1,#4		;Clear bit 4, capture disable
	
	;Select the Input and set the filter
	ld a, #$0C
	and a, CCMR2	;Clear except bit 2,3
	ld CCMR2, a

	nop
	or a, #$21		;0x01 | ( 0x02 << 4);
	ld CCMR2, a
	
	nop
	and a, #$F3		;Clear bit 2,3  => prescalar = 0
	ld CCMR2, a

	;Select the Polarity
	bres CCER1,#5	;Clear bit 5, rising edge
	
  ;Set the CCE Bit
  bset CCER1,#4	;	//Set bit 4, capture enable

ret
