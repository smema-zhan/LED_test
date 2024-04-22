#include "CallUart.h"
#include "usart.h"
#include "string.h"

uint8_t dma_recv_len = 0; // 本次数据接收的数量
uint8_t usart_rx_buffer[USART_BUFFER_SIZE] = {0};
uint8_t usart_tx_buffer[USART_BUFFER_SIZE] = {0};

void startUart(UART_HandleTypeDef *huart)
{
    memset(usart_tx_buffer, 0x00, USART_BUFFER_SIZE);
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

            ProcessRecvCmd(usart_rx_buffer,usart_tx_buffer);

            HAL_UART_Transmit(&USER_UART, usart_tx_buffer, strlen((char *)usart_tx_buffer), 0xffff);
            memset(usart_tx_buffer, 0x00, USART_BUFFER_SIZE);
            memset(usart_rx_buffer, 0x00, USART_BUFFER_SIZE);
            // 再次打开DMA
            HAL_UART_Receive_DMA(&USER_UART, usart_rx_buffer, USART_BUFFER_SIZE);
        }
    }
}

__weak void ProcessRecvCmd(uint8_t *usart_rx_buffer, uint8_t *usart_tx_buffer)
{
  UNUSED(usart_rx_buffer);
  UNUSED(usart_tx_buffer);
}