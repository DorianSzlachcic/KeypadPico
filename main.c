#include "pico/stdlib.h"

#include "display.h"

void blink()
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        break;
    }
}

int main(void)
{
    if(display_icons() != 0)
        return -1;

    return 0;
}
