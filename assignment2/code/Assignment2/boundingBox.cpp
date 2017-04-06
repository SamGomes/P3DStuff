#include "boundingBox.h"

BoundingBox::BoundingBox() {
	minPos = glm::vec3();
	maxPos = glm::vec3();
}

glm::vec3 BoundingBox::getMinPos()
{
	return this->minPos;
}

glm::vec3 BoundingBox::getMaxPos()
{
	return this->maxPos;
}

void BoundingBox::setPoints(glm::vec3 min, glm::vec3 max) {
	minPos = min;
	maxPos = max;
}

bool BoundingBox::getIntersection(Ray ray, glm::vec3 & tMin, glm::vec3 & tMax)
{
	//TODO: Everything!!
	return false;
}
