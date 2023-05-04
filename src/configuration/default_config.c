#include "default_config.h"

#include <string.h>

#include "img_data.h"
#include "tusb.h"
#include "button.h"

struct config get_default_config()
{
    struct config default_config;
    strcpy(default_config.image_bitmap, img);

    struct button btn_keyboard = {'k', L_CTRL, {HID_KEY_X, 0, 0, 0, 0, 0}, -1};
    default_config.button1 = btn_keyboard;
    
    btn_keyboard.keycode[0] = HID_KEY_C;
    default_config.button2 = btn_keyboard;

    btn_keyboard.keycode[0] = HID_KEY_V;
    default_config.button3 = btn_keyboard;

    btn_keyboard.keycode[0] = HID_KEY_ESCAPE;
    btn_keyboard.modifiers = (L_CTRL | L_SHIFT);
    default_config.button4 = btn_keyboard;

    btn_keyboard.keycode[0] = HID_KEY_DELETE;
    btn_keyboard.modifiers = (L_CTRL | L_ALT);
    default_config.button8 = btn_keyboard;

    struct button btn_consumer = {'c', -1, {-1, -1, -1, -1, -1, -1}, HID_USAGE_CONSUMER_SCAN_PREVIOUS};
    default_config.button5 = btn_consumer;

    btn_consumer.consumer_report = HID_USAGE_CONSUMER_PLAY_PAUSE;
    default_config.button6 = btn_consumer;

    btn_consumer.consumer_report = HID_USAGE_CONSUMER_SCAN_NEXT;
    default_config.button7 = btn_consumer;

    return default_config;
}