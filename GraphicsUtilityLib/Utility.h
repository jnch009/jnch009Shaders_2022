#pragma once

#include "ofMain.h"

class Utility {
public:
    static struct DirectionalLight {
        glm::vec3 direction;
        glm::vec3 color;
        float intensity;
    };

    static struct CameraData {
        glm::vec3 position;
        float rotation;
        float fov;
    };

    static struct UniformVariableData {
        glm::mat4 mvp;
        glm::mat3 normal;
        glm::mat4 model;
        glm::vec3 meshCol;
        glm::vec3 lightDir;
        glm::vec3 lightCol;
        glm::vec3 cameraPos;
    };

    static glm::vec4 determineColor(int key);
    static float dot(glm::vec3 a, glm::vec3 b);
    static float angleBetween(glm::vec3 a, glm::vec3 b);
    static glm::vec3 getLightDirection(DirectionalLight& l);
    static glm::vec3 getLightColor(DirectionalLight& l);
    static void setShaderMode(bool& isModeOn, bool setToFalse = false);
    static void useNormalShader(ofShader shader, ofMesh mesh, UniformVariableData uniforms);
    static void useDiffuseShader(ofShader shader, ofMesh mesh, UniformVariableData uniforms);
    static void useRimShader(ofShader shader, ofMesh mesh, UniformVariableData uniforms);
};