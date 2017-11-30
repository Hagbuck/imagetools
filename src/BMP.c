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
                    bmp->width += bmp->biWidth[i];
                    
                    bmp->height = bmp->height << 8;
                    bmp->height += bmp->biHeight[i];  
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
 * @brief      Display BMP_image's header
 *
 * @param[in]  bmp   The bitmap
 */
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
    printf("> BITMAP SIZE bmp       : %.2x %.2x %.2x %.2x\n", bmp->biSizeImage[0], bmp->biSizeImage[1], bmp->biSizeImage[2], bmp->biSizeImage[3]);
    printf("> BITMAP Xpels          : %.2x %.2x %.2x %.2x\n", bmp->biXpelsPerMeter[0], bmp->biXpelsPerMeter[1], bmp->biXpelsPerMeter[2], bmp->biXpelsPerMeter[3]);
    printf("> BITMAP Ypels          : %.2x %.2x %.2x %.2x\n", bmp->biYpelsPerMeter[0], bmp->biYpelsPerMeter[1], bmp->biYpelsPerMeter[2], bmp->biYpelsPerMeter[3]);
    printf("> BITMAP ClrUsed        : %.2x %.2x %.2x %.2x\n", bmp->biClrUsed[0], bmp->biClrUsed[1], bmp->biClrUsed[2], bmp->biClrUsed[3]);
    printf("> BITMAP ClrImportant   : %.2x %.2x %.2x %.2x\n", bmp->biClrImportant[0], bmp->biClrImportant[1], bmp->biClrImportant[2], bmp->biClrImportant[3]);
    printf("-------------------------------------\n");
}

/**
 * @brief      Free the pixel array of a BMP_image
 *
 * @param      bmp   The bitmap
 */
void free_BMP_pixels(BMP_image* const bmp)
{
    int i;
    for(i = 0; i < bmp->height; ++i)
        free(bmp->pixels[i]);
    free(bmp->pixels); 
}

/**
 * @brief      Free a BMP_image
 *
 * @param      bmp   The bitmap
 */
void free_BMP_image(BMP_image* const bmp)
{
    free_BMP_pixels(bmp);
    free(bmp);
}