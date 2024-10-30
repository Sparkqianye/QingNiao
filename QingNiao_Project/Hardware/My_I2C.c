 #include "stm32f4xx.h"                  // Device header
#include "Delay.h"

//PC10 SCL   PC12 SDA
void MyI2C_W_SCL(uint8_t BitValue)
{
		GPIO_WriteBit(GPIOC,GPIO_Pin_10,(BitAction)BitValue);
		Delay_us (10);
}
void MyI2C_W_SDA(uint8_t BitValue)
{
		GPIO_WriteBit(GPIOC,GPIO_Pin_12,(BitAction)BitValue);
		Delay_us (10);
}


uint8_t MyI2C_R_SDA(void)
{
		uint8_t BitValue;
		BitValue = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12);
		Delay_us(10);
		return BitValue;
}	


void MyI2C_Init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		
		GPIO_SetBits(GPIOC, GPIO_Pin_10 | GPIO_Pin_12);
//  RCC->AHB1ENR   |=  (1ul << 1);
//  GPIOB->MODER   &= ~((3ul << 2*8));
//  GPIOB->MODER   |=  ((1ul << 2*8));
//  GPIOB->OTYPER  &= ~((1ul <<   8));
//  GPIOB->OSPEEDR &= ~((3ul << 2*8));
//  GPIOB->OSPEEDR |=  ((1ul << 2*8));
//  GPIOB->PUPDR   &= ~((3ul << 2*8));
//  GPIOB->BSRR    &= ~((1ul << 8));
//  GPIOB->BSRR    |= 0ul << 8;
//  
//  GPIOB->MODER   &= ~((3ul << 2*9));
//  GPIOB->MODER   |=  ((1ul << 2*9));
//  GPIOB->OTYPER  &= ~((1ul <<   9));
//  GPIOB->OSPEEDR &= ~((3ul << 2*9));
//  GPIOB->OSPEEDR |=  ((1ul << 2*9));
//  GPIOB->PUPDR   &= ~((3ul << 2*9));
//  GPIOB->BSRR    &= ~((1ul << 9));
//  GPIOB->BSRR    |= 0ul << 9;
  

}


void MyI2C_Start(void)
{
		MyI2C_W_SDA(1);
		MyI2C_W_SCL(1);
		MyI2C_W_SDA(0);
		MyI2C_W_SCL(0);
}
void MyI2C_Stop(void)
{
		MyI2C_W_SDA(0);
		MyI2C_W_SCL(1);
		MyI2C_W_SDA(1);
}
void MyI2C_SendByte(uint8_t Byte)
{	
		uint8_t i;
		for(i = 0; i<8;i++)
		{
			MyI2C_W_SDA(Byte & (0x80 >> i));
			MyI2C_W_SCL(1);
			MyI2C_W_SCL(0);
		}
	
}

uint8_t MyI2C_ReceiveByte(void)
{
		uint8_t  i, Byte = 0x00;
		for(i=0;i<8;i++)
		{
			MyI2C_W_SDA(1);
			MyI2C_W_SCL(1);
			if(MyI2C_R_SDA() == 1){Byte |= (0x80 >> i);}
			MyI2C_W_SCL(0);
		}
		return Byte;
}	

void MyI2C_SendAck(uint8_t AckBit)
{	
			MyI2C_W_SDA(AckBit);
			MyI2C_W_SCL(1);
			MyI2C_W_SCL(0);

}

uint8_t MyI2C_ReceiveAck(void)
{
			uint8_t AckBit;
			MyI2C_W_SDA(1);
			MyI2C_W_SCL(1);
			AckBit = MyI2C_R_SDA();
			MyI2C_W_SCL(0);
			return AckBit;
}	
