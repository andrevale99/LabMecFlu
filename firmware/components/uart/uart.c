#include "uart.h"

static const char *TAG = "UART";

esp_err_t uart_init(uart_t *uart, int intr_alloc_flags)
{
    esp_err_t erro = ESP_OK;

    ESP_LOGI(TAG, "Inicializando uart...");

    if (!uart)
    {
        ESP_LOGE(TAG, "uart_port_t NULL");
        return ESP_ERR_NOT_FOUND;
    }

    erro = uart_driver_install(uart->port, uart->rxBufferSize, uart->txBufferSize,
                               uart->queueSize, &uart->handleQueue,
                               intr_alloc_flags);

    if (erro != ESP_OK)
    {
        ESP_LOGE(TAG, "uart_driver_intall erro: %s", esp_err_to_name(erro));
        return erro;
    }

    erro = uart_param_config(uart->port, &uart->config);
    if (erro != ESP_OK)
    {
        ESP_LOGE(TAG, "uart_param_config erro: %s", esp_err_to_name(erro));
        return erro;
}

    erro = uart_set_pin(uart->port, uart->txPin, uart->rxPin, uart->rtsPin, uart->ctsPin);

    if (erro != ESP_OK)
    {
        ESP_LOGE(TAG, "uart-set_pin erro: %s", esp_err_to_name(erro));
        return erro;
    }

    ESP_LOGI(TAG, "uart Finalizada");

    return ESP_OK;
}