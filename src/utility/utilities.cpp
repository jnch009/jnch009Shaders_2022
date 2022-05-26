#include "utilities.h"

glm::vec4 utilities::determineColor(int key) {
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