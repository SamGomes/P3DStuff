#include "plane.h"
#include <stdio.h>

Plane::Plane(glm::vec3 position1, glm::vec3 position2, glm::vec3 position3)
{
	this->type = PLANE;
	this->position = position1;
	this->position2 = position2;
	this->position3 = position3;
	this->material = NULL;

	this->normal = glm::cross((this->getPosition2() - this->getPosition()), (this->getPosition3() - this->getPosition()));
	this->normal = glm::normalize(this->normal);
	this->d = -glm::dot(this->position, this->normal);
}

glm::vec3 Plane::getPosition2()
{
	return position2;
}

glm::vec3 Plane::getPosition3()
{
	return position3;
}

bool Plane::hasIntersection(Ray ray)
{
	float denom = glm::dot(normal,ray.getDirection());
	if (abs(denom) > 0.0001f){
		float t = glm::dot(this->position - ray.getInitialPoint(), normal) / denom;
		if (t >= 0) return true; 
	}
	return false;
}

bool Plane::getIntersectionPoint(glm::vec3& intersect, Ray ray)
{
	glm::vec3 rayDir = ray.getDirection();
	glm::vec3 rayInitPoint = ray.getInitialPoint();

	float denom = glm::dot(normal, ray.getDirection());
	if (abs(denom) < 0.0001f) {
		return false;
	}

	float t = -(glm::dot(rayInitPoint, normal) + d) / denom;

	if (t <= 0.0f)
		return false;

	intersect = rayInitPoint + t*rayDir;
	return true;	
}

glm::vec3 Plane::getNormal(glm::vec3 intersectionPoint, Ray ray)
{
	return normal;
}

bool Plane::isInside(glm::vec3 point) {
	return false;
}
