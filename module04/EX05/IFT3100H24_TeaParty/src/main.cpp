// IFT3100H24_TeaParty/main.cpp
// Exemple de chargement et de rendu de plusieurs instances d'un modèle importé à partir d'un fichier de géométrie externe (un teapot en format .obj).

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
