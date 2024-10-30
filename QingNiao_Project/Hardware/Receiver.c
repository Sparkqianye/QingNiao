//PB8为3通道PWM信号口,对应TIM4_CH3
//改为PA0连接通道3，对应TIM2_CH1
#include "stm32f4xx.h"                  // Device header

void ICTIM1CH1_2_Init(void)//PA8--TIM1CH1
{
  RCC_APB1PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1);

  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频系数（1，不分频）
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//对齐模式（向上对齐）
  TIM_TimeBaseInitStructure.TIM_Period = 65536-1;//arr
  TIM_TimeBaseInitStructure.TIM_Prescaler = 16-1;//psc
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//定时器溢出增加倍数
  TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

  
  TIM_ICInitTypeDef TIM_ICInitStructure;
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//定时器通道PA8_TIM1_CH1
  TIM_ICInitStructure.TIM_ICFilter = 0x0F;//滤波（最大0x0F）
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//计数方式（向上计数法）
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//输入预分频器
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//输入方式（直接输入方式）
  TIM_ICInit(TIM1,&TIM_ICInitStructure);
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//通道2
  TIM_ICInitStructure.TIM_ICFilter = 0x0F;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//计数方式（向下计数法）
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//输入方式（间接输入方式）
  TIM_ICInit(TIM1,&TIM_ICInitStructure);


  
  TIM_SelectInputTrigger(TIM1,TIM_TS_TI1FP1); 
  TIM_SelectSlaveMode(TIM1,TIM_SlaveMode_Reset);
  
  TIM_Cmd(TIM1,ENABLE);
}

void ICTIM2CH1_2_Init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//PA0
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);

  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频系数（1，不分频）
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//对齐模式（向上对齐）
  TIM_TimeBaseInitStructure.TIM_Period = 65536-1;//arr
  TIM_TimeBaseInitStructure.TIM_Prescaler = 16-1;//psc
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//定时器溢出增加倍数
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

  
  TIM_ICInitTypeDef TIM_ICInitStructure;
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//定时器通道（PB8对应TIM4CH3）//PA0对应TIM2CH1
  TIM_ICInitStructure.TIM_ICFilter = 0x0F;//滤波（最大0x0F）
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//计数方式（向上计数法）
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//输入预分频器
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//输入方式（直接输入方式）
  
  TIM_ICInit(TIM2,&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//通道2
  TIM_ICInitStructure.TIM_ICFilter = 0x0F;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//计数方式（向下计数法）
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//输入方式（间接输入方式）
  TIM_ICInit(TIM2,&TIM_ICInitStructure);


  
  TIM_SelectInputTrigger(TIM2,TIM_TS_TI1FP1); 
  TIM_SelectSlaveMode(TIM2,TIM_SlaveMode_Reset);
  
  TIM_Cmd(TIM2,ENABLE);
}  

void ICTIM4CH1_2_Init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//PB6
  
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);

  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频系数（1，不分频）
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//对齐模式（向上对齐）
  TIM_TimeBaseInitStructure.TIM_Period = 65536-1;//arr
  TIM_TimeBaseInitStructure.TIM_Prescaler = 16-1;//psc
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//定时器溢出增加倍数
  TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);

  
  TIM_ICInitTypeDef TIM_ICInitStructure;
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//定时器通道（PB8对应TIM4CH3）//PA0对应TIM2CH1
  TIM_ICInitStructure.TIM_ICFilter = 0x0F;//滤波（最大0x0F）
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//计数方式（向上计数法）
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//输入预分频器
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//输入方式（直接输入方式） 
  TIM_ICInit(TIM4,&TIM_ICInitStructure);
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//通道2
  TIM_ICInitStructure.TIM_ICFilter = 0x0F;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//计数方式（向下计数法）
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//输入方式（间接输入方式）
  TIM_ICInit(TIM4,&TIM_ICInitStructure);


  
  TIM_SelectInputTrigger(TIM4,TIM_TS_TI1FP1); 
  TIM_SelectSlaveMode(TIM4,TIM_SlaveMode_Reset);
  
  TIM_Cmd(TIM4,ENABLE);
}

void ICTIM5CH1_2_Init(void)
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//PA1
  
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5);

  GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频系数（1，不分频）
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//对齐模式（向上对齐）
  TIM_TimeBaseInitStructure.TIM_Period = 65536-1;//arr
  TIM_TimeBaseInitStructure.TIM_Prescaler = 16-1;//psc
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//定时器溢出增加倍数
  TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);

  
  TIM_ICInitTypeDef TIM_ICInitStructure;
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;//定时器通道
  TIM_ICInitStructure.TIM_ICFilter = 0x0F;//滤波（最大0x0F）
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;//计数方式（向上计数法）
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;//输入预分频器
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;//输入方式（直接输入方式）
  TIM_ICInit(TIM5,&TIM_ICInitStructure);
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;//通道1
  TIM_ICInitStructure.TIM_ICFilter = 0x0F;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//计数方式（向下计数法）
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//输入方式（间接输入方式）
  TIM_ICInit(TIM5,&TIM_ICInitStructure);


  
  TIM_SelectInputTrigger(TIM5,TIM_TS_TI2FP2); 
  TIM_SelectSlaveMode(TIM5,TIM_SlaveMode_Reset);
  
  TIM_Cmd(TIM5,ENABLE);
}


void ICTIM4CH3_4_Init(void)
{
  RCC->AHB1ENR |= (1<<1);
  RCC->APB1ENR |= (1<<2);
  
  GPIOB->MODER &= ~(0xff<<12);
	GPIOB->MODER |= (0xaa<<12);
	GPIOB->OSPEEDR |= (0xaa<<12);
	GPIOB->PUPDR |= (0xaa<<12);
  
  GPIOB->AFR[1] &= ~(0xff);
	GPIOB->AFR[0] &= ~(0xffU<<24);
	GPIOB->AFR[0] |= (0x2<<24);
	GPIOB->AFR[0] |= (0x2<<28);
	GPIOB->AFR[1] |= (0x1<<1);
	GPIOB->AFR[1] |= (0x1<<5);
  
  TIM4->CR1 &=~(0Xf<<1);
	TIM4->CR1 |= (0x1<<7);
	TIM4->SMCR &= ~(0x7);
  
  TIM4->PSC = 16-1;
	TIM4->ARR = 65536-1;
  
  TIM4->CCMR2 &= ~(0x3<<0);
	TIM4->CCMR2 |= (0x01<<0);
	TIM4->CCMR2 &= ~(0x3<<2);
	TIM4->CCMR2 &= ~(0xf<<4);
	
	TIM4->CCER |= (0x1<<8);
	TIM4->CCER &= ~(0x1<<9);
	
  TIM_ICInitTypeDef TIM_ICInitStructure;
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;//通道4
  TIM_ICInitStructure.TIM_ICFilter = 0x0F;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//计数方式（向下计数法）
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//输入方式（间接输入方式）
  TIM_ICInit(TIM4,&TIM_ICInitStructure);
//	TIM4->CCMR2 &= ~(0x3<<8);
//	TIM4->CCMR2 |= (0x01<<8);
//	TIM4->CCMR2 &= ~(0x3<<10);
//	TIM4->CCMR2 &= ~(0xf<<12);
//	
//	TIM4->CCER |=(0x1<<12);
//	TIM4->CCER &= ~(0x1<<13);
	
	
	TIM4->DIER |= (0x1<<0);
	TIM4->DIER |= (0x1<<1);
	TIM4->DIER |= (0x1<<2);
	TIM4->DIER |= (0x1<<3);
	TIM4->DIER |= (0x1<<4);
	
	TIM4->CR1 |= (0x1<<0);
  
  TIM_Cmd(TIM4,ENABLE);
}

//void ICTIM2CH3_4_Init(void)//PA2_CH3  PA3_CH4
//{
//  RCC->AHB1ENR |= (1<<0);
//  RCC->APB1ENR |= (1<<0);
//  
//  GPIOA->MODER &= ~(0x0f);
//	GPIOA->MODER |= (0x0a);
//	GPIOA->OSPEEDR |= (0x0a);
//	GPIOA->PUPDR |= (0x0a);
//  
//  GPIOA->AFR[0] &= ~(0xff<<8);
//	GPIOA->AFR[0] |= (0x1<<8);
//	GPIOA->AFR[0] |= (0x1<<12);
//  
//  TIM2->CR1 &=~(0Xf<<1);
//	TIM2->CR1 |= (0x1<<7);
//	TIM2->SMCR &= ~(0x7);
//  
//  TIM2->PSC = 16-1;
//	TIM2->ARR = 65536-1;
//  
//  TIM2->CCMR2 &= ~(0x3<<0);
//	TIM2->CCMR2 |= (0x01<<0);
//	TIM2->CCMR2 &= ~(0x3<<2);
//	TIM2->CCMR2 &= ~(0xf<<4);
//	
//	TIM2->CCER |= (0x1<<8);
//	TIM2->CCER &= ~(0x1<<9);
//	
//  TIM_ICInitTypeDef TIM_ICInitStructure;
//  
//  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;//通道2
//  TIM_ICInitStructure.TIM_ICFilter = 0x0F;
//  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;//计数方式（向下计数法）
//  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_IndirectTI;//输入方式（间接输入方式）
//  TIM_ICInit(TIM2,&TIM_ICInitStructure);
////	TIM4->CCMR2 &= ~(0x3<<8);
////	TIM4->CCMR2 |= (0x01<<8);
////	TIM4->CCMR2 &= ~(0x3<<10);
////	TIM4->CCMR2 &= ~(0xf<<12);
////	
////	TIM4->CCER |=(0x1<<12);
////	TIM4->CCER &= ~(0x1<<13);
//	
//	
//	TIM2->DIER |= (0x1<<0);
//	TIM2->DIER |= (0x1<<1);
//	TIM2->DIER |= (0x1<<2);
//	TIM2->DIER |= (0x1<<3);
//	TIM2->DIER |= (0x1<<4);
//	
//	TIM2->CR1 |= (0x1<<0);
//  
//  TIM_Cmd(TIM2,ENABLE);
//}
