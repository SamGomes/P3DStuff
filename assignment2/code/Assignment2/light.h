#pragma once

#include "glm\vec3.hpp"
#include "sampler.h"

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	~Light();

	glm::vec3* getPosition();
	glm::vec3 getSampledPosition();
	glm::vec3* getColor();
	void setSampler(Sampler * sampler);
	Sampler * getSampler();
	

private:
	glm::vec3 *position, *color;
	Sampler * sampler;
};