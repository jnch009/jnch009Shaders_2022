#version 410
uniform vec3 meshCol;
uniform vec3 cameraPos; // 1: camera coordinates in world space
in vec3 fragNrm;
in vec3 fragWorldPos; // 2: fragment position in world space from vertex shader
out vec4 outCol;
void main()
{
	vec3 normal = normalize(fragNrm);
	vec3 toCam = normalize(cameraPos - fragWorldPos); // 3: calculating vector from fragment to camera
	float rimAmt = 1.0 - max(0.0, dot(normal, toCam)); // 4: dot product and clamping to range 0-1
	rimAmt = pow(rimAmt, 2); // 5: concentrates our rim effect
	vec3 rimLightCol = vec3(1, 1, 1);
	outCol = vec4(rimLightCol * rimAmt, 1.0);
}