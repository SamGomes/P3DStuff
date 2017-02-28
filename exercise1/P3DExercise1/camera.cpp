#include "glm\common.hpp"
#include "camera.h"


Camera::Camera()
{
	this->eye = NULL;
	this->center = NULL;
	this->up = NULL;
}

Camera::~Camera()
{
	if (this->eye != NULL)
		delete this->eye;
	if (this->center != NULL)
		delete this->center;	
	if (this->up != NULL)
	delete this->up;
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

void Camera::setProjection(float fovY, float zNear, float zFar, int resX, int resY)
{
	this->fovY = fovY;
	this->zNear = zNear;
	this->zFar = zFar;
	this->resX = resX;
	this->resY = resY;

}
