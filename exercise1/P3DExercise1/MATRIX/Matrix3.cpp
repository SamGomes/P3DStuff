#include "Matrix3.h"


 

Matrix3::Matrix3() : Matrix(0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0) {

	this->initializeSubMatrixes();
	this->updateData();
	this->setDeterminant(this->calcDeterminant());
}

Matrix3::Matrix3(float pos00, float pos01, float pos02, float pos10, float pos11, float pos12, float pos20, float pos21, float pos22) :
	     Matrix(pos00, pos01, pos02,pos10, pos11, pos12,pos20, pos21, pos22)
{

	this->initializeSubMatrixes();
	this->updateData();
	this->setDeterminant(this->calcDeterminant());
}




//float Matrix3::calcDeterminant()
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

float Matrix3::calcDeterminant()
{
	this->initializeSubMatrixes();
	return (this->getValue(0, 0)*this->submatrix11_12_21_22.getDeterminant()
		 - this->getValue(0, 1)*this->submatrix10_12_20_22.getDeterminant()
		 + this->getValue(0, 2)*this->submatrix10_11_20_21.getDeterminant());
}


void Matrix3::set(float pos00, float pos01, float pos02, float pos10, float pos11, float pos12, float pos20, float pos21, float pos22)
{
	this->initializeSubMatrixes();
	this->updateData();
	Matrix::set(pos00, pos01, pos02,
				pos10, pos11, pos12,
				pos20, pos21, pos22);
}

void Matrix3::initializeSubMatrixes()
{

	submatrix00_01_10_11
		= Matrix2(this->getValue(0, 0), this->getValue(0, 1), this->getValue(1, 0), this->getValue(1, 1));
	submatrix01_02_11_12
		= Matrix2(this->getValue(0, 1), this->getValue(0, 2), this->getValue(1, 1), this->getValue(1, 2));
	submatrix10_11_20_21
		= Matrix2(this->getValue(1, 0), this->getValue(1, 1), this->getValue(2, 0), this->getValue(2, 1));
	submatrix11_12_21_22
		= Matrix2(this->getValue(1, 1), this->getValue(1, 2), this->getValue(2, 1), this->getValue(2, 2));

	submatrix00_02_10_12
		= Matrix2(this->getValue(0, 0), this->getValue(0, 2), this->getValue(1, 0), this->getValue(1, 2));
	submatrix10_12_20_22
		= Matrix2(this->getValue(1, 0), this->getValue(1, 2), this->getValue(2, 0), this->getValue(2, 2));

	submatrix00_01_20_21
		= Matrix2(this->getValue(0, 0), this->getValue(0, 1), this->getValue(2, 0), this->getValue(2, 1));
	submatrix01_02_21_22
		= Matrix2(this->getValue(0, 1), this->getValue(0, 2), this->getValue(2, 1), this->getValue(2, 2));

	submatrix00_02_20_22
		= Matrix2(this->getValue(0, 0), this->getValue(0, 2), this->getValue(2, 0), this->getValue(2, 2));

}


Matrix3 Matrix3::transposed()
{
	Matrix3 out;
	int i = 0, j = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			out.setValue(i, j, this->getValue(j, i));
		}
	}
	return out;
}
void Matrix3::transpose()
{
	*this = this->transposed();
}
Matrix3 Matrix3::calcCoefficientMatrix()
{
	Matrix3 out;
	out.setValue(0, 0, this->submatrix11_12_21_22.getDeterminant());
	out.setValue(0, 1, -this->submatrix10_12_20_22.getDeterminant());
	out.setValue(0, 2, this->submatrix10_11_20_21.getDeterminant());

	out.setValue(1, 0, -this->submatrix01_02_21_22.getDeterminant());
	out.setValue(1, 1, this->submatrix00_02_20_22.getDeterminant());
	out.setValue(1, 2, -this->submatrix00_01_20_21.getDeterminant());

	out.setValue(2, 0, this->submatrix01_02_11_12.getDeterminant());
	out.setValue(2, 1, -this->submatrix00_02_10_12.getDeterminant());
	out.setValue(2, 2, this->submatrix00_01_10_11.getDeterminant());

	return out;
}
Matrix3 Matrix3::adjugated()
{
	return this->calcCoefficientMatrix().transposed();
}
Matrix3 Matrix3::inversed()
{
	return  this->adjugated() * (1/this->getDeterminant()) ;
}
void Matrix3::invert()
{
	*this = this->inversed();
}

Matrix3 Matrix3::operator*(float num){
	Matrix3 out;
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			out.setValue(i, j, this->getValue(i, j)*num);
		}
	}
	return out;
}

bool Matrix3::operator==(Matrix3 mat)
{
	return  this->getValue(0, 0) == mat.getValue(0, 0) &&
			this->getValue(0, 1) == mat.getValue(0, 1) &&
			this->getValue(0, 2) == mat.getValue(0, 2) &&
			this->getValue(1, 0) == mat.getValue(1, 0) &&
			this->getValue(1, 1) == mat.getValue(1, 1) &&
			this->getValue(1, 2) == mat.getValue(1, 2) &&
			this->getValue(2, 0) == mat.getValue(2, 0) &&
			this->getValue(2, 1) == mat.getValue(2, 1) &&
			this->getValue(2, 2) == mat.getValue(2, 2);
}

bool Matrix3::operator!=(Matrix3 mat)
{
	return  this->getValue(0, 0) != mat.getValue(0, 0) ||
			this->getValue(0, 1) != mat.getValue(0, 1) ||
			this->getValue(0, 2) != mat.getValue(0, 2) ||
			this->getValue(1, 0) != mat.getValue(1, 0) ||
			this->getValue(1, 1) != mat.getValue(1, 1) ||
			this->getValue(1, 2) != mat.getValue(1, 2) ||
			this->getValue(2, 0) != mat.getValue(2, 0) ||
			this->getValue(2, 1) != mat.getValue(2, 1) ||
			this->getValue(2, 2) != mat.getValue(2, 2); 
}

Matrix3 Matrix3::operator*(Matrix3 mat)
{
	Matrix3 out;
	int i, j, k;
	float sum = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				sum = sum + this->getValue(i, k)*mat.getValue(k, j);
			}
			out.setValue(i, j, sum);
			sum = 0;
		}
	}
	return out;
}

Matrix3 Matrix3::operator+(Matrix3 mat)
{
	Matrix3 out;
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			out.setValue(i, j, this->getValue(i, j) + mat.getValue(i, j));
		}
	}
	return out;
}

Matrix3 Matrix3::operator-(Matrix3 mat)
{
	Matrix3 out;
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			out.setValue(i, j, this->getValue(i, j) - mat.getValue(i, j));
		}
	}
	return out;
}

void Matrix3::operator+=(Matrix3 mat)
{
	*this = this->operator+(mat);
}

void Matrix3::operator*=(Matrix3 mat)
{
	*this = this->operator*(mat);
}

void Matrix3::operator*=(float num)
{
	*this = this->operator*(num);
}

void Matrix3::operator-=(Matrix3 mat)
{
	*this = this->operator-(mat);
}

Matrix3 Matrix3::operator-()
{
	return this->operator*(-1.0f);
}


