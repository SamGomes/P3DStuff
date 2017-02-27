#include "Vector2.h"
#include <math.h>
#include <iostream>
#include"stdio.h"

using namespace std;





Vector2::Vector2(float x, float y) : Vector(x,y){
}



void Vector2::set(float x, float y) {
	Vector::set(x,y);
	
}


float Vector2::getX() { return Vector::getX(); }
float Vector2::getY() { return Vector::getY(); }


 Vector2 Vector2::normalized() {
	Vector2 out;
	if (this->calcMagnitude() == 0) return Vector2(0, 0);
	out.set(this->getX() / this->calcMagnitude(),
		this->getY() / this->calcMagnitude());
	return out;

}

void Vector2::normalize() {

	*this=this->normalized();

}

void Vector2::transform(Matrix2 mat) {
	*this = this->transformed(mat);
}

void Vector2::print() {
	cout << "( " << this->getX() <<" , "<< this->getY()<<" )" << endl;
}

bool Vector2::operator==(Vector2 vec) {
	return ((this->getX() == vec.getX()) && (this->getY() == vec.getY()));
}

bool Vector2::operator!=(Vector2 vec) {
	return ((this->getX() != vec.getX()) || (this->getY() != vec.getY()));
}

Vector2 Vector2::operator* (float num) {
	Vector2* out = new Vector2(0, 0);
	out->set(getX()*num, getY()*num);
	return *out;
}


void Vector2::operator+=(Vector2 vec) {
	*this = this->operator+(vec);
}

void Vector2::operator-=(Vector2 vec) {
	*this = this->operator-(vec);
}

void Vector2::operator*=(float num) {
	*this = this->operator*(num);
}



Vector2 Vector2::operator+(Vector2 vec) {
	Vector2 out;
	out = *(new Vector2(0, 0));
	out.set(this->getX() + vec.getX(), this->getY() + vec.getY());

	return out;
}
Vector2 Vector2::operator-() {


	return *this * -1;
}

Vector2 Vector2::operator-(Vector2 vec) {
	Vector2 out;
	out = *(new Vector2(0, 0));
	out.set(this->getX() - vec.getX(), this->getY() - vec.getY());

	return out;
}

Vector2 Vector2::transformed(Matrix2 mat)
{
	Vector2 out;
	out.set(
		this->getX()*mat.getValue(0, 0) + this->getY()*mat.getValue(0, 1),
		this->getX()*mat.getValue(1, 0) + this->getY()*mat.getValue(1, 1)
		);
	return out;
}

