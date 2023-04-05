#include "Utility.h"

glm::vec4 Utility::determineColor(int key) {
    /* rgb(1,0,1,1) if keypress is down arrow*/
    if (key == 57359) {
        return glm::vec4(1, 0, 1, 1);
    }

    /* rgb(1,1,1,0.25) if keypress is up arrow*/
    if (key == 57357) {
        return glm::vec4(1, 1, 1, 0.25);
    }

    /* rgb(1,1,0,1) if keypress is left arrow*/
    if (key == 57356) {
        return glm::vec4(1, 1, 0, 1);
    }

    /* rgb(0,1,1,0.5) if keypress is right arrow*/
    if (key == 57358) {
        return glm::vec4(0, 1, 1, 0.5);
    }

    return glm::vec4(1, 0, 0, 1);
}

// 1. If the dot product is 0, it means that the two vectors are perpendicular to one another.
// 2. A positive dot product means that the angle between the two vectors is less than 90 degrees.
// 3. A negative dot product means that the angle between the two vectors is greater than 90 degrees.
float Utility::dot(glm::vec3 a, glm::vec3 b) {
    float x = a.x * b.x;
    float y = a.y * b.y;
    float z = a.z * b.z;
    return x + y + z;
}

// length of vector: square root of the sum of the squares
// not used for lighting calculations, but still important to know
float Utility::angleBetween(glm::vec3 a, glm::vec3 b) {
    float d = dot(a, b);
    float len = length(a) * length(b);
    float cosAngle = d / len;
    float angle = acos(cosAngle);
    return angle;
}

// multiplied by negative 1 because we are changing the direction that light faces
// we want it to point away from the surface instead of towards it
glm::vec3 Utility::getLightDirection(Utility::DirectionalLight& l) {
    return glm::normalize(l.direction * 1.0f);
}

glm::vec3 Utility::getLightColor(Utility::DirectionalLight& l) {
    return l.color * l.intensity;
}

/** 
setShaderMode is a toggle that allows us to turn the shader mode on or off.
currentShader represents the shader we want to toggle based on a keypress.
allShaders repesents the full list of all shaders we have and want to turn off if they don't match our currentShader.
*/
void Utility::setShaderMode(bool& currentShader, std::vector<bool*> allShaders) {
    for (bool* shader : allShaders) {
        if (&currentShader != shader) {
            *shader = false;
        }
        else {
            if (currentShader) {
                currentShader = false;
            }
            else {
                currentShader = true;
            }
        }
    }   
}

void Utility::useNormalShader(ofShader normalShader, ofMesh torusMesh, UniformVariableData uniforms) {
    normalShader.begin();
    normalShader.setUniformMatrix4f("mvp", uniforms.mvp);
    normalShader.setUniformMatrix3f("normal", uniforms.normal);
    torusMesh.draw();
    normalShader.end();
}

void Utility::useDiffuseShader(ofShader diffuseShader, ofMesh torusMesh, UniformVariableData uniforms) {
    diffuseShader.begin();
    diffuseShader.setUniformMatrix4f("mvp", uniforms.mvp);
    diffuseShader.setUniformMatrix3f("normal", uniforms.normal);
    diffuseShader.setUniform3f("meshCol", uniforms.meshCol);
    diffuseShader.setUniform3f("lightDir", uniforms.lightDir);
    diffuseShader.setUniform3f("lightCol", uniforms.lightCol);
    torusMesh.draw();
    diffuseShader.end();
}

void Utility::useRimShader(ofShader rimShader, ofMesh torusMesh, UniformVariableData uniforms) {
    rimShader.begin();
    rimShader.setUniformMatrix4f("mvp", uniforms.mvp);
    rimShader.setUniformMatrix3f("normal", uniforms.normal);
    rimShader.setUniformMatrix4f("model", uniforms.model);
    rimShader.setUniform3f("meshCol", uniforms.meshCol);
    rimShader.setUniform3f("cameraPos", uniforms.cameraPos);
    torusMesh.draw();
    rimShader.end();
}

void Utility::useRimAndDirShader(ofShader rimAndDirShader, ofMesh torusMesh, UniformVariableData uniforms) {
    rimAndDirShader.begin();
    rimAndDirShader.setUniformMatrix4f("mvp", uniforms.mvp);
    rimAndDirShader.setUniformMatrix3f("normal", uniforms.normal);
    rimAndDirShader.setUniformMatrix4f("model", uniforms.model);
    rimAndDirShader.setUniform3f("meshCol", uniforms.meshCol);
    rimAndDirShader.setUniform3f("cameraPos", uniforms.cameraPos);
    rimAndDirShader.setUniform3f("lightDir", uniforms.lightDir);
    rimAndDirShader.setUniform3f("lightCol", uniforms.lightCol);
    torusMesh.draw();
    rimAndDirShader.end();
}