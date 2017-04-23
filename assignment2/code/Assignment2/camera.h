#ifndef CAMERA_H
#define CAMERA_H

#include "glm\vec3.hpp"
#include "sampler.h"
#include "ray.h"

class Camera
{

protected: //vars
	Sampler* samplerAA;
	glm::vec3 *eye, *center, *up;
	glm::vec3 *eyeX, *eyeY, *eyeZ;
	float fovY, zNear, zFar;
	int resX, resY;
	float focusDistance, pixelWidth, pixelHeight;


public: //methods
	Camera(Sampler* samplerAA);
	~Camera();


	glm::vec3* getEye();
	glm::vec3* getCenter();
	glm::vec3* getUp();
	glm::vec3* getEyeX();
	glm::vec3* getEyeY();
	glm::vec3* getEyeZ();

	virtual void setView(glm::vec3 eye, glm::vec3 center, glm::vec3 up);

	float getFovY();
	int getResX();
	int getResY();
	float getFocusDistance();
	float getPixelWidth();
	float getPixelHeight();
	Sampler* getSamplerAA();

	void setProjection(float fovY, float zNear, float zFar, int resX, int resY);
	virtual Ray calculatePrimaryRay(int x, int y, glm::vec2 offset) = 0;


};

#endif