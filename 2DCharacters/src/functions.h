#pragma once
#include "ofMain.h"
#include "Transformation.h"

class functions {
    public:
        glm::mat4 updateTransformation(glm::vec3 t, float r, glm::vec3 s, Transformation transformation);
        glm::mat4 buildMatrix(glm::vec3 trans, float rot, glm::vec3 scale);
        void buildMesh(ofMesh& mesh, float w, float h, glm::vec3 pos);
};
