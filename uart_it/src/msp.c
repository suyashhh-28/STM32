/*
 * msp.c
 *
 *  Created on: Aug 20, 2026
 *      Author: suyash
 */
#include "stm32f4xx_hal.h"
void HAL_MspInit(void){
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	SCB->SHCSR |=0x7<<16;
	HAL_NVIC_SetPriority(MemoryManagement_IRQn,0,0);
	HAL_NVIC_SetPriority(BusFault_IRQn,0,0);
	HAL_NVIC_SetPriority(UsageFault_IRQn,0,0);

}
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef gpio_uart = {0};
    if (huart->Instance == USART2)
    {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        gpio_uart.Pin = GPIO_PIN_2 | GPIO_PIN_3;
        gpio_uart.Mode = GPIO_MODE_AF_PP;
        gpio_uart.Pull = GPIO_PULLUP;
        gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
        gpio_uart.Alternate = GPIO_AF7_USART2;

        HAL_GPIO_Init(GPIOA, &gpio_uart);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
        HAL_NVIC_SetPriority(USART2_IRQn,15,0);

    }
}
