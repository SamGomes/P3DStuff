#include "DOFCamera.h"

DOFCamera::DOFCamera(Sampler * samplerAA, Sampler * samplerDOF, float lensRadius, float zoom) : Camera(samplerAA)
{
	this->samplerDOF = samplerDOF;
	this->lensRadius = 1.0;
	this->viewPlaneDistance = 5.0;
	this->zoom = 1;
}

Ray DOFCamera::calculatePrimaryRay(int x, int y, glm::vec2 offset)
{
	glm::vec3 pixelPoint;
	pixelPoint.x = ((((float)x + offset.x) / ((float)this->resX)) - 0.5f) * this->pixelWidth / this->zoom;
	pixelPoint.y = ((((float)y + offset.y) / ((float)this->resY)) - 0.5f) * this->pixelHeight / this->zoom;

	glm::vec2 samplePoint = samplerDOF->nextSample();
	glm::vec2 lensPoint = samplePoint*lensRadius;

	glm::vec3 origin = *this->getEye() + lensPoint.x*(*this->eyeX) + lensPoint.y*(*this->eyeY);

	glm::vec3 dir = this->computeRayDirection(pixelPoint, samplePoint);
	return  Ray(origin, dir);
}

glm::vec3 DOFCamera::computeRayDirection(glm::vec2 pixelPoint, glm::vec2 lensPoint) {
	glm::vec2 p;

	p.x = pixelPoint.x *  this->focusDistance / this->viewPlaneDistance;
	p.y = pixelPoint.y * this->focusDistance / this->viewPlaneDistance;

	glm::vec3 dir = (p.x - lensPoint.x)*(*this->eyeX) + (p.y - lensPoint.y) * (*this->eyeY) - focusDistance*(*this->eyeZ);
	dir = glm::normalize(dir);
	return dir;
}

