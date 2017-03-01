#include "sphere.h"

#include <iostream>

bool Sphere::hasIntersection(Ray ray)
{
	float r = this->getRadius();
	glm::vec3 pos = this->getPosition();

	glm::vec3 rayDir = ray.getDirection();
	glm::vec3 rayInitPoint = ray.getInitialPoint();

	float descriminant = (glm::dot(rayDir, (rayInitPoint - pos))*glm::dot(rayDir, (rayInitPoint - pos))) - glm::dot(rayDir, rayDir)*(glm::dot((rayInitPoint - pos), (rayInitPoint - pos)) - r*r);

	
	if (descriminant < 0) {
		return false;
	}
	return true;

	

}

bool Sphere::getIntersectionPoint(glm::vec3* intersect, Ray ray)
{
	if (this->hasIntersection(ray)){

		float r = this->getRadius();
		glm::vec3 pos = this->getPosition();

		glm::vec3 rayDir = ray.getDirection();
		glm::vec3 rayInitPoint = ray.getInitialPoint();

		float descriminant = (glm::dot(rayDir, (rayInitPoint - pos))*glm::dot(rayDir, (rayInitPoint - pos))) - (glm::dot(rayDir, rayDir)*(glm::dot((rayInitPoint - pos), (rayInitPoint - pos)) - r*r));

		float point1 = (glm::dot(rayDir*-1.0f, (rayInitPoint - pos)) + std::sqrt(descriminant)) / (glm::dot(rayDir, rayDir));
		float point2 = (glm::dot(rayDir*-1.0f, (rayInitPoint - pos)) - std::sqrt(descriminant)) / (glm::dot(rayDir, rayDir));

		intersect->x = rayInitPoint.x + point1*ray.getDirection().x;
		intersect->y = rayInitPoint.y + point1*ray.getDirection().y;
		intersect->z = rayInitPoint.z + point1*ray.getDirection().z;
		return true;
	}
	intersect = nullptr;
	return false;
}

glm::vec3 Sphere::getNormal(glm::vec3 intersectionPoint)
{
	glm::vec3 aux = intersectionPoint - this->getPosition();
	return glm::normalize(aux);
}

Sphere::Sphere(glm::vec3 position, float radius)
{
	this->type = SPHERE;
	this->position = position;
	this->radius = radius;
	this->material = NULL;
}

float Sphere::getRadius() {
	return this->radius;
}
