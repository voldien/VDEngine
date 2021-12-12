#include <Misc/VDRandom.h>
#include <cfloat>
#include <cstdlib>

VDRandom::VDRandom(unsigned long long seed = 7564231ULL){
	this->seed = seed;
	this->mult = 62089911ULL;
	this->llong_max = 4294967295ULL;
	this->float_max = 429467295.0f;
	this->float_max = FLT_MAX;
}

void VDRandom::setSeed(unsigned long long seed){
	this->seed = seed;
}

unsigned int VDRandom::rand(){
	seed = mult * seed;
	return seed % llong_max;
}

float VDRandom::randfNormalize(){
	seed = mult * seed;
	return (seed % llong_max) / float_max;
}

float VDRandom::randf()const{
	return ((float)::rand() / (float)RAND_MAX);
}
