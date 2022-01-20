// IFT3100H22_GL_ImageExport.cpp
// Exemple d'une section de code pour exporter une image à partir du contenu d'un framebuffer avec OpenGL.

// entrée
// • Identifiant du framebuffer à copier.
// sortie
// • Un fichier image qui contient une copie du contenu du framebuffer.

// un framebuffer complet avec un renderbuffer attaché à GL_COLOR_ATTACHMENT0
GLuint framebuffer = ...;

// propriétés du framebuffer
GLint image_width;
GLint image_height;
GLint image_format


// 1. Extraction des propriétés du framebuffer

// sélectionner le framebuffer à échantillonner
glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

// extraire les propriétés de largeur et de hauteur du framebuffer
glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &image_width);
glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &image_height);

// extraire le type d'espace de couleur du framebuffer
glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, &image_format);

// déterminer le nombre de composantes de couleur selon le type d'espace de couleur
int image_component;
if (image_format == GL_RGBA)
  image_component = 4;
else if(image_format == GL_RGB)
  image_component = 3;
else if(...)


// 2. allocation de l'espace mémoire pour les pixels de l'image

int image_size = image_width * image_height * image_component;
GLubyte* pixels = (GLubyte*) std::malloc(image_size * sizeof(GLubyte));


// 3. copier le contenu du framebuffer

// lire le contenu du framebuffer et copier les pixels en mémoire RAM
glReadPixels(0, 0, image_width, image_height, image_format, GL_UNSIGNED_BYTE, pixels);

// la lecture se fera dans le renderbuffer GL_COLOR_ATTACHMENT0 du FBO


// 4. sauvegarde dans un fichier image

// ouvrir un nouveau fichier image en mode écriture
// ...

// écrire les pixels dans le fichier image
// ...

// fermer le fichier image
// ...

// libérer l'espace occupé par l'image en mémoire RAM
std::free(pixels);
