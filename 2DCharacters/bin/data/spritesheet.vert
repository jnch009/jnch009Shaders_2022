#version 410
layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;
uniform vec2 size;
uniform vec2 offset;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
out vec2 fragUV;
void main()
{
	gl_Position = proj * view * model * vec4(pos, 1.0);
	/* vec2(uv.x, 1.0 - uv.y) * size = captures all the coordinates of the character*/
	/* (offset * size) = moves to the appropriate sprite location */
	fragUV = vec2(uv.x, 1.0 - uv.y) * size + (offset * size);
}