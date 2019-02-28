// IFT3100H19_TextureSampling.glsl
// Exemple d'une section de code pour échantillonner une texture en GLSL.

// coordonnées de mapping
in vec2 surface_texcoord;

// texture diffuse
uniform sampler2D texture_diffuse;

// échantillonnage de la texture

// échantillonner une couleur RGBA
vec4 sample4 = texture(texture_diffuse, surface_texcoord);

// échantillonner une couleur RGB
vec3 sample3 = texture(texture_diffuse, surface_texcoord).rgb;

// échantillonner les composantes rouge et verte de la couleur
vec3 sample2 = texture(texture_diffuse, surface_texcoord).rg;

// échantillonner le composante rouge de la couleur
float sample1 = texture(texture_diffuse, surface_texcoord).r;
