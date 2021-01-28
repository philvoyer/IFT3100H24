// IFT3100H21_AlmostEmptyProject/main.cpp
// Exemple d'un projet relativement vide, mais avec une bonne structure de base.
// Un bon point de départ pour commencer un nouveau projet avec une scène vide.
// Animation de la couleur d'arrière-plan par interpolation de niveaux de gris en fonction du numéro du frame courant.
// Trace des données temporelles dans la console à chaque frame.

#include "ofMain.h"
#include "application.h"

// point d'entrée de l'application
int main()
{
  // création du contexte de rendu (OpenGL 2.1 par défaut)
  ofSetupOpenGL(512, 512, OF_WINDOW);

  // instancier et lancer l'application (openFrameworks 0.11.0)
  ofRunApp(new Application());
}
