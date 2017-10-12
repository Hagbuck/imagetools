/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "basic_tools.h"

struct PGM_image
{

    int hauteur;
    int largeur;
    int v_max;


};

PGM_image PGM_read_image(FILE * file);
