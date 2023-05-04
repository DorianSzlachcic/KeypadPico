#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"

#include "lfs.h"

#include "bsp/board.h"
#include "tusb.h"

#include "usb_descriptors.h"

#include "display.h"
#include "button.h"
#include "filesystem.h"

void blink(int t)
{
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    for(int i = 0; i<t;i++) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
}

void core1_entry()
{
    lfs_t lfs;
    lfs_file_t file;

    // mount the filesystem
    int err = lfs_mount(&lfs, &PICO_FLASH_CFG);

    // reformat if we can't mount the filesystem
    // this should only happen on the first boot
    if (err) {
        lfs_format(&lfs, &PICO_FLASH_CFG);
        lfs_mount(&lfs, &PICO_FLASH_CFG);
    }

    // read current count
    if(lfs_file_open(&lfs, &file, "config.json", LFS_O_RDWR | LFS_O_CREAT) >= 0)
    {
        while(true)
        {
            tud_task();
            if(tud_cdc_connected())
            {
                if(tud_cdc_available())
                {
                    char i[64];
                    tud_cdc_read(i, 64);
                    tud_cdc_read_flush();
                    lfs_file_write(&lfs, &file, i, 64);

                    tud_cdc_write_str("Ack\n");
                    tud_cdc_write_flush();
                    gpio_put(PICO_DEFAULT_LED_PIN, 0);
                    sleep_ms(100);
                    gpio_put(PICO_DEFAULT_LED_PIN, 1);
                }
            }
                
        }
    }
}

int main(void)
{
    // Turned off while working without screen 
    // if(display_icons() != 0)
    //     return -1;

    board_init();
    tusb_init();

    stdio_init_all();

    //core1_entry();

    buttons_init();

    while(true)
    {
        tud_task();
        unsigned char buttons_state = read_buttons();
        buttons_task(buttons_state);        
    }
    
    return 0;
}