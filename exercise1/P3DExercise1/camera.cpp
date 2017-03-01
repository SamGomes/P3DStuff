#include "glm\common.hpp"
#include "glm\glm.hpp"
#include "camera.h"

#define M_PI 3.14159265358979323846

Camera::Camera()
{
	this->eye = NULL;
	this->center = NULL;
	this->up = NULL;
	this->eyeX = NULL;
	this->eyeY = NULL;
	this->eyeZ = NULL;
}

Camera::~Camera()
{
	if (this->eye != NULL)
		delete this->eye;
	if (this->center != NULL)
		delete this->center;	
	if (this->up != NULL)
		delete this->up;
	if (this->eyeX != NULL)
		delete this->eyeX;
	if (this->eyeY != NULL)
		delete this->eyeY;
	if (this->eyeZ != NULL)
		delete this->eyeZ;
}

glm::vec3 * Camera::getEye()
{
	return this->eye;
}

glm::vec3 * Camera::getCenter()
{
	return this->center;
}

glm::vec3 * Camera::getUp()
{
	return this->up;
}

glm::vec3 * Camera::getEyeX()
{
	return this->eyeX;
}

glm::vec3 * Camera::getEyeY()
{
	return this->eyeY;
}

glm::vec3 * Camera::getEyeZ()
{
	return this->eyeZ;
}

void Camera::setView(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	if (this->eye != NULL)
		delete this->eye;
	this->eye = new glm::vec3(eye);

	if (this->center != NULL)
		delete this->center;
	this->center = new glm::vec3(center);

	if (this->up != NULL)
		delete this->center;
	this->up = new glm::vec3(up);


	if (this->eyeX != NULL)
		delete this->eyeX;
	if (this->eyeY != NULL)
		delete this->eyeY;
	if (this->eyeZ != NULL)
		delete this->eyeZ;

	glm::vec3 dir = *this->eye - *this->center;
	float df = dir.length();

	glm::vec3 eyeZtemp = *this->eye - *this->center;
	this->focusDistance = eyeZtemp.length();

	this->eyeZ = new glm::vec3(glm::normalize(eyeZtemp));
	this->eyeX = new glm::vec3(glm::normalize(glm::cross(*this->up, *this->eyeZ)));
	this->eyeY = new glm::vec3(glm::cross(*this->eyeZ, *this->eyeX));

}

float Camera::getFovY()
{
	return this->fovY;
}

int Camera::getResX()
{
	return this->resX;
}

int Camera::getResY()
{
	return this->resY;
}

float Camera::getFocusDistance()
{
	return this->focusDistance;
}

float Camera::getPixelWidth()
{
	return this->pixelWidth;
}

float Camera::getPixelHeight()
{
	return this->pixelHeight;
}

void Camera::setProjection(float fovY, float zNear, float zFar, int resX, int resY)
{
	this->fovY = fovY;
	this->zNear = zNear;
	this->zFar = zFar;
	this->resX = resX;
	this->resY = resY;

	float angle = (this->fovY * (float)M_PI) / 180.0f; //in degrees, must be converted

	this->pixelHeight = 2 * this->focusDistance * tanf(angle / 2);
	this->pixelWidth = ((float)resX / (float)resY) * this->pixelHeight;
}

glm::vec3 Camera::calculatePrimaryRay(int x, int y)
{
	glm::vec3 xComp = (*this->eyeX) * this->pixelWidth * (((float)x / (float)this->resX) - 0.5f);
	glm::vec3 yComp = (*this->eyeY) * this->pixelHeight * (((float)y / (float)this->resY) - 0.5f);
	glm::vec3 zComp = -this->focusDistance * (*this->eyeZ);

	glm::vec3 d = xComp + yComp + zComp;
	return glm::normalize(d);
}
