#include "UniformGrid.h"

#define GRID_EPSILON 0.00001f

UniformGrid::UniformGrid(float mFactor, std::vector<Object*> objects)
{
	setupBoundingBox(objects);

}

bool UniformGrid::rayCast(Ray ray, glm::vec3 & targetPoint, Object *& targetObject)
{
	//TODO: Everything
	return false;
}

GridCell UniformGrid::getCell(int x, int y, int z)
{
	return cells[x + nCells.x * y + nCells.x * nCells.y * z];
}

void UniformGrid::setupBoundingBox(std::vector<Object*> objects)
{
	this->nObjects = objects.size();

	glm::vec3 newMinPos(INFINITY, INFINITY, INFINITY);
	glm::vec3 newMaxPos(-INFINITY, -INFINITY, -INFINITY);

	for (auto object : objects) {
		BoundingBox objectBox = object->getBoundingBox();

		if (objectBox.getMinPos().x < boundingBox.getMinPos().x)
			newMinPos.x = objectBox.getMinPos().x;

		if (objectBox.getMinPos().y < boundingBox.getMinPos().y)
			newMinPos.y = objectBox.getMinPos().y;

		if (objectBox.getMinPos().z < boundingBox.getMinPos().z)
			newMinPos.z = objectBox.getMinPos().z;

		if (objectBox.getMaxPos().x > boundingBox.getMaxPos().x)
			newMaxPos.x = objectBox.getMaxPos().x;

		if (objectBox.getMaxPos().y > boundingBox.getMaxPos().y)
			newMaxPos.y = objectBox.getMaxPos().y;

		if (objectBox.getMaxPos().z > boundingBox.getMaxPos().z)
			newMaxPos.z = objectBox.getMaxPos().z;
	}
	
	newMinPos -= GRID_EPSILON;
	newMaxPos += GRID_EPSILON;

	this->boundingBox.setPoints(newMinPos, newMaxPos);
}
