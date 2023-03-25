#pragma once
#include "ofMain.h"

using namespace glm;

class Transformation {
    mat4 trans, rot, scaler;

    public:
        void setTranslate(vec3 t) {
            trans = translate(t);
        }
        mat4 getTranslate() {
            return trans;
        }

        void setRotate(float r) {
            rot = rotate(r, vec3(0, 0, 1));
        }
        mat4 getRotate() {
            return rot;
        }

        void setScale(vec3 s) {
            scaler = scale(s);
        }
        mat4 getScale() {
            return scaler;
        }
};
