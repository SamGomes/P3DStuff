#include "ray.h"

unsigned long Ray::idInc = 0;

Ray::Ray(glm::vec3 initialPoint, glm::vec3 direction) {
	this->initialPoint = initialPoint;
	this->direction = glm::normalize(direction);
	this->id = Ray::idInc++;
}

glm::vec3 Ray::getInitialPoint() {
	return this->initialPoint;
}

glm::vec3 Ray::getDirection() {
	return this->direction;
}

unsigned long Ray::getId()
{
	return id;
}
