#ifndef UNITSAMPLER_H
#define UNITSAMPLER_H

#include "sampler.h"

class RegularSampler : public Sampler {

protected:
	void generateSamples();
public:
	RegularSampler(int numSamples, int numSteps);

	
};


#endif;