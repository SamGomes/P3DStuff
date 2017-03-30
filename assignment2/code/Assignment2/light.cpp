#include "light.h"

Light::Light(glm::vec3 position, glm::vec3 color)
{
	this->position = new glm::vec3(position);
	this->color = new glm::vec3(color);
	this->sampler = NULL;
}

Light::~Light()
{
	delete this->position;
	delete this->color;
	if (sampler != NULL) {
		delete sampler;
	}
}

void Light::setSampler(Sampler * sampler) {
	if (this->sampler != NULL) {
		delete this->sampler;
	}
	this->sampler = sampler;
}

Sampler * Light::getSampler() {
	return this->sampler;
}

glm::vec3 * Light::getPosition()
{
	return this->position;
}

glm::vec3 * Light::getColor()
{
	return this->color;
}

