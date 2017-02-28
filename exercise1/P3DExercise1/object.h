#ifndef OBJECT_H
#define OBJECT_H

#include"glm\glm.hpp"
#include"Ray.h"

enum objType
{
	SPHERE = 0,
	PLANE = 1
};

class Object{

private:
	glm::vec3 position;
	//Material* material;

protected:
	objType type;
public:
	glm::vec3 getPosition();
	//Material* getMaterial();
	
	void setPosition(glm::vec3 position);
	//void setMaterial(Material* material);
	
	objType getType();
	
	virtual bool hasIntersection(Ray ray) = 0;
	virtual bool getIntersectionPoint(glm::vec3* intersect, Ray ray) = 0;
};


#endif;