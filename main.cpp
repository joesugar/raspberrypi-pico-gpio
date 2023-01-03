#include <pico/stdlib.h>
#include <stdio.h>

int main()
{
    const uint LED_PIN = 25;
    const uint OUT_PIN = 14;
    const uint IN_PIN  = 15;

    const uint GPIO_HI = 1;
    const uint GPIO_LO = 0;

    // Initialize the GPIO to blink the LED.
    //
    gpio_init(OUT_PIN);
    gpio_set_dir(OUT_PIN, GPIO_OUT);

    gpio_init(IN_PIN);
    gpio_set_dir(IN_PIN, GPIO_IN);

    // Initialize the serial port.
    //
    stdio_init_all();

    // Loop to blink the LED and print the message.
    //
    uint value = GPIO_LO;
    while (true)
    {
        gpio_put(OUT_PIN, GPIO_HI);
        printf("Set pin hi!\n");
        sleep_ms(500);

        value = gpio_get(IN_PIN);
        if (value == GPIO_HI)
            printf("Read pin hi!\n");
        else
            printf("Read pin lo!\n");
        sleep_ms(500);

        gpio_put(OUT_PIN, GPIO_LO);
        printf("Set pin lo!\n");
        sleep_ms(500);

        value = gpio_get(IN_PIN);
        if (value == GPIO_HI)
            printf("Read pin hi!\n");
        else
            printf("Read pin lo!\n");
        sleep_ms(500);
    }
    return 0;
}