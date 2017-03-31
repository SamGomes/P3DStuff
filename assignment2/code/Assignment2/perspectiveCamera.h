#ifndef PERSPCAMERA_H
#define PERSPCAMERA_H

#include "glm\vec3.hpp"
#include "sampler.h"
#include "ray.h"
#include "Camera.h"

class PerspectiveCamera : public Camera
{
public: //methods
	PerspectiveCamera(Sampler * samplerAA);
	Ray calculatePrimaryRay(int x, int y, glm::vec2 offset);
	void setView(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
}; 

#endif
