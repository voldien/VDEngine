#include"VDAudioSetting.h"
#include"VDEngine.h"
#include<AL/al.h>

bool VDAudioSetting::isEnable(){
	if(engine.audioContext != nullptr){
		return true;
	}
	return false;
}

bool VDAudioSetting::isDisable(){
	return engine.audioContext == nullptr;
}

void VDAudioSetting::setMasterVolume(float volume){
	if(VDAudioSetting::isDisable())
		return;

	//alListenerf(AL_)
}

float VDAudioSetting::getMasterVolume(){
	if(VDAudioSetting::isDisable())
		return 0;

	float volume;

	return volume;
}

void VDAudioSetting::setSpeakMode(SpeakerMode speakerMode){
	if(VDAudioSetting::isDisable()){
		return;
	}

}

VDAudioSetting::SpeakerMode VDAudioSetting::getSpeakerMode(){
	if(VDAudioSetting::isDisable()){
		return eUnknown;
	}

	return (SpeakerMode)0;
}

int VDAudioSetting::getSampleRate(){
	if(VDAudioSetting::isDisable()){
		return 0;
	}

	int sampleRate;

	return sampleRate;
}

void VDAudioSetting::setSampleRate(int samplerate){
	if(VDAudioSetting::isDisable()){
		return;
	}

	int sampleRate;
	int numoutputchannels;
	int maxinputchannels;

}


VDAudioSetting::Format VDAudioSetting::getFormat(){
	if(VDAudioSetting::isDisable()){
		return (VDAudioSetting::Format)0;
	}

	int sampleRate;
	int numoutputchannels;
	int maxinputchannels;

	return None;
}

void VDAudioSetting::setFormat(Format format){
	if(VDAudioSetting::isDisable()){
		return;
	}
}

int VDAudioSetting::getVolumeSpeed(){
	if(VDAudioSetting::isDisable()){
		return 0;
	}

	return 1;
}

void VDAudioSetting::setVolumeSpeed(int volumeSpeed){
	if(VDAudioSetting::isDisable()){
		return;
	}
}
