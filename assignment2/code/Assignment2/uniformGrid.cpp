#include "UniformGrid.h"

#define GRID_EPSILON 0.00001f

UniformGrid::UniformGrid(float mFactor, std::vector<Object*> objects)
{
	setupBoundingBox(objects);
	createCells(mFactor);
	fillCells(objects);
}

bool UniformGrid::rayCast(Ray ray, glm::vec3 & targetPoint, Object *& targetObject)
{
	//TODO: Everything
	return false;
}

int UniformGrid::getCellIndex(int x, int y, int z)
{
	return x + nCells.x * y + nCells.x * nCells.y * z;
}

void UniformGrid::setupBoundingBox(std::vector<Object*> objects)
{
	this->nObjects = objects.size();

	glm::vec3 newMinPos(INFINITY, INFINITY, INFINITY);
	glm::vec3 newMaxPos(-INFINITY, -INFINITY, -INFINITY);

	for (auto object : objects) {
		BoundingBox objectBox = object->getBoundingBox();

		if (objectBox.getMinPos().x < newMinPos.x)
			newMinPos.x = objectBox.getMinPos().x;

		if (objectBox.getMinPos().y < newMinPos.y)
			newMinPos.y = objectBox.getMinPos().y;

		if (objectBox.getMinPos().z < newMinPos.z)
			newMinPos.z = objectBox.getMinPos().z;

		if (objectBox.getMaxPos().x > newMaxPos.x)
			newMaxPos.x = objectBox.getMaxPos().x;

		if (objectBox.getMaxPos().y > newMaxPos.y)
			newMaxPos.y = objectBox.getMaxPos().y;

		if (objectBox.getMaxPos().z > newMaxPos.z)
			newMaxPos.z = objectBox.getMaxPos().z;
	}
	
	newMinPos -= GRID_EPSILON;
	newMaxPos += GRID_EPSILON;

	this->boundingBox.setPoints(newMinPos, newMaxPos);
	this->worldSize = newMaxPos - newMinPos;
}

void UniformGrid::createCells(float mFactor)
{
	float objectToVolumeRatio = cbrtf(nObjects / (worldSize.x * worldSize.y * worldSize.z) );

	this->nCells.x = (int)(mFactor * worldSize.x * objectToVolumeRatio) + 1;
	this->nCells.y = (int)(mFactor * worldSize.y * objectToVolumeRatio) + 1;
	this->nCells.z = (int)(mFactor * worldSize.z * objectToVolumeRatio) + 1;

	GridCell aux;
	this->cells = std::vector<GridCell>(this->nCells.x * this->nCells.y * this->nCells.z, aux);
}

void UniformGrid::fillCells(std::vector<Object*> objects)
{
	for (auto object : objects) {
		glm::vec3 minPosRelative = ((object->getBoundingBox().getMinPos() - this->boundingBox.getMinPos()) / this->worldSize);
		glm::vec3 maxPosRelative = ((object->getBoundingBox().getMaxPos() - this->boundingBox.getMinPos()) / this->worldSize);

		int minIndexX = glm::clamp((int)(minPosRelative.x * nCells.x), 0, this->nCells.x - 1);
		int minIndexY = glm::clamp((int)(minPosRelative.y * nCells.y), 0, this->nCells.y - 1);
		int minIndexZ = glm::clamp((int)(minPosRelative.z * nCells.z), 0, this->nCells.z - 1);

		int maxIndexX = glm::clamp((int)(maxPosRelative.x * nCells.x), 0, this->nCells.x - 1);
		int maxIndexY = glm::clamp((int)(maxPosRelative.y * nCells.y), 0, this->nCells.y - 1);
		int maxIndexZ = glm::clamp((int)(maxPosRelative.z * nCells.z), 0, this->nCells.z - 1);

		for (int x = minIndexX; x <= maxIndexX; x++) {
			for (int y = minIndexY; y <= maxIndexY; y++) {
				for (int z = minIndexZ; z <= maxIndexZ; z++) {
					cells[getCellIndex(x, y, z)].objects.push_back(object);
				}
			}
		}
	}
}
