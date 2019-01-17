// IFT3100H19_ImageImport/main.cpp
// Exemple d'importation et d'affichage en pleine fenêtre d'une image.
// L'image est importée à partir d'un fichier qui se trouve dans le répertoire ./bin/data.
// Une nouvelle image peut aussi être glissée-déposée sur la fenêtre de l'application.

#include "ofMain.h"
#include "application.h"

// point d'entrée de l'application
int main( )
{
  // création du contexte de rendu (OpenGL 2.1 par défaut)
  ofSetupOpenGL(512, 512, OF_WINDOW);

  // instancier et lancer l'application (openFrameworks 0.10.1)
  ofRunApp(new Application());
}
