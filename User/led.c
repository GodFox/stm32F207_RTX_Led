#include "led.h"

void LedInit(void)
{
	GPIO_InitTypeDef Led;				//注意：声明变量要放在执行语句之前
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);			//对外设的始时钟进行使能，才能对寄存器进行操作
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	
	Led.GPIO_Pin = GPIO_Pin_13;
	Led.GPIO_Mode = GPIO_Mode_OUT;
	Led.GPIO_OType = GPIO_OType_PP;
  Led.GPIO_PuPd = GPIO_PuPd_UP;
  Led.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &Led);
	
	Led.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOD, &Led);
	Led.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOD, &Led);	
	Led.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOC, &Led);
	

	GPIOD ->BSRRH |= GPIO_Pin_13;
	GPIOD ->BSRRH |= GPIO_Pin_14;
	GPIOD ->BSRRH |= GPIO_Pin_15;
	GPIOC ->BSRRH |= GPIO_Pin_7;
	
	
}


void LedDelay(void)
{
	int i;
	for(i = 0; i < 6000000; i++);
}
