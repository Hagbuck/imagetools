/**
 * [POLYTECH APP3] Projet base de developpement en C
 * Detcheberry Valentin
 * Vuillemin Anthony
 */

#ifndef IMAGE_TOOLS_BMP_H
#define IMAGE_TOOLS_BMP_H

/**
 * Thoses functions and structure are used to get modify and save a BMP.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "basic_tools.h"
#include "Matrix.h"
#include "RGB.h"

#define BMP_V_MAX   255

typedef struct BMP_header BMP_header;
struct BMP_header
{
    /*** HEADER FILE ***/
    unsigned char   bfType[2];
    unsigned char   bfSize[4];
    unsigned char   bfReserved1[2];
    unsigned char   bfReserved2[2];
    unsigned char   bfOffBits[4];

    /*** HEADER BITMAP ***/
    unsigned char   biSize[4];
    unsigned char   biWidth[4];
    unsigned char   biHeight[4];
    unsigned char   biPlane[2];
    unsigned char   biBitCount[2];
    unsigned char   biCompression[4];
    unsigned char   biSizeImage[4];
    unsigned char   biXpelsPerMeter[4];
    unsigned char   biYpelsPerMeter[4];
    unsigned char   biClrUsed[4];
    unsigned char   biClrImportant[4];
};

typedef struct BMP_image BMP_image;
struct BMP_image
{
    BMP_header      header;

    /** BITMAP PIXELS **/
    int             width;
    int             height;
    RGB**           pixels;
};

/**
 * e__color is a enumeration used into the histogram to know wich color it have to catch
 */
typedef enum e__color e__color;
enum e__color{RED, GREEN, BLUE, INTENSITY};

typedef struct BMP_histogram BMP_histogram;
struct BMP_histogram
{
    BMP_header      header;
    e__color        component;
    int*            intensity_values;
    int             size;
};

// BMP struct manipulating
BMP_image*      BMP_get_image_from_file(FILE* file);
e__bool         BMP_fill_header(BMP_image* const bmp, FILE* const file);
e__bool         BMP_header_to_str(BMP_image* const bmp, unsigned char* str);
e__bool         BMP_fill_pixels(BMP_image* const bmp, FILE* const file);
e__bool         BMP_save_image_into_file(BMP_image* const bmp, FILE* const file);

e__bool         BMP_copy_header(BMP_image* const src, BMP_image* const dest);
e__bool         BMP_copy_header_into_histogram(BMP_image* const src, BMP_histogram* const dest);
e__bool         BMP_histogram_copy_header_into_BMP_image(BMP_histogram* const src, BMP_image* const dest);
BMP_image*      BMP_get_copy(BMP_image* const bmp);

// Basic filtering
e__bool         BMP_set_gray_filter(BMP_image* const bmp);
e__bool         BMP_set_reversed_filter(BMP_image* const bmp);
e__bool         BMP_set_horizontal_reversed(BMP_image* const bmp);
e__bool         BMP_set_vertical_reversed(BMP_image* const bmp);

// Linear filtering
e__bool         BMP_set_FIR_1D_horizontal_filter_with_depth(BMP_image* const bmp, int depth);
e__bool         BMP_set_FIR_1D_vertical_filter_with_depth(BMP_image* const bmp, int depth);
e__bool         BMP_set_FIR_2D_border_filter_x(BMP_image* const bmp);
e__bool         BMP_set_FIR_2D_border_filter_y(BMP_image* const bmp);
e__bool         BMP_set_sobel_filter(BMP_image* const bmp);
e__bool         BMP_convolution_with_Matrix(BMP_image* const bmp, Matrix* const matrix);

// Histogram
BMP_histogram*  BMP_get_histogram(BMP_image* const bmp, e__color component);
BMP_image*      BMP_get_BMP_image_from_BMP_histogram(BMP_histogram* const histogram);
e__bool         BMP_save_histogram_as_BMP_file(BMP_histogram* const histogram, FILE* file);

// Free and display
void            BMP_show_header(const BMP_image* const bmp);
void            free_BMP_pixels(BMP_image* const bmp);
void            free_BMP_image(BMP_image* const bmp);
void            free_BMP_histogram(BMP_histogram* const histogram);

#endif