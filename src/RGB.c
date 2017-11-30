/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#include "RGB.h"

e__bool RGB_copy_RGB(RGB* const dest, RGB* const src)
{
    if(dest != NULL && src != NULL)
    {
        dest->r = src->r;
        dest->g = src->g;
        dest->b = src->b;
    }
    return FALSE;
}

e__bool Int_RGB_copy_RGB(Int_RGB* const dest, RGB* const src)
{
    if(dest != NULL && src != NULL)
    {
        dest->r = src->r;
        dest->g = src->g;
        dest->b = src->b;
    }
    return FALSE;
}

e__bool RGB_copy_Int_RGB(RGB* const dest, Int_RGB* const src)
{
    if(dest != NULL && src != NULL)
    {
        dest->r = src->r;
        dest->g = src->g;
        dest->b = src->b;
    }
    return FALSE;
}


e__bool RGB_plus_RGB_in_RGB(RGB* const res, RGB* const a, RGB* const b)
{
    if(res != NULL && a != NULL && b != NULL)
    {
        res->r = a->r + b->r;
        res->b = a->r + b->b;
        res->g = a->r + b->g;
    }
    return FALSE;
}

e__bool RGB_plus_RGB_in_Int_RGB(Int_RGB* const res, RGB* const a, RGB* const b)
{
    if(res != NULL && a != NULL && b != NULL)
    {
        res->r = a->r + b->r;
        res->b = a->r + b->b;
        res->g = a->r + b->g;
    }
    return FALSE;
}

e__bool Int_RGB_plus_Int_RGB_in_Int_RGB(Int_RGB* const res, Int_RGB* const a, Int_RGB* const b)
{
    if(res != NULL && a != NULL && b != NULL)
    {
        res->r = a->r + b->r;
        res->b = a->r + b->b;
        res->g = a->r + b->g;
    }
    return FALSE;
}


e__bool RGB_plus_equals_RGB(RGB* const origin, RGB* const added)
{
    if(origin != NULL && added != NULL)
    {
        origin->r += added->r;
        origin->g += added->g;
        origin->b += added->b;
    }
    return FALSE;
}

e__bool RGB_plus_equals_Int_RGB(RGB* const origin, Int_RGB* const added)
{
    if(origin != NULL && added != NULL)
    {
        origin->r += added->r;
        origin->g += added->g;
        origin->b += added->b;
    }
    return FALSE;
}

e__bool Int_RGB_plus_equals_RGB(Int_RGB* const origin, RGB* const added)
{
    if(origin != NULL && added != NULL)
    {
        origin->r += added->r;
        origin->g += added->g;
        origin->b += added->b;
    }
    return FALSE;
}

e__bool Int_RGB_plus_equals_Int_RGB(Int_RGB* const origin, Int_RGB* const added)
{
    if(origin != NULL && added != NULL)
    {
        origin->r += added->r;
        origin->g += added->g;
        origin->b += added->b;
    }
    return FALSE;
}


e__bool RGB_divide_by_int(RGB* const pixel, int divisor)
{
    if(pixel != NULL && divisor != 0)
    {
        pixel->r /= divisor;
        pixel->g /= divisor;
        pixel->b /= divisor;
    }
    return FALSE;
}

e__bool Int_RGB_divide_by_int(Int_RGB* const pixel, int divisor)
{
    if(pixel != NULL && divisor != 0)
    {
        pixel->r /= divisor;
        pixel->g /= divisor;
        pixel->b /= divisor;
    }
    return FALSE;
}