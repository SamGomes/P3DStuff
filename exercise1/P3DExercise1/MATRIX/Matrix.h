#pragma once
#include <GL/freeglut.h>

#ifndef MATRIX_H
#define MATRIX_H

using namespace std;

//This class is an general implementation of the Matrix data model
class Matrix
{

//Common attributes of a matrix
private:
	int dimension; //the dimension of the matrix (2 for 2D, 3 for 3D, ...)
	float determinant; //the determinant of the matrix


protected:

	//(internal) representation of the matrix
	float matrixStruct[4][4];

	//(internal) calculates the determinant (its to be overrided)
	virtual float calcDeterminant() { return 0.0f; };

	//(internal) sets the determinant of the matrix
	void setDeterminant(float det);
	


	//get the Matrix dimension
	int getDimension();

public:
	GLfloat data[16];
	//Constructors of the general model

	void updateData();

	Matrix();
	Matrix(float pos00, float pos01,
		   float pos10, float pos11 );
	Matrix(float pos00, float pos01, float pos02,
		   float pos10, float pos11, float pos12,
		   float pos20, float pos21, float pos22);

	Matrix(float pos00, float pos01, float pos02, float pos03,
		float pos10, float pos11, float pos12, float pos13,
		float pos20, float pos21, float pos22, float pos23,
		float pos30, float pos31, float pos32, float pos33);

	//set functions of the general model

	void set(float pos00, float pos01,
		float pos10, float pos11);
	void set(float pos00, float pos01, float pos02,
		float pos10, float pos11, float pos12,
		float pos20, float pos21, float pos22);
	void set(float pos00, float pos01, float pos02, float pos03,
		float pos10, float pos11, float pos12, float pos13,
		float pos20, float pos21, float pos22, float pos23,
		float pos30, float pos31, float pos32, float pos33);


	//returns the calculated value for determinant
	float getDeterminant();

	//returns the value of the matrix in the position (row,column)
	float getValue(int row, int column);

	//sets the value of the matrix in the position (row,column)
	void setValue(int row, int column, float value);

	//prints the matrix in the format [value value (...)] \n [(...) (...) (...)]
	void print() ;

};

#endif
