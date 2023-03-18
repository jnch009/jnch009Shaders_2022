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
float dot(glm::vec3 a, glm::vec3 b) {
    float x = a.x * b.x;
    float y = a.y * b.y;
    float z = a.z * b.z;
    return x + y + z;
}

// length of vector: square root of the sum of the squares
// not used for lighting calculations, but still important to know
float angleBetween(glm::vec3 a, glm::vec3 b) {
    float d = dot(a, b);
    float len = length(a) * length(b);
    float cosAngle = d / len;
    float angle = acos(cosAngle);
    return angle;
}