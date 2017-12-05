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
