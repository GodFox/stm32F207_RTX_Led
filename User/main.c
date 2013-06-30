#include "stm32f2xx.h"
#include <RTL.h>
#include <stdio.h>


unsigned char LedCunt;

OS_TID tsk_1;

extern int fputc(int ch, FILE *f);

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

void uartinit(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);	
}

int sendchar (int c) {

  if (c == '\n')  
  {
	  while (!(USART1->SR & 0x0080));
	  USART1->DR = 0x0D;
  }
  while (!(USART1->SR & 0x0080));
  USART1->DR = (c & 0x1FF);
  return (c);
}

int  getkey(void)
{
	return 0;
}

__task void LedTest(void)
{
	printf("task LedTest running\n");
	while(1)
	{
		switch (LedCunt)
		{
			case 0:
			{
				GPIOD ->BSRRH |= GPIO_Pin_13;
				GPIOD ->BSRRL |= GPIO_Pin_14;
				GPIOD ->BSRRL |= GPIO_Pin_15;
				GPIOC ->BSRRL |= GPIO_Pin_7;
				printf("Led 1 Light\n");
				LedDelay();
				LedCunt += 1;
			}
			case 1:
			{
				GPIOD ->BSRRH |= GPIO_Pin_13;
				GPIOD ->BSRRH |= GPIO_Pin_14;
				GPIOD ->BSRRL |= GPIO_Pin_15;
				GPIOC ->BSRRL |= GPIO_Pin_7;
				printf("Led 1/2 Light\n");
				LedDelay();
				LedCunt += 1;
			}
			case 2:
			{
				GPIOD ->BSRRH |= GPIO_Pin_13;
				GPIOD ->BSRRH |= GPIO_Pin_14;
				GPIOD ->BSRRH |= GPIO_Pin_15;
				GPIOC ->BSRRL |= GPIO_Pin_7;
				printf("Led 1/2/3 Light\n");
				LedDelay();
				LedCunt += 1;
			}
			case 3:
			{
				GPIOD ->BSRRH |= GPIO_Pin_13;
				GPIOD ->BSRRH |= GPIO_Pin_14;
				GPIOD ->BSRRH |= GPIO_Pin_15;
				GPIOC ->BSRRH |= GPIO_Pin_7;
				printf("Led 1/2/3/4 Light\n");
				LedDelay();
				LedCunt += 1;
			}
			case 4:
			{
				GPIOD ->BSRRL |= GPIO_Pin_13;
				GPIOD ->BSRRL |= GPIO_Pin_14;
				GPIOD ->BSRRL |= GPIO_Pin_15;
				GPIOC ->BSRRL |= GPIO_Pin_7;
				printf("No Led Light\n");
				LedDelay();
				LedCunt = 0;
			}
		}
	}
}

__task void run(void)
{
	tsk_1 = os_tsk_create(LedTest,0);
	
	os_tsk_delete_self();
}


int main(void)
{
	LedCunt = 0;
	LedInit();
	uartinit();
	os_sys_init(run);
}
