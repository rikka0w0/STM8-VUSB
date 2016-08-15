#ifndef INIT_H_
#define INIT_H_

#include "stm8s.h"
#include "mcu_gpio.h"

void Init_GPIO(void);
void Init_Clock(void);
void Init_TIM1(void);
void delay(uint8_t n);

#endif /* MAIN_H_ */
