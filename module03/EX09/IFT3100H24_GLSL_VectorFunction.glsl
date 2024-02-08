// IFT3100H24_GLSL_VectorFunction.glsl
// Exemples de fonctions applicables aux variables de type vecteur en GLSL.

// 1. calculer la magnitude d'un vecteur (sa longueur dans l'espace)
float lenght_of_vector = length(vec3(1.0, 2.0, 3.0));

// 2. normaliser un vecteur (donne un vecteur dont la magnitude est de 1 unité)
vec3 normalized_vector = normalize(vec3(1.0, 2.0, 3.0));

// 3. calculer le produit vectoriel entre 2 vecteurs
vec3 axis_x = vec3(1.0, 0.0, 0.0);
vec3 axis_y = vec3(0.0, 1.0, 0.0);
vec3 axis_z = cross(axis_x, axis_y; // le résultat sera vec3(0.0, 0.0, 1.0)

// 4. calculer la réflexion diffuse d'un matériau
vec3 normal = vec3(...); // normale du sommet transformée dans l'espace de la vue
vec3 light = vec3(...);  // vecteur normalisé en direction d'une lumière
float n_dot_l = dot(normal, light);

// 5. calculer la direction de la réflexion d'une lumière
vec3 r = reflect(-light, normal);

// 6. calculer la réflexion spéculaire d'un matériau
float p = ...; // facteur de puissance spéculaire
vec3 v = vec3(...); // vecteur normalisé en direction d'une caméra
float r_dot_v = pow(dot(r, v) p);

// 7. calculer des couleurs par mixage (interpolation) entre deux autres couleurs
vec3 color_ambient  = mix(vec3(0.0), vec3(1.0), 0.1); // gris foncé
vec3 color_diffuse  = mix(vec3(0.0), vec3(1.0), 0.5); // gris
vec3 color_specular = mix(vec3(0.0), vec3(1.0), 1.0); // blanc

// 8. calculer la couleur d'un fragment de la surface d'un matériau (modèle d'illumination de Phong)
vec3 fragment_color = color_ambient + n_dot_l * color_diffuse + r_dot_v * color_specular;
