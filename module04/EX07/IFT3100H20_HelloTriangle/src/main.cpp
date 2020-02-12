// IFT3100H20_HelloTriangle/main.cpp
// Exemple où un triangle par seconde est dessinée à des positions aléatoires dans la fenêtre d'affichage.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
