// IFT3100H20_ColorSpaceBitmap\main.cpp
// Génération procédurale d'une image dans un espace de couleur binaire.
// Les pixels sont colorés selon le pattern d'un échiquier.
// Exportation des données de l'image dans un fichier .pbm (portable bitmap).

#include <iostream>
#include <fstream>
#include <vector>

// espace de couleur
enum class Color {white, black};

// fonction principale du programme
int main(int argc, char* argv[])
{
  // 1. déclaration des variables du programme

  // coordonnée d'un pixel sur l'axe x
  int x;

  // coordonnée d'un pixel sur l'axe y
  int y;

  // index d'un pixel dans l'image
  int index;

  // nombre de pixels en largeur dans l'image
  int width;

  // nombre de pixels en hauteur dans l'image
  int height;


  // 2. extractions des paramètres du programme

  switch (argc)
  {
    case 1:
      width = 8;
      height = 8;
      break;

    case 2:
      width = atoi(argv[1]);
      height = width;
      break;

    case 3:
    default:
      width = atoi(argv[1]);
      height = atoi(argv[2]);
      break;
  }


  // 3. initialisation des pixels de l'image

  // calculer le nombre de pixels dans l'image
  int count = width * height;

  // vecteur pour contenir les pixels de l'image
  std::vector<bool> pixel(count);

  // génération du pattern d'échiquier
  for (y = 0; y < height; ++y)
  {
    for (x = 0; x < width; ++x)
    {
      // calculer l'index du pixel
      index = y * width + x;

      // alternance entre les deux couleurs
      if ((x + y) % 2 == 0)
        pixel[index] = static_cast<bool>(Color::white);
      else
        pixel[index] = static_cast<bool>(Color::black);
    }
  }


  // 4. afficher l'image dans la console

  for (y = 0; y < height; ++y)
  {
    for (x = 0; x < width; ++x)
    {
      index = y * width + x;

      std::cout << pixel[index] << ' ';
    }
    std::cout << '\n';
  }


  // 5. sauvegarde des pixels dans un fichier image

  // nom du fichier image de type .pbm (portable bitmap)
  std::string filename = "image" + std::to_string(width) + "x" + std::to_string(height) + ".pbm";

  // déclaration et ouverture du fichier en mode écriture
  std::ofstream file;
  file.open(filename, std::ios::out);

  // entête du ficher pour une image avec un espace de couleur binaire (P1 pour bitmap)
  file << "P1\n";

  // largeur et hauteur de l'image sur la seconde ligne de l'entête
  file << width << ' ' << height << '\n';

  // écriture des pixels dans le fichier image
  for (y = 0; y < height; ++y)
  {
    for (x = 0; x < width; ++x)
    {
      index = y * width + x;

      file << pixel[index] << ' ';
    }
    file << '\n';
  }

  // fermeture du fichier
  file.close();
}
