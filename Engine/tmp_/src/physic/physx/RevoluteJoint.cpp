#define USE_PHYSX
#include"VDRevoluteJoint.h"
#include"VDRigidBody.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;

VDRevoluteJoint::VDRevoluteJoint(){
	this->joint = nullptr;
}

VDRevoluteJoint::VDRevoluteJoint(VDRigidBody* rigidbody){

}

void VDRevoluteJoint::instanceInitilize(){

}

void VDRevoluteJoint::onEnable(){
	VDJoint::onEnable();
}

void VDRevoluteJoint::onDisable(){
	VDJoint::onDisable();
}

void VDRevoluteJoint::initializeComponent(){

}

void VDRevoluteJoint::onDestroy(){

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
