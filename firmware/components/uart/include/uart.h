#ifndef UART_H
#define UART_H

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#include "driver/uart.h"

#include "esp_log.h"
#include "esp_err.h"

/**
 * @brief Estrutura para configurar e comunicar
 * pela uart.
 */
typedef struct uart
{
    uart_config_t config; /*Configuracao uart*/
    uart_port_t port; /*Port da uart (canal)*/

    int rxPin; /*Pino RX*/
    int txPin; /*Pino TX*/
    int rtsPin; /*Pino RTS*/
    int ctsPin; /*Pino CTS*/
    int dtrPin; /*Pino DTR*/
    int dsrPin; /*Pino DSR*/

    int rxBufferSize; /*Tamanho do buffer RX*/
    int txBufferSize; /*Tamanho do buffer TX*/

    QueueHandle_t handleQueue; /*Queue caso use tratamento de eventos*/
    int queueSize; /*Tamanho da queue, baseado no tipo (int, float,...)*/
}uart_t;


esp_err_t uart_init(uart_t *, int);

#endif