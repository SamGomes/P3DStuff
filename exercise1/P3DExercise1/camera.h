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

	glm::vec3 calculatePrimaryRay(int x, int y);

private:
	glm::vec3 *eye, *center, *up;
	glm::vec3 *eyeX, *eyeY, *eyeZ;
	float fovY, zNear, zFar;
	int resX, resY;
	float focusDistance, pixelWidth, pixelHeight;
};