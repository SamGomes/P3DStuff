#ifndef SAMPLER_H
#define SAMPLER_H

#include "glm\vec2.hpp"
#include <time.h>
#include <algorithm>  
#include <vector>


class Sampler {

public: //vars
	std::vector<glm::vec2> samples;

protected: //vars
	std::vector<int> sampleIndexes;
	int numSamples;
	int numSets;
	int jump;
	unsigned long count;



protected: //methods
	float unitaryRandom();


public: //methods
	Sampler(int numSamples,int numSets);
	void shuffleSamples();
	glm::vec2 nextSample();

	int getNumSamples();
	int getNumSets();

	virtual void generateSamples() = 0;

};


#endif;