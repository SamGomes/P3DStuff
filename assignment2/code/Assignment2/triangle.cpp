#include "triangle.h"

#include <iostream>


Triangle::Triangle(glm::vec3 position1, glm::vec3 position2, glm::vec3 position3)
{
	this->type = TRIANGLE;
	this->position = position1;
	this->position2 = position2;
	this->position3 = position3;

	this->v23 = (this->getPosition3() - this->getPosition2());
	this->v12 = (this->getPosition2() - this->getPosition());
	this->v31 = (this->getPosition() - this->getPosition3());

	this->normal = glm::cross(v12, v23);
	this->normal = glm::normalize(this->normal);

	this->material = NULL;

	this->d = -glm::dot(this->position, this->normal);

	//set bounding box
	
	std::vector<glm::vec3> points;
	points.push_back(position); points.push_back(position2); points.push_back(position3);

	glm::vec3 p0(INFINITY), p1 (-INFINITY);

	for (auto point : points) {
		if (point.x < p0.x) {
			p0.x = point.x;
		}
		if(point.x > p1.x){
			p1.x = point.x;
		}
		if (point.y < p0.y) {
			p0.y = point.y;
		}
		if (point.y > p1.y) {
			p1.y = point.y;
		}
		if (point.z < p0.z) {
			p0.z = point.z;
		}
		if (point.z > p1.z) {
			p1.z = point.z;
		}
	}

	this->boundingBox.setPoints(p0, p1);

}

bool Triangle::hasIntersection(Ray ray)
{
	//---------------------------- calc plane intersection ----------------------------

	glm::vec3 rayDir = ray.getDirection();
	glm::vec3 rayInitPoint = ray.getInitialPoint();

	float denom = glm::dot(normal, ray.getDirection());
	if (abs(denom) < 0.0001f) {
		return false;
	}

	float t = -(glm::dot(rayInitPoint, normal) + d) / denom;

	if (t <= 0.0f)
		return false;

	glm::vec3 intersect = rayInitPoint + t*rayDir;

	//---------------------------- check if it is in triangle -------------------------

	glm::vec3 vi1 = intersect - this->getPosition();
	glm::vec3 vi2 = intersect - this->getPosition2();
	glm::vec3 vi3 = intersect - this->getPosition3();

	float a1 = glm::dot(normal, glm::cross(v23, vi2) / 2.0f);
	float a2 = glm::dot(normal, glm::cross(v31, vi3) / 2.0f);
	float a3 = glm::dot(normal, glm::cross(v12, vi1) / 2.0f);

	float at = a1 + a2 + a3;

	float l1 = a1 / at;
	float l2 = a2 / at;
	float l3 = a3 / at;

	return (l1 >= 0 && l1 <= 1) && (l2 >= 0 && l2 <= 1) && (l3 >= 0 && l3 <= 1);
}

glm::vec3 Triangle::getPosition2()
{
	return position2;
}

glm::vec3 Triangle::getPosition3()
{
	return position3;
}

bool Triangle::getIntersectionPoint(glm::vec3& intersect, float& t, Ray ray)
{

	if (this->lastRayId == ray.getId()) {
		if (lastT < 0) return false;
		t = lastT;
		intersect = ray.getInitialPoint() + t * ray.getDirection();
		return true;
	}
	lastRayId = ray.getId();
	lastT = -1;
	//---------------------------- calc plane intersection ----------------------------

	glm::vec3 rayDir = ray.getDirection();
	glm::vec3 rayInitPoint = ray.getInitialPoint();

	float denom = glm::dot(normal, ray.getDirection());
	if (abs(denom) < 0.0001f) {
		return false;
	}

	t = -(glm::dot(rayInitPoint, normal) + d) / denom;

	if (t <= 0.0f)
		return false;

	intersect = rayInitPoint + t*rayDir;

	//---------------------------- check if it is in triangle -------------------------

	glm::vec3 vi1 = intersect - this->getPosition();
	glm::vec3 vi2 = intersect - this->getPosition2();
	glm::vec3 vi3 = intersect - this->getPosition3();

	float a1 = glm::dot(normal, glm::cross(v23, vi2) / 2.0f);
	float a2 = glm::dot(normal, glm::cross(v31, vi3) / 2.0f);
	float a3 = glm::dot(normal, glm::cross(v12, vi1) / 2.0f);

	float at = a1 + a2 + a3;

	float l1 = a1 / at;
	float l2 = a2 / at;
	float l3 = a3 / at;

	bool intersection = (l1 >= 0 && l1 <= 1) && (l2 >= 0 && l2 <= 1) && (l3 >= 0 && l3 <= 1);
	if (intersection) {
		lastT = t;
	}

	return intersection;
}

glm::vec3 Triangle::getNormal(glm::vec3 intersectionPoint, Ray ray)
{
	return normal;
}


bool Triangle::isInside(glm::vec3 point) {
	return false;
}
