
#include "sampler.h"

Sampler::Sampler(int numSamples, int numSets) {
	this->numSamples = numSamples;
	this->numSets = numSets;

	srand(time(NULL));
}

void Sampler::shuffleSamples() {
	std::random_shuffle(samples.begin(), samples.end());
}

glm::vec2 Sampler::nextSample() {
	if (count % numSamples == 0) {
		jump = (rand() % numSets) * numSamples;
	}
	return (samples[jump + count++ % numSamples]);
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

