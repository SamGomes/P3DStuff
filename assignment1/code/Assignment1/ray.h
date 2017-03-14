#ifndef RAY_H
#define RAY_H

#include"glm\glm.hpp"

class Ray {

private:
	glm::vec3 initialPoint;
	glm::vec3 direction;

public:
	Ray(glm::vec3 initialPoint, glm::vec3 direction);

	glm::vec3 getInitialPoint();
	glm::vec3 getDirection();
};


#endif;