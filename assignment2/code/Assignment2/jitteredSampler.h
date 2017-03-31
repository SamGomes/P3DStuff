#ifndef JITTSAMPLER_H
#define JITTSAMPLER_H

#include "sampler.h"

class JitteredSampler : public Sampler {

public:
	JitteredSampler(int numSamples, int numSets);
	void generateSamples();
};


#endif;