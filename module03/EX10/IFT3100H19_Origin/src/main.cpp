// IFT3100H19_Origin/main.cpp
// Transformation du système de coordonnées par translation pour modifier la position de l'origine de la scène.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
