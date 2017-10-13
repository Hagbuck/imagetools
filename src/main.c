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
    FILE* output = get_file("img/out.pgm", "w");

    PGM_image* pgm = PGM_get_image_from_file(file);

    display_PGM_image(pgm);

    PGM_save_image_into_file(pgm, output);

    free_PGM_image(pgm);

    fclose(file);
    fclose(output);
    return 0;
}