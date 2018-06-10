#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

#define MAT_ROWS 1
#define MAT_COLS 9

static const uint8_t m_board_mat_rows[MAT_ROWS] = {13,};
static const uint8_t m_board_mat_cols[MAT_COLS] = {4, 5, 6, 7, 8, 9, 10, 11, 12};

int main(void)
{

	for(int i = 0; i < MAT_COLS; i++) {
		nrf_gpio_cfg_output(m_board_mat_cols[i]);
		nrf_gpio_pin_write(m_board_mat_cols[i], 1);
	}

	for(int i = 0; i < MAT_ROWS; i++) {
		nrf_gpio_cfg_output(m_board_mat_rows[i]);
		nrf_gpio_pin_write(m_board_mat_rows[i], 1);
	}


    /* Toggle LEDs. */
    while (true)
    {
        for (int i = 0; i < LEDS_NUMBER; i++) {
            nrf_delay_ms(500);
            nrf_gpio_pin_toggle(m_board_mat_cols[0]);
        }
    }
}
