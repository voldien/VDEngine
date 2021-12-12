#include <Animation/VDAnimation.h>
#include <Animation/VDAnimationClip.h>
#include <Animation/VDCurve.h>
#include <Animation/VDKeyFrame.h>
#include <bits/move.h>
#include <Core/VDObject.h>
#include <Core/VDTime.h>
#include <DataStructure/VDIterator.h>
#include <malloc.h>
#include <Scene/VDScene.h>
#include <cstring>
#include <exception>

using namespace std;
typedef std::vector<VDCurve> VDCurveList;

VDAnimation::VDAnimation() : VDBehavior(){
	this->time = 0;
	this->animationState = VDAnimation::None;
}

VDAnimation::VDAnimation(const VDAnimation& animation) : VDBehavior(){
	*this = animation;
}

void VDAnimation::instanceInitilize(){
	unsigned int x;
	for(x = 0; x < this->getNumClips(); x++){
		this->getClip(x)->findNodeDataPointer(this->transform());
	}
}

void VDAnimation::onEnable(){

}

void VDAnimation::onDisable(){

}

void VDAnimation::initializeComponent(){
	VDScene::getScene()->AnimationCollection.push_back(this);
}

void VDAnimation::onDestroy(){
	// find the references
	for(int x = 0; x < this->getNumClips(); x++){
		this->getClip(x)->deincrement();
	}
}

VDBehavior* VDAnimation::copyComponent(unsigned int& dataSize){
	VDAnimation* animation = (VDAnimation*)malloc(sizeof(VDAnimation));
	memcpy(animation, this, sizeof(VDAnimation));
	dataSize = sizeof(VDAnimation);
	return (VDBehavior*)animation;
}

bool VDAnimation::isPlaying()const{
	return (VDAnimation::getState() & VDAnimation::IsPlaying);
}

void VDAnimation::play(int index){
	this->time = 0.0f;
	this->animationState |= (int)VDAnimation::IsPlaying;
	std::swap(*this->clips[0], *this->clips[index]);
}

void VDAnimation::play(const char* animationClip){
	for(int i = 0; i < getNumClips(); i++){
		if(strcmp(this->getClip(i)->getName(), animationClip) == 0){
			this->play(i);
			break;
		}
	}
}

void VDAnimation::stop(){
	/*	Reset timer.	*/
	this->time = 0.0f;
	this->animationState = (~VDAnimation::IsPlaying & (int)this->animationState);
}

void VDAnimation::addClip(VDAnimationClip* animationClip){

	if(animationClip == nullptr){
		throw new exception();
	}

	animationClip->findNodeDataPointer(this->transform());
	this->clips.push_back(animationClip);
}

VDAnimationClip* VDAnimation::getClip(int index)const{
	return this->clips[index];
}

unsigned int VDAnimation::getNumClips()const{
	return this->clips.size();
}

VDAnimationClip* VDAnimation::getCurrentPlayingClip(){
	return this->getClip(0);
}

void VDAnimation::internalUpdate(){


	if(this->isPlaying()){
		this->time += VDTime::deltaTimed();

		VDCurveList::iterator end = this->getClip(0)->getCurves()->end();
		VDCurveList::iterator x = this->getClip(0)->getCurves()->begin();
		for(; x != end; x++){
			for(unsigned int y = 0; y < x->getLength(); y++){
				if(this->time > x->getKey(y).getTime() && this->time < x->getKey(y + 1).getTime()){
					if(!x->getPointer()){
						break;
					}

					float curveValue = x->linearInterpolation(y, this->time);
					x->setCurveValue<float>(curveValue);
					break;

				}
			}
			if(this->getClip(0)->isLoop()){
				this->time = 0.0f;
			}
			if(this->getClip(0)->isPingPong()){
				this->time = 0.0f;
			}

		}/*	curves	*/

	}/*	playing animation	*/
}

void VDAnimation::internalCurveUpdate(unsigned int index){

}

void VDAnimation::setAnimationOnStep(float time){
	VDCurve* lside;
	VDCurve* rside;
	VDAnimationClip* current = this->getCurrentPlayingClip();
	int index;

	for(int x = 0; x < current->getNumCurves(); x++){
		current->getCurve(x).linearInterpolation(0, time);
	}

}

