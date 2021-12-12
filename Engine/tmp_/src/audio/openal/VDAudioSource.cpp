#include <AL/al.h>
#include <Audio/VDAudioClip.h>
#include <Audio/VDAudioSource.h>
#include <stdint.h>

VDAudioSource::VDAudioSource() : VDBehavior(){
	this->clip = 0;
	this->channel = 0;
}
VDAudioSource::VDAudioSource(const VDAudioSource& source): VDBehavior(){

}


void VDAudioSource::instanceInitilize(){}
void VDAudioSource::onEnable(){}
void VDAudioSource::onDisable(){}
void VDAudioSource::onDestroy(){}
void VDAudioSource::initializeComponent(){}
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

VDAudioClip* VDAudioSource::getClip()const{
	return this->clip;
}

void VDAudioSource::play(){
	alSourcePlay((intptr_t)this->channel);
}

void VDAudioSource::pause(){
	alSourcePause((intptr_t)this->channel);
}

void VDAudioSource::stop(){
	alSourceStop((intptr_t)this->channel);
}

void VDAudioSource::mute(bool mute){

}

void VDAudioSource::loop(int loop){
	alSourcei((intptr_t)this->channel, AL_LOOPING, 1);
}

bool VDAudioSource::isPlaying()const{
	int status;
	alGetSourcei((intptr_t)this->channel, AL_SOURCE_STATE, &status);
	return status;
}


void VDAudioSource::AudioMechanicUpdate(VDDoubleBufferedAllocator* allocator){
	unsigned int x;
	int results;
}

