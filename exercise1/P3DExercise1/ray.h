#ifndef RAY_H
#define RAY_H

#include "glm/vec3.hpp"

class Ray {

private:
	float initialPoint;
	glm::vec3 direction;

public:
	Ray(float initialPoint, glm::vec3 direction);
};


#endif;