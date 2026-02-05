#include "LabMecFluPWM.h"

static QueueHandle_t *handleUART_to_PWM;

static const char *TAG = "[LabMecFluPWM]";

esp_err_t LabMecFluPWM_config(QueueHandle_t *handleQueue)
{
    ledc_timer_config_t ledc_timer = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_8_BIT,
        .timer_num = 1,
        .freq_hz = 1 * 1000 * 10, // Set output frequency at 10 kHz
        .clk_cfg = LEDC_AUTO_CLK};
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = 1,
        .intr_type = LEDC_INTR_DISABLE,
        .gpio_num = BOMBA_GPIO,
        .duty = 0, // Set duty to 0%
        .hpoint = 0};
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));

    handleUART_to_PWM = handleQueue;

    xTaskCreate(vTaskPWM, "vTaskPWM", 2048, NULL, 2, NULL);

    return ESP_OK;
}

void vTaskPWM(void *pvParameters)
{
    uint32_t duty = 0;
    const uint32_t duty_max = 255; // Max duty for 8-bit resolution
    LabMecFluUART_Command_t command;
    while (1)
    {
        if (xQueueReceive(*handleUART_to_PWM, &command,
                          pdMS_TO_TICKS(100)) == pdPASS)
        {
             ESP_LOGI(TAG, "Comando recebido: %c, Valor: %d",
                         command.cmd, command.value);
        }
    }
}