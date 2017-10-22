/* read_bmp.h
** TP_IMAGE
** VUILLEMIN Anthony
*/

#ifndef READ_BMP_H_INCLUDED
#define READ_BMP_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum e__bool e__bool;
enum e__bool{FALSE, TRUE};

typedef struct s__bmp s__bmp;
struct s__bmp
{
    FILE *file;

    /*** HEADER FILE ***/
    unsigned char bfType[2];
    unsigned char bfSize[4];
    unsigned char bfReserved1[2];
    unsigned char bfReserved2[2];
    unsigned char bfOffBits[4];

    /*** HEADER BITMAP ***/
    unsigned char biSize[4];
    unsigned char biWidth[4];
    unsigned char biHeight[4];
    unsigned char biPlane[2];
    unsigned char biBitCount[2];
    unsigned char biCompression[4];
    unsigned char biSizeImage[4];
    unsigned char biXpelsPerMeter[4];
    unsigned char biYpelsPerMeter[4];
    unsigned char biClrUsed[4];
    unsigned char biClrImportant[4];

};

e__bool openBMP(s__bmp *bmp, char const *path, char const *mode);
e__bool fillBMPHeader(s__bmp *bmp);
void copyHeaderBMP(s__bmp *cop, s__bmp const *bmp);
void showHeader(s__bmp const *bmp);
void copyContainGray(s__bmp *cop, s__bmp const *bmp);
void copyContainBlackAndWhite(s__bmp *cop, s__bmp const *bmp);
void copyContainNegatif(s__bmp *cop, s__bmp const *bmp);
void fusionTwoBMP(s__bmp *cop, s__bmp const *bmp, s__bmp const *bmp2);

#endif // READ_BMP_H_INCLUDED
