#include "UniformGrid.h"

UniformGrid::UniformGrid(float mFactor, std::vector<Object*> objects)
{
	setupBoundingBox(objects);
}



bool UniformGrid::rayCast(Ray ray, glm::vec3 & targetPoint, Object *& targetObject)
{

	glm::vec3 tNext;
	glm::vec3 dt;

	glm::vec3 iStep;
	glm::vec3 iStop;
	
	glm::vec3 tMax, tMin;
	bool rayInsideBB = this->boundingBox.getIntersection(ray,tMin,tMax);

	if (!rayInsideBB) {
		return false;
	}


	//tMin and tMax calculation

	glm::vec3 oldTMin = tMin;

	if (tMin.x > tMax.x){
		tMin.x = tMax.x;
		tMax.x = oldTMin.x;
	}

	if (tMin.y > tMax.y) {
		tMin.y = tMax.y;
		tMax.y = oldTMin.y;
	}

	if (tMin.z > tMax.z) {
		tMin.z = tMax.z;
		tMax.z = oldTMin.z;
	}


	//calculo starting cell
	int ix, iy, iz;
	glm::vec3 rayOrigin = ray.getInitialPoint();
	glm::vec3 rayDir = ray.getDirection();
	glm::vec3 p0 = this->boundingBox.getMinPos();
	glm::vec3 p1 = this->boundingBox.getMaxPos();
	if (this->boundingBox.isInside(rayOrigin)) {
		ix = glm::clamp((rayOrigin.x - p0.x)* nCells.x / (p1.x - p0.x), 0.0f, (float)(nCells.x - 1));
		iy = glm::clamp((rayOrigin.y - p0.y)* nCells.y / (p1.y - p0.y), 0.0f, (float)(nCells.y - 1));
		iz = glm::clamp((rayOrigin.z - p0.z)* nCells.z / (p1.z - p0.z), 0.0f, (float)(nCells.z - 1));
	}
	else {
		glm::vec3 p = rayOrigin + tMin * rayDir;
		ix = glm::clamp((p.x - p0.x)* nCells.x / (p1.x - p0.x), 0.0f, (float)(nCells.x - 1));
		iy = glm::clamp((p.y - p0.y)* nCells.y / (p1.y - p0.y), 0.0f, (float)(nCells.y - 1));
		iz = glm::clamp((p.z - p0.z)* nCells.z / (p1.z - p0.z), 0.0f, (float)(nCells.z - 1));
	}
	GridCell startingCell = this->getCell(ix, iy, iz);

	//dt calc
	dt.x = (tMax.x - tMin.x) / nCells.x;
	dt.y = (tMax.y - tMin.y) / nCells.y;
	dt.z = (tMax.z - tMin.z) / nCells.z;

	//calc initial txNext
	if (tNext.x < tNext.y) {
		ix += 1;
		tNext += dt.x;
	}else{
		iy += 1;
		tNext += dt.y;
	}

	//set up grid traversal
	if (rayDir.x > 0) {
		tNext.x = tMin.x + (ix + 1) * dt.x;
		iStep.x = 1;
		iStop.x = nCells.x;
	}
	else {
		tNext.x = tMin.x + (ix + 1) * dt.x;
		iStep.x = -1;
		iStop.x = -1;
	}
	if (rayDir.x < GRID_EPSILON) {
		tNext.x = INFINITY;
		iStep.x = -1;
		iStop.x = -1;
	}

	//--------------------

	if (rayDir.y > 0) {
		tNext.y = tMin.y + (iy + 1) * dt.y;
		iStep.y = 1;
		iStop.y = nCells.y;
	}
	else {
		tNext.y = tMin.y + (iy + 1) * dt.y;
		iStep.y = -1;
		iStop.x = -1;
	}
	if (rayDir.x < GRID_EPSILON) {
		tNext.x = INFINITY;
		iStep.x = -1;
		iStop.x = -1;
	}

	//--------------------

	if (rayDir.z > 0) {
		tNext.z = tMin.z + (iz + 1) * dt.z;
		iStep.z = 1;
		iStop.z = nCells.z;
	}
	else {
		tNext.z = tMin.z + (iz + 1) * dt.z;
		iStep.z = -1;
		iStop.z = -1;
	}
	if (rayDir.z < GRID_EPSILON) {
		tNext.z = INFINITY;
		iStep.z = -1;
		iStop.z = -1;
	}



	//cell traversal
	for(auto cell: this->cells){

		std::vector<Object*> objects = cell.objects;

		for (auto object : objects) {
			if (tNext.x < tNext.y && tNext.x < tNext.z) {
				Material* mat = object->getMaterial();
				return true;
			}

			tNext.x += dt.x;
			ix += iStep.x;

			if (ix == iStop.x) {
				return false;
			}
			else {
				if (tNext.y < tNext.z) {
					float t = object->hasIntersection(ray);
					if (object && t < tNext.y) {
						Material* mat = object->getMaterial();
						return true;
					}
					tNext.y += dt.y;
					iy += iStep.y;

					if (iy == iStop.y) {
						return false;
					}
				}
				else {
					float t = object->hasIntersection(ray);
					if (object && t < tNext.z) {
						Material* mat = object->getMaterial();
						return true;
					}
					tNext.y += dt.z;
					iz += iStep.z;

					if (iz == iStop.z) {
						return false;
					}
				}
			}
		}
	}
}

GridCell UniformGrid::getCell(int x, int y, int z)
{
	return cells[x + nCells.x * y + nCells.x * nCells.y * z];
}

void UniformGrid::setupBoundingBox(std::vector<Object*> objects)
{
	/*nObjects = objects.size();

	boundingBox.getMinPos = glm::vec3(INFINITY, INFINITY, INFINITY);
	boundingBox.getMaxPos = glm::vec3(-INFINITY, -INFINITY, -INFINITY);

	for (auto object : objects) {
		BoundingBox objectBox = object->getBoundingBox();

		if (objectBox.getMinPos().x < boundingBox.getMinPos().x)
			boundingBox.getMinPos.x = objectBox.getMinPos().x;

		if (objectBox.getMinPos().y < boundingBox.getMinPos().y)
			boundingBox.getMinPos.y = objectBox.getMinPos().y;

		if (objectBox.getMinPos().z < boundingBox.getMinPos().z)
			boundingBox.getMinPos.z = objectBox.getMinPos().z;

		if (objectBox.getMaxPos().x > boundingBox.getMaxPos().x)
			boundingBox.getMaxPos.x = objectBox.getMaxPos().x;

		if (objectBox.getMaxPos().y > boundingBox.getMaxPos().y)
			boundingBox.getMaxPos.y = objectBox.getMaxPos().y;

		if (objectBox.getMaxPos().z > boundingBox.getMaxPos.z)
			boundingBox.getMaxPos.z = objectBox.getMaxPos().z;
	}*/
}
