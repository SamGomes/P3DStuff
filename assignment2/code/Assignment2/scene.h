#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "uniformGrid.h"
#include "camera.h"
#include "light.h"
#include "material.h"
#include "object.h"
#include "glm\vec3.hpp"

class Scene {

private:

	glm::vec3* backgroundColor;
	Camera* camera;
	std::vector<Light*>* lights;
	std::vector<Material*>* materials;
	std::vector<Object*>* objects;

	Sampler* samplerAA;
	Sampler* samplerDOF;

	int numSamplesAA;
	int numSamplesDOF;


	UniformGrid* uniformGrid;

public:
	Scene(int numSamplesAA, int numSamplesDOF);
	~Scene();

	glm::vec3* getBackgroundColor();
	Camera* getCamera();
	std::vector<Light*>* getLights();
	std::vector<Material*>* getMaterials();
	std::vector<Object*>* getObjects();

	Sampler* getSamplerAA();
	Sampler* getSamplerDOF();

	UniformGrid* getUniformGrid();

	bool loadSceneFromNFF(char* path);

};


#endif;