// IFT3100H21_Lighting/main.cpp
// Démonstration de différents types de lumières et de matériaux.
// La scène contient trois modèles : un cube, une sphère et un teapot.
// Chaque modèle possède son propre matériau.
// L'éclairage de la scène est une lumière ambiante, une directionnelle, une ponctuelle et un projecteur.
// Le programme peut soit utiliser les fonctions du pipeline fixe (OpenGL 2.1) ou les shaders par défaut de openFrameworks (OpenGL 3.3).
// Avec les fonctions du pipeline fixe, le modèle d'illumination est Blinn-Phong calculé au niveau des sommets.
// Avec le shader par défaut de openFrameworks, le modèle d'illumination est Blinn-Phong calculé au niveau des fragments.

#include "ofMain.h"
#include "application.h"

bool use_gl_fixed_function_pipeline = false;

int main()
{
  ofGLWindowSettings windowSettings;
  windowSettings.setSize(1024, 512);

  if (use_gl_fixed_function_pipeline)
    windowSettings.setGLVersion(2, 1);
  else
    windowSettings.setGLVersion(3, 3);

  ofCreateWindow(windowSettings);
  ofRunApp(new Application());
}
