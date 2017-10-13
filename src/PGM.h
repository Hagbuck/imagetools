/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#ifndef IMAGE_TOOLS_PGM_H
#define IMAGE_TOOLS_PGM_H

#include "basic_tools.h"

typedef struct PGM_image PGM_image;
struct PGM_image
{
    int hauteur;
    int largeur;
    int v_max;
};

PGM_image PGM_read_image(FILE * file);

#endif