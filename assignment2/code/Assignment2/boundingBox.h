#pragma once

#include "glm\vec3.hpp"
#include "ray.h"

class BoundingBox {

protected:
	glm::vec3 minPos, maxPos;

public:
	glm::vec3 getMinPos();
	glm::vec3 getMaxPos();

	bool getIntersection(Ray ray, glm::vec3& tMin, glm::vec3& tMax);
};