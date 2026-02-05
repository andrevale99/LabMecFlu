#ifndef LABMECFLUPWM_H
#define LABMECFLUPWM_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/ledc.h"
#include "driver/gpio.h"

#include "esp_err.h"
#include "esp_log.h"

#include "LabMecFluUART.h"

#define BOMBA_GPIO GPIO_NUM_13

esp_err_t LabMecFluPWM_config(QueueHandle_t *handleQueue);

void vTaskPWM(void *pvParameters);

#endif
