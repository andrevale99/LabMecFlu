#ifndef TASK_ADS_111X
#define TASK_ADS_111X

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "TaskADS111x"

static TaskHandle_t handleTaskADS111x = NULL;

static void TaskADS111x(void *args)
{
    while(1)
    {

    }
}

void task_ads111x_init(void)
{

}

#endif