#include "stm32f2xx.h"
#include "usart.h"
#include "stdio.h"

unsigned char keyset = 0;

void keyinit(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
}


void EXTI_Configuration(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	
	EXTI_InitStructure.EXTI_Line    = EXTI_Line13;
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,GPIO_PinSource13);
	
	
	EXTI_InitStructure.EXTI_Line    = EXTI_Line0;
	EXTI_Init(&EXTI_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,GPIO_PinSource0);
	
	EXTI_InitStructure.EXTI_Line    = EXTI_Line1;
	EXTI_Init(&EXTI_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,GPIO_PinSource1);
	
	EXTI_InitStructure.EXTI_Line    = EXTI_Line4;
	EXTI_Init(&EXTI_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,GPIO_PinSource4);
	
	EXTI_InitStructure.EXTI_Line    = EXTI_Line5;
	EXTI_Init(&EXTI_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,GPIO_PinSource5);
	
	EXTI_InitStructure.EXTI_Line    = EXTI_Line6;
	EXTI_Init(&EXTI_InitStructure);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,GPIO_PinSource6);
	
}

void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
// 	NVIC_InitTypeDef NVIC_InitStructure1;
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_Init(&NVIC_InitStructure);
}


void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
			EXTI_ClearITPendingBit(EXTI_Line13);	
			if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
				{
					//printf("key2\n");
					GPIO_ResetBits(GPIOC,GPIO_Pin_13);
					keyset = 2;
				}
		}
}

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line0);
				if(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0))
				{
					//printf("key1\n");
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);
					keyset = 1;
				}
    }
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line1);
				if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1))
				{
					//printf("key3\n");
					GPIO_ResetBits(GPIOE,GPIO_Pin_1);
					keyset = 3;
				}
    }
}

void EXTI4_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line4);
				if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4))
				{
					//printf("key4\n");
					GPIO_ResetBits(GPIOE,GPIO_Pin_4);
					keyset = 4;
				}
    }
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line5);
				if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5))
				{
					//printf("key5\n");
					GPIO_ResetBits(GPIOE,GPIO_Pin_5);
					keyset = 5;
				}
    }
	if (EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
        EXTI_ClearITPendingBit(EXTI_Line6);
				if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6))
				{
					//printf("key6\n");
					GPIO_ResetBits(GPIOE,GPIO_Pin_6);
					keyset = 6;
				}
    }
}
