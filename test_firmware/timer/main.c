#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "boards.h"
#include "app_util_platform.h"
#include "nrf_drv_uart.h"
#include "nrf_drv_timer.h"
#include "nrf_assert.h"

static uint8_t const STR_HELLO[] = "NRF51 Timer Tests\n";
static nrf_drv_uart_t uart_driver = NRF_DRV_UART_INSTANCE(0);
static nrf_drv_timer_t TIMER0 = NRF_DRV_TIMER_INSTANCE(0);

void test1_handler(nrf_timer_event_t event_type, void* p_context)
{
    static uint32_t i = 0;
    char buffer[20];
    if(event_type == NRF_TIMER_EVENT_COMPARE0) {
        snprintf(buffer, 20, "Tick: %ld\n", i++ * 1);
        nrf_drv_uart_tx(&uart_driver, (uint8_t *)buffer, strlen(buffer));
    }
}
//
//static void test1_cc0_250ms(void) {
//
//    //    nrf_drv_timer_config_t conf_timer0 = NRF_DRV_TIMER_DEFAULT_CONFIG;
//    nrf_drv_timer_config_t conf_timer0;
//    conf_timer0.frequency = NRF_TIMER_FREQ_31250Hz;
//    conf_timer0.mode = NRF_TIMER_MODE_TIMER;
//    conf_timer0.bit_width = NRF_TIMER_BIT_WIDTH_16;
//    conf_timer0.interrupt_priority = APP_IRQ_PRIORITY_LOW;
//    conf_timer0.p_context = NULL;
//
//    uint32_t err_code = nrf_drv_timer_init(&TIMER0, &conf_timer0, test1_handler);
//    APP_ERROR_CHECK(err_code);
//
//    uint32_t time_ms = 250;
//    uint32_t time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER0, time_ms);
//
//    nrf_drv_timer_extended_compare(&TIMER0, NRF_TIMER_CC_CHANNEL0,
//                               time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);
//
//    nrf_drv_timer_enable(&TIMER0);
//}

void test2_handler(nrf_timer_event_t event_type, void* p_context)
{
//    static uint32_t i = 0;
//    char buffer[20];
//    if(event_type == NRF_TIMER_EVENT_COMPARE0) {
//        snprintf(buffer, 20, "Tick: %ld\n", i++ * 1000);
//        nrf_drv_uart_tx(&uart_driver, (uint8_t *)buffer, strlen(buffer));
//    }
}

void dummy_handler(nrf_timer_event_t event_type, void* p_context) {

}

static void test2_cc0_1ms(void) {

    //    nrf_drv_timer_config_t conf_timer0 = NRF_DRV_TIMER_DEFAULT_CONFIG;
    nrf_drv_timer_config_t conf_timer0;
    conf_timer0.frequency = NRF_TIMER_FREQ_16MHz;
    conf_timer0.mode = NRF_TIMER_MODE_TIMER;
    conf_timer0.bit_width = NRF_TIMER_BIT_WIDTH_32;
    conf_timer0.interrupt_priority = APP_IRQ_PRIORITY_LOW;
    conf_timer0.p_context = NULL;

    uint32_t err_code = nrf_drv_timer_init(&TIMER0, &conf_timer0, test1_handler);
    APP_ERROR_CHECK(err_code);

    uint32_t time_ms = 1000;
    uint32_t time_ticks = nrf_drv_timer_ms_to_ticks(&TIMER0, time_ms);

    nrf_drv_timer_extended_compare(&TIMER0, NRF_TIMER_CC_CHANNEL0,
                               time_ticks, NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK, true);

    nrf_drv_timer_enable(&TIMER0);
}

int main(void)
{
    // Init UART
    nrf_drv_uart_config_t config = NRF_DRV_UART_DEFAULT_CONFIG;

    config.pselrxd = RX_PIN_NUMBER;
    config.pseltxd = TX_PIN_NUMBER;
    config.baudrate = NRF_UART_BAUDRATE_19200;
    config.hwfc = NRF_UART_HWFC_DISABLED;
    config.parity = NRF_UART_PARITY_EXCLUDED;

    uint32_t err_code = nrf_drv_uart_init(&uart_driver, &config, NULL);
    ASSERT(err_code == NRF_SUCCESS);

    nrf_drv_uart_rx_enable(&uart_driver);
    nrf_drv_uart_tx(&uart_driver, STR_HELLO, sizeof(STR_HELLO));

    test2_cc0_1ms();

    while (true) ;
}
