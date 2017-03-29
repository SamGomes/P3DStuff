
#include "regularSampler.h"

RegularSampler::RegularSampler(int numSamples, int numSteps) : Sampler(numSamples, numSteps){
	this->generateSamples();
}

void RegularSampler::generateSamples() {

	int n = (int)sqrt(this->numSamples);

	for (int p = 0; p < numSets; p++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				glm::vec2 samplePoint((k + 0.5f) / n, (j + 0.5f) / n);
				samples.push_back(samplePoint);
			}
		}
	}
}