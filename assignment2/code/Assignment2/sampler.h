#ifndef SAMPLER_H
#define SAMPLER_H

#include "glm\vec2.hpp"
#include <time.h>
#include <algorithm>  
#include <vector>


class Sampler {

protected:

	std::vector<glm::vec2> samples;
	virtual void generateSamples() = 0;

	float unitaryRandom();

	int numSamples;
	int numSets;

	int jump;
	int count;

public:

	Sampler(int numSamples,int numSets);
	void shuffleSamples();
	glm::vec2 nextSample();

	int getNumSamples();
	int getNumSets();


};


#endif;