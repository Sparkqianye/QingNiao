#include "stm32f4xx.h"                  // Device header
#include "main.h"


static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

extern void LED_Init(void);
uint32_t Data, Duty;

int main(void)
{
//  LED_Init();
  GY86_Init();
  Serial_Init();
  PWM_Init();
  ICTIM2CH1_2_Init();
  
  while(1){   
    
//  int16_t hmcX,hmcY,hmcZ;
//	HMC5883L_GetData(&hmcX,&hmcY,&hmcZ);
//  Serial_Printf("hmcX = %d\r\n",hmcX);
//  Delay_ms(100);
//  Serial_Printf("hmcY = %d\r\n",hmcY);
//  Delay_ms(100);
//  Serial_Printf("hmcZ = %d\r\n",hmcZ);
//  Delay_ms(100);
//    
//  int16_t mpuX,mpuY,mpuZ,gyroX,gyroY,gyroZ;
//	MPU6000_GetData(&mpuX,&mpuY,&mpuZ,&gyroX,&gyroY,&gyroZ);
//	Serial_Printf("mpuX = %d\r\n",mpuX);
//  Delay_ms(100);
//  Serial_Printf("mpuY = %d\r\n",mpuY);
//  Delay_ms(100);
//  Serial_Printf("mpuZ = %d\r\n",mpuZ);
//  Delay_ms(100);
//  Serial_Printf("gyroX = %d\r\n",gyroX);
//  Delay_ms(100);
//  Serial_Printf("gyroY = %d\r\n",gyroY);
//  Delay_ms(100);
//  Serial_Printf("gyroZ = %d\r\n",gyroZ);
//  Delay_ms(100);
    
    
		Data = (TIM_GetCapture2(TIM2)+1)*10/(TIM_GetCapture1(TIM2)+1);
//		Data = TIM_GetCapture1(TIM2);
	
		Duty = Data*5/7;
    PWM_SetDuty1(Duty);
		PWM_SetDuty2(Duty);
		PWM_SetDuty3(Duty);
		PWM_SetDuty4(Duty);
		
		Serial_Printf("Data:%d\r\n",Duty);
//    PWM_SetDuty1(10);//PC6
//    PWM_SetDuty2(12);//PC7
//    PWM_SetDuty3(14);//PC8
//    PWM_SetDuty4(8);//PC9
    
    
//    Serial_Printf("TIM2_CH1_2:\r\n");//PA0
//    Serial_Printf("CH1:%d\r\n",TIM_GetCapture1(TIM2));
//    Serial_Printf("CH2:%d\r\n",TIM_GetCapture2(TIM2));
//    Serial_Printf("Freq:%d   ",(1000000 / (TIM_GetCapture1(TIM2)+1)));
//    Serial_Printf("Duty:%d\r\n\r\n",(TIM_GetCapture2(TIM2)+1)*100/(TIM_GetCapture1(TIM2)+1));
//    
//    Serial_Printf("TIM5_CH1_2:\r\n");//PA1
//    Serial_Printf("CH1:%d\r\n",TIM_GetCapture1(TIM5));
//    Serial_Printf("CH2:%d\r\n",TIM_GetCapture2(TIM5));
//    Serial_Printf("Freq:%d   ",(1000000 / (TIM_GetCapture2(TIM5)+1)));
//    Serial_Printf("Duty:%d\r\n\r\n",(TIM_GetCapture1(TIM5)+1)*100/(TIM_GetCapture2(TIM5)+1));
//    
//    Serial_Printf("TIM4_CH1_2:\r\n");//PB6
//    Serial_Printf("CH1:%d\r\n",TIM_GetCapture1(TIM4));
//    Serial_Printf("CH2:%d\r\n",TIM_GetCapture2(TIM4));
//    Serial_Printf("Freq:%d   ",(1000000 / (TIM_GetCapture1(TIM4)+1)));
//    Serial_Printf("Duty:%d\r\n\r\n",(TIM_GetCapture2(TIM4)+1)*100/(TIM_GetCapture1(TIM4)+1));
    
//    Serial_Printf("TIM4_CH3_4:\r\n");//PB8
//    Serial_Printf("CH3:%d\r\n",TIM_GetCapture3(TIM4));
//    Serial_Printf("CH4:%d\r\n",TIM_GetCapture4(TIM4));
//    Serial_Printf("Freq:%d   ",(1000000 / (TIM_GetCapture3(TIM4)+1)));
//    Serial_Printf("Duty:%d\r\n\r\n\r\n",((TIM_GetCapture4(TIM4)+1)*100/(TIM_GetCapture3(TIM4)+1))+1);
//    Delay_s(2);
//    Serial_Printf("TIM2_CH3_4:\r\n");//PA2
//    Serial_Printf("CH3:%d\r\n",TIM_GetCapture3(TIM2));
//    Serial_Printf("CH4:%d\r\n",TIM_GetCapture4(TIM2));
//    Serial_Printf("Freq:%d   ",(1000000 / (TIM_GetCapture3(TIM2)+1)));
//    Serial_Printf("Duty:%d\r\n\r\n\r\n",((TIM_GetCapture4(TIM2)+1)*100/(TIM_GetCapture3(TIM2)+1))+1);
    //PWM: PC6789   TIM3_CH1234
    //考虑改为：PA0--TIM2CH1  PA1--TIM5CH2  PA2--TIM2CH3  PA3--TIM5CH4  PB8--TIM4CH3  PB6--TIM4CH1  
    
    
  }
  
}


/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime;

  while(uwTimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  { 
    uwTimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

