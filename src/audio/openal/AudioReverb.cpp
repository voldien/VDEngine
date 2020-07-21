#include"VDAudioReverb.h"
#include"VDEngine.h"

#define DEFAULT_MIN_RANGE 10
#define DEFAULT_MAX_RANGE 100

VDAudioReverb::VDAudioReverb(void) : VDBehavior(){
	this->reverb = NULL;
}

VDAudioReverb::VDAudioReverb(const VDAudioReverb& audio) : VDBehavior(){
	this->reverb = NULL;
}

void VDAudioReverb::instanceInitilize(void){

}

void VDAudioReverb::onEnable(void){
	if(this->reverb){
		//this->reverb->setActive(true);
	}
}

void VDAudioReverb::onDisable(void){
	if(this->reverb){
		//this->reverb->setActive(false);
	}
}

void VDAudioReverb::onDestroy(void){
	if(this->reverb){
		//this->reverb->release();
	}
}

void VDAudioReverb::initializeComponent(void){

}

VDBehavior* VDAudioReverb::copyComponent(unsigned int& dataSize){
	VDAudioReverb* audioReverb = (VDAudioReverb*)malloc(sizeof(VDAudioReverb));
	memcpy(audioReverb,this, sizeof(VDAudioReverb));
	dataSize = sizeof(VDAudioReverb);
	return (VDBehavior*)audioReverb;
}

void VDAudioReverb::setMinDistance(float distance){

}

float VDAudioReverb::getMinDistance(void)const{
	return 0;
}

void VDAudioReverb::setMaxDistance(float distance){
	float min;

}

float VDAudioReverb::getMaxDistance(void)const{
	return 0;
}


void VDAudioReverb::setPropertiePreset(const void* Properties){

}


void VDAudioReverb::setProperties(VDAudioReverb::Properties prop){

}

void VDAudioReverb::setReverb(float reverb){

}

int VDAudioReverb::getReverb(void)const{

}

void VDAudioReverb::setReverbDelay(float reverbdelay){

}

float VDAudioReverb::getReverbDelay(void)const{

}

void VDAudioReverb::setReflections(float Reflections){

}

float VDAudioReverb::getReflections(void)const{

}

