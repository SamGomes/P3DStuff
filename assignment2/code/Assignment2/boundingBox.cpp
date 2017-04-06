#include "boundingBox.h"

glm::vec3 BoundingBox::getMinPos()
{
	return this->minPos;
}

glm::vec3 BoundingBox::getMaxPos()
{
	return this->maxPos;
}

bool BoundingBox::getIntersection(Ray ray, glm::vec3 & tMin, glm::vec3 & tMax)
{
	//TODO: Everything!!
	return false;
}
