#ifndef LIGHT_COUNT
#define LIGHT_COUNT 8
#endif

//#version 430 core
in VS_OUT{
  vec3 tangentVertex;
  vec3 tangentCamera;
  vec2 texcoord;
  LightSource tangentLights[LIGHT_COUNT];
} fs_in;

uniform sampler2D normalMap;

out vec4 fragColor;

void main(void)
{
  vec3 normal = texture(normalMap, fs_in.texcoord).xyz * 2 - 1; 
  fragColor = blinn(fs_in.tangentVertex, normal, fs_in.tangentCamera, fs_in.tangentLights);
  //fragColor = vec4(normalize(fs_in.tangentLights[0].position.xyz) * 0.5 + 0.5, 1);
}
