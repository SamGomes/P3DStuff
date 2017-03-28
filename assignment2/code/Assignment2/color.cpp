#include "color.h"


Color::Color(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

float Color::getR() {
	return r;
}
float Color::getG() {
	return g;
}
float Color::getB() {
	return b;
}