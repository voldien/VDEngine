#define USE_PHYSX
#include"VDRigidBody.h"
#include"VDSpringJoint.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;


VDSpringJoint::VDSpringJoint(){
	this->joint = nullptr;
}

VDSpringJoint::VDSpringJoint(VDRigidBody* rigidBody){

}

void VDSpringJoint::instanceInitilize(){

}

void VDSpringJoint::initializeComponent(){
	VDJoint::initializeComponent();
	VDPhysicActor::initVDPhysicObject(true, true);
}

void VDSpringJoint::onEnable(){

}

void VDSpringJoint::onDisable(){

}

void VDSpringJoint::onDestroy(){
	VDJoint::onDestroy();
}

VDBehavior* VDSpringJoint::copyComponent(unsigned int& dataSize){
	VDSpringJoint* rigid = (VDSpringJoint*)malloc(sizeof(VDSpringJoint));
	memcpy(rigid,this, sizeof(VDSpringJoint));
	dataSize = sizeof(VDSpringJoint);
	return (VDBehavior*)rigid;
}

void VDSpringJoint::attachJoint(VDRigidBody* rigidbody){
	this->joint = PxDistanceJointCreate(*VDPhysic::getPhysicHandle(),
		this->GetDynamicActor(),VDPhysic::createPxTransformInstance(this->transform()),
		rigidbody->GetDynamicActor(),
		VDPhysic::createPxTransformInstance(rigidbody->transform()));

	VDPhysic::addActor(this->actor);
	pxGetDistanceJoint()->setDistanceJointFlag(PxDistanceJointFlag::eMAX_DISTANCE_ENABLED,true);
	pxGetDistanceJoint()->setDistanceJointFlag(PxDistanceJointFlag::eMIN_DISTANCE_ENABLED,true);
	pxGetDistanceJoint()->setDistanceJointFlag(PxDistanceJointFlag::eSPRING_ENABLED,true);
	this->joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION,true);
	this->joint->setConstraintFlag(PxConstraintFlag::eREPORTING,true);
	pxGetDistanceJoint()->setStiffness(0.5f);

	pxGetDistanceJoint()->setMaxDistance(0.5f);
	pxGetDistanceJoint()->setDamping(0.2f);

	this->setBreakForce(FLT_MAX, FLT_MAX);
}
