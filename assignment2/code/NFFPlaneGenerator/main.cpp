#include <stdio.h>
#include <iostream>
#include <fstream>


#include "glm\vec3.hpp"

char* filename = "../Assignment2/scene/testAA.nff";
glm::vec3 firstSquareColor(1.0f, 0.0f, 0.0f);
glm::vec3 secondSquareColor(0.0f, 1.0f, 0.0f);

int nSquaresH = 100;
int nSquaresV = 100;

float sizeH = 1000;
float sizeV = 1000;

float initialX = -50;
float initialZ = -500;

void addSquaresToFile(FILE* file) {
	float stepH = sizeH / (float)nSquaresH;
	float stepV = sizeV / (float)nSquaresV;

	//adding the squares
	for (int color = 0; color < 2; color++) {
		glm::vec3 colorVec = (color == 0) ? firstSquareColor : secondSquareColor;
		fprintf(file, "f %f %f %f 1 0 1 0 1\n", colorVec.r, colorVec.g, colorVec.b);

		for (int i = 0; i < nSquaresH; i++) {
			for (int j = 0; j < nSquaresV; j++) {
				if ((i + j) % 2 != color)
					continue;

				float xMin = stepH*i + initialX;
				float xMax = xMin + stepH;
				float zMin = stepV*j + initialZ;
				float zMax = zMin + stepV;

				fprintf(file, "p 3\n");
				fprintf(file, "%f %f %f\n", xMin, 0.0, zMin);
				fprintf(file, "%f %f %f\n", xMax, 0.0, zMin);
				fprintf(file, "%f %f %f\n", xMin, 0.0, zMax);

				fprintf(file, "p 3\n");
				fprintf(file, "%f %f %f\n", xMin, 0.0, zMax);
				fprintf(file, "%f %f %f\n", xMax, 0.0, zMin);
				fprintf(file, "%f %f %f\n", xMax, 0.0, zMax);
			}
		}
	}
}

int main() {
	if (!std::ifstream(filename))
	{
		std::cout << "File doesn't exists" << std::endl;
		return 0;
	}

	FILE* file;
	fopen_s(&file, filename, "a");

	addSquaresToFile(file);
	std::cout << "Plane created!\n" << std::endl;
	return 0;
}