#ifndef PLANE_H
#define PLANE_H

#include"object.h"

class Plane : public Object {

private:
	glm::vec3 position2;
	glm::vec3 position3;
	glm::vec3 normal;

public:
	Plane(glm::vec3 position1, glm::vec3 position2, glm::vec3 position3);

	glm::vec3 getPosition2();
	glm::vec3 getPosition3();

	bool hasIntersection(Ray ray);
	bool getIntersectionPoint(glm::vec3& intersect, Ray ray);
	glm::vec3 getNormal(glm::vec3 intersectionPoint, Ray ray);

};


#endif
