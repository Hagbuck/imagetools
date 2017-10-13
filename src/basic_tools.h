/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#ifndef IMAGE_TOOLS_BASIC_TOOLS_H
#define IMAGE_TOOLS_BASIC_TOOLS_H

#include <stdio.h>
#include <stdlib.h>

/**
 * Listing of error
 */
#define ERR_FAILED_OPENED_FILE      1
#define ERR_FILE_IS_NULL            2
#define ERR_IMAGE_FILE_IS_INCORRECT 3
#define ERR_PIXEL_VALUE_INCORECT    4

typedef enum e__bool e__bool;
enum e__bool{FALSE, TRUE};

FILE * get_file(char* file_name, char* method);
e__bool save_string_into_file(char* str, FILE* file);

#endif