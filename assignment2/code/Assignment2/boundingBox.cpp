#include "boundingBox.h"

glm::vec3 BoundingBox::getMinPos()
{
	return this->minPos;
}

glm::vec3 BoundingBox::getMaxPos()
{
	return this->maxPos;
}

bool BoundingBox::isInside(glm::vec3 point)
{
	if (point.x > this->minPos.x && point.x < this->maxPos.x) {
		if (point.y > this->minPos.y && point.y < this->maxPos.y) {
			return true;
		}
	}
	return false;
}

bool BoundingBox::getIntersection(Ray ray, glm::vec3 & tMin, glm::vec3 & tMax)
{
	//TODO: Everything!!
	return false;
}
