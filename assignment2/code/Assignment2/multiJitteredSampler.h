#pragma once

#include "sampler.h"

class MultiJitteredSampler : public Sampler {

private:
	void shuffleXCoordinates(int n);
	void shuffleYCoordinates(int n);

public:
	MultiJitteredSampler(int numSamples, int numSets);
	void generateSamples();
};