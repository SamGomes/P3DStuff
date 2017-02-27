#include "Vector4.h"
#include <math.h>
#include <iostream>
#include"stdio.h"

using namespace std;

void Vector4::updateData()
{
	data[0] = this->getX();
	data[1] = this->getY();
	data[2] = this->getZ();
	data[3] = this->getW();

}

Vector4::Vector4(float x, float y, float z, float w) : Vector(x, y, z, w) {
	this->updateData();
}


void Vector4::set(float x, float y, float z, float w) {
	Vector::set(x, y, z, w);
	this->updateData();
}


float Vector4::getX() { return Vector::getX(); }
float Vector4::getY() { return Vector::getY(); }
float Vector4::getZ() { return Vector::getZ(); }
float Vector4::getW() { return Vector::getW(); }


void Vector4::print() {
	cout << "( " << this->getX() << " , " << this->getY() << " , " << this->getZ() <<", " << this->getW() << " )" << endl;
}

Vector4 Vector4::normalized() {
	Vector4 out;
	if (this->calcMagnitude() == 0) {
		return Vector4(0, 0, 0, 1);
	}
	float s = 1 / (this->getW() * sqrt(this->getX()*this->getX() + this->getY()*this->getY() + this->getZ()*this->getZ()));
	out.set(this->getX() *s,
		this->getY() *s,
		this->getZ() *s,1);
	return out;
	
}

void Vector4::normalize() {
	*this = this->normalized();
}

void Vector4::transform(Matrix4 mat) {
	*this = this->transformed(mat);
}




bool Vector4::operator==(Vector4 vec) {
	return ((this->getX() == vec.getX()) && (this->getY() == vec.getY()) && (this->getZ() == vec.getZ()));
}
bool Vector4::operator!=(Vector4 vec) {
	return ((this->getX() != vec.getX()) || (this->getY() != vec.getY()) || (this->getZ() != vec.getZ()));
}

Vector4 Vector4::operator* (float num) {

	Vector4* out = new Vector4(0, 0, 0,0);
	out->set(getX()*num, getY()*num, getZ()*num,1);

	return *out;
}

void Vector4::operator+=(Vector4 vec) {
	*this = this->operator+(vec);
}

void Vector4::operator-=(Vector4 vec) {
	*this = this->operator-(vec);
}

void Vector4::operator*=(float num) {
	*this = this->operator*(num);
}

Vector4 Vector4::operator+(Vector4 vec) {

	Vector4 out;

	out = *(new Vector4(0, 0, 0, 0));
	out.set(this->getX() + vec.getX(), this->getY() + vec.getY(), this->getZ() + vec.getZ(), this->getW() + vec.getW());

	return out;
}

Vector4 Vector4::operator-(Vector4 vec) {

	Vector4 out;

	out = *(new Vector4(0, 0, 0, 0));
	out.set(this->getX() - vec.getX(), this->getY() - vec.getY(), this->getZ() - vec.getZ(), this->getZ() - vec.getW());

	return out;
}

Vector4 Vector4::operator-() {


	return *this * -1;
}

float Vector4::dot(Vector4 vec) {
	return this->getX() * vec.getX() + this->getY() * vec.getY() + this->getZ() * vec.getZ() + this->getW() * vec.getW();
}


Vector4 Vector4::cross(Vector4 vec) {
	Vector4 out;
	out = *(new Vector4(0, 0, 0, 0));
	out.set((this->getY() * vec.getZ()) - (this->getZ() * vec.getY()),
		(this->getZ() * vec.getX()) - (this->getX() * vec.getZ()),
		(this->getX() * vec.getY()) - (this->getY() * vec.getX()),1);
	return out;
}

Vector4 Vector4::transformed(Matrix4 mat)
{
	Vector4 out;
	out.set(
		this->getX()*mat.getValue(0, 0) + this->getY()*mat.getValue(0, 1) + this->getZ()*mat.getValue(0, 2) + this->getW()* mat.getValue(0,3),
		this->getX()*mat.getValue(1, 0) + this->getY()*mat.getValue(1, 1) + this->getZ()*mat.getValue(1, 2) + this->getW()* mat.getValue(1, 3),
		this->getX()*mat.getValue(2, 0) + this->getY()*mat.getValue(2, 1) + this->getZ()*mat.getValue(2, 2) + this->getW()* mat.getValue(2, 3),
		this->getX()*mat.getValue(3, 0) + this->getY()*mat.getValue(3, 1) + this->getZ()*mat.getValue(3, 2) + this->getW()* mat.getValue(3, 3) );
	return out;
}
