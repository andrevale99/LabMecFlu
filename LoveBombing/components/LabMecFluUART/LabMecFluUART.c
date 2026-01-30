#include "LabMecFluUART.h"

static const char *TAG = "[LabMecFluUART]";

esp_err_t LabMecFluUART_init(void)
{
    esp_err_t ret;

    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    ret = uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL, 0);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Falha ao instalar o driver UART: %s",
                 esp_err_to_name(ret));
        return ret;
    }

    ret = uart_param_config(UART_NUM_0, &uart_config);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Falha ao configurar os parâmetros UART: %s",
                 esp_err_to_name(ret));
        return ret;
    }

    ret = uart_set_pin(UART_NUM_0, TX, RX, -1, -1);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Falha ao configurar os pinos UART: %s",
                 esp_err_to_name(ret));
        return ret;
    }

    ESP_LOGI(TAG, "UART inicializada com sucesso");

    xTaskCreate(vTaskUART, "vTaskUART", 2048, NULL, 10, NULL);

    return ret;
}

void vTaskUART(void *pvParameters)
{
    char cdataRecv;
    uint8_t buffer[BUF_SIZE];
    uint8_t cont = 0;
    while (1)
    {
        int len = uart_read_bytes(UART_NUM_0, &cdataRecv, 1,
                                  100 / portTICK_PERIOD_MS);
        if (len > 0)
        {
            buffer[cont++] = cdataRecv;
            uart_write_bytes(UART_NUM_0, &cdataRecv,
                             len);

            if (buffer[cont - 1] == '\r' || buffer[cont - 1] == '\n' || cont == BUF_SIZE)
            {
                uart_write_bytes(UART_NUM_0, (const char *)buffer,
                                 cont - 1);
                
                memset(buffer, 0, cont);

                cont = 0;
            }
        }
    }
}