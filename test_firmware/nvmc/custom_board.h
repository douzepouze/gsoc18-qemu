/**
 * Created by Steffen Görtz <contrib@steffen-goertz.de>
 *
 **/

#ifndef PCA10001_H
#define PCA10001_H

#ifdef __cplusplus
extern "C" {
#endif

#include "nrf_gpio.h"

#define BUTTON_START   17
#define BUTTON_0       17
#define BUTTON_1       26
#define BUTTON_STOP    26
#define BUTTON_PULL    NRF_GPIO_PIN_NOPULL

#define BUTTONS_ACTIVE_STATE 0

#define BSP_BUTTON_0   BUTTON_0
#define BSP_BUTTON_1   BUTTON_1

#define BUTTONS_NUMBER 2
#define LEDS_NUMBER    0

#define BUTTONS_LIST { BUTTON_0, BUTTON_1 }

#define RX_PIN_NUMBER  25
#define TX_PIN_NUMBER  24

#ifdef __cplusplus
}
#endif

#endif
