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

glm::vec3 Light::getSampledPosition()
{
	if (sampler) {
		glm::vec2 sp = sampler->nextSample();
		glm::vec3 lightPosSampled = *position;
		lightPosSampled.x += 1 * (sp.x - 0.5f);
		lightPosSampled.y += 1 * (sp.y - 0.5f);
		return lightPosSampled;
	}
	else 
		return *position;
}

glm::vec3 * Light::getColor()
{
	return this->color;
}

