#include "circleSampler.h"

CircleSampler::CircleSampler(int numSamples, int numSteps) : Sampler(numSamples, numSteps) {
	this->generateSamples();
}

void CircleSampler::generateSamples() {

	int n = (int)sqrt(this->numSamples);

	for (int p = 0; p < numSets; p++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				glm::vec2 samplePoint((k + unitaryRandom()) / n, (j + unitaryRandom()) / n);
				samples.push_back(samplePoint);
			}
		}
	}
	samples = mapSampleToUnitDisk(samples);
}

std::vector<glm::vec2> CircleSampler::mapSampleToUnitDisk(std::vector<glm::vec2> samples) {
	int size = samples.size();
	float r, phi;
	glm::vec2 sp;

	std::vector<glm::vec2> diskSamples;
	diskSamples.reserve(size);

	for (int j = 0; j < size; j++) {
		
		glm::vec2 samplePoint;

		samplePoint.x = 2.0 * samples[j].x - 1.0;
		samplePoint.y = 2.0 * samples[j].y - 1.0;

		if (samplePoint.x > -samplePoint.y) {
			if (samplePoint.x > -samplePoint.y) {
				r = samplePoint.x;
				phi = 2 - samplePoint.x / samplePoint.y;
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
		phi = M_PI / 4.0;

		diskSamples.push_back(glm::vec2(r * cos(phi), r * sin(phi)));
	}
	return diskSamples;
}