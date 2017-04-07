#ifndef RAY_H
#define RAY_H

#include"glm\glm.hpp"

class Ray {
private:
	glm::vec3 initialPoint;
	glm::vec3 direction;
	unsigned long id;

	static unsigned long idInc;

public:
	Ray(glm::vec3 initialPoint, glm::vec3 direction);
	
	
	
	glm::vec3 getInitialPoint();
	glm::vec3 getDirection();
	unsigned long getId();
};


#endif;