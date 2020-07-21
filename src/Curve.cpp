#include <Animation/VDCurve.h>
#include <Animation/VDKeyFrame.h>
#include <stdlib.h>
#include <VDSimpleType.h>
#include <cassert>
#include <cmath>
#include <cstring>


VDCurve::VDCurve(void) : VDAssetObject(){
	this->length = 0;
	this->cFlag = 0;
	this->keysFrames = NULL;
	this->pointer = NULL;
	this->set = NULL;
}

VDCurve::VDCurve(const VDCurve& curve) {
	*this = curve;
}

VDCurve::VDCurve(int keyCount) : VDAssetObject(){
	this->length = keyCount;
	this->cFlag = 0;
	this->keysFrames = (VDKeyFrame*)malloc(sizeof(*keysFrames) * keyCount);
	memset(this->keysFrames, 0, sizeof(*keysFrames) * keyCount);
	this->pointer = NULL;
	this->set = NULL;
}

void VDCurve::release(void){
	free(this->keysFrames);
	this->keysFrames = NULL;
	this->length = 0;
}


void VDCurve::addKey(const VDKeyFrame& keyFrame, int index){
	this->keysFrames = (VDKeyFrame*)realloc(this->keysFrames, ++this->length);

	/*	perform relocating of index.	*/
	memcpy(&this->keysFrames[index], &keyFrame, sizeof(VDKeyFrame));
}

void VDCurve::removeKey(unsigned int Index){
	if(this->length < Index){
		return;
	}
	VDKeyFrame* tempalloc = (VDKeyFrame*)calloc(this->length - 1, sizeof(VDKeyFrame));
	memcpy(this->keysFrames ,tempalloc, sizeof(VDKeyFrame) * (Index - 1));

	memcpy(this->keysFrames, &tempalloc[Index + 1], sizeof(VDKeyFrame) * (Index + 1));
}

float VDCurve::linearInterpolation(unsigned int index, float time){
	if(this->length == 1){
		return this->keysFrames[0].getValue();
	}

	if(index <= this->length - 1){

		float deltaTime = this->keysFrames[index + 1].getTime() - this->keysFrames[index].getTime();
		float finalFactor = (time - this->keysFrames[index].getTime()) / deltaTime;
		float value;// = lerpf((float)this->keysFrame[index].value,(float)this->keysFrame[index + 1].value,(float)finalFactor);
		return value;
		assert(finalFactor < 1.0f);
		return ( 1.0f  - finalFactor ) *this->keysFrames[index].getValue() + (finalFactor *  this->keysFrames[index + 1].getValue());
	}
	else{
		return this->keysFrames[index - 1].getValue() + (this->keysFrames[index].getValue() - this->keysFrames[index - 1].getValue()) *
				((this->keysFrames[index].getTime() - this->keysFrames[index - 1].getTime()) / abs(time -  this->keysFrames[index].getTime()));
	}
}

float VDCurve::tangentInterpolation(unsigned int index, float time){
	if(this->length == 1){
		return this->keysFrames[0].getTime();
	}
}

void VDCurve::setMethodSetCallBack(VDSetClassMethod method){
	this->set = method;
}

VDSetClassMethod VDCurve::getMethodSetCallBack(void)const{
	return this->set;
}

