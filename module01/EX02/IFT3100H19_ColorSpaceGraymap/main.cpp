// IFT3100H19_ColorSpaceGraymap\main.cpp
// Génération procédurale d'une image dans un espace de couleur en niveau de gris (256 variations).
// Les pixels sont colorés selon la valeur d'un xor entre ses coordonnées x et y.
// Exportation des données de l'image dans un fichier .pgm (portable graymap).

#include <iostream>
#include <fstream>
#include <vector>

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
      width = 256;
      height = 256;
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
  std::vector<unsigned char> pixel(count);

  // génération du pattern
  for (y = 0; y < height; ++y)
  {
    for (x = 0; x < width; ++x)
    {
      // calculer l'index du pixel
      index = y * width + x;

      // xor des coordonnées x et y
      pixel[index] = x ^ y;
    }
  }

  // 4. sauvegarde des pixels dans un fichier image

  // nom du fichier image de type .pgm (portable graymap)
  std::string filename = "image" + std::to_string(width) + "x" + std::to_string(height) + ".pgm";

  // déclaration et ouverture du fichier en mode écriture
  std::ofstream file;
  file.open(filename, std::ios::out);

  // entête du ficher pour une image avec un espace de couleur en niveau de gris (P2 pour graymap)
  file << "P2\n";

  // largeur et hauteur de l'image sur la seconde ligne de l'entête
  file << width << ' ' << height << '\n';

  // valeur maximale de l'espace de couleur sur la troisième ligne de l'entête
  file << "255\n";

  // écriture des pixels dans le fichier image
  for (y = 0; y < height; ++y)
  {
    for (x = 0; x < width; ++x)
    {
      index = y * width + x;

      file << static_cast<int>(pixel[index]) << ' ';
    }
    file << '\n';
  }

  // fermeture du fichier
  file.close();
}
