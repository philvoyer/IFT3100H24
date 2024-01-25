// IFT3100H24_ImageExport/main.cpp
// Exemple d'exportation du contenu de la fenêtre d'affichage dans un fichier image situé dans le répertoire ./bin/data.
// L'exportation est déclenchée lorsque la barre d'espacement est relâchée.
// Un filtre permet d'inverser la couleur du contenu de la fenêtre d'affichage.

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
