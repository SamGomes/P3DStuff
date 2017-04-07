#pragma once

#include <vector>

#include "glm\vec3.hpp"
#include "boundingBox.h"
#include "object.h"

typedef struct {
	std::vector<Object*> objects;
	BoundingBox boundingBox;
} GridCell;

class UniformGrid
{
public:
	UniformGrid(float mFactor, std::vector<Object*> objects);
	bool rayCast(Ray ray, glm::vec3& targetPoint, Object*& targetObject);
	int getCellIndex(int x, int y, int z);

private:
	int nObjects;
	glm::ivec3 nCells;
	glm::vec3 worldSize;
	BoundingBox boundingBox;
	std::vector<GridCell> cells;

	void setupBoundingBox(std::vector<Object*> objects);
	void createCells(float mFactor);
	void fillCells(std::vector<Object*> objects);

	glm::ivec3 worldPosToIdx(glm::vec3 point);
	void calcInitialTNext(float& tNext, int& iStep, int& iStop, float pMin, float dt, float rayDir, int i, int nCells);

	Object* traverseGrid(glm::vec3& minIntersection, glm::vec3 pNext, glm::ivec3 iStep, glm::ivec3 iStop, glm::ivec3 i, glm::vec3 dt, Ray ray);
};