#include "main.h"

void Init_GPIO(void)
{
	GPIOC->CR1 = 0xFF;
	
	GPIOC->CR1 = 0;
	GPIOC->CR2 = 0;
	GPIOC->DDR = 0x3F;
	GPIOC->ODR = 0;
}

void Init_Clock(void)
{
	CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
}

void Init_TIM1(void)
{
	CLK->PCKENR1 |= CLK_PCKENR1_TIM1;
	
	TIM1_TimeBaseInit(0, TIM1_PSCRELOADMODE_UPDATE, 1000, 0);
	TIM1_ICInit(TIM1_CHANNEL_2, TIM1_ICPOLARITY_RISING, TIM1_ICSELECTION_DIRECTTI, TIM1_ICPSC_DIV1, 0x02);
	TIM1_SelectInputTrigger(TIM1_TS_TI2FP2);
	TIM1_SelectSlaveMode(TIM1_SLAVEMODE_TRIGGER);
	TIM1_ClearFlag(TIM1_FLAG_CC2);
	TIM1_ITConfig(TIM1_IT_CC2, ENABLE);
}

void delay(uint8_t n)
{
	unsigned int i;
	while(n>0)
	{
		for(i=0;i<2000;i++);
		n--;
	}
}
