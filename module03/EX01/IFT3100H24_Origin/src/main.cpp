// IFT3100H24_Origin/main.cpp
// Dans cet exemple, une représentation de l'origine de la scène est dessinée à deux localisations,
// une avant transformation et une après transformation du système de coordonnées par translation
// pour modifier la position de l'origine de la scène.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
