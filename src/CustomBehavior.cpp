#include <Core/VDBehavior.h>
#include <Core/VDComponent.h>
#include <Core/VDCustomBehavior.h>
#include <malloc.h>
#include <Physic/VDCharacterControllerHit.h>
#include <Scene/VDGameObject.h>
#include <VDDef.h>
#include <cstring>


VDCustomBehavior::VDCustomBehavior(void) : VDBehavior(){
}
VDCustomBehavior::VDCustomBehavior(const VDCustomBehavior& brood){

}

void VDCustomBehavior::update(void){return;}
void VDCustomBehavior::fixedUpdate(void){return;}
void VDCustomBehavior::lateUpdate(void){return;}
void VDCustomBehavior::onAwake(void){return;}
void VDCustomBehavior::onGUI(void){return;}

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

void VDCustomBehavior::onBecameInvisible(void){

}

void VDCustomBehavior::onBecameVisible(void){

}

void VDCustomBehavior::onPreCulled(void){

}


void VDCustomBehavior::initializeComponent(void){
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
