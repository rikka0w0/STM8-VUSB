#include "main.h"

uint8_t data_buffer[4];
extern uint8_t usb_ready;
//extern void usb_send_nack(void);
void main(void)
{
	
	CLK->CKDIVR = 0;
	disableInterrupts();
	Init_GPIO();
	Init_TIM1();
	Init_Clock();
	usb_init();
	enableInterrupts();

	while(1)
	{
		//usb_send_nack();
		usb_process();
	}

}
