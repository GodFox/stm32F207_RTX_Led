#include "irq.h"
#include "usart.h"


void NVIC_Config(void)
{
  	NVIC_InitTypeDef NVIC_InitStructure;

  	/* Enable the USARTx Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;			//�Դ���1�����ж�ʹ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		//�жϵ����ȼ�
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  	NVIC_Init(&NVIC_InitStructure);
}

void USART1_IRQHandler(void)
{
  unsigned char temp;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)		//���ڽ��ռĴ����ж�
  {
    /* Read one byte from the receive data register */
    //RxBuffer[RxCounter++] = (USART_ReceiveData(USART2) & 0x7F);
	temp = 	(USART_ReceiveData(USART1));						//��ȡ����1���յ�������
	sendchar(temp);						//��ӡ����
    //if(RxCounter == NbrOfDataToRead)
    //{
      /* Disable the EVAL_COM1 Receive interrupt */
      //USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
    //}
  }

  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)	//���ڷ��ͼĴ����ж�
  {   
    /* Write one byte to the transmit data register */
    USART_SendData(USART1, tempbuf[TxCounter++]);				//��������

    if(TxCounter == NbrOfDataToTransfer)					//���ͽ����ж�
    {
      /* Disable the EVAL_COM1 Transmit interrupt */
      USART_ITConfig(USART1, USART_IT_TXE, DISABLE);		//�����ж�
    }
  }
}
