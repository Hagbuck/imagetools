% [POLYTECH APP3] Projet base de developpement en C
% Octobre 2017 - Decembre 2017
% Detcheberry Valentin & Vuillemin Anthony

# imagetools

**Imagetools** est un projet étudiant réaliser à *Polytech Paris Sud*. C'est un projet codé en langage **C**.

Ce projet à pour objectif la gestion et manipulation d'images **PGM** et **BMP** au minimum.

# Fonctionnalitées

* Lecture d'une image
* Sauvegarde d'une image
* Application de différents filtres:
    * Nuance de gris
    * Inverse
    * Rotation horizontal
    * Rotation vertical
    * Filtrage linéaire
        * RIF 1D horizontal
        * RIF 1D vertical
        * RIF 2D avec une convolution matricielle
            * RIF 2D bordure x
            * RIF 2D bordure y
            * Filtre de Sobel
* Obtention d'un histogramme
    * Avec seulement l'intensité
    * Avec toutes les composentes (uniquement pour les BMP)
* Sauvegarde d'un histogramme
* Egalisation d'un histogramme

# Interfaces

**Imagetools** dispose de 3 interfaces :

* Interface console
* Interface en ligne de commande
* Interface graphique

# Compilation

Pour compiler le projet en entier : `make`

Si vous voulez uniquement une interface : 

* Interface console : `make ci`
* Interface en ligne de commande : `make cli`
* Interface graphique : `make gui`

# Utilisation

## CI : Interface console

Lancez : `./imagetools-ci.out`

## CLI : Interface line de commande

Lancez : `./imagetools-cli.out`

### Liste des commandes

* **Ouvrir une image** (*-p* pour pgm et *-b* pour bmp)
* Appliquer un filtre
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
* Obtenir histogramme (*--histogram* + r,g,b,i ou c + path)
* Sauvegarde de l'image (*-s* path)

Les commandes seront appliquer dans l'ordre dans lequel elles sont passées.

### Exemples

On récupère *lena.ascii.pgm* on applique un fitre d'inversion, on sauvegarde l'histogramme d'intensité et on sauvegarde la modification dans le fichier *reversed/lena.ascii.pgm*.

`./imagetools -p img/lena.ascii.pgm --reversed --histogram i histogram/lena.ascii.pgm -s reversed/lena.ascii.pgm`


## GUI : Interface graphique

Lancez : `./imagetools-gui.out`