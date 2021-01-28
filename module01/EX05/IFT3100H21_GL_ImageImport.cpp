// IFT3100H21_GL_ImageImport.cpp
// Exemple d'une section de code pour importer une image et la convertir en texture avec OpenGL.

// entrées
// • Une référence vers un fichier image existant (chemin d'accès local ou URL).
// • Ensemble des propriétés de l'image (ex: largeur, hauteur, espace de couleur, nombre de composantes de couleur).

// sortie
// • Une texture générée à partir de l'image, chargée en mémoire GPU, adéquatement configurée et prête à l'utilisation.

// 1. ouvrir le fichier image en mode lecture et en extraire les propriétés

int image_width = ...;
int image_height = ...;
int image_component = ...;
int image_pixel_count = ...;
int image_size = ...;


// 2. allocation de l'espace mémoire pour les pixels de l'image

// calculer le nombre total de pixels dans l'image
image_pixel_count = image_width * image_height;

// calculer le nombre d'octets à allouer en mémoire pour contenir l'image
// (largeur x hauteur x nombre de composantes de couleur)
image_size = image_pixel_count * image_component;

// déclarer un pointeur vers un espace mémoire qui servira à stocker les pixels de l'image
// (GLubyte est 'unsigned byte' de 8 bits donc 256 niveaux de couleur par composante)
GLubyte* pixels;

// allocation d'un espace mémoire suffisamment grand pour contenir tous les pixels de l'image
pixels = (GLubyte*) std::malloc(image_size * sizeof(GLubyte));


// 3. lire le contenu de l'image et copier ses pixels en mémoire (RAM)
// ...


// 4. création d'une texture à partir de l'image

// déclarer un identifiant pour référencer la texture
// (GLubyte est un 'unsigned int' de 32 bits)
GLuint texture_id;

// création d'un identifiant pour une nouvelle texture
glGenTextures(1, &texture_id);

// sélectionner cette nouvelle texture comme texture active
glBindTexture(GL_TEXTURE_2D, texture_id);

// définir les paramètres d'enveloppement aux extrémités de la texture active
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

// définir les paramètres d'interpolation des texels de la texture active
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

// copier les pixels de l'image (mémoire RAM) vers la texture active (mémoire GPU)
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

// générer les différents niveaux de mipmapping de la texture
glGenerateMipmap(GL_TEXTURE_2D);

// la copie de l'image en mémoire RAM peut maintenant être supprimée car une copie existe maintenant en mémoire GPU
std::free(pixels);
