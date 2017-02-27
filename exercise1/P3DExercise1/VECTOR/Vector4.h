#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Matrix4.h"

#ifndef VECTOR4_H
#define VECTOR4_H

class Vector4 : public Vector
{



public:
	GLfloat data[4];

	void updateData();

	Vector4() {};
	Vector4(float x, float y, float z, float w);

	float getX();
	float getY();
	float getZ();
	float getW();


	void set(float x, float y, float z, float w);

	/*returns a new Vector4 that corresponds of the normalized calling Vector4
	(without changing its coordinates)*/
	Vector4 normalized();

	//normalizes the Vector4
	void normalize();

	//overloaded vector of dimension 4 operations

	bool operator==(Vector4 vec);
	bool operator!=(Vector4 vec);
	Vector4 operator*(float num);
	Vector4 operator+(Vector4 vec);
	void operator+=(Vector4 vec);
	void operator*=(float num);
	Vector4 operator-(Vector4 vec);
	Vector4 operator-();
	void operator-=(Vector4 vec);
	float dot(Vector4 vec);
	Vector4 cross(Vector4 vec);

	Vector4 transformed(Matrix4 mat);
	void transform(Matrix4 mat);

	//prints the Vector3 coordinates
	void print();
};

#endif
