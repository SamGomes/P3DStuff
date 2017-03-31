
#include "sampler.h"

Sampler::Sampler(int numSamples, int numSets) {
	this->numSamples = numSamples;
	this->numSets = numSets;
	this->count = 0;
	this->jump = 0;

	srand(time(NULL));
}

void Sampler::shuffleSamples() {
	sampleIndexes.reserve(numSamples*numSets);
	std::vector<int> indices;

	for (int i = 0; i < numSamples; i++)
		indices.push_back(i);

	for (int p = 0; p < numSets; p++) {
		std::random_shuffle(indices.begin(), indices.end());
		for (int i = 0; i < numSamples; i++) {
			sampleIndexes.push_back(indices[i]);
		}
	
	}
}

glm::vec2 Sampler::nextSample() {
	if (count % numSamples == 0) {
		jump = (rand() % numSets) * numSamples;
	}
	return (samples[jump + sampleIndexes[jump + count++ % numSamples]]);
}


int Sampler::getNumSamples() {
	return numSamples;
}
int Sampler::getNumSets() {
	return numSets;
}

float Sampler::unitaryRandom() {
	return (float) rand() / (float) RAND_MAX;
}

