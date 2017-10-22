/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "BMP.h"

BMP_image* BMP_get_image_from_file(FILE* file)
{
    if(file != NULL)
    {
        BMP_image* bmp = malloc(sizeof(BMP_image));
        if(bmp != NULL)
        {
            if(BMP_fill_header(bmp, file) == TRUE)
            {
                // TODO : Convert the width into hex value and decimal value
                printf("> width : %d\n", bmp->biWidth[2]);

                bmp->height = 1;
                bmp->width = 1;

                int i;
                bmp->pixels = malloc(bmp->height * sizeof(rgb*));
                if(bmp->pixels != NULL)
                {
                    for(i = 0; i < bmp->height; ++i)
                    {
                        bmp->pixels[i] = malloc(bmp->width * sizeof(rgb));
                        if(bmp->pixels[i] == NULL)
                        {
                            printf("ERROR bad alloc : %d\n", ERR_BAD_ALLOC);
                            exit(ERR_BAD_ALLOC);
                        }
                    }
                    return bmp;
                }
                else
                {
                    printf("ERROR bad alloc : %d\n", ERR_BAD_ALLOC);
                    exit(ERR_BAD_ALLOC);
                }
            }
            else
            {
                printf("ERROR Filling HEADER : %d\n", ERR_IMAGE_FILE_IS_INCORRECT);
                exit(ERR_IMAGE_FILE_IS_INCORRECT);
            }
        }
        else
        {
            printf("ERROR bad alloc : %d\n", ERR_BAD_ALLOC);
            exit(ERR_BAD_ALLOC);
        }
    }
    else
    {
        printf("ERROR file is NULL : %d\n", ERR_FILE_IS_NULL);
        exit(ERR_FILE_IS_NULL);
    }
}

e__bool BMP_fill_header(BMP_image* const bmp, FILE* const file)
{
    int i;
    fseek(file, 0, SEEK_SET);
    fread(&bmp->bfType[0], 1, 1, file);
    fread(&bmp->bfType[1], 1, 1, file);
    if(bmp->bfType[0] == 'B' && bmp->bfType[1] == 'M')
    {
        for(i = 3; i >= 0; --i)  // READ THE FOUR HEXA CODE FOR THE SIZE
            fread(&bmp->bfSize[i], 1, 1, file);

        for(i = 1; i >= 0; --i)
            fread(&bmp->bfReserved1[i], 1, 1, file);

        for(i = 1; i >= 0; --i)
            fread(&bmp->bfReserved2[i], 1, 1, file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->bfOffBits[i], 1, 1, file);

        /*** HEADER BITMAP ***/
        for(i = 3; i >= 0; --i)
            fread(&bmp->biSize[i], 1, 1, file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biWidth[i], 1, 1, file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biHeight[i], 1, 1, file);

        for(i = 1; i >= 0; --i)
            fread(&bmp->biPlane[i], 1, 1, file);

        for(i = 1; i >= 0; --i)
            fread(&bmp->biBitCount[i], 1, 1, file);

         for(i = 3; i >= 0; --i)
            fread(&bmp->biCompression[i], 1, 1, file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biSizeImage[i], 1, 1, file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biXpelsPerMeter[i], 1, 1, file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biYpelsPerMeter[i], 1, 1, file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biClrUsed[i], 1, 1, file);

        for(i = 3; i >= 0; --i)
            fread(&bmp->biClrImportant[i], 1, 1, file);

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void BMP_show_header(const BMP_image* const bmp)
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

void free_BMP_image(BMP_image* bmp)
{
    int i;
    for(i = 0; i < bmp->height; ++i)
        free(bmp->pixels[i]);
    free(bmp->pixels);

    free(bmp);
}