#pragma once
#include "Vector.h"
#include "MATRIX/Matrix2.h"

#ifndef VECTOR2_H
#define VECTOR2_H
using namespace std;


class Vector2 :public  Vector
{



public:

	Vector2() {};
	Vector2(float x, float y);

	float getX();
	float getY();


	void set(float x, float y);

	/*returns a new Vector2 that corresponds of the normalized calling Vector2
	(without changing its coordinates)*/
	Vector2 normalized();

	//normalizes the Vector2
	void normalize();

	//overloaded vector of dimension 2 operations

	bool operator==(Vector2 vec);
	bool operator!=(Vector2 vec);
	Vector2 operator*(float num);
	Vector2 operator+(Vector2 vec);
	void operator+=(Vector2 vec);
	void operator*=(float num);
	Vector2 operator-(Vector2 vec);
	Vector2 operator-();
	void operator-=(Vector2 vec);
	
	Vector2 transformed(Matrix2 mat);
	void transform(Matrix2 mat);

	//prints the Vector2 coordinates
	void print();
	
	
};



#endif