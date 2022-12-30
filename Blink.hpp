#include <pico/stdlib.h>
#include <stdio.h>
#include <map>
#include <string>

class Blink
{
public:
    // Connstructor
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
    }

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

    const uint GPIO_HI = 1;
    const uint GPIO_LO = 0;

    uint gpio_in_pin_;
    uint gpio_out_pin_;
};