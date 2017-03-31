#include "circleSampler.h"

CircleSampler::CircleSampler(Sampler* baseSampler) : Sampler(baseSampler->getNumSamples(), baseSampler->getNumSets()) {
	this->baseSampler = baseSampler;	
	this->numSamples = baseSampler->getNumSamples();
	this->numSets = baseSampler->getNumSets();
	this->generateSamples();
	this->shuffleSamples();

}

void CircleSampler::generateSamples() {

	int n = (int)sqrt(this->numSamples);

	baseSampler->generateSamples();
	baseSampler->shuffleSamples();

	samples = baseSampler->samples;

	samples = mapSampleToUnitDisk(samples);
}

CircleSampler::~CircleSampler() {
	if (this->baseSampler != NULL) 
		delete this->baseSampler;
}

std::vector<glm::vec2> CircleSampler::mapSampleToUnitDisk(std::vector<glm::vec2> samples) {
	int size = samples.size();
	float r, phi;
	glm::vec2 sp;

	std::vector<glm::vec2> diskSamples;
	diskSamples.reserve(size);

	for (int j = 0; j < size; j++) {
		
		glm::vec2 samplePoint;

		samplePoint.x = 2.0f * samples[j].x - 1.0f;
		samplePoint.y = 2.0f * samples[j].y - 1.0f;

		if (samplePoint.x > -samplePoint.y) {
			if (samplePoint.x > samplePoint.y) {
				r = samplePoint.x;
				phi = samplePoint.y / samplePoint.x;
			}
			else {
				r = samplePoint.y;
				phi = 2 - samplePoint.x / samplePoint.y;
			}
		}
		else
		{
			if (samplePoint.x < samplePoint.y) {
				r = -samplePoint.x;
				phi = 4 + samplePoint.y / samplePoint.x;
			}
			else 
			{
				r = -samplePoint.y;
				if (samplePoint.y != 0.0) {
					phi = 6 - samplePoint.x / samplePoint.y;
				}
				else {
					phi = 0.0;
				}
				
			}
		}
		phi *= (float) M_PI / 4.0f;

		diskSamples.push_back(glm::vec2(r * cos(phi), r * sin(phi)));
	}
	return diskSamples;
}