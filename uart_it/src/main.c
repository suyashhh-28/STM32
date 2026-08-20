#include "stm32f4xx_hal.h"
#include <string.h>

#define TRUE  1
#define FALSE 0

void SystemClockConfig(void);
void UART2_Init(void);
void ErrorHandler(void);

UART_HandleTypeDef huart2;

uint8_t data_buffer[100];
uint8_t rcvd_data;
uint16_t count = 0;
volatile uint8_t reception_complete = FALSE;

char *user_data = "the application is running\r\n";

int main(void)
{
    HAL_Init();
    SystemClockConfig();
    UART2_Init();

    uint16_t len_of_data = (uint16_t)strlen(user_data);
    HAL_UART_Transmit(&huart2, (uint8_t *)user_data, len_of_data, HAL_MAX_DELAY);

    // Arm the first byte reception in interrupt mode
    HAL_UART_Receive_IT(&huart2, &rcvd_data, 1);

    while (1)
    {
        if (reception_complete == TRUE)
        {
            HAL_UART_Transmit(&huart2, data_buffer, count, HAL_MAX_DELAY);

            count = 0;
            reception_complete = FALSE;
        }  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        if (rcvd_data == '\r' || rcvd_data == '\n')
        {
            if (count < sizeof(data_buffer) - 2)
            {
                data_buffer[count++] = '\r';
                data_buffer[count++] = '\n';
            }
            reception_complete = TRUE;
        }
        else
        {
            if (count < sizeof(data_buffer) - 1)
            {
                data_buffer[count++] = rcvd_data;
            }
        }
        HAL_UART_Receive_IT(&huart2, &rcvd_data, 1);
    }}

void UART2_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        ErrorHandler();
    }}

void SystemClockConfig(void)
{
}

void ErrorHandler(void)
{
    __disable_irq();
    while (1)
    {
    }
}

