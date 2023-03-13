#include <stdlib.h>

#include "pico/stdlib.h"

#include "GUI_Paint.h"
#include "EPD_2in9_V2.h"

#include "hardware/flash.h"
#include "hardware/sync.h"

void readfile(unsigned char* buffer, const char* filename) {
    FILE *f;
    if (f = fopen(filename, "rb"))
    {
        buffer = (unsigned char*)malloc(64*64);
        fseek(f, 54, SEEK_SET);
        fread(buffer, 64*64*4, 1, f);
        fclose(f);
    }
    else {
        const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
    }
    }
    
    
    
}


int main(void)
{

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

    unsigned char* fileImage;
    readfile(fileImage, "/icon.bmp");

    Paint_NewImage(Image, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
    Paint_Clear(WHITE);

    Paint_DrawBitMap(fileImage);

    EPD_2IN9_V2_Display(Image);

    DEV_Delay_ms(3000);

    EPD_2IN9_V2_Clear();

    return 0;
}
