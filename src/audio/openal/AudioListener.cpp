#include"VDAudioListener.h"
#include"VDEngine.h"
#include<AL/al.h>


VDAudioListener::VDAudioListener(void) : VDBehavior(){

}

VDAudioListener::VDAudioListener(const VDAudioListener& listener) : VDBehavior(){

}

void VDAudioListener::instanceInitilize(void){

}

void VDAudioListener::onEnable(void){
	VDScene::getScene()->gListener = this;
}

void VDAudioListener::onDisable(void){
	VDScene::getScene()->gListener = NULL;
}

void VDAudioListener::onDestroy(void){
	VDScene::getScene()->gListener = NULL;
}

void VDAudioListener::initializeComponent(void){
	if(!VDAudioListener::getAudioListener())
		VDScene::getScene()->gListener = this;
	else
		VDDebug::errorLog("Can't have more than one VDAudioListener!");
}

VDBehavior* VDAudioListener::copyComponent(unsigned int& dataSize){
	VDAudioListener* audioListener = (VDAudioListener*)malloc(sizeof(VDAudioListener));
	memcpy(audioListener,this, sizeof(VDAudioListener));
	dataSize = sizeof(VDAudioListener);
	return (VDBehavior*)audioListener;
}


void VDAudioListener::updateAudioListener(VDDoubleBufferedAllocator* allocator){
	if(VDScene::getScene()->gListener == NULL)
		return;

	VDAudioSource::AudioMechanicUpdate(allocator);
	VDAudioListener* gListener = VDScene::getScene()->gListener;

	VDVector3 prePos;
	VDVector3 pos = gListener->transform()->getPosition();
	alGetListener3f(AL_POSITION, &prePos[0],&prePos[1],&prePos[2]);
	VDVector3 vel = prePos - gListener->transform()->getPosition();
	alListener3f(AL_POSITION, pos.x(), pos.y(), pos.z());
	alListener3f(AL_VELOCITY, vel.x(), vel.y(), vel.z());
	alListenerfv(AL_DIRECTION, &gListener->transform()->getRotation().forward()[0]);

}

VDAudioListener* VDAudioListener::getAudioListener(void){
	return VDScene::getScene()->gListener;
}
