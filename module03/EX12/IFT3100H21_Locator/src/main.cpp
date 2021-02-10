// IFT3100H21_Locator/main.cpp
// Transformation d'un ensemble de localisateurs au hasard dans un espace cubique,
// avec possibilités d'activer et de désactiver les attributs de translation, de rotation et de proportion.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
