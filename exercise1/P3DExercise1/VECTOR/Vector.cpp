#include "Vector.h"
#include <math.h>
#include <iostream>
#include"stdio.h"

using namespace std;

Vector::Vector() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
	this->dimension = 0;
	this->quadrance = 0;
}

Vector::Vector(float x, float y) {
	this->x = x;
	this->y = y;
	this->z = 1;
	this->w = 1;
	this->dimension = 2;
	
}
Vector::Vector(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = 1;
	this->dimension = 3;
}
Vector::Vector(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	this->dimension = 4;
}

void Vector::setQuadrance(float quadrance) {
	this->quadrance = quadrance;
}

float Vector::calcQuadrance() {
	return (this->getX()*this->getX() + this->getY()*this->getY() + this->getZ()*this->getZ());
}

void Vector::set(float x, float y) {
	this->x = x;
	this->y = y;
	
}
void Vector::set(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
}
void Vector::set(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
}



float Vector::getX() {  return this->x; }
float Vector::getY() { return this->y; }
float Vector::getZ() { return this->z; }
float Vector::getW() { return this->w; }
int Vector::getDimension() { return this->dimension; }
float Vector::calcMagnitude() { return sqrt(this->calcQuadrance()); }






