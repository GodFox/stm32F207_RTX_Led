#include "irq.h"
#include "usart.h"


void NVIC_Config(void)
{
  	NVIC_InitTypeDef NVIC_InitStructure;

  	/* Enable the USARTx Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//对串口1进行中断使能
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//中断的优先级
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
}

void USART1_IRQHandler(void)
{
  unsigned char temp;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)		//串口接收寄存器中断
  {
    /* Read one byte from the receive data register */
    //RxBuffer[RxCounter++] = (USART_ReceiveData(USART2) & 0x7F);
	temp = 	(USART_ReceiveData(USART1));						//获取串口1接收到的内容
	sendchar(temp);						//打印出来
    //if(RxCounter == NbrOfDataToRead)
    //{
      /* Disable the EVAL_COM1 Receive interrupt */
      //USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
    //}
  }

  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)	//串口发送寄存器中断
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(USART1, tempbuf[TxCounter++]);				//发送内容

    if(TxCounter == NbrOfDataToTransfer)					//发送结束判断
    {
      /* Disable the EVAL_COM1 Transmit interrupt */
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);		//禁用中断
    }
  }
}
