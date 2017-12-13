/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "console_interface.h"

/**
 * @brief      Shows the logo.
 */
void show_logo(void)
{
    puts("\t+---------------------------------------+");
    puts("\t|              IMAGE TOOLS              |");
    puts("\t|                 v.0.5                 |");
    puts("\t+---------------------------------------+");
}

/**
 * @brief      Main menu function
 *             Usefull to select which kind of image 
 *             will be manipulate
 */ 
void main_menu(void)
{
    e__bool is_end = FALSE;
    char action;
    do
    {
        jump_clear();
        show_logo();
        puts("\t| [MAIN] .............................. |");
        puts("\t+---------------------------------------+");
        puts("\t| b. BMP image ........................ |");
        puts("\t| p. PGM P2 image ..................... |");
        puts("\t| q. Quit program ..................... |");
        puts("\t+---------------------------------------+");
        printf("\t: ");
        action = get_action();
        puts("");

        switch(action)
        {
            case 'b':
            case 'B':
                bmp_menu();
            break;

            case 'p':
            case 'P':
                pgm_p2_menu();
            break;

            case 'q':
            case 'Q':
                puts("Closing program");
                is_end = TRUE;
            break;

            default:
                printf("Command [%c] doesn't exist !\n", action);
            break;
        }

    }while(is_end == FALSE);
}

/**
 * @brief      Gets the action.
 *             It's a scanf function to get a char   
 * 
 * @return     The action.
 */
char get_action(void)
{
    // char action;
    // scanf("%[^\n]%*c", &action);

    char    action;
    int     scanf_return;
    int     c;
    e__bool number_ok = FALSE;

    do
    {
        scanf_return = scanf("%c%*[^\n]", &action);

        if(!scanf_return) // ERROR input
        {
            while ( ((c = getchar()) != '\n') && c != EOF); // Clear
            printf("\tIncorrect input, please enter an integer : ");
        }
        else // VALID input
        {
            getchar(); // Remove the '\n'
            number_ok = 1;
        }
    }while (number_ok == FALSE);

    return action;
}

/**
 * @brief      Gets the number.
 *             it's a scanf function to get a integer
 *
 * @return     The number.
 */
int get_number(void)
{
    // int nb;
    // scanf("%d", &nb);
    // scanf("%*[^\n]");
    // getchar();

    int     nb;
    int     scanf_return;
    int     c;
    e__bool number_ok = FALSE;

    do
    {
        scanf_return = scanf("%d%*[^\n]", &nb);

        if(!scanf_return) // ERROR input
        {
            while ( ((c = getchar()) != '\n') && c != EOF); // Clear
            printf("\tIncorrect input, please enter an integer : ");
        }
        else // VALID input
        {
            getchar(); // Remove the '\n'
            number_ok = 1;
        }
    }while (number_ok == FALSE);

    return nb;
}

/**
 * @brief      The BMP window
 */
void bmp_menu(void)
{
    e__bool is_end = FALSE;
    char action;

    int nb_dot = NB_DOT;
    int i, j;
    int depth_fir;
    int size, value;    // Usefull for Matrix

    char file_path[256] = "";
    char save_path[256] = "";
    FILE *in = NULL;
    FILE *out = NULL;
    BMP_image *bmp = NULL;
    Matrix* kernel = NULL;

    do
    {
        jump_clear();
        show_logo();
        puts("\t| [MAIN] > [BMP] ...................... |");
        printf("\t| FILE : [%s] ", file_path); for(i = 0; i < nb_dot; ++i){printf(".");} puts(" |");
        puts("\t+---------------------------------------+");
        puts("\t| l. Load BMP ......................... |");
        puts("\t| s. Save BMP ......................... |");
        puts("\t| q. Quit BMP ......................... |");
        puts("\t+---------------------------------------+");
        puts("\t| i. Informations BMP ................. |");
        puts("\t| j. Show bmp Histogram ............... |");
        puts("\t| k. Save bmp Histogram ............... |");
        puts("\t+---------------------------------------+");
        puts("\t| g. Gray filter ...................... |");
        puts("\t| r. Reversed filter .................. |");
        puts("\t| h. Horizontal reversed .............. |");
        puts("\t| v. Vertical reversed ................ |");
        puts("\t| e. Equalized histogram .............. |");
        puts("\t| f. FIR filters ...................... |");
        puts("\t+---------------------------------------+");
        printf("\t: ");
        action = get_action();
        puts("");

        switch(action)
        {
            case 'l':
            case 'L':
                printf("\t FILE PATH : ");
                scanf("%[^\n]%*c", file_path);
                printf("\t> Openning %s...\n", file_path);
                in = get_file(file_path, "rb");
                if(in == NULL)
                {
                    printf("\t> Openning [%s] failed !", file_path);
                    strcpy(file_path, "");
                }
                else
                {
                    printf("\t> Openning [%s] succesfull !\n", file_path);

                    if(bmp != NULL) // BMP is already loaded
                    {
                        free_BMP_image(bmp);
                    }

                    bmp = BMP_get_image_from_file(in);
                    puts("\t> Creating manipulated structure ...");
                    if(bmp != NULL)
                    {
                        puts("\t> Creating manipulated structure succesfull !");
                        nb_dot = NB_DOT - strlen(file_path);
                        /* Couper au milieur les caractères en trop */
                        if(nb_dot < 0)
                            nb_dot = 0;
                    }
                    else
                    {
                        puts("\t> Creating manipulated structure failed !");
                        printf("\t> Closing file [%s] ...", file_path);
                        strcpy(file_path, "");
                    }
                    fclose(in);
                }
            break;

            case 's':
            case 'S':
                if(bmp != NULL)
                {
                    printf("\tSAVE FILE PATH : ");
                    scanf("%[^\n]%*c", save_path);
                    printf("\t> Openning %s...\n", save_path);
                    out = get_file(save_path, "wb");
                    if(out == NULL)
                    {
                        printf("\t> Openning [%s] failed !", save_path);
                        strcpy(save_path, "");
                    }
                    else
                    {
                        printf("\t> Openning [%s] succesfull !\n", save_path);
                        BMP_save_image_into_file(bmp, out);
                        fclose(out);
                        printf("\t> [%s] saved into [%s] successfull !\n", file_path, save_path);
                    }
                }
                else
                {
                    puts("\t> ERROR any BMP_image is load !");
                }
            break;

            case 'q':
            case 'Q':
                puts("Closing program");
                is_end = TRUE;

                if(bmp != NULL)
                {
                    free_BMP_image(bmp);
                }
            break;

            case 'i':
            case 'I':
                if(bmp != NULL)
                {
                    printf("\t> FILE NAME           : %s\n", file_path);
                    printf("\t> Size (width:height) : (%d : %d)\n", bmp->width, bmp->height);

                    BMP_show_header(bmp);
                }
                else
                {
                    puts("\t> ERROR any BMP_image is load !");
                }
            break;

            case 'j':
            case 'J':
                if(bmp != NULL)
                {
                    BMP_histogram* hist = NULL;
                    puts("\t> Loading histogram ...");
                    hist = BMP_get_histogram(bmp, INTENSITY);

                    if(hist != NULL)
                    {
                        puts("\t> Loading histogram successful");
                        // display_BMP_histogram(hist);
                    }
                    else
                    {
                        puts("\t> ERROR Getting histogram !");
                    }
                }
                else
                {
                    puts("\t> ERROR any bmp_image is load !");
                }
            break;

            case 'k':
            case 'K':
                if(bmp != NULL)
                {
                    BMP_histogram* hist = NULL;
                    puts("\t> Loading histogram ...");
                    hist = BMP_get_histogram(bmp, INTENSITY);

                    if(hist != NULL)
                    {
                        puts("\t> Loading histogram successful");

                        printf("\tSAVE HISTOGRAM FILE PATH : ");
                        scanf("%[^\n]%*c", save_path);
                        printf("\t> Openning %s...\n", save_path);
                        out = get_file(save_path, "wb");
                        if(out == NULL)
                        {
                            printf("\t> Openning [%s] failed !", save_path);
                            strcpy(save_path, "");
                        }
                        else
                        {
                            printf("\t> Openning [%s] succesfull !\n", save_path);
                            BMP_save_histogram_as_BMP_file(hist, out);
                            fclose(out);
                            printf("\t> [%s] saved into [%s] successfull !\n", file_path, save_path);
                        }
                        free_BMP_histogram(hist);
                    }
                    else
                    {
                        puts("\t> ERROR Getting histogram !");
                    }
                }
                else
                {
                    puts("\t> ERROR any bmp_image is load !");
                }
            break;

            case 'g':
            case 'G':
                if(bmp != NULL)
                {
                    BMP_set_gray_filter(bmp);
                    puts("\t> Gray filter setted");
                }
                else
                {
                    puts("\t> ERROR any BMP_image is load !");
                }
            break;

            case 'r':
            case 'R':
            if(bmp != NULL)
                {
                    BMP_set_reversed_filter(bmp);
                    puts("\t> Reversed filter setted");
                }
                else
                {
                    puts("\t> ERROR any BMP_image is load !");
                }
            break;

            case 'h':
            case 'H':
                if(bmp != NULL)
                {
                    BMP_set_horizontal_reversed(bmp);
                    puts("\t> Horizontal reversed setted");
                }
                else
                {
                    puts("\t> ERROR any BMP_image is load !");
                }
            break;

            case 'v':
            case 'V':
                if(bmp != NULL)
                {
                    BMP_set_vertical_reversed(bmp);
                    puts("\t> Vertical reversed setted");
                }
                else
                {
                    puts("\t> ERROR any BMP_image is load !");
                }
            break;

            case 'e':
            case 'E':
                if(bmp != NULL)
                {
                    BMP_set_equalize_histogram(bmp);
                    puts("\t> Histogram of the bmp is equalized");
                }
                else
                {
                    puts("\t> ERROR any BMP_image is load !");
                }
            break;

            case 'f':
            case 'F':
                if(bmp != NULL)
                {
                    jump_clear();
                    show_logo();
                    puts("\t| [MAIN] > [BMP] > [FIR] .............. |");
                    printf("\t| FILE : [%s] ", file_path); for(i = 0; i < nb_dot; ++i){printf(".");} puts(" |");
                    puts("\t+---------------------------------------+");
                    puts("\t| q. Quit bmp ......................... |");
                    puts("\t+---------------------------------------+");
                    puts("\t| h. FIR 1D Horinzontal ............... |");
                    puts("\t| v. FIR 1D Vertical .................. |");
                    puts("\t| x. FIR 2D Border x .................. |");
                    puts("\t| y. FIR 2D Border y .................. |");
                    puts("\t| s. Sobel filter ..................... |");
                    puts("\t| m. Matrix convolution ............... |");
                    puts("\t+---------------------------------------+");
                    printf("\t: ");

                    action = get_action();

                    switch(action)
                    {
                        case 'h':
                        case 'H':
                            puts("\tFIR 1D Horizontal filter selected");
                            printf("\tDEPTH : ");
                            depth_fir = get_number();

                            if(depth_fir < 0)
                                depth_fir = 0;
                            if(depth_fir > bmp->width)
                                depth_fir = bmp->width;

                            BMP_set_FIR_1D_horizontal_filter_with_depth(bmp, depth_fir);
                            printf("\t> FIR 1D Horizontal filter setted with %d deeply\n", depth_fir);
                        break;

                        case 'v':
                        case 'V':
                            puts("\tFIR 1D Vertical filter selected");
                            printf("\tDEPTH : ");
                            depth_fir = get_number();

                            if(depth_fir < 0)
                                depth_fir = 0;
                            if(depth_fir > bmp->height)
                                depth_fir = bmp->height;

                            BMP_set_FIR_1D_vertical_filter_with_depth(bmp, depth_fir);
                            printf("\t> FIR 1D Vertical filter setted with %d deeply\n", depth_fir);
                        break;

                        case 'x':
                        case 'X':
                            BMP_set_FIR_2D_border_filter_x(bmp);
                            puts("\t> FIR 2D Border filter X setted");
                        break;

                        case 'y':
                        case 'Y':
                            BMP_set_FIR_2D_border_filter_y(bmp);
                            puts("\t> FIR 2D Border filter Y setted");
                        break;

                        case 's':
                        case 'S':
                            BMP_set_sobel_filter(bmp);
                            puts("\t> Sobel filter setted");
                        break;

                        case 'm':
                        case 'M':
                            do
                            {
                                printf("\tMatrix size ( size should be bigger than 0 and odd) : ");
                                size = get_number();
                            }while(size <= 0 || size % 2 == 0);
                            
                            kernel = create_Matrix(size, size);
                            display_Matrix(kernel);

                            // Fill the matrix
                            for(i = 0; i < size; ++i)
                            {
                                for(j = 0; j < size; ++j)
                                {
                                    printf("\n\t(%d:%d) : ", j, i);
                                    value = get_number();
                                    set_value_into_Matrix(kernel, j, i, value);
                                    display_Matrix(kernel);
                                }
                            }

                            BMP_convolution_with_Matrix(bmp, kernel);

                            puts("\n\t>Matrix convolution setted");

                            free_Matrix(kernel);
                        break;

                        default:
                            puts("Closing FIR");
                        break;
                    }
                }
                else
                {
                    puts("\t> ERROR any BMP_image is load !");
                }
            break;

            default:
                printf("Command [%c] doesn't exist !\n", action);
            break;
        }
    }while(is_end == FALSE);
}

/**
 * @brief      The PGM window
 */
void pgm_p2_menu(void)
{
    e__bool is_end = FALSE;
    char action;

    int nb_dot = NB_DOT;
    int i, j;
    int depth_fir;
    int size, value;    // Usefull for Matrix

    char file_path[256] = "";
    char save_path[256] = "";
    FILE *in = NULL;
    FILE *out = NULL;
    PGM_P2_image *pgm = NULL;
    Matrix* kernel = NULL;

    do
    {
        jump_clear();
        show_logo();
        puts("\t| [MAIN] > [PGM] ...................... |");
        printf("\t| FILE : [%s] ", file_path); for(i = 0; i < nb_dot; ++i){printf(".");} puts(" |");
        puts("\t+---------------------------------------+");
        puts("\t| l. Load PGM ......................... |");
        puts("\t| s. Save PGM ......................... |");
        puts("\t| q. Quit PGM ......................... |");
        puts("\t+---------------------------------------+");
        puts("\t| i. Informations PGM ................. |");
        puts("\t| j. Show PGM Histogram ............... |");
        puts("\t| k. Save PGM Histogram ............... |");
        puts("\t+---------------------------------------+");
        puts("\t| r. Reversed filter .................. |");
        puts("\t| h. Horizontal reversed .............. |");
        puts("\t| v. Vertical reversed ................ |");
        puts("\t| v. Vertical reversed ................ |");
        puts("\t| f. FIR filters ...................... |");
        puts("\t+---------------------------------------+");
        printf("\t: ");
        action = get_action();
        puts("");

        switch(action)
        {
            case 'l':
            case 'L':
                printf("\t FILE PATH : ");
                scanf("%[^\n]%*c", file_path);
                printf("\t> Openning %s...\n", file_path);
                in = get_file(file_path, "rb");
                if(in == NULL)
                {
                    printf("\t> Openning [%s] failed !", file_path);
                    strcpy(file_path, "");
                }
                else
                {
                    printf("\t> Openning [%s] succesfull !\n", file_path);

                    if(pgm != NULL) // pgm is already loaded
                    {
                        free_PGM_P2_image(pgm);
                    }

                    pgm = PGM_P2_get_image_from_file(in);
                    puts("\t> Creating manipulated structure ...");
                    if(pgm != NULL)
                    {
                        puts("\t> Creating manipulated structure succesfull !");
                        nb_dot = NB_DOT - strlen(file_path);
                        /* Couper au milieur les caractères en trop */
                        if(nb_dot < 0)
                            nb_dot = 0;
                    }
                    else
                    {
                        puts("\t> Creating manipulated structure failed !");
                        printf("\t> Closing file [%s] ...", file_path);
                        strcpy(file_path, "");
                    }
                    fclose(in);
                }
            break;

            case 's':
            case 'S':
                if(pgm != NULL)
                {
                    printf("\tSAVE FILE PATH : ");
                    scanf("%[^\n]%*c", save_path);
                    printf("\t> Openning %s...\n", save_path);
                    out = get_file(save_path, "wb");
                    if(out == NULL)
                    {
                        printf("\t> Openning [%s] failed !", save_path);
                        strcpy(save_path, "");
                    }
                    else
                    {
                        printf("\t> Openning [%s] succesfull !\n", save_path);
                        PGM_P2_save_image_into_file(pgm, out);
                        fclose(out);
                        printf("\t> [%s] saved into [%s] successfull !\n", file_path, save_path);
                    }
                }
                else
                {
                    puts("\t> ERROR any PGM_image is load !");
                }
            break;

            case 'q':
            case 'Q':
                puts("Closing program");
                is_end = TRUE;

                if(pgm != NULL)
                {
                    free_PGM_P2_image(pgm);
                }
            break;

            case 'i':
            case 'I':
                if(pgm != NULL)
                {
                    printf("\t> FILE NAME           : %s\n", file_path);
                    printf("\t> Size (width:height) : (%d : %d)\n", pgm->width, pgm->height);
                    printf("\t> Max value_comp()    : %d\n", pgm->v_max);
                }
                else
                {
                    puts("\t> ERROR any PGM_image is load !");
                }
            break;

            case 'j':
            case 'J':
                if(pgm != NULL)
                {
                    PGM_P2_histogram* hist = NULL;
                    puts("\t> Loading histogram ...");
                    hist = PGM_P2_get_histogram(pgm);

                    if(hist != NULL)
                    {
                        puts("\t> Loading histogram successful");
                        display_PGM_P2_histogram(hist);
                    }
                    else
                    {
                        puts("\t> ERROR Getting histogram !");
                    }
                }
                else
                {
                    puts("\t> ERROR any PGM_image is load !");
                }
            break;

            case 'k':
            case 'K':
                if(pgm != NULL)
                {
                    PGM_P2_histogram* hist = NULL;
                    puts("\t> Loading histogram ...");
                    hist = PGM_P2_get_histogram(pgm);

                    if(hist != NULL)
                    {
                        puts("\t> Loading histogram successful");

                        printf("\tSAVE HISTOGRAM FILE PATH : ");
                        scanf("%[^\n]%*c", save_path);
                        printf("\t> Openning %s...\n", save_path);
                        out = get_file(save_path, "wb");
                        if(out == NULL)
                        {
                            printf("\t> Openning [%s] failed !", save_path);
                            strcpy(save_path, "");
                        }
                        else
                        {
                            printf("\t> Openning [%s] succesfull !\n", save_path);
                            PGM_P2_save_histogram_as_PGM_P2_file(hist, out);
                            fclose(out);
                            printf("\t> [%s] saved into [%s] successfull !\n", file_path, save_path);
                        }
                        free_PGM_P2_histogram(hist);
                    }
                    else
                    {
                        puts("\t> ERROR Getting histogram !");
                    }
                }
                else
                {
                    puts("\t> ERROR any pgm_image is load !");
                }
            break;

            case 'r':
            case 'R':
                if(pgm != NULL)
                {
                    PGM_P2_set_reversed_filter(pgm);
                    puts("\t> Reversed filter setted");
                }
                else
                {
                    puts("\t> ERROR any PGM_image is load !");
                }
            break;

            case 'h':
            case 'H':
                if(pgm != NULL)
                {
                    PGM_P2_set_horizontal_reversed(pgm);
                    puts("\t> Horizontal reversed setted");
                }
                else
                {
                    puts("\t> ERROR any PGM_image is load !");
                }
            break;

            case 'v':
            case 'V':
                if(pgm != NULL)
                {
                    PGM_P2_set_vertical_reversed(pgm);
                    puts("\t> Vertical reversed setted");
                }
                else
                {
                    puts("\t> ERROR any PGM_image is load !");
                }
            break;

            case 'f':
            case 'F':
                if(pgm != NULL)
                {
                    jump_clear();
                    show_logo();
                    puts("\t| [MAIN] > [PGM] > [FIR] .............. |");
                    printf("\t| FILE : [%s] ", file_path); for(i = 0; i < nb_dot; ++i){printf(".");} puts(" |");
                    puts("\t+---------------------------------------+");
                    puts("\t| q. Quit FIR ......................... |");
                    puts("\t+---------------------------------------+");
                    puts("\t| h. FIR 1D Horinzontal ............... |");
                    puts("\t| v. FIR 1D Vertical .................. |");
                    puts("\t| x. FIR 2D Border x .................. |");
                    puts("\t| y. FIR 2D Border y .................. |");
                    puts("\t| s. Sobel filter ..................... |");
                    puts("\t| m. Matrix convolution ............... |");
                    puts("\t+---------------------------------------+");
                    printf("\t: ");

                    action = get_action();

                    switch(action)
                    {
                        case 'h':
                        case 'H':
                            puts("\tFIR 1D Horizontal filter selected");
                            printf("\tDEPTH : ");
                            depth_fir = get_number();

                            if(depth_fir < 0)
                                depth_fir = 0;
                            if(depth_fir > pgm->width)
                                depth_fir = pgm->width;

                            PGM_P2_set_FIR_1D_horizontal_filter_with_depth(pgm, depth_fir);
                            printf("\t> FIR 1D Horizontal filter setted with %d deeply\n", depth_fir);
                        break;

                        case 'v':
                        case 'V':
                            puts("\tFIR 1D Vertical filter selected");
                            printf("\tDEPTH : ");
                            depth_fir = get_number();

                            if(depth_fir < 0)
                                depth_fir = 0;
                            if(depth_fir > pgm->height)
                                depth_fir = pgm->height;

                            PGM_P2_set_FIR_1D_vertical_filter_with_depth(pgm, depth_fir);
                            printf("\t> FIR 1D Vertical filter setted with %d deeply\n", depth_fir);
                        break;

                        case 'x':
                        case 'X':
                            PGM_P2_set_FIR_2D_border_filter_x(pgm);
                            puts("\t> FIR 2D Border filter X setted");
                        break;

                        case 'y':
                        case 'Y':
                            PGM_P2_set_FIR_2D_border_filter_y(pgm);
                            puts("\t> FIR 2D Border filter Y setted");
                        break;

                        case 's':
                        case 'S':
                            PGM_P2_set_sobel_filter(pgm);
                            puts("\t> Sobel filter setted");
                        break;

                        case 'm':
                        case 'M':
                            do
                            {
                                printf("\tMatrix size ( size should be bigger than 0 and odd) : ");
                                size = get_number();
                            }while(size <= 0 || size % 2 == 0);
                            
                            kernel = create_Matrix(size, size);
                            display_Matrix(kernel);

                            // Fill the matrix
                            for(i = 0; i < size; ++i)
                            {
                                for(j = 0; j < size; ++j)
                                {
                                    printf("\n\t(%d:%d) : ", j, i);
                                    value = get_number();
                                    set_value_into_Matrix(kernel, j, i, value);
                                    display_Matrix(kernel);
                                }
                            }

                            PGM_P2_convolution_with_Matrix(pgm, kernel);

                            puts("\n\t>Matrix convolution setted");

                            free_Matrix(kernel);
                        break;

                        default:
                            puts("Closing FIR");
                        break;
                    }
                }
                else
                {
                    puts("\t> ERROR any PGM_image is load !");
                }
            break;

            default:
                printf("Command [%c] doesn't exist !\n", action);
            break;
        }
    }while(is_end == FALSE);
}

/**
 * @brief      Display a jump
 *             To clear the window
 */
void jump_clear(void)
{
    int i;
    for(i = 0; i < JUMP; ++i)
        puts("");
}