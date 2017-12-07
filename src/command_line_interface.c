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

    int depth;

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
            ++i;
            if(i < argc)
            {
                depth = get_int_from_str(argv[i]);
                if(bmp != NULL)
                    BMP_set_FIR_1D_horizontal_filter_with_depth(bmp, depth);
                if(pgm != NULL)
                    PGM_P2_set_FIR_1D_horizontal_filter_with_depth(pgm, depth);
            }
        }
        else if(strcmp(argv[i], "--fir1d-v") == 0)
        {
            ++i;
            if(i < argc)
            {
                depth = get_int_from_str(argv[i]);
                if(bmp != NULL)
                    BMP_set_FIR_1D_vertical_filter_with_depth(bmp, depth);
                if(pgm != NULL)
                    PGM_P2_set_FIR_1D_vertical_filter_with_depth(pgm, depth);
            }
        }
        else if(strcmp(argv[i], "--fir2d-x") == 0)
        {
            if(bmp != NULL)
                BMP_set_FIR_2D_border_filter_x(bmp);
            if(pgm != NULL)
                PGM_P2_set_FIR_2D_border_filter_x(pgm);
        }
        else if(strcmp(argv[i], "--fir2d-y") == 0)
        {
            if(bmp != NULL)
                BMP_set_FIR_2D_border_filter_y(bmp);
            if(pgm != NULL)
                PGM_P2_set_FIR_2D_border_filter_y(pgm);
        }
        else if(strcmp(argv[i], "--sobel") == 0)
        {
            if(bmp != NULL)
                BMP_set_sobel_filter(bmp);
            if(pgm != NULL)
                PGM_P2_set_sobel_filter(pgm);
        }
        /*else if(strcmp(argv[i], "--equalize-hist") == 0)
        {
            if(bmp != NULL)
                BMP_set_equalize_histogram(bmp);
            if(pgm != NULL)
                PGM_P2_set_equalize_histogram(pgm);
        }*/

        /**
         * GETTING HISTOGRAM
         */
        else if(strcmp(argv[i], "--histogram") == 0)
        {
            ++i;
            if(i < argc)
            {
                if(bmp != NULL)
                {
                    BMP_histogram* bmp_hist = NULL;
                    e__bool all_components = FALSE;

                    if(strcmp(argv[i], "r") == 0)
                        bmp_hist = BMP_get_histogram(bmp, RED);
                    else if(strcmp(argv[i], "g") == 0)
                        bmp_hist = BMP_get_histogram(bmp, GREEN);
                    else if(strcmp(argv[i], "b") == 0)
                        bmp_hist = BMP_get_histogram(bmp, BLUE);
                    else if(strcmp(argv[i], "i") == 0)
                        bmp_hist = BMP_get_histogram(bmp, INTENSITY);
                    else if(strcmp(argv[i], "c") == 0)
                    {
                        bmp_hist = BMP_get_histogram(bmp, INTENSITY);
                        all_components = TRUE;
                    }
                    else    // ERROR PARAMETER GO BACK
                    {
                        bmp_hist = BMP_get_histogram(bmp, INTENSITY);
                        --i;
                    }
                    
                    ++i;
                    if(i < argc)
                    {
                        file = get_file(argv[i], "wb");
                        if(all_components == TRUE)
                        {
                            BMP_histogram* red = BMP_get_histogram(bmp, RED);
                            BMP_histogram* green = BMP_get_histogram(bmp, GREEN);
                            BMP_histogram* blue = BMP_get_histogram(bmp, BLUE);

                            BMP_image* hist_components = BMP_get_BMP_image_from_all_BMP_histogram(bmp_hist, red, green, blue);
                            BMP_save_image_into_file(hist_components, file);

                            free_BMP_image(hist_components);
                            free_BMP_histogram(red);
                            free_BMP_histogram(green);
                            free_BMP_histogram(blue);
                        }
                        else
                            BMP_save_histogram_as_BMP_file(bmp_hist, file);
                        fclose(file);
                        free_BMP_histogram(bmp_hist);
                    }
                    else
                    {
                        --i; // GO BACK;
                        puts("ERROR any file path sended...");
                    }
                }
                if(pgm != NULL)
                {
                    PGM_P2_histogram* pgm_hist = NULL;

                    if(strcmp(argv[i], "r") == 0
                    || strcmp(argv[i], "g") == 0
                    || strcmp(argv[i], "b") == 0
                    || strcmp(argv[i], "i") == 0
                    || strcmp(argv[i], "c") == 0
                    )
                        pgm_hist = PGM_P2_get_histogram(pgm);
                    else    // ERROR PARAMETER GO BACK
                    {
                        pgm_hist = PGM_P2_get_histogram(pgm);
                        --i;
                    }
                    
                    ++i;
                    if(i < argc)
                    {
                        file = get_file(argv[i], "wb");
                        PGM_P2_save_histogram_as_PGM_P2_file(pgm_hist, file);
                        fclose(file);
                        free_PGM_P2_histogram(pgm_hist);
                    }
                    else
                    {
                        --i; // GO BACK;
                        puts("ERROR any file path sended...");
                    }
                }
            }
            else
            {
                --i; // GO BACK
            }
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
                --i; // GO BACK;
                puts("ERROR any file path sended...");
            }
        }
    }

    free_PGM_P2_image(pgm);
    free_BMP_image(bmp);
}