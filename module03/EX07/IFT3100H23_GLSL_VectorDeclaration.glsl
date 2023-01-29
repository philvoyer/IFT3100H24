// IFT3100H23_GLSL_VectorDeclaration.glsl
// Exemples de déclaration de variables de type vecteur en GLSL.

// 1. déclaration d'un vecteur pour l'origine d'un espace
vec3 origin = vec3(0.0, 0.0, 0.0);

// 2. déclaration d'un vecteur avec trois composantes qui ont la même valeur initiale
vec3 vector_of_1 = vec3(1.0); // équivalent à vec3(1.0, 1.0, 1.0)

// 3. déclaration d'un vecteur avec les trois composantes de la couleur blanche dans l'espace RGB
vec3 color_white_rgb = vec3(1.0);

// 4. déclaration d'un vecteur avec les quatre composantes de la couleur blanche dans l'espace RGBA
vec4 color_white_rgba = vec4(1.0);

// 5. déclaration d'un vecteur avec trois dimensions (nombres entiers)
ivec3 vector_3d_integer = ivec3(1, 2, 3);

// 6. déclaration d'un vecteur avec deux dimensions (nombres réels)
vec2 vector_2d = vec2(1.0, 2.0);

// 7. déclaration d'un vecteur avec trois dimensions (nombres réels)
vec3 vector_3d = vec3(1.0, 2.0, 3.0);

// 8. déclaration d'un vecteur avec quatre dimensions (nombres réels)
vec4 vector_4d = vec4(1.0, 2.0, 3.0, 4.0);

// 9. déclaration d'un vecteur avec les quatre composantes d'une position 3D homogène (pour multiplication avec matrice 4x4)
vec4 position = vec4(vec3(0.0, 0.0, 1.0), 1.0);

// 10. constantes de couleur (espace de couleur RGBA encodé dans un vecteur 4D)
const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
const vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
const vec4 grey  = vec4(0.5, 0.5, 0.5, 1.0);
const vec4 red   = vec4(1.0, 0.0, 0.0, 1.0);
const vec4 green = vec4(0.0, 1.0, 0.0, 1.0);
const vec4 blue  = vec4(0.0, 0.0, 1.0, 1.0);
