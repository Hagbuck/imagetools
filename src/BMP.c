/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "BMP.h"

/**
 * @brief      Get a BMP_image from a BMP file
 *             And fill the struct bmp_P2_image
 *
 * @param      file  The file
 *
 * @return     The BMP_image
 */
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
                    bmp->width += bmp->header.biWidth[i];
                    
                    bmp->height = bmp->height << 8;
                    bmp->height += bmp->header.biHeight[i];  
                }

                // Allocate the space for the pixels
                bmp->pixels = malloc(bmp->height * sizeof(RGB*));
                if(bmp->pixels != NULL)
                {
                    for(i = 0; i < bmp->height; ++i)
                    {
                        bmp->pixels[i] = malloc(bmp->width * sizeof(RGB));
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

/**
 * @brief      Fill the header var from the file informations
 *
 * @param      bmp   The bitmap
 * @param      file  The file
 *
 * @return     TRUE if success, otherwise FALSE
 */
e__bool BMP_fill_header(BMP_image* const bmp, FILE* const file)
{
    if(file != NULL && bmp != NULL)
    {
        int i;
        fseek(file, 0, SEEK_SET);           // Go the beginning of the file
        fread(&bmp->header.bfType[0], 1, 1, file);
        fread(&bmp->header.bfType[1], 1, 1, file);
        if(bmp->header.bfType[0] == 'B' && bmp->header.bfType[1] == 'M')
        {
            for(i = 3; i >= 0; --i)  // READ THE FOUR HEXA CODE FOR THE SIZE
                fread(&bmp->header.bfSize[i], 1, 1, file);

            for(i = 1; i >= 0; --i)
                fread(&bmp->header.bfReserved1[i], 1, 1, file);

            for(i = 1; i >= 0; --i)
                fread(&bmp->header.bfReserved2[i], 1, 1, file);

            for(i = 3; i >= 0; --i)
                fread(&bmp->header.bfOffBits[i], 1, 1, file);

            /*** HEADER BITMAP ***/
            for(i = 3; i >= 0; --i)
                fread(&bmp->header.biSize[i], 1, 1, file);

            for(i = 3; i >= 0; --i)
                fread(&bmp->header.biWidth[i], 1, 1, file);

            for(i = 3; i >= 0; --i)
                fread(&bmp->header.biHeight[i], 1, 1, file);

            for(i = 1; i >= 0; --i)
                fread(&bmp->header.biPlane[i], 1, 1, file);

            for(i = 1; i >= 0; --i)
                fread(&bmp->header.biBitCount[i], 1, 1, file);

             for(i = 3; i >= 0; --i)
                fread(&bmp->header.biCompression[i], 1, 1, file);

            for(i = 3; i >= 0; --i)
                fread(&bmp->header.biSizeImage[i], 1, 1, file);

            for(i = 3; i >= 0; --i)
                fread(&bmp->header.biXpelsPerMeter[i], 1, 1, file);

            for(i = 3; i >= 0; --i)
                fread(&bmp->header.biYpelsPerMeter[i], 1, 1, file);

            for(i = 3; i >= 0; --i)
                fread(&bmp->header.biClrUsed[i], 1, 1, file);

            for(i = 3; i >= 0; --i)
                fread(&bmp->header.biClrImportant[i], 1, 1, file);

            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    return FALSE;
}

/**
 * @brief      Convert header value into a string
 *             Usefull for writing the BMP_image into a file
 *
 * @param      bmp   The bitmap
 * @param      str   The string
 *
 * @return     TRUE if sucess, otherwise FALSE
 */
e__bool BMP_header_to_str(BMP_image* const bmp, unsigned char* str)
{
    if(bmp != NULL && str != NULL)
    {
        str[0] = bmp->header.bfType[0];
        str[1] = bmp->header.bfType[1];

        int i, j = 2;

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.bfSize[i];

        for(i = 1; i >= 0; --i, ++j)
            str[j] = bmp->header.bfReserved1[i];

        for(i = 1; i >= 0; --i, ++j)
            str[j] = bmp->header.bfReserved2[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.bfOffBits[i];

        /*** str BITMAP ***/
        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.biSize[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.biWidth[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.biHeight[i];

        for(i = 1; i >= 0; --i, ++j)
            str[j] = bmp->header.biPlane[i];

        for(i = 1; i >= 0; --i, ++j)
            str[j] = bmp->header.biBitCount[i];

         for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.biCompression[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.biSizeImage[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.biXpelsPerMeter[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.biYpelsPerMeter[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.biClrUsed[i];

        for(i = 3; i >= 0; --i, ++j)
            str[j] = bmp->header.biClrImportant[i];

        return TRUE;
    }
    return FALSE;
}

/**
 * @brief      Fill BMP_image pixel array from pixel value into the file
 *
 * @param      bmp   The bitmap
 * @param      file  The file
 *
 * @return     TRUE if success, otherwise FALSE
 */
e__bool BMP_fill_pixels(BMP_image* const bmp, FILE* const file)
{
    unsigned char pixel[3];     // An array which will contain the pixels value (RGB)
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

/**
 * @brief      Save the BMP_image into a file
 *
 * @param      bmp   The bitmap
 * @param      file  The file
 *
 * @return     TRUE if success, otherwise FALSE
 */
e__bool BMP_save_image_into_file(BMP_image* const bmp, FILE* const file)
{
    if(bmp != NULL)
    {
        if(file != NULL)
        {
            fseek(file, 0, SEEK_SET);
            unsigned char header[54];
            unsigned char RGB[3];

            BMP_header_to_str(bmp, header);
            
            fwrite(header, 1, 54, file);
            fseek(file, 54, SEEK_SET);

            int i, j;
            for(i = 0; i < bmp->height; ++i)
            {
                for(j = 0; j < bmp->width; ++j)
                {
                    RGB[0] = bmp->pixels[i][j].b;
                    RGB[1] = bmp->pixels[i][j].g;
                    RGB[2] = bmp->pixels[i][j].r;
                    fwrite(RGB, 1, 3, file);
                }
            }
        }
        else
        {
            printf("ERROR file is NULL : %d\n", ERR_FILE_IS_NULL);
            exit(ERR_FILE_IS_NULL);
            return FALSE;
        }
    }
    else
    {
        printf("ERROR bmp is NULL : %d\n", ERR_STRUCT_IS_NULL);
        exit(ERR_STRUCT_IS_NULL);
        return FALSE;
    }
    return TRUE;
}

/**
 * @brief      Copy header value from src to dest
 *
 * @param      src   The source
 * @param      dest  The destination
 *
 * @return     TRUE if success, otherwise FALSE
 */
e__bool BMP_copy_header(BMP_image* const src, BMP_image* const dest)
{
    if(src != NULL && dest != NULL)
    {
        int i;

        /*** HEADER FILE ***/
        for(i = 0; i < 2; ++i)
            dest->header.bfType[i] = src->header.bfType[i];

        for(i = 0; i < 4; ++i)
            dest->header.bfSize[i] = src->header.bfSize[i];

        for(i = 0; i < 2; ++i)
            dest->header.bfReserved1[i] = src->header.bfReserved1[i];

        for(i = 0; i < 2; ++i)
            dest->header.bfReserved2[i] = src->header.bfReserved2[i];

        for(i = 0; i < 4; ++i)
            dest->header.bfOffBits[i] = src->header.bfOffBits[i];

        /*** HEADER BITMAP ***/
        for(i = 0; i < 4; ++i)
            dest->header.biSize[i] = src->header.biSize[i];

        for(i = 0; i < 4; ++i)
            dest->header.biWidth[i] = src->header.biWidth[i];

        for(i = 0; i < 4; ++i)
            dest->header.biHeight[i] = src->header.biHeight[i];

        for(i = 0; i < 2; ++i)
            dest->header.biPlane[i] = src->header.biPlane[i];

        for(i = 0; i < 2; ++i)
            dest->header.biBitCount[i] = src->header.biBitCount[i];

        for(i = 0; i < 4; ++i)
            dest->header.biCompression[i] = src->header.biCompression[i];

        for(i = 0; i < 4; ++i)
            dest->header.biSizeImage[i] = src->header.biSizeImage[i];

        for(i = 0; i < 4; ++i)
            dest->header.biXpelsPerMeter[i] = src->header.biXpelsPerMeter[i];

        for(i = 0; i < 4; ++i)
            dest->header.biYpelsPerMeter[i] = src->header.biYpelsPerMeter[i];

        for(i = 0; i < 4; ++i)
            dest->header.biClrUsed[i] = src->header.biClrUsed[i];

        for(i = 0; i < 4; ++i)
            dest->header.biClrImportant[i] = src->header.biClrImportant[i];

        return TRUE;
    }
    return FALSE;
}

e__bool BMP_copy_header_into_histogram(BMP_image* const src, BMP_histogram* const dest)
{
    if(src != NULL && dest != NULL)
    {
        int i;

        /*** HEADER FILE ***/
        for(i = 0; i < 2; ++i)
            dest->header.bfType[i] = src->header.bfType[i];

        for(i = 0; i < 4; ++i)
            dest->header.bfSize[i] = src->header.bfSize[i];

        for(i = 0; i < 2; ++i)
            dest->header.bfReserved1[i] = src->header.bfReserved1[i];

        for(i = 0; i < 2; ++i)
            dest->header.bfReserved2[i] = src->header.bfReserved2[i];

        for(i = 0; i < 4; ++i)
            dest->header.bfOffBits[i] = src->header.bfOffBits[i];

        /*** HEADER BITMAP ***/
        for(i = 0; i < 4; ++i)
            dest->header.biSize[i] = src->header.biSize[i];

        for(i = 0; i < 4; ++i)
            dest->header.biWidth[i] = src->header.biWidth[i];

        for(i = 0; i < 4; ++i)
            dest->header.biHeight[i] = src->header.biHeight[i];

        for(i = 0; i < 2; ++i)
            dest->header.biPlane[i] = src->header.biPlane[i];

        for(i = 0; i < 2; ++i)
            dest->header.biBitCount[i] = src->header.biBitCount[i];

        for(i = 0; i < 4; ++i)
            dest->header.biCompression[i] = src->header.biCompression[i];

        for(i = 0; i < 4; ++i)
            dest->header.biSizeImage[i] = src->header.biSizeImage[i];

        for(i = 0; i < 4; ++i)
            dest->header.biXpelsPerMeter[i] = src->header.biXpelsPerMeter[i];

        for(i = 0; i < 4; ++i)
            dest->header.biYpelsPerMeter[i] = src->header.biYpelsPerMeter[i];

        for(i = 0; i < 4; ++i)
            dest->header.biClrUsed[i] = src->header.biClrUsed[i];

        for(i = 0; i < 4; ++i)
            dest->header.biClrImportant[i] = src->header.biClrImportant[i];

        return TRUE;
    }
    return FALSE;
}

e__bool BMP_histogram_copy_header_into_BMP_image(BMP_histogram* const src, BMP_image* const dest)
{
    if(src != NULL && dest != NULL)
    {
        int i;

        /*** HEADER FILE ***/
        for(i = 0; i < 2; ++i)
            dest->header.bfType[i] = src->header.bfType[i];

        for(i = 0; i < 4; ++i)
            dest->header.bfSize[i] = src->header.bfSize[i];

        for(i = 0; i < 2; ++i)
            dest->header.bfReserved1[i] = src->header.bfReserved1[i];

        for(i = 0; i < 2; ++i)
            dest->header.bfReserved2[i] = src->header.bfReserved2[i];

        for(i = 0; i < 4; ++i)
            dest->header.bfOffBits[i] = src->header.bfOffBits[i];

        /*** HEADER BITMAP ***/
        for(i = 0; i < 4; ++i)
            dest->header.biSize[i] = src->header.biSize[i];

        for(i = 0; i < 4; ++i)
            dest->header.biWidth[i] = src->header.biWidth[i];

        for(i = 0; i < 4; ++i)
            dest->header.biHeight[i] = src->header.biHeight[i];

        for(i = 0; i < 2; ++i)
            dest->header.biPlane[i] = src->header.biPlane[i];

        for(i = 0; i < 2; ++i)
            dest->header.biBitCount[i] = src->header.biBitCount[i];

        for(i = 0; i < 4; ++i)
            dest->header.biCompression[i] = src->header.biCompression[i];

        for(i = 0; i < 4; ++i)
            dest->header.biSizeImage[i] = src->header.biSizeImage[i];

        for(i = 0; i < 4; ++i)
            dest->header.biXpelsPerMeter[i] = src->header.biXpelsPerMeter[i];

        for(i = 0; i < 4; ++i)
            dest->header.biYpelsPerMeter[i] = src->header.biYpelsPerMeter[i];

        for(i = 0; i < 4; ++i)
            dest->header.biClrUsed[i] = src->header.biClrUsed[i];

        for(i = 0; i < 4; ++i)
            dest->header.biClrImportant[i] = src->header.biClrImportant[i];

        return TRUE;
    }
    return FALSE;
}

/**
 * @brief      Get a copy of the BMP_image
 *
 * @param      bmp   The bitmap
 *
 * @return     The copy
 */
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
        copy->pixels = malloc(copy->height * sizeof(RGB*));
        for(i = 0; i < copy->height; ++i)
        {
            copy->pixels[i] = malloc(copy->width * sizeof(RGB));
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

/**
 * @brief      Apply Gray filter on the BMP_image pixels
 *
 * @param      bmp   The bitmap
 *
 * @return     TRUE if success, otherwise FALSE
 */
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

/**
 * @brief      Apply reversed filter on the BMP_image pixels
 *
 * @param      bmp   The bitmap
 *
 * @return     TRUE if success, otherwise FALSE
 */
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

/**
 * @brief      Apply a horizontal reverse on the BMP_image pixels
 *
 * @param      bmp   The bitmap
 *
 * @return     TRUE if success, otherwise FALSE
 */
e__bool BMP_set_horizontal_reversed(BMP_image* const bmp)
{
    if(bmp != NULL)
    {
        int i;
        int mid = bmp->height / 2;
        for(i = 0; i < mid; ++i)
        {
            // PAS BON
            RGB* line = bmp->pixels[i];
            bmp->pixels[i] = bmp->pixels[bmp->height-1 - i];
            bmp->pixels[bmp->height-1 - i] = line;
        }
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief      Apply a vertical reverse on the BMP_image pixels
 *
 * @param      bmp   The bitmap
 *
 * @return     TRUE if success, otherwise FALSE
 */
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
                RGB temp = bmp->pixels[i][j];
                bmp->pixels[i][j] = bmp->pixels[i][bmp->width-1 - j];
                bmp->pixels[i][bmp->width-1 - j] = temp;
            }
        }
        return TRUE;
    }
    return FALSE; 
}

/**
 * @brief      Set equalize histogram filter on BMP
 *
 * @param      bmp   The bitmap
 *
 * @return     TRUE if sucess, FALSE otherwise
 */
e__bool BMP_set_equalize_histogram(BMP_image* const bmp)
{
    if(bmp != NULL)
    {
        //DONNEES
        float nbPixels = bmp->width * bmp->height;

        int i,j;
        //tabPixel RGB
        float tabPixelR[256];
        float tabPixelG[256];
        float tabPixelB[256];
        

        //on initialise à zéro
        for(i=0; i<256; i++){
            tabPixelR[i]=0;
            tabPixelG[i]=0;
            tabPixelB[i]=0;
        }

        //on compte le nombre d'occurence
        for(i=0; i<bmp->height; i++){
            for(j=0; j<bmp->width; j++){
                tabPixelR[bmp->pixels[i][j].r]++;
                tabPixelG[bmp->pixels[i][j].g]++;
                tabPixelB[bmp->pixels[i][j].b]++;
            }
        }

        //tabProb RGB
        float tabProbR[256];
        float tabProbG[256];
        float tabProbB[256];

        for(i=0; i<256; i++){
            tabProbR[i]=tabPixelR[i]/nbPixels;
            tabProbG[i]=tabPixelG[i]/nbPixels;
            tabProbB[i]=tabPixelB[i]/nbPixels;
        }

        //tabProbCumulée RGB
        float tabProbCumulR[256];
        float tabProbCumulG[256];
        float tabProbCumulB[256];
        //initialisation
        tabProbCumulR[0]=tabProbR[0];
        tabProbCumulG[0]=tabProbG[0];
        tabProbCumulB[0]=tabProbB[0];

        for(i=1; i<256; i++){
            tabProbCumulR[i]=tabProbCumulR[i-1]+tabProbR[i];
            tabProbCumulG[i]=tabProbCumulG[i-1]+tabProbG[i];
            tabProbCumulB[i]=tabProbCumulB[i-1]+tabProbB[i];
        }

        //tabFinal RGB
        float tabFinalR[256];
        float tabFinalG[256];
        float tabFinalB[256];

        for(i=0; i<256; i++){
            tabFinalR[i]=tabProbCumulR[i]*256;
            tabFinalG[i]=tabProbCumulG[i]*256;
            tabFinalB[i]=tabProbCumulB[i]*256;
        }

        //on crée la nouvelle image

        // BMP_image* new_bmp = BMP_get_copy(bmp);

        for(i=0; i<bmp->height; i++){
            for(j=0; j<bmp->width; j++){

                bmp->pixels[i][j].r = tabFinalR[bmp->pixels[i][j].r];
                bmp->pixels[i][j].g = tabFinalG[bmp->pixels[i][j].g];
                bmp->pixels[i][j].b = tabFinalB[bmp->pixels[i][j].b];
            }
        }
        return TRUE;
    }
    return FALSE;
}

e__bool BMP_set_FIR_1D_horizontal_filter_with_depth(BMP_image* const bmp, int depth)
{
    if(bmp != NULL)
    {
        int         i, j, k;
        int         x_after, x_before;
        Int_RGB     pixel;
        int         value_taken;
        RGB**       pixels_out = NULL;

        // Allocate memory for the pixels out
        pixels_out = malloc(bmp->height * sizeof(RGB*));
        for(i = 0; i < bmp->height; ++i)
        {
            pixels_out[i] = malloc(bmp->width * sizeof(RGB));
        }

        // Set the FIR 1D filter
        for(i = 0; i < bmp->height; ++i) // HEIGHT
        {
            for(j = 0; j < bmp->width; ++j) // WIDTH
            {
                // Reading the pixel
                value_taken = 1;
                pixel.r = bmp->pixels[i][j].r;
                pixel.g = bmp->pixels[i][j].g;
                pixel.b = bmp->pixels[i][j].b;

                // Reading around the pixel
                for(k = 1; k <= depth; ++k)
                {
                    // Before the pixel
                    x_before = j - k;
                    if(x_before >= 0)
                    {
                        ++value_taken;
                        pixel.r += bmp->pixels[i][x_before].r;
                        pixel.g += bmp->pixels[i][x_before].g;
                        pixel.b += bmp->pixels[i][x_before].b;
                    }

                    // After the pixel
                    x_after = j + k;
                    if(x_after < bmp->width)
                    {
                        ++value_taken;
                        pixel.r += bmp->pixels[i][x_after].r;
                        pixel.g += bmp->pixels[i][x_after].g;
                        pixel.b += bmp->pixels[i][x_after].b;
                    }
                }
                pixel.r /= value_taken;
                pixel.g /= value_taken;
                pixel.b /= value_taken;

                pixels_out[i][j].r = pixel.r;
                pixels_out[i][j].g = pixel.g;
                pixels_out[i][j].b = pixel.b;
            }
        }

        // Free the last pixels array
        free_BMP_pixels(bmp);
        // And set the new
        bmp->pixels = pixels_out;

        return TRUE;
    }
    return FALSE;
}

e__bool BMP_set_FIR_1D_vertical_filter_with_depth(BMP_image* const bmp, int depth)
{
    if(bmp != NULL)
    {
        int         i, j, k;
        int         y_after, y_before;
        Int_RGB     pixel;
        int         value_taken;
        RGB**       pixels_out = NULL;

        // Allocate memory for the pixels out
        pixels_out = malloc(bmp->height * sizeof(RGB*));
        for(i = 0; i < bmp->height; ++i)
        {
            pixels_out[i] = malloc(bmp->width * sizeof(RGB));
        }

        // Set the FIR 1D filter
        for(i = 0; i < bmp->width; ++i) // WIDTH
        {
            for(j = 0; j < bmp->height; ++j) // HEIGHT
            {
                // Reading the pixel
                value_taken = 1;
                pixel.r = bmp->pixels[j][i].r;
                pixel.g = bmp->pixels[j][i].g;
                pixel.b = bmp->pixels[j][i].b;

                // Reading around the pixel
                for(k = 1; k <= depth; ++k)
                {
                    // Before the pixel
                    y_before = j - k;
                    if(y_before >= 0)
                    {
                        ++value_taken;
                        pixel.r += bmp->pixels[y_before][i].r;
                        pixel.g += bmp->pixels[y_before][i].g;
                        pixel.b += bmp->pixels[y_before][i].b;
                    }

                    // After the pixel
                    y_after = j + k;
                    if(y_after < bmp->height)
                    {
                        ++value_taken;
                        pixel.r += bmp->pixels[y_after][i].r;
                        pixel.g += bmp->pixels[y_after][i].g;
                        pixel.b += bmp->pixels[y_after][i].b;
                    }
                }
                pixel.r /= value_taken;
                pixel.g /= value_taken;
                pixel.b /= value_taken;

                pixels_out[j][i].r = pixel.r;
                pixels_out[j][i].g = pixel.g;
                pixels_out[j][i].b = pixel.b;
            }
        }

        // Free the last pixels array
        free_BMP_pixels(bmp);
        // And set the new
        bmp->pixels = pixels_out;

        return TRUE;
    }
    return FALSE;
}
e__bool BMP_set_FIR_2D_border_filter_x(BMP_image* const bmp)
{
    Matrix* matrix = create_Matrix(3,3);
    set_value_into_Matrix(matrix, 0, 0, -1);
    set_value_into_Matrix(matrix, 0, 1, -2);
    set_value_into_Matrix(matrix, 0, 2, -1);

    set_value_into_Matrix(matrix, 2, 0, 1);
    set_value_into_Matrix(matrix, 2, 1, 2);
    set_value_into_Matrix(matrix, 2, 2, 1);

    e__bool res = BMP_convolution_with_Matrix(bmp, matrix);
    return res;
}

e__bool BMP_set_FIR_2D_border_filter_y(BMP_image* const bmp)
{
    Matrix* matrix = create_Matrix(3,3);
    set_value_into_Matrix(matrix, 0, 0, -1);
    set_value_into_Matrix(matrix, 1, 0, -2);
    set_value_into_Matrix(matrix, 2, 0, -1);

    set_value_into_Matrix(matrix, 0, 2, 1);
    set_value_into_Matrix(matrix, 1, 2, 2);
    set_value_into_Matrix(matrix, 2, 2, 1);

    e__bool res = BMP_convolution_with_Matrix(bmp, matrix);
    return res;
}

e__bool BMP_set_sobel_filter(BMP_image* const bmp)
{
    if(bmp != NULL)
    {
        BMP_image* border_x = BMP_get_copy(bmp);
        BMP_image* border_y = BMP_get_copy(bmp);

        if(border_x != NULL && border_y != NULL)
        {
            BMP_set_FIR_2D_border_filter_x(border_x);
            BMP_set_FIR_2D_border_filter_y(border_y);

            int         i, j;
            RGB         pixel;
            Double_RGB  pixel_double;
            RGB**       pixels_out = NULL;

            // Allocate memory for the pixels out
            pixels_out = malloc(bmp->height * sizeof(RGB*));
            if(pixels_out != NULL)
            {
                for(i = 0; i < bmp->height; ++i)
                {
                    pixels_out[i] = malloc(bmp->width * sizeof(RGB));
                    if(pixels_out[i] == NULL)
                    {
                        printf("ERROR bad alloc : %d\n", ERR_BAD_ALLOC);
                        exit(ERR_BAD_ALLOC);
                    }
                }

                for(i = 0; i < bmp->height; ++i)
                {
                    for(j = 0; j < bmp->width; ++j)
                    {
                        pixel_double.r = (double)(border_x->pixels[i][j].r * border_x->pixels[i][j].r + border_y->pixels[i][j].r * border_y->pixels[i][j].r);
                        pixel_double.g = (double)(border_x->pixels[i][j].g * border_x->pixels[i][j].g + border_y->pixels[i][j].g * border_y->pixels[i][j].g);
                        pixel_double.b = (double)(border_x->pixels[i][j].b * border_x->pixels[i][j].b + border_y->pixels[i][j].b * border_y->pixels[i][j].b);

                        pixel.r = (int)sqrt(pixel_double.r);
                        pixel.g = (int)sqrt(pixel_double.g);
                        pixel.b = (int)sqrt(pixel_double.b);

                        pixels_out[i][j].r = pixel.r;
                        pixels_out[i][j].g = pixel.g;
                        pixels_out[i][j].b = pixel.b;
                    }
                }

                free_BMP_pixels(bmp);
                bmp->pixels = pixels_out;

                free_BMP_image(border_x);
                free_BMP_image(border_y);

                return TRUE;
            }
            else
            {
                printf("ERROR bad alloc : %d\n", ERR_BAD_ALLOC);
                exit(ERR_BAD_ALLOC);
            }
        }
    }
    return FALSE;
}

e__bool BMP_convolution_with_Matrix(BMP_image* const bmp, Matrix* const matrix)
{
    if(bmp != NULL && matrix != NULL)
    {
        if(matrix->width % 2 != 0
        && matrix->height % 2 != 0) // We need a matrix with odd width and height
        {
            int         i, j;                   // To browse the bmp
            int         k, l;                   // Offset into the bmp
            int         x_matrix, y_matrix;     // To browse the matrix
            int         x_index, y_index;       // Index of the readed pixel for the convolution
            int         x_mid_matrix = matrix->width / 2;
            int         y_mid_matrix = matrix->height / 2;
            
            Int_RGB     pixel;              // The new pixel
            RGB         bmp_pixel_browsed;  // The value of the pixel to use, usefull if the index is out the bmp array

            RGB**       pixels_out = NULL;  // The new bmp pixels array

            // Allocate memory for the pixels out
            pixels_out = malloc(bmp->height * sizeof(RGB*));
            for(i = 0; i < bmp->height; ++i)
            {
                pixels_out[i] = malloc(bmp->width * sizeof(RGB));
            }

            // Browse the whole image
            for(i = 0; i < bmp->height; ++i)
            {
                for(j = 0; j < bmp->width; ++j)
                {
                    // printf("(%d:%d)\n", j, i);
                    pixel.r = 0;
                    pixel.g = 0;
                    pixel.b = 0;
                    // By default, the value to use is the central pixel
                    bmp_pixel_browsed.r = bmp->pixels[i][j].r;
                    bmp_pixel_browsed.g = bmp->pixels[i][j].g;
                    bmp_pixel_browsed.b = bmp->pixels[i][j].b;


                    // Browse the whole matrix
                    // x_matrix and y_matrix are used to browse the Matrix
                    // k and l are used to browse the pixels array
                    for(y_matrix = 0, k = -y_mid_matrix; y_matrix < matrix->height; ++y_matrix, ++k)
                    {
                        y_index = i + k;

                        for(x_matrix = 0, l = -x_mid_matrix; x_matrix < matrix->width; ++x_matrix, ++l)
                        {
                            x_index = j + l;

                            // The y or x coord are outside the pixels array
                            if(y_index < 0 || y_index >= bmp->height
                            || x_index < 0 || x_index >= bmp->width)
                            {
                                // We calculate the convolution with the central pixel
                                bmp_pixel_browsed.r = bmp->pixels[i][j].r;
                                bmp_pixel_browsed.g = bmp->pixels[i][j].g;
                                bmp_pixel_browsed.b = bmp->pixels[i][j].b;
                            }

                            // The x and y coord are inside the pixels array
                            else
                            {
                                // We use the right pixel
                                bmp_pixel_browsed.r = bmp->pixels[y_index][x_index].r;
                                bmp_pixel_browsed.g = bmp->pixels[y_index][x_index].g;
                                bmp_pixel_browsed.b = bmp->pixels[y_index][x_index].b;
                            }

                            // The convolution operation
                            pixel.r += (bmp_pixel_browsed.r * matrix->values[y_matrix][x_matrix]);
                            pixel.g += (bmp_pixel_browsed.g * matrix->values[y_matrix][x_matrix]);
                            pixel.b += (bmp_pixel_browsed.b * matrix->values[y_matrix][x_matrix]);
                        }
                    }

                    // Adjust pixel value
                    // RED
                    if(pixel.r < 0)
                        pixel.r = 0;
                    else if(pixel.r > BMP_V_MAX)
                        pixel.r = BMP_V_MAX;

                    // GREEN
                    if(pixel.g < 0)
                        pixel.g = 0;
                    else if(pixel.g > BMP_V_MAX)
                        pixel.g = BMP_V_MAX;

                    // BLUE
                    if(pixel.b < 0)
                        pixel.b = 0;
                    else if(pixel.b > BMP_V_MAX)
                        pixel.b = BMP_V_MAX;

                    pixels_out[i][j].r = pixel.r;
                    pixels_out[i][j].g = pixel.g;
                    pixels_out[i][j].b = pixel.b;
                }
            }

            free_BMP_pixels(bmp);
            bmp->pixels = pixels_out;

            return TRUE;
        }
    }
    return FALSE;
}

/**
 * @brief      Get the histogram of a BMP_image
 *
 * @param      bmp          The BMP_image
 * @param      component    Which component catch (red, green, blue, luminosity)
 *
 * @return     The histogram of bmp
 */
BMP_histogram* BMP_get_histogram(BMP_image* const bmp, e__color component)
{
    BMP_histogram* histogram = malloc(sizeof(BMP_histogram));
    BMP_copy_header_into_histogram(bmp, histogram);
    int i, j;
    int pixel_value;

    histogram->component = component;
    histogram->size = BMP_V_MAX + 1;       // We need 0 to v_max included [0;v_max]
    histogram->intensity_values = malloc(histogram->size * sizeof(int)); // Allocate as many array space as the number of potentials pixels values in bmp 

    for(i = 0; i < histogram->size; ++i)    // Set all intensity value to 0
    {
        histogram->intensity_values[i] = 0;
    }

    for(i = 0; i < bmp->height; ++i)    // Foreach pixel
    {
        for(j = 0; j < bmp->width; ++j)
        {
            /**
             * Each case of the array is a intensity
             * So for each pixel
             * Increment the intensity which match with this pixel intensity
             */
            if(component == RED)
                pixel_value = bmp->pixels[i][j].r;
            else if(component == GREEN)
                pixel_value = bmp->pixels[i][j].g;
            else if(component == BLUE)
                pixel_value = bmp->pixels[i][j].b;
            else
                pixel_value = (bmp->pixels[i][j].r + bmp->pixels[i][j].g + bmp->pixels[i][j].b)/3;

            ++(histogram->intensity_values[pixel_value]);
        }
    }
    return histogram;
}
/**
 * @brief      Transform a BMP_histogram into a BMP_image
 *
 * @param      histogram  The histogram
 *
 * @return     The BMP_image which represent the Histogram
 */
BMP_image* BMP_get_BMP_image_from_BMP_histogram(BMP_histogram* const histogram)
{
    if(histogram != NULL)
    {
        if(histogram->intensity_values != NULL && histogram->size > 0)
        {
            BMP_image* bmp = malloc(sizeof(BMP_image));
            BMP_histogram_copy_header_into_BMP_image(histogram, bmp);
            int i, j;
            int max = histogram->intensity_values[0];

            RGB color;
            // Default and / or if component is ALL, draw in white
            color.r = 255;
            color.g = 255;
            color.b = 255;

            if(histogram->component == RED)
            {
                // color.r = 255;
                color.g = 0;
                color.b = 0;
            }
            else if(histogram->component == GREEN)
            {
                color.r = 0;
                // color.g = 255;
                color.b = 0;
            }
            else if(histogram->component == BLUE)
            {
                color.r = 0;
                color.g = 0;
                // color.b = 255;
            }

            bmp->width = histogram->size;           // A col of the histogram will be a a col into the picture

            for(i = 1; i < histogram->size; ++i)                // Search the higher intensity
            {
                int intensity = histogram->intensity_values[i];
                if(histogram->intensity_values[i] > max)
                    max = intensity;
            }

            bmp->height = max;                      // The line number is the same as the max value into the histogram
            
            int mask = 0x000000FF;
            int temp_value = 0;
            // Reading of width and height and convert into the header arrays
            for(i = 3; i >= 0; --i)
            {
                temp_value = mask & bmp->width;
                // printf("> %x & %x = %x\n", mask, bmp->width, temp_value);
                temp_value = temp_value >> (8 * (3-i));
                bmp->header.biWidth[i] = temp_value;

                temp_value = mask & bmp->height;
                temp_value = temp_value >> (8 * (3-i));
                bmp->header.biHeight[i] = temp_value;

                mask = mask << 8;
            }
            // printf("> %d %d\n", histogram->intensity_values[0], histogram->intensity_values[histogram->size - 1]);

            // Allocate the memory for a 2D array which will contain the pixels
            bmp->pixels = malloc(bmp->height * sizeof(int*));
            for(i = 0; i < bmp->height; ++i)
            {
                bmp->pixels[i] = malloc(bmp->width * sizeof(int));
            }


            for(i = bmp->height - 1; i >= 0; --i)        // Foreach pixel
            {
                for(j = 0; j < bmp->width; ++j)
                {
                    // For the j col
                    // If the line number (the real line number) is under the intensity value
                    // So the pixel should be empty (white)
                    // Otherwithe, it should be black
                    if(i > histogram->intensity_values[j]) // If the pixel should be black (background)
                    {
                        bmp->pixels[i][j].r = 0;
                        bmp->pixels[i][j].g = 0;
                        bmp->pixels[i][j].b = 0;
                    }
                    else                            // If the pixel pixel should be colored (histogramme)
                    {
                        bmp->pixels[i][j].r = color.r;
                        bmp->pixels[i][j].g = color.g;
                        bmp->pixels[i][j].b = color.b;
                    }
                }
            }
            return bmp;
        }
    }
    return NULL;
}

/**
 * @brief      Get a BMP_image with the cumulate of all Histogram
 *
 * @param      intensity  The intensity
 * @param      red        The red
 * @param      green      The green
 * @param      blue       The blue
 *
 * @return     TRUE if success, FALSE otherwise
 */
BMP_image* BMP_get_BMP_image_from_all_BMP_histogram(BMP_histogram* const intensity, BMP_histogram* const red, BMP_histogram* const green, BMP_histogram* const blue)
{
    if(intensity && red && green && blue)
    {
        if(intensity->intensity_values != NULL && intensity->size > 0
        && red->intensity_values != NULL && red->size > 0
        && green->intensity_values != NULL && green->size > 0
        && blue->intensity_values != NULL && blue->size > 0
        )
        {
            BMP_image* bmp = malloc(sizeof(BMP_image));
            BMP_histogram_copy_header_into_BMP_image(intensity, bmp);
            int i, j;
            int max = 0;
            int pixel;

            bmp->width = intensity->size;           // A col of the histogram will be a a col into the picture

            for(i = 0; i < intensity->size; ++i)                // Search the higher intensity
            {
                if(red->intensity_values[i] > max)
                    max = red->intensity_values[i];
                if(green->intensity_values[i] > max)
                    max = green->intensity_values[i];
                if(blue->intensity_values[i] > max)
                    max = blue->intensity_values[i];
            }

            bmp->height = max;                      // The line number is the same as the max value into the histogram
            
            int mask = 0x000000FF;
            int temp_value = 0;
            // Reading of width and height and convert into the header arrays
            for(i = 3; i >= 0; --i)
            {
                temp_value = mask & bmp->width;
                // printf("> %x & %x = %x\n", mask, bmp->width, temp_value);
                temp_value = temp_value >> (8 * (3-i));
                bmp->header.biWidth[i] = temp_value;

                temp_value = mask & bmp->height;
                temp_value = temp_value >> (8 * (3-i));
                bmp->header.biHeight[i] = temp_value;

                mask = mask << 8;
            }

            // Allocate the memory for a 2D array which will contain the pixels
            bmp->pixels = malloc(bmp->height * sizeof(int*));
            for(i = 0; i < bmp->height; ++i)
            {
                bmp->pixels[i] = malloc(bmp->width * sizeof(int));
            }


            for(i = bmp->height - 1; i >= 0; --i)        // Foreach pixel
            {
                for(j = 0; j < bmp->width; ++j)
                {
                    // For the j col
                    // By default, each pixel is black
                    bmp->pixels[i][j].r = 0;
                    bmp->pixels[i][j].g = 0;
                    bmp->pixels[i][j].b = 0;

                    // And add the component value for each pixel

                    if(i < red->intensity_values[j]) // If the pixel should be red
                    {
                        pixel = bmp->pixels[i][j].r + 255;
                        if(pixel > 255)
                            bmp->pixels[i][j].r = 255;
                        else
                            bmp->pixels[i][j].r = pixel;
                    }

                    if(i < green->intensity_values[j]) // If the pixel should be green
                    {
                        pixel = bmp->pixels[i][j].g + 255;
                        if(pixel > 255)
                            bmp->pixels[i][j].g = 255;
                        else
                            bmp->pixels[i][j].g = pixel;
                    }

                    if(i < blue->intensity_values[j]) // If the pixel should be blue
                    {
                        pixel = bmp->pixels[i][j].b + 255;
                        if(pixel > 255)
                            bmp->pixels[i][j].b = 255;
                        else
                            bmp->pixels[i][j].b = pixel;
                    }
                }
            }
            return bmp;
        }
    }
    return NULL;
}

/**
 * @brief      Transform a PGM_P2_histogram into a PGM_P2_image
 *             And save it into a file
 *
 * @param      histogram  The histogram
 * @param      file       The file
 *
 * @return     TRUE if success, FALSE otherwise
 */
e__bool BMP_save_histogram_as_BMP_file(BMP_histogram* const histogram, FILE* file)
{
    BMP_image* bmp_histogram = BMP_get_BMP_image_from_BMP_histogram(histogram);
    e__bool res = BMP_save_image_into_file(bmp_histogram, file);
    free_BMP_image(bmp_histogram);
    return res;
}


/**
 * @brief      Display BMP_image's header
 *
 * @param[in]  bmp   The bitmap
 */
void BMP_show_header(const BMP_image* const bmp)
{
    printf("-------------------------------------\n");
    printf(" HEADER FILE\n");
    printf("-------------------------------------\n");
    printf("> TYPE                  : %c%c\n", bmp->header.bfType[0], bmp->header.bfType[1]);
    printf("> SIZE FILE             : %.2x %.2x %.2x %.2x\n", bmp->header.bfSize[0], bmp->header.bfSize[1], bmp->header.bfSize[2], bmp->header.bfSize[3]);
    printf("> Reserved 1            : %.2x %.2x \n", bmp->header.bfReserved1[0], bmp->header.bfReserved1[1]);
    printf("> Reserved 2            : %.2x %.2x \n", bmp->header.bfReserved2[0], bmp->header.bfReserved2[1]);
    printf("> OFFSET                : %.2x %.2x %.2x %.2x\n", bmp->header.bfOffBits[0], bmp->header.bfOffBits[1], bmp->header.bfOffBits[2], bmp->header.bfOffBits[3]);
    printf("-------------------------------------\n");
    printf(" HEADER BITMAP\n");
    printf("> BITMAP SIZE           : %.2x %.2x %.2x %.2x\n", bmp->header.biSize[0], bmp->header.biSize[1], bmp->header.biSize[2], bmp->header.biSize[3]);
    printf("> BITMAP WIDTH          : %.2x %.2x %.2x %.2x\n", bmp->header.biWidth[0], bmp->header.biWidth[1], bmp->header.biWidth[2], bmp->header.biWidth[3]);
    printf("> BITMAP HEIGHT         : %.2x %.2x %.2x %.2x\n", bmp->header.biHeight[0], bmp->header.biHeight[1], bmp->header.biHeight[2], bmp->header.biHeight[3]);
    printf("> BITMAP PLANE          : %.2x %.2x\n", bmp->header.biPlane[0], bmp->header.biPlane[1]);
    printf("> BITMAP BitCount       : %.2x %.2x\n", bmp->header.biBitCount[0], bmp->header.biBitCount[1]);
    printf("> BITMAP Compression    : %.2x %.2x %.2x %.2x\n", bmp->header.biCompression[0], bmp->header.biCompression[1], bmp->header.biCompression[2], bmp->header.biCompression[3]);
    printf("> BITMAP SIZE bmp       : %.2x %.2x %.2x %.2x\n", bmp->header.biSizeImage[0], bmp->header.biSizeImage[1], bmp->header.biSizeImage[2], bmp->header.biSizeImage[3]);
    printf("> BITMAP Xpels          : %.2x %.2x %.2x %.2x\n", bmp->header.biXpelsPerMeter[0], bmp->header.biXpelsPerMeter[1], bmp->header.biXpelsPerMeter[2], bmp->header.biXpelsPerMeter[3]);
    printf("> BITMAP Ypels          : %.2x %.2x %.2x %.2x\n", bmp->header.biYpelsPerMeter[0], bmp->header.biYpelsPerMeter[1], bmp->header.biYpelsPerMeter[2], bmp->header.biYpelsPerMeter[3]);
    printf("> BITMAP ClrUsed        : %.2x %.2x %.2x %.2x\n", bmp->header.biClrUsed[0], bmp->header.biClrUsed[1], bmp->header.biClrUsed[2], bmp->header.biClrUsed[3]);
    printf("> BITMAP ClrImportant   : %.2x %.2x %.2x %.2x\n", bmp->header.biClrImportant[0], bmp->header.biClrImportant[1], bmp->header.biClrImportant[2], bmp->header.biClrImportant[3]);
    printf("-------------------------------------\n");
}

/**
 * @brief      Free the pixel array of a BMP_image
 *
 * @param      bmp   The bitmap
 */
void free_BMP_pixels(BMP_image* const bmp)
{
    if(bmp != NULL)
    {
        int i;
        for(i = 0; i < bmp->height; ++i)
            free(bmp->pixels[i]);
        free(bmp->pixels); 
    }
}

/**
 * @brief      Free a BMP_image
 *
 * @param      bmp   The bitmap
 */
void free_BMP_image(BMP_image* const bmp)
{
    if(bmp)
    {
        free_BMP_pixels(bmp);
        free(bmp);
    }
}

/**
 * @brief      Free a BMP_histogram
 *
 * @param      bmp   The bitmap
 */
void free_BMP_histogram(BMP_histogram* const histogram)
{
    if(histogram!= NULL)
    {
        free(histogram->intensity_values);
        free(histogram);
    }
}