#ifndef SPHERE_H
#define SPHERE_H

#include"object.h"

class Sphere : Object{

private:
	float radius;

public:

	float getRadius();

	bool hasIntersection(Ray ray);
	bool getIntersectionPoint(glm::vec3* intersect, Ray ray);
	glm::vec3 getNormal(glm::vec3 intersectionPoint);
};


#endif;
