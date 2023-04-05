#version 410

uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 meshCol;
in vec3 fragNrm;
out vec4 outCol;
/*The math here is actually backwards
If light points towards the fragment then areas facing the light get darker
Therefore we pass in the lightDir backwards to cancel it out
*/
void main(){
      vec3 normal = normalize(fragNrm);
      float lightAmt = max(0.0, dot(normal, lightDir)); // prevent negative brightness
      vec3 fragLight = lightCol * lightAmt;
      outCol = vec4(meshCol * fragLight, 1.0);
}