#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>

#include "object.h"


class Triangle : public Object {

private:
	glm::vec3 position2;
	glm::vec3 position3;
	glm::vec3 normal;

	glm::vec3 v12;
	glm::vec3 v31;
	glm::vec3 v23;

	float d;

public:
	Triangle(glm::vec3 position1, glm::vec3 position2, glm::vec3 position3);

	glm::vec3 getPosition2();
	glm::vec3 getPosition3();

	bool hasIntersection(Ray ray);
	bool getIntersectionPoint(glm::vec3& intersect, Ray ray);
	glm::vec3 getNormal(glm::vec3 intersectionPoint, Ray ray);
	bool isInside(glm::vec3 point);
};


#endif;
