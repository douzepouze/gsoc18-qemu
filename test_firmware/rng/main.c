#include <stdbool.h>
#include <stdint.h>
#include "boards.h"
#include "nrf_assert.h"
#include "nrf_drv_rng.h"

int main(void)
{
//    nrf_drv_rng_config_t m_default_config = NRF_DRV_RNG_DEFAULT_CONFIG;
//    ret_code_t err_code = nrf_drv_rng_init(NULL);
//    ASSERT(err_code == NRF_SUCCESS);

    nrf_rng_task_trigger(NRF_RNG_TASK_START);

    while (true)
    {
        register uint8_t val = nrf_rng_random_value_get();
        val = val;
    }
}
