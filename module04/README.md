# IFT3100H24

## Module 4 : Géométrie

### Exemple 4.1 (BonjourTriangle)

Exemple où un triangle par seconde est dessiné à des positions aléatoires dans la fenêtre d'affichage.

### Exemple 4.2 (EquilateralTriangle)

Exemple de dessin d'un triangle équilatéral et calcul de certaines de ses propriétés.

### Exemple 4.3 (RegularPolygon)

Exemple de dessin des polygones réguliers du triangle au dodécagone (3-12 arêtes).

### Exemple 4.4 (TriangleSoup)

Exemple de génération aléatoire et rendu d'une soupe aux triangles.

### Exemple 4.5 (TeaParty)

Exemple de chargement et de rendu de plusieurs instances d'un modèle importé à partir d'un fichier de géométrie externe (un teapot en format `.obj`).

### Exemple 4.6 (LambertTeapot)

Exemple d'importation et de rendu d'un teapot avec un shader de Lambert.

Un autre shader permet aussi de visualiser les normales sur la surface du modèle par conversion des composantes XYZ en couleur RGB.

Le fichier de géométrie du teapot et les shaders sont dans le répertoire `./bin/data`.

### Exemple 4.7 (GL_Mesh)

Exemple d'une classe minimaliste pour stocker les données des sommets d'un maillage triangulaire.

### Exemple 4.8 (GL_VertexBuffer)

Exemple d'une section de code pour créer d'un buffer de géométrie (vbo).

### Exemple 4.9 (GL_VertexAttributeFixedPipeline)

Exemple d'une section de code pour assigner les pointeurs vers chaque attribut de la structure de sommet d'un buffer de géométrie (pipeline fixe).

### Exemple 4.10 (GL_VertexAttributeModernPipeline)

Exemple d'une section de code pour assigner les pointeurs vers chaque attribut de la structure de sommet d'un buffer de géométrie (pipeline moderne).

### Exemple 4.11 (GL_VertexBufferDraw)

Exemple de différentes approches pour dessiner un buffer de géométrie.

### Exemple 4.12 (GL_VertexBufferSwap)

Exemple d'une section de code qui inverse en alternance deux buffers de géométrie utilisés pour la mise à jour et le rendu afin d'éviter de bloquer le pipeline de rendu.
