#include "button.h"

#include "pico/stdlib.h"
#include "tusb.h"
#include "hid.h"
#include "usb_descriptors.h"
#include "default_config.h"

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
    struct config configuration = get_default_config();

    if((1 << 0) & buttons_state){
        send_button_report(configuration.button1);
    }
    if((1 << 1) & buttons_state){
        send_button_report(configuration.button2);
    }
    if((1 << 2) & buttons_state){
        send_button_report(configuration.button3);
    }
    if((1 << 3) & buttons_state){
        send_button_report(configuration.button4);
    }
    if((1 << 4) & buttons_state){
        send_button_report(configuration.button5);
    }
    if((1 << 5) & buttons_state){
        send_button_report(configuration.button6);
    }
    if((1 << 6) & buttons_state){
        send_button_report(configuration.button7);
    }
    if((1 << 7) & buttons_state){
        send_button_report(configuration.button8);
    }
}


void send_button_report(struct button btn)
{
    if(btn.type == 'k')
        send_keyboard_report(btn.modifiers, btn.keycode);

    if(btn.type == 'c')
        send_consumer_report(btn.consumer_report, 2);
}