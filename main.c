#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"

#include "bsp/board.h"
#include "tusb.h"

#include "usb_descriptors.h"

#include "display.h"
#include "button.h"

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
    stdio_init_all();

    // Turned off while working without screen 
    // if(display_icons() != 0)
    //     return -1;

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_put(LED_PIN, 1);

    buttons_init();
    board_init();
    tud_init(0);
    while(true)
    {
        tud_task();
        unsigned char buttons_state = read_buttons();
        buttons_task(buttons_state);
    }
    
    return 0;
}