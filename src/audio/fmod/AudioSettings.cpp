#include<fmod/fmod.hpp>
#include"VDAudioSetting.h"
#include"VDEngine.h"

bool VDAudioSetting::isEnable(void){
	if(engine.audioContext != NULL){
		return true;
	}
	return false;
}

bool VDAudioSetting::isDisable(void){
	return engine.audioContext == NULL;
}

void VDAudioSetting::setMasterVolume(float volume){
	if(VDAudioSetting::isDisable())
		return;

	FMOD::SoundGroup* group;
	VDCASTP(FMOD::System*,engine.audioContext)->getMasterSoundGroup(&group);
	group->setVolume(volume);
}

float VDAudioSetting::getMasterVolume(void){
	if(VDAudioSetting::isDisable())
		return 0;

	float volume;
	FMOD::SoundGroup* group;

	/**/
	VDCASTP(FMOD::System*,engine.audioContext)->getMasterSoundGroup(&group);
	group->getVolume(&volume);
	return volume;
}

void VDAudioSetting::setSpeakMode(SpeakerMode speakerMode){
	if(VDAudioSetting::isDisable())
		return;

	VDCASTP(FMOD::System*,engine.audioContext)->setSpeakerMode((FMOD_SPEAKERMODE)speakerMode);
}

VDAudioSetting::SpeakerMode VDAudioSetting::getSpeakerMode(void){
	if(VDAudioSetting::isDisable())
		return eUnknown;

	FMOD_SPEAKERMODE speakdermode;
	VDCASTP(FMOD::System*,engine.audioContext)->getSpeakerMode(&speakdermode);
	return (SpeakerMode)speakdermode;
}

int VDAudioSetting::getSampleRate(void){
	if(VDAudioSetting::isDisable())
		return 0;

	int sampleRate;
	VDCASTP(FMOD::System*,engine.audioContext)->getSoftwareFormat(&sampleRate, NULL, NULL, NULL, NULL, NULL);
	return sampleRate;
}

void VDAudioSetting::setSampleRate(int samplerate){
	if(VDAudioSetting::isDisable())
		return;

	int sampleRate;
	FMOD_SOUND_FORMAT format;
	int numoutputchannels;
	int maxinputchannels;
	FMOD_DSP_RESAMPLER resamplemethod;

	if(VDCASTP(FMOD::System*,engine.audioContext)->getSoftwareFormat(&sampleRate,&format,&numoutputchannels,&maxinputchannels,&resamplemethod,NULL) == FMOD_OK){
		if(VDCASTP(FMOD::System*,engine.audioContext)->setSoftwareFormat(samplerate,format,numoutputchannels,maxinputchannels,resamplemethod) != FMOD_OK){
			/*	Reset sample rate*/
			VDCASTP(FMOD::System*,engine.audioContext)->setSoftwareFormat(sampleRate,format,numoutputchannels,maxinputchannels,resamplemethod);
		}
	}
}


VDAudioSetting::Format VDAudioSetting::getFormat(void){
	if(VDAudioSetting::isDisable())
		return 0;

	int sampleRate;
	FMOD_SOUND_FORMAT format;
	int numoutputchannels;
	int maxinputchannels;
	FMOD_DSP_RESAMPLER resamplemethod;


	if(VDCASTP(FMOD::System*,engine.audioContext)->getSoftwareFormat(&sampleRate,&format,&numoutputchannels,&maxinputchannels,&resamplemethod,NULL) == FMOD_OK){
		return (VDAudioSetting::Format)format;
	}
	return eNone;
}

void VDAudioSetting::setFormat(Format format){
	if(VDAudioSetting::isDisable())
		return;
}

int VDAudioSetting::getVolumeSpeed(void){
	if(VDAudioSetting::isDisable())
		return 0;
	return 1;
}

void VDAudioSetting::setVolumeSpeed(int volumeSpeed){
	if(VDAudioSetting::isDisable())
		return;
}
