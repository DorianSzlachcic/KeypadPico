#include <stdlib.h>

#include "lib/GUI/GUI_Paint.h"
#include "lib/Fonts/fonts.h"
#include "lib/e-Paper/EPD_2in9_V2.h"

void Loading_Screen(UBYTE* Image)
{
    Paint_NewImage(Image, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
    Paint_Clear(WHITE);

    Paint_DrawString_EN(50, 50, "Loading", &Font12, WHITE, BLACK);

    EPD_2IN9_V2_Display(Image);

    DEV_Delay_ms(1000);

    Paint_NewImage(Image, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
    Paint_Clear(WHITE);

    Paint_DrawString_EN(50, 50, "Loading", &Font12, WHITE, BLACK);
    Paint_DrawPoint(100, 50, BLACK, DOT_PIXEL_4X4, DOT_FILL_RIGHTUP);

    EPD_2IN9_V2_Display(Image);

    DEV_Delay_ms(1000);

    Paint_NewImage(Image, EPD_2IN9_V2_WIDTH, EPD_2IN9_V2_HEIGHT, 90, WHITE);
    Paint_Clear(WHITE);
    EPD_2IN9_V2_Display(Image);

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

    EPD_2IN9_V2_Clear();

    return 0;
}
