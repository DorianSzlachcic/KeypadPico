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
    tusb_init();

    while(true)
    {
        tud_task();
        unsigned char buttons_state = read_buttons();
        buttons_task(buttons_state);
        printf("hello");
    }
    // lfs_t lfs;
    // lfs_file_t file;

    // // mount the filesystem
    // int err = lfs_mount(&lfs, &PICO_FLASH_CFG);

    // // reformat if we can't mount the filesystem
    // // this should only happen on the first boot
    // if (err) {
    //     lfs_format(&lfs, &PICO_FLASH_CFG);
    //     lfs_mount(&lfs, &PICO_FLASH_CFG);
    // }

    // // read current count
    // uint32_t boot_count = 0;
    // lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    // lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

    // // update boot count
    // boot_count += 1;
    // lfs_file_rewind(&lfs, &file);
    // lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

    // // remember the storage is not updated until the file is closed successfully
    // lfs_file_close(&lfs, &file);

    // // release any resources we were using
    // lfs_unmount(&lfs);

    // blink(boot_count);
    
    return 0;
}