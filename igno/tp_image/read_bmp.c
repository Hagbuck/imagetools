/* read_bmp.c
** TP_IMAGE
** VUILLEMIN Anthony
*/

#include "read_bmp.h"

e__bool openBMP(s__bmp *bmp, char const *path, char const *mode)
{
    bmp->file = fopen(path, mode);

    if(bmp->file)
    {
        fillBMPHeader(bmp);
        return TRUE;
    }
    else
    {
        printf("FAILURE opening : %s\n", path);
        return FALSE;
    }
}

e__bool fillBMPHeader(s__bmp *bmp)
{
    int i;
    fseek(bmp->file, 0, SEEK_SET);
    fread(&bmp->bfType[0], 1, 1, bmp->file);
    fread(&bmp->bfType[1], 1, 1, bmp->file);
    if(bmp->bfType[0] == 'B' && bmp->bfType[1] == 'M')
    {
        for(i = 3; i >= 0; --i)  // READ THE FOUR HEXA CODE FOR THE SIZE
            fread(&bmp->bfSize[i], 1, 1, bmp->file);

        for(i = 1; i >= 0; --i)
            fread(&bmp->bfReserved1[i], 1, 1, bmp->file);

        for(i = 1; i >= 0; --i)
            fread(&bmp->bfReserved2[i], 1, 1, bmp->file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->bfOffBits[i], 1, 1, bmp->file);

        /*** HEADER BITMAP ***/
        for(i = 3; i >= 0; --i)
            fread(&bmp->biSize[i], 1, 1, bmp->file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biWidth[i], 1, 1, bmp->file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biHeight[i], 1, 1, bmp->file);

        for(i = 1; i >= 0; --i)
            fread(&bmp->biPlane[i], 1, 1, bmp->file);

        for(i = 1; i >= 0; --i)
            fread(&bmp->biBitCount[i], 1, 1, bmp->file);

         for(i = 3; i >= 0; --i)
            fread(&bmp->biCompression[i], 1, 1, bmp->file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biSizeImage[i], 1, 1, bmp->file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biXpelsPerMeter[i], 1, 1, bmp->file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biYpelsPerMeter[i], 1, 1, bmp->file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biClrUsed[i], 1, 1, bmp->file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biClrImportant[i], 1, 1, bmp->file);

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void copyHeaderBMP(s__bmp *cop, s__bmp const *bmp)
{
    int i = 0;
    unsigned char header[54];
    fseek(bmp->file, 0, SEEK_SET);
    fseek(cop->file, 0, SEEK_SET);
    fread(header, 1, 54, bmp->file);
    fwrite(header, 1, 54, cop->file);
    fillBMPHeader(cop);
}

void showHeader(s__bmp const *bmp)
{
    printf("-----------------\n");
    printf(" HEADER FILE\n");
    printf("-----------------\n");
    printf("> TYPE : %c%c\n", bmp->bfType[0], bmp->bfType[1]);
    printf("> SIZE FILE : %.2x %.2x %.2x %.2x\n", bmp->bfSize[0], bmp->bfSize[1], bmp->bfSize[2], bmp->bfSize[3]);
    printf("> Reserved 1 : %.2x %.2x \n", bmp->bfReserved1[0], bmp->bfReserved1[1]);
    printf("> Reserved 2 : %.2x %.2x \n", bmp->bfReserved2[0], bmp->bfReserved2[1]);
    printf("> OFFSET : %.2x %.2x %.2x %.2x\n", bmp->bfOffBits[0], bmp->bfOffBits[1], bmp->bfOffBits[2], bmp->bfOffBits[3]);
    printf("-----------------\n");
    printf(" HEADER BITMAP\n");
    printf("> BITMAP SIZE : %.2x %.2x %.2x %.2x\n", bmp->biSize[0], bmp->biSize[1], bmp->biSize[2], bmp->biSize[3]);
    printf("> BITMAP WIDTH : %.2x %.2x %.2x %.2x\n", bmp->biWidth[0], bmp->biWidth[1], bmp->biWidth[2], bmp->biWidth[3]);
    printf("> BITMAP HEIGHT : %.2x %.2x %.2x %.2x\n", bmp->biHeight[0], bmp->biHeight[1], bmp->biHeight[2], bmp->biHeight[3]);
    printf("> BITMAP PLANE : %.2x %.2x\n", bmp->biPlane[0], bmp->biPlane[1]);
    printf("> BITMAP BitCount : %.2x %.2x\n", bmp->biBitCount[0], bmp->biBitCount[1]);
    printf("> BITMAP Compression : %.2x %.2x %.2x %.2x\n", bmp->biCompression[0], bmp->biCompression[1], bmp->biCompression[2], bmp->biCompression[3]);
    printf("> BITMAP SIZE IMG : %.2x %.2x %.2x %.2x\n", bmp->biSizeImage[0], bmp->biSizeImage[1], bmp->biSizeImage[2], bmp->biSizeImage[3]);
    printf("> BITMAP Xpels : %.2x %.2x %.2x %.2x\n", bmp->biXpelsPerMeter[0], bmp->biXpelsPerMeter[1], bmp->biXpelsPerMeter[2], bmp->biXpelsPerMeter[3]);
    printf("> BITMAP Ypels : %.2x %.2x %.2x %.2x\n", bmp->biYpelsPerMeter[0], bmp->biYpelsPerMeter[1], bmp->biYpelsPerMeter[2], bmp->biYpelsPerMeter[3]);
    printf("> BITMAP ClrUsed : %.2x %.2x %.2x %.2x\n", bmp->biClrUsed[0], bmp->biClrUsed[1], bmp->biClrUsed[2], bmp->biClrUsed[3]);
    printf("> BITMAP ClrImportant : %.2x %.2x %.2x %.2x\n", bmp->biClrImportant[0], bmp->biClrImportant[1], bmp->biClrImportant[2], bmp->biClrImportant[3]);
    printf("-----------------\n");
}

void copyContainGray(s__bmp *cop, s__bmp const *bmp)
{
    unsigned char pixel[3];
    unsigned color;
    fseek(cop->file, 54, SEEK_SET);
    fseek(bmp->file, 54, SEEK_SET);
    while(!feof(bmp->file))
    {
        fread(pixel, 3, 1, bmp->file);

        color = pixel[0] + pixel[1] + pixel[2];
        color /= 3;
        pixel[0] = color;
        pixel[1] = color;
        pixel[2] = color;

        fwrite(pixel, 3, 1, cop->file);
    }
}

void copyContainBlackAndWhite(s__bmp *cop, s__bmp const *bmp)
{
    unsigned char pixel[3];
    unsigned color;
    fseek(cop->file, 54, SEEK_SET);
    fseek(bmp->file, 54, SEEK_SET);
    while(!feof(bmp->file))
    {
        fread(pixel, 3, 1, bmp->file);

        color = pixel[0] + pixel[1] + pixel[2];
        color /= 3;
        if(color >= 256/2)
        {
            pixel[0] = 255;
            pixel[1] = 255;
            pixel[2] = 255;
        }
        else
        {
            pixel[0] = 0;
            pixel[1] = 0;
            pixel[2] = 0;
        }

        fwrite(pixel, 3, 1, cop->file);
    }
}

void copyContainNegatif(s__bmp *cop, s__bmp const *bmp)
{
    unsigned char pixel[3];
    unsigned temp;
    fseek(cop->file, 54, SEEK_SET);
    fseek(bmp->file, 54, SEEK_SET);
    while(!feof(bmp->file))
    {
        fread(pixel, 3, 1, bmp->file);

        temp = pixel[0];
        pixel[0] = 255 - pixel[0];
        pixel[1] = 255 - pixel[1];
        pixel[2] = 255 - pixel[2];

        fwrite(pixel, 3, 1, cop->file);
    }
}

void fusionTwoBMP(s__bmp *cop, s__bmp const *bmp, s__bmp const *bmp2)
{
    unsigned char pixel_1[3];
    unsigned char pixel_2[3];
    unsigned int count = 0;
    unsigned temp;
    fseek(cop->file, 54, SEEK_SET);
    fseek(bmp->file, 54, SEEK_SET);
    fseek(bmp->file, 54, SEEK_SET);
    while(!feof(bmp->file))
    {
        fread(pixel_1, 3, 1, bmp->file);
        fread(pixel_2, 3, 1, bmp2->file);

//        if(rand() % 2)
        if(count % 2 == 0)
            fwrite(pixel_1, 3, 1, cop->file);
        else
            fwrite(pixel_2, 3, 1, cop->file);
        ++count;
    }
}
