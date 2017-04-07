#include "object.h"



glm::vec3 Object::getPosition()
{
	return this->position;
}

Material * Object::getMaterial()
{
	return this->material;
}

BoundingBox Object::getBoundingBox()
{
	return this->boundingBox;
}

void Object::setMaterial(Material* material)
{
	this->material = material;
}

objType Object::getType()
{
	return this->type;
}


