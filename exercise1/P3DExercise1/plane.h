#ifndef PLANE_H
#define PLANE_H

#include"object.h"

class Plane : Object {

private:
	glm::vec3 position2;
	glm::vec3 position3;

public:
	glm::vec3 getPosition2();
	glm::vec3 getPosition3();

	bool hasIntersection(Ray ray);
	bool getIntersectionPoint(glm::vec3*  intersect, Ray ray);

};


#endif