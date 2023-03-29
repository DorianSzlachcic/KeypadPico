#include "button.h"

#include "pico/stdlib.h"
#include "tusb.h"
#include "hid.h"
#include "usb_descriptors.h"

void buttons_init()
{
    gpio_init(BUTTON_1);
    gpio_set_dir(BUTTON_1, GPIO_IN);

    gpio_init(BUTTON_2);
    gpio_set_dir(BUTTON_2, GPIO_IN);

    gpio_init(BUTTON_3);
    gpio_set_dir(BUTTON_3, GPIO_IN);

    gpio_init(BUTTON_4);
    gpio_set_dir(BUTTON_4, GPIO_IN);

    gpio_init(BUTTON_5);
    gpio_set_dir(BUTTON_5, GPIO_IN);

    gpio_init(BUTTON_6);
    gpio_set_dir(BUTTON_6, GPIO_IN);

    gpio_init(BUTTON_7);
    gpio_set_dir(BUTTON_7, GPIO_IN);

    gpio_init(BUTTON_8);
    gpio_set_dir(BUTTON_8, GPIO_IN);
}

unsigned char read_buttons()
{
    unsigned char buttons_state = 0;

    buttons_state = buttons_state | (gpio_get(BUTTON_1) << 0);
    buttons_state = buttons_state | (gpio_get(BUTTON_2) << 1);
    buttons_state = buttons_state | (gpio_get(BUTTON_3) << 2);
    buttons_state = buttons_state | (gpio_get(BUTTON_4) << 3);
    buttons_state = buttons_state | (gpio_get(BUTTON_5) << 4);
    buttons_state = buttons_state | (gpio_get(BUTTON_6) << 5);
    buttons_state = buttons_state | (gpio_get(BUTTON_7) << 6);
    buttons_state = buttons_state | (gpio_get(BUTTON_8) << 7);

    return buttons_state;
}

void buttons_task(unsigned char buttons_state)
{
    if((1 << 0) & buttons_state){
        unsigned char keycode[6] = {HID_KEY_X, 0, 0, 0, 0, 0};
        send_keyboard_report(L_CTRL, keycode);
    }
    if((1 << 1) & buttons_state){
        unsigned char keycode[6] = {HID_KEY_C, 0, 0, 0, 0, 0};
        send_keyboard_report(L_CTRL, keycode);
    }
    if((1 << 2) & buttons_state){
        unsigned char keycode[6] = {HID_KEY_V, 0, 0, 0, 0, 0};
        send_keyboard_report(L_CTRL, keycode);
    }
    if((1 << 3) & buttons_state){
        send_consumer_report(HID_USAGE_CONSUMER_SCAN_PREVIOUS, 2);
    }
    if((1 << 4) & buttons_state){
        send_consumer_report(HID_USAGE_CONSUMER_PLAY_PAUSE, 2);
    }
    if((1 << 5) & buttons_state){
        send_consumer_report(HID_USAGE_CONSUMER_SCAN_NEXT, 2);
    }
    if((1 << 6) & buttons_state){
        unsigned char keycode[6] = {HID_KEY_ESCAPE, 0, 0, 0, 0, 0};
        send_keyboard_report((L_CTRL | L_SHIFT), keycode);
    }
    if((1 << 7) & buttons_state){
        unsigned char keycode[6] = {HID_KEY_DELETE, 0, 0, 0, 0, 0};
        send_keyboard_report((L_CTRL | L_ALT), keycode);
    }
}
