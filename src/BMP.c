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
                bmp->height = 0x0000;
                bmp->width = 0x0000;
                int i;
                
                // Reading od width and height and convert into integer
                for(i = 0; i < 4; ++i)
                {
                    bmp->width = bmp->width << 8;
                    bmp->width += bmp->biWidth[i];
                    
                    bmp->height = bmp->height << 8;
                    bmp->height += bmp->biHeight[i];  
                }

                // Allocate the space for the pixels
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

                    BMP_fill_pixels(bmp, file);

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
    fseek(file, 0, SEEK_SET);           // Go the beginning of the file
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

e__bool BMP_header_to_str(BMP_image* const bmp, unsigned char* str)
{
    if(bmp != NULL && str != NULL)
    {
        str[0] = bmp->bfType[0];
        str[1] = bmp->bfType[1];

        int i, j = 2;

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->bfSize[i];

        for(i = 1; i >= 0; --i, ++j)
            str[j] = bmp->bfReserved1[i];

        for(i = 1; i >= 0; --i, ++j)
            str[j] = bmp->bfReserved2[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->bfOffBits[i];

        /*** str BITMAP ***/
        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->biSize[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->biWidth[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->biHeight[i];

        for(i = 1; i >= 0; --i, ++j)
            str[j] = bmp->biPlane[i];

        for(i = 1; i >= 0; --i, ++j)
            str[j] = bmp->biBitCount[i];

         for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->biCompression[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->biSizeImage[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->biXpelsPerMeter[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->biYpelsPerMeter[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->biClrUsed[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->biClrImportant[i];

        return TRUE;
    }
    return FALSE;
}

e__bool BMP_fill_pixels(BMP_image* const bmp, FILE* const file)
{
    unsigned char pixel[3];     // An array which will contain the pixels value (rgb)
    int i = 0;
    int j = 0;
    int pixels_count = 0;

    if(fseek(file, 54, SEEK_SET) == 0)  // set the cursor at the begining of pixels value
    {
        while(!feof(file))
        {
            fread(pixel, 1, 3, file);

            j = pixels_count % bmp->width;
            i = pixels_count / bmp->width;

            // if(pixels_count == 0 || pixels_count == 1 || pixels_count == 2)
                // printf("> %d : (%d,%d) : [%2x,%2x,%2x]\n", pixels_count+1, i, j, pixel[0], pixel[1], pixel[2]);

            if(i < bmp->height && j < bmp->width)
            {
                bmp->pixels[i][j].b = pixel[0];
                bmp->pixels[i][j].g = pixel[1];
                bmp->pixels[i][j].r = pixel[2];
            }

            ++pixels_count;
        }
        return TRUE;
    }
    return FALSE;
}

e__bool BMP_save_image_into_file(BMP_image* const bmp, FILE* const file)
{
    if(bmp != NULL)
    {
        if(file != NULL)
        {
            fseek(file, 0, SEEK_SET);
            unsigned char header[54];
            unsigned char rgb[3];

            BMP_header_to_str(bmp, header);
            
            fwrite(header, 1, 54, file);
            fseek(file, 54, SEEK_SET);

            int i, j;
            for(i = 0; i < bmp->height; ++i)
            {
                for(j = 0; j < bmp->width; ++j)
                {
                    rgb[0] = bmp->pixels[i][j].b;
                    rgb[1] = bmp->pixels[i][j].g;
                    rgb[2] = bmp->pixels[i][j].r;
                    fwrite(rgb, 1, 3, file);
                }
            }
            return TRUE;
        }
        else
        {
            printf("ERROR file is NULL : %d\n", ERR_FILE_IS_NULL);
            exit(ERR_FILE_IS_NULL);
            return FALSE;
        }
    }
    printf("ERROR bmp is NULL : %d\n", ERR_STRUCT_IS_NULL);
    exit(ERR_STRUCT_IS_NULL);
    return FALSE;
}

e__bool BMP_copy_header(BMP_image* const src, BMP_image* const dest)
{
    if(src != NULL && dest != NULL)
    {
        int i;

        /*** HEADER FILE ***/
        for(i = 0; i < 2; ++i)
            dest->bfType[i] = src->bfType[i];

        for(i = 0; i < 4; ++i)
            dest->bfSize[i] = src->bfSize[i];

        for(i = 0; i < 2; ++i)
            dest->bfReserved1[i] = src->bfReserved1[i];

        for(i = 0; i < 2; ++i)
            dest->bfReserved2[i] = src->bfReserved2[i];

        for(i = 0; i < 4; ++i)
            dest->bfOffBits[i] = src->bfOffBits[i];

        /*** HEADER BITMAP ***/
        for(i = 0; i < 4; ++i)
            dest->biSize[i] = src->biSize[i];

        for(i = 0; i < 4; ++i)
            dest->biWidth[i] = src->biWidth[i];

        for(i = 0; i < 4; ++i)
            dest->biHeight[i] = src->biHeight[i];

        for(i = 0; i < 2; ++i)
            dest->biPlane[i] = src->biPlane[i];

        for(i = 0; i < 2; ++i)
            dest->biBitCount[i] = src->biBitCount[i];

        for(i = 0; i < 4; ++i)
            dest->biCompression[i] = src->biCompression[i];

        for(i = 0; i < 4; ++i)
            dest->biSizeImage[i] = src->biSizeImage[i];

        for(i = 0; i < 4; ++i)
            dest->biXpelsPerMeter[i] = src->biXpelsPerMeter[i];

        for(i = 0; i < 4; ++i)
            dest->biYpelsPerMeter[i] = src->biYpelsPerMeter[i];

        for(i = 0; i < 4; ++i)
            dest->biClrUsed[i] = src->biClrUsed[i];

        for(i = 0; i < 4; ++i)
            dest->biClrImportant[i] = src->biClrImportant[i];

        return TRUE;
    }
    return FALSE;
}

BMP_image* BMP_get_copy(BMP_image* const bmp)
{
    BMP_image* copy = malloc(sizeof(BMP_image));
    if(copy != NULL)
    {
        int i, j;

        BMP_copy_header(bmp, copy);

        copy->width = bmp->width;
        copy->height = bmp->height;

        // Allocate the memory for the pixels
        copy->pixels = malloc(copy->height * sizeof(rgb*));
        for(i = 0; i < copy->height; ++i)
        {
            copy->pixels[i] = malloc(copy->width * sizeof(rgb));
            if(copy->pixels[i] == NULL)
            {
                printf("ERROR bad alloc : %d\n", ERR_BAD_ALLOC);
                exit(ERR_BAD_ALLOC);
            }
        }

        // Copy pixels
        for(i = 0; i < copy->height; ++i)
        {
            for(j = 0; j < copy->width; ++j)
            {
                copy->pixels[i][j].r = bmp->pixels[i][j].r;
                copy->pixels[i][j].g = bmp->pixels[i][j].g;
                copy->pixels[i][j].b = bmp->pixels[i][j].b;
            }
        }
        return copy;
    }
    return NULL;
}

e__bool BMP_set_gray_filter(BMP_image* const bmp)
{
    if(bmp != NULL)
    {
        unsigned char color;
        int i,j;
        for(i = 0; i < bmp->height; ++i)
        {
            for(j = 0; j < bmp->width; ++j)
            {
                color = bmp->pixels[i][j].r +
                        bmp->pixels[i][j].g +
                        bmp->pixels[i][j].b ;
                color /= 3;

                bmp->pixels[i][j].r = color;
                bmp->pixels[i][j].g = color;
                bmp->pixels[i][j].b = color;
            }
        }
        return TRUE;
    }
    return FALSE;
}

e__bool BMP_set_reversed_filter(BMP_image* const bmp)
{
    if(bmp != NULL)
    {
        int i,j;
        for(i = 0; i < bmp->height; ++i)
        {
            for(j = 0; j < bmp->width; ++j)
            {
                bmp->pixels[i][j].r = 255 - bmp->pixels[i][j].r;
                bmp->pixels[i][j].g = 255 - bmp->pixels[i][j].g;
                bmp->pixels[i][j].b = 255 - bmp->pixels[i][j].b;
            }
        }
        return TRUE;
    }
    return FALSE;
}

e__bool BMP_set_horizontal_reversed(BMP_image* const bmp)
{
    if(bmp != NULL)
    {
        int i;
        int mid = bmp->height / 2;
        for(i = 0; i < mid; ++i)
        {
            // PAS BON
            rgb* line = bmp->pixels[i];
            bmp->pixels[i] = bmp->pixels[bmp->height-1 - i];
            bmp->pixels[bmp->height-1 - i] = line;
        }
        return TRUE;
    }
    return FALSE;
}

e__bool BMP_set_vertical_reversed(BMP_image* const bmp)
{
    if(bmp != NULL)
    {
        int i,j;
        int half_width = bmp->width / 2;
        for(i = 0; i < bmp->height; ++i)
        {
            for(j = 0; j < half_width; ++j)
            {
                rgb temp = bmp->pixels[i][j];
                bmp->pixels[i][j] = bmp->pixels[i][bmp->width-1 - j];
                bmp->pixels[i][bmp->width-1 - j] = temp;
            }
        }
        return TRUE;
    }
    return FALSE; 
}

void BMP_show_header(const BMP_image* const bmp)
{
    printf("-------------------------------------\n");
    printf(" HEADER FILE\n");
    printf("-------------------------------------\n");
    printf("> TYPE                  : %c%c\n", bmp->bfType[0], bmp->bfType[1]);
    printf("> SIZE FILE             : %.2x %.2x %.2x %.2x\n", bmp->bfSize[0], bmp->bfSize[1], bmp->bfSize[2], bmp->bfSize[3]);
    printf("> Reserved 1            : %.2x %.2x \n", bmp->bfReserved1[0], bmp->bfReserved1[1]);
    printf("> Reserved 2            : %.2x %.2x \n", bmp->bfReserved2[0], bmp->bfReserved2[1]);
    printf("> OFFSET                : %.2x %.2x %.2x %.2x\n", bmp->bfOffBits[0], bmp->bfOffBits[1], bmp->bfOffBits[2], bmp->bfOffBits[3]);
    printf("-------------------------------------\n");
    printf(" HEADER BITMAP\n");
    printf("> BITMAP SIZE           : %.2x %.2x %.2x %.2x\n", bmp->biSize[0], bmp->biSize[1], bmp->biSize[2], bmp->biSize[3]);
    printf("> BITMAP WIDTH          : %.2x %.2x %.2x %.2x\n", bmp->biWidth[0], bmp->biWidth[1], bmp->biWidth[2], bmp->biWidth[3]);
    printf("> BITMAP HEIGHT         : %.2x %.2x %.2x %.2x\n", bmp->biHeight[0], bmp->biHeight[1], bmp->biHeight[2], bmp->biHeight[3]);
    printf("> BITMAP PLANE          : %.2x %.2x\n", bmp->biPlane[0], bmp->biPlane[1]);
    printf("> BITMAP BitCount       : %.2x %.2x\n", bmp->biBitCount[0], bmp->biBitCount[1]);
    printf("> BITMAP Compression    : %.2x %.2x %.2x %.2x\n", bmp->biCompression[0], bmp->biCompression[1], bmp->biCompression[2], bmp->biCompression[3]);
    printf("> BITMAP SIZE IMG       : %.2x %.2x %.2x %.2x\n", bmp->biSizeImage[0], bmp->biSizeImage[1], bmp->biSizeImage[2], bmp->biSizeImage[3]);
    printf("> BITMAP Xpels          : %.2x %.2x %.2x %.2x\n", bmp->biXpelsPerMeter[0], bmp->biXpelsPerMeter[1], bmp->biXpelsPerMeter[2], bmp->biXpelsPerMeter[3]);
    printf("> BITMAP Ypels          : %.2x %.2x %.2x %.2x\n", bmp->biYpelsPerMeter[0], bmp->biYpelsPerMeter[1], bmp->biYpelsPerMeter[2], bmp->biYpelsPerMeter[3]);
    printf("> BITMAP ClrUsed        : %.2x %.2x %.2x %.2x\n", bmp->biClrUsed[0], bmp->biClrUsed[1], bmp->biClrUsed[2], bmp->biClrUsed[3]);
    printf("> BITMAP ClrImportant   : %.2x %.2x %.2x %.2x\n", bmp->biClrImportant[0], bmp->biClrImportant[1], bmp->biClrImportant[2], bmp->biClrImportant[3]);
    printf("-------------------------------------\n");
}

void free_BMP_image(BMP_image* bmp)
{
    int i;
    for(i = 0; i < bmp->height; ++i)
        free(bmp->pixels[i]);
    free(bmp->pixels);

    free(bmp);
}
