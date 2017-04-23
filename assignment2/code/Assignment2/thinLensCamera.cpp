#include "thinLensCamera.h"

ThinLensCamera::ThinLensCamera(Sampler * samplerAA, Sampler * samplerDOF, float lensRadius, float focusDistance, float viewPlaneDistance, float zoom) : Camera(samplerAA)
{
	this->samplerDOF = samplerDOF;
	this->lensRadius = lensRadius;
	this->viewPlaneDistance = viewPlaneDistance;
	this->focusDistance = focusDistance;
	this->zoom = 1;
}

ThinLensCamera::~ThinLensCamera() {
	if (samplerDOF != NULL) delete samplerDOF;
}

Ray ThinLensCamera::calculatePrimaryRay(int x, int y, glm::vec2 offset)
{
	glm::vec2 centerPoint;
	centerPoint.x = ((((float)x + offset.x) / ((float)this->resX)) - 0.5f) * this->pixelWidth / this->zoom;
	centerPoint.y = ((((float)y + offset.y) / ((float)this->resY)) - 0.5f) * this->pixelHeight / this->zoom;

	glm::vec2 samplePoint = samplerDOF->nextSample();
	glm::vec2 lensPoint = samplePoint*lensRadius;

	glm::vec3 origin = *this->getEye() + lensPoint.x*(*this->eyeX) + lensPoint.y*(*this->eyeY);

	glm::vec3 dir = this->computeRayDirection(centerPoint, lensPoint);
	return  Ray(origin, dir);
}

glm::vec3 ThinLensCamera::computeRayDirection(glm::vec2 centerPoint, glm::vec2 lensPoint) {
	
	glm::vec2 p;

	p.x = centerPoint.x *  this->focusDistance / this->viewPlaneDistance;
	p.y = centerPoint.y * this->focusDistance / this->viewPlaneDistance;


	//ask about z coord!
	glm::vec3 dir = (p.x - lensPoint.x)*(*this->eyeX) + (p.y - lensPoint.y) * (*this->eyeY) - focusDistance*(*this->eyeZ);
	dir = glm::normalize(dir);
	return dir;
}

void ThinLensCamera::setView(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	Camera::setView(eye, center, up);
}

Sampler* ThinLensCamera::getSamplerDOF()
{
	return this->samplerDOF;
}
