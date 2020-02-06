// IFT3100H20_MatrixFunction.glsl
// Exemples de fonctions applicables aux variables de type matrice en GLSL.

// variable locale
mat4 m = mat4(/*...*/);

// 1. transposition d'une matrice
mat4 m1 = transpose(m);

// 2. inversion d'une matrice
mat4 m2 = inverse(m);

// 3. déterminant d'une matrice
float d = determinant(m);

// 4. produit matriciel (opérateur *)
mat4 m3 = m1 * m2;
