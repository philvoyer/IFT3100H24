# IFT3100H21

## Module 7 : Illumination classique

### Exemple 7.1

Démonstration de différents types de lumières et de matériaux du pipeline fixe de OpenGL (version 2.1).

La scène contient trois modèles : un cube, une sphère et un teapot.

Chaque modèle possède son propre matériau.

L'éclairage de la scène est une lumière ambiante, une directionnelle, une ponctuelle et un projecteur.

Le programme peut soit utiliser les fonctions du pipeline fixe (OpenGL 2.1) ou les shaders par défaut de openFrameworks (OpenGL 3.3).

Avec les fonctions du pipeline fixe, le modèle d'illumination est Blinn-Phong calculé au niveau des sommets.

Avec le shader par défaut de openFrameworks, le modèle d'illumination est Blinn-Phong calculé au niveau des fragments.

### Exemple 7.2

Démonstration de 5 modèles d'illumination classiques implémentés avec des shaders :

- couleur de remplissage uniforme sur toute la surface,
- modèle d'illumination de Lambert,
- modèle d'illumination de Gouraud,
- modèle d'illumination de Phong et
- modèle d'illumination de Blinn-Phong.

Le facteur de brillance spéculaire est animé par oscillation.

La position de la source de lumière est interactive.
