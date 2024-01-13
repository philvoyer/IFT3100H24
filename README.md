# IFT3100H24

Exemples et références du cours 'IFT-3100 Infographie' de l'Université Laval (édition hiver 2024).

## Module 1

Étude des propriétés de l’image, organisation matricielle des pixels, résolution d’image, espace de couleur, transparence, formats de fichier image, compression, importation, exportation et manipulation d’images par programmation.

## Module 2

Techniques de dessin basées sur l’idée de symboliser des instances de primitives vectorielles à partir d’un minimum d’attributs numériques pour ensuite pouvoir reconstruire leur représentation sous forme de pixels à partir d’algorithmes.

## Module 3

Étude des principaux outils mathématiques utilisés pour la transformation géométrique dans les espaces 2D et 3D tels que les vecteurs, les matrices et les quaternions.

## Module 4

Représentation de primitives géométriques et d’objets complexes sous forme de maillages triangulaires, spécification des attributs de sommet, mise en cache de la géométrie et commandes de rendu.

## Module 5

Propriétés de caméra, fenêtre d’affichage, transformation du point de vue dans une scène, projection graphique et techniques d’occlusion.

## Module 6

Conversion d’image en texture, mise en cache, échantillonnage, compression, traitement et filtrage.

## Module 7

Illumination à partir des sources de lumière d’une scène et des propriétés du matériau d’une surface.

## Module 8

Techniques de modélisation de géométries continues telles que des courbes et des surfaces paramétriques, triangulation, parcours et échantillonnage à partir d’algorithmes.

## Module 9

Techniques de rendu qui utilisent des rayons pour simuler l’illumination directe et indirecte, la réflexion, la réfraction et l’ombrage des surfaces.

## Module 10

Rendu basé sur la physique, réflexion diélectrique, métallicité, rugosité, microfacettes, équation de rendu, BRDF.

## Compilation

Ce dépôt contient trois types d'exemples :

1. Des extraits de sections de code OpenGL minimalistes en C++ ou GLSL. Ces exemples ne sont pas exécutables.
2. Des exemples en C++ pur, sans autre dépendance que les librairies standards du langage. Un *Makefile* accompagne ces exemples, simplement faire un *make* dans une console pour compiler un exécutable.
3. Tous les autres exemples utilisent *openFrameworks 0.11.2*. Simplement cloner ce dépôt dans le répertoire */apps* et utiliser le *projectGenerator* qui accompagne la technologie pour générer les solutions de votre IDE préféré. Une fois ouvert dans un IDE, supprimer les références vers les fichiers *ofApp.h* et *ofApp.cpp* car ils ne sont pas utilisés.
