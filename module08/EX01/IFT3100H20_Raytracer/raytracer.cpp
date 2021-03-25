// IFT3100H21_Raytracer/raytracer.cpp
// Exemple d'un raytracer minimaliste.
// Inspiré de smallpt.
// make : g++ -std=c++11 raytracer.cpp -o raytracer
// run  : ./raytracer image_width image_height ray_per_pixel

// c
#include <cmath>    // sqrt pow fabs cos sin

// c++
#include <iostream> // std cout endl
#include <sstream>  // stringstream
#include <fstream>

// c++11
#include <vector>
#include <random>
#include <chrono>

// paramètres du programme
const int max_depth = 5;
const double camera_fov = 0.5135;
constexpr double gamma_correction = 1 / 2.2;

// variables du programme
int image_width = 0;
int image_height = 0;
int ray_per_pixel = 0;
int pixel_count = 0;

// types de matériau
enum class SurfaceType {diffuse, specular, refraction};

// fonction pour borner une valeur numérique entre 0 et 1
double clamp(double x)
{
  return x < 0 ? 0 : x > 1 ? 1 : x;
}

// type vecteur 3D
struct Vector
{
  double x, y, z;

  // construction
  constexpr Vector() : x(0.0), y(0.0), z(0.0) {}
  constexpr Vector(double x) : x(x), y(0.0), z(0.0) {}
  constexpr Vector(double x, double y) : x(x), y(y), z(0.0) {}
  constexpr Vector(double x, double y, double z) : x(x), y(y), z(z) {}

  // produit scalaire (dot product)
  double dot(const Vector& v) const
  {
    return x * v.x + y * v.y + z * v.z;
  }

  // produit vectoriel (cross product)
  Vector cross(const Vector& v) const
  {
    return Vector(
      y * v.z - z * v.y,
      z * v.x - x * v.z,
      x * v.y - y * v.x);
  }

  // multiplication vectorielle
  Vector multiply(const Vector& v) const
  {
    return Vector(
      x * v.x,
      y * v.y,
      z * v.z);
  }

  // multiplication scalaire
  Vector operator*(double s) const
  {
    return Vector(
      x * s,
      y * s,
      z * s);
  }

  // addition vectorielle
  Vector operator+(const Vector& v) const
  {
    return Vector(
      x + v.x,
      y + v.y,
      z + v.z);
  }

  // soustraction vectorielle
  Vector operator-(const Vector& v) const
  {
    return Vector(
      x - v.x,
      y - v.y,
      z - v.z);
  }

  // normalisation
  Vector& normalize()
  {
    return *this = *this * (1.0 / sqrt(x * x + y * y + z * z));
  }
};

// structure d'un rayon sous forme de droite paramétrique
// équation d'un rayon : p(t) = o + td
struct Ray
{
  Vector origin;
  Vector direction;

  Ray(Vector o, Vector d) : origin(o), direction(d) {}
};

// type Sphere sous forme d'un point central et d'un rayon
struct Sphere
{
  double radius;   // rayon de la sphère
  Vector position; // position du centre de la sphère
  Vector emission; // couleur émissive de la sphère
  Vector color;    // couleur diffuse de la sphère

  SurfaceType material; // type de réflexion de la sphère

  // constructeur
  Sphere(double r, Vector p, Vector e, Vector c, SurfaceType m): radius(r), position(p), emission(e), color(c), material(m) {}

  // fonction d'intersection entre la sphère et un rayon
  double intersect(const Ray& ray) const
  {
    // distance de l'intersection la plus près si elle existe
    double distance;

    // seuil de tolérance numérique du test d'intersection
    double epsilon = 1e-4;

    // distance du point d'intersection
    double t;

    // vecteur entre le centre de la sphère et l'origine du rayon
    Vector delta = position - ray.origin;

    // calculer a
    double a = delta.dot(delta);

    // calculer b
    double b = delta.dot(ray.direction);

    // calculer c
    double c = radius * radius;

    // calculer le discriminant de l'équation quadratique
    double discriminant = b * b - a + c;

    // valider si le discriminant est négatif
    if (discriminant < 0)
    {
      // il n'y a pas d'intersection avec cette sphère
      return distance = 0;
    }

    // calculer la racine carrée du discriminant seulement si non négatif
    discriminant = sqrt(discriminant);

    // déterminer la distance de la première intersection
    t = b - discriminant;

    // valider si la distance de la première intersection est dans le seuil de tolérance
    if (t > epsilon)
      distance = t;
    else
    {
      // déterminer la distance de la première intersection
      t = b + discriminant;

      // valider si la distance de la seconde intersection est dans le seuil de tolérance
      if (t > epsilon)
        distance = t;
      else
        distance = 0;
    }

    // retourner la distance du point d'intersection
    return distance;
  }
};

// structure d'une caméra
struct Camera
{
  Vector position;
  Vector orientation;
  Vector target;

  Vector axis_x;
  Vector axis_y;
  Vector axis_z;

  Vector up;

  float viewport_width;
  float viewport_height;

  float fov;

  Camera(Vector p, Vector o) : position(p), orientation(o) {}

  // fonction qui permet de calibrer la caméra en fonction la valeur courante de ses attributs
  void calibrate()
  {
    axis_z = orientation;
    axis_x = Vector(viewport_width * fov / viewport_height);
    axis_y = axis_x.cross(axis_z).normalize() * fov;
  }
};

// structure d'une image
struct Image
{
  int width;  // largeur de l'image
  int height; // hauteur de l'image
  int count;  // nombre de pixels
  int index;  // index d'un des pixels

  double size; // poids en mémoire (en mégaoctets)

  // pointeur vers une séquence de pixels sous forme vectorielle
  Vector* pixel;

  // constructeurs
  Image() : width(1), height(1) {}
  Image(int w) : width(w), height(w) {}
  Image(int w, int h) : width(w), height(h) {}

  // fonction qui redimensionne l'image
  void resize(int w, int h)
  {
    if (w > 0 && h > 0)
    {
      width = w;
      height = h;

      // calculer le nombre de pixels dans l'image
      count = width * height;

      // calculer la taille de l'espace mémoire (en mégaoctets)
      size = sizeof(Vector) * count / pow(1024.0, 2);

      // allocation de la mémoire pour les pixels de l'image
      pixel = new Vector[count];
    }
  }

  ~Image()
  {
    if (pixel != nullptr)
      delete[] pixel;
  }
};

// variables globales

// déclaration du graphe de scène
std::vector<Sphere> scene;

// orientation initiale de la caméra
Vector camera_orientation(Vector(0, -0.042612, -1).normalize());

// position initiale de la caméra
constexpr Vector camera_position(50, 50, 300);

// déclaration de la caméra utilisée pour rendre la scène
Camera camera(camera_position, camera_orientation);

// déclaration d'une image
Image image;

// source d'entropie
std::random_device rd;

// générateur de nombres pseudo-aléatoires (algorithme mersenne twister)
std::mt19937 rng{rd()};

// distribution uniforme entre 0 et 1
std::uniform_real_distribution<double> random01{0.0, 1.0};

// traitement de la couleur d'un pixel
int format_color_component(double value)
{
  // appliquer la correction gamma
  value = pow(clamp(value), gamma_correction);

  // convertir la valeur dans l'espace de couleur
  value = value * 255 + 0.5;

  // conversion numérique de réel vers entier
  return static_cast<int>(value);
}

// fonction qui valide s'il y a intersection entre un rayon et les géométries de la scène
// retourne l'intersection la plus près de la caméra (distance et index de l'élément)
bool raycast(const Ray& ray, double& distance, int& id)
{
  // variable temporaire pour la distance d'une intersection entre un rayon et une sphère
  double d;

  // initialiser la distance à une valeur suffisamment éloignée pour qu'on la considère comme l'infinie
  double infinity = distance = 1e20;

  // nombre d'éléments dans la scène
  int n = static_cast<int>(scene.size());

  // parcourir tous les éléments de la scène
  for (int index = 0; index < n; ++index)
  {
    // test d'intersection entre le rayon et la géométrie à cet index
    d = scene[index].intersect(ray);

    // valider s'il y a eu intersection et si la distance est inférieure aux autres intersections
    if (d && d < distance)
    {
      // nouvelle valeur courante de la distance et l'index de l'intersection la plus rapprochée de la caméra
      distance = d;
      id = index;
    }
  }

  // il y a eu intersection si la distance est plus petite que l'infini
  if (distance < infinity)
    return true;
  else
    return false;
}

// fonction récursive qui calcule la radiance
Vector compute_radiance(const Ray& ray, int depth)
{
  // valeur de la radiance
  Vector radiance;

  // distance de l'intersection
  double distance;

  // identifiant de la géométrie en intersection
  int id = 0;

  // valider s'il n'y a pas intersection
  if (!raycast(ray, distance, id))
    return Vector(); // couleur par défault (noir)

  // référence sur une géométrie en intersection avec un rayon
  const Sphere& obj = scene[id];

  // calculer les coordonnées du point d'intersection
  Vector x = ray.origin + ray.direction * distance;

  // calculer la normale au point d'intersection
  Vector n = (x - obj.position).normalize();

  // ajustement de la direction de la normale
  Vector na = n.dot(ray.direction) < 0 ? n : n * -1;

  // isoler la composante de couleur la plus puissante
  Vector f = obj.color;
  double threshold = f.x > f.y && f.x > f.z ? f.x : f.y > f.z ? f.y : f.z;

  // valider si la limite du nombre de récursions est atteinte
  if (++depth > max_depth)
  {
    // test de probabilité
    if (random01(rng) < threshold)
      f = f * (1 / threshold);
    else
      return obj.emission;
  }

  if (obj.material == SurfaceType::diffuse)
  {
    // matériau avec réflexion diffuse

    double r1 = 2 * M_PI * random01(rng);
    double r2 = random01(rng);
    double r2s = sqrt(r2);

    Vector w = na;
    Vector u = ((fabs(w.x) > 0.1 ? Vector(0, 1) : Vector(1)).cross(w)).normalize();
    Vector v = w.cross(u);
    Vector d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).normalize();

    radiance = obj.emission + f.multiply(compute_radiance(Ray(x, d), depth));

    return radiance;
  }
  else if (obj.material == SurfaceType::specular)
  {
    // matériau avec réflexion spéculaire

    radiance = obj.emission + f.multiply(compute_radiance(Ray(x, ray.direction - n * 2.0 * n.dot(ray.direction)), depth));

    return radiance;
  }
  else if (obj.material == SurfaceType::refraction)
  {
    // matériau avec réflexion réfraction

    Ray reflection_ray(x, ray.direction - n * 2.0 * n.dot(ray.direction));

    bool into = n.dot(na) > 0;

    double ior = 1.5; // indice de réfraction du verre
    double nc = 1.0;
    double nt = ior;
    double nnt = into ? nc / nt : nt / nc;
    double ddn = ray.direction.dot(na);
    double cos2t;

    if ((cos2t = 1.0 - nnt * nnt * (1.0 - ddn * ddn)) < 0.0)
    {
      radiance = obj.emission + f.multiply(compute_radiance(reflection_ray, depth));

      return radiance;
    }

    Vector tdir = (ray.direction * nnt - n * ((into ? 1.0 : -1.0) * (ddn * nnt + sqrt(cos2t)))).normalize();

    // effet de fresnel
    double a = nt - nc;
    double b = nt + nc;
    double r0 = a * a / (b * b);
    double c = 1.0 - (into ? -ddn : tdir.dot(n));
    double re = r0 + (1.0 - r0) * c*c*c*c*c;
    double tr = 1 - re;
    double p = 0.25 + 0.5 * re;
    double rp = re / p;
    double tp = tr / (1.0 - p);

    radiance = obj.emission + f.multiply(depth > 2 ? (random01(rng) < p ?
       compute_radiance(reflection_ray, depth) * rp : compute_radiance(Ray(x, tdir), depth) * tp) :
       compute_radiance(reflection_ray, depth) * re + compute_radiance(Ray(x, tdir), depth) * tr);

    return radiance;
  }
  else
  {
    return radiance;
  }
}

// fonction qui permet de sauvegarder des pixels dans un fichier image (format .ppm)
void save_image_file(int width, int height, int ray_per_pixel, const Vector* pixel)
{
  // nom du fichier image de type .ppm (portable pixmap)
  std::stringstream ss;
  ss << "image" << width << "x" << height << "_" << ray_per_pixel << ".ppm";
  std::string filename = ss.str();

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
  for (int index = 0; index < width * height; ++index)
  {
    // écrire la couleur du pixel dans le fichier image
    file << static_cast<std::uint32_t>(format_color_component(pixel[index].x)) << " ";
    file << static_cast<std::uint32_t>(format_color_component(pixel[index].y)) << " ";
    file << static_cast<std::uint32_t>(format_color_component(pixel[index].z)) << " ";
  }

  // fermeture du fichier
  file.close();
}

// fonction d'initialisation de la scène
void init()
{
  std::cout << "scene setup" << std::endl;

  constexpr double anchor = 1e5;
  constexpr double wall_radius = anchor;

  constexpr double box_size_x = 100.0;
  constexpr double box_size_y = 81.6;
  constexpr double box_size_z = 81.6;

  constexpr double box_x_min = 0.0;
  constexpr double box_x_max = box_size_x;
  constexpr double box_y_min = 0.0;
  constexpr double box_y_max = box_size_y;
  constexpr double box_z_min = 0.0;
  constexpr double box_z_max = box_size_z;

  constexpr double box_center_x = (box_x_max - box_x_min) / 2.0;
  constexpr double box_center_y = (box_y_max - box_y_min) / 2.0;
  constexpr double box_center_z = (box_z_max - box_z_min) / 2.0;

  // vider la scène de son contenu
  scene.clear();

  // génération du contenu de la scène
  scene.insert(scene.begin(), {

    // approximation d'une boîte de Cornell avec des sphères surdimensionnées qui simulent des surfaces planes
    Sphere(wall_radius, Vector( box_center_x,  anchor,            box_size_z),   Vector(), Vector(0.75, 0.75, 0.75), SurfaceType::diffuse),    // plancher
    Sphere(wall_radius, Vector( box_center_x, -anchor+box_size_y, box_size_z),   Vector(), Vector(0.75, 0.75, 0.75), SurfaceType::diffuse),    // plafond
    Sphere(wall_radius, Vector( anchor+1,      box_center_y,      box_size_z),   Vector(), Vector(0.75, 0.25, 0.25), SurfaceType::diffuse),    // mur gauche
    Sphere(wall_radius, Vector( box_center_x,  box_center_y,      anchor),       Vector(), Vector(0.25, 0.75, 0.25), SurfaceType::diffuse),    // mur arrière
    Sphere(wall_radius, Vector(-anchor+99,     box_center_y,      box_size_z),   Vector(), Vector(0.25, 0.25, 0.75), SurfaceType::diffuse),    // mur droit
    Sphere(wall_radius, Vector( box_center_x,  box_center_y,     -anchor+170),   Vector(), Vector(0.0,  0.0,  0.0),  SurfaceType::diffuse),    // mur avant

    // ensemble des sphères situées à l'intérieur de la boîte de Cornell
    Sphere(22.5,        Vector( 30,            30,                40),           Vector(), Vector(1.0, 1.0, 1.0),    SurfaceType::specular),   // sphère mirroir
    Sphere(17.5,        Vector( 75,            40,                75),           Vector(), Vector(1.0, 1.0, 1.0),    SurfaceType::refraction), // sphère de verre

    Sphere(600,  Vector(box_center_x, 600.0 + box_size_z - 0.27, box_size_z), Vector(15, 15, 15), Vector(0.0, 0.0, 0.0), SurfaceType::diffuse) // sphère lumineuse
  });

  // allocation de la mémoire de l'image en fonction des paramètres du programme
  image.resize(image_width, image_height);

  std::cout << "image resize to " << image.width << "x" << image.height << " (" << image.count << " pixels) " << image.size << " MB)" << std::endl;

  // calibration de la caméra
  camera.viewport_width = image.width;
  camera.viewport_height = image.height;
  camera.fov = camera_fov;
  camera.calibrate();
}

// fonction appelée quand le rendu de la scène est terminée
void post_render()
{
  // écrire les pixels dans un fichier image
  save_image_file(image.width, image.height, ray_per_pixel, image.pixel);

  std::cout << "raytracer task is done" << std::endl;
}

// fonction de rendu de la scène
void render()
{
  std::cout << "render start" << std::endl;

  unsigned short x = 0;

  int index, y, s, sx, sy = 0;

  float progression = 0.0f;

  double r1, r2 = 0.0;
  double dx, dy = 0.0;

  Vector radiance;

  Vector distance;

  // itération sur les rangées de pixels
  for (y = 0; y < image_height; ++y)
  {
    // calculer le pourcentage de progression
    progression = 100.0f * y / (image_height - 1.0f);

    // afficher le pourcentage de progression du rendu dans la console
    fprintf(stderr,"\rraytracing (%d rays per pixel) : %4.1f %%", ray_per_pixel, progression);

    // itération sur les colonnes de pixels
    for (x = 0; x < image_width; ++x)
    {
      // déterminer l'index du pixel
      index = (image_height - y - 1) * image_width + x;

      // itération sur les rangées du bloc de 2x2 échantillons
      for (sy = 0; sy < 2; ++sy)
      {
        // itération sur les colonnes du bloc de 2x2 échantillons
        for (sx = 0; sx < 2; ++sx)
        {
          // initialiser la radiance
          radiance = Vector();

          // itération des sur les rayons par pixel
          for (s = 0; s < ray_per_pixel; ++s)
          {
            // filtre de la tente
            r1 = 2.0 * random01(rng);
            dx = r1 < 1.0 ? sqrt(r1) - 1.0 : 1.0 - sqrt(2.0 - r1);

            r2 = 2.0 * random01(rng);
            dy = r2 < 1.0 ? sqrt(r2) - 1.0 : 1.0 - sqrt(2.0 - r2);

            // calculer la distance de ...
            distance = camera.axis_x * (((sx + 0.5 + dx) / 2.0 + x) / image_width - 0.5) +
                       camera.axis_y * (((sy + 0.5 + dy) / 2.0 + y) / image_height - 0.5) + camera.axis_z;

            // appel récursif du calcul de la radiance
            radiance = radiance + compute_radiance(Ray(camera.position + distance * 140, distance.normalize()), 0) * (1.0 / ray_per_pixel);
          }

          image.pixel[index] = image.pixel[index] + Vector(clamp(radiance.x), clamp(radiance.y), clamp(radiance.z)) * 0.25;
        }
      }
    }
  }

  std::cout << "\nrender done" << std::endl;
}

// fonction de mise à jour
void update()
{
  auto t1 = std::chrono::high_resolution_clock::now();

  // rendu de la scène
  render();

  auto t2 = std::chrono::high_resolution_clock::now();

  // temps de calcul
  auto render_time = t2 - t1;

  std::cout << "render time : " << std::chrono::duration_cast<std::chrono::seconds>(render_time).count() << "s" << std::endl;
}

// fonction principale du programme
int main(int argc, char* argv[])
{
  std::cout << "raytracer start" << std::endl;

  std::cout << "parse program arguments:" << std::endl;

  std::cout << "argc:\t" << argc << std::endl;

  for (int index = 0; index < argc; ++index)
    std::cout << "arg[" << index << "]:\t" << argv[index] << std::endl;

  switch (argc)
  {
    case 1:
      image_width = 256;
      image_height = 256;
      ray_per_pixel = 16;
      break;

    case 2:
      image_width = 256;
      image_height = 256;
      ray_per_pixel = atoi(argv[1]);
      break;

    case 3:
      image_width = atoi(argv[1]);
      image_height = image_width;
      ray_per_pixel = atoi(argv[2]);
      break;

    default:
    case 4:
      image_width = atoi(argv[1]);
      image_height = atoi(argv[2]);
      ray_per_pixel = atoi(argv[3]);
      break;
  }

  std::cout << "program init done" << std::endl;

  // initialisation de la scène
  init();

  // faire un rendu de la scène par lancer de rayons
  update();

  // procédure post-rendu (sauvegarde de l'image et désallocation de la mémoire)
  post_render();
}
