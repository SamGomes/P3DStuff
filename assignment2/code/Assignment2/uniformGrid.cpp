#include "UniformGrid.h"

#define GRID_EPSILON 0.00001f

UniformGrid::UniformGrid(float mFactor, std::vector<Object*> objects)
{
	setupBoundingBox(objects);
	createCells(mFactor);
	fillCells(objects);
}

glm::ivec3 UniformGrid::worldPosToIdx(glm::vec3 point) {
	glm::ivec3 i;
	i.x = glm::clamp((int)(((point.x - this->boundingBox.getMinPos().x) / this->worldSize.x)* nCells.x), 0, (nCells.x - 1));
	i.y = glm::clamp((int)(((point.y - this->boundingBox.getMinPos().y) / this->worldSize.y)* nCells.y), 0, (nCells.y - 1));
	i.z = glm::clamp((int)(((point.z - this->boundingBox.getMinPos().z) / this->worldSize.z)* nCells.z), 0, (nCells.z - 1));
	return i;
}

void UniformGrid::calcInitialTNext(float& tNext, int& iStep, int& iStop, float pMin, float dt, float rayDir, int i, int nCells) {
	if (rayDir > 0) {
		tNext = pMin + (i + 1) * dt;
		iStep = 1;
		iStop = nCells;
	}
	else if (rayDir < 0) {
		tNext = pMin + (nCells - i) * dt;
		iStep = -1;
		iStop = -1;
	}
	else  {
		tNext = INFINITY;
		iStep = -1;
		iStop = -1;
	}
}

Object* UniformGrid::traverseGrid(
	glm::vec3& minIntersection, glm::vec3 pNext, glm::ivec3 iStep, glm::ivec3 iStop, 
	glm::ivec3 i, glm::vec3 dt, Ray ray) {

	//cell traversal
	while (true) {

		std::vector<Object*> objects = this->cells[getCellIndex(i.x, i.y, i.z)].objects;

		float minT = INFINITY;
		Object* minTObject = NULL;


		for (auto object : objects) {
			float currT;
			glm::vec3 currIntersection;
			
			if (object->getIntersectionPoint(currIntersection, currT, ray)
				&& currT < minT) {
				minIntersection = currIntersection;
				minT = currT;
				minTObject = object;
			}
		}


		if (pNext.x < pNext.y && pNext.x < pNext.z) {
			if (minTObject && minT < pNext.x) {
				return minTObject;
			}
			pNext.x += dt.x;
			i.x += iStep.x;

			if (i.x == iStop.x){
				return NULL;
			}
		}else if (pNext.y < pNext.z) {
			if (minTObject && minT < pNext.y) {
				return minTObject;
			}
			pNext.y += dt.y;
			i.y += iStep.y;

			if (i.y == iStop.y) {
				return NULL;
			}
		}
		else
		{
			if (minTObject && minT < pNext.z) {
				return minTObject;
			}
			pNext.z += dt.z;
			i.z += iStep.z;

			if (i.z == iStop.z) {
				return NULL;
			}
		}
	}
	return NULL;
}

bool UniformGrid::rayCast(Ray ray, glm::vec3& targetPoint, Object*& targetObject)
{

	glm::vec3 pNext;
	glm::vec3 dt;

	glm::ivec3 iStep;
	glm::ivec3 iStop;
	
	float tProx, tDist;
	glm::vec3 tMin, tMax;

	bool rayInsideBB = this->boundingBox.getIntersection(ray, tProx, tDist, tMin, tMax);
	if (!rayInsideBB) {
		return false;
	}

	glm::ivec3 i;
	glm::vec3 rayOrigin = ray.getInitialPoint();
	glm::vec3 rayDir = ray.getDirection();
	if (this->boundingBox.isInside(rayOrigin)) {
		i = worldPosToIdx(rayOrigin);
	}
	else {
		glm::vec3 pMin = rayOrigin + tProx * rayDir;
		i = worldPosToIdx(pMin);
	}

	//dt calc does this work?
	dt = (tMax - tMin) / (glm::vec3) nCells;

	//calc initial txNext
	pNext = tMin;

	calcInitialTNext(pNext.x, iStep.x, iStop.x, tMin.x, dt.x, rayDir.x, i.x, nCells.x);
	calcInitialTNext(pNext.y, iStep.y, iStop.y, tMin.y, dt.y, rayDir.y, i.y, nCells.y);
	calcInitialTNext(pNext.z, iStep.z, iStop.z, tMin.z, dt.z, rayDir.z, i.z, nCells.z);

	targetObject = traverseGrid(targetPoint, pNext, iStep, iStop, i, dt, ray);

	if (targetObject != NULL)
		return true;
	return false;
	//return (targetObject!=NULL);
}

int UniformGrid::getCellIndex(int x, int y, int z)
{
	return x + nCells.x * y + nCells.x * nCells.y * z;
}

void UniformGrid::setupBoundingBox(std::vector<Object*> objects)
{
	nObjects = objects.size();

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
		
		glm::ivec3 minIndex = worldPosToIdx(object->getBoundingBox().getMinPos());
		glm::ivec3 maxIndex = worldPosToIdx(object->getBoundingBox().getMaxPos());

		for (int x = minIndex.x; x <= maxIndex.x; x++) {
			for (int y = minIndex.y; y <= maxIndex.y; y++) {
				for (int z = minIndex.z; z <= maxIndex.z; z++) {
					cells[getCellIndex(x, y, z)].objects.push_back(object);
				}
			}
		}
	}
}
