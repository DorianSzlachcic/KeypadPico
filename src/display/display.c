#include "display.h"

#include <stdlib.h>

#include "GUI_Paint.h"
#include "EPD_2in9_V2.h"
#include "img_data.h"

int display_icons()
{
    if(DEV_Module_Init()!=0){
        return -1;
    }
    EPD_2IN9_V2_Init();
    EPD_2IN9_V2_Clear();

    UBYTE* Image;
    UWORD Imagesize = ((EPD_2IN9_V2_WIDTH % 8 == 0)? (EPD_2IN9_V2_WIDTH / 8 ): (EPD_2IN9_V2_WIDTH / 8 + 1)) * EPD_2IN9_V2_HEIGHT;
    if((Image = (UBYTE *)malloc((EPD_2IN9_V2_WIDTH * EPD_2IN9_V2_HEIGHT) / 8)) == NULL) {
        printf("Failed memory allocation...\r\n");
        return -1;
    }

    Paint_NewImage(Image, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
    Paint_Clear(WHITE);

    Paint_NewImage(Image, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
    Paint_SelectImage(Image);
    Paint_Clear(WHITE);
    Paint_DrawBitMap(img);

    EPD_2IN9_V2_Display(Image);

    return 0;
}