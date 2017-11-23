/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#ifndef IMAGE_TOOLS_MATRIX_H
#define IMAGE_TOOLS_MATRIX_H

#include "basic_tools.h"

typedef struct Matrix Matrix;
struct Matrix
{
    int     width;
    int     height;
    int**   values;
};

Matrix*     create_Matrix(int width, int height);

e__bool     set_value_into_Matrix(Matrix* const matrix, int x, int y, int value);
int         get_value_from_Matrix(Matrix* const matrix, int x, int y);

void        free_Matrix(Matrix* const matrix);
void        display_Matrix(Matrix* const matrix);

#endif