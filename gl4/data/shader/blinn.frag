#ifndef LIGHT_COUNT
#define LIGHT_COUNT 8
#endif

// exactly the same as gl_LightSourceParameters
struct LightSource {
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec4 position;  
  vec3 spotDirection;
  float spotExponent;
  float spotCutoff;
  float spotCosCutoff;
  float constantAttenuation;
  float linearAttenuation;
  float quadraticAttenuation;
};

struct LightModel{
  vec4 ambient;
  bool localViewer; // only has meaning if lighting is in view space
};

struct LightProduct {
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
};

struct Material {
  vec4 emission;
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  float shininess;
};

uniform LightModel lightModel;
uniform LightSource lights[LIGHT_COUNT];
uniform Material material;

void light(vec3 vertex, vec3 normal, vec3 v2e, LightSource source,
  Material material, out LightProduct product) {
  product = LightProduct(vec4(0), vec4(0), vec4(0));
  // skip blank light
  if (source.constantAttenuation == 0.0) return;

  vec3 v2l = source.position.w == 0.0 ? source.position.xyz : source.position.xyz - vertex;
  vec3 l = normalize(v2l);
  vec3 n = normal;
  vec3 v = v2e;

  // spot light effect
  float spotEffect = 1.0;
  if (source.position.w == 1.0 && source.spotCutoff >= 0.0 && source.spotCutoff <= 90.0) {
    float nldotd = dot(-l, source.spotDirection);
    if (nldotd < source.spotCosCutoff) return;
    spotEffect = pow(clamp(nldotd, 0.0, 1.0), source.spotExponent);
  }

  // attenuation
  float atten = 1.0; 
  if(source.position.w == 1.0)
  {
    float dist = length(v2l);
    atten = 1.0 / (source.constantAttenuation + source.linearAttenuation *
        dist + source.quadraticAttenuation * dist * dist);
  }

  float visibility = atten * spotEffect;

  // ambient
  product.ambient = visibility * source.ambient * material.ambient;

  // diffuse
  float ndotl = dot(n, l);
  if (ndotl <= 0.0) return;
  ndotl = clamp(ndotl, 0.0, 1.0);
  product.diffuse = visibility * ndotl * source.diffuse * material.diffuse; 

  // specular
  vec3 h = normalize(l + v);
  float ndoth = dot(h, n);
  if(ndoth <= 0.0) return;
  ndoth = clamp(ndoth, 0.0, 1.0);

  product.specular = visibility * pow(ndoth, material.shininess) * source.specular * material.specular;
}

LightProduct getLightProduct(vec3 vertex, vec3 normal, vec3 camera, Material material,
    LightSource lights[LIGHT_COUNT]){
  vec3 v2e = lightModel.localViewer ? normalize(camera - vertex) : vec3(0,0,1);
  LightProduct product = LightProduct(vec4(0),vec4(0),vec4(0));

  for (int i = 0; i < LIGHT_COUNT; i++) {
    LightProduct currentProduct = LightProduct(vec4(0),vec4(0),vec4(0));
    light(vertex, normal, v2e, lights[i], material, currentProduct);
    product.diffuse += currentProduct.diffuse;
    product.specular += currentProduct.specular;
    product.ambient += currentProduct.ambient;
  }
  return product;
}

// the most simple case, in view space
vec4 blinn(vec3 vertex, vec3 normal){
  LightProduct product = getLightProduct(vertex, normal, vec3(0.0), material, lights);
  vec4 color = material.emission + lightModel.ambient * material.ambient +
    product.ambient + product.diffuse + product.specular;
  return color;
}

// some shader(such as gbuffer) get material from texture, in view space
vec4 blinn(vec3 vertex, vec3 normal, Material material){
  LightProduct product = getLightProduct(vertex, normal, vec3(0.0), material, lights);
  vec4 color = material.emission + lightModel.ambient * material.ambient +
    product.ambient + product.diffuse + product.specular;
  return color;
}

// some shader(such as normal map) don't use view space light positions, in
// whatever space excpet view
vec4 blinn(vec3 vertex, vec3 normal, vec3 camera, LightSource lights[LIGHT_COUNT]){
  // will this code be optimized by opengl ? only light position is from uniform
  LightProduct product = getLightProduct(vertex, normal, camera, material, lights);
  vec4 color = material.emission + lightModel.ambient * material.ambient +
    product.ambient + product.diffuse + product.specular;
  return color;
}