// IFT3100H20_ImageFilter/main.cpp
// Exemple d'un filtre d'image créé avec un shader de fragments.
// Le filtre applique une teinte de couleur RGB mixée avec la couleur de l'image d'origine.

#include "ofMain.h"
#include "application.h"


int main()
{
  ofGLFWWindowSettings windowSettings;
  windowSettings.resizable = false;
  windowSettings.setGLVersion(3, 3);
  windowSettings.numSamples = 4;
  ofCreateWindow(windowSettings);
  ofRunApp(new Application());
}
