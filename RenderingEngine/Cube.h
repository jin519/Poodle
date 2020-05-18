#pragma once

#include <glm/glm.hpp>
#include "Transform.h"

class Cube 
{
public:
	/* member variable */
	Transform transform; 
	float side;
	glm::vec3 rotationSpeed;
};