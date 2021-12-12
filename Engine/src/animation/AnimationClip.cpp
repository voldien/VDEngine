#include <Animation/VDAnimationClip.h>
#include <Animation/VDCurve.h>
#include <Asset/VDSmartReference.h>
#include <Core/VDObject.h>
#include <DataStructure/VDIterator.h>
#include <Scene/VDTransform.h>
#include <VDDef.h>
#include <VDSimpleType.h>

using namespace std;

VDAnimationClip::VDAnimationClip() : VDAssetObject(){
	this->duration = 0.0f;
	this->frameTicks = 0.0f;
	this->animationState = (AnimationClipState)0;
}

VDAnimationClip::VDAnimationClip(float duration, float frameTicks){
	this->duration = duration;
	this->frameTicks = frameTicks;
	this->animationState = (AnimationClipState)0;
}

VDAnimationClip::VDAnimationClip(const VDAnimationClip& animationClip){
	*this = animationClip;
}

VDAnimationClip::~VDAnimationClip(){
	this->reference.deincreemnt();
}

void VDAnimationClip::release(){

}

void VDAnimationClip::addCurve(const VDCurve& curve){
	this->curves.push_back(curve);
}

void VDAnimationClip::findNodeDataPointer(VDTransform* transform){

	/*	*/
	for(VDCurveList::Iterator x = this->curves.begin(); x != this->curves.end(); x++){
		VDTransform* findNode = transform->findChild(x->getName());
		if(!findNode){
			continue;
		}

		switch(x->getCurveFlag()){
		case VDCurve::eTransformPosX:
			x->setMethodSetCallBack((VDSetClassMethod)&VDTransform::AnimationSetPositionX);
			break;
		case VDCurve::eTransformPosY:
			x->setMethodSetCallBack((VDSetClassMethod)&VDTransform::AnimationSetPositionY);
			break;
		case VDCurve::eTransformPosZ:
			x->setMethodSetCallBack((VDSetClassMethod)&VDTransform::AnimationSetPositionZ);
			break;
		case VDCurve::eTransformScaX:
			x->setMethodSetCallBack((VDSetClassMethod)&VDTransform::AnimationSetPositionZ);
			break;
		case VDCurve::eTransformScaY:
			x->setMethodSetCallBack((VDSetClassMethod)&VDTransform::AnimationSetPositionZ);
			break;
		case VDCurve::eTransformScaZ:
			x->setMethodSetCallBack((VDSetClassMethod)&VDTransform::AnimationSetPositionZ);
			break;
		case VDCurve::eTransformRotX:
		case VDCurve::eTransformRotY:
		case VDCurve::eTransformRotZ:
		case VDCurve::eTransformQuadX:
		case VDCurve::eTransformQuadY:
		case VDCurve::eTransformQuadZ:
		case VDCurve::eTransformQuadW:
			x->setPointer(  VDCASTP(void*, findNode) );
			break;
		default:
			break;
		}
	}/**/
}
