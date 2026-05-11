#ifndef TASK_UART_H
#define TASK_UART_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "uart.h"

static const char *TAG = "TaskUart";

static TaskHandle_t handleTaskUart = NULL;

static void TaskUart(void *args)
{
    while(1)
    {

    }
}

void task_uart_create(void)
{
    
}

#endif