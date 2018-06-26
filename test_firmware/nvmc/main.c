#include <stdbool.h>
#include <stdint.h>
#include "boards.h"
#include "nrf_nvmc.c"

static void test_erase_page(void) {
    volatile uintptr_t offset = 1024 * 200;
    // Fill memory
    for(uint16_t i=0; i < 256; i++) {
        *(uint8_t *)(offset + i)  = i;
        ASSERT(i == *(uint8_t *)(offset + i));
    }
    // Erase page
    nrf_nvmc_page_erase(offset);

    // Check memory empty
    for(uint16_t i=0; i < 256; i++) {
        ASSERT(0xFF == *(uint8_t *)(offset + i));
    }
}

int main(void) {
    test_erase_page();

    /* Forever. */
    while (true) {
        ;
    }
}
