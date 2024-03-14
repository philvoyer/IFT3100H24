// IFT3100H24_GL_Texture.cpp
// Exemple de sections de code pour configurer et manipuler des textures avec OpenGL.

// 1. ouvrir un fichier image en mode lecture et en extraire les propriétés

int image_width = ...;
int image_height = ...;
int image_component = ...;


// 2. allocation de l'espace mémoire pour les pixels de l'image

int image_size = image_width * image_height * image_component;

GLubyte* pixels = (GLubyte*) std::malloc(image_size * sizeof(GLubyte));

// lire le contenu de l'image et copier ses pixels en mémoire (RAM)
// ...


// 3. sélectionner l'unité de texture active

// index de l'unité de texture
int index = ...; // index de 0 à GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS

glActiveTexture(GL_TEXTURE0 + index);


// 4. création d'une texture à partir des données de l'image

GLuint texture_id;
glGenTextures(1, &texture_id);
glBindTexture(GL_TEXTURE_2D, texture_id);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);


// 5. définir les paramètres d'enveloppement aux extrémités de la texture active

// mode d'enveloppement de texture : GL_CLAMP_TO_BORDER
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

// mode d'enveloppement de texture : GL_CLAMP_TO_EDGE
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

// mode d'enveloppement de texture : GL_REPEAT
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

// mode d'enveloppement de texture : GL_MIRRORED_REPEAT
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);


// 6. définir les paramètres d'interpolation des texels de la texture active

// pas de filtrage
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

// filtrage bilinéaire
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

// filtrage trilinéaire
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

// filtrage anisotropique
// avec GL_ARB_texture_filter_anisotropic si OpenGL 4.6
// avec GL_EXT_texture_filter_anisotropic sinon
GLfloat largest_anisotropy;
glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest_anisotropy);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest_anisotropy);


// 7. mipmapping

// générer les différents niveaux de mipmapping de la texture
glGenerateMipmap(GL_TEXTURE_2D);


// 8. composition

// activer la composition
glEnable(GL_BLEND);

// configuration du mode de composition
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


// 9. correction gamma

// activer la correction gamma automatique avec l'espace de couleur sRGB
glEnable(GL_FRAMEBUFFER_SRGB);


// 10. anticrénelage

// activer le multisampling
glEnable(GL_MULTISAMPLE);

// nombres d'échantillon
GLint sample_count = 4;

// framebuffer avec anticrénelage (MSAA)
glRenderbufferStorageMultisample(GL_RENDERBUFFER, sample_count, GL_RGBA, image_width, image_height);

// texture avec anticrénelage (MSAA)
GLuint multisampled_texture_id;
glGenTextures(1, &multisampled_texture_id);
glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, multisampled_texture_id);
glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, sample_count, GL_RGBA, image_width, image_height, GL_TRUE);
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, multisampled_texture_id, 0);

// résolution de l'anticrénelage de la texture par copie dans un framebuffer
glBlitFramebuffer(0, 0, image_width, image_height, 0, 0, image_width, image_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
