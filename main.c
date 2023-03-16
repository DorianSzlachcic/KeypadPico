#include <stdlib.h>
#include <lfs.h>

#include "pico/stdlib.h"

#include "GUI_Paint.h"
#include "EPD_2in9_V2.h"
#include "filesystem.h"

#define BUFFER_LENGTH 256

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

uint16_t get_block(uint8_t *buffer) {
  uint16_t buffer_index= 0;
  while (true) {
    int c = getchar_timeout_us(100);
    if (c != PICO_ERROR_TIMEOUT && buffer_index < BUFFER_LENGTH) {
      buffer[buffer_index++] = (c & 0xFF);
    } else {
      break;
    }
  }
  return buffer_index;
}


int main(void)
{
    int buff_index = 0;

    unsigned char* fileImage = (unsigned char*)malloc(BUFFER_LENGTH);

    while (buff_index < 1)
    {
        buff_index = get_block(fileImage);
        printf("wait\n");
    }

    blink();


    if(DEV_Module_Init()!=0){
        return -1;
    }
    EPD_2IN9_V2_Init();
    EPD_2IN9_V2_Clear();

    UBYTE* Image;
    UWORD Imagesize = ((EPD_2IN9_V2_WIDTH % 8 == 0)? (EPD_2IN9_V2_WIDTH / 8 ): (EPD_2IN9_V2_WIDTH / 8 + 1)) * EPD_2IN9_V2_HEIGHT;
    if((Image = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed memory allocation...\r\n");
        return -1;
    }

    Paint_NewImage(Image, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
    Paint_Clear(WHITE);
    Paint_DrawBitMap(fileImage);

    EPD_2IN9_V2_Display(Image);

    DEV_Delay_ms(3000);

    EPD_2IN9_V2_Clear();

    return 0;
}
