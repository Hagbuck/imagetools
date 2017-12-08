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
#define ERR_FAILED_OPENED_FILE          1   
#define ERR_FILE_IS_NULL                2
#define ERR_IMAGE_FILE_IS_INCORRECT     3
#define ERR_PIXEL_VALUE_INCORECT        4
#define ERR_BAD_ALLOC                   5
#define ERR_STRUCT_IS_NULL              6
#define ERR_CANNOT_CONVERT_STR_TO_INT   7


#define NUMBER_MAX_SIZE                 7


typedef enum e__bool e__bool;
enum e__bool{FALSE, TRUE};

FILE*   get_file(char* const file_name, char* const method);
e__bool save_string_into_file(char* const str, FILE* const file);
void    str_to_int(char* const str, int* const integer);
int     get_int_from_str(char* const str);

#endif