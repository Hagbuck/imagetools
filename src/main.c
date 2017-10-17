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
    FILE* output = get_file("img/histogram.pgm", "w");

    PGM_P2_image* pgm = PGM_P2_get_image_from_file(file);
    PGM_P2_histogram* hist_pgm = PGM_P2_get_histogram(pgm);
    PGM_P2_image* histo = PGM_P2_get_PGM_P2_image_from_PGM_P2_histogram(hist_pgm);
    
    // display_PGM_P2_histogram(hist_pgm);

    // PGM_P2_save_histogram_as_PGM_P2_file(hist_pgm, output);
    PGM_P2_save_image_into_file(histo, output);

    // display_PGM_P2_image(histo);

    free_PGM_P2_image(pgm);
    free_PGM_P2_image(histo);
    free_PGM_P2_histogram(hist_pgm);

    fclose(file);
    fclose(output);
    return 0;
}