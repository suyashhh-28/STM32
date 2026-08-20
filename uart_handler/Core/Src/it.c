/*
 * it.c
 *
 *  Created on: Aug 20, 2026
 *      Author: suyash
 */
#include "stm32f4xx_hal.h"

void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
