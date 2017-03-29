
#include "randomSampler.h"

RandomSampler::RandomSampler(int numSamples, int numSteps) : Sampler(numSamples, numSteps) {
	this->generateSamples();
}

void RandomSampler::generateSamples() {
	for (int p = 0; p < numSets; p++) {
		for (int j = 0; j < numSamples; j++) {
			glm::vec2 samplePoint(unitaryRandom() - 0.5f, unitaryRandom() - 0.5f);
			samples.push_back(samplePoint);
		}
	}
}