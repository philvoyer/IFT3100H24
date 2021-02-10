// IFT3100H21_VectorDeclaration.glsl
// Exemples de déclaration de variables de type vecteur en GLSL.

// 1. déclaration d'un vecteur avec trois dimensions qui ont la même valeur initiale
vec3 vector_of_1 = vec3(1.0); // équivalent à vec3(1.0, 1.0, 1.0)

// 2. déclaration d'un vecteur avec les trois composantes de la couleur blanche dans l'espace RGB
vec3 color_white_rgb = vec3(1.0);

// 3. déclaration d'un vecteur avec les quatre composantes de la couleur blanche dans l'espace RGBA
vec4 color_white_rgba = vec4(1.0);

// 4. déclaration d'un vecteur avec trois dimensions (nombres entiers)
ivec3 ivector_3d = ivec3(1, 2, 3);

// 5. déclaration d'un vecteur avec deux dimensions (nombres réels)
vec2 vector_2d = vec2(1.0, 2.0);

// 6. déclaration d'un vecteur avec trois dimensions (nombres réels)
vec3 vector_3d = vec3(1.0, 2.0, 3.0);

// 7. déclaration d'un vecteur avec quatre dimensions (nombres réels)
vec4 vector_4d = vec4(1.0, 2.0, 3.0, 4.0);

// 8. déclaration d'un vecteur avec les quatre composantes d'une position 3D homogène
vec4 position = vec4(vec3(0.0, 0.0, 1.0), 1.0);
