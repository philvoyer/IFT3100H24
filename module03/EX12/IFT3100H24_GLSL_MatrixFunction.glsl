// IFT3100H24_GLSL_MatrixFunction.glsl
// Exemples de fonctions applicables aux variables de type matrice en GLSL.

// déclaration d'une matrice 4x4
mat4 m = mat4(...);

// 1. calculer une matrice transposée
mat4 m1 = transpose(m);

// 2. calculer une matrice inversée
mat4 m2 = inverse(m);

// 3. calculer le déterminant d'une matrice
float d = determinant(m);

// 4. produit matriciel entre 2 matrices avec l'opérateur *
mat4 m3 = m1 * m2;
