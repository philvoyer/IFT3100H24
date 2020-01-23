// IFT3100H20_ImageImport/main.cpp
// Exemple d'importation et d'affichage en pleine fenêtre d'une image.
// L'image est importée à partir d'un fichier qui se trouve dans le répertoire ./bin/data.
// Une nouvelle image peut aussi être glissée-déposée sur la fenêtre de l'application.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
