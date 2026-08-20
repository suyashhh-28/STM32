/*
 * it.c
 *
 *  Created on: Aug 20, 2026
 *      Author: suyash
 */
#include "stm32f4xx_hal.h"
#include "main.h"

extern UART_HandleTypeDef huart2;

void SysTick_Handler(void)
{
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
}

void USART2_IRQHandler(void)
{
    HAL_UART_IRQHandler(&huart2);
}
