// IFT3100H24_Move/main.cpp
// Dans cet exemple, une transformation de type translation est appliquée sur l'origine de la scène en fonction du temps
// pour permettre un mouvement dans l'espace sur le plan XZ à partir de l'état courant des flèches du clavier.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
