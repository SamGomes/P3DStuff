#pragma once

#include "glm\vec3.hpp"
#include "sampler.h"
#include "ray.h"

class Camera
{

private:
	Sampler* samplerAA;
	Sampler* samplerDOF;

public:
	Camera(Sampler* samplerAA, Sampler* samplerDOF);
	~Camera();


	glm::vec3* getEye();
	glm::vec3* getCenter();
	glm::vec3* getUp();
	glm::vec3* getEyeX();
	glm::vec3* getEyeY();
	glm::vec3* getEyeZ();

	void setView(glm::vec3 eye, glm::vec3 center, glm::vec3 up);

	float getFovY();
	int getResX();
	int getResY();
	float getFocusDistance();
	float getPixelWidth();
	float getPixelHeight();

	void setProjection(float fovY, float zNear, float zFar, int resX, int resY);
	glm::vec2 computeRayDirection(glm::vec2 pixelPoint, glm::vec2 lensPoint);
	Ray calculatePerspectivePrimaryRay(int x, int y, glm::vec2 offset);
	Ray calculateAperturedPrimaryRay(int x, int y, glm::vec2 offset);

private:
	glm::vec3 *eye, *center, *up;
	glm::vec3 *eyeX, *eyeY, *eyeZ;
	float fovY, zNear, zFar;
	int resX, resY;
	float focusDistance, pixelWidth, pixelHeight;

	float lensRadius;
	float viewPlaneDistance;
	float zoom;

};