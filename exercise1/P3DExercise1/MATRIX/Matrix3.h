#pragma once
#include"Matrix.h"
#include"Matrix2.h"

#include <GL/freeglut.h>

class Matrix3 :public  Matrix {

private:


	Matrix2 submatrix00_01_10_11;
	Matrix2 submatrix01_02_11_12;
	Matrix2 submatrix10_11_20_21;
	Matrix2 submatrix11_12_21_22;

	Matrix2 submatrix00_02_10_12;
	Matrix2 submatrix10_12_20_22;

	Matrix2 submatrix00_01_20_21;
	Matrix2 submatrix01_02_21_22;

	Matrix2 submatrix00_02_20_22;

public:

	Matrix3();
	Matrix3(float pos00, float pos01, float pos02,
			float pos10, float pos11, float pos12,
			float pos20, float pos21, float pos22);


	void set(float pos00, float pos01, float pos02,
		float pos10, float pos11, float pos12,
		float pos20, float pos21, float pos22);

	void initializeSubMatrixes();

	Matrix3 transposed();
	void transpose();

	Matrix3 calcCoefficientMatrix();
	Matrix3 adjugated();

	Matrix3 inversed();
	void invert();


	float calcDeterminant() override;



	bool operator==(Matrix3 mat);
	bool operator!=(Matrix3 mat);

	Matrix3 operator*(Matrix3 num);
	Matrix3 operator*(float num);
	Matrix3 operator+(Matrix3 mat);
	Matrix3 operator-(Matrix3 mat);

	void operator+=(Matrix3 mat);
	void operator*=(Matrix3 mat);
	void operator*=(float num);
	void operator-=(Matrix3 mat);

	Matrix3 operator-();

};