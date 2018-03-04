#include <AL/al.h>
#include <Audio/VDAudioClip.h>
#include <Audio/VDAudioSource.h>
#include <stdint.h>

VDAudioSource::VDAudioSource(void) : VDBehavior(){
	this->clip = 0;
	this->channel = 0;
}
VDAudioSource::VDAudioSource(const VDAudioSource& source): VDBehavior(){

}


void VDAudioSource::instanceInitilize(void){}
void VDAudioSource::onEnable(void){}
void VDAudioSource::onDisable(void){}
void VDAudioSource::onDestroy(void){}
void VDAudioSource::initializeComponent(void){}
VDBehavior* VDAudioSource::copyComponent(unsigned int& dataSize){}


void VDAudioSource::setClip(VDAudioClip* clip){
	if(this->clip){
		this->clip->deincrement();
		this->clip = clip;
	}
	this->clip = clip;
	if(this->clip)
		this->clip->increment();
}

VDAudioClip* VDAudioSource::getClip(void)const{
	return this->clip;
}

void VDAudioSource::play(void){
	alSourcePlay((intptr_t)this->channel);
}

void VDAudioSource::pause(void){
	alSourcePause((intptr_t)this->channel);
}

void VDAudioSource::stop(void){
	alSourceStop((intptr_t)this->channel);
}

void VDAudioSource::mute(bool mute){

}

void VDAudioSource::loop(int loop){
	alSourcei((intptr_t)this->channel, AL_LOOPING, 1);
}

bool VDAudioSource::isPlaying(void)const{
	int status;
	alGetSourcei((intptr_t)this->channel, AL_SOURCE_STATE, &status);
	return status;
}


void VDAudioSource::AudioMechanicUpdate(VDDoubleBufferedAllocator* allocator){
	unsigned int x;
	int results;
}

