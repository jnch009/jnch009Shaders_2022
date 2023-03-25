#version 410
layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;
uniform float time;
out vec2 fragUV;
void main() 
{
	/*For the GL_position that we're looking at, we are updating it to the
	pixel at the UV coordinate offset by time
	*/
	gl_Position = vec4(pos, 1.0);

	/*This is saying, get the fragment at the UV coordinate offset by time*/
	fragUV = vec2(uv.x, 1.0 - uv.y) + vec2(1, 0.0) * time;
}