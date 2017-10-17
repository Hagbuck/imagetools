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
 * 
 * To Do :
 * - Manipulate the PGM_P2_image
 * - Save the PGM_P2_image on a hard drive
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic_tools.h"

#define BUFFER_SIZE         200
#define MAX_CHAR_PER_LINE   70
#define FILE_MAX_SIZE       4096
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

int                 get_first_int_from_string(char* buffer);
int                 get_second_int_from_string(char* buffer);

void                fill_picture_line_from_string(PGM_P2_image* pgm, int picture_line, char* buffer);

e__bool             is_separator(char char_readed);

void                free_PGM_P2_image(PGM_P2_image* pgm);
void                free_PGM_P2_histogram(PGM_P2_histogram* histogram);
void                display_PGM_P2_image(PGM_P2_image* pgm);
void                display_PGM_P2_histogram(PGM_P2_histogram* histogram);

#endif