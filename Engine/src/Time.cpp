#include <Core/VDTime.h>
#include <SDL2/SDL_timer.h>
#include <time.h>

long int VDTime::ticks = SDL_GetPerformanceCounter();
long int VDTime::ticksSinceLevel = 0;
long int timeResolution = VDTime::getTimeResolution();
float VDTime::scale = 1.0f;
float VDTime::fixed = 0.016666666667f;

float theDelta;
float delta_data[5];
unsigned int nDeltaTime = sizeof(delta_data) / sizeof(delta_data[0]);
unsigned int idelta = 0;

float VDTime::internal_delta_timef(void){
	double ttime = (double)(SDL_GetPerformanceCounter() - VDTime::ticks) / (double)VDTime::getTimeResolution();
	return (float)ttime *  VDTime::getTimeScale();
}

float VDTime::internal_delta_timed(void){
	double ttime = (double)(SDL_GetPerformanceCounter() - VDTime::ticks) / (double)VDTime::getTimeResolution();
	return ttime *  VDTime::getTimeScale();
}

float VDTime::deltaTime(void){
	return theDelta;
}

double VDTime::deltaTimed(void){
	double ttime = (double)(SDL_GetPerformanceCounter() - VDTime::ticks) / (double)timeResolution;
	return ttime *  VDTime::getTimeScale();
}


float VDTime::smoothDeltaTime(void){
	double ttime = delta_data[0] + delta_data[1] + delta_data[2] + delta_data[3] + delta_data[4];
	return (ttime / (double)nDeltaTime) *  VDTime::getTimeScale();
}

unsigned int VDTime::time(void){
	return SDL_GetTicks();
}

static long int _private_startup = SDL_GetPerformanceCounter();
float VDTime::timef(void){
	return (double)(SDL_GetPerformanceCounter() - _private_startup) / (double)timeResolution;
}

double VDTime::timed(void){
	return (double)SDL_GetPerformanceCounter() / (double)timeResolution;
}

long int VDTime::getUnixTime(void){
	return ::time(NULL);
}

float VDTime::getTimeScale(void){
	return VDTime::scale;
}

void VDTime::setTimeScale(float scale){
	VDTime::scale = scale;
	/*	update fixed update timer	*/
}

static long int _private_level_startup = SDL_GetPerformanceCounter();
float VDTime::timeSinceLevelLoad(void){
	return (double)(SDL_GetPerformanceCounter() - _private_level_startup) / (double)timeResolution;
}

float VDTime::fixedTime(void){
	return fixed / getTimeScale();
}

long int VDTime::getTimeResolution(void){
	return SDL_GetPerformanceFrequency();
}

void VDTime::sleep(long int msec){
	SDL_Delay(msec);
}

void VDTime::internal_update(void){
	theDelta = internal_delta_timef();
	delta_data[idelta] = VDTime::deltaTime();
	++idelta %= nDeltaTime;
	/*	update ticks.	*/
	VDTime::ticks = SDL_GetPerformanceCounter();
}

