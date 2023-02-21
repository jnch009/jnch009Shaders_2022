#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include <vector>

class MeshData {
	public:
		std::vector<glm::vec2> texCoords = {
			glm::vec2(0, 0),
			glm::vec2(0, 1),
			glm::vec2(1, 1),
			glm::vec2(1, 0)
		};

		std::vector<glm::vec3> topLeft = {
			glm::vec3(-1, 0, 0),
			glm::vec3(-1, 1, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(0, 0, 0)
		};

		std::vector<glm::vec3> topRight = {
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0),
			glm::vec3(1, 1, 0),
			glm::vec3(1, 0, 0)
		};

		std::vector<glm::vec3> bottomLeft = {
			glm::vec3(-1, -1, 0),
			glm::vec3(-1, 0, 0),
			glm::vec3(0, 0, 0),
			glm::vec3(0, -1, 0)
		};

		std::vector<glm::vec3> bottomRight = {
			glm::vec3(0, -1, 0),
			glm::vec3(0, 0, 0),
			glm::vec3(1, 0, 0),
			glm::vec3(1, -1, 0)
		};

		std::vector<glm::vec3> quad = {
			glm::vec3(-1, -1, 0),
			glm::vec3(-1, 1, 0),
			glm::vec3(1, 1, 0),
			glm::vec3(1, -1, 0)
		};
};