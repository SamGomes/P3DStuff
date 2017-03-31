#ifndef DOFCAMERA_H
#define DOFCAMERA_H

#include "glm\vec3.hpp"
#include "sampler.h"
#include "ray.h"
#include "Camera.h"

class DOFCamera: public Camera
{

private:
	Sampler* samplerDOF;
	float lensRadius;
	float viewPlaneDistance;
	float zoom;

public:
	DOFCamera(Sampler * samplerAA, Sampler * samplerDOF, float lensRadius, float zoom);

	Ray calculatePrimaryRay(int x, int y, glm::vec2 offset);

private:
	glm::vec3 computeRayDirection(glm::vec2 pixelPoint, glm::vec2 lensPoint);
	

};

#endif