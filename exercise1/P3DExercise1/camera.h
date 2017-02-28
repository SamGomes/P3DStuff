#pragma once

#include "glm\vec3.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	glm::vec3* getEye();
	glm::vec3* getCenter();
	glm::vec3* getUp();


	void setView(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	
	float getFovY();
	int getResX();
	int getResY();

	void setProjection(float fovY, float zNear, float zFar, int resX, int resY);

private:
	glm::vec3 *eye, *center, *up;
	float fovY, zNear, zFar;
	int resX, resY;
};