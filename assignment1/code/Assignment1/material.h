#pragma once

#include "glm\vec3.hpp"

class Material
{
public:
	Material(glm::vec3 color, float diffuse, float specular, float shininess, float transmittance, float indexOfRefraction);
	~Material();

	glm::vec3* getColor();
	float getDiffuse();
	float getSpecular();
	float getShininess();
	float getTransmittance();
	float getIndexOfRefraction();

private:
	glm::vec3 * color;
	float diffuse, specular, shininess, transmittance, indexOfRefraction;
};