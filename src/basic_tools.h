/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#ifndef IMAGE_TOOLS_BASIC_TOOLS_H
#define IMAGE_TOOLS_BASIC_TOOLS_H

#include <stdio.h>

typedef enum e__bool e__bool;
enum e__bool{FALSE, TRUE};

FILE * get_file(char* file_name, char* method);
e__bool save_string_into_file(char* str, FILE* file);

#endif