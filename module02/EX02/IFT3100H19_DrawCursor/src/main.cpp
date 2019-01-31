// IFT3100H19_DrawCursor/main.cpp
// Dessiner un curseur en fonction des états et des événements d'un périphérique de pointage.

#include "ofMain.h"
#include "application.h"

int main()
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
