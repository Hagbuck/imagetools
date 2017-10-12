/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "basic_tools.h"

FILE * get_file(char* file_name)
{

    FILE * file;
    file = fopen (file_name, "r");
    if(file)
    {
        return file;
    }
    return NULL;

}


