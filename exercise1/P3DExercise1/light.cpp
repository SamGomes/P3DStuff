#include "light.h"

Light::Light(glm::vec3 position, glm::vec3 color)
{
	this->position = new glm::vec3(position);
	this->color = new glm::vec3(color);
}

Light::~Light()
{
	delete this->position;
	delete this->color;
}

glm::vec3 * Light::getPosition()
{
	return this->position;
}

glm::vec3 * Light::getColor()
{
	return this->color;
}

