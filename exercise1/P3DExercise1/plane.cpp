#include "plane.h"

Plane::Plane(glm::vec3 position1, glm::vec3 position2, glm::vec3 position3)
{
	this->type = PLANE;
	this->position = position1;
	this->position2 = position2;
	this->position3 = position3;
	this->material = NULL;
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
	/*if (glm::dot((this->getPosition2() - this->getPosition()), ray.getDirection())<0)
		return false;*/

	return true;
}

bool Plane::getIntersectionPoint(glm::vec3& intersect, Ray ray)
{
	glm::vec3 rayDir = ray.getDirection();
	glm::vec3 rayInitPoint = ray.getInitialPoint();

	if (glm::dot((this->getPosition2() - this->getPosition()),ray.getDirection())<0)
		return false;

	glm::vec3 normal = -glm::cross((this->getPosition2() - this->getPosition()), (this->getPosition3() - this->getPosition()));
	float t = -1 * (glm::dot(this->getPosition(), normal) + glm::distance((this->getPosition2() - this->getPosition()), glm::vec3(0.0f)) / glm::dot(ray.getDirection(), normal));

	intersect.x = rayInitPoint.x + t*ray.getDirection().x;
	intersect.y = rayInitPoint.y + t*ray.getDirection().y;
	intersect.z = rayInitPoint.z + t*ray.getDirection().z;
	return true;	
}

glm::vec3 Plane::getNormal(glm::vec3 intersectionPoint, Ray ray)
{
	glm::vec3 aux = glm::cross((this->getPosition() - this->getPosition2()), (this->getPosition() - this->getPosition3()));
	return glm::normalize(aux);
}
