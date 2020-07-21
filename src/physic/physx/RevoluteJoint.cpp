#define USE_PHYSX
#include"VDRevoluteJoint.h"
#include"VDRigidBody.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;

VDRevoluteJoint::VDRevoluteJoint(void){
	this->joint = NULL;
}

VDRevoluteJoint::VDRevoluteJoint(VDRigidBody* rigidbody){

}

void VDRevoluteJoint::instanceInitilize(void){

}

void VDRevoluteJoint::onEnable(void){
	VDJoint::onEnable();
}

void VDRevoluteJoint::onDisable(void){
	VDJoint::onDisable();
}

void VDRevoluteJoint::initializeComponent(void){

}

void VDRevoluteJoint::onDestroy(void){

}

VDBehavior* VDRevoluteJoint::copyComponent(unsigned int& dataSize){
	BEHAVIOR_DEFUALT_COPYCOMPONENT
}

void VDRevoluteJoint::attachJoint(VDRigidBody* object){
	this->joint = PxRevoluteJointCreate(*VDPhysic::getPhysicHandle(),
		object->actor,
		VDPhysic::createPxTransformInstance(object->transform()),
		this->actor,
		VDPhysic::createPxTransformInstance(this->transform()));

}
