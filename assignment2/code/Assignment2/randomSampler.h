#pragma once

#include "sampler.h"

class RandomSampler : public Sampler {

protected:
	void generateSamples();
public:
	RandomSampler(int numSamples, int numSteps);


};

