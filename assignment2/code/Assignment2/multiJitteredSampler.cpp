#include "multiJitteredSampler.h"

MultiJitteredSampler::MultiJitteredSampler(int numSamples, int numSteps) : Sampler(numSamples, numSteps)
{
	this->generateSamples();
}

void MultiJitteredSampler::generateSamples()
{
	int n = (int)sqrt(this->numSamples);

	for (int p = 0; p < numSets; p++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				glm::vec2 innerGridPoint((j + unitaryRandom()) / n, (k + unitaryRandom()) / n);
				glm::vec2 samplePoint((k + innerGridPoint.x) / n, (j + innerGridPoint.y) / n);
				samples.push_back(samplePoint);
			}
		}
	}
	shuffleXCoordinates(n);
	shuffleYCoordinates(n);
}

void MultiJitteredSampler::shuffleXCoordinates(int n){
	for (int p = 0; p < numSets; p++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int shuffleIndex = p*numSamples + i*n + (rand() % n);
				int currentIndex = p*numSamples + i*n + j;
				float temp = samples[currentIndex].x;
				samples[currentIndex].x = samples[shuffleIndex].x;
				samples[shuffleIndex].x = temp;
			}
		}
	}
}



void MultiJitteredSampler::shuffleYCoordinates(int n)
{
	for (int p = 0; p < numSets; p++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int shuffleIndex = p*numSamples + (rand() % n)*n + j;
				int currentIndex = p*numSamples + i*n + j;
				float temp = samples[currentIndex].y;
				samples[currentIndex].y = samples[shuffleIndex].y;
				samples[shuffleIndex].y = temp;
			}
		}
	}
}