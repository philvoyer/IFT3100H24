// IFT3100H23_Oscillator/main.cpp
// Dans cet exemple, deux approches différentes sont utilisées pour animer un modèle par oscillation.
// Un cercle rouge est animé par le CPU avec une fonction d'oscillation implémentée en **C++** et
// un cercle vert est animé par le GPU avec la même fonction implémentée en **GLSL** dans un shader de sommets.
// La fonction d'oscillation génère un mouvement perpétuel en fonction du temps courant, d'une amplitude et d'une fréquence.

#include "ofMain.h"
#include "application.h"

int main()
{
  // paramètres du contexte de rendu OpenGL
  ofGLFWWindowSettings windowSettings;

  // option de redimentionnement de la fenêtre d'affichage
  windowSettings.resizable = true;

  // sélection de la version de OpenGL
  windowSettings.setGLVersion(3, 3);

  // création de la fenêtre
  ofCreateWindow(windowSettings);

  // démarrer l'exécution de l'application
  ofRunApp(new Application());
}
