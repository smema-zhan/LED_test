#include "main.h"
#include "string.h"
#include "CallUart.h"
#include "usart.h"

static uint8_t led_flag = 0;
static uint8_t continue_flag = 0;

void LED_control(void)
{
    if (strcmp((char *)usart_rx_buffer, "start") == 0)
    {
        led_flag = 1;
        HAL_UART_Transmit(&USER_UART, "LED start", sizeof("LED start"), 0xffff);
        memset(usart_rx_buffer, 0x00, USART_BUFFER_SIZE);
        dma_recv_len = 0;
        UartFlag = 0;
    }
    else if (strcmp((char *)usart_rx_buffer, "stop") == 0)
    {
        led_flag = 0;
        HAL_UART_Transmit(&USER_UART, "LED stop", sizeof("LED stop"), 0xffff);
        memset(usart_rx_buffer, 0x00, USART_BUFFER_SIZE);
        dma_recv_len = 0;
        UartFlag = 0;
    }
    else if (dma_recv_len > 0)
    {
        led_flag = 0;
        HAL_UART_Transmit(&USER_UART, "unknow command", sizeof("unknow command"), 0xffff);
        memset(usart_rx_buffer, 0x00, USART_BUFFER_SIZE);
        dma_recv_len = 0;
        UartFlag = 0;
    }
    if ((uint8_t)HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 1 && led_flag == 1)
    {
        HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
        HAL_Delay(1000);
        HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
        HAL_Delay(1000);
        continue_flag = 1;
    }
    else if (led_flag == 0 && continue_flag == 1)
    {
        HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_SET);
        continue_flag = 0;
    }
}

void Loop(void)
{
    LED_control();
}
