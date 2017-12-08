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
FILE * get_file(char* const file_name, char* const method)
{
    FILE * file;
    file = fopen(file_name, method);
    if(file)
    {
        return file;
    }
    printf("ERROR : %d\n", ERR_FAILED_OPENED_FILE);
    return NULL;
    // exit(ERR_FAILED_OPENED_FILE);
}

/**
 * @brief      Saves a string into file.
 *
 * @param      str   The string
 * @param      file  The file
 *
 * @return     { TRUE if success, otherwise FALSE }
 */
e__bool save_string_into_file(char* const str, FILE* const file)
{
    if(file)
    {
        fputs(str, file);
        return TRUE;
    }
    return FALSE;
}

/**
 * @brief      Transform the string into an integer
 *
 * @param      str      The string
 * @param      integer  The integer
 */
void str_to_int(char* const str, int* const integer)
{
    int i = 0;
    char c;
    *integer = 0;

    do
    {
        c = str[i];
        if(c >= '0' && c <= '9')
        {
            ++i;
            *integer += c - '0';
            *integer *= 10;
        }
    }while(c != '\0' && i < NUMBER_MAX_SIZE);
    *integer /= 10;
}

/**
 * @brief      Transform a string into an integer
 *
 * @param      str   The string
 *
 * @return     The integer
 */
int get_int_from_str(char* const str)
{
    int i = 0;
    char c;
    int integer = 0;
    int factor = 1; // If the number is negative

    if(str[0] == '-') // The number is negative
    {
        factor = -1;
        ++i;    // We catch the first element, so we go to the next case
    }
    do
    {
        c = str[i];
        if(c >= '0' && c <= '9')
        {
            ++i;
            integer += c - '0';
            integer *= 10;
        }
        else if(c != '\0')
        {
            printf("ERROR %d cannot convert str to int !\n", ERR_CANNOT_CONVERT_STR_TO_INT);
            exit(ERR_CANNOT_CONVERT_STR_TO_INT);
        }
    }while(c != '\0' && i < NUMBER_MAX_SIZE);
    integer /= 10;

    integer *= factor;

    return integer;
}