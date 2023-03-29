#include "hid.h"

#include "bsp/board.h"
#include "tusb.h"
#include "usb_descriptors.h"

void send_keyboard_report(unsigned char modifiers, unsigned char keycode[])
{
    if ( !tud_hid_ready() ) return;

    if(tud_suspended())
        tud_remote_wakeup();
    else
    {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, modifiers, keycode);
        sleep_ms(10);

        tud_task(); //Need to be done between sending reports

        sleep_ms(5);
        unsigned char keycode2[6] = { 0 };
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode2);

        tud_task();
    }
    sleep_ms(200);
}

void send_consumer_report(int consumer_report, unsigned int len)
{
    if ( !tud_hid_ready() ) return;

    if(tud_suspended())
        tud_remote_wakeup();
    else
    {
        tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &consumer_report, len);
        sleep_ms(10);

        tud_task(); //Need to be done between sending reports

        sleep_ms(5);
        int empty_report = 0;
        tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &empty_report, len);

        tud_task();
    }
    sleep_ms(200);
}

// Functions needed by tinyusb hid

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