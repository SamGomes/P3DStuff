#ifndef CIRCLESAMPLER_H
#define CIRCLESAMPLER_H

#define _USE_MATH_DEFINES

#include "sampler.h"
#include <math.h>

class CircleSampler : public Sampler {

protected:
	void generateSamples();
	std::vector<glm::vec2> CircleSampler::mapSampleToUnitDisk(std::vector<glm::vec2> samples);

public:
	CircleSampler(int numSamples, int numSteps);
};


#endif;