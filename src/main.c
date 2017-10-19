/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include <stdio.h>
#include <stdlib.h>

#include "basic_tools.h"
#include "PGM_P2.h"

#define LENA            "img/lena.ascii.pgm"
#define LENA_REV        "img/lena.ascii_reversed.pgm"
#define LENA_HIST       "img/lena.ascii_histogram.pgm"
#define LENA_HIST_REV   "img/lena.ascii_reversed_histogram.pgm"
#define FEEP            "img/feep.pgm"
#define FEEP_REV        "img/feep_reversed.pgm"
#define FEEP_HIST       "img/feep_histogram.pgm"
#define FEEP_HIST_REV   "img/feep_reversed_histogram.pgm"

int main(int argc, char *argv[])
{
    FILE* file = get_file(LENA, "r");
    FILE* out_reversed = get_file(LENA_REV, "w");
    FILE* out_histo = get_file(LENA_HIST, "w");
    FILE* out_histo_reversed = get_file(LENA_HIST_REV, "w");

    puts("LOAD");
    PGM_P2_image* pgm = PGM_P2_get_image_from_file(file);

    puts("GET HISTO");
    PGM_P2_histogram* hist_pgm = PGM_P2_get_histogram(pgm);

    puts("SAVE HISTO");
    PGM_P2_save_histogram_as_PGM_P2_file(hist_pgm, out_histo);

    puts("REVERSED");
    PGM_P2_image* pgm_reversed = PGM_P2_reversed_filter(pgm);

    puts("SAVE REVERSED");
    PGM_P2_save_image_into_file(pgm_reversed, out_reversed);

    puts("GET HISTO REVERSED");
    PGM_P2_histogram* hist_reversed_pgm = PGM_P2_get_histogram(pgm_reversed);

    puts("SAVE HISTO REVERSED");
    PGM_P2_save_histogram_as_PGM_P2_file(hist_reversed_pgm, out_histo_reversed);

    free_PGM_P2_image(pgm);
    free_PGM_P2_image(pgm_reversed);
    free_PGM_P2_histogram(hist_pgm);
    free_PGM_P2_histogram(hist_reversed_pgm);

    fclose(file);
    fclose(out_reversed);
    fclose(out_histo);
    fclose(out_histo_reversed);
    return 0;
}