#include <pico/stdlib.h>
#include <stdio.h>

#include "Blink.hpp"

int main()
{
    static const uint OUT_PIN = 14;
    static const uint IN_PIN  = 15;

    // Initialize the serial port.
    //
    stdio_init_all();

    Blink blink(IN_PIN, OUT_PIN);
    blink.run(10);
    printf("\nDone!\n");

    while (true);
    return 0;
}