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
            * Filtre de Sobel
* Obtention d'un histogramme
* Sauvegarde d'un histogramme
* Egalisation d'un histogramme

# Interfaces

**Imagetools** dispose de 3 interfaces :

* Interface console
* Interface en ligne de commande (A FAIRE)
* Interface graphique (A FAIRE, surement avec la SDL2 si la licence est compatible avec nos objectifs)