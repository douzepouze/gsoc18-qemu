#include <stdbool.h>
#include <stdint.h>
#include "boards.h"
#include "nrf_drv_uart.h"
#include "nrf_assert.h"

static uint8_t const str[] = "Hello NRF51\n";

int main(void)
{
    // Init UART
    nrf_drv_uart_config_t config = NRF_DRV_UART_DEFAULT_CONFIG;

    config.pselrxd = RX_PIN_NUMBER;
    config.pseltxd = TX_PIN_NUMBER;
    config.baudrate = NRF_UART_BAUDRATE_19200;
    config.hwfc = NRF_UART_HWFC_DISABLED;
    config.parity = NRF_UART_PARITY_EXCLUDED;

    nrf_drv_uart_t uart_driver = NRF_DRV_UART_INSTANCE(0);
    uint32_t err_code = nrf_drv_uart_init(&uart_driver, &config, NULL);
    ASSERT(err_code == NRF_SUCCESS);

    nrf_drv_uart_rx_enable(&uart_driver);
    nrf_drv_uart_tx(&uart_driver, str, sizeof(str));

    uint8_t buffer[10];

    /* Toggle LEDs. */
    while (true)
    {
        nrf_drv_uart_rx(&uart_driver, buffer, sizeof(buffer));
        nrf_drv_uart_tx(&uart_driver, buffer, sizeof(buffer));
    }
}
