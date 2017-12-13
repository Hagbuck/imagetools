/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "PGM_P2.h"

/**
 * @brief      Get a PGM_P2_image from a PGM file
 *             Read the whole file line per line
 *             And fill the struct PGM_P2_image
 *
 * @param      file  The file
 *
 * @return     The PGM_P2_image
 */
PGM_P2_image* PGM_P2_get_image_from_file(FILE* const file)
{
    if(file)
    {
        PGM_P2_image* pgm = malloc(sizeof(PGM_P2_image));

        char buffer[MAX_CHAR_PER_LINE];       // Contain the line readed.
        int buffer_index;

        int line_number = 0;            // The real line number of the file   
        int picture_line_number = 0;    // The relative line number of picture line (The part with pixels values)
        int pixel_value;
        int i;
        
        char char_readed;

        do
        {
            char_readed = fgetc(file);

            // if(line_number > 2)
            // {
            //     if(is_separator(char_readed) == TRUE)
            //         while(is_separator(char_readed = fgetc(file)) == TRUE);
            // }

            if(char_readed == '#')          // If this line is a commentary
            {
                while(fgetc(file) != '\n'); // Go to the next line
            }
            else if(char_readed != EOF)
            {
                if(line_number <= 3)            // On the third first line we use the first char of the line as the first char .... Obviously
                {
                    if(is_separator(char_readed) == TRUE && char_readed != EOF)
                    {
                        while(is_separator(char_readed) == TRUE)
                        {
                            char_readed = fgetc(file);
                        }
                    }
                    buffer[0] = char_readed;
                    buffer_index = 1;
                }
                else                            // BUT : after during the reading of the pixel value, we read the first char of the next line
                {                               // So the char read here, is the second of the line...
                    buffer[1] = char_readed;
                    buffer_index = 2;
                }
                switch(line_number)
                {
                    /**
                     * Checking the PGM Magic number
                     */
                    case 0:
                        do
                        {
                            char_readed = fgetc(file);
                            buffer[buffer_index] = char_readed;
                            ++buffer_index;

                        }while(char_readed != '\n');
                        buffer[buffer_index] = '\0';

                        // if(strcmp(buffer, "P2\n") != 0) // The magic number is not P2
                        if(buffer[0] != 'P'
                        || buffer[1] != '2')
                        {
                            printf("ERROR : %d\n", ERR_IMAGE_FILE_IS_INCORRECT);
                            exit(ERR_IMAGE_FILE_IS_INCORRECT);
                        }
                    break;

                    /**
                     * Searching width and height
                     */
                    case 1:
                        do
                        {
                            char_readed = fgetc(file);
                            if(char_readed != ' ')
                            {
                                buffer[buffer_index] = char_readed;
                                ++buffer_index;
                            }
                        }while(char_readed != ' ');
                        buffer[buffer_index] = '\0';

                        pgm->width = atoi(buffer);

                        while((char_readed = fgetc(file)) == ' ');

                        buffer_index = 1;
                        buffer[0] = char_readed;
                        do
                        {
                            char_readed = fgetc(file);
                            if(is_separator(char_readed) == FALSE)
                            {
                                buffer[buffer_index] = char_readed;
                                ++buffer_index;
                            }
                        }while(is_separator(char_readed) == FALSE);
                        buffer[buffer_index] = '\0';

                        pgm->height = atoi(buffer);

                        // Allocate the memory for a 2D array which will contain the pixels
                        pgm->pixels = malloc(pgm->height * sizeof(int*));
                        for(i = 0; i < pgm->height; ++i)
                        {
                            pgm->pixels[i] = malloc(pgm->width * sizeof(int));
                        }
                    break;

                    /**
                     * Searching Max value
                     */
                    case 2:
                        do
                        {
                            char_readed = fgetc(file);
                            if(is_separator(char_readed) == FALSE)
                            {
                                buffer[buffer_index] = char_readed;
                                ++buffer_index;
                            }
                        }while(is_separator(char_readed) == FALSE);
                        buffer[buffer_index] = '\0';

                        pgm->v_max = atoi(buffer);
                    break;

                    /**
                     * All other line which are a part of the picture
                     */
                    default:
                        for(i = 0; i < pgm->width; ++i)
                        {
                            while(is_separator(char_readed) == FALSE)
                            {
                                char_readed = fgetc(file);
                                if(is_separator(char_readed) == FALSE)
                                {
                                    buffer[buffer_index] = char_readed;
                                    ++buffer_index;
                                }
                            }

                            buffer[buffer_index] = '\0';

                            pixel_value = atoi(buffer);
                            pgm->pixels[picture_line_number][i] = pixel_value;

                            while(is_separator(char_readed) == TRUE && char_readed != EOF)
                            {
                                char_readed = fgetc(file);
                            }
                            
                            buffer[0] = char_readed;
                            buffer_index = 1;
                        }
                        ++picture_line_number;
                    break;
                }
                ++line_number;
            }

        }while(char_readed != EOF);

        return pgm;
    }
    exit(ERR_FILE_IS_NULL);
}

/**
 * @brief      Set the reversed filter on a PGM_P2_image
 *
 * @param      img   The image
 *
 * @return     True if success, otherwise False
 */
e__bool PGM_P2_set_reversed_filter(PGM_P2_image* const img)
{
    if(img != NULL)
    {
        int i,j;
        int pixel_value;

        for(i = 0; i < img->height; ++i)
        {
            for(j = 0; j < img->width; ++j)
            {
                pixel_value = img->pixels[i][j];           // Get the pixel value
                pixel_value = img->v_max - pixel_value;    // Reverse pixel value

                img->pixels[i][j] = pixel_value;           // Set the new pixel value
            }
        }
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief      Create a new PGM_P2_image based on img
 *             with a reversed filter
 *
 * @param      img   The image
 *
 * @return     the new image reversed
 */
PGM_P2_image* PGM_P2_reversed_filter(PGM_P2_image* const img)
{
    PGM_P2_image* reversed = PGM_P2_get_copy(img);
    PGM_P2_set_reversed_filter(reversed);
    // int i,j;
    // int pixel_value;

    // for(i = 0; i < reversed->height; ++i)
    // {
    //     for(j = 0; j < reversed->width; ++j)
    //     {
    //         pixel_value = reversed->pixels[i][j];           // Get the pixel value
    //         pixel_value = reversed->v_max - pixel_value;    // Reverse pixel value

    //         reversed->pixels[i][j] = pixel_value;           // Set the new pixel value
    //     }
    // }
    return reversed;
}

/**
 * @brief      Apply a horizontal reverse on the PGM_P2_image pixels
 *
 * @param      img   The pgm
 *
 * @return     TRUE if success, otherwise FALSE
 */
e__bool PGM_P2_set_horizontal_reversed(PGM_P2_image* const img)
{
    if(img != NULL)
    {
        int i;
        int mid = img->height / 2;
        for(i = 0; i < mid; ++i)
        {
            // PAS BON
            int* line = img->pixels[i];
            img->pixels[i] = img->pixels[img->height-1 - i];
            img->pixels[img->height-1 - i] = line;
        }
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief      Apply a vertical reverse on the PGM_P2_image pixels
 *
 * @param      img   The pgm
 *
 * @return     TRUE if success, otherwise FALSE
 */
e__bool PGM_P2_set_vertical_reversed(PGM_P2_image* const img)
{
    if(img != NULL)
    {
        int i,j;
        int half_width = img->width / 2;
        for(i = 0; i < img->height; ++i)
        {
            for(j = 0; j < half_width; ++j)
            {
                int temp = img->pixels[i][j];
                img->pixels[i][j] = img->pixels[i][img->width-1 - j];
                img->pixels[i][img->width-1 - j] = temp;
            }
        }
        return TRUE;
    }
    return FALSE; 
}

/**
 * @brief      Set the FIR 1D horizontal filter on a PGM_P2_image
 *
 * @param      img   The image
 *
 * @return     TRUE if sucess, FALSE otherwise
 */
e__bool PGM_P2_set_FIR_1D_horizontal_filter(PGM_P2_image* const img)
{
    return PGM_P2_set_FIR_1D_horizontal_filter_with_depth(img, 1);
    // if(img != NULL)
    // {
    //     int     i, j;
    //     int**   pixels_out = NULL;

    //     // Allocate memory for the pixels out
    //     pixels_out = malloc(img->height * sizeof(int*));
    //     for(i = 0; i < img->height; ++i)
    //     {
    //         pixels_out[i] = malloc(img->width * sizeof(int));
            
    //         // Copy the first and last value for each line (because the filter will not copy them)
    //         // And it's not necessary to copy the whole matrix because the next loop will fill it
    //         pixels_out[i][0] = img->pixels[i][0];
    //         pixels_out[i][img->width -1] = img->pixels[i][img->width -1];
    //     }

    //     // Set the FIR 1D filter
    //     for(i = 0; i < img->height; ++i) // HEIGHT
    //     {
    //         for(j = 1; j < img->width - 1; ++j) // WIDTH [+1;-1]
    //         {
    //             pixels_out[i][j] = (img->pixels[i][j - 1] + img->pixels[i][j] + img->pixels[i][j + 1]) / 3;
    //         }
    //     }

    //     // Free the last pixels array, and set the new
    //     for(i = 0; i < img->height; ++i)
    //         free(img->pixels[i]);
    //     free(img->pixels);
    //     img->pixels = pixels_out;
    //     return TRUE;
    // }
    // return FALSE;
}

/**
 * @brief      Set the FIR 1D horizontal with depth on a PGM_P2_image
 *
 * @param      img    The image
 * @param[in]  depth  The depth
 *
 * @return     TRUE if sucess, FALSE otherwise
 */
e__bool PGM_P2_set_FIR_1D_horizontal_filter_with_depth(PGM_P2_image* const img, int depth)
{
    if(img != NULL)
    {
        int     i, j, k;
        int     x_after, x_before;
        int     pixel;
        int     value_taken = 0;
        int**   pixels_out = NULL;

        // Allocate memory for the pixels out
        pixels_out = malloc(img->height * sizeof(int*));
        for(i = 0; i < img->height; ++i)
        {
            pixels_out[i] = malloc(img->width * sizeof(int));
        }

        // Set the FIR 1D filter
        for(i = 0; i < img->height; ++i) // HEIGHT
        {
            for(j = 0; j < img->width; ++j) // WIDTH
            {
                // Reading the pixel
                value_taken = 1;
                pixel = img->pixels[i][j];

                // Reading around the pixel
                for(k = 1; k <= depth; ++k)
                {
                    // Before the pixel
                    x_before = j - k;
                    if(x_before >= 0)
                    {
                        ++value_taken;
                        pixel += img->pixels[i][x_before];
                    }

                    // After the pixel
                    x_after = j + k;
                    if(x_after < img->width)
                    {
                        ++value_taken;
                        pixel += img->pixels[i][x_after];
                    }
                }
                pixel /= value_taken;

                pixels_out[i][j] = pixel;
            }
        }

        // Free the last pixels array
        free_PGM_P2_pixels(img);
        // And set the new
        img->pixels = pixels_out;

        return TRUE;
    }
    return FALSE;
}

/**
 * @brief      Set the FIR 1D vertical filter on a PGM_P2_image
 *
 * @param      img   The image
 *
 * @return     TRUE if sucess, FALSE otherwise
 */
e__bool PGM_P2_set_FIR_1D_vertical_filter(PGM_P2_image* const img)
{
    return PGM_P2_set_FIR_1D_vertical_filter_with_depth(img, 1);
}

/**
 * @brief      Set the FIR 1D vertical with depth on a PGM_P2_image
 *
 * @param      img    The image
 * @param[in]  depth  The depth
 *
 * @return     TRUE if sucess, FALSE otherwise
 */
e__bool PGM_P2_set_FIR_1D_vertical_filter_with_depth(PGM_P2_image* const img, int depth)
{
    if(img != NULL)
    {
        int     i, j, k;
        int     y_after, y_before;
        int     pixel;
        int     value_taken = 0;
        int**   pixels_out = NULL;

        // Allocate memory for the pixels out
        pixels_out = malloc(img->height * sizeof(int*));
        for(i = 0; i < img->height; ++i)
        {
            pixels_out[i] = malloc(img->width * sizeof(int));
        }

        // Set the FIR 1D filter
        for(i = 0; i < img->width; ++i) // WIDTH
        {
            for(j = 0; j < img->height; ++j) // HEIGHT
            {
                // Reading the pixel
                value_taken = 1;
                pixel = img->pixels[j][i];

                // Reading around the pixel
                for(k = 1; k <= depth; ++k)
                {
                    // Before the pixel
                    y_before = j - k;
                    if(y_before >= 0)
                    {
                        ++value_taken;
                        pixel += img->pixels[y_before][i];
                    }

                    // After the pixel
                    y_after = j + k;
                    if(y_after < img->height)
                    {
                        ++value_taken;
                        pixel += img->pixels[y_after][i];
                    }
                }
                pixel /= value_taken;

                pixels_out[j][i] = pixel;
            }
        }

        // Free the last pixels array
        free_PGM_P2_pixels(img);
        // And set the new
        img->pixels = pixels_out;

        return TRUE;
    }
    return FALSE;
}

/**
 * @brief      Set the FIR border filter x on a PGM_P2_image
 *
 * @param      pgm   The pgm
 *
 * @return     TRUE if sucess, FALSE otherwise
 */
e__bool PGM_P2_set_FIR_2D_border_filter_x(PGM_P2_image* const pgm)
{
    Matrix* matrix = create_Matrix(3,3);
    set_value_into_Matrix(matrix, 0, 0, -1);
    set_value_into_Matrix(matrix, 0, 1, -2);
    set_value_into_Matrix(matrix, 0, 2, -1);

    set_value_into_Matrix(matrix, 2, 0, 1);
    set_value_into_Matrix(matrix, 2, 1, 2);
    set_value_into_Matrix(matrix, 2, 2, 1);

    e__bool res = PGM_P2_convolution_with_Matrix(pgm, matrix);
    return res;
}

/**
 * @brief      Set the FIR border filter y on a PGM_P2_image
 *
 * @param      pgm   The pgm
 *
 * @return     TRUE if sucess, FALSE otherwise
 */
e__bool PGM_P2_set_FIR_2D_border_filter_y(PGM_P2_image* const pgm)
{
    Matrix* matrix = create_Matrix(3,3);
    set_value_into_Matrix(matrix, 0, 0, -1);
    set_value_into_Matrix(matrix, 1, 0, -2);
    set_value_into_Matrix(matrix, 2, 0, -1);

    set_value_into_Matrix(matrix, 0, 2, 1);
    set_value_into_Matrix(matrix, 1, 2, 2);
    set_value_into_Matrix(matrix, 2, 2, 1);

    e__bool res = PGM_P2_convolution_with_Matrix(pgm, matrix);
    return res;
}

/**
 * @brief      Apply the sobel filter on a PGM_P2_image
 *
 * @param      pgm   The pgm
 *
 * @return     TRUE if sucess, FALSE otherwise
 */
e__bool PGM_P2_set_sobel_filter(PGM_P2_image* const pgm)
{
    if(pgm != NULL)
    {
        PGM_P2_image* border_x = PGM_P2_get_copy(pgm);
        PGM_P2_image* border_y = PGM_P2_get_copy(pgm);

        if(border_x != NULL && border_y != NULL)
        {
            PGM_P2_set_FIR_2D_border_filter_x(border_x);
            PGM_P2_set_FIR_2D_border_filter_y(border_y);

            int     i, j;
            int     pixel;
            double  pixel_double;
            int**   pixels_out = NULL;

            // Allocate memory for the pixels out
            pixels_out = malloc(pgm->height * sizeof(int*));
            if(pixels_out != NULL)
            {
                for(i = 0; i < pgm->height; ++i)
                {
                    pixels_out[i] = malloc(pgm->width * sizeof(int));
                    if(pixels_out[i] == NULL)
                    {
                        printf("ERROR bad alloc : %d\n", ERR_BAD_ALLOC);
                        exit(ERR_BAD_ALLOC);
                    }
                }

                for(i = 0; i < pgm->height; ++i)
                {
                    for(j = 0; j < pgm->width; ++j)
                    {
                        pixel_double = (double)(border_x->pixels[i][j] * border_x->pixels[i][j] + border_y->pixels[i][j] * border_y->pixels[i][j]);
                        pixel = (int)sqrt(pixel_double);
                        pixels_out[i][j] = pixel;
                    }
                }

                free_PGM_P2_pixels(pgm);
                pgm->pixels = pixels_out;

                free_PGM_P2_image(border_x);
                free_PGM_P2_image(border_y);

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

/**
 * @brief      Apply the convolution between the pgm pixels and the matrix
 *
 * @param      pgm     The pgm
 * @param      matrix  The matrix
 *
 * @return     TRUE if sucess, FALSE otherwise
 */
e__bool PGM_P2_convolution_with_Matrix(PGM_P2_image* const pgm, Matrix* const matrix)
{
    if(pgm != NULL && matrix != NULL)
    {
        if(matrix->width % 2 != 0
        && matrix->height % 2 != 0) // We need a matrix with odd width and height
        {
            int     i, j;                   // To browse the pgm
            int     k, l;                   // Offset into the pgm
            int     x_matrix, y_matrix;     // To browse the matrix
            int     x_index, y_index;       // Index of the readed pixel for the convolution
            int     x_mid_matrix = matrix->width / 2;
            int     y_mid_matrix = matrix->height / 2;
            
            int     pixel;              // The new pixel
            int     pgm_pixel_browsed;  // The value of the pixel to use, usefull if the index is out the pgm array

            int**   pixels_out = NULL;  // The new pgm pixels array

            // Allocate memory for the pixels out
            pixels_out = malloc(pgm->height * sizeof(int*));
            for(i = 0; i < pgm->height; ++i)
            {
                pixels_out[i] = malloc(pgm->width * sizeof(int));
            }
            
            // Browse the whole image
            for(i = 0; i < pgm->height; ++i)
            {
                for(j = 0; j < pgm->width; ++j)
                {
                    pixel = 0;
                    pgm_pixel_browsed = pgm->pixels[i][j];  // By default, the value to use is the central pixel

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
                            if(y_index < 0 || y_index >= pgm->height
                            || x_index < 0 || x_index >= pgm->width)
                            {
                                // We calculate the convolution with the central pixel
                                pgm_pixel_browsed = pgm->pixels[i][j];
                            }

                            // The x and y coord are inside the pixels array
                            else
                            {
                                // We use the right pixel
                                pgm_pixel_browsed = pgm->pixels[y_index][x_index];
                            }

                            // The convolution operation
                            pixel += (pgm_pixel_browsed * matrix->values[y_matrix][x_matrix]);
                        }
                    }

                    // Adjust pixel value
                    if(pixel < 0)
                        pixel = 0;
                    else if(pixel > pgm->v_max)
                        pixel = pgm->v_max;

                    pixels_out[i][j] = pixel;
                }
            }

            free_PGM_P2_pixels(pgm);
            pgm->pixels = pixels_out;

            return TRUE;
        }
    }
    return FALSE;
}

/**
 * @brief      Get the histogram of a PGM_P2_image
 *
 * @param      img   The image
 *
 * @return     The histogram of img
 */
PGM_P2_histogram* PGM_P2_get_histogram(PGM_P2_image* const img)
{
    PGM_P2_histogram* histogram = malloc(sizeof(PGM_P2_histogram));
    int i, j;
    int pixel_value;

    histogram->size = img->v_max + 1;       // We need 0 to v_max included [0;v_max]
    histogram->intensity_value = malloc(histogram->size * sizeof(int)); // Allocate as many array space as the number of potentials pixels values in img 

    for(i = 0; i < histogram->size; ++i)    // Set all intensity value to 0
    {
        histogram->intensity_value[i] = 0;
    }

    for(i = 0; i < img->height; ++i)    // Foreach pixel
    {
        for(j = 0; j < img->width; ++j)
        {
            /**
             * Each case of the array is a intensity
             * So for each pixel
             * Increment the intensity which match with this pixel intensity
             */
            pixel_value = img->pixels[i][j];

            ++(histogram->intensity_value[pixel_value]);
        }
    }
    return histogram;
}

/**
 * @brief      Transform a PGM_P2_image into a string
 *             And save it into a file
 *
 * @param      pgm   The pgm
 * @param      file  The file
 *
 * @return     TRUE if the save success, FALSE otherwise
 */
e__bool PGM_P2_save_image_into_file(PGM_P2_image* const pgm, FILE* const file)
{
    int width = pgm->width;
    int height = pgm->height;
    // char str_pgm[FILE_MAX_SIZE];        // A string which contain the pgm as a string
    
    char* str_pgm = malloc((HEADER_PGM_SIZE * sizeof(char))   // Space for the header
        + ((8 * width * height) + height) * sizeof(char));    // Space for pixels (8 for maximal int size + ' ' (7+1)) (+height for each '\n')

    char str_number[NUMBER_MAX_SIZE];   // A string which contain a number, used to collect the pixel value

    sprintf(str_pgm, "P2\n%d %d\n%d\n", width, height, pgm->v_max); // Add the headers values into the string

    int str_pgm_index = strlen(str_pgm);

    /**
     * For each pixels
     */
    int i, j, k;
    for(i = 0; i < height; ++i)
    {
        for(j = 0; j < width; ++j)
        {
            sprintf(str_number, "%d ", pgm->pixels[i][j]);  // Add the pixel value
            k = 0;
            while(str_number[k] != '\0')        // Add the pixel value into the str_pgm
            {
                str_pgm[str_pgm_index] = str_number[k];
                ++str_pgm_index;
                ++k;
            }
        }
        str_pgm[str_pgm_index] = '\n';
        ++str_pgm_index;
    }
    return save_string_into_file(str_pgm, file);
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
e__bool PGM_P2_save_histogram_as_PGM_P2_file(PGM_P2_histogram* const histogram, FILE* const file)
{
    PGM_P2_image* pgm_histogram = PGM_P2_get_PGM_P2_image_from_PGM_P2_histogram(histogram);
    e__bool res = PGM_P2_save_image_into_file(pgm_histogram, file);
    free_PGM_P2_image(pgm_histogram);
    return res;
}

/**
 * @brief      Set equalization filter into PGM_P2_image
 *
 * @param      pgm   The pgm
 *
 * @return     { description_of_the_return_value }
 */
e__bool PGM_P2_set_equalize_histogram(PGM_P2_image* const pgm)
{
    if(pgm != NULL)
    {
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief      copy a PGM_P2_image and return the new instance
 *
 * @param      img   The image
 *
 * @return     the copy of img
 */
PGM_P2_image* PGM_P2_get_copy(PGM_P2_image* const img)
{
    PGM_P2_image* copy = malloc(sizeof(PGM_P2_image));
    int i,j;

    copy->height = img->height;
    copy->width  = img->width;
    copy->v_max  = img->v_max;

    // Allocate the memory for a 2D array which will contain the pixels
    copy->pixels = malloc(copy->height * sizeof(int*));
    for(i = 0; i < copy->height; ++i)
    {
        copy->pixels[i] = malloc(copy->width * sizeof(int));
        for(j = 0; j < copy->width; ++j)
        {
            copy->pixels[i][j] = img->pixels[i][j];
        }
    }
    return copy;
}

/**
 * @brief      Transform a PGM_P2_histogram into a PGM_P2_image
 *
 * @param      histogram  The histogram
 *
 * @return     The PGM_P2_image which represent the Histogram
 */
PGM_P2_image* PGM_P2_get_PGM_P2_image_from_PGM_P2_histogram(PGM_P2_histogram* const histogram)
{
    if(histogram != NULL)
    {
        if(histogram->intensity_value != NULL && histogram->size > 0)
        {
            PGM_P2_image* pgm = malloc(sizeof(PGM_P2_image));
            int i, j;
            int max = histogram->intensity_value[0];

            pgm->width = histogram->size;           // A col of the histogram will be a a col into the picture
            pgm->v_max = 1;                         // Only need one color

            for(i = 1; i < histogram->size; ++i)                // Search the higher intensity
            {
                int intensity = histogram->intensity_value[i];
                if(histogram->intensity_value[i] > max)
                    max = intensity;
            }

            pgm->height = max;                      // The line number is the same as the max value into the histogram

            // Allocate the memory for a 2D array which will contain the pixels
            pgm->pixels = malloc(pgm->height * sizeof(int*));
            for(i = 0; i < pgm->height; ++i)
            {
                pgm->pixels[i] = malloc(pgm->width * sizeof(int));
            }


            for(i = 0; i < pgm->height; ++i)        // Foreach pixel
            {
                for(j = 0; j < pgm->width; ++j)
                {
                    // For the j col
                    // If the line number (the real line number) is under the intensity value
                    // So the pixel should be empty (white)
                    // Otherwithe, it should be black
                    if((pgm->height - i) <= histogram->intensity_value[j]) // If the pixel should be white
                    {
                        pgm->pixels[i][j] = pgm->v_max;
                    }
                    else                            // If the pixel pixel should be black
                    {
                        pgm->pixels[i][j] = 0;
                    }
                }
            }
            return pgm;
        }
    }
    return NULL;
}

/**
 * @brief      Determines if the character is a separator.
 *
 * @param[in]  char_readed  The character readed
 *
 * @return     True if separator, False otherwise.
 */
e__bool is_separator(char char_readed)
{
    // if(char_readed == ' ' || char_readed == '\n' || char_readed == '\t' || char_readed == 'EOF' || char_readed == 'LF' || char_readed == 0)
    if(char_readed == ' '
    || char_readed == '\n'
    || char_readed == '\t'
    || char_readed == EOF
    || char_readed == 0x0A
    || char_readed == 0x0B
    || char_readed == 0x08
    || char_readed == 0x0D
    || char_readed == 0x09
    || char_readed == 0x14
    || char_readed == 0)
        return TRUE;
    return FALSE;
}

void free_PGM_P2_pixels(PGM_P2_image* const pgm)
{
    if(pgm != NULL)
    {
        int i;
        for(i = 0; i < pgm->height; ++i)
            free(pgm->pixels[i]);
        free(pgm->pixels);
    }
}

/**
 * @brief      Delete a PGM_P2_image
 *
 * @param      pgm   The pgm
 */
void free_PGM_P2_image(PGM_P2_image* const pgm)
{
    if(pgm != NULL)
    {
        free_PGM_P2_pixels(pgm);
        free(pgm);
    }
}

/**
 * @brief      Delete a PGM_P2_histogram
 *
 * @param      histogram  The histogram
 */
void free_PGM_P2_histogram(PGM_P2_histogram* const histogram)
{
    if(histogram!= NULL)
    {
        free(histogram->intensity_value);
        free(histogram);
    }
}

/**
 * @brief      Display the pgm in the terminal
 *
 * @param      pgm   The pgm
 */
void display_PGM_P2_image(PGM_P2_image* const pgm)
{
    int i, j;

    printf("PGM(%d, %d) vmax : %d\n", pgm->width, pgm->height, pgm->v_max);

    for(i = 0; i < pgm->height; ++i)
    {
        for(j = 0; j < pgm->width; ++j)
        {
            printf("%d ", pgm->pixels[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief      Display a histogram in the terminal
 *
 * @param      histogram  The histogram
 */
void display_PGM_P2_histogram(PGM_P2_histogram* const histogram)
{
    int i;

    puts("Val : Int");
    for(i = 0; i < histogram->size; ++i)
    {
        printf("> %d : %d\n", i, histogram->intensity_value[i]);
    }
}




/**
 * @brief      Set equalize histogram filter on PGM_P2
 *
 * @param      pgm   The bitmap
 *
 * @return     TRUE if sucess, FALSE otherwise
 */
e__bool PGM_P2_set_equalize_histogram(PGM_P2_image* const pgm)
{
    if(pgm != NULL)
    {
        //DONNEES
        float nbPixels = pgm->width * pgm->height;

        int i,j;
        int taille=pgm->v_max;
        //tabPixel nuance de gris
        float tabPixel;
        

        //on initialise à zéro
        for(i=0; i<taille; i++){
            tabPixel[i]=0;
        }

        //on compte le nombre d'occurence
        for(i=0; i<pgm->height; i++){
            for(j=0; j<pgm->width; j++){
                tabPixel[pgm->pixels[i][j]]++;
            }
        }

        //tabProb nuance de gris
        float tabProb[taille];

        for(i=0; i<taille; i++){
            tabProb[i]=tabPixel[i]/nbPixels;
        }

        //tabProbCumulée nuance de gris
        float tabProbCumul[taille];

        //initialisation
        tabProbCumul[0]=tabProb[0];

        for(i=1; i<taille; i++){
            tabProbCumul[i]=tabProbCumul[i-1]+tabProb[i];
        }

        //tabFinal nuance de gris
        float tabFinal[taille];

        for(i=0; i<taille; i++){
            tabFinal[i]=tabProbCumul[i]*taille;
        }

        //on crée la nouvelle image

        // PGM_P2_image* new_pgm = PGM_P2_image_get_copy(pgm);

        for(i=0; i<pgm->height; i++){
            for(j=0; j<pgm->width; j++){

                pgm->pixels[i][j] = tabFinal[pgm->pixels[i][j]];
            }
        }
        return TRUE;
    }
    return FALSE;
}