#pragma once
#include"Matrix.h"

#include <GL/freeglut.h>

class Matrix4 :public  Matrix {

private:

public:
	

	Matrix4();
	Matrix4(float pos00, float pos01, float pos02, float pos03,
			float pos10, float pos11, float pos12, float pos13,
			float pos20, float pos21, float pos22, float pos23,
			float pos30, float pos31, float pos32, float pos33);


	void set(float pos00, float pos01, float pos02, float pos03,
			float pos10, float pos11, float pos12, float pos13,
			float pos20, float pos21, float pos22, float pos23,
			float pos30, float pos31, float pos32, float pos33);

	
	bool operator==(Matrix4 mat);
	bool operator!=(Matrix4 mat);

	Matrix4 operator*(Matrix4 num);
	Matrix4 operator*(float num);
	Matrix4 operator+(Matrix4 mat);
	Matrix4 operator-(Matrix4 mat);

	void operator+=(Matrix4 mat);
	void operator*=(Matrix4 mat);
	void operator*=(float num);
	void operator-=(Matrix4 mat);

	Matrix4 operator-();

};