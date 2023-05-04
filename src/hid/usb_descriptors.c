
// ****************************************************************************
// *                                                                          *
// *    Auto-created by 'genusb' - USB Descriptor Generator version 1.05      *
// *                                                                          *
// ****************************************************************************
// *                                                                          *
// *    Interfaces : HID (K,M,G,C), CDC                                       *
// *                                                                          *
// ****************************************************************************

// The MIT License (MIT)
//
// Copyright 2021-2022, "Hippy"
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.

#include "tusb.h"
#include "pico/unique_id.h"

// ****************************************************************************
// *                                                                          *
// *    VID and PID Definitions                                               *
// *                                                                          *
// ****************************************************************************

// The default TinyUSB PID is -
//
//    01-- ---- --nv ihmc
//
// But we want to allow multiple CDC channels so we use -
//
//    11-g vtbn maih wccc
//       | |||| |||| | `------  CDC     1
//       | |||| |||| `--------  WEB
//       | |||| |||`----------  HID     1
//       | |||| ||`-----------  MIDI
//       | |||| |`------------  AUDIO
//       | |||| `-------------  MSC
//       | |||`---------------  NET
//       | ||`----------------  BTH
//       | |`-----------------  TMC
//       | `------------------  VENDOR
//       `--------------------  GUD

// We also want to encode our PID as our 'bcdDevice' -
//
//    -awg tvbn -mih -ccc
//     ||| ||||  |||   `------  CDC     1
//     |`|-||||--|||----------  WEB
//     | | ||||  ||`----------  HID     1
//     | | ||||  |`-----------  MIDI
//     `-|-||||--|------------  AUDIO
//       | ||||  `------------  MSC
//       | |||`---------------  NET
//       | ||`----------------  BTH
//       | `|-----------------  TMC
//       |  `-----------------  VENDOR
//       `--------------------  GUD

#define USBD_VID                (0x2E8A)        // Raspberry Pi

#define USBD_PID                ( 0xC000              +         /* 0xC011 */ \
                                  PID_MAP(CDC,     0) + \
                                  PID_MAP(HID,     4)   )

#define PID_MAP(itf, n)         ( (CFG_TUD_##itf) << (n) )

#define USBD_DEV                ( 0x8000              +         /* 0x8011 */ \
                                  DEV_MAP(CDC,     0) + \
                                  DEV_MAP(HID,     4)   )

#define DEV_MAP(itf, n)         ( (CFG_TUD_##itf) << (n) )


// ****************************************************************************
// *                                                                          *
// *    USB Device Descriptor Strings                                         *
// *                                                                          *
// ****************************************************************************

enum {
    USBD_STR_LANGUAGE,          // 0
    USBD_STR_MANUFACTURER,      // 1
    USBD_STR_PRODUCT,           // 2
    USBD_STR_SERIAL_NUMBER,     // 3
    USBD_STR_CDC_NAME,          // 4
    USBD_STR_HID_NAME,          // 5
};

char *const usbd_desc_str[] = {
    [USBD_STR_MANUFACTURER]     = "Raspberry Pi",
    [USBD_STR_PRODUCT]          = "GenUsb-HC",
    [USBD_STR_SERIAL_NUMBER]    = NULL,
    [USBD_STR_CDC_NAME]         = "CDC",
    [USBD_STR_HID_NAME]         = "HID_KMGC",
};

// ****************************************************************************
// *                                                                          *
// *    Device Descriptor                                                     *
// *                                                                          *
// ****************************************************************************

static const tusb_desc_device_t usbd_desc_device = {
    .bLength                    = sizeof(tusb_desc_device_t),
    .bDescriptorType            = TUSB_DESC_DEVICE,
    .bcdUSB                     = 0x0200,
    .bDeviceClass               = TUSB_CLASS_MISC,
    .bDeviceSubClass            = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol            = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0            = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor                   = USBD_VID,
    .idProduct                  = USBD_PID,
    .bcdDevice                  = USBD_DEV,
    .iManufacturer              = USBD_STR_MANUFACTURER,
    .iProduct                   = USBD_STR_PRODUCT,
    .iSerialNumber              = USBD_STR_SERIAL_NUMBER,
    .bNumConfigurations         = 1,
};

// ****************************************************************************
// *                                                                          *
// *    Endpoint Definitions                                                  *
// *                                                                          *
// ****************************************************************************

// .--------------------------------------------------------------------------.
// |    Virtual Serial Port                                                   |
// `--------------------------------------------------------------------------'

#define EPNUM_CDC_CMD           (0x81)
#define EPNUM_CDC_DATA          (0x82)

#define USBD_CDC_CMD_SIZE       (64)
#define USBD_CDC_DATA_SIZE      (64)

// .--------------------------------------------------------------------------.
// |    HID Device                                                            |
// `--------------------------------------------------------------------------'

#define EPNUM_HID               (0x83)

#define USBD_HID_BUFSIZE        (16)
#define USBD_HID_POLL_INTERVAL  (10)

#define REPORT_ID_KEYBOARD      (1)
#define REPORT_ID_MOUSE         (2)
#define REPORT_ID_MOUSE_ABS     (3)
#define REPORT_ID_GAMEPAD       (4)
#define REPORT_ID_CONSUMER      (5)

static const uint8_t desc_hid_report[] =
{
    TUD_HID_REPORT_DESC_KEYBOARD  (HID_REPORT_ID(REPORT_ID_KEYBOARD)),
    TUD_HID_REPORT_DESC_MOUSE     (HID_REPORT_ID(REPORT_ID_MOUSE)),
    TUD_HID_REPORT_DESC_GAMEPAD   (HID_REPORT_ID(REPORT_ID_GAMEPAD)),
    TUD_HID_REPORT_DESC_CONSUMER  (HID_REPORT_ID(REPORT_ID_CONSUMER))
};

// ****************************************************************************
// *                                                                          *
// *    Device Configuration                                                  *
// *                                                                          *
// ****************************************************************************

#define USBD_MAX_POWER_MA       (250)

#define USBD_DESC_LEN           ( (TUD_CONFIG_DESC_LEN                    ) + \
                                  (TUD_CDC_DESC_LEN       * CFG_TUD_CDC   ) + \
                                  (TUD_HID_DESC_LEN       * CFG_TUD_HID   )   )

enum {
    ITF_NUM_CDC,    ITF_NUM_CDC_DATA,
    ITF_NUM_HID,
    ITF_NUM_TOTAL
};

static const uint8_t usbd_desc_cfg[USBD_DESC_LEN] = {

    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL,
                          USBD_STR_LANGUAGE,
                          USBD_DESC_LEN,
                          TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP,
                          USBD_MAX_POWER_MA),

    TUD_CDC_DESCRIPTOR(ITF_NUM_CDC,
                      USBD_STR_CDC_NAME,
                         EPNUM_CDC_CMD, USBD_CDC_CMD_SIZE,
                         0x02,
                         EPNUM_CDC_DATA, USBD_CDC_DATA_SIZE),

    TUD_HID_DESCRIPTOR(ITF_NUM_HID,
                      USBD_STR_HID_NAME, HID_ITF_PROTOCOL_NONE, sizeof(desc_hid_report),
                         EPNUM_HID, USBD_HID_BUFSIZE, USBD_HID_POLL_INTERVAL),

};

// ****************************************************************************
// *                                                                          *
// *    USB Device Callbacks                                                  *
// *                                                                          *
// ****************************************************************************

const uint8_t *tud_descriptor_device_cb(void) {
    return (const uint8_t *)&usbd_desc_device;
}

const uint8_t *tud_descriptor_configuration_cb(uint8_t index) {
    (void)index;
    return usbd_desc_cfg;
}

char const* string_desc_arr [] =
{
  (const char[]) { 0x09, 0x04 }, // 0: is supported language is English (0x0409)
  "TinyUSB",                     // 1: Manufacturer
  "TinyUSB Device",              // 2: Product
  "123456789012",                // 3: Serials, should use chip ID
  "TinyUSB CDC",                 // 4: CDC Interface
  "TinyUSB MSC",                 // 5: MSC Interface
};

static uint16_t _desc_str[32];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long enough for transfer to complete
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
  (void) langid;

  uint8_t chr_count;

  if ( index == 0)
  {
    memcpy(&_desc_str[1], string_desc_arr[0], 2);
    chr_count = 1;
  }else
  {
    // Note: the 0xEE index string is a Microsoft OS 1.0 Descriptors.
    // https://docs.microsoft.com/en-us/windows-hardware/drivers/usbcon/microsoft-defined-usb-descriptors

    if ( !(index < sizeof(string_desc_arr)/sizeof(string_desc_arr[0])) ) return NULL;

    const char* str = string_desc_arr[index];

    // Cap at max char
    chr_count = (uint8_t) strlen(str);
    if ( chr_count > 31 ) chr_count = 31;

    // Convert ASCII string into UTF-16
    for(uint8_t i=0; i<chr_count; i++)
    {
      _desc_str[1+i] = str[i];
    }
  }

  // first byte is length (including header), second byte is string type
  _desc_str[0] = (uint16_t) ((TUSB_DESC_STRING << 8 ) | (2*chr_count + 2));

  return _desc_str;
}

const uint8_t *tud_hid_descriptor_report_cb(uint8_t instance) {
    return desc_hid_report;
}

