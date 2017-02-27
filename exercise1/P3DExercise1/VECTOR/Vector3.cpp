#include "Vector3.h"
#include <math.h>
#include <iostream>
#include"stdio.h"

using namespace std;

 void Vector3::updateData()
{
	data[0] = this->getX();
	data[1] = this->getY();
	data[2] = this->getZ();
	data[3] = this->getW();
 
}

Vector3::Vector3(float x, float y,float z) : Vector(x, y, z){
	this->updateData();
}


void Vector3::set(float x, float y, float z) {
	Vector::set(x,y,z);
	this->updateData();
}


float Vector3::getX() { return Vector::getX(); }
float Vector3::getY() { return Vector::getY(); }
float Vector3::getZ() { return Vector::getZ(); }


void Vector3::print() {
	cout << "( " << this->getX() << " , " << this->getY() << " , " << this->getZ() << " )" << endl;
}

Vector3 Vector3::normalized() {
	Vector3 out;
	if (this->calcMagnitude() == 0) return Vector3(0, 0, 0);
	out.set(this->getX() / this->calcMagnitude(),
		this->getY() / this->calcMagnitude(),
		this->getZ() / this->calcMagnitude());
	return out;

}

void Vector3::normalize() {
	*this = this->normalized();
}

void Vector3::transform(Matrix3 mat) {
	*this = this->transformed(mat);
}




bool Vector3::operator==(Vector3 vec) {
	return ((this->getX() == vec.getX()) && (this->getY() == vec.getY()) && (this->getZ() == vec.getZ()));
}
bool Vector3::operator!=(Vector3 vec) {
	return ((this->getX() != vec.getX()) || (this->getY() != vec.getY()) || (this->getZ() != vec.getZ()));
}

Vector3 Vector3::operator* (float num) {

	Vector3* out = new Vector3(0, 0, 0);
	out->set(getX()*num, getY()*num, getZ()*num);

	return *out;
}

void Vector3::operator+=(Vector3 vec) {
	*this = this->operator+(vec);
}

void Vector3::operator-=(Vector3 vec) {
	*this = this->operator-(vec);
}

void Vector3::operator*=(float num) {
	*this = this->operator*(num);
}

Vector3 Vector3::operator+(Vector3 vec) {

	Vector3 out;
	
	out = *(new Vector3(0, 0, 0));
	out.set(this->getX() + vec.getX(), this->getY() + vec.getY(), this->getZ() + vec.getZ());
		
	return out;
}

Vector3 Vector3::operator-(Vector3 vec) {

	Vector3 out;
	
	out = *(new Vector3(0, 0, 0));
	out.set(this->getX() - vec.getX(), this->getY() - vec.getY(),this->getZ()-vec.getZ());
		
	return out;
}

Vector3 Vector3::operator-() {


	return *this * -1;
}

float Vector3::dot(Vector3 vec) {
	return this->getX() * vec.getX() + this->getY() * vec.getY() + this->getZ() * vec.getZ();
}


Vector3 Vector3::cross(Vector3 vec) {
	Vector3 out;
	out = *(new Vector3(0, 0, 0));
	out.set((this->getY() * vec.getZ()) - (this->getZ() * vec.getY()),
		(this->getZ() * vec.getX()) - (this->getX() * vec.getZ()),
		(this->getX() * vec.getY()) - (this->getY() * vec.getX()));
	return out;
}

Vector3 Vector3::transformed(Matrix3 mat)
{
	Vector3 out;
	out.set(
		this->getX()*mat.getValue(0,0) + this->getY()*mat.getValue(0,1) + this->getZ()*mat.getValue(0,2),
		this->getX()*mat.getValue(1, 0) + this->getY()*mat.getValue(1, 1) + this->getZ()*mat.getValue(1,2),
		this->getX()*mat.getValue(2, 0) + this->getY()*mat.getValue(2, 1) + this->getZ()*mat.getValue(2,2)
		);
	return out;
}
