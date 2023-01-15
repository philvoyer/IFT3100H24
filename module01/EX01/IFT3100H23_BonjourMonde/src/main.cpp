// IFT3100H23_BonjourMonde/main.cpp
// Exemple d'un programme minimaliste.
// Les événements du clavier et de la souris changent les 3 composantes d'une couleur RGB aléatoire.
// La couleur aléatoire est appliquée comme couleur d'arrière-plan.
// L'inverse de la couleur aléatoire est utilisée comme teinte.
// La teinte est appliquée sur différentes primitives vectorielles avec un shader.

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
