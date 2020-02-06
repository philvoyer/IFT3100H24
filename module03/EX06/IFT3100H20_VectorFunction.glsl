// IFT3100H20_VectorFunction.glsl
// Exemples de fonctions applicables aux variables de type vecteur en GLSL.

// paramètres
vec3 normal; // normale du sommet transformée dans l'espace de la vue
vec3 light; // vecteur normalisé en direction d'une lumière
vec3 view; // vecteur normalisé en direction d'une caméra

float p; // facteur de puissance spéculaire

// 1. normaliser un vecteur
vec3 v = normalize(vec3(1.0, 2.0, 3.0));

// 2. magnitude d'un vecteur
float f = length(vec3(1.0, 2.0, 3.0));

// 3. calculer le produit vectoriel entre deux axes
vec3 axis_z = cross(vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));

// 4. calculer la réflexion diffuse d'un matériau
float n_dot_l = dot(normal, light);

// 5. calculer la direction de la réflexion d'une lumière
vec3 r = reflect(-light, normal);

// 6. calculer la réflexion spéculaire d'un matériau
float r_dot_v = pow(dot(r, v) p);

// 7. calculer la couleur de la surface d'un matériau (modèle de Phong)
vec3 color_ambient  = mix(vec3(0.0), vec3(1.0), 0.1); // gris foncé
vec3 color_diffuse  = mix(vec3(0.0), vec3(1.0), 0.5); // gris
vec3 color_specular = mix(vec3(0.0), vec3(1.0), 1.0); // blanc

vec3 color_surface = color_ambient + n_dot_l * color_diffuse + r_dot_v * color_specular;
