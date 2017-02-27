#ifndef RAY_H
#define RAY_H

#include "VECTOR\Vector.h"

class Ray {

private:
	float initialPoint;
	Vector direction;

public:
	Ray(float initialPoint,Vector direction);
};


#endif;