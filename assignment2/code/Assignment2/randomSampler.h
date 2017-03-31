#pragma once

#include "sampler.h"

class RandomSampler : public Sampler {

public:
	RandomSampler(int numSamples, int numSets);
	void generateSamples();

};

