#include <string>
#include <fstream>
#include <sstream>

#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "multiJitteredSampler.h"
#include "jitteredSampler.h"


#include "scene.h"

Scene::Scene(int numSamplesAA, int numSamplesDOF)
{
	std::vector<int> a = { 4, 5, 6, 7 };
	this->backgroundColor = new glm::vec3(0.0f, 0.0f, 0.0f);
	this->lights = new std::vector<Light*>();
	this->materials = new std::vector<Material*>();
	this->objects = new std::vector<Object*>();
	
	this->numSamplesDOF = numSamplesDOF*numSamplesDOF;
	this->numSamplesAA = numSamplesAA*numSamplesAA;
	samplerAA = new JitteredSampler(this->numSamplesAA, 83); //83 is the magic number, or is it?
	samplerDOF = new MultiJitteredSampler(this->numSamplesDOF, 83);

	this->camera = new Camera(samplerAA,samplerDOF);

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

	
	for (auto it = objects->begin(); it != objects->end(); ++it) {
		delete *it;
	}
	delete objects;

	if (samplerAA != NULL) delete samplerAA;
	if (samplerDOF != NULL) delete samplerDOF;
}

glm::vec3 * Scene::getBackgroundColor()
{
	return this->backgroundColor;
}

Sampler* Scene::getSamplerAA()
{
	return samplerAA;
}

Sampler* Scene::getSamplerDOF()
{
	return samplerDOF;
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


std::vector<Object*>* Scene::getObjects()
{
	return this->objects;
}


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
			if (!std::getline(fileStream, line) || line.substr(0, 4) != "from")
				return false; //No "from" info

			std::istringstream fromStream(line.substr(5));
			glm::vec3 from;
			fromStream >> x; fromStream >> y; fromStream >> z;
			from = glm::vec3(x, y, z);

			//Parsing "at"
			if (!std::getline(fileStream, line) || line.substr(0, 2) != "at")
				return false; //No "at" info

			std::istringstream atStream(line.substr(3));
			glm::vec3 at;
			atStream >> x; atStream >> y; atStream >> z;
			at = glm::vec3(x, y, z);

			//Parsing "up"
			if (!std::getline(fileStream, line) || line.substr(0, 2) != "up")
				return false; //No "up" info

			std::istringstream upStream(line.substr(3));
			glm::vec3 up;
			upStream >> x; upStream >> y; upStream >> z;
			up = glm::vec3(x, y, z);

			//Parsing "angle"
			if (!std::getline(fileStream, line) || line.substr(0, 5) != "angle")
				return false; //No "angle" info

			std::istringstream angleStream(line.substr(6));
			float angle;
			angleStream >> angle;

			//Parsing "hither"
			if (!std::getline(fileStream, line) || line.substr(0, 6) != "hither")
				return false; //No "hither" info

			std::istringstream hitherStream(line.substr(7));
			float hither;
			hitherStream >> hither;

			//Parsing "resolution"
			if (!std::getline(fileStream, line) || line.substr(0, 10) != "resolution")
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

			if (lightStream.peek() != EOF) {
				lightStream >> x; lightStream >> y; lightStream >> z;
				lightColor.x = x, lightColor.y = y, lightColor.z = z;
			}

			this->lights->push_back(new Light(lightPosition, lightColor));
		}

		//check f for material info
		else if (line.substr(0, 2) == "f ") {

		std::istringstream materialStream(line.substr(2));
		glm::vec3 materialColor;
		float materialDiffuse, materialSpecular, materialShininess, 
				materialTransmittance, materialIndexOfRefraction;

		materialStream >> x; materialStream >> y; materialStream >> z;
		materialStream >> materialDiffuse; materialStream >> materialSpecular; 
		materialStream >> materialShininess; materialStream >> materialTransmittance;
		materialStream >> materialIndexOfRefraction;
		materialColor = glm::vec3(x, y, z);

		Material* newMaterial = new Material(materialColor, materialDiffuse, materialSpecular,
			materialShininess, materialTransmittance, materialIndexOfRefraction);
		this->materials->push_back(newMaterial);
		currentMaterial = newMaterial;
	}

		//check s for sphere info
		else if (line.substr(0, 2) == "s ") {

			std::istringstream sphereStream(line.substr(2));
			glm::vec3 spherePosition;
			float sphereRadius;

			sphereStream >> x; sphereStream >> y; sphereStream >> z; 
			spherePosition = glm::vec3(x, y, z);
			sphereStream >> sphereRadius;

			Sphere * newSphere = new Sphere(spherePosition, sphereRadius);
			newSphere->setMaterial(currentMaterial);
			this->objects->push_back(newSphere);
		
		}

		//check pl for plane info
		else if (line.substr(0, 3) == "pl ") {

			std::istringstream planeStream(line.substr(3));
			glm::vec3 planePosition1, planePosition2, planePosition3;

			planeStream >> x; planeStream >> y; planeStream >> z;
			planePosition1 = glm::vec3(x, y, z);

			planeStream >> x; planeStream >> y; planeStream >> z;
			planePosition2 = glm::vec3(x, y, z);

			planeStream >> x; planeStream >> y; planeStream >> z;
			planePosition3 = glm::vec3(x, y, z);

			Plane * newPlane = new Plane(planePosition1, planePosition2, planePosition3);
			newPlane->setMaterial(currentMaterial);
			this->objects->push_back(newPlane);
		}

		//check p for triangulized polygon
		else if (line.substr(0, 2) == "p ") {

			int totalVertices = std::stoi(line.substr(2, 3));

			for (int i = 0; i < totalVertices; i+=3) {
				std::string insideLine;
				std::getline(fileStream, insideLine);

				std::istringstream triangleStream(insideLine);
				glm::vec3 trianglePosition1, trianglePosition2, trianglePosition3;

				triangleStream >> x; triangleStream >> y; triangleStream >> z;
				trianglePosition1 = glm::vec3(x, y, z);

				std::getline(fileStream, insideLine);
				triangleStream = std::istringstream(insideLine);
				
				triangleStream >> x; triangleStream >> y; triangleStream >> z;
				trianglePosition2 = glm::vec3(x, y, z);

				std::getline(fileStream, insideLine);
				triangleStream = std::istringstream(insideLine);

				triangleStream >> x; triangleStream >> y; triangleStream >> z;
				trianglePosition3 = glm::vec3(x, y, z);

				Triangle * newTriangle = new Triangle(trianglePosition1, trianglePosition2, trianglePosition3);
				newTriangle->setMaterial(currentMaterial);
				this->objects->push_back(newTriangle);
				
			}


		}

	}

	return true;
}