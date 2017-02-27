#include "Matrix.h"
#include <math.h>
#include <string>
#include <iostream>
#include <iomanip>
#include"stdio.h"
using namespace std;


void Matrix::updateData()
{

	data[0] = this->getValue(0, 0);
	data[1] = this->getValue(1, 0);
	data[2] = this->getValue(2, 0);
	data[3] = this->getValue(3, 0);
	data[4] = this->getValue(0, 1);
	data[5] = this->getValue(1, 1);
	data[6] = this->getValue(2, 1);
	data[7] = this->getValue(3, 1);
	data[8] = this->getValue(0, 2);
	data[9] = this->getValue(1, 2);
	data[10] = this->getValue(2, 2);
	data[11] = this->getValue(3, 2);
	data[12] = this->getValue(0, 3);
	data[13] = this->getValue(1, 3);
	data[14] = this->getValue(2, 3);
	data[15] = this->getValue(3, 3);
}

Matrix::Matrix()
{
	
}

Matrix::Matrix(float pos00, float pos01, float pos10, float pos11)
{
	this->dimension = 2;

	this->setValue(0, 0, pos00);
	this->setValue(0, 1, pos01);
	this->setValue(1, 0, pos10);
	this->setValue(1, 1, pos11);


}

Matrix::Matrix(float pos00, float pos01, float pos02, float pos10, float pos11, float pos12, float pos20, float pos21, float pos22)
{
	this->dimension = 3;

	this->setValue(0, 0, pos00);
	this->setValue(0, 1, pos01);
	this->setValue(0, 2, pos02);

	this->setValue(1, 0, pos10);
	this->setValue(1, 1, pos11);
	this->setValue(1, 2, pos12);

	this->setValue(2, 0, pos20);
	this->setValue(2, 1, pos21);
	this->setValue(2, 2, pos22);


}
Matrix::Matrix(float pos00, float pos01, float pos02, float pos03,
	float pos10, float pos11, float pos12, float pos13,
	float pos20, float pos21, float pos22, float pos23,
	float pos30, float pos31, float pos32, float pos33) {
	this->dimension = 4;

	this->setValue(0, 0, pos00);
	this->setValue(0, 1, pos01);
	this->setValue(0, 2, pos02);
	this->setValue(0, 3, pos03);

	this->setValue(1, 0, pos10);
	this->setValue(1, 1, pos11);
	this->setValue(1, 2, pos12);
	this->setValue(1, 3, pos13);

	this->setValue(2, 0, pos20);
	this->setValue(2, 1, pos21);
	this->setValue(2, 2, pos22);
	this->setValue(2, 3, pos23);

	this->setValue(3, 0, pos30);
	this->setValue(3, 1, pos31);
	this->setValue(3, 2, pos32);
	this->setValue(3, 3, pos33);
}


void Matrix::setDeterminant(float det)
{
	this->determinant = det;
}


float Matrix::getDeterminant()
{
	return this->determinant;
}

float Matrix::getValue(int row, int column)
{
	return this->matrixStruct[row][column];
}

void Matrix::setValue(int row, int column,float value)
{
	this->updateData();
	this->matrixStruct[row][column]=value;
	this->setDeterminant(this->calcDeterminant());
}




int Matrix::getDimension()
{
	return this->dimension;
}

void Matrix::set(float pos00, float pos01, float pos10, float pos11)
{
	this->setValue(0, 0, pos00);
	this->setValue(0, 1, pos01);
	this->setValue(1, 0, pos10);
	this->setValue(1, 1, pos11);
	this->setDeterminant(this->calcDeterminant());

}

void Matrix::set(float pos00, float pos01, float pos02, float pos10, float pos11, float pos12, float pos20, float pos21, float pos22)
{
	this->setValue(0, 0, pos00);
	this->setValue(0, 1, pos01);
	this->setValue(0, 2, pos02);
	this->setValue(1, 0, pos10);
	this->setValue(1, 1, pos11);
	this->setValue(1, 2, pos12);
	this->setValue(2, 0, pos20);
	this->setValue(2, 1, pos21);
	this->setValue(2, 2, pos22);
	this->setDeterminant(this->calcDeterminant());
}

void Matrix::set(float pos00, float pos01, float pos02, float pos03,
	float pos10, float pos11, float pos12, float pos13,
	float pos20, float pos21, float pos22, float pos23,
	float pos30, float pos31, float pos32, float pos33)
{
	this->setValue(0, 0, pos00);
	this->setValue(0, 1, pos01);
	this->setValue(0, 2, pos02);
	this->setValue(0, 3, pos03);
	this->setValue(1, 0, pos10);
	this->setValue(1, 1, pos11);
	this->setValue(1, 2, pos12);
	this->setValue(1, 3, pos13);
	this->setValue(2, 0, pos20);
	this->setValue(2, 1, pos21);
	this->setValue(2, 2, pos22);
	this->setValue(2, 3, pos23);
	this->setValue(3, 1, pos31);
	this->setValue(3, 2, pos32);
	this->setValue(3, 3, pos33);
}

void Matrix::print()
{
	
	for (int  i = 0; i < this->dimension; i++) {

		cout << "[";
		cout << this->getValue(i,0);
		int j;
		for ( j = 1; j < (this->dimension)-1; j++) {
			cout  << " ";
			cout  << this->getValue(i,j);
			
		}
		cout << " ";
		cout << this->getValue(i,j)<< "]" << endl;
	}
	cout << endl;
}
