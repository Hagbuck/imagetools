/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "console_interface.h"

void show_logo(void)
{
    puts("\t+---------------------------------------+");
    puts("\t|              IMAGE TOOLS              |");
    puts("\t|                 v.0.3                 |");
    puts("\t+---------------------------------------+");
}

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
        puts("\t| b. PGM P2 image ..................... |");
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

char get_action(void)
{
    char action;
    scanf("%[^\n]%*c", &action);
    return action;
}

void bmp_menu(void)
{
    e__bool is_end = FALSE;
    char action;

    char file_path[256] = "";
    char save_path[256] = "";
    FILE *in = NULL;
    FILE *out = NULL;
    BMP_image *bmp = NULL;

    do
    {
        jump_clear();
        show_logo();
        puts("\t| [MAIN] > [BMP] ...................... |");
        printf("\t| FILE : [%s]\n", file_path);
        puts("\t+---------------------------------------+");
        puts("\t| l. Load BMP ......................... |");
        puts("\t| s. Save BMP ......................... |");
        puts("\t| q. Quit BMP ......................... |");
        puts("\t+---------------------------------------+");
        puts("\t| g. Gray filter ...................... |");
        puts("\t| r. Reversed filter .................. |");
        puts("\t| h. Horizontal reversed .............. |");
        puts("\t| v. Vertical reversed ................ |");
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
                    bmp = BMP_get_image_from_file(in);
                    puts("\t> Creating manipulated structure ...");
                    if(bmp != NULL)
                    {
                        puts("\t> Creating manipulated structure succesfull !");
                    }
                    else
                    {
                        puts("\t> Creating manipulated structure failed !");
                        printf("\t> Closing file [%s] ...", file_path);
                        strcpy(file_path, "");
                        fclose(in);
                    }
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
                    if(in == NULL)
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
                if(in != NULL)
                {
                    fclose(in);
                }
                if(bmp != NULL)
                {
                    free_BMP_image(bmp);
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

            default:
                printf("Command [%c] doesn't exist !\n", action);
            break;
        }
    }while(is_end == FALSE);
}

void jump_clear(void)
{
    int i;
    for(i = 0; i < JUMP; ++i)
        puts("");
}