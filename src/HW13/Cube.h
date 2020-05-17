#pragma once

#include <glm/glm.hpp>

class Cube 
{
public:
	/* member variable */
	glm::vec3 position{ 0.f, 0.f, 0.f };
	float side = 1.f;
	glm::vec3 rotationAxis{ 1.f, 1.f, 1.f };
	float rotationSpeed = 1.f;
};