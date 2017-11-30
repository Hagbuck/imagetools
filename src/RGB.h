/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#ifndef IMAGE_TOOLS_RGB_H
#define IMAGE_TOOLS_RGB_H

#include "basic_tools.h"

/**
 * RGB is a pixel with 3 component red green and blue
 * Each component take 256 bits in memory
 */
typedef struct RGB RGB;
struct RGB
{
    unsigned char   r;
    unsigned char   g;
    unsigned char   b;
};

/**
 * Int_RGB is a pixel, but with a bigger memory
 * usefull to calculate 
 */
typedef struct Int_RGB Int_RGB;
struct Int_RGB
{
    int r;
    int g;
    int b;
};

/**
 * Double_RGB is a pixel, but with a bigger memory
 * usefull to calculate 
 */
typedef struct Double_RGB Double_RGB;
struct Double_RGB
{
    double r;
    double g;
    double b;
};

/**
 * Those functions arn't used because they don't working 
 * TODO : Debug functions and test them
 */
e__bool         RGB_copy_RGB(RGB* const dest, RGB* const src);
e__bool         Int_RGB_copy_RGB(Int_RGB* const dest, RGB* const src);
e__bool         RGB_copy_Int_RGB(RGB* const dest, Int_RGB* const src);

e__bool         RGB_plus_RGB_in_RGB(RGB* const res, RGB* const a, RGB* const b);
e__bool         RGB_plus_RGB_in_Int_RGB(Int_RGB* const res, RGB* const a, RGB* const b);
e__bool         Int_RGB_plus_Int_RGB_in_Int_RGB(Int_RGB* const res, Int_RGB* const a, Int_RGB* const b);

e__bool         RGB_plus_equals_RGB(RGB* const origin, RGB* const added);
e__bool         RGB_plus_equals_Int_RGB(RGB* const origin, Int_RGB* const added);
e__bool         Int_RGB_plus_equals_RGB(Int_RGB* const origin, RGB* const added);
e__bool         Int_RGB_plus_equals_Int_RGB(Int_RGB* const origin, Int_RGB* const added);

e__bool         RGB_divide_by_int(RGB* const pixel, int divisor);
e__bool         Int_RGB_divide_by_int(Int_RGB* const pixel, int divisor);

#endif