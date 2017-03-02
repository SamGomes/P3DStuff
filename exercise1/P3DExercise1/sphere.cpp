#include "sphere.h"

#include <iostream>

bool Sphere::hasIntersection(Ray ray)
{
	glm::vec3 c = this->getPosition();
	glm::vec3 e = ray.getInitialPoint();

	float r = this->getRadius();

	glm::vec3 d = ray.getDirection();

	//normalize rd
	d = glm::normalize(d);

	//calculate square Doc

	float d_oc = (c.x - e.x)*(c.x - e.x)
		+ (c.y - e.y)*(c.y - e.y)
		+ (c.z - e.z)*(c.z - e.z);

	//test if radius origin is inside the sphere
	if (d_oc == r*r) {
		return false;
	}

	//calculate b
	float b = d.x*(c.x - e.x) + d.y*(c.y - e.y) + d.z*(c.z - e.z);

	//test if radius origin points in opposite to the sphere
	if (d_oc > r*r) {
		if (b < 0) {
			return false;
		}
	}

	//calc R
	float R = b*b - d_oc + r*r;

	//test for negative root
	if (R < 0) {
		return false;
	}
	return true;
	

}

bool Sphere::getIntersectionPoint(glm::vec3& intersect, Ray ray)
{

	glm::vec3 c = this->getPosition();
	glm::vec3 e = ray.getInitialPoint();

	float r = this->getRadius();

	glm::vec3 d = ray.getDirection();

	//normalize rd
	d = glm::normalize(d);

	//calculate square Doc

	float d_oc = (c.x - e.x)*(c.x - e.x)
		+ (c.y - e.y)*(c.y - e.y)
		+ (c.z - e.z)*(c.z - e.z);

	//test if radius origin is inside the sphere
	if (d_oc == r*r) {
		return false;
	}

	//calculate b
	float b = d.x*(c.x - e.x) + d.y*(c.y - e.y) + d.z*(c.z - e.z);

	//test if radius origin points in opposite to the sphere
	if (d_oc > r*r) {
		if (b < 0) {
			return false;
		}
	}
	
	//calc R
	float R = b*b - d_oc + r*r;

	//test for negative root
	if (R < 0) {
		return false;
	}

	//calc roots
	float point1 = b - std::sqrt(R);
	float point2 = b + std::sqrt(R);

	//check for smallest root
	if (point1 > 0 && point2 > 0) {
		point1 = std::fminf(point1, point2);
	}

	//calc intersection point
	intersect.x = e.x + point1*d.x;
	intersect.y = e.y + point1*d.y;
	intersect.z = e.z + point1*d.z;
	return true;
	
}

glm::vec3 Sphere::getNormal(glm::vec3 intersectionPoint, Ray ray)
{
	glm::vec3 c = this->getPosition();
	glm::vec3 e = ray.getInitialPoint();
	float r = this->getRadius();

	float d_oc = (c.x - e.x)*(c.x - e.x)
		+ (c.y - e.y)*(c.y - e.y)
		+ (c.z - e.z)*(c.z - e.z);

	glm::vec3 aux = (intersectionPoint - this->getPosition())/this->radius;

	if (d_oc < r*r) {
		aux = -1.0f*aux;
	}

	return aux;
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
