#pragma once

#include "sampler.h"

class MultiJitteredSampler : public Sampler {

private:
	void shuffleXCoordinates(int n);
	void shuffleYCoordinates(int n);

protected:
	void generateSamples();
public:
	MultiJitteredSampler(int numSamples, int numSteps);
};