#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"

#include "bsp/board.h"
#include "tusb.h"

#include "usb_descriptors.h"

#include "display.h"

void send_report();

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
    // Turned off while working without screen 
    // if(display_icons() != 0)
    //     return -1;

    gpio_init(5);
    gpio_set_dir(5, GPIO_IN);

    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);


    board_init();

    tud_init(0);

    gpio_put(LED_PIN, 1);

    bool pressed = false;
    while(true)
    {
        tud_task();

        int x = gpio_get(5);
        if(x && !pressed)
        {
            send_report();
            pressed = true;
        }
        else if(!x && pressed)
        {
            pressed = false;
        }

    }

    return 0;
}

void send_report()
{
    if ( !tud_hid_ready() ) return;

    if(tud_suspended())
        tud_remote_wakeup();
    else
    {
        unsigned char keycode[6] = { 0 };
        keycode[0] = HID_KEY_A;
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        sleep_ms(10);

        tud_task();

        sleep_ms(5);
        unsigned char keycode2[6] = { 0 };
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode2);
    }
    sleep_ms(200);
}


// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
}