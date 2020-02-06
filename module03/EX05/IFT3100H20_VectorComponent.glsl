// IFT3100H20_VectorComponent.glsl
// Exemples d’accès aux composantes d’un vecteur en GLSL.

// variables locales
vec3 v = vec3(1.0, 2.0, 3.0);
vec3 result;
float component;

// 1. lecture par index de composante
component = v[0];
component = v[1];
component = v[2];

// 2. écriture par index de composante
v[0] = 1.0;
v[1] = 2.0;
v[2] = 3.0;

// 3. lecture par étiquette de composante de transformation
component = v.x;
component = v.y;
component = v.z;

// 4. écriture par étiquette de composante de transformation
v.x = 1.0;
v.y = 2.0;
v.z = 3.0;

// 5. lecture par étiquette de composante de couleur
component = v.r;
component = v.g;
component = v.b;

// 6. écriture par étiquette de composante de couleur
v.r = 1.0;
v.g = 2.0;
v.b = 3.0;

// 7. lecture par étiquette de composante de texture (uvw ou stp)
component = v.u;
component = v.v;
component = v.w;

// 8. écriture par étiquette de composante de texture
v.u = 1.0;
v.v = 2.0;
v.w = 3.0;

// 9. swizzle par étiquette de composante de transformation
result = v.xyz; // result = (1.0, 2.0, 3.0)
result = v.zyx; // result = (3.0, 2.0, 1.0)
result = v.xzy; // result = (1.0, 3.0, 2.0)
result = v.yxz; // result = (2.0, 1.0, 3.0)
result = v.xxx; // result = (1.0, 1.0, 1.0)

// 10. swizzle par étiquette de composante de couleur
result = v.rgb; // result = (1.0, 2.0, 3.0)
result = v.bgr; // result = (3.0, 2.0, 1.0)
result = v.rbg; // result = (1.0, 3.0, 2.0)
result = v.grb; // result = (2.0, 1.0, 3.0)
result = v.rrr; // result = (1.0, 1.0, 1.0)

// 11. swizzle par étiquette de composante de texture
result = v.uvw;  // result = (1.0, 2.0, 3.0)
result = v.wvu;  // result = (3.0, 2.0, 1.0)
result = v.uwv;  // result = (1.0, 3.0, 2.0)
result = v.vuw;  // result = (2.0, 1.0, 3.0)
result = v.uuu;  // result = (1.0, 1.0, 1.0)
