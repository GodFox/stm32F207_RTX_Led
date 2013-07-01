#include "stm32f2xx.h"

#define countof(a)   (sizeof(a) / sizeof(*(a)))

void NVIC_Config(void);
void USART1_IRQHandler(void);
