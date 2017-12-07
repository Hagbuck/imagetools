/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#ifndef IMAGE_TOOLS_GUI_INTERFACE_H
#define IMAGE_TOOLS_GUI_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "basic_tools.h"
#include "PGM_P2.h"
#include "BMP.h"
#include "Matrix.h"

#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   512

typedef struct GEntity GEntity;
struct GEntity
{
    SDL_Texture*    text;   // The entity's texture
    SDL_Rect        dest;   // The dest box of the entity
};

typedef struct Btn_list Btn_list;
struct Btn_list
{
    char**          name;       // Contain all button name
    GEntity*        button;     // Contain all button
    GEntity*        hover;      // Contain all hover button
    int             size;       // Number of button
};

// Windows
int             main_window(int argc, char** argv);
void            load_BMP(SDL_Window* const window, SDL_Renderer* const renderer);
void            save_BMP(BMP_image* const bmp);
void            BMP_window(SDL_Window* const window, SDL_Renderer* const renderer, BMP_image* bmp, char* const file_path);
void            load_PGM(SDL_Window* const window, SDL_Renderer* const renderer);
void            PGM_window(SDL_Window* const window, SDL_Renderer* const renderer, PGM_P2_image* pgm, char* const file_path);
Btn_list*       create_HUD_Btn_list(SDL_Renderer* const renderer);
void            draw_Btn_list(Btn_list* const btn, SDL_Renderer* const renderer, int mouse_x, int mouse_y);
char*           get_button_name_hunder_mouse_into_Btn_list(Btn_list* const btn, int mouse_x, int mouse_y);
void            free_Btn_list(Btn_list* const btn);


// Basic SDL tools
void            init_SDL(void);
SDL_Window*     create_SDL_Window(char* const win_title, int win_width, int win_height);
SDL_Renderer*   create_SDL_Renderer(SDL_Window* window);
void            loadGEntity(GEntity* const entity, SDL_Renderer* renderer, char* const address);
SDL_Texture*    loadTexture(SDL_Renderer* renderer, char* const address);
SDL_Texture*    loadTextureWithDest(SDL_Renderer* renderer, char* const address, SDL_Rect *dest);
e__bool         testCollider(int x, int y, SDL_Rect r);

//GEntity
void            GEntity_set_pos(GEntity* const entity, int x, int y);
void            GEntity_set_x(GEntity* const entity, int x);
void            GEntity_set_y(GEntity* const entity, int y);
void            GEntity_center_x(GEntity* const entity, int win_width);
void            GEntity_center_y(GEntity* const entity, int win_height);
void            GEntity_center(GEntity* const entity, int win_width, int win_height);

#endif