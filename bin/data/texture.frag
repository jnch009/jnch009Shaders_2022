#version 410
uniform sampler2D parrotTex;
in vec2 fragUV;
out vec4 outCol;
void main()
{
      /*In this frag shader, we sample the color from the UV coordinate
      we passed through from our vertex shader.
      */
      outCol = texture(parrotTex, fragUV);
}