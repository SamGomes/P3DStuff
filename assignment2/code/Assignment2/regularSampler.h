#ifndef UNITSAMPLER_H
#define UNITSAMPLER_H

#include "sampler.h"

class RegularSampler : public Sampler {

public:
	RegularSampler(int numSamples, int numSets);
	void generateSamples();
	
};


#endif;