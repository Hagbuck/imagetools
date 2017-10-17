/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include <stdio.h>
#include <stdlib.h>

#include "basic_tools.h"
#include "PGM_P2.h"

int main(int argc, char *argv[])
{
    FILE* file = get_file("img/test.pgm", "r");
    FILE* output = get_file("img/copy.pgm", "w");

    PGM_P2_image* pgm = PGM_P2_get_image_from_file(file);

    //display_PGM_P2_image(pgm);
    
    PGM_P2_image* copy = PGM_P2_get_copy(pgm);

    PGM_P2_save_image_into_file(copy, output);

    free_PGM_P2_image(pgm);

    fclose(file);
    fclose(output);
    return 0;
}