// IFT3100H21_Interface/main.cpp
// Exemple d'une interface graphique qui permet de paramétrer des options de dessin.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(800, 600, OF_WINDOW);
  ofRunApp(new Application());
}
