// IFT3100H19_ConstantDeclaration.glsl
// Exemples de déclaration de variables constantes en GLSL.

// 1. constantes scalaires (nombres entiers)
const int zero = 0;
const int one = 1;

// 2. constantes scalaires (nombres réels)
const float two = 2.0;
const float pi = 3.14159;
const float phi = 1.61803;

// 3. constantes de couleur (vecteur 4D)
const vec4 black = vec4(0.0, 0.0, 0.0, 1.0);
const vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
const vec4 grey  = vec4(0.5, 0.5, 0.5, 1.0);
const vec4 red   = vec4(1.0, 0.0, 0.0, 1.0);
const vec4 green = vec4(0.0, 1.0, 0.0, 1.0);
const vec4 blue  = vec4(0.0, 0.0, 1.0, 1.0);

// 4. constantes de transformation (vecteur et matrice)
const vec3 origin = vec3(0.0);
const mat4 identity = mat4(1.0);
