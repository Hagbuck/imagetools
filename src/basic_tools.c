/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "basic_tools.h"

/**
 * @brief      Gets the file.
 *
 * @param      file_name  The file name
 * @param      mehod      The opened mehod
 *
 * @return     The file.
 */
FILE * get_file(char* file_name, char* method)
{
    FILE * file;
    file = fopen(file_name, method);
    if(file)
    {
        return file;
    }
    printf("ERROR : %d\n", ERR_FAILED_OPENED_FILE);
    exit(ERR_FAILED_OPENED_FILE);
}

/**
 * @brief      Saves a string into file.
 *
 * @param      str   The string
 * @param      file  The file
 *
 * @return     { TRUE if success, otherwise FALSE }
 */
e__bool save_string_into_file(char* str, FILE* file)
{
    if(file)
    {
        fputs(str, file);
        return TRUE;
    }
    return FALSE;
}

