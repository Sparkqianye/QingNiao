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

			LDR R0,=RCC_AHB1ENR			;将RCC_AHB1ENR寄存器地址放在R0
			MOV	R1,#(1<<0)        		;将1左移0位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			ORR R2,R2,R1				;将R1的值或上R2后放进R2
			STR R2,[R0] 				;将R2的值放进R0地址所对应的寄存器中
	
	
	;GPIOA->MODER   &= ~((3ul << 2*1));	取反：MVN R0,#0
	
			LDR R0,=GPIOA_MODER         ;将GPIOA_MODER寄存器地址放在R0
			MVN	R1,#(3<<2)           	;将3取反左移两位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			AND R3,R2,R1				;将R1的值与上R2后放进R3
			STR R3,[R0] 				;将R3的值放进R0地址所对应的寄存器中


	;GPIOA->MODER   |=  ((1ul << 2*1));
	
			LDR R0,=GPIOA_MODER 		;将GPIOA_MODER寄存器地址放在R0
			MOV	R1,#(1<<2)			    ;将1左移2位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			ORR R2,R2,R1				;将R1的值或上R2后放进R2
			STR R2,[R0] 				;将R2的值放进R0地址所对应的寄存器中
	
	
	;GPIOA->OTYPER  &= ~((1ul <<   1));	按位与：TST R1,#0xffe
			
			LDR R0,=GPIOA_OTYPER        ;将GPIOA_OTYPER寄存器地址放在R0
			MVN	R1,#(1<<1)           	;将1取反左移1位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			AND R3,R2,R1				;将R1的值与上R2后放进R3
			STR R3,[R0] 				;将R3的值放进R0地址所对应的寄存器中


	;GPIOA->OSPEEDR &= ~((3ul << 2*1));
			
			LDR R0,=GPIOA_OSPEEDR       ;将GPIOA_OSPEEDR寄存器地址放在R0
			MVN	R1,#(3<<2)		        ;将取反左移2位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			AND R3,R2,R1				;将R1的值与上R2后放进R3
			STR R3,[R0] 				;将R3的值放进R0地址所对应的寄存器中


	;GPIOA->OSPEEDR |=  ((1ul << 2*1));
	
			LDR R0,=GPIOA_OSPEEDR 		;将GPIOA_OSPEEDR寄存器地址放在R0
			MOV	R1,#(1<<2)              ;将1左移2位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			ORR R2,R2,R1				;将R1的值或上R2后放进R2
			STR R2,[R0] 				;将R2的值放进R0地址所对应的寄存器中
	
	
	;GPIOA->PUPDR   &= ~((3ul << 2*1));
	
			LDR R0,=GPIOA_PUPDR		    ;将GPIOA_PUPDR寄存器地址放在R0
			MVN	R1,#(3<<2)		        ;将3取反左移2位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			AND R3,R2,R1				;将R1的值与上R2后放进R3
			STR R3,[R0] 				;将R2的值放进R0地址所对应的寄存器中
			
			
;			POP {R0,R1,R2,R3,PC}

LED_Offf

;			PUSH {R0,R1,R2,LR}

	;GPIOA->BSRR   &= ~((1ul << 1));	取反：MVN R0,#0
	
			LDR R0,=GPIOA_BSRR         ;将GPIOA_MODER寄存器地址放在R0
			MVN	R1,#(0<<1)           	;将3取反左移两位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			AND R3,R2,R1				;将R1的值与上R2后放进R3
			STR R3,[R0] 				;将R3的值放进R0地址所对应的寄存器中
	;GPIOA->BSRR |= 0ul << 1;
	
			LDR R0,=GPIOA_BSRR 			;将GPIOA_BSRR寄存器地址放在R0
			MOV	R1,#(0<<1)		        ;将0左移1位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			ORR R2,R2,R1				;将R1的值或上R2后放进R2
			STR R2,[R0] 				;将R2的值放进R0地址所对应的寄存器中
			
LED_Onnn

;			PUSH {R0,R1,R2,LR}
	;GPIOA->BSRR   &= ~((1ul << 1));	取反：MVN R0,#0
	
			LDR R0,=GPIOA_BSRR         ;将GPIOA_MODER寄存器地址放在R0
			MVN	R1,#(0<<1)           	;将3取反左移两位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			AND R3,R2,R1				;将R1的值与上R2后放进R3
			STR R3,[R0] 				;将R3的值放进R0地址所对应的寄存器中
	;GPIOA->BSRR |= 0ul << 1;
	
			LDR R0,=GPIOA_BSRR 			;将GPIOA_BSRR寄存器地址放在R0
			MOV	R1,#(1<<1)		        ;将1左移1位放进R1
			LDR R2,[R0]					;将存储器地址为R0的字数据读入R2
			ORR R2,R2,R1				;将R1的值或上R2后放进R2
			STR R2,[R0] 				;将R2的值放进R0地址所对应的寄存器中
			
			;POP {R0,R1,R2,PC}
			;NOP
			

	
			END

