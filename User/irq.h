#include "stm32f2xx.h"

#define countof(a)   (sizeof(a) / sizeof(*(a)))

char tempbuf[] = "\n\rUSART Printf Example: retarget the C library printf function to the USART\n\r" ;
char RxBuffer[50];
unsigned char  RxCounter;
unsigned char  TxCounter;
unsigned char NbrOfDataToTransfer  = countof(tempbuf);
unsigned char NbrOfDataToRead  = 50;

void NVIC_Config(void);
void USART1_IRQHandler(void);
