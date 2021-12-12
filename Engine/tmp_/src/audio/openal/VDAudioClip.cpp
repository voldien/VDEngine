#include"VDAudioClip.h"
#include"VDEngine.h"
#include<AL/al.h>

using namespace std;

map<const char*, VDAudioClip*> audioClipCollection;

VDAudioClip::VDAudioClip() : VDAssetObject() {
	this->soundTrack = nullptr;
}

VDAudioClip::VDAudioClip(const VDAudioClip& clip){
	*this = clip;
}

VDAudioClip::VDAudioClip(const char* path, Format format) : VDAssetObject() {
	this->soundTrack = nullptr;
	this->load(path, format);
}

VDAudioClip::~VDAudioClip(){
	this->release();
}

void VDAudioClip::release(){
	if(!this->soundTrack){

	}

	this->soundTrack = nullptr;
	this->setName(nullptr);
}

bool VDAudioClip::is3D(){
	//FMOD_MODE audioMode;
	//this->soundTrack->getMode(&audioMode);
	//return (audioMode & FMOD_3D) != 0 ? SDL_TRUE : SDL_FALSE;
}

bool VDAudioClip::is2D(){
	//FMOD_MODE audioMode;
	//this->soundTrack->getMode(&audioMode);
	//return (audioMode & FMOD_2D);
}


int VDAudioClip::load(const char* path, unsigned int dataBitFlag){

	this->setName(path);

	//return results == FMOD_OK;
}

void VDAudioClip::write(void* buffer, int rSize){
	int read;
}

void* VDAudioClip::read(int rSize){
	void* alloc = malloc(rSize);

	//soundTrack->readData(alloc, rSize, nullptr);
	return alloc;
}

void VDAudioClip::assigneClip(VDAudioClip* audioClip){
	audioClipCollection.insert(std::pair<const char*,VDAudioClip*>(audioClip->getName(), audioClip));
}
