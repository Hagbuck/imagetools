/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "command_line_interface.h"

void cli(int argc, char** argv)
{
    PGM_P2_image* pgm = NULL;
    BMP_image* bmp = NULL;
    FILE* file = NULL;
    int i;
    for(i = 1; i < argc; ++i)
    {
        /**
         * LOADING
         */
        if(strcmp(argv[i], "-p") == 0)
        {
            ++i;
            if(i < argc)
            {
                file = get_file(argv[i], "rb");
                pgm = PGM_P2_get_image_from_file(file);
                fclose(file);
            }
            else
            {
                puts("ERROR any file path sended...");
            }
        }
        else if(strcmp(argv[i], "-b") == 0)
        {
            ++i;
            if(i < argc)
            {
                file = get_file(argv[i], "rb");
                bmp = BMP_get_image_from_file(file);
                fclose(file);
            }
            else
            {
                puts("ERROR any file path sended...");
            }
        }
        /**
         * FILTERING
         */
        else if(strcmp(argv[i], "--gray") == 0)
        {
            if(bmp != NULL)
                BMP_set_gray_filter(bmp);
        }
        else if(strcmp(argv[i], "--reversed") == 0)
        {
            if(bmp != NULL)
                BMP_set_reversed_filter(bmp);
            if(pgm != NULL)
                PGM_P2_set_reversed_filter(pgm);
        }
        else if(strcmp(argv[i], "--h-rotate") == 0)
        {
            if(bmp != NULL)
                BMP_set_horizontal_reversed(bmp);
            if(pgm != NULL)
                PGM_P2_set_horizontal_reversed(pgm);
        }
        else if(strcmp(argv[i], "--v-rotate") == 0)
        {
            if(bmp != NULL)
                BMP_set_vertical_reversed(bmp);
            if(pgm != NULL)
                PGM_P2_set_vertical_reversed(pgm);
        }
        else if(strcmp(argv[i], "--fir1d-h") == 0)
        {
            int depth;
            if(bmp != NULL)
                BMP_set_FIR_1D_horizontal_filter_with_depth(bmp, depth);
            if(pgm != NULL)
                BMP_set_FIR_1D_horizontal_filter_with_depth(pgm, depth);
        }


        /**
         * SAVING
         */
        else if(strcmp(argv[i], "-s") == 0)
        {
            ++i;
            if(i < argc)
            {
                file = get_file(argv[i], "wb");
                if(pgm != NULL)
                    PGM_P2_save_image_into_file(pgm, file);
                else if(bmp != NULL)
                    BMP_save_image_into_file(bmp, file);
                fclose(file);
            }
            else
            {
                puts("ERROR any file path sended...");
            }
        }
    }

    free_PGM_P2_image(pgm);
    free_BMP_image(bmp);
}