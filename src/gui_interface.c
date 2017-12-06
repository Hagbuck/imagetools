/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "gui_interface.h"

int main_window(int argc, char** argv)
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

void load_BMP(SDL_Window* const window, SDL_Renderer* const renderer)
{
    char file_path[256] = "";
    FILE* file = NULL;
    BMP_image* bmp = NULL;

    printf("\t FILE PATH : ");
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

            BMP_window(window, renderer, bmp, file_path);
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

void BMP_window(SDL_Window* const window, SDL_Renderer* const renderer, BMP_image* bmp, char* const file_path)
{
    e__bool is_end = FALSE;
    int     i, j;

    char*   hud_button_clicked = NULL;
    int     mouse_x, mouse_y;
    e__bool mouse_down = FALSE;

    Btn_list* btn = create_HUD_Btn_list(renderer);

    int hud_width = btn->button[0].dest.w + 16*2;
    int hud_height = 16;
    int picture_y_offset = 0;

    int time_a = 0;

    for(i = 0; i < btn->size; ++i)
        hud_height += btn->button[i].dest.h + 16;

    if(bmp->height > hud_height)        // HUD smaller than the picture
    {
        SDL_SetWindowSize(window, bmp->width + hud_width + 16, bmp->height);
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
                printf("%d UP\n", event.key.keysym.sym);
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_end = TRUE;
                }
            break;

            case SDL_MOUSEBUTTONDOWN:
                puts("clicked");
                if(mouse_down == FALSE)
                {
                    hud_button_clicked = get_button_name_hunder_mouse_into_Btn_list(btn, mouse_x, mouse_y);
                    if(hud_button_clicked != NULL)
                    {
                        printf("> %s\n", hud_button_clicked);
                        if(strcmp(hud_button_clicked, "gray") == 0)
                            BMP_set_gray_filter(bmp);
                        else if(strcmp(hud_button_clicked, "reversed") == 0)
                            BMP_set_reversed_filter(bmp);
                        else if(strcmp(hud_button_clicked, "h-rotated") == 0)
                            BMP_set_horizontal_reversed(bmp);
                        else if(strcmp(hud_button_clicked, "v-rotated") == 0)
                            BMP_set_vertical_reversed(bmp);
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

void load_PGM(SDL_Window* const window, SDL_Renderer* const renderer)
{
    char file_path[256] = "";
    FILE* file = NULL;
    PGM_P2_image* pgm = NULL;

    printf("\t FILE PATH : ");
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
            PGM_window(window, renderer, pgm, file_path);
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

void PGM_window(SDL_Window* const window, SDL_Renderer* const renderer, PGM_P2_image* pgm, char* const file_path)
{
    e__bool is_end = FALSE;
    int     i, j;

    int     mouse_x, mouse_y;
    int     pixel_value;

    SDL_SetWindowSize(window, pgm->width, pgm->height);

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

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    is_end = TRUE;
                }
            break;
        }

        SDL_RenderClear(renderer);

        for(i = 0; i < pgm->height; ++i)
        {
            for(j = 0; j < pgm->width; ++j)
            {
                pixel_value = (pgm->pixels[i][j] * 255 / pgm->v_max);
                SDL_SetRenderDrawColor(renderer, pixel_value, pixel_value, pixel_value, 255);
                SDL_RenderDrawPoint(renderer, j, i);
            }
        }
        SDL_RenderPresent(renderer);
    }
    free_PGM_P2_image(pgm);
}

Btn_list* create_HUD_Btn_list(SDL_Renderer* const renderer)
{
    Btn_list* btn = malloc(sizeof(Btn_list));

    btn->size = 4;

    btn->name = malloc(btn->size * sizeof(char*));
    btn->name[0] = malloc(strlen("gray") * sizeof(char));
    strcpy(btn->name[0], "gray");
    btn->name[1] = malloc(strlen("reversed") * sizeof(char));
    strcpy(btn->name[1], "reversed");
    btn->name[2] = malloc(strlen("h-rotated") * sizeof(char));
    strcpy(btn->name[2], "h-rotated");
    btn->name[3] = malloc(strlen("v-rotated") * sizeof(char));
    strcpy(btn->name[3], "v-rotated");

    btn->button = malloc(btn->size * sizeof(GEntity));

    loadGEntity(&btn->button[0], renderer, "rc/gray_button.png");
    GEntity_set_pos(&btn->button[0], 16, 16);

    loadGEntity(&btn->button[1], renderer, "rc/reversed_button.png");
    GEntity_set_pos(&btn->button[1], btn->button[0].dest.x, btn->button[0].dest.y + btn->button[0].dest.h + 16);

    loadGEntity(&btn->button[2], renderer, "rc/horizontal_rotate.png");
    GEntity_set_pos(&btn->button[2], btn->button[1].dest.x, btn->button[1].dest.y + btn->button[1].dest.h + 16);

    loadGEntity(&btn->button[3], renderer, "rc/vertical_rotate.png");
    GEntity_set_pos(&btn->button[3], btn->button[2].dest.x, btn->button[2].dest.y + btn->button[2].dest.h + 16);

    btn->hover = malloc(btn->size * sizeof(GEntity));

    loadGEntity(&btn->hover[0], renderer, "rc/gray_button_hover.png");
    GEntity_set_pos(&btn->hover[0], btn->button[0].dest.x, btn->button[0].dest.y);

    loadGEntity(&btn->hover[1], renderer, "rc/reversed_button_hover.png");
    GEntity_set_pos(&btn->hover[1], btn->button[1].dest.x, btn->button[1].dest.y);

    loadGEntity(&btn->hover[2], renderer, "rc/horizontal_rotate_hover.png");
    GEntity_set_pos(&btn->hover[2], btn->button[2].dest.x, btn->button[2].dest.y);

    loadGEntity(&btn->hover[3], renderer, "rc/vertical_rotate_hover.png");
    GEntity_set_pos(&btn->hover[3], btn->button[3].dest.x, btn->button[3].dest.y);

    return btn;
}

GWindow* create_HUD(void)
{
    GWindow* hud = malloc(sizeof(GWindow));

    hud->window = create_SDL_Window("ToolsBox", 1, 1);
    hud->renderer = create_SDL_Renderer(hud->window);

    hud->button_list = create_HUD_Btn_list(hud->renderer);

    SDL_SetWindowSize(hud->window, 3*16 + 2*hud->button_list->button[0].dest.w, 3*16 + 2*hud->button_list->button[0].dest.h);

    return hud;
}

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

void draw_GWindow(GWindow* const window, int mouse_x, int mouse_y)
{
    if(window != NULL)
    {
        SDL_SetRenderDrawColor(window->renderer, 30,30,30,255);
        //TODO : color bg
        SDL_RenderClear(window->renderer);
        int i;
        for(i = 0; i < window->button_list->size; ++i)
        {
            if(SDL_GetMouseFocus() == window->window
            && testCollider(mouse_x, mouse_y, window->button_list->button[i].dest) == TRUE)
                    SDL_RenderCopy(window->renderer, window->button_list->hover[i].text, NULL, &window->button_list->hover[i].dest);                
            else
                SDL_RenderCopy(window->renderer, window->button_list->button[i].text, NULL, &window->button_list->button[i].dest);
        }
        SDL_RenderPresent(window->renderer);
    }
}

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

char* get_button_name_hunder_mouse_into_GWindow(GWindow* const window, int mouse_x, int mouse_y)
{
    if(window != NULL)
    {
        if(SDL_GetMouseFocus() == window->window)
        {
            int i;
            for(i = 0; i < window->button_list->size; ++i)
            {
                if(testCollider(mouse_x, mouse_y, window->button_list->button[i].dest) == TRUE)
                    return window->button_list->name[i];
            }
        }
    }
    return NULL;
}

void free_GWindow(GWindow* const window)
{
    if(window != NULL)
    {
        free_Btn_list(window->button_list);
        // SDL_DestroyRenderer(window->renderer);
        SDL_DestroyWindow(window->window);

        free(window);
    }
}

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

void loadGEntity(GEntity* const entity, SDL_Renderer* renderer, char* const address)
{
    entity->text = loadTexture(renderer, address);
    SDL_QueryTexture(entity->text, NULL, NULL, &entity->dest.w, &entity->dest.h); // Capt the size of the texture
}

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

SDL_Texture* loadTextureWithDest(SDL_Renderer* renderer, char* const address, SDL_Rect *dest)
{
    SDL_Texture *text = loadTexture(renderer, address);
    SDL_QueryTexture(text, NULL, NULL, &dest->w, &dest->h);     // Capt the size of the texture
    return text;
}

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

void GEntity_set_pos(GEntity* const entity, int x, int y)
{
    entity->dest.x = x;
    entity->dest.y = y;
}

void GEntity_set_x(GEntity* const entity, int x)
{
    entity->dest.x = x;
}

void GEntity_set_y(GEntity* const entity, int y)
{
    entity->dest.y = y;
}

void GEntity_center_x(GEntity* const entity, int win_width)
{
    entity->dest.x = win_width / 2 - entity->dest.w / 2;
}

void GEntity_center_y(GEntity* const entity, int win_height)
{
    entity->dest.y = win_height / 2 - entity->dest.h / 2;
}

void GEntity_center(GEntity* const entity, int win_width, int win_height)
{
    GEntity_center_x(entity, win_width);
    GEntity_center_y(entity, win_height);
}