% [POLYTECH APP3] Development project with C langage
% October 2017 - December 2017
% Detcheberry Valentin & Vuillemin Anthony

# imagetools

**Imagetools** is a school project made at *Polytech Paris Sud*. It is develop with **C langage**.

This project can manipulate **BMP** and **PGM** pictures.

# Features

* Read a picture
* Save a picture
* Set filters
    * Reversed
    * Horizontal rotation
    * Vertical rotation
    * Linear filtering
        * FIR 1D horizontal
        * FIR 1D vertical
        * FIR 2D with matrix convolution
            * FIR 2D border x
            * FIR 2D border y
            * Sobel filter
* Get histogram
    * With only intensity
    * With all component (only for BMP)
* Save histogram
* Set histogram equalisation

# Interfaces

**Imagetools** have 3 interfaces :

* Console interface
* Commande line interface
* Graphical interface

# Compilation

To compile the whole project : `make`

If you only want one interface :

* Console interface : `make ci`
* Command line interface : `make cli`
* Graphical interface : `make gui`

# Use

## CI : Console interface

Launch : `./imagetools-ci.out`

## CLI : Command line interface

Launch `./imagetools-cli.out`

### Command's list

* **Open an image** (*-p* for pgm and *-b* for bmp)
* Set a filter
    * --gray
    * --reversed
    * --h-rotate
    * --v-rotate
    * --fir1d-h (+ int_depth)
    * --fir1d-v (+ int_depth)
    * --fir2d-x
    * --fir2d-y
    * --sobel
    * --equalize-hist
* Get histogram (*--histogram* + r,g,b,i or c + path)
* Save image (*-s* path)

Each command will be apply in the order which they are passed

### Examples

We get *lena.ascii.pgm*, and we set the reversed filter, we save the intensity histogram and save the new picture as *reversed/lena.ascii.pgm*

`./imagetools -p img/lena.ascii.pgm --reversed --histogram i histogram/lena.ascii.pgm -s reversed/lena.ascii.pgm`

## GUI : Graphical interface

Launch `./imagetools-gui.out`