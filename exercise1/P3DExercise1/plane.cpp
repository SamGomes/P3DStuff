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
	glm::vec3 normal = glm::cross((this->getPosition2()-this->getPosition()),(this->getPosition3()-this->getPosition()));
	float denom = glm::dot(normal,ray.getDirection());
	if (abs(denom) > 0.0001f) // your favorite epsilon
	{
		float t = glm::dot((this->getPosition() - ray.getInitialPoint()),normal) / denom;
		if (t >= 0) return true; // you might want to allow an epsilon here too
	}
	return false;

}

bool Plane::getIntersectionPoint(glm::vec3* intersect, Ray ray)
{

	/*if (this->hasIntersection(ray)) {

		glm::vec3 rayDir = ray.getDirection();
		glm::vec3 rayInitPoint = ray.getInitialPoint();

		glm::vec3 normal = glm::cross((this->getPosition2() - this->getPosition()), (this->getPosition3() - this->getPosition()));
		float t = -1 * (glm::dot(this->getPosition(), normal) + 0) / glm::dot(ray.getDirection(), normal);

		intersect->x = rayInitPoint.x + t*ray.getDirection().x;
		intersect->y = rayInitPoint.y + t*ray.getDirection().y;
		intersect->z = rayInitPoint.z + t*ray.getDirection().z;
		return true;
	}*/

	intersect = nullptr;
	return false;
}

glm::vec3 Plane::getNormal(glm::vec3 intersectionPoint, Ray ray)
{
	glm::vec3 aux = glm::cross((this->getPosition() - this->getPosition2()), (this->getPosition() - this->getPosition3()));
	return glm::normalize(aux);
}
