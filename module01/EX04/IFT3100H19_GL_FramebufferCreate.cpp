// IFT3100H19_GL_FramebufferCreate.cpp
// Exemple d'une section de code pour créer et configurer un framebuffer avec OpenGL.

// entrée
// • Une fenêtre d'affichage liée à un contexte de rendu.
// sortie
// • Un framebuffer prêt à l'utilisation, avec un buffer de rendu couleur et un buffer de profondeur.

// résolution en largeur de la fenêtre d'affichage
int viewport_width  = ...;
// résolution en hauteur de la fenêtre d'affichage
int viewport_height = ...;

// identifiant du framebuffer
GLuint framebuffer;
// identifiant du buffer de rendu
GLuint renderbuffer;
// identifiant du buffer de profondeur
GLuint depthbuffer;

// 1. création du framebuffer

// générer un identifiant pour un nouveau framebuffer
glGenFramebuffers(1, &framebuffer);

// sélectionner ce nouveau framebuffer comme framebuffer actif
glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

// 2. création du buffer de rendu attaché au framebuffer

// générer un identifiant pour un nouveau buffer de rendu
glGenRenderbuffers(1, &renderbuffer);

// sélectionner ce nouveau buffer comme buffer de rendu actif
glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);

// allouer l'espace mémoire du buffer de rendu
glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, viewport_width, viewport_height);

// attacher le buffer de rendu au framebuffer
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, renderbuffer);

// 3. création du buffer de profondeur attaché au framebuffer

// générer un identifiant pour un nouveau buffer de profondeur
glGenRenderbuffers(1, &depthbuffer);

// sélectionner ce nouveau buffer comme buffer de rendu actif
glBindRenderbuffer(GL_RENDERBUFFER, depthbuffer);

// allouer l'espace mémoire du buffer de profondeur
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, viewport_width, viewport_height);

// attacher le buffer de profondeur au framebuffer
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthbuffer);

// 4. valider si le framebuffer est complet
bool is_framebuffer_complete = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE ? true : false;
