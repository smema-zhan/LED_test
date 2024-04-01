#ifndef __CALLUART_H
#define __CALLUART_H

#include "main.h"

#define USER_UART huart1
#define USART_BUFFER_SIZE 1024
#define BUF_LIST_SIZE 10

extern void startUart(UART_HandleTypeDef *huart);
extern void UART_RxCpltCallback(UART_HandleTypeDef *huart);

extern uint8_t usart_rx_buffer[USART_BUFFER_SIZE];
extern uint8_t BufList[BUF_LIST_SIZE][USART_BUFFER_SIZE];
extern uint8_t UartFlag;
extern uint8_t dma_recv_len;
#endif // CALLUART_H