# IFT3100H24

## Module 1 : Image

### Exemple 1.1 (BonjourMonde)

Exemple d'un programme minimaliste.

Les événements du clavier et de la souris changent les 3 composantes d'une couleur RGB aléatoire.

La couleur aléatoire est appliquée comme couleur d'arrière-plan.

L'inverse de la couleur aléatoire est utilisé comme teinte.

La teinte est appliquée sur différentes primitives vectorielles avec un shader.

### Exemple 1.2 (AlmostEmptyProject)

Exemple d'un projet relativement vide, mais avec une bonne structure de base.

Ce projet est un bon point de départ pour commencer un nouveau projet avec une scène vide.

Afin d'avoir un peu de rétroaction à l'exécution, il y a une animation de la couleur d'arrière-plan par interpolation de niveaux de gris en fonction du numéro du frame courant.

Il y a aussi une trace dans la console à chaque frame qui permet de voir la valeur courante de différentes données temporelles.

Notamment : le numéro du frame courant, le temps écoulé depuis le début de l'exécution du programme, le temps écoulé depuis le frame précédent et une estimation de la cadence de rafraichissement, avec 60 mises à jour par seconde comme objectif.

Notez qu'une trace dans la console à chaque mise à jour à un impact négatif sur les performances et que cela devrait normalement être évité. 

### Exemple 1.3 (ImageImport)

Exemple d'importation et d'affichage en pleine fenêtre d'une image.

L'image est importée à partir d'un fichier qui se trouve dans le répertoire `./bin/data`.

Une nouvelle image peut aussi être glissée-déposée sur la fenêtre de l'application.

### Exemple 1.4 (ImageExport)

Exemple d'exportation du contenu de la fenêtre d'affichage dans un fichier image situé dans le répertoire `./bin/data`.

L'exportation est déclenchée lorsque la barre d'espacement est relâchée.

Un shader est utilisé pour créer un filtre qui permet d'inverser la couleur du contenu de la fenêtre d'affichage.

### Exemple 1.5 (Triptyque)

Exemple d'échantillonnage dans une image chargée en mémoire pour en extraire 3 nouvelles images.

Ces nouvelles images sont ensuite dessinées de gauche à droite avec un espacement horizontal et vertical.

Un shader est utilisé pour appliquer une teinte sur les images.

### Exemple 1.6 (ColorSpaceBitmap)

Génération procédurale d'une image dans un espace de couleur binaire.

Les pixels sont colorés selon le pattern d'un échiquier.

Exportation des données de l'image dans un fichier `.pbm` (*portable bitmap*).

### Exemple 1.7 (ColorSpaceGraymap)

Génération procédurale d'une image dans un espace de couleur en niveau de gris (256 variations).

Les pixels sont colorés selon la valeur d'un `xor` ('ou' exclusif) entre les coordonnées x et y.

Exportation des données de l'image dans un fichier `.pgm` (*portable graymap*).

### Exemple 1.8 (ColorSpacePixmap)

Génération procédurale d'une image dans un espace de couleur RGB (256 variations par composante de couleur).

Les pixels sont colorés par interpolation linéaire de deux composantes de couleur sur l'axe horizontal et vertical.

Exportation des données de l'image dans un fichier `.ppm` (*portable pixmap*).

### Exemple 1.9 (GL_FramebufferCreate)

Exemple d'une section de code pour créer et configurer un framebuffer avec OpenGL.

### Exemple 1.10 (GL_ImageImport)

Exemple d'une section de code pour importer une image et la convertir en texture avec OpenGL.

### Exemple 1.11 (GL_ImageExport)

Exemple d'une section de code pour exporter une image à partir du contenu d'un framebuffer avec OpenGL.
