// IFT3100H23_TextureSampling.glsl
// Exemple d'une section de code pour échantillonner une texture en GLSL.

// exemple de déclaration des coordonnées de mapping en provenance d'une structure de sommets
in vec2 surface_texcoord;

// exemple d'un échantillonneur de texture
uniform sampler2D texture_diffuse;

// échantillonnage de la texture

// échantillonner une couleur RGBA
vec4 sample4 = texture(texture_diffuse, surface_texcoord);

// échantillonner une couleur RGB
vec3 sample3 = texture(texture_diffuse, surface_texcoord).rgb;

// échantillonner les composantes rouge et verte de la couleur
vec2 sample2 = texture(texture_diffuse, surface_texcoord).rg;

// échantillonner le composante rouge de la couleur
float sample1 = texture(texture_diffuse, surface_texcoord).r;

// échantillonner une couleur RGB avec un swizzle des composantes
vec3 sample3 = texture(texture_diffuse, surface_texcoord).brg;

// échantillonner une couleur RGBA avec d'autres étiquettes de composante
vec3 sample4 = texture(texture_diffuse, surface_texcoord).rgba;
vec3 sample4 = texture(texture_diffuse, surface_texcoord).xyzw;
vec3 sample4 = texture(texture_diffuse, surface_texcoord).stpq;
