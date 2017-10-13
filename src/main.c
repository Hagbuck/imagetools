/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include <stdio.h>
#include <stdlib.h>

#include "basic_tools.h"
#include "PGM.h"

int main(int argc, char *argv[])
{
    FILE* file = get_file("img/test.pgm", "r");

    PGM_image* pgm = PGM_get_image_from_file(file);

    display_PGM_image(pgm);

    free_PGM_image(pgm);

    fclose(file);
    return 0;
}