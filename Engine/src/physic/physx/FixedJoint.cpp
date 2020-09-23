#define USE_PHYSX
#include"VDTransform.h"
#include"VDFixedJoint.h"
#include"VDRigidBody.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;

VDFixedJoint::VDFixedJoint(void) : VDJoint(){
}

VDFixedJoint::VDFixedJoint(const VDFixedJoint& joint){
}

VDFixedJoint::VDFixedJoint(VDRigidBody* rigidbody){
	this->attachJoint(rigidbody);
}

void VDFixedJoint::instanceInitilize(void){

}

void VDFixedJoint::initializeComponent(void){

}

void VDFixedJoint::onEnable(void){

}

void VDFixedJoint::onDisable(void){

}

void VDFixedJoint::onDestroy(void){
	VDJoint::onDestroy();
}

VDBehavior* VDFixedJoint::copyComponent(unsigned int& dataSize){
	BEHAVIOR_DEFUALT_COPYCOMPONENT
}

void VDFixedJoint::attachJoint(VDRigidBody* rigidbody){
	if(!rigidbody)
		return;

	this->joint = PxFixedJointCreate(*VDPhysic::getPhysicHandle(),
		GetRigidActor(),
		VDPhysic::createPxTransformInstance(rigidbody->transform()),
		rigidbody->GetRigidActor(),
		VDPhysic::createPxTransformInstance(this->transform()));
}
