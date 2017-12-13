/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "gui_interface.h"

/**
 * @brief      Main window of the gui interface
 *
 * @return     exit return
 */
int main_window(void)
{
    init_SDL();
    SDL_Window* window = create_SDL_Window("Imagetools v0.5", WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_Renderer* renderer = create_SDL_Renderer(window);
    e__bool is_end = FALSE;

    int mouse_x, mouse_y;

    GEntity lena_bg;
    GEntity open_bmp;
    GEntity open_bmp_hover;
    GEntity open_pgm;
    GEntity open_pgm_hover;

    // Loading and set position of images
    loadGEntity(&lena_bg, renderer, "rc/lena_bg.bmp");
    GEntity_set_pos(&lena_bg, 0, 0);

    loadGEntity(&open_bmp, renderer, "rc/open_bmp.png");
    GEntity_center_x(&open_bmp, WINDOW_WIDTH);
    GEntity_set_y(&open_bmp, open_bmp.dest.h);

    loadGEntity(&open_bmp_hover, renderer, "rc/open_bmp_hover.png");
    GEntity_center_x(&open_bmp_hover, WINDOW_WIDTH);
    GEntity_set_y(&open_bmp_hover, open_bmp_hover.dest.h);

    loadGEntity(&open_pgm, renderer, "rc/open_pgm.png");
    GEntity_center_x(&open_pgm, WINDOW_WIDTH);
    GEntity_set_y(&open_pgm, open_bmp.dest.y + open_bmp.dest.h * 2);

    loadGEntity(&open_pgm_hover, renderer, "rc/open_pgm_hover.png");
    GEntity_center_x(&open_pgm_hover, WINDOW_WIDTH);
    GEntity_set_y(&open_pgm_hover, open_bmp_hover.dest.y + open_bmp_hover.dest.h * 2);


    // Main loop
    SDL_Event event;
    while (is_end == FALSE)
    {
        SDL_WaitEvent(&event);                  // Get user event
        SDL_GetMouseState(&mouse_x, &mouse_y);  // Get mouse position
        switch(event.type)
        {
            case SDL_QUIT:
                is_end = TRUE;
            break;

            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_end = TRUE;
                }
            break;
            
            case SDL_MOUSEBUTTONUP:
                if(testCollider(mouse_x, mouse_y, open_bmp.dest) == TRUE)
                {
                    load_BMP(window, renderer);
                    SDL_SetWindowSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);   
                }
                else if(testCollider(mouse_x, mouse_y, open_pgm.dest) == TRUE)
                {
                    load_PGM(window, renderer);
                    SDL_SetWindowSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);   
                }
            break;
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, lena_bg.text, NULL, &lena_bg.dest);                    // Draw background picture

        if(testCollider(mouse_x, mouse_y, open_bmp.dest) == TRUE)                       // If the mouse is hovering BMP button
            SDL_RenderCopy(renderer, open_bmp_hover.text, NULL, &open_bmp_hover.dest);  // Show hover button
        else                                                                            // Otherwise
            SDL_RenderCopy(renderer, open_bmp.text, NULL, &open_bmp.dest);              // Show classic button

        if(testCollider(mouse_x, mouse_y, open_pgm.dest) == TRUE)                       // If the mouse is hovering PGM button
            SDL_RenderCopy(renderer, open_pgm_hover.text, NULL, &open_pgm_hover.dest);  // Show hover button
        else                                                                            // Otherwise
            SDL_RenderCopy(renderer, open_pgm.text, NULL, &open_pgm.dest);              // Show classic button

        SDL_RenderPresent(renderer);
    }
    
    
    SDL_DestroyTexture(lena_bg.text);
    SDL_DestroyTexture(open_bmp.text);
    SDL_DestroyTexture(open_bmp_hover.text);
    SDL_DestroyTexture(open_pgm.text);
    SDL_DestroyTexture(open_pgm_hover.text);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

/**
 * @brief      Temporary function to get and load a BMP from the 
 *             terminal
 *
 * @param      window    The window
 * @param      renderer  The renderer
 */
void load_BMP(SDL_Window* const window, SDL_Renderer* const renderer)
{
    char file_path[256] = "";
    FILE* file = NULL;
    BMP_image* bmp = NULL;

    printf("\n\t FILE PATH : ");
    scanf("%[^\n]%*c", file_path);
    printf("\t> Openning %s...\n", file_path);
    file = get_file(file_path, "rb");
    if(file == NULL)
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

        bmp = BMP_get_image_from_file(file);
        puts("\t> Creating manipulated structure ...");
        if(bmp != NULL)
        {
            puts("\t> Creating manipulated structure succesfull !");

            BMP_window(window, renderer, bmp);
        }
        else
        {
            puts("\t> Creating manipulated structure failed !");
            printf("\t> Closing file [%s] ...", file_path);
            strcpy(file_path, "");
        }
        fclose(file);
    }
}

/**
 * @brief      Temporary function to save a BMP from the 
 *             terminal
 *
 * @param      bmp   The bitmap
 */
void save_BMP(BMP_image* const bmp)
{
    char file_path[256] = "";
    FILE* file = NULL;

    if(bmp != NULL)
    {
        printf("\n\tSAVE FILE PATH : ");
        scanf("%[^\n]%*c", file_path);
        printf("\t> Openning %s...\n", file_path);
        file = get_file(file_path, "wb");
        if(file == NULL)
        {
            printf("\t> Openning [%s] failed !", file_path);
            strcpy(file_path, "");
        }
        else
        {
            printf("\t> Openning [%s] succesfull !\n", file_path);
            BMP_save_image_into_file(bmp, file);
            fclose(file);
            printf("\t> Saved into [%s] successfull !\n", file_path);
        }
    }
    else
    {
        puts("\t> ERROR any BMP_image is load !");
    }
}

/**
 * @brief      The BMP management window
 *
 * @param      window     The window
 * @param      renderer   The renderer
 * @param      bmp        The bitmap
 */
void BMP_window(SDL_Window* const window, SDL_Renderer* const renderer, BMP_image* bmp)
{
    e__bool is_end = FALSE;
    int     i, j;

    char*   hud_button_clicked = NULL;
    int     mouse_x, mouse_y;
    e__bool mouse_down = FALSE;

    Btn_list* btn = create_HUD_Btn_list(renderer);

    int hud_width = btn->button[0].dest.w + btn->button[5].dest.w + btn->button[10].dest.w + 16*4;
    int hud_height = 16;
    int picture_y_offset = 0;

    int time_a = 0;

    for(i = 0; i < NB_BUTTON_IN_COL; ++i)
        hud_height += btn->button[i].dest.h + 16;

    if(bmp->height > hud_height)        // HUD smaller than the picture
    {
        SDL_SetWindowSize(window, bmp->width + hud_width + 16, bmp->height + 16*2);
        picture_y_offset = 16;
    }
    else                                // HUD bigger than the picture
    {
        SDL_SetWindowSize(window, bmp->width + hud_width + 16, hud_height);
        picture_y_offset = (hud_height - bmp->height) / 2;
    }

    SDL_Event event;
    while (is_end == FALSE)
    {
        SDL_WaitEvent(&event);                  // Get user event
        SDL_GetMouseState(&mouse_x, &mouse_y);  // Get mouse position
        switch(event.type)
        {
            case SDL_QUIT:
                is_end = TRUE;
            break;

            case SDL_KEYUP:
                // printf("%d UP\n", event.key.keysym.sym);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_end = TRUE;
                }
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(mouse_down == FALSE)
                {
                    hud_button_clicked = get_button_name_hunder_mouse_into_Btn_list(btn, mouse_x, mouse_y);
                    if(hud_button_clicked != NULL)
                    {
                        printf("> %s\n", hud_button_clicked);
                        if(strcmp(hud_button_clicked, "save") == 0)
                            save_BMP(bmp);
                        else if(strcmp(hud_button_clicked, "gray") == 0)
                            BMP_set_gray_filter(bmp);
                        else if(strcmp(hud_button_clicked, "reversed") == 0)
                            BMP_set_reversed_filter(bmp);
                        else if(strcmp(hud_button_clicked, "h-rotated") == 0)
                            BMP_set_horizontal_reversed(bmp);
                        else if(strcmp(hud_button_clicked, "v-rotated") == 0)
                            BMP_set_vertical_reversed(bmp);
                        else if(strcmp(hud_button_clicked, "fir1d-h") == 0)
                            BMP_set_FIR_1D_horizontal_filter_with_depth(bmp, 1);
                        else if(strcmp(hud_button_clicked, "fir1d-v") == 0)
                            BMP_set_FIR_1D_vertical_filter_with_depth(bmp, 1);
                        else if(strcmp(hud_button_clicked, "fir2d-x") == 0)
                            BMP_set_FIR_2D_border_filter_x(bmp);
                        else if(strcmp(hud_button_clicked, "fir2d-y") == 0)
                            BMP_set_FIR_2D_border_filter_y(bmp);
                        else if(strcmp(hud_button_clicked, "sobel") == 0)
                            BMP_set_sobel_filter(bmp);
                        else if(strcmp(hud_button_clicked, "histogram") == 0)
                        {
                            BMP_histogram* hist = BMP_get_histogram(bmp, INTENSITY);

                            BMP_image* hist_bmp = BMP_get_BMP_image_from_BMP_histogram(hist);
                            save_BMP(hist_bmp);

                            free_BMP_image(hist_bmp);
                            free_BMP_histogram(hist);
                        }
                        else if(strcmp(hud_button_clicked, "histogram-color") == 0)
                        {
                            BMP_histogram* hist_i = BMP_get_histogram(bmp, INTENSITY);
                            BMP_histogram* hist_r = BMP_get_histogram(bmp, RED);
                            BMP_histogram* hist_g = BMP_get_histogram(bmp, GREEN);
                            BMP_histogram* hist_b = BMP_get_histogram(bmp, BLUE);

                            BMP_image* hist_color = BMP_get_BMP_image_from_all_BMP_histogram(hist_i, hist_r, hist_g, hist_b);
                            save_BMP(hist_color);

                            free_BMP_image(hist_color);
                            free_BMP_histogram(hist_i);
                            free_BMP_histogram(hist_r);
                            free_BMP_histogram(hist_g);
                            free_BMP_histogram(hist_b);
                        }
                        else if(strcmp(hud_button_clicked, "equalized") == 0)
                        {
                            BMP_set_equalize_histogram(bmp);
                        }
                    }
                }
                mouse_down = TRUE;
            break;

            case SDL_MOUSEBUTTONUP:
                mouse_down = FALSE;
            break;

            case SDL_MOUSEMOTION:
                // printf("(%d:%d)\n", mouse_x, mouse_y);
            break;                
        }

        

        if(SDL_GetTicks() - time_a >= 80)
        {
            SDL_RenderClear(renderer);
            for(i = 0; i < bmp->height; ++i)
            {
                for(j = 0; j < bmp->width; ++j)
                {
                    SDL_SetRenderDrawColor(renderer, bmp->pixels[i][j].r, bmp->pixels[i][j].g, bmp->pixels[i][j].b, 255);
                    SDL_RenderDrawPoint(renderer, j + hud_width, bmp->height - i + picture_y_offset);
                }
            }


            SDL_SetRenderDrawColor(renderer, 30,30,30,255);
            draw_Btn_list(btn, renderer, mouse_x, mouse_y);


            SDL_RenderPresent(renderer);
            time_a = SDL_GetTicks();
            SDL_Delay(20);
        }
    }
    free_BMP_image(bmp);
    free_Btn_list(btn);
}

/**
 * @brief      Temporary function to get and load a PGM from the 
 *             terminal
 *
 * @param      window    The window
 * @param      renderer  The renderer
 */
void load_PGM(SDL_Window* const window, SDL_Renderer* const renderer)
{
    char file_path[256] = "";
    FILE* file = NULL;
    PGM_P2_image* pgm = NULL;

    printf("\n\t FILE PATH : ");
    scanf("%[^\n]%*c", file_path);
    printf("\t> Openning %s...\n", file_path);
    file = get_file(file_path, "rb");
    if(file == NULL)
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

        pgm = PGM_P2_get_image_from_file(file);
        puts("\t> Creating manipulated structure ...");
        if(pgm != NULL)
        {
            puts("\t> Creating manipulated structure succesfull !");
            PGM_window(window, renderer, pgm);
        }
        else
        {
            puts("\t> Creating manipulated structure failed !");
            printf("\t> Closing file [%s] ...", file_path);
            strcpy(file_path, "");
        }
        fclose(file);
    }
}

/**
 * @brief      Temporary function to save a PGM from the 
 *             terminal
 *
 * @param      pgm   The pgm
 */
void save_PGM(PGM_P2_image* const pgm)
{
    char file_path[256] = "";
    FILE* file = NULL;
 
    if(pgm != NULL)
    {
        printf("\tSAVE FILE PATH : ");
        scanf("%[^\n]%*c", file_path);
        printf("\t> Openning %s...\n", file_path);
        file = get_file(file_path, "wb");
        if(file == NULL)
        {
            printf("\t> Openning [%s] failed !", file_path);
            strcpy(file_path, "");
        }
        else
        {
            printf("\t> Openning [%s] succesfull !\n", file_path);
            PGM_P2_save_image_into_file(pgm, file);
            fclose(file);
            printf("\t> [%s] saved into [%s] successfull !\n", file_path, file_path);
        }
    }
    else
    {
        puts("\t> ERROR any PGM_image is load !");
    }
}

/**
 * @brief      The PGM management window
 *
 * @param      window     The window
 * @param      renderer   The renderer
 * @param      pgm        The pgm
 * @param      file_path  The file path
 */
void PGM_window(SDL_Window* const window, SDL_Renderer* const renderer, PGM_P2_image* pgm)
{
    e__bool is_end = FALSE;
    int     i, j;

    char*   hud_button_clicked = NULL;
    int     mouse_x, mouse_y;
    e__bool mouse_down = FALSE;

    Btn_list* btn = create_HUD_Btn_list(renderer);

    int hud_width = btn->button[0].dest.w + btn->button[5].dest.w + btn->button[10].dest.w + 16*4;
    int hud_height = 16;
    int picture_y_offset = 0;
    int pixel_value;    // Int for be sure the calculation will not overflow

    int time_a = 0;

    for(i = 0; i < NB_BUTTON_IN_COL; ++i)
        hud_height += btn->button[i].dest.h + 16;

    if(pgm->height > hud_height)        // HUD smaller than the picture
    {
        SDL_SetWindowSize(window, pgm->width + hud_width + 16, pgm->height + 16*2);
        picture_y_offset = 16;
    }
    else                                // HUD bigger than the picture
    {
        SDL_SetWindowSize(window, pgm->width + hud_width + 16, hud_height);
        picture_y_offset = (hud_height - pgm->height) / 2;
    }

    SDL_Event event;
    while (is_end == FALSE)
    {
        SDL_WaitEvent(&event);                  // Get user event
        SDL_GetMouseState(&mouse_x, &mouse_y);  // Get mouse position
        switch(event.type)
        {
            case SDL_QUIT:
                is_end = TRUE;
            break;

            case SDL_KEYUP:
                // printf("%d UP\n", event.key.keysym.sym);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_end = TRUE;
                }
            break;

            case SDL_MOUSEBUTTONDOWN:
                if(mouse_down == FALSE)
                {
                    hud_button_clicked = get_button_name_hunder_mouse_into_Btn_list(btn, mouse_x, mouse_y);
                    if(hud_button_clicked != NULL)
                    {
                        printf("> %s\n", hud_button_clicked);
                        if(strcmp(hud_button_clicked, "save") == 0)
                            save_PGM(pgm);
                        else if(strcmp(hud_button_clicked, "gray") == 0)
                            puts("No effect");
                        else if(strcmp(hud_button_clicked, "reversed") == 0)
                            PGM_P2_set_reversed_filter(pgm);
                        else if(strcmp(hud_button_clicked, "h-rotated") == 0)
                            PGM_P2_set_horizontal_reversed(pgm);
                        else if(strcmp(hud_button_clicked, "v-rotated") == 0)
                            PGM_P2_set_vertical_reversed(pgm);
                        else if(strcmp(hud_button_clicked, "fir1d-h") == 0)
                            PGM_P2_set_FIR_1D_horizontal_filter_with_depth(pgm, 1);
                        else if(strcmp(hud_button_clicked, "fir1d-v") == 0)
                            PGM_P2_set_FIR_1D_vertical_filter_with_depth(pgm, 1);
                        else if(strcmp(hud_button_clicked, "fir2d-x") == 0)
                            PGM_P2_set_FIR_2D_border_filter_x(pgm);
                        else if(strcmp(hud_button_clicked, "fir2d-y") == 0)
                            PGM_P2_set_FIR_2D_border_filter_y(pgm);
                        else if(strcmp(hud_button_clicked, "sobel") == 0)
                            PGM_P2_set_sobel_filter(pgm);
                        else if(strcmp(hud_button_clicked, "histogram") == 0
                             || strcmp(hud_button_clicked, "histogram-color") == 0)
                        {
                            PGM_P2_histogram* hist = PGM_P2_get_histogram(pgm);
                            PGM_P2_image* hist_pgm = PGM_P2_get_PGM_P2_image_from_PGM_P2_histogram(hist);
                            save_PGM(hist_pgm);

                            free_PGM_P2_image(hist_pgm);
                            free_PGM_P2_histogram(hist);
                        }
                        else if(strcmp(hud_button_clicked, "equalized") == 0)
                        {
                            PGM_P2_set_equalize_histogram(pgm);
                        }
                    }
                }
                mouse_down = TRUE;
            break;

            case SDL_MOUSEBUTTONUP:
                mouse_down = FALSE;
            break;

            case SDL_MOUSEMOTION:
                // printf("(%d:%d)\n", mouse_x, mouse_y);
            break;                
        }

        

        if(SDL_GetTicks() - time_a >= 80)
        {
            SDL_RenderClear(renderer);
            for(i = 0; i < pgm->height; ++i)
            {
                for(j = 0; j < pgm->width; ++j)
                {
                    pixel_value = pgm->pixels[i][j] * 255 / pgm->v_max;
                    SDL_SetRenderDrawColor(renderer, pixel_value, pixel_value, pixel_value, 255);
                    SDL_RenderDrawPoint(renderer, j + hud_width, i + picture_y_offset);
                }
            }


            SDL_SetRenderDrawColor(renderer, 30,30,30,255);
            draw_Btn_list(btn, renderer, mouse_x, mouse_y);


            SDL_RenderPresent(renderer);
            time_a = SDL_GetTicks();
            SDL_Delay(20);
        }
    }
    free_PGM_P2_image(pgm);
    free_Btn_list(btn);
}

/**
 * @brief      Get a list of all button for the HUD
 *
 * @param      renderer  The renderer
 *
 * @return     The button list
 */
Btn_list* create_HUD_Btn_list(SDL_Renderer* const renderer)
{
    Btn_list* btn = malloc(sizeof(Btn_list));

    btn->size = 13;

    btn->name = malloc(btn->size * sizeof(char*));

    btn->name[0] = malloc(strlen("save") * sizeof(char));
    strcpy(btn->name[0], "save");
    btn->name[1] = malloc(strlen("gray") * sizeof(char));
    strcpy(btn->name[1], "gray");
    btn->name[2] = malloc(strlen("reversed") * sizeof(char));
    strcpy(btn->name[2], "reversed");
    btn->name[3] = malloc(strlen("h-rotated") * sizeof(char));
    strcpy(btn->name[3], "h-rotated");
    btn->name[4] = malloc(strlen("v-rotated") * sizeof(char));
    strcpy(btn->name[4], "v-rotated");
    btn->name[5] = malloc(strlen("fir1d-h") * sizeof(char));
    strcpy(btn->name[5], "fir1d-h");
    btn->name[6] = malloc(strlen("fir1d-v") * sizeof(char));
    strcpy(btn->name[6], "fir1d-v");
    btn->name[7] = malloc(strlen("fir2d-x") * sizeof(char));
    strcpy(btn->name[7], "fir2d-x");
    btn->name[8] = malloc(strlen("fir2d-y") * sizeof(char));
    strcpy(btn->name[8], "fir2d-y");
    btn->name[9] = malloc(strlen("sobel") * sizeof(char));
    strcpy(btn->name[9], "sobel");
    btn->name[10] = malloc(strlen("histogram") * sizeof(char));
    strcpy(btn->name[10], "histogram");
    btn->name[11] = malloc(strlen("histogram-color") * sizeof(char));
    strcpy(btn->name[11], "histogram-color");
    btn->name[12] = malloc(strlen("equalized") * sizeof(char));
    strcpy(btn->name[12], "equalized");

    btn->button = malloc(btn->size * sizeof(GEntity));

    loadGEntity(&btn->button[0], renderer, "rc/save_button.png");
    GEntity_set_pos(&btn->button[0], 16, 16);

    loadGEntity(&btn->button[1], renderer, "rc/gray_button.png");
    GEntity_set_pos(&btn->button[1], btn->button[0].dest.x, btn->button[0].dest.y + btn->button[0].dest.h + 16);

    loadGEntity(&btn->button[2], renderer, "rc/reversed_button.png");
    GEntity_set_pos(&btn->button[2], btn->button[1].dest.x, btn->button[1].dest.y + btn->button[1].dest.h + 16);

    loadGEntity(&btn->button[3], renderer, "rc/horizontal_rotate.png");
    GEntity_set_pos(&btn->button[3], btn->button[2].dest.x, btn->button[2].dest.y + btn->button[2].dest.h + 16);

    loadGEntity(&btn->button[4], renderer, "rc/vertical_rotate.png");
    GEntity_set_pos(&btn->button[4], btn->button[3].dest.x, btn->button[3].dest.y + btn->button[3].dest.h + 16);

    /** SECOND COL **/

    loadGEntity(&btn->button[5], renderer, "rc/fir1d_h_button.png");
    GEntity_set_pos(&btn->button[5], btn->button[0].dest.x + btn->button[0].dest.w + 16, btn->button[0].dest.y);

    loadGEntity(&btn->button[6], renderer, "rc/fir1d_v_button.png");
    GEntity_set_pos(&btn->button[6], btn->button[1].dest.x + btn->button[1].dest.w + 16, btn->button[1].dest.y);

    loadGEntity(&btn->button[7], renderer, "rc/fir2d_x_button.png");
    GEntity_set_pos(&btn->button[7], btn->button[2].dest.x + btn->button[2].dest.w + 16, btn->button[2].dest.y);

    loadGEntity(&btn->button[8], renderer, "rc/fir2d_y_button.png");
    GEntity_set_pos(&btn->button[8], btn->button[3].dest.x + btn->button[3].dest.w + 16, btn->button[3].dest.y);

    loadGEntity(&btn->button[9], renderer, "rc/sobel_button.png");
    GEntity_set_pos(&btn->button[9], btn->button[4].dest.x + btn->button[4].dest.w + 16, btn->button[4].dest.y);

    /** THIRD COL **/

    loadGEntity(&btn->button[10], renderer, "rc/histogram_button.png");
    GEntity_set_pos(&btn->button[10], btn->button[5].dest.x + btn->button[5].dest.w + 16, btn->button[0].dest.y);

    loadGEntity(&btn->button[11], renderer, "rc/histogram_color_button.png");
    GEntity_set_pos(&btn->button[11], btn->button[6].dest.x + btn->button[6].dest.w + 16, btn->button[1].dest.y);

    loadGEntity(&btn->button[12], renderer, "rc/equalized_button.png");
    GEntity_set_pos(&btn->button[12], btn->button[7].dest.x + btn->button[7].dest.w + 16, btn->button[7].dest.y);


    btn->hover = malloc(btn->size * sizeof(GEntity));

    loadGEntity(&btn->hover[0], renderer, "rc/save_button_hover.png");
    GEntity_set_pos(&btn->hover[0], btn->button[0].dest.x, btn->button[0].dest.y);

    loadGEntity(&btn->hover[1], renderer, "rc/gray_button_hover.png");
    GEntity_set_pos(&btn->hover[1], btn->button[1].dest.x, btn->button[1].dest.y);

    loadGEntity(&btn->hover[2], renderer, "rc/reversed_button_hover.png");
    GEntity_set_pos(&btn->hover[2], btn->button[2].dest.x, btn->button[2].dest.y);

    loadGEntity(&btn->hover[3], renderer, "rc/horizontal_rotate_hover.png");
    GEntity_set_pos(&btn->hover[3], btn->button[3].dest.x, btn->button[3].dest.y);

    loadGEntity(&btn->hover[4], renderer, "rc/vertical_rotate_hover.png");
    GEntity_set_pos(&btn->hover[4], btn->button[4].dest.x, btn->button[4].dest.y);

    /* SECOND COL HOVER **/

    loadGEntity(&btn->hover[5], renderer, "rc/fir1d_h_button_hover.png");
    GEntity_set_pos(&btn->hover[5], btn->button[5].dest.x, btn->button[5].dest.y);

    loadGEntity(&btn->hover[6], renderer, "rc/fir1d_v_button_hover.png");
    GEntity_set_pos(&btn->hover[6], btn->button[6].dest.x, btn->button[6].dest.y);

    loadGEntity(&btn->hover[7], renderer, "rc/fir2d_x_button_hover.png");
    GEntity_set_pos(&btn->hover[7], btn->button[7].dest.x, btn->button[7].dest.y);

    loadGEntity(&btn->hover[8], renderer, "rc/fir2d_y_button_hover.png");
    GEntity_set_pos(&btn->hover[8], btn->button[8].dest.x, btn->button[8].dest.y);

    loadGEntity(&btn->hover[9], renderer, "rc/sobel_button_hover.png");
    GEntity_set_pos(&btn->hover[9], btn->button[9].dest.x, btn->button[9].dest.y);

    /** THIRD COL HOVER **/

    loadGEntity(&btn->hover[10], renderer, "rc/histogram_button_hover.png");
    GEntity_set_pos(&btn->hover[10], btn->button[10].dest.x, btn->button[10].dest.y);

    loadGEntity(&btn->hover[11], renderer, "rc/histogram_color_button_hover.png");
    GEntity_set_pos(&btn->hover[11], btn->button[11].dest.x, btn->button[11].dest.y);

    loadGEntity(&btn->hover[12], renderer, "rc/equalized_button_hover.png");
    GEntity_set_pos(&btn->hover[12], btn->button[12].dest.x, btn->button[12].dest.y);

    return btn;
}

/**
 * @brief      Draws a button list.
 *
 * @param      btn       The button
 * @param      renderer  The renderer
 * @param[in]  mouse_x   The mouse x
 * @param[in]  mouse_y   The mouse y
 */
void draw_Btn_list(Btn_list* const btn, SDL_Renderer* const renderer, int mouse_x, int mouse_y)
{
    if(btn != NULL)
    {
        int i;
        for(i = 0; i < btn->size; ++i)
        {
            if(testCollider(mouse_x, mouse_y, btn->button[i].dest) == TRUE)
                    SDL_RenderCopy(renderer, btn->hover[i].text, NULL, &btn->hover[i].dest);                
            else
                SDL_RenderCopy(renderer, btn->button[i].text, NULL, &btn->button[i].dest);
        }
    }
}

/**
 * @brief      Gets the button name hunder the mouse
 *
 * @param      btn      The button
 * @param[in]  mouse_x  The mouse x
 * @param[in]  mouse_y  The mouse y
 *
 * @return     The button name hunder the mouse.
 */
char* get_button_name_hunder_mouse_into_Btn_list(Btn_list* const btn, int mouse_x, int mouse_y)
{
    if(btn != NULL)
    {
        int i;
        for(i = 0; i < btn->size; ++i)
        {
            if(testCollider(mouse_x, mouse_y, btn->button[i].dest) == TRUE)
                return btn->name[i];
        }
    }
    return NULL;
}

/**
 * @brief      Free memory of Btn_list
 *
 * @param      btn   The button
 */
void free_Btn_list(Btn_list* const btn)
{
    if(btn != NULL)
    {
        int i;
        for(i = 0; i < btn->size; ++i)
        {
            free(btn->name[i]);
            SDL_DestroyTexture(btn->button[i].text);
            SDL_DestroyTexture(btn->hover[i].text);
        }
        free(btn->name);
        free(btn->button);
        free(btn->hover);

        free(btn);
    }
}

/**
 * @brief      Initialize SDL
 */
void init_SDL(void)
{
    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
}

/**
 * @brief      Creates a sdl window.
 *
 * @param      win_title   The window title
 * @param[in]  win_width   The window width
 * @param[in]  win_height  The window height
 *
 * @return     The window
 */
SDL_Window* create_SDL_Window(char* const win_title, int win_width, int win_height)
{
    // Création de la fenêtre
    SDL_Window* window = SDL_CreateWindow(win_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, SDL_WINDOW_SHOWN);

    if(window == 0)
    {
        printf("Erreur lors de la creation de la fenetre : %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return window;
}

/**
 * @brief      Creates a sdl renderer.
 *
 * @param      window  The window
 *
 * @return     The renderer
 */
SDL_Renderer* create_SDL_Renderer(SDL_Window* window)
{
    // Création du render
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer
    if(renderer == NULL)
    {
        printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    return renderer;
}

/**
 * @brief      Loads a GEntity.
 *
 * @param      entity    The entity
 * @param      renderer  The renderer
 * @param      address   The address
 */
void loadGEntity(GEntity* const entity, SDL_Renderer* renderer, char* const address)
{
    entity->text = loadTexture(renderer, address);
    SDL_QueryTexture(entity->text, NULL, NULL, &entity->dest.w, &entity->dest.h); // Capt the size of the texture
}

/**
 * @brief      Loads a texture.
 *
 * @param      renderer  The renderer
 * @param      address   The address
 *
 * @return     The texture
 */
SDL_Texture* loadTexture(SDL_Renderer* renderer, char* const address)
{
    SDL_Surface* surf = NULL;
    SDL_Texture* text = NULL;

    surf = IMG_Load(address);

    if(!surf)
    {
        printf("ERROR Loading : %s : %s\n", address,  SDL_GetError());
        SDL_Delay(1000);
        exit(EXIT_FAILURE);
    }

    text = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);
    return text;
}

/**
 * @brief      Loads a texture with destination.
 *
 * @param      renderer  The renderer
 * @param      address   The address
 * @param      dest      The destination
 *
 * @return     The texture
 */
SDL_Texture* loadTextureWithDest(SDL_Renderer* renderer, char* const address, SDL_Rect *dest)
{
    SDL_Texture *text = loadTexture(renderer, address);
    SDL_QueryTexture(text, NULL, NULL, &dest->w, &dest->h);     // Capt the size of the texture
    return text;
}

/**
 * @brief      Test collider between a point and a square
 *
 * @param[in]  x     x position of the point
 * @param[in]  y     y position of the point
 * @param[in]  r     the quare (SDL_Rect)
 *
 * @return     TRUE if they collide, otherwise FALSE
 */
e__bool testCollider(int x, int y, SDL_Rect r)
{
    if(x > r.x + r.w    // More at the right
       ||x < r.x        // More at the left
       ||y < r.y        // More at the top
       ||y > r.y + r.h) // More at the down
        return FALSE;
    else
        return TRUE;
}

/**
 * @brief      Set the position of a GEntity
 *
 * @param      entity  The entity
 * @param[in]  x       x position for the entity
 * @param[in]  y       y position for the entity
 */
void GEntity_set_pos(GEntity* const entity, int x, int y)
{
    entity->dest.x = x;
    entity->dest.y = y;
}

/**
 * @brief      Set x position of a GEntity
 *
 * @param      entity  The entity
 * @param[in]  x       the x positon for the entity
 */
void GEntity_set_x(GEntity* const entity, int x)
{
    entity->dest.x = x;
}

/**
 * @brief      Set y position of a GEntity
 *
 * @param      entity  The entity
 * @param[in]  y       the y position for the entity
 */
void GEntity_set_y(GEntity* const entity, int y)
{
    entity->dest.y = y;
}

/**
 * @brief      set the x coordonate of a GEntity at the middle of the width
 *
 * @param      entity     The entity
 * @param[in]  win_width  The window width
 */
void GEntity_center_x(GEntity* const entity, int win_width)
{
    entity->dest.x = win_width / 2 - entity->dest.w / 2;
}

/**
 * @brief      set the y coordonate of a GEntity at the middle of the width
 *
 * @param      entity     The entity
 * @param[in]  win_height The window height
 */
void GEntity_center_y(GEntity* const entity, int win_height)
{
    entity->dest.y = win_height / 2 - entity->dest.h / 2;
}

/**
 * @brief      Set the GEntity coordonate at the middle of the box(window)
 *
 * @param      entity      The entity
 * @param[in]  win_width   The window width
 * @param[in]  win_height  The window height
 */
void GEntity_center(GEntity* const entity, int win_width, int win_height)
{
    GEntity_center_x(entity, win_width);
    GEntity_center_y(entity, win_height);
}