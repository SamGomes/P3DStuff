#ifndef OBJECT_H
#define OBJECT_H

#include"glm\glm.hpp"
#include"Ray.h"
#include"Material.h"

enum objType
{
	SPHERE = 0,
	PLANE = 1
};

class Object{

protected:
	glm::vec3 position;
	Material* material;
	objType type;
public:
	glm::vec3 getPosition();
	Material* getMaterial();
	
	void setMaterial(Material* material);
	
	objType getType();
	
	virtual bool hasIntersection(Ray ray) = 0;
	virtual bool getIntersectionPoint(glm::vec3& intersect, Ray ray) = 0;
	virtual glm::vec3 getNormal(glm::vec3 intersectionPoint, Ray ray) = 0;
};


#endif;