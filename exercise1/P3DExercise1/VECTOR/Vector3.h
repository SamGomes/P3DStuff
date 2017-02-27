#pragma once
#include "Vector.h"
#include "MATRIX/Matrix3.h"

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 : public Vector
{


public:
	 GLfloat data[4];

	void updateData();

	Vector3() {};
	Vector3(float x, float y, float z);

	float getX();
	float getY();
	float getZ();


	void set(float x, float y, float z);

	/*returns a new Vector3 that corresponds of the normalized calling Vector3 
	  (without changing its coordinates)*/
	Vector3 normalized();

	//normalizes the Vector3
	void normalize();

	//overloaded vector of dimension 3 operations

	bool operator==(Vector3 vec);
	bool operator!=(Vector3 vec);
	Vector3 operator*(float num);
	Vector3 operator+(Vector3 vec);
	void operator+=(Vector3 vec);
	void operator*=(float num);
	Vector3 operator-(Vector3 vec);
	Vector3 operator-();
	void operator-=(Vector3 vec);
	float dot(Vector3 vec);
	Vector3 cross(Vector3 vec);
	
	Vector3 transformed(Matrix3 mat);
	void transform(Matrix3 mat);

	//prints the Vector3 coordinates
	void print();
};

#endif
