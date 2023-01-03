#include <pico/stdlib.h>
#include <stdio.h>

#include "Blink.hpp"

int main()
{
    static const uint OUT_PIN = 25;     // LED pin
    static const uint32_t DELAY_MS = 500;

    // Initialize the serial port.
    //
    stdio_init_all();

    Blink blink(OUT_PIN, DELAY_MS);
    blink.run(100);

    printf("\nDone!\n");
    while (true);
    return 0;
}