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
    SDL_Texture*    text;
    SDL_Rect        dest;
};

// Windows
int             main_window(int argc, char** argv);

// Basic SDL tools
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