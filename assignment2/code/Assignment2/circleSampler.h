#ifndef CIRCLESAMPLER_H
#define CIRCLESAMPLER_H

#define _USE_MATH_DEFINES

#include "sampler.h"
#include <math.h>

class CircleSampler : public Sampler {

private:
	Sampler* baseSampler;

protected:
	std::vector<glm::vec2> CircleSampler::mapSampleToUnitDisk(std::vector<glm::vec2> samples);

public:
	CircleSampler(Sampler* baseSampler);
	~CircleSampler();
	void generateSamples();
};


#endif;