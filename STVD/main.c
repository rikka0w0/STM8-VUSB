#include "main.h"

uint8_t data_buffer[4];
extern uint8_t usb_ready;

void main(void)
{
	char x=10;
	char y=10;
	
	CLK->CKDIVR = 0;
	disableInterrupts();
	Init_GPIO();
	Init_TIM1();
	Init_Clock();
	usb_init();
	enableInterrupts();

	while(1)
	{
		usb_process();
	}

}
