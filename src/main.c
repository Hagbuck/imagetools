/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include <stdio.h>
#include <stdlib.h>

#include "basic_tools.h"

int main(int argc, char *argv[])
{
    /**
     * basic example to read and display a file
     */
    FILE* file = get_file("img/test.pgm", "r");
    if(file)
    {
        int car;
        do
        {
            car = fgetc(file);
            if(car != EOF)
                printf("%c", car);
        }while(car != EOF);
        puts("");
        
        fclose(file);
    }
    return 0;
}