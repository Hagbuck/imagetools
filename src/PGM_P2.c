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
PGM_P2_image* PGM_P2_get_image_from_file(FILE* file)
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

            if(char_readed == '#')          // If this line is a commentary
            {
                while(fgetc(file) != '\n'); // Go to the next line
            }
            else if(char_readed != EOF)
            {
                buffer[0] = char_readed;
                buffer_index = 1;
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

                        if(strcmp(buffer, "P2\n") != 0) // The magic number is not P2
                        {
                            printf("ERRO : %d\n", ERR_IMAGE_FILE_IS_INCORRECT);
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
                            if(char_readed != ' ')
                            {
                                buffer[buffer_index] = char_readed;
                                ++buffer_index;
                            }
                        }while(char_readed != ' ');
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
 * @brief      Create a new PGM_P2_image based on img
 *             with a reversed filter
 *
 * @param      img   The image
 *
 * @return     the new image reversed
 */
PGM_P2_image* PGM_P2_reversed_filter(PGM_P2_image *img)
{
    PGM_P2_image* reversed = PGM_P2_get_copy(img);
    int i,j;
    int pixel_value;

    for(i = 0; i < reversed->height; ++i)
    {
        for(j = 0; j < reversed->width; ++j)
        {
            pixel_value = reversed->pixels[i][j];           // Get the pixel value
            pixel_value = reversed->v_max - pixel_value;    // Reverse pixel value

            reversed->pixels[i][j] = pixel_value;           // Set the new pixel value
        }
    }
    return reversed;
}

/**
 * @brief      Get the histogram of a PGM_P2_image
 *
 * @param      img   The image
 *
 * @return     The histogram of img
 */
PGM_P2_histogram* PGM_P2_get_histogram(PGM_P2_image *img)
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
e__bool PGM_P2_save_image_into_file(PGM_P2_image* pgm, FILE* file)
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
 * @return     { description_of_the_return_value }
 */
e__bool PGM_P2_save_histogram_as_PGM_P2_file(PGM_P2_histogram* histogram, FILE* file)
{
    PGM_P2_image* pgm_histogram = PGM_P2_get_PGM_P2_image_from_PGM_P2_histogram(histogram);
    e__bool res = PGM_P2_save_image_into_file(pgm_histogram, file);
    free_PGM_P2_image(pgm_histogram);
    return res;
}

/**
 * @brief      copy a PGM_P2_image and return the new instance
 *
 * @param      img   The image
 *
 * @return     the copy of img
 */
PGM_P2_image* PGM_P2_get_copy(PGM_P2_image* img)
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
        for(int j = 0; j < copy->width; ++j)
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
PGM_P2_image* PGM_P2_get_PGM_P2_image_from_PGM_P2_histogram(PGM_P2_histogram* histogram)
{
    if(histogram != NULL)
    {
        if(histogram->intensity_value != NULL && histogram->size > 0)
        {
            PGM_P2_image* pgm = malloc(sizeof(PGM_P2_image*));
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
                    if((pgm->height - i) > histogram->intensity_value[j]) // If the pixel should be white
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
    || char_readed == 'LF'
    || char_readed == 'VT'
    || char_readed == 'BS' 
    || char_readed == 'CR' 
    || char_readed == 'TAB' 
    || char_readed == 'FF' 
    || char_readed == 0)
        return TRUE;
    return FALSE;
}

/**
 * @brief      Delete a PGM_P2_image
 *
 * @param      pgm   The pgm
 */
void free_PGM_P2_image(PGM_P2_image* pgm)
{
    int i;
    for(i = 0; i < pgm->height; ++i)
        free(pgm->pixels[i]);
    free(pgm->pixels);

    free(pgm);
}

/**
 * @brief      Delete a PGM_P2_histogram
 *
 * @param      histogram  The histogram
 */
void free_PGM_P2_histogram(PGM_P2_histogram* histogram)
{
    free(histogram->intensity_value);
    free(histogram);
}

/**
 * @brief      Display the pgm in the terminal
 *
 * @param      pgm   The pgm
 */
void display_PGM_P2_image(PGM_P2_image* pgm)
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
 * @brief      Display an histogram in the terminak
 *
 * @param      histogram  The histogram
 */
void display_PGM_P2_histogram(PGM_P2_histogram* histogram)
{
    int i;

    puts("Val : Int");
    for(i = 0; i < histogram->size; ++i)
    {
        printf("> %d : %d\n", i, histogram->intensity_value[i]);
    }
}