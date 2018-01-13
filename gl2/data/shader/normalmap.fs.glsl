varying vec3 lightPos;
uniform sampler2D normalMap;

void main(void)
{
  vec3 N = texture2D(normalMap, gl_TexCoord[0].xy).xyz * 2.0 - 1.0; 
  N = normalize(N);
  vec3 L = normalize(lightPos);
  float dotNL = dot(N, L);
  vec4 color = gl_FrontMaterial.diffuse * dotNL * gl_LightSource[0].diffuse;
  gl_FragColor = vec4(color.xyz, gl_FrontMaterial.diffuse.w);
}
