#pragma once

#include "ofMain.h"

class Utility {
public:
    static glm::vec4 determineColor(int key);
    static float dot(glm::vec3 a, glm::vec3 b);
};