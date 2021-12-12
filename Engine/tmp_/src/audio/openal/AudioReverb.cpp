#include"VDAudioReverb.h"
#include"VDEngine.h"

#define DEFAULT_MIN_RANGE 10
#define DEFAULT_MAX_RANGE 100

VDAudioReverb::VDAudioReverb() : VDBehavior(){
	this->reverb = nullptr;
}

VDAudioReverb::VDAudioReverb(const VDAudioReverb& audio) : VDBehavior(){
	this->reverb = nullptr;
}

void VDAudioReverb::instanceInitilize(){

}

void VDAudioReverb::onEnable(){
	if(this->reverb){
		//this->reverb->setActive(true);
	}
}

void VDAudioReverb::onDisable(){
	if(this->reverb){
		//this->reverb->setActive(false);
	}
}

void VDAudioReverb::onDestroy(){
	if(this->reverb){
		//this->reverb->release();
	}
}

void VDAudioReverb::initializeComponent(){

}

VDBehavior* VDAudioReverb::copyComponent(unsigned int& dataSize){
	VDAudioReverb* audioReverb = (VDAudioReverb*)malloc(sizeof(VDAudioReverb));
	memcpy(audioReverb,this, sizeof(VDAudioReverb));
	dataSize = sizeof(VDAudioReverb);
	return (VDBehavior*)audioReverb;
}

void VDAudioReverb::setMinDistance(float distance){

}

float VDAudioReverb::getMinDistance()const{
	return 0;
}

void VDAudioReverb::setMaxDistance(float distance){
	float min;

}

float VDAudioReverb::getMaxDistance()const{
	return 0;
}


void VDAudioReverb::setPropertiePreset(const void* Properties){

}


void VDAudioReverb::setProperties(VDAudioReverb::Properties prop){

}

void VDAudioReverb::setReverb(float reverb){

}

int VDAudioReverb::getReverb()const{

}

void VDAudioReverb::setReverbDelay(float reverbdelay){

}

float VDAudioReverb::getReverbDelay()const{

}

void VDAudioReverb::setReflections(float Reflections){

}

float VDAudioReverb::getReflections()const{

}

