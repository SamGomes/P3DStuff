#include "perspectiveCamera.h"

PerspectiveCamera::PerspectiveCamera(Sampler * samplerAA) : Camera(samplerAA)
{
}


Ray PerspectiveCamera::calculatePrimaryRay(int x, int y, glm::vec2 offset)
{
	glm::vec3 xComp = (*this->eyeX) * this->pixelWidth * ((((float)x + offset.x) / ((float)this->resX)) - 0.5f);
	glm::vec3 yComp = (*this->eyeY) * this->pixelHeight * ((((float)y + offset.y) / ((float)this->resY)) - 0.5f);
	glm::vec3 zComp = -this->focusDistance * (*this->eyeZ);

	glm::vec3 d = xComp + yComp + zComp;
	d = glm::normalize(d);
	return  Ray(*this->getEye(), d);
}

void PerspectiveCamera::setView(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
	Camera::setView(eye, center, up);
	this->focusDistance = glm::length(*this->eye - *this->center);
}