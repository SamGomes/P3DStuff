#include <string>
#include <fstream>
#include <sstream>

#include "scene.h"

Scene::Scene()
{
	std::vector<int> a = { 4, 5, 6, 7 };
	this->camera = new Camera();
	this->backgroundColor = new glm::vec3(0.0f, 0.0f, 0.0f);
	this->lights = new std::vector<Light*>();
	this->materials = new std::vector<Material*>();
	//this->objects = new std::vector<Object*>();
}

Scene::~Scene()
{
	delete this->camera;
	delete this->backgroundColor;

	for (auto it = lights->begin(); it != lights->end(); ++it) {
		delete *it;
	}
	delete lights;

	for (auto it = materials->begin(); it != materials->end(); ++it) {
		delete *it;
	}
	delete materials;

	/*
	for (auto it = objects->begin(); it != objects->end(); ++it) {
		delete *it;
	}
	delete objects;
	*/
}

glm::vec3 * Scene::getBackgroundColor()
{
	return this->backgroundColor;
}

Camera* Scene::getCamera()
{
	return this->camera;
}

std::vector<Light*>* Scene::getLights()
{
	return this->lights;
}

std::vector<Material*>* Scene::getMaterials()
{
	return this->materials;
}

/*
std::vector<Object*>* Scene::getObjects()
{
	return this->objects;
}
*/

bool Scene::loadSceneFromNFF(char * path)
{
	std::ifstream fileStream(path);
	std::string line;
	float x, y, z;
	Material* currentMaterial = NULL;

	if (fileStream.fail()) {
		return false;
	}

	
	while (std::getline(fileStream, line))
	{
		//check v for camera info
		if (line.substr(0, 1) == "v") {

			//Parsing "from"
			if (std::getline(fileStream, line) || line.substr(0, 4) != "from")
				return false; //No "from" info

			std::istringstream fromStream(line.substr(5));
			glm::vec3 from;
			fromStream >> x; fromStream >> y; fromStream >> z;
			from = glm::vec3(x, y, z);

			//Parsing "at"
			if (std::getline(fileStream, line) || line.substr(0, 2) != "at")
				return false; //No "at" info

			std::istringstream atStream(line.substr(3));
			glm::vec3 at;
			atStream >> x; atStream >> y; atStream >> z;
			at = glm::vec3(x, y, z);

			//Parsing "up"
			if (std::getline(fileStream, line) || line.substr(0, 2) != "up")
				return false; //No "up" info

			std::istringstream upStream(line.substr(3));
			glm::vec3 up;
			upStream >> x; upStream >> y; upStream >> z;
			up = glm::vec3(x, y, z);

			//Parsing "angle"
			if (std::getline(fileStream, line) || line.substr(0, 5) != "angle")
				return false; //No "angle" info

			std::istringstream angleStream(line.substr(6));
			float angle;
			angleStream >> angle;

			//Parsing "hither"
			if (std::getline(fileStream, line) || line.substr(0, 6) != "hither")
				return false; //No "hither" info

			std::istringstream hitherStream(line.substr(7));
			float hither;
			hitherStream >> hither;

			//Parsing "resolution"
			if (std::getline(fileStream, line) || line.substr(0, 10) != "resolution")
				return false; //No "resolution" info

			std::istringstream resolutionStream(line.substr(11));
			int resX, resY;
			resolutionStream >> resX; resolutionStream >> resY;

			this->camera->setView(from, at, up);
			this->camera->setProjection(angle, hither, INFINITY, resX, resY);
		}

		//check b for background info
		else if (line.substr(0, 2) == "b ") {

			std::istringstream backgroundStream(line.substr(2));
			backgroundStream >> x; backgroundStream >> y; backgroundStream >> z;
			this->backgroundColor->x = x;
			this->backgroundColor->y = y;
			this->backgroundColor->z = z;
		}

		//check l for light info
		else if (line.substr(0, 2) == "l ") {

			std::istringstream lightStream(line.substr(2));
			glm::vec3 lightPosition, lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

			lightStream >> x; lightStream >> y; lightStream >> z;
			lightPosition = glm::vec3(x, y, z);

			if (lightStream.peek() != EOF) { //FIX ME: EOF or \0, \n
				lightStream >> x; lightStream >> y; lightStream >> z;
				lightColor.x = x, lightColor.y = y, lightColor.z = z;
			}
		}
	}

	return true;
}