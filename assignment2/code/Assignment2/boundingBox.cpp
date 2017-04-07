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

bool BoundingBox::isInside(glm::vec3 point)
{
	if (point.x > this->minPos.x && point.x < this->maxPos.x) {
		if (point.y > this->minPos.y && point.y < this->maxPos.y) {
			if (point.z > this->minPos.z && point.z < this->maxPos.z) {
				return true;
			}
		}
	}
	return false;
}


void BoundingBox::setPoints(glm::vec3 min, glm::vec3 max) {
	minPos = min;
	maxPos = max;
}


bool BoundingBox::intersectionLoop(float& tProx, float& tDist, float v0, float vd, float vMin, float vMax) {
	if (v0 == 0) {
		if (v0 < vMin || v0 > vMax) {
			return false;
		}
		else {
			return true;
		}
	}
	float tMin = (vMin - v0) / vd;
	float tMax = (vMax - v0) / vd;

	if (tMin > tMax) {
		float minAux = tMin;
		tMin = tMax;
		tMax = minAux;
	}
	if (tMin > tProx) tProx = tMin;
	if (tMax < tDist) tDist = tMax;

	if (tProx > tDist) {
		return false;
	}

	if (tDist < 0) {
		return false;
	}
	return true;
}

bool BoundingBox::getIntersection(Ray ray, float& tProx, float& tDist)
{
	tProx = -INFINITY;
	tDist = INFINITY;

	glm::vec3 v0 = ray.getInitialPoint();
	glm::vec3 vd = ray.getDirection();
	

	if (glm::length(v0) == 0) return false;

	return intersectionLoop(tProx, tDist, v0.x, vd.x, minPos.x, maxPos.x)
		&& intersectionLoop(tProx, tDist, v0.y, vd.y, minPos.y, maxPos.y)
		&& intersectionLoop(tProx, tDist, v0.z, vd.z, minPos.z, maxPos.z);
}
