#include "main.h"
#include "CallUart.h"
#include "usart.h"

extern void startUart(UART_HandleTypeDef *huart);

void Business_int(void)
{
    startUart(&USER_UART);
}