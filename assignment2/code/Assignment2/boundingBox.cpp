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


bool BoundingBox::intersectionLoop(float& tMin, float& tMax, float& tProx, 
	float& tDist, float v0, float vd, float vMin, float vMax) {
	if (v0 == 0) {
		if (v0 < vMin || v0 > vMax) {
			return false;
		}
		else {
			return true;
		}
	}
	tMin = (vMin - v0) / vd;
	tMax = (vMax - v0) / vd;

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

bool BoundingBox::getIntersection(Ray ray, float& tProx, float& tDist, glm::vec3& tMin, glm::vec3& tMax)
{
	tProx = -INFINITY;
	tDist = INFINITY;

	glm::vec3 v0 = ray.getInitialPoint();
	glm::vec3 vd = ray.getDirection();
	

	if (glm::length(v0) == 0) return false;

	bool xIntersection = intersectionLoop(tMin.x, tMax.x, tProx, tDist, v0.x, vd.x, minPos.x, maxPos.x);
	bool yIntersection = intersectionLoop(tMin.y, tMax.y, tProx, tDist, v0.y, vd.y, minPos.y, maxPos.y);
	bool zIntersection = intersectionLoop(tMin.z, tMax.z, tProx, tDist, v0.z, vd.z, minPos.z, maxPos.z);

	return xIntersection && yIntersection && zIntersection;
}
