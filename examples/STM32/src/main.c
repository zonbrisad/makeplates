/**
 *---------------------------------------------------------------------------
 * @file    main.c
 * @brief   A test example for STM32 Cortex M3 MCU
 *
 * @author  GPLv2
 * @date    2016-02-24
 * @licence Peter Malmberg <peter.malmberg@gmail.com>
 *
 *---------------------------------------------------------------------------
 */


#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


/**
 * Macro declarations
 *------------------------------------------------------------------
 */

/**
 * Variable declarations
 *------------------------------------------------------------------
 */

/**
 * Prototype declarations
 *------------------------------------------------------------------
 */

/**
 * Code
 *------------------------------------------------------------------
 */
int main() {
	
	 int i;
	/* Initialize Leds mounted on STM32 board */
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* Initialize LED which connected to PC6,9, Enable the Clock*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	
	
	
	//printf("KAlle\n");
	//SH_SendChar('B');
	//SH_SendString("Test of semihosting\n");
	
	
	while(1){
		//printf("A");
		//SH_SendChar('A');
		GPIOC->ODR ^= GPIO_Pin_13;
		  for(i=0;i<0x200000;i++) {
			}
	}
	
}
