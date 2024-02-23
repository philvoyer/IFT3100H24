// IFT3100H24_CameraProjection/main.cpp
// Exemple d'une scène avec projection en perspective.

#include "ofMain.h"
#include "application.h"

int main()
{
  // paramètres du contexte de rendu
  ofGLFWWindowSettings windowSettings;

  // résolution de la fenêtre d'affichage
  windowSettings.setSize(960, 540);

  // sélection de la version de OpenGL
  windowSettings.setGLVersion(3, 3);

  // création de la fenêtre
  ofCreateWindow(windowSettings);

  // démarrer l'exécution de l'application
  ofRunApp(new Application());
}
