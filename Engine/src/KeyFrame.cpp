#include <Animation/VDKeyFrame.h>

VDKeyFrame::VDKeyFrame(void){
	this->tangentIn = 0;
	this->tangentOut = 0;
	this->value = 0;
	this->time = 0;
}

VDKeyFrame::VDKeyFrame(const VDKeyFrame& key){
	this->tangentIn = key.tangentIn;
	this->tangentOut = key.tangentOut;
	this->value = key.value;
	this->time = key.time;
}

VDKeyFrame::VDKeyFrame(float value, float time){
	this->tangentIn = 0.0f;
	this->tangentOut = 0.0f;
	this->value = value;
	this->time = time;
}

VDKeyFrame::VDKeyFrame(float value, float time, float tangentIn, float tangentOut){
	this->tangentIn = tangentIn;
	this->tangentOut = tangentOut;
	this->value = value;
	this->time = time;
}
