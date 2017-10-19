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
    FILE* file = get_file("img/lena.ascii.pgm", "r");
    // FILE* out_copy = get_file("img/lena_copy.pgm", "w");
    FILE* out_reversed = get_file("img/lena_reversed.pgm", "w");
    FILE* out_histo = get_file("img/lena_histogram.pgm", "w");

    puts("LOAD");
    PGM_P2_image* pgm = PGM_P2_get_image_from_file(file);
    // display_PGM_P2_image(pgm);
    // PGM_P2_save_image_into_file(pgm, out_copy);

    puts("GET HISTO");
    PGM_P2_histogram* hist_pgm = PGM_P2_get_histogram(pgm);

    puts("SAVE HISTO");
    PGM_P2_save_histogram_as_PGM_P2_file(hist_pgm, out_histo);

    puts("REVERSED");
    PGM_P2_image* pgm_reversed = PGM_P2_reversed_filter(pgm);

    puts("SAVE REVERSED");
    PGM_P2_save_image_into_file(pgm_reversed, out_reversed);


    free_PGM_P2_image(pgm);
    free_PGM_P2_image(pgm_reversed);
    free_PGM_P2_histogram(hist_pgm);

    fclose(file);
    // fclose(out_copy);
    fclose(out_reversed);
    fclose(out_histo);
    return 0;
}