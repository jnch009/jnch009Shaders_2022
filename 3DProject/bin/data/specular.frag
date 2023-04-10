#version 410

uniform vec3 lightDir;
uniform vec3 lightCol;
uniform vec3 camPos;
uniform vec3 meshCol;
uniform vec3 meshSpecCol;
uniform vec3 ambientCol;
in vec3 fragWorldPos;
in vec3 fragNrm;
out vec4 outCol;

void main(){
	vec3 normalVec = normalize(fragNrm);

	/* 
	We reverse the light direction again
	because reflect's first argument expects vector to point
	towards the mesh surface.
	*/
	vec3 refl = reflect(-lightDir,normalVec);
	vec3 toCam = normalize(camPos - fragWorldPos);
	float specAmt = max(0.0,dot(refl, toCam));
	float specBrightness = pow(specAmt, 16.0);
	vec3 specCol = meshSpecCol * lightCol * specBrightness;

	float diffAmt = max(0.0, dot(normalVec, lightDir)); // prevent negative brightness
	vec3 diffCol = meshCol * lightCol * diffAmt;

	vec3 ambient = meshCol * ambientCol;
	outCol = vec4(specCol + diffCol + ambient, 1.0);

}