#pragma once

#include <GL/freeglut.h>

#ifndef VECTOR_H
#define VECTOR_H

using namespace std;
//This class is an general implementation of the Vector data model
class Vector
{
private:
	int dimension;
	float x;
	float y;
	float z;
	float w;
	float quadrance;


public:

	virtual  GLfloat* toArray() { GLfloat out[4]; return out; };

	//Constructors of the general model
	Vector();
	Vector(float x, float y);
	Vector(float x, float y, float z);
	Vector(float x, float y, float z, float w);

	//get functions of coordinates
	float getX();
	float getY();
	float getZ();
	float getW();

	//get the vector dimension
	int getDimension();

	//get the vector norm
	float calcMagnitude();

	//get the vector quadrance (for some derived calculations)
	float calcQuadrance();

	//set the vector quadrance
	void setQuadrance(float quadrance);

	//set functions for the coordinates
	void set(float x, float y);
	void set(float x, float y, float z);
	void set(float x, float y, float z, float w);



};



#endif
