#include "Matrix4.h"




Matrix4::Matrix4() : Matrix(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) {

	this->updateData();
	this->setDeterminant(this->calcDeterminant());
}

Matrix4::Matrix4(float pos00, float pos01, float pos02, float pos03,
	float pos10, float pos11, float pos12, float pos13,
	float pos20, float pos21, float pos22, float pos23,
	float pos30, float pos31, float pos32, float pos33):
	Matrix(pos00, pos01,  pos02,  pos03,
			pos10, pos11,  pos12,  pos13,
			pos20,  pos21,  pos22,  pos23,
			pos30, pos31,  pos32, pos33)
{

	this->updateData();
}




//float Matrix4::calcDeterminant()
//{
//	return( ((this->getValue(0, 0)*this->getValue(1, 1)*this->getValue(2, 2))
//		  +  (this->getValue(0, 1)*this->getValue(1, 2)*this->getValue(2, 0))
//		  +  (this->getValue(0, 2)*this->getValue(1, 0)*this->getValue(2, 1)))
//		  -
//			((this->getValue(0, 2)*this->getValue(1, 1)*this->getValue(2, 0))
//		  +  (this->getValue(0, 0)*this->getValue(1, 2)*this->getValue(2, 1))
//		  +  (this->getValue(0, 1)*this->getValue(1, 0)*this->getValue(2, 2)))
//		  );
//}




void Matrix4::set(float pos00, float pos01, float pos02, float pos03,
	float pos10, float pos11, float pos12, float pos13,
	float pos20, float pos21, float pos22, float pos23,
	float pos30, float pos31, float pos32, float pos33)
{
	this->updateData();
	Matrix::set(pos00, pos01, pos02, pos03,
				pos10, pos11, pos12, pos13,
				pos20, pos21, pos22, pos23,
				pos30, pos31, pos32, pos33);
}


Matrix4 Matrix4::operator*(float num) {
	Matrix4 out;
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			out.setValue(i, j, this->getValue(i, j)*num);
		}
	}
	return out;
}

bool Matrix4::operator==(Matrix4 mat)
{
	return  this->getValue(0, 0) == mat.getValue(0, 0) &&
		this->getValue(0, 1) == mat.getValue(0, 1) &&
		this->getValue(0, 2) == mat.getValue(0, 2) &&
		this->getValue(0, 3) == mat.getValue(0, 3) &&
		this->getValue(1, 0) == mat.getValue(1, 0) &&
		this->getValue(1, 1) == mat.getValue(1, 1) &&
		this->getValue(1, 2) == mat.getValue(1, 2) &&
		this->getValue(1, 3) == mat.getValue(1, 3) &&
		this->getValue(2, 0) == mat.getValue(2, 0) &&
		this->getValue(2, 1) == mat.getValue(2, 1) &&
		this->getValue(2, 2) == mat.getValue(2, 2) &&
		this->getValue(3, 1) == mat.getValue(3, 1) &&
		this->getValue(3, 2) == mat.getValue(3, 2) &&
		this->getValue(3, 3) == mat.getValue(3, 3);
}

bool Matrix4::operator!=(Matrix4 mat)
{
	return  this->getValue(0, 0) != mat.getValue(0, 0) ||
		this->getValue(0, 1) != mat.getValue(0, 1) ||
		this->getValue(0, 2) != mat.getValue(0, 2) ||
		this->getValue(0, 3) != mat.getValue(0, 3) ||
		this->getValue(1, 0) != mat.getValue(1, 0) ||
		this->getValue(1, 1) != mat.getValue(1, 1) ||
		this->getValue(1, 2) != mat.getValue(1, 2) ||
		this->getValue(1, 3) != mat.getValue(1, 3) ||
		this->getValue(2, 0) != mat.getValue(2, 0) ||
		this->getValue(2, 1) != mat.getValue(2, 1) ||
		this->getValue(2, 2) != mat.getValue(2, 2) ||
		this->getValue(2, 3) != mat.getValue(2, 3) ||
		this->getValue(3, 1) != mat.getValue(3, 1) ||
		this->getValue(3, 2) != mat.getValue(3, 2) ||
		this->getValue(3, 3) != mat.getValue(3, 3);
}

Matrix4 Matrix4::operator*(Matrix4 mat)
{
	Matrix4 out;
	int i, j, k;
	float sum = 0;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			for (k = 0; k < 4; k++) {
				sum = sum + this->getValue(i, k)*mat.getValue(k, j);
			}
			out.setValue(i, j, sum);
			sum = 0;
		}
	}
	out.updateData();
	return out;
}

Matrix4 Matrix4::operator+(Matrix4 mat)
{
	Matrix4 out;
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			out.setValue(i, j, this->getValue(i, j) + mat.getValue(i, j));
		}
	}
	return out;
}

Matrix4 Matrix4::operator-(Matrix4 mat)
{
	Matrix4 out;
	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			out.setValue(i, j, this->getValue(i, j) - mat.getValue(i, j));
		}
	}
	return out;
}

void Matrix4::operator+=(Matrix4 mat)
{
	*this = this->operator+(mat);
}

void Matrix4::operator*=(Matrix4 mat)
{
	*this = this->operator*(mat);
}

void Matrix4::operator*=(float num)
{
	*this = this->operator*(num);
}

void Matrix4::operator-=(Matrix4 mat)
{
	*this = this->operator-(mat);
}

Matrix4 Matrix4::operator-()
{
	return this->operator*(-1.0f);
}


