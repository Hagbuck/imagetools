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

        char buffer[BUFFER_SIZE];       // Contain the line readed.

        int line_number = 0;            // The real line number of the file   
        int picture_line_number = 0;    // The relative line number of picture line (The part with pixels values)

        int i;

        while (fgets(buffer, BUFFER_SIZE, file) != NULL)
        {
            if(buffer[0] != '#') // This line is not a commentary
            {
                switch(line_number)
                {
                    /**
                     * Checking the PGM Magic number
                     */
                    case 0:
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
                        pgm->width = get_first_int_from_string(buffer);
                        pgm->height = get_second_int_from_string(buffer);

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
                        pgm->v_max = get_first_int_from_string(buffer);
                    break;

                    /**
                     * All other line which are a part of the picture
                     */
                    default:
                        fill_picture_line_from_string(pgm, picture_line_number, buffer);
                        ++picture_line_number;
                    break;
                }
                ++line_number;
            }
        }
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
    // 
    char* str_pgm = malloc((HEADER_PGM_SIZE * sizeof(char))   // Space for the header
        + ((8 * width * height) + height) * sizeof(char));    // Space for pixels (8 for maximal int size + ' ' (7+1)) (+height for each '\n')

    char str_number[NUMBER_MAX_SIZE];   // A string which contain a number, used to collect the pixel value

    sprintf(str_pgm, "P2\n%d %d\n%d\n", width, height, pgm->v_max); // Add the headers values into the string

    /**
     * For each pixels
     */
    int i, j;
    for(i = 0; i < height; ++i)
    {
        for(j = 0; j < width; ++j)
        {
            sprintf(str_number, "%d ", pgm->pixels[i][j]);  // Add the pixel value
            strcat(str_pgm, str_number);
        }
        strcat(str_pgm, "\n");
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
 * @brief      Gets the first int from string.
 *             Read all character one by one
 *             Create a number with it
 *             Will stop when a character is not
 *             a number
 *
 * @param      buffer  The buffer
 *
 * @return     The first int from string.
 */
int get_first_int_from_string(char* buffer)
{
    char str_int[MAX_CHAR_PER_LINE];    // A string which contain the number
    char char_readed;                   // The actually character readed
    int i = 0;                          // Index of the whole line ( buffer )
    int index_str_int = 0;              // Index of the string which contain the number
    
    /**
     * Read the buffer character per character
     */
    do
    {
        char_readed = buffer[i];
        if(char_readed >= '0' && char_readed <= '9')    // If the char is a number 
        {
            str_int[index_str_int] = char_readed;       // Add the number at the end of str_int
            ++index_str_int;                            // Adjust the index 
        }
        else if(is_separator(char_readed) == TRUE)      // If the char is a separator
        {
            str_int[index_str_int] = '\0';              // Add the EndLine character at the end of str_int
        }                                               // And it will mark the end of the loop
        else
        {
            printf("ERROR getting integer from string: %d\n", ERR_IMAGE_FILE_IS_INCORRECT);
            exit(ERR_IMAGE_FILE_IS_INCORRECT);
        }
        ++i;                                            // Move the character readed by one place
    }while(is_separator(char_readed) == FALSE);

    return atoi(str_int);   // Return the number as a integer
}

/**
 * @brief      Gets the second int from string.
 *             Work exactly as the same as get_first_int_from_string
 *             But first we pass the first number
 *
 * @param      buffer  The buffer
 *
 * @return     The second int from string.
 */
int get_second_int_from_string(char* buffer)
{
    char str_int[MAX_CHAR_PER_LINE];
    char char_readed;
    int i = 0;
    int index_str_int = 0;

    /**
     * Pass first
     */
    while(buffer[i] != ' ')
    {
        ++i;
    }
    ++i;

    do
    {
        char_readed = buffer[i];
        if(char_readed >= '0' && char_readed <= '9')
        {
            str_int[index_str_int] = char_readed;
            ++index_str_int;
        }
        else if(is_separator(char_readed) == TRUE)
        {
            str_int[index_str_int] = '\0';
        }
        else
        {
            printf("ERROR getting height : %d\n", ERR_IMAGE_FILE_IS_INCORRECT);
            exit(ERR_IMAGE_FILE_IS_INCORRECT);
        }
        ++i;
    }while(is_separator(char_readed) == FALSE);

    return atoi(str_int);
}

/**
 * @brief      fill a line in the pixels array of a PGM_P2_image from a string who contain the pixels value
 *             Read each character. For each number separate by a separator.
 *             Add this number into the 2D array of the PGM_P2_image
 *
 * @param      pgm           The pgm
 * @param[in]  picture_line  The picture line
 * @param      buffer        A line who contain all the pixel value 
 */
void fill_picture_line_from_string(PGM_P2_image* pgm, int picture_line, char* buffer)
{
    int i, j = 0;
    char str_int[MAX_CHAR_PER_LINE];    // A string which contain the pixel value
    int index_str_int;                  // Index of str_int
    char char_readed;

    /**
     * Foreach pixel to add
     */
    for(i = 0; i < pgm->width; ++i)
    {
        /**
         * Read into the buffer until it find a number
         */
        index_str_int = 0; // Go to the begin of the pixel value buffer
        do
        {
            char_readed = buffer[j];

            if(char_readed >= '0' && char_readed <= '9')    // If the char read is a number
            {
                str_int[index_str_int] = char_readed;       // We add it into the str_int
                ++index_str_int;                            // Adjust the index
                ++j;                                        // Go to the next char into the buffer 
            }
            else if(is_separator(char_readed) == TRUE)      // If the char is a separator
            {
                str_int[index_str_int] = '\0';              // We add the EndLine character at the end of str_int
            }                                               // And it will ending the loop
            else
            {
                printf("ERROR getting character \'%d\' : %d\n", char_readed, ERR_IMAGE_FILE_IS_INCORRECT);
                exit(ERR_IMAGE_FILE_IS_INCORRECT);
            }
            
        }while(is_separator(char_readed) == FALSE);

        while(is_separator(buffer[++j]) == TRUE);       // Here we read until the new pixel value for pass all the useless separators


        int pixel_value = atoi(str_int);                // Transform the string into an integer

        if(pixel_value > pgm->v_max || pixel_value < 0 )// Check if the pixel value if correct
        {
            printf("ERROR pixel_value > v_max : %d\n", ERR_PIXEL_VALUE_INCORECT);
            exit(ERR_PIXEL_VALUE_INCORECT);
        }

        pgm->pixels[picture_line][i] = pixel_value;     // Add the pixel value into the pixel array
    }
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
    if(char_readed == ' ' || char_readed == '\n' || char_readed == '\t' || char_readed == 'EOF' || char_readed == 'LF' || char_readed == 0)
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