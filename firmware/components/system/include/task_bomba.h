#ifndef TASK_BOMBA_H
#define TASK_BOMBA_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "TaskBomba";

static TaskHandle_t handleTaskBomba = NULL;

static void TaskBomba(void *args)
{
    while(1)
    {
        
    }
}

void task_bomba_init(void)
{
    
}

#endif