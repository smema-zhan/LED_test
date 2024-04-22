#include "main.h"
#include "string.h"
#include "CallUart.h"
#include "usart.h"

static uint8_t led_flag = 0;
static uint8_t continue_flag = 0;

void ProcessRecvCmd(uint8_t *usart_rx_buffer, uint8_t *usart_tx_buffer)
{
    if (strcmp((char *)usart_rx_buffer, "start") == 0)
    {
        if (led_flag == 1)
            strcpy((char *)usart_tx_buffer, "LED has been started");
        else
            strcpy((char *)usart_tx_buffer, "LED start");
        led_flag = 1;
    }
    else if (strcmp((char *)usart_rx_buffer, "stop") == 0)
    {
        if (led_flag == 0)
            strcpy((char *)usart_tx_buffer, "LED has been stopped");
        else
            strcpy((char *)usart_tx_buffer, "LED stop");
        led_flag = 0;
    }
    else
        strcpy((char *)usart_tx_buffer, "Unknow command");
}

void LED_control(void)
{

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
