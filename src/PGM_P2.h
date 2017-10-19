/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#ifndef IMAGE_TOOLS_PGM_P2_H
#define IMAGE_TOOLS_PGM_P2_H

/**
 * Thoses functions and structure are used to get modify and save a PGM.
 * 
 * Actually features :
 * - Get a PGM_P2_image from a file
 * - Save the PGM_P2_image on a hard drive
 * - Get a copy of a PGM_P2 with a reversed filter
 * - Get the histogram of an image
 * - Save a Histogram as a PGM picture
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic_tools.h"

#define BUFFER_SIZE         2048
#define MAX_CHAR_PER_LINE   70
#define FILE_MAX_SIZE       4096
#define HEADER_PGM_SIZE     81 /* P2\n(3digits) + 70(width+height, max size for a line : 70) + 8 (7digits max + \n)*/
#define NUMBER_MAX_SIZE     7

typedef struct PGM_P2_image PGM_P2_image;
struct PGM_P2_image
{
    int     height;
    int     width;
    int     v_max;
    int**   pixels;
};

typedef struct PGM_P2_histogram PGM_P2_histogram;
struct PGM_P2_histogram
{
    int*    intensity_value;
    int     size;
};


PGM_P2_image*       PGM_P2_get_image_from_file(FILE* file);
PGM_P2_image*       PGM_P2_reversed_filter(PGM_P2_image *img);
PGM_P2_histogram*   PGM_P2_get_histogram(PGM_P2_image *img);
e__bool             PGM_P2_save_image_into_file(PGM_P2_image* pgm, FILE* file);
e__bool             PGM_P2_save_histogram_as_PGM_P2_file(PGM_P2_histogram* histogram, FILE* file);

PGM_P2_image*       PGM_P2_get_copy(PGM_P2_image* img);
PGM_P2_image*       PGM_P2_get_PGM_P2_image_from_PGM_P2_histogram(PGM_P2_histogram* histogram);

e__bool             is_separator(char char_readed);

void                free_PGM_P2_image(PGM_P2_image* pgm);
void                free_PGM_P2_histogram(PGM_P2_histogram* histogram);
void                display_PGM_P2_image(PGM_P2_image* pgm);
void                display_PGM_P2_histogram(PGM_P2_histogram* histogram);

#endif