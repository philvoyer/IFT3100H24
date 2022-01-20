// IFT3100H22_ColorSpacePixmap\main.cpp
// Génération procédurale d'une image dans un espace de couleur RGB (256 variations par composante de couleur).
// Les pixels sont colorés par interpolation linéaire de deux composantes de couleur sur l'axe horizontal et vertical.
// Exportation des données de l'image dans un fichier .ppm (portable pixmap).

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

  // couleur RGBA 32 bits
  std::uint32_t color;

  // composantes de couleur de 8 bits
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;

  // valeur maximale d'une composante de l'espace de couleur
  const std::uint32_t color_space_max = 255;

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
  std::vector<std::uint32_t> pixel(count);

  // valeur incrémentale pour chaque composante
  double step_x = color_space_max / (double) width;
  double step_y = color_space_max / (double) height;

  // génération du pattern
  for (y = 0; y < height; ++y)
  {
    for (x = 0; x < width; ++x)
    {
      // calculer l'index du pixel
      index = y * width + x;

      // interpolation des composantes de couleur
      r = x * step_x;
      g = y * step_y;
      b = 0;
      a = color_space_max;;

      // version 1 : pour entier non signé de 8 bits par composante en une ligne
      color = (r << 24) | (g << 16) | (b << 8) | a;

      // version 2 : pour entier non signé de 8 bits par composante
      color = 0;
      color |= r << 24;
      color |= g << 16;
      color |= b << 8;
      color |= a;

      // version 3 : pour n'importe quel type d'entier
      color = 0;
      color |= (r & color_space_max) << 24;
      color |= (g & color_space_max) << 16;
      color |= (b & color_space_max) << 8;
      color |= (a & color_space_max);

      // assigner la couleur du pixel dans l'image
      pixel[index] = color;
    }
  }

  // 4. sauvegarde des pixels dans un fichier image

  // nom du fichier image de type .ppm (portable pixmap)
  std::string filename = "image" + std::to_string(width) + "x" + std::to_string(height) + ".ppm";

  // déclaration et ouverture du fichier en mode écriture
  std::ofstream file;
  file.open(filename, std::ios::out);

  // entête du ficher pour une image avec un espace de couleur RGB 24 bits (P3 pour pixmap)
  file << "P3\n";

  // largeur et hauteur de l'image sur la seconde ligne de l'entête
  file << width << ' ' << height << '\n';

  // valeur maximale de l'espace de couleur sur la troisième ligne de l'entête
  file << "255\n";

  // écriture des pixels dans le fichier image
  for (y = 0; y < height; ++y)
  {
    for (x = 0; x < width; ++x)
    {
      // déterminer l'index du pixel
      index = y * width + x;

      // couleur du pixel
      color = pixel[index];

      // extraction des composantes de couleur
      r = color_space_max & (color >> 24);
      g = color_space_max & (color >> 16);
      b = color_space_max & (color >> 8);
      a = color_space_max & color;

      // écrire la couleur du pixel dans le fichier image
      file << static_cast<std::uint32_t>(r) << " ";
      file << static_cast<std::uint32_t>(g) << " ";
      file << static_cast<std::uint32_t>(b) << " ";
    }
    file << '\n';
  }

  // fermeture du fichier
  file.close();
}
