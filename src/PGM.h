/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#ifndef IMAGE_TOOLS_PGM_H
#define IMAGE_TOOLS_PGM_H

/**
 * Thoses functions and structure are used to get modify and save a PGM.
 * 
 * Actually features :
 * - Get a PGM_image from a file
 * 
 * To Do :
 * - Manipulate the PGM_image
 * - Save the PGM_image on a hard drive
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "basic_tools.h"

#define BUFFER_SIZE         200
#define MAX_CHAR_PER_LINE   70
#define FILE_MAX_SIZE       2048
#define NUMBER_MAX_SIZE     7

typedef struct PGM_image PGM_image;
struct PGM_image
{
    int height;
    int width;
    int v_max;
    int** pixels;
};

PGM_image* PGM_get_image_from_file(FILE* file);
e__bool PGM_save_image_into_file(PGM_image* pgm, FILE* file);

int get_first_int_from_string(char* buffer);
int get_second_int_from_string(char* buffer);

void fill_picture_line_from_string(PGM_image* pgm, int picture_line, char* buffer);

e__bool is_separator(char char_readed);

void free_PGM_image(PGM_image* pgm);
void display_PGM_image(PGM_image* pgm);

#endif