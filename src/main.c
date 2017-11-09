/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include <stdio.h>
#include <stdlib.h>

#include "basic_tools.h"
#include "PGM_P2.h"
#include "BMP.h"

#define LENA            "img/lena.ascii.pgm"
#define LENA_REV        "img/lena.ascii_reversed.pgm"
#define LENA_COPY       "img/lena.ascii_copy.pgm"
#define LENA_HIST       "img/lena.ascii_histogram.pgm"
#define LENA_HIST_REV   "img/lena.ascii_reversed_histogram.pgm"

#define FEEP            "img/feep.pgm"
#define FEEP_REV        "img/feep_reversed.pgm"
#define FEEP_COPY       "img/feep_copy.pgm"
#define FEEP_HIST       "img/feep_histogram.pgm"
#define FEEP_HIST_REV   "img/feep_reversed_histogram.pgm"

#define MARIO           "img/mario.bmp"
#define MARIO_REV       "img/mario_reversed.bmp"
#define MARIO_COPY      "img/mario_copy.bmp"
#define MARIO_GRAY      "img/mario_gray.bmp"
#define MARIO_H_REV     "img/mario_horizontal_reversed.bmp"
#define MARIO_V_REV     "img/mario_vertical_reversed.bmp"

int main(int argc, char *argv[])
{
    // FILE* file = get_file(FEEP, "r");
    // FILE* out_copy = get_file(FEEP_COPY, "w");
    // FILE* out_reversed = get_file(FEEP_REV, "w");
    // FILE* out_histo = get_file(FEEP_HIST, "w");
    // FILE* out_histo_reversed = get_file(FEEP_HIST_REV, "w");

    // puts("LOAD");
    // PGM_P2_image* pgm = PGM_P2_get_image_from_file(file);

    // puts("SAVE COPY");
    // PGM_P2_save_image_into_file(pgm, out_copy);
    
    // puts("GET HISTO");
    // PGM_P2_histogram* hist_pgm = PGM_P2_get_histogram(pgm);

    // puts("SAVE HISTO");
    // PGM_P2_save_histogram_as_PGM_P2_file(hist_pgm, out_histo);

    // puts("REVERSED");
    // PGM_P2_image* pgm_reversed = PGM_P2_reversed_filter(pgm);

    // puts("SAVE REVERSED");
    // PGM_P2_save_image_into_file(pgm_reversed, out_reversed);

    // puts("GET HISTO REVERSED");
    // PGM_P2_histogram* hist_reversed_pgm = PGM_P2_get_histogram(pgm_reversed);

    // puts("SAVE HISTO REVERSED");
    // PGM_P2_save_histogram_as_PGM_P2_file(hist_reversed_pgm, out_histo_reversed);

    // free_PGM_P2_image(pgm);
    // free_PGM_P2_image(pgm_reversed);
    // free_PGM_P2_histogram(hist_pgm);
    // free_PGM_P2_histogram(hist_reversed_pgm);

    // fclose(file);
    // fclose(out_copy);
    // fclose(out_reversed);
    // fclose(out_histo);
    // fclose(out_histo_reversed);
    

    FILE* file = get_file(MARIO, "rb");
    FILE* out = get_file(MARIO_V_REV, "wb");

    BMP_image* bmp = BMP_get_image_from_file(file);
    BMP_image* copy = BMP_get_copy(bmp);

    if(copy == NULL)
        puts("NULL");

    BMP_set_vertical_reversed(copy);

    // BMP_show_header(bmp);

    // printf("> %d:%d\n", bmp->width, bmp->height); 
    
    BMP_save_image_into_file(copy, out);
    
    free_BMP_image(bmp);
    free_BMP_image(copy);
    
    fclose(file);
    fclose(out);

    return 0;
}




