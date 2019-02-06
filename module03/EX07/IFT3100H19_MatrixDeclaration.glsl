// IFT3100H19_MatrixDeclaration.glsl
// Exemples de déclaration de variables de type matrice en GLSL.

// 1. matrice identité de dimension 3 par 3
mat3 ma33 = mat3(
  1.0, 0.0, 0.0,  // colonne #1
  0.0, 1.0, 0.0,  // colonne #2
  0.0, 0.0, 1.0); // colonne #3

// 2. matrice identité de dimension 3 par 3
mat3 mb33(1.0);

// 3. matrice identité de dimension 4 par 4
mat4 ma44 = mat4(
  1.0, 0.0, 0.0, 0.0,  // colonne #1
  0.0, 1.0, 0.0, 0.0,  // colonne #2
  0.0, 0.0, 1.0, 0.0,  // colonne #3
  0.0, 0.0, 0.0, 1.0); // colonne #4

// 4. matrice identité de dimension 4 par 4
mat4 mb44(1.0);
