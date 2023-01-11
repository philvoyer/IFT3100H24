// IFT3100H22 ~ pbr_330_fs.glsl

#version 330

#define PI 3.14159265358979323846264338327950288

const float light_attenuation_factor_constant = 0.01;
const float light_attenuation_factor_linear = 0.000001;
const float light_attenuation_factor_quadratic = 0.0000001;

// attributs de surface interpolés à partir des valeurs en sortie du shader de sommet
in vec3 surface_position;
in vec3 surface_normal;
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

// couleurs de réflexion du matériau
uniform vec3 material_color_ambient;
uniform vec3 material_color_diffuse;
uniform vec3 material_color_specular;

// facteur de brillance du matériau
uniform float material_brightness;

// facteur de métallicité du matériau
uniform float material_metallic;

// facteur de rugosité du matériau
uniform float material_roughness;

// facteur d'occlusion ambiante
uniform float material_occlusion;

// indice de réfraction de l'effet de Fresnel;
uniform vec3 material_fresnel_ior;

// facteur d'exposition
uniform float tone_mapping_exposure;

// mode de mappage tonal (Reinhard ou ACES filmic)
uniform bool tone_mapping_toggle;

// facteur gamma
uniform float tone_mapping_gamma;

// texture diffuse
uniform sampler2D texture_diffuse;

// texture métallique
uniform sampler2D texture_metallic;

// texture de rugosité
uniform sampler2D texture_roughness;

// texture d'occlusion ambiante
uniform sampler2D texture_occlusion;

// position d'une source de lumière
uniform vec3 light_position;

// couleur de la source de lumière
uniform vec3 light_color;

// intensité de la source de lumière
uniform float light_intensity;

// fonction de distribution des microfacettes (Trowbridge-Reitz)
float trowbridge_reitz(vec3 n, vec3 h, float roughness)
{
  float a = roughness * roughness;
  float a2 = a * a;
  float ndh = max(dot(n, h), 0.0);
  float ndh2 = ndh * ndh;
  float numerator = a2;
  float denominator = (ndh2 * (a2 - 1.0) + 1.0);
  denominator = denominator * denominator * PI;
  return numerator / denominator;
}

// fonction géométrique pour calculer l'impact de l'occlusion et de l'ombrage des microfacettes (Schlick-Beckmann)
float schlick_beckmann(float costheta, float roughness)
{
  float r = (roughness + 1.0);
  float k = (r * r) / 8.0;
  float numerator = costheta;
  float denominator = costheta * (1.0 - k) + k;
  return numerator / denominator;
}

// fonction géométrique avec occlusion et ombrage combinés (méthode de Smith)
float smith(vec3 n, vec3 l, vec3 v, float roughness)
{
  float ndl = max(dot(n, l), 0.0);
  float ndv = max(dot(n, v), 0.0);
  float shadow = schlick_beckmann(ndl, roughness);
  float occlusion = schlick_beckmann(ndv, roughness);
  return shadow * occlusion;
}

// fonction qui calcul l'effet de Fresnel
vec3 schlick_fresnel(float costheta, vec3 f0)
{
  return f0 + (1.0 - f0) * pow(1.0 - costheta, 5.0);
}

// mappage tonal de la couleur HDR vers LDR (Reinhard tone mapping)
vec3 tone_mapping_reinhard(vec3 x)
{
  return x / (x + vec3(1.0));
}

// mappage tonal de la couleur HDR vers LDR (approximation de la courbe du ACES filmic tone mapping)
vec3 tone_mapping_aces_filmic(vec3 x)
{
  float a = 2.51f;
  float b = 0.03f;
  float c = 2.43f;
  float d = 0.59f;
  float e = 0.14f;
  return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

// fonction qui calcule un modèle d'illumination de type pbr avec brdf de cook-torrance
vec3 brdf_cook_torrance()
{
  // re-normaliser la normale après interpolation
  vec3 n = normalize(surface_normal);

  // calculer la direction de la surface vers la lumière (l)
  vec3 l = normalize(light_position - surface_position);

  // calculer la direction de la surface vers la caméra (v)
  vec3 v = normalize(-surface_position);

  // calculer la direction du demi-vecteur de réflection (h) en fonction du vecteur de lumière (l) et de vue (v)
  vec3 h = normalize(l + v);

  // échantillonage de la texture diffuse
  vec3 texture_sample_diffuse = texture(texture_diffuse, surface_texcoord).rgb;

  // conversion de l'échantillon de la texture diffuse de l'espace gamma vers l'espace linéaire
  texture_sample_diffuse = pow(texture_sample_diffuse, vec3(tone_mapping_gamma));

  // échantillonage de la texture de métallicité
  float texture_sample_metallic = texture(texture_metallic, surface_texcoord).r;

  // échantillonage de la texture de rugosité
  float texture_sample_roughness = texture(texture_roughness, surface_texcoord).r;

  // échantillonage de la texture d'occlusion
  float texture_sample_occlusion = texture(texture_occlusion, surface_texcoord).r;

  // facteurs du matériau combinées avec les échantillons de couleur
  float metallic = material_metallic * texture_sample_metallic;
  float roughness = material_roughness * texture_sample_roughness;
  float occlusion = material_occlusion * texture_sample_occlusion;

  // combiner l'échantillon de la texture diffuse avec la couleur diffuse du matériau
  vec3 albedo = material_color_diffuse * texture_sample_diffuse;

  // calculer la réflexion ambiante
  vec3 ambient = material_color_ambient * albedo * occlusion;

  // distance entre la position de la lumière et de la surface
  float light_distance = length(light_position - surface_position);

  // calculer l'atténuation de l'intensité de la lumière en fonction de la distance
  float light_attenuation = 1.0 / (light_attenuation_factor_constant + light_attenuation_factor_linear * light_distance + light_attenuation_factor_quadratic * (light_distance * light_distance));

  // calculer la radiance de la lumière
  vec3 radiance = light_color * light_attenuation * light_intensity;

  // calculer le niveau de réflexion diffuse (n • l)
  float diffuse_reflection = max(dot(n, l), 0.0);

  // calculer la distribution des microfacettes
  float d = trowbridge_reitz(n, h, roughness);

  // calculer la fonction géométrique
  float g = smith(n, l, v, roughness);

  // reflexion de la surface avec un angle d'incidence nul
  vec3 f0 = material_fresnel_ior;

  // moduler l'effet de Fresnel ave la couleur diffuse en fonction du facteur de métallicité
  f0 = mix(f0, albedo, metallic);

  // calculer l'effet de Fresnel
  vec3 f = schlick_fresnel(max(dot(h, v), 0.0), f0);

  // calculer le numérateur de l'équation (produit des fonctions d, f et g)
  vec3 coor_torrance_numerator = d * f * g;

  // calculer le dénominateur de l'équation (facteur de normalisation)
  float coor_torrance_denominator = 4.0 * max(dot(n, v), 0.0) * diffuse_reflection;

  // calculer le résultat de l'équation avec le numérateur et de dénominateur
  vec3 specular = coor_torrance_numerator / max(coor_torrance_denominator, 0.001);

  // mixer avec la couleur spéculaire du matériau
  specular = specular * material_color_specular;

  // calculer le ratio de réflection de la lumière à partir de l'effet de Fresnel (contribution spéculaire)
  vec3 ks = f;

  // calculer le ratio de réfraction (contribution diffuse) proportionnelement à la contribution spéculaire
  vec3 kd = vec3(1.0) - ks;

  // pondérer la contribution diffuse en fonction du niveau de métallicité de la surface
  kd *= 1.0 - metallic;

  // calculer la réflectance de la fonction BRDF de Cook-Torrance
  vec3 reflectance = (kd * albedo / PI + specular) * radiance * diffuse_reflection;

  // mixer la couleur des composantes de réflexion
  vec3 color = (ambient + reflectance) * material_brightness;

  // retourner la couleur
  return color;
}

void main()
{
  // évaluation du modèle d'illumination
  vec3 color = brdf_cook_torrance();

  // ajustement de la couleur en fonction du facteur d'exposition
  color = vec3(1.0) - exp(-color * tone_mapping_exposure);

  // mappage tonal de la couleur HDR vers LDR
  if (tone_mapping_toggle)
    color = tone_mapping_aces_filmic(color);
  else
    color = tone_mapping_reinhard(color);

  // conversion de couleur de l'espace linéaire vers l'espace gamma
  color = pow(color, vec3(1.0 / tone_mapping_gamma));

  // assigner la couleur final du fragment dans un attribut en sortie
  fragment_color = vec4(color, 1.0);
}
