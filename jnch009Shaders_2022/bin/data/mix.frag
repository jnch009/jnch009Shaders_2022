#version 410
uniform sampler2D parrotTex;
uniform sampler2D checkerboard;
in vec2 fragUV;
out vec4 outCol;
void main() 
{
	vec4 parrot = texture(parrotTex, fragUV);
	vec4 cboard = texture(checkerboard, fragUV);
	outCol = mix(cboard, parrot, cboard.r);
}