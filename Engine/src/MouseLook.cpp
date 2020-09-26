#include <Core/VDInput.h>
#include <Core/VDTime.h>
#include <DataStructure/VDPoint.h>
#include <Misc/VDMouseLook.h>
#include <Scene/VDTransform.h>
#include <VDSimpleType.h>
#include<Core/Math.h>


VDMouseLook::VDMouseLook(void) : VDCustomBehavior(){
	this->state = eFreeRotation;
}

VDMouseLook::VDMouseLook(const VDMouseLook& look){
	*this = look;
}

VDMouseLook::~VDMouseLook(void){

}

void VDMouseLook::onAwake(void){
	this->sensitivityX = 30.5f;
	this->sensitivityY = 30.5f;

	this->minimumX = -60.0f;
	this->maximumX = 60.0f;

	this->minimumY = 0.0f;
	this->maximumY = 0.0f;

	this->rotationY = 0.0f;
	this->rotationX = 0.0;
	this->setRotationMode(eXandY);

}

void VDMouseLook::lateUpdate(void){
	float delta = VDTime::deltaTime();
	this->mousedelta = this->mousepos - VDInput::mousePosition();

	/**/
	switch((unsigned int)this->getRotationMode()){
	case eFreeRotation:{	



		}break;
	case eX:{
		this->rotationY += this->sensitivityX  * mousedelta.y() * delta;
		this->rotationY = fragcore::Math::clamp(this->rotationY,this->minimumX, this->maximumX);
		VDQuaternion q = VDQuaternion(fragcore::Math::deg2Rad(this->rotationY), this->transform()->getRotation().getYaw(), 0.0f);
		this->transform()->setLocalRotation(q);
		}break;
	case eY:{
			this->transform()->rotate(VDVector3(0.0f, mousedelta.x() * this->sensitivityY * delta , 0.0f));
		}break;
	case eXandY:{
		this->rotationX += (float)(mousedelta.x()) * this->sensitivityY * delta;
		this->rotationY += (float)(mousedelta.y()) * this->sensitivityY * delta;
		this->rotationY = fragcore::Math::clamp(this->rotationY, this->minimumX, this->maximumX);

		VDQuaternion p = VDQuaternion::createQuaternionOfAxis(
			fragcore::Math::deg2Rad<float>(0.0f),
			fragcore::Math::deg2Rad<float>(this->rotationX),
			fragcore::Math::deg2Rad<float>(0.0f));
		p *= VDQuaternion::createQuaternionOfAxis(
			fragcore::Math::deg2Rad<float>(this->rotationY),
			fragcore::Math::deg2Rad<float>(0.0f),
			fragcore::Math::deg2Rad<float>(0.0f));

		this->transform()->setRotation( (p).normalize());
		}break;
	default:
		break;
	}

	this->mousepos = VDInput::mousePosition();
}



void VDMouseLook::setRotationMode(rotationState state){
	this->state = state;
}

VDMouseLook::rotationState VDMouseLook::getRotationMode(void)const{
	return this->state;
}
