// IFT3100H19_DrawZone/main.cpp
// Dessiner une zone rectangulaire en fonction de la position où un des boutons du périphérique de pointage a été appuyé
// et de la position courante du curseur, tout en restant dans les limites du canevas.

#include "ofMain.h"
#include "application.h"

int main( )
{
  ofSetupOpenGL(512, 512, OF_WINDOW);
  ofRunApp(new Application());
}
