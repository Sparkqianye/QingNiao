	;#include "stm32f4xx.h"                  // Device header
	;#include "main.h"
	;#define  RCC_AHB1ENR_GPIOAEN                 ((uint32_t)0x00000001)
	;__IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
	;#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000)
	;__IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
	;__IO uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
	;__IO uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
	;__IO uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
	;__IO uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
	;__IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
	;__IO uint32_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
	;__IO uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
	;__IO uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
	
RCC_AHB1ENR				EQU		0x40023830
GPIOA_MODER				EQU		0x40020000
GPIOA_OTYPER			EQU		0x40020004
GPIOA_OSPEEDR			EQU		0x40020008
GPIOA_PUPDR				EQU		0x4002000C
GPIOA_BSRR				EQU		0x40020018
	
	
			AREA		EXAMPLE,CODE,READONLY
			EXPORT		LED_Init
			EXPORT		LED_Onnn
			EXPORT		LED_Offf

			ENTRY
LED_Init

;			PUSH {R0,R1,R2,R3,LR}
	;RCC->AHB1ENR |=  (1ul << 0);                  /* Enable GPIOA clock         */

			LDR R0,=RCC_AHB1ENR			;��RCC_AHB1ENR�Ĵ�����ַ����R0
			MOV	R1,#(1<<0)        		;��1����0λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			ORR R2,R2,R1				;��R1��ֵ����R2��Ž�R2
			STR R2,[R0] 				;��R2��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����
	
	
	;GPIOA->MODER   &= ~((3ul << 2*1));	ȡ����MVN R0,#0
	
			LDR R0,=GPIOA_MODER         ;��GPIOA_MODER�Ĵ�����ַ����R0
			MVN	R1,#(3<<2)           	;��3ȡ��������λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			AND R3,R2,R1				;��R1��ֵ����R2��Ž�R3
			STR R3,[R0] 				;��R3��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����


	;GPIOA->MODER   |=  ((1ul << 2*1));
	
			LDR R0,=GPIOA_MODER 		;��GPIOA_MODER�Ĵ�����ַ����R0
			MOV	R1,#(1<<2)			    ;��1����2λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			ORR R2,R2,R1				;��R1��ֵ����R2��Ž�R2
			STR R2,[R0] 				;��R2��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����
	
	
	;GPIOA->OTYPER  &= ~((1ul <<   1));	��λ�룺TST R1,#0xffe
			
			LDR R0,=GPIOA_OTYPER        ;��GPIOA_OTYPER�Ĵ�����ַ����R0
			MVN	R1,#(1<<1)           	;��1ȡ������1λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			AND R3,R2,R1				;��R1��ֵ����R2��Ž�R3
			STR R3,[R0] 				;��R3��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����


	;GPIOA->OSPEEDR &= ~((3ul << 2*1));
			
			LDR R0,=GPIOA_OSPEEDR       ;��GPIOA_OSPEEDR�Ĵ�����ַ����R0
			MVN	R1,#(3<<2)		        ;��ȡ������2λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			AND R3,R2,R1				;��R1��ֵ����R2��Ž�R3
			STR R3,[R0] 				;��R3��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����


	;GPIOA->OSPEEDR |=  ((1ul << 2*1));
	
			LDR R0,=GPIOA_OSPEEDR 		;��GPIOA_OSPEEDR�Ĵ�����ַ����R0
			MOV	R1,#(1<<2)              ;��1����2λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			ORR R2,R2,R1				;��R1��ֵ����R2��Ž�R2
			STR R2,[R0] 				;��R2��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����
	
	
	;GPIOA->PUPDR   &= ~((3ul << 2*1));
	
			LDR R0,=GPIOA_PUPDR		    ;��GPIOA_PUPDR�Ĵ�����ַ����R0
			MVN	R1,#(3<<2)		        ;��3ȡ������2λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			AND R3,R2,R1				;��R1��ֵ����R2��Ž�R3
			STR R3,[R0] 				;��R2��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����
			
			
;			POP {R0,R1,R2,R3,PC}

LED_Offf

;			PUSH {R0,R1,R2,LR}

	;GPIOA->BSRR   &= ~((1ul << 1));	ȡ����MVN R0,#0
	
			LDR R0,=GPIOA_BSRR         ;��GPIOA_MODER�Ĵ�����ַ����R0
			MVN	R1,#(0<<1)           	;��3ȡ��������λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			AND R3,R2,R1				;��R1��ֵ����R2��Ž�R3
			STR R3,[R0] 				;��R3��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����
	;GPIOA->BSRR |= 0ul << 1;
	
			LDR R0,=GPIOA_BSRR 			;��GPIOA_BSRR�Ĵ�����ַ����R0
			MOV	R1,#(0<<1)		        ;��0����1λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			ORR R2,R2,R1				;��R1��ֵ����R2��Ž�R2
			STR R2,[R0] 				;��R2��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����
			
LED_Onnn

;			PUSH {R0,R1,R2,LR}
	;GPIOA->BSRR   &= ~((1ul << 1));	ȡ����MVN R0,#0
	
			LDR R0,=GPIOA_BSRR         ;��GPIOA_MODER�Ĵ�����ַ����R0
			MVN	R1,#(0<<1)           	;��3ȡ��������λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			AND R3,R2,R1				;��R1��ֵ����R2��Ž�R3
			STR R3,[R0] 				;��R3��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����
	;GPIOA->BSRR |= 0ul << 1;
	
			LDR R0,=GPIOA_BSRR 			;��GPIOA_BSRR�Ĵ�����ַ����R0
			MOV	R1,#(1<<1)		        ;��1����1λ�Ž�R1
			LDR R2,[R0]					;���洢����ַΪR0�������ݶ���R2
			ORR R2,R2,R1				;��R1��ֵ����R2��Ž�R2
			STR R2,[R0] 				;��R2��ֵ�Ž�R0��ַ����Ӧ�ļĴ�����
			
			;POP {R0,R1,R2,PC}
			;NOP
			

	
			END

