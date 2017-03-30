#ifndef JITTSAMPLER_H
#define JITTSAMPLER_H

#include "sampler.h"

class JitteredSampler : public Sampler {

protected:
	void generateSamples();
public:
	JitteredSampler(int numSamples, int numSets);
};


#endif;