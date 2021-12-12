#include"VDTransform.h"
#include"VDEngine.h"
#include<fmod/fmod.hpp>

#include"VDAudioSource.h"
using namespace std;

vector<VDAudioSource*> audioSources;

VDAudioSource::VDAudioSource() : VDBehavior(){
	this->Clip = nullptr;
	this->channel = nullptr;
}

void VDAudioSource::instanceInitilize(){

}

void VDAudioSource::onEnable(){
	this->channel->setPaused(true);
}

void VDAudioSource::onDisable(){
	this->channel->setPaused(true);
}

void VDAudioSource::onDestroy(){
	if(this->channel)
		this->channel->stop();
}

void VDAudioSource::initializeComponent(){
	this->channel = nullptr;
	this->Clip = nullptr;
	audioSources.push_back(this);
}

VDBehavior* VDAudioSource::copyComponent(unsigned int& dataSize){
	VDAudioSource* audiosource = (VDAudioSource*)malloc(sizeof(VDAudioSource));
	memcpy(audiosource,this, sizeof(VDAudioSource));
	dataSize = sizeof(VDAudioSource);
	return VDCASTP(VDBehavior*,audiosource);
}

void VDAudioSource::play(){
	FMOD_RESULT results;
	if(!this->Clip)
		return;

	results = ((FMOD::System*)engine.audioContext)->playSound(FMOD_CHANNEL_FREE, this->Clip->getSoundTrack(), false, &this->channel);

	/*	TODO do it really need to do this part. I don't think so	*/
	if(results == FMOD_OK){
		setMaxDistance(5.0);
		setMinDistance(1.0);
	}else{
		VDDebug::warningLog("No audio clip\n");
	}
}

void VDAudioSource::pause(){
	this->channel->setPaused(true);
}

void VDAudioSource::stop(){
	this->channel->stop();
}

void VDAudioSource::mute(bool mute){
	if(!this->channel)
		return;

	this->channel->setMute(mute);
}

void VDAudioSource::loop(int loop){
	if(this->channel)
		return;

	this->channel->setMode(FMOD_LOOP_NORMAL);
}

bool VDAudioSource::isPlaying()const{
	bool playing;
	this->channel->isPlaying(&playing);
	return playing;
}

float VDAudioSource::getFrequency()const{
	float pvalue;
	this->channel->getFrequency(&pvalue);
	return pvalue;
}

void VDAudioSource::setFrequency(float frequency){
	float pvalue;
	this->channel->setFrequency(frequency);
}

void VDAudioSource::setVolume(float volume){
	this->channel->setVolume(volume);
}

float VDAudioSource::getVolume()const{
	float volume;
	this->channel->getVolume(&volume);
	return volume;
}
void VDAudioSource::setPriority(int Priority){
	this->channel->setPriority(Priority);
}

int VDAudioSource::getPriority()const{
	int priority;
	this->channel->getPriority(&priority);
	return priority;
}
	
void VDAudioSource::setMaxDistance(float maxDistance){
	this->channel->set3DMinMaxDistance(getMaxDistance(),maxDistance);
}

float VDAudioSource::getMaxDistance()const{
	float max;
	this->channel->get3DMinMaxDistance(nullptr,&max);
	return max;
}

void VDAudioSource::setMinDistance(float Mindistance){
	this->channel->set3DMinMaxDistance(Mindistance,getMaxDistance());
}

float VDAudioSource::getMinDistance()const{
	float min;
	this->channel->get3DMinMaxDistance(&min,nullptr);
	return min;
}



static void private_update(VDTaskSchedule::VDTaskPackage* package){

}

void VDAudioSource::AudioMechanicUpdate(VDDoubleBufferedAllocator* allocator){
	unsigned int x;
	int results;

	/*	TODO add to task schedule.	*/
	VDTaskSchedule::VDTaskPackage pack = {0};
	unsigned int num = audioSources.size();
	const unsigned int packageSize = 32;
	vector<VDAudioSource*>::Iterator begin = audioSources.begin();
	vector<VDAudioSource*>::Iterator end = audioSources.end();
	for(int x  = 0; x < num; x += packageSize){
		pack.begin = allocator->fetch(sizeof(vector<VDAudioSource*>::Iterator));
		pack.end = allocator->fetch(sizeof(vector<VDAudioSource*>::Iterator));
		//pack.begin = VDCASTP(void*, begin + x);
		//pack.end  = VDCAST(void*, begin + x + packageSize);
		pack.size = packageSize;
		pack.offset = x;
		pack.callback = private_update;
		VDEngine::getTaskSchedule().submitTask(&pack);
	}


	for(x = 0; x < audioSources.size(); x++){
		if(!audioSources[x]->channel)
			continue;

		if((audioSources[x])->Clip->is3D()){
			VDVector3 prePos;
			VDVector3 vel;
			audioSources[x]->channel->get3DAttributes((FMOD_VECTOR*)&prePos, nullptr);
			vel = prePos - audioSources[x]->transform()->postion;
			results = audioSources[x]->channel->set3DAttributes(
				(FMOD_VECTOR*)&audioSources[x]->transform()->postion,
				(FMOD_VECTOR*)&vel);

		}
	}/**/
}
