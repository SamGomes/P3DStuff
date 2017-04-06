#pragma once

#include "glm\vec3.hpp"
#include "ray.h"

class BoundingBox {

protected:
	glm::vec3 minPos, maxPos;

public:
	BoundingBox();
	
	glm::vec3 getMinPos();
	glm::vec3 getMaxPos();

	void setPoints(glm::vec3 min, glm::vec3 max);

	bool getIntersection(Ray ray, glm::vec3& tMin, glm::vec3& tMax);
};