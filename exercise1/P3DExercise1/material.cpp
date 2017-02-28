#include "material.h"

Material::Material(glm::vec3 color, float diffuse, float specular, float shininess, float transmittance, float indexOfRefraction)
{
	this->color = new glm::vec3(color);
	this->diffuse = diffuse;
	this->specular = specular;
	this->shininess = shininess;
	this->transmittance = transmittance;
	this->indexOfRefraction = indexOfRefraction;
}

Material::~Material()
{
	delete this->color;
}

glm::vec3 * Material::getColor()
{
	return this->color;
}

float Material::getDiffuse()
{
	return this->diffuse;
}

float Material::getSpecular()
{
	return this->specular;
}

float Material::getShininess()
{
	return this->shininess;
}

float Material::getTransmittance()
{
	return this->transmittance;
}

float Material::getIndexOfRefraction()
{
	return this->indexOfRefraction;
}
