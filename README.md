# jnch009Shaders_2022
Learning from Practical Shader Development

In order to get the project to run, use VS2019 or earlier. There is currently an issue in openFrameworks in VS2022 with a DLL missing error.

## How to get the project working
1. Install openFrameworks from this link: https://openframeworks.cc/download/older/ and download release v0.10.0, this is very important.
If you do not use v0.10.0, the project will not run.
2. After downloading v0.10.0, extract the folder into the same folder as the repo. DO NOT MODIFY the folder name or the project will not run.
3. Open the folder "jnch009-Practical-Shader-Development" and open the solution file.


## Learnings about UV/Texture coordinates
- OpenGL by default expects image data to be read from bottom to top
- Images generally go from top to bottom which is why we need to invert (ie. 1 - uv.y)

In chapter 3 quad, putting the uv-coordinates as (0,0) with the position (-1, -1)
you'd expect that the bottom left would be black, **however** the bottom left is green
Why?
	- Because you're inverting the y => (0, 1 - 0) = (0, 1) or green

## Understanding Column Major and Row Major multiplication
By default GLM uses column major matrices. 
When doing column major multiplication, we need to *post-multiply* meaning multiply from **right** to **left**
When doing row major multiplication, we do the opposite by going from **left** to **right**

## Coordinate Spaces
1. Model Space (Object Space)
- The coordinate space that is defined in a modelling program
2. World Space
- The coordinate space defined in a game world. Multiply by model matrix.
3. View Space
- The camera's coordinate space. Multiply by view matrix.
4. Clip Space
- Normalized device coordinates where vertices outside of the -1 to +1 bounds are clipped
- Multiply by projection matrix.

*Note: you can go backwards by multiplying by the inverse matrix*

## Normals
- Very important to always normalize vectors that have been interpolated across a face.
- Why does interpolation happen?
	- Because each face is formed of 3 vertices which have information about their position, normal, UV coordinate, etc...
	- So when you're sending the information over from the vertex shader to the fragment shader, something needs to happen to the inbetweens
	- And that's where interpolation comes into play, to fill in those inbetweens.