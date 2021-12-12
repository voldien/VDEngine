#include <Core/VDBehavior.h>
#include <Core/VDComponent.h>
#include <Core/VDCustomBehavior.h>
#include <malloc.h>
#include <Physic/VDCharacterControllerHit.h>
#include <Scene/VDGameObject.h>
#include <VDDef.h>
#include <cstring>


VDCustomBehavior::VDCustomBehavior() : VDBehavior(){
}
VDCustomBehavior::VDCustomBehavior(const VDCustomBehavior& brood){

}

void VDCustomBehavior::update(){return;}
void VDCustomBehavior::fixedUpdate(){return;}
void VDCustomBehavior::lateUpdate(){return;}
void VDCustomBehavior::onAwake(){return;}
void VDCustomBehavior::onGUI(){return;}

void VDCustomBehavior::onCharacterController(const VDCharacterControllerHit& hit){

}
void VDCustomBehavior::onCollisionEnter(const VDCollision& collisionData){

}

void VDCustomBehavior::onCollisionExit(const VDCollision& collisionData){

}

void VDCustomBehavior::onCollisionStay(const VDCollision& collisionData){

}

void VDCustomBehavior::onTriggerEnter(VDCollider* collider){

}

void VDCustomBehavior::onTriggerExit(VDCollider * collider){

}

void VDCustomBehavior::onJointBreak(float breakForce){

}

void VDCustomBehavior::onBecameInvisible(){

}

void VDCustomBehavior::onBecameVisible(){

}

void VDCustomBehavior::onPreCulled(){

}


void VDCustomBehavior::initializeComponent(){
	VDBehavior::initializeComponent();
	this->menable |= VDCustomBehavior::CustomBehavior;
	this->gameObject()->active |= VDCustomBehavior::CustomBehavior;
	this->onAwake();
}

VDBehavior* VDCustomBehavior::copyComponent(unsigned int& dataSize){
	VDCustomBehavior* BehaviorData = (VDCustomBehavior*)malloc(sizeof(*this));
	memcpy(BehaviorData, this, sizeof(*this));
	dataSize = sizeof(*this);
	return VDCASTP(VDBehavior*,BehaviorData);
}
