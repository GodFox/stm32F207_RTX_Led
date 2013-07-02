#include "stm32f2xx.h"
#include "usart.h"
#include "led.h"
#include "irq.h"
#include "key.c"
#include <RTL.h>
#include <stdio.h>


unsigned char LedCunt;

OS_TID tsk_1,tsk_2,tsk_3;

__task void LedTest(void)
{
	printf("task LedTest\n");
	while(1)
	{
		if(keyset == 0)
		{
			switch (LedCunt)
			{
				case 0:
				{
					GPIOD ->BSRRH |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 1:
				{
					GPIOD ->BSRRH |= GPIO_Pin_13;
					GPIOD ->BSRRH |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1/2 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 2:
				{
					GPIOD ->BSRRH |= GPIO_Pin_13;
					GPIOD ->BSRRH |= GPIO_Pin_14;
					GPIOD ->BSRRH |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1/2/3 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 3:
				{
					GPIOD ->BSRRH |= GPIO_Pin_13;
					GPIOD ->BSRRH |= GPIO_Pin_14;
					GPIOD ->BSRRH |= GPIO_Pin_15;
					GPIOC ->BSRRH |= GPIO_Pin_7;
					//printf("Led 1/2/3/4 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 4:
				{
					GPIOD ->BSRRL |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("No Led Light\n");
					LedDelay();
					LedCunt = 0;
				}
			}
		}
	}
}

__task void Inter_Uart(void)
{
	
	printf("task Inter Uart\n");
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);			//串口发送中断使能
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);		//串口接收完成中断
	while(1);
}

__task void Exti_key(void)
{
	
	printf("task Exti Key\n");
	while(1)
	{
		if(keyset == 1)
		{
			switch (LedCunt)
			{
				case 0:
				{
					GPIOD ->BSRRH |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 1:
				{
					GPIOD ->BSRRL |= GPIO_Pin_13;
					GPIOD ->BSRRH |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1/2 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 2:
				{
					GPIOD ->BSRRL |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRH |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1/2/3 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 3:
				{
					GPIOD ->BSRRL |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRH |= GPIO_Pin_7;
					//printf("Led 1/2/3/4 Light\n");
					LedDelay();
					LedCunt = 0;
				}
			}
		}
		else if (keyset == 2)
		{
			switch (LedCunt)
			{
				case 0:
				{
					GPIOD ->BSRRL |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRH |= GPIO_Pin_7;
					//printf("Led 1 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 1:
				{
					GPIOD ->BSRRL |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRH |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1/2 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 2:
				{
					GPIOD ->BSRRL |= GPIO_Pin_13;
					GPIOD ->BSRRH |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1/2/3 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 3:
				{
					GPIOD ->BSRRH |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1/2/3/4 Light\n");
					LedDelay();
					LedCunt = 0;
				}
			}
		}
		else if (keyset == 3)
		{
			switch (LedCunt)
			{
				case 0:
				{
					GPIOD ->BSRRH |= GPIO_Pin_13;
					GPIOD ->BSRRH |= GPIO_Pin_14;
					GPIOD ->BSRRH |= GPIO_Pin_15;
					GPIOC ->BSRRH |= GPIO_Pin_7;
					//printf("Led 1 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 1:
				{
					GPIOD ->BSRRL |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1/2 Light\n");
					LedDelay();
					LedCunt = 0;
				}
			}
		}
		else if(keyset == 4)
		{
			switch (LedCunt)
			{
				case 0:
				{
					GPIOD ->BSRRH |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRH |= GPIO_Pin_7;
					//printf("Led 1 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 1:
				{
					GPIOD ->BSRRL |= GPIO_Pin_13;
					GPIOD ->BSRRH |= GPIO_Pin_14;
					GPIOD ->BSRRH |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1/2 Light\n");
					LedDelay();
					LedCunt = 0;
				}
			}
		}
		else if(keyset == 5)
		{
			switch (LedCunt)
			{
				case 0:
				{
					GPIOD ->BSRRH |= GPIO_Pin_13;
					GPIOD ->BSRRL |= GPIO_Pin_14;
					GPIOD ->BSRRH |= GPIO_Pin_15;
					GPIOC ->BSRRL |= GPIO_Pin_7;
					//printf("Led 1 Light\n");
					LedDelay();
					LedCunt += 1;
				}
				case 1:
				{
					GPIOD ->BSRRL |= GPIO_Pin_13;
					GPIOD ->BSRRH |= GPIO_Pin_14;
					GPIOD ->BSRRL |= GPIO_Pin_15;
					GPIOC ->BSRRH |= GPIO_Pin_7;
					//printf("Led 1/2 Light\n");
					LedDelay();
					LedCunt = 0;
				}
			}
		}
		else if (keyset == 6)
			keyset = 0;
	}
}

__task void run(void)
{
	tsk_1 = os_tsk_create(LedTest,0);
	tsk_2 = os_tsk_create(Inter_Uart,0);
	tsk_3 = os_tsk_create(Exti_key,0);
	
	os_tsk_delete_self();
}


int main(void)
{
	LedCunt = 0;
	LedInit();
	usartinit();
	NVIC_Config();
	
	keyinit();
	EXTI_Configuration();
	NVIC_Configuration();
	
	os_sys_init(run);
	for(;;);
}
