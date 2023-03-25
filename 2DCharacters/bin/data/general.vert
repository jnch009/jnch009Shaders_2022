#version 410
layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
out vec2 fragUV;
void main()
{
      gl_Position = proj * view * model * vec4(pos, 1.0);
      /* OpenGL by default expects image data to be read from bottom to top */
      /* Images generally go from top to bottom which is why we need to invert */
      fragUV = vec2(uv.x, 1.0 - uv.y);
}