/* main.c
** TP_IMAGE
** VUILLEMIN Anthony
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "read_bmp.h"

int main(void)
{
    s__bmp bmp, bmp2, cop;
    srand(time(NULL));

    if(openBMP(&bmp, "image/mario.bmp", "rb") == TRUE)
    {
        showHeader(&bmp);
        if(openBMP(&cop, "image/fusion.bmp", "wb+") == TRUE)
        {
            copyHeaderBMP(&cop, &bmp);
            showHeader(&cop);
//            copyContainGray(&cop, &bmp);
//            copyContainBlackAndWhite(&cop, &bmp);
//            copyContainNegatif(&cop, &bmp);
            if(openBMP(&bmp2, "image/simpson.bmp", "rb") == TRUE)
            {
                copyHeaderBMP(&bmp2, &bmp);
                showHeader(&bmp2);
                fusionTwoBMP(&cop, &bmp, &bmp2);
            }
        }
    }
    fclose(bmp.file);
    fclose(cop.file);
    return 0;
}
