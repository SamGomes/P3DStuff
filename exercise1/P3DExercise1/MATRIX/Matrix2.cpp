#include "Matrix2.h"

Matrix2::Matrix2() : Matrix(0,0,0,0) {
	this->setDeterminant(this->calcDeterminant());
}

Matrix2::Matrix2(float pos00, float pos01, float pos10, float pos11): Matrix(pos00,pos01,pos10,pos11)
{
	this->setDeterminant(this->calcDeterminant());
}

float Matrix2::calcDeterminant() 
{
	return (this->getValue(0,0)*this->getValue(1,1))- (this->getValue(1, 0)*this->getValue(0, 1));
}


void Matrix2::set(float pos00, float pos01, float pos10, float pos11)
{
	Matrix::set(pos00,pos01,pos10,pos11);
}


Matrix2 Matrix2::transposed()
{
	Matrix2 out;
	int i = 0, j = 0;
	for (i = 0; i < this->getDimension(); i++) {
		for (j = 0; j < this->getDimension(); j++) {
			out.setValue(i, j, this->getValue(j, i));
		}
	}
	return out;
}
void Matrix2::transpose()
{
	*this = this->transposed();
}
Matrix2 Matrix2::inversed()
{
	return Matrix2(-this->getValue(1,1), this->getValue(0,1),  this->getValue(1,0),- this->getValue(0,0))*(1 / -(this->getDeterminant()));
}
void Matrix2::invert()
{
	*this = this->inversed();
}

Matrix2  Matrix2::operator*(float num){
	Matrix2 out;
	int i,j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			out.setValue(i,j,this->getValue(i,j)*num);
		}
	}
	return out;
}

bool Matrix2::operator==(Matrix2 mat)
{
	return  this->getValue(0, 0) == mat.getValue(0, 0) && 
			this->getValue(0, 1) == mat.getValue(0, 1) &&
			this->getValue(1, 0) == mat.getValue(1, 0) &&
			this->getValue(1, 1) == mat.getValue(1, 1);
}

bool Matrix2::operator!=(Matrix2 mat)
{
	return  this->getValue(0, 0) != mat.getValue(0, 0) ||
			this->getValue(0, 1) != mat.getValue(0, 1) ||
			this->getValue(1, 0) != mat.getValue(1, 0) ||
			this->getValue(1, 1) != mat.getValue(1, 1);
}

Matrix2 Matrix2::operator*(Matrix2 mat)
{
	Matrix2 out;
	int i, j,k;
	float sum=0;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			for (k = 0; k < 2; k++) {
				sum = sum + this->getValue(i, k)*mat.getValue(k, j);
			}
			out.setValue(i,j,sum);
			sum = 0;
		}
	}
	return out;
}

Matrix2 Matrix2::operator+(Matrix2 mat)
{
	Matrix2 out;
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			out.setValue(i, j, this->getValue(i, j)+mat.getValue(i,j));
		}
	}
	return out;
}

Matrix2 Matrix2::operator-(Matrix2 mat)
{
	Matrix2 out;
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			out.setValue(i, j, this->getValue(i, j) - mat.getValue(i, j));
		}
	}
	return out;
}

void Matrix2::operator+=(Matrix2 mat)
{
	*this = this->operator+(mat);
}

void Matrix2::operator*=(Matrix2 mat)
{
	*this = this->operator*(mat);
}

void Matrix2::operator-=(Matrix2 mat)
{
	*this = this->operator-(mat);
}


void Matrix2::operator*=(float num)
{
	*this = this->operator*(num);
}


Matrix2 Matrix2::operator-()
{
	return this->operator*(-1.0f);
}
