#include "CallUart.h"
#include "usart.h"
#include "string.h"

uint8_t dma_recv_len = 0; // 本次数据接收的数量
uint8_t usart_rx_buffer[USART_BUFFER_SIZE] = {0};
uint8_t UartFlag = 0;//命令是否处理完成

void startUart(UART_HandleTypeDef *huart)
{
    memset(usart_rx_buffer, 0x00, USART_BUFFER_SIZE);
    __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE);
    HAL_UART_Receive_DMA(huart, usart_rx_buffer, USART_BUFFER_SIZE);
}

void UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
    {
        if (huart == &USER_UART)
        {
            __HAL_UART_CLEAR_IDLEFLAG(huart);
            HAL_UART_DMAStop(huart);

            dma_recv_len = USART_BUFFER_SIZE - __HAL_DMA_GET_COUNTER(USER_UART.hdmarx);

            if (UartFlag == 0)
                UartFlag = 1;
            else
                HAL_UART_Transmit(&USER_UART, "mcu busy!", sizeof("mcu busy!"), 0xffff);

            // 再次打开DMA
            HAL_UART_Receive_DMA(&USER_UART, usart_rx_buffer, USART_BUFFER_SIZE);
        }
    }
}