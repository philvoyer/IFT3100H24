// IFT3100H21_Triptyque/main.cpp
// Exemple d'échantillonnage dans une image chargée en mémoire pour en extraire 3 nouvelles images.
// Ces nouvelles images sont ensuite dessinées de gauche à droite avec un espacement horizontal et vertical.
// Un shader est utilisé pour appliquer une teinte sur les images.

#include "ofMain.h"
#include "application.h"

int main()
{
  // paramètres du contexte de rendu OpenGL
  ofGLFWWindowSettings windowSettings;

  // option de redimentionnement de la fenêtre d'affichage
  windowSettings.resizable = false;

  // sélection de la version de OpenGL
  windowSettings.setGLVersion(3, 3);

  // création de la fenêtre
  ofCreateWindow(windowSettings);

  // démarrer l'exécution de l'application
  ofRunApp(new Application());
}
