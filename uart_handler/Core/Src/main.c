#include "stm32f4xx_hal.h"
#include <string.h>
#define TRUE 1
#define FALSE 0
void SystemClockConfig(void);
void UART2_Init(void);
void ErrorHandler(void);
uint8_t data_buffer[100];
uint8_t rcvd_data;
uint8_t reception_complete=FALSE;
UART_HandleTypeDef huart2;
char *user_data= "the application is running\r\n";
int main(void)
{
    HAL_Init();
    SystemClockConfig();
    UART2_Init();
    uint16_t len_of_data=strlen(user_data);
    HAL_UART_Transmit(&huart2,(uint8_t *)user_data,len_of_data,HAL_MAX_DELAY);



    uint32_t count = 0;
    uint8_t convert_to_capital(uint8_t data)
    {
        if (data >= 'a' && data <= 'z')
        {
            data = data - ('a' - 'A');
        }

        return data;
    }
    while(1) {
            HAL_UART_Receive(&huart2, &rcvd_data, 1, HAL_MAX_DELAY);

            HAL_UART_Transmit(&huart2, &rcvd_data, 1, HAL_MAX_DELAY);

            if(rcvd_data == '\r' || rcvd_data == '\n') {
                data_buffer[count] = '\0';
                break;
            }
            else if (count < sizeof(data_buffer) - 1) {
            	data_buffer[count++] = convert_to_capital(rcvd_data);
            }
        }

}


void SystemClockConfig(void)
{
}

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
    }
}



void ErrorHandler(void)
{
    __disable_irq();

    while (1)
    {
    }
}
