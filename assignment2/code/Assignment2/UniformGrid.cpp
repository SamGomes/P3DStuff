#include "UniformGrid.h"

UniformGrid::UniformGrid(float mFactor, std::vector<Object*> objects)
{
	//TODO: Everything
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
