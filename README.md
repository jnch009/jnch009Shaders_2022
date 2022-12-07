# jnch009Shaders_2022
Learning from Practical Shader Development

In order to get the project to run, use VS2019 or earlier. There is currently an issue in openFrameworks in VS2022 with a DLL missing error.

## Understanding Column Major and Row Major multiplication
By default GLM uses column major matrices. 
When doing column major multiplication, we need to *post-multiply* meaning multiply from **right** to **left**
When doing row major multiplication, we do the opposite by going from **left** to **right**