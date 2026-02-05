#include "LabMecFluMAIN.h"

QueueHandle_t handleUART_to_PWM;

static const char *TAG = "[LabMecFlu]";

esp_err_t LabMecFlu_init(void)
{
    esp_err_t ret;

    handleUART_to_PWM = xQueueCreate(2,
                                     sizeof(LabMecFluUART_Command_t));

    ret = LabMecFluUART_init(&handleUART_to_PWM);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Falha ao inicializar o ADS1115: %s",
                 esp_err_to_name(ret));
        return ret;
    }

    ret = LabMecFluPWM_config(&handleUART_to_PWM);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Falha ao inicializar o PWM: %s",
                 esp_err_to_name(ret));
        return ret;
    }

    return ESP_OK;
}