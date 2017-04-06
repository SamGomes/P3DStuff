#include "UniformGrid.h"

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
	nObjects = objects.size();

	//boundingBox.getMinPos = glm::vec3(INFINITY, INFINITY, INFINITY);
	//boundingBox.getMaxPos = glm::vec3(-INFINITY, -INFINITY, -INFINITY);

	for (auto object : objects) {
		BoundingBox objectBox = object->getBoundingBox();

		//if (objectBox.getMinPos().x < boundingBox.getMinPos.x)
		//	boundingBox.getMinPos.x = objectBox.getMinPos().x;

		//if (objectBox.getMinPos().y < boundingBox.getMinPos.y)
		//	boundingBox.getMinPos.y = objectBox.getMinPos().y;

		//if (objectBox.getMinPos().z < boundingBox.getMinPos.z)
		//	boundingBox.getMinPos.z = objectBox.getMinPos().z;

		//if (objectBox.getMaxPos().x > boundingBox.getMaxPos.x)
		//	boundingBox.getMaxPos.x = objectBox.getMaxPos().x;

		//if (objectBox.getMaxPos().y > boundingBox.getMaxPos.y)
		//	boundingBox.getMaxPos.y = objectBox.getMaxPos().y;

		//if (objectBox.getMaxPos().z > boundingBox.getMaxPos.z)
		//	boundingBox.getMaxPos.z = objectBox.getMaxPos().z;
	}
}
