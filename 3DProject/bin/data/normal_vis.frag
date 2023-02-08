#version 410

uniform vec3 lightDir;
uniform vec3 lightCol;
in vec3 fragNrm;

out vec4 outCol;

void main()
{
      // normalize function will transform a vector into a magnitude of 1
      vec3 normal = normalize(fragNrm);
      outCol = vec4(normal, 1.0f);
}