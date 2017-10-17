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
    FILE* output = get_file("img/reversed.pgm", "w");

    PGM_P2_image* pgm = PGM_P2_get_image_from_file(file);

    //display_PGM_P2_image(pgm);
    
    PGM_P2_image* reversed = PGM_P2_reversed_filter(pgm);

    PGM_P2_save_image_into_file(reversed, output);

    display_PGM_P2_image(reversed);

    free_PGM_P2_image(pgm);
    free_PGM_P2_image(reversed);

    fclose(file);
    fclose(output);
    return 0;
}