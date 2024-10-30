#include "stm32f4xx.h"                  // Device header
#include <stdio.h>
#include <stdarg.h>

void TTL_USB_Init()
{
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//PA11TX,PA12RX
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_USART6);
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_USART6);
  
  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_Init(USART6, &USART_InitStructure);
  
  
  
  USART_Cmd(USART6, ENABLE);
  
}

void TTL_USB_SendByte(uint8_t Byte)
{
	USART_SendData(USART6, Byte);
	while (USART_GetFlagStatus(USART6, USART_FLAG_TXE) == RESET);
}

void TTL_USB_SendArray(uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		TTL_USB_SendByte(Array[i]);
	}
}

void TTL_USB_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		TTL_USB_SendByte(String[i]);
	}
}

//int fputc(int ch, FILE *f)
//{
//	TTL_USB_SendByte(ch);
//	return ch;
//}

//void TTL_USB_Printf(char *format, ...)
//{
//	char String[100];
//	va_list arg;
//	va_start(arg, format);
//	vsprintf(String, format, arg);
//	va_end(arg);
//	TTL_USB_SendString(String);
//}

