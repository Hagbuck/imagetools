/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "Matrix.h"

/**
 * @brief      Creates a matrix. All value will be setted to 0
 *
 * @param[in]  width   The width
 * @param[in]  height  The height
 *
 * @return     The matrix
 */
Matrix* create_Matrix(int width, int height)
{
    if(width > 0 && height > 0)
    {
        int i, j;

        Matrix* matrix = malloc(sizeof(Matrix));
        if(matrix != NULL)
        {
            matrix->width = width;
            matrix->height = height;

            matrix->values = malloc(height * sizeof(int*));
            if(matrix->values != NULL)
            {
                for(i = 0; i < height; ++i)
                {
                    matrix->values[i] = malloc(width * sizeof(int));
                    if(matrix->values[i] == NULL)
                    {
                        printf("ERROR bad alloc : %d\n", ERR_BAD_ALLOC);
                        exit(ERR_BAD_ALLOC);   
                    }

                    // Fill the matrix values with 0
                    for(j = 0; j < width; ++j)
                        matrix->values[i][j] = 0;
                }
                return matrix;
            }
            else
            {
                printf("ERROR bad alloc : %d\n", ERR_BAD_ALLOC);
                exit(ERR_BAD_ALLOC);            
            }
        }
        else
        {
            printf("ERROR bad alloc : %d\n", ERR_BAD_ALLOC);
            exit(ERR_BAD_ALLOC);            
        }
    }
    return NULL;
}

/**
 * @brief      Sets the value into matrix.
 *
 * @param      matrix  The matrix
 * @param[in]  x       x index
 * @param[in]  y       y index
 * @param[in]  value   The value
 *
 * @return     TRUE if success, FALSE otherwise
 */
e__bool set_value_into_Matrix(Matrix* const matrix, int x, int y, int value)
{
    if(matrix != NULL)
    {
        if(x >= 0 && x < matrix->width
        && y >= 0 && y < matrix->height)
        {
            matrix->values[y][x] = value;
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}

/**
 * @brief      Gets the value from matrix.
 *
 * @param      matrix  The matrix
 * @param[in]  x       x index
 * @param[in]  y       y index
 *
 * @return     The value from matrix.
 */
int get_value_from_Matrix(Matrix* const matrix, int x, int y)
{
    if(matrix != NULL)
    {
        if(x >= 0 && x < matrix->width
        && y >= 0 && y < matrix->height)
        {
            return matrix->values[y][x];
        }
    }
    return 0; // Only for jump the warning
}

/**
 * @brief      Free the memory of a Matrix
 *
 * @param      matrix  The matrix
 */
void free_Matrix(Matrix* const matrix)
{
    if(matrix != NULL)
    {
        int i;
        for(i = 0; i < matrix->height; ++i)
            free(matrix->values[i]);
        free(matrix);
    }
}

/**
 * @brief      Display a matrix
 *
 * @param      matrix  The matrix
 */
void display_Matrix(Matrix* const matrix)
{
    if(matrix != NULL)
    {
        int i,j;
        for(i = 0; i < matrix->height; ++i)
        {
            for(j = 0; j < matrix->width; ++j)
            {
                printf("[%d]\t", matrix->values[i][j]);
            }
            puts("");
        }
    }
}