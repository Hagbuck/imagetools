% [POLYTECH APP3] Projet base de developpement en C
% Octobre 2017 - Decembre 2017
% Detcheberry Valentin & Vuillemin Anthony

# imagetools

**Imagetools** est un projet étudiant réaliser à *Polytech* par Valentin Detcheberry et Anthony Vuillemin. C'est un projet codé en langage **C** sur une durée de 2 mois.

Ce projet à pour objectif la gestion et manipulation d'images **PGM** et **BMP** au minimum.

# Fonctionnalitées

Les fonctionnalitées seront si possible pour les deux formats mais d'après le cahier des charges elles sont réparties comme suit :

## Génériques 

* Lecture d'une image
* Sauvegarde d'une image
* Application de différents filtres:
    * Inverse
    * Rotation horizontal
    * Rotation vertical
* Histogramme

## PGM
* Filtre numérique RIF

## BMP
* Application de différents filtres:
    * Nuance de gris
* Égalisation
* Filtrage linéaire
* Extraction des contours (filtre de sobel)

## Interface

Par defaut on utilise une interface terminal, si possible on utilisera une interface **SDL2**