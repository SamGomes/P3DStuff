#pragma once
#include"Matrix.h"

class Matrix2 :public  Matrix{

	public:
		
		Matrix2();
		Matrix2(float pos00, float pos01,
			    float pos10, float pos11);



		void set(float pos00, float pos01,
			     float pos10, float pos11);

		Matrix2 transposed();
		void transpose();

		Matrix2 inversed();
		void invert();



		float calcDeterminant() override;



		bool operator==(Matrix2 mat);
		bool operator!=(Matrix2 mat);

		Matrix2 operator*(Matrix2 mat);
		Matrix2 operator*(float num);
		Matrix2 operator+(Matrix2 mat);
		Matrix2 operator-(Matrix2 mat);
		
		void operator+=(Matrix2 mat);
		void operator*=(Matrix2 mat);
		void operator*=(float num);
		void operator-=(Matrix2 mat);

		Matrix2 operator-();

};