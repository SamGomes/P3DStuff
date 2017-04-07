#ifndef OBJECT_H
#define OBJECT_H

#include "glm\glm.hpp"
#include "Ray.h"
#include "Material.h"
#include "boundingBox.h"

enum objType
{
	SPHERE = 0,
	PLANE = 1,
	TRIANGLE = 2
};

class Object{

protected:
	glm::vec3 position;
	Material* material;
	BoundingBox boundingBox;
	objType type;
public:

	glm::vec3 getPosition();
	Material* getMaterial();
	BoundingBox getBoundingBox();
	
	void setMaterial(Material* material);
	
	objType getType();
	
	virtual bool hasIntersection(Ray ray) = 0;
	virtual bool getIntersectionPoint(glm::vec3& intersect, float& t, Ray ray) = 0;
	virtual glm::vec3 getNormal(glm::vec3 intersectionPoint, Ray ray) = 0;
	virtual bool isInside(glm::vec3 point) = 0;
};


#endif;