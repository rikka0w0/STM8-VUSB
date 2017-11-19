#include "stm8s.h"
#include "usb.h"

extern void USB_RX(void);

void main(void)
{	
	GPIO_Init(GPIOA, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST);
	_asm("bres $5000,#3");
	USB_Init();
	
	CLK_CCOConfig(CLK_OUTPUT_CPUDIV16);
  CLK_CCOCmd(ENABLE);

	while(1)
	{
		//USB_RX();
		
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		
		nop();
		nop();
		nop();
		nop();
		nop();
		nop();
		
	}

}
