#include <pico/stdlib.h>
#include <stdio.h>

#include "Blink.hpp"

// GPIO interrupt callback
// gpio         Which GPIO caused this interrupt
// event_mask   Which events caused this interrupt. See gpio_irq_level for details. 
//
static auto gpio_irq_callback(uint gpio, uint32_t event_mask) -> void
{
    printf("Callback on GPIO %d\n", gpio);
}


// Main method
//
int main()
{

    static const bool ENABLE = true;
    static const bool DISABLE = false;

    static const uint OUT_PIN = 14;
    static const uint IN_PIN  = 15;

    static const uint32_t DELAY_MS = 500;

    // Initialize the serial port.
    //
    stdio_init_all();

    uint32_t event_mask = GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE;
    gpio_set_irq_enabled_with_callback(IN_PIN, event_mask, ENABLE, gpio_irq_callback);

    Blink blink(IN_PIN, OUT_PIN, DELAY_MS);
    blink.run(10);

    printf("\nDone!\n");
    while (true);
    return 0;
}