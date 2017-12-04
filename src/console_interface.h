/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#ifndef IMAGE_TOOLS_CONSOLE_INTERFACE_H
#define IMAGE_TOOLS_CONSOLE_INTERFACE_H

#include <stdio.h>
#include <stdlib.h>

#include "basic_tools.h"
#include "PGM_P2.h"
#include "BMP.h"
#include "Matrix.h"

#define JUMP    6
#define NB_DOT  27

void    show_logo(void);
void    main_menu(void);
char    get_action(void);
int     get_number(void);
void    bmp_menu(void);
void    pgm_p2_menu(void);

void    jump_clear(void);

#endif