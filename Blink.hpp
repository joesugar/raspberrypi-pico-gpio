#include <pico/stdlib.h>
#include <stdio.h>
#include <map>
#include <string>

// For information on the Raspberry Pi Pico GPIOs, see
// https://raspberrypi.github.io/pico-sdk-doxygen/group__hardware__gpio.html
//
class Blink
{
public:
    // Constructor
    //
    Blink(uint gpio_in_pin, uint gpio_out_pin)
        : gpio_in_pin_(gpio_in_pin)
        , gpio_out_pin_(gpio_out_pin)
    {
        // Initialize the GPIO to blink the LED.
        //
        gpio_init(gpio_out_pin);
        gpio_set_dir(gpio_out_pin, GPIO_OUT);

        gpio_init(gpio_in_pin);
        gpio_set_dir(gpio_in_pin, GPIO_IN);

        uint32_t event_mask = GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE;
        gpio_set_irq_enabled_with_callback(gpio_in_pin, event_mask, ENABLE, gpio_irq_callback);
    }

    // Call this function to set and reset the gpio levels.
    //
    auto run(uint count) -> void
    {
        std::map<uint, std::string> msg_map {
            std::make_pair(GPIO_HI, "Read pin hi!\n"),
            std::make_pair(GPIO_LO, "Read pin lo!\n")
        };

        uint value = 0;
        for (uint i = 0; i < count; i++)
        {
            printf("\nRound %d of %d\n", i, count);
            
            gpio_put(gpio_out_pin_, GPIO_HI);
            printf("Set pin hi!\n");
            sleep_ms(500);

            value = gpio_get(gpio_in_pin_);
            printf(msg_map.at(value).c_str());
            sleep_ms(500);

            gpio_put(gpio_out_pin_, GPIO_LO);
            printf("Set pin lo!\n");
            sleep_ms(500);

            value = gpio_get(gpio_in_pin_);
            printf(msg_map.at(value).c_str());
            sleep_ms(500);
        }
    }

private:

    // GPIO interrupt callback
    // gpio         Which GPIO caused this interrupt
    // event_mask   Which events caused this interrupt. See gpio_irq_level for details. 
    //
    static auto gpio_irq_callback(uint gpio, uint32_t event_mask) -> void
    {
        printf("Callback on GPIO %d\n", gpio);
    }

    static const uint GPIO_HI = 1;
    static const uint GPIO_LO = 0;

    static const bool ENABLE = true;
    static const bool DISABLE = false;

    uint gpio_in_pin_;
    uint gpio_out_pin_;
};