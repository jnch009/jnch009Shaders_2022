#include "functions.h"
#include "ofMain.h"
#include "Transformation.h"
#include "structs.h"

glm::mat4 functions::updateTransformation(glm::vec3 t, float r, glm::vec3 s, Transformation transformation) {
	using glm::mat4;
	mat4 scale = glm::scale(s);
	mat4 rotate = glm::rotate(r, vec3(0, 0, 1));
	mat4 translate = glm::translate(s);
	mat4 initialTransform = translate * rotate * scale;
	mat4 finalTransform = transformation.getTranslate() * transformation.getRotate() * transformation.getScale();
	//Multiplying a matrix by its' inverse ALWAYS creates the identity matrix
	return initialTransform * inverse(initialTransform) * finalTransform;
}

glm::mat4 functions::buildMatrix(glm::vec3 trans, float rot, glm::vec3 scale)
{
	using glm::mat4;
	mat4 translation = glm::translate(trans);
	mat4 rotation = glm::rotate(rot, glm::vec3(0.0, 0.0, 1.0));
	mat4 scaler = glm::scale(scale);
	// by default GLM uses column major so we have to multiply in reverse order
	return translation * rotation * scaler;
}

void functions::buildMesh(ofMesh& mesh, float w, float h, glm::vec3 pos)
{
	float verts[] = { -w + pos.x, -h + pos.y, pos.z,
		-w + pos.x, h + pos.y, pos.z,
		w + pos.x, h + pos.y, pos.z,
		w + pos.x, -h + pos.y, pos.z };

	float uvs[] = { 0,0, 0,1, 1,1, 1,0 };
	for (int i = 0; i < 4; ++i) {
		int idx = i * 3;
		int uvIdx = i * 2;
		mesh.addVertex(glm::vec3(verts[idx], verts[idx + 1], verts[idx + 2]));
		mesh.addTexCoord(glm::vec2(uvs[uvIdx], uvs[uvIdx + 1]));
	}

	ofIndexType indices[6] = { 0,1,2,2,3,0 };
	mesh.addIndices(indices, 6);
}

glm::mat4 functions::buildViewMatrix(CameraData cam)
{
	using namespace glm;
	return inverse(buildMatrix(cam.position, cam.rotation, vec3(1, 1, 1)));
}