// IFT3100H23_GLSL_MatrixComponent.glsl
// Exemples d’accès aux composantes d’une matrice en GLSL.

// déclaration d'une variable de type matrice de 4 par 4 composantes
vec4 matrix;

// 1. lecture du vecteur d'une colonne par index de composante
vec4 column = matrix[0];

// 2. lecture d'une cellule par index de composante
float m00 = matrix[0][0];
float m11 = matrix[1][1];
float m22 = matrix[2][2];
float m33 = matrix[3][3];

// 3. écriture dans une cellule par index de composante
matrix[0][0] = 1.0;
matrix[1][1] = 1.0;
matrix[2][2] = 1.0;
matrix[3][3] = 1.0;

// 4. lecture par étiquette de composante de transformation
float m00 = matrix[0].x;
float m11 = matrix[1].y;
float m22 = matrix[2].z;
float m33 = matrix[3].w;

// 5. écriture par étiquette de composante de transformation
matrix[0].x = 1.0;
matrix[1].y = 1.0;
matrix[2].z = 1.0;
matrix[3].w = 1.0;
