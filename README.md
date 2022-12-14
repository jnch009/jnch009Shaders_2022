# jnch009Shaders_2022
Learning from Practical Shader Development

In order to get the project to run, use VS2019 or earlier. There is currently an issue in openFrameworks in VS2022 with a DLL missing error.

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