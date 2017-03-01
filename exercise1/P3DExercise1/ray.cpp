#include "ray.h"


Ray::Ray(glm::vec3 initialPoint, glm::vec3 direction) {
	this->initialPoint = initialPoint;
	this->direction = glm::normalize(direction);
}

glm::vec3 Ray::getInitialPoint() {
	return this->initialPoint;
}

glm::vec3 Ray::getDirection() {
	return this->direction;
}