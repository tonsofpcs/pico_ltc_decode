/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * Original: differential_manchester.pio
 * Source: https://github.com/raspberrypi/pico-examples
 * 
 * Modified for LTC 2021-10-21 E. Adler
 * https://github.com/tonsofpcs/pico_ltc_decode
 * 
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "differential_manchester.pio.h"

// Differential serial transmit/receive example
// Need to connect a wire from GPIO2 -> GPIO3

const uint pin_tx = 2;
const uint pin_rx = 3;

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

int main() {
    stdio_init_all();

    PIO pio = pio0;
//    uint sm_tx = 0;
    uint sm_rx = 1;

    long blarb = 0;

//    uint offset_tx = pio_add_program(pio, &differential_manchester_tx_program);
    uint offset_rx = pio_add_program(pio, &differential_manchester_rx_program);
//    printf("Transmit program loaded at %d\n", offset_tx);
    printf("Receive program loaded at %d\n", offset_rx);

    // Configure state machines, set bit rate at 5 Mbps
//    differential_manchester_tx_program_init(pio, sm_tx, offset_tx, pin_tx, 125.f / (16 * 5));
    differential_manchester_rx_program_init(pio, sm_rx, offset_rx, pin_rx, 125.f * 10000 / (16 * 24)); // 2400 bps
//    differential_manchester_rx_program_init(pio, sm_rx, offset_rx, pin_rx, 125.f * 10000 / (16 * 24 * 2)); // 4800 bps?

/*
    pio_sm_set_enabled(pio, sm_tx, false);
    pio_sm_put_blocking(pio, sm_tx, 0);
    pio_sm_put_blocking(pio, sm_tx, 0x0ff0a55a);
    pio_sm_put_blocking(pio, sm_tx, 0x12345678);
    pio_sm_set_enabled(pio, sm_tx, true);
*/
    for (int i = 0; i < 10; ++i) {
        sleep_ms(1000);
        printf("Hello...\n");
    }
    while (true) {
        for (int i = 0; i < 4; ++i) {
            blarb = pio_sm_get_blocking(pio, sm_rx);
/*            printf("%d%d %d%d %d %d %d %d %d %d %d ",
                reverse((blarb >> 8) & 0xff) & 0x03, //frame tens
                reverse(blarb & 0xff) & 0x0f, //frame ones
                reverse((blarb >> 24) & 0xff) & 0x07, //seconds tens
                reverse((blarb >> 16) & 0xff) & 0x0f, //seconds
                reverse((blarb >> 8) & 0xff) & 0x0c, //frame flags
                reverse((blarb >> 24) & 0xff) & 0x08, //seconds flag
                reverse(blarb & 0xff) & 0xf0, // user bits
                reverse((blarb >> 8) & 0xff) & 0xf0, // user bits
                reverse((blarb >> 16) & 0xff) & 0xf0, //user bits
                reverse((blarb >> 24) & 0xff) & 0xf0, //user bits
                0
            ); */
            printf("%08x\n", blarb);  // i < 10
        }
        printf(" \n");
    }
    return 0;

}
