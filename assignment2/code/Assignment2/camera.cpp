#include "glm\common.hpp"
#include "glm\glm.hpp"
#include "camera.h"

#define M_PI 3.14159265358979323846


Camera::Camera(Sampler* samplerAA, Sampler* samplerDOF)
{
	this->eye = NULL;
	this->center = NULL;
	this->up = NULL;
	this->eyeX = NULL;
	this->eyeY = NULL;
	this->eyeZ = NULL;
	this->samplerAA = samplerAA;
	this->samplerDOF = samplerDOF;
	this->lensRadius = 1;
	this->viewPlaneDistance = 1;
	this->zoom = 1;
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


glm::vec2 Camera::computeRayDirection(glm::vec2 pixelPoint, glm::vec2 lensPoint) {
	glm::vec2 p;

	p.x = pixelPoint.x *  this->focusDistance/ this->viewPlaneDistance;
	p.y = pixelPoint.y * this->focusDistance / this->viewPlaneDistance;

	glm::vec3 dir = (p.x - lensPoint.x)*(*this->eyeX) + (p.y - lensPoint.y) * (*this->eyeY) - focusDistance*(*this->eyeZ);
	dir = glm::normalize(dir);
	return dir;
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
	float df = glm::length(dir);

	glm::vec3 eyeZtemp = *this->eye - *this->center;
	this->focusDistance = glm::length(eyeZtemp);

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

Ray Camera::calculatePerspectivePrimaryRay(int x, int y, glm::vec2 offset)
{
	glm::vec3 xComp = (*this->eyeX) * this->pixelWidth * ((((float)x + offset.x) / ((float)this->resX)) - 0.5f);
	glm::vec3 yComp = (*this->eyeY) * this->pixelHeight * ((((float)y + offset.y) / ((float)this->resY)) - 0.5f);
	glm::vec3 zComp = -this->focusDistance * (*this->eyeZ);

	glm::vec3 d = xComp + yComp + zComp;
	d = glm::normalize(d);
	return  Ray(*this->getEye(), d);
}

Ray Camera::calculateAperturedPrimaryRay(int x, int y, glm::vec2 offset)
{
	glm::vec3 pixelPoint;
	pixelPoint.x =  ((((float)x + offset.x) / ((float)this->resX)) - 0.5f) * this->pixelWidth / this->zoom;
	pixelPoint.y =  ((((float)y + offset.y) / ((float)this->resY)) - 0.5f) * this->pixelHeight / this->zoom;

	glm::vec2 samplePoint = samplerDOF->nextSample();
	glm::vec2 lensPoint = samplePoint*lensRadius;

	glm::vec3 origin = *this->getEye() + lensPoint.x*(*this->eyeX) + lensPoint.y*(*this->eyeY);

	glm::vec3 dir = glm::vec3(this->computeRayDirection(pixelPoint, samplePoint),0);
	return  Ray(origin, dir);
}
