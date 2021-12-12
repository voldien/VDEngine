#define USE_PHYSX
#include"VDJoint.h"
#include"VDRigidBody.h"
#include<physx/PxPhysicsAPI.h>

using namespace std;
using namespace physx;


VDJoint::VDJoint() : VDPhysicActor(){

}

void VDJoint::instanceInitilize(){

}

void VDJoint::onEnable(){
	//this->joint->setConstraintFlag(PxConstraintFlag::ePROJECTION
}

void VDJoint::onDisable(){

}

void VDJoint::initializeComponent(){
	if(!this->existComponentType<VDRigidBody>()){
		this->gameObject()->addComponet(new VDRigidBody());
	}
	this->joint = nullptr;
}

void VDJoint::onDestroy(){
	VDCAST(PxActor*,this->getActor())->release();
}

VDBehavior* VDJoint::copyComponent(unsigned int& dataSize){
	VDJoint* joint = (VDJoint*)malloc(sizeof(VDJoint));
	memcpy(joint,this, sizeof(VDJoint));
	dataSize = sizeof(VDJoint);
	return (VDBehavior*)joint;
}

void VDJoint::attachJoint(VDRigidBody* jointAttachment){
	if(jointAttachment != nullptr){
		if(!jointAttachment->actor)
			return;

		this->joint = PxRevoluteJointCreate(*VDPhysic::getPhysicHandle(),this->rigidBody()->actor, PxTransform(),jointAttachment->actor,PxTransform());
	}
}

void VDJoint::Break(){
	this->joint->setConstraintFlag(PxConstraintFlag::eBROKEN, true);
}

VDVector3 VDJoint::getRelativeAngularVelocity()const{
	return *VDCASTP(VDVector3*,&this->joint->getRelativeAngularVelocity());
}

VDVector3 VDJoint::getRelativeLinearVelocity()const{
	return *VDCASTP(VDVector3*,&this->joint->getRelativeLinearVelocity());
}

void VDJoint::setBreakForce(float force, float torque){
	this->joint->setBreakForce(force, torque);
}

void VDJoint::getBreakForce(float* force, float* torque){
	this->joint->getBreakForce(*force, *torque);
}

VDRigidBody* VDJoint::getAttachedRigidBody()const{
	PxRigidActor* a,*b;
	this->joint->getActors(a,b);
	return VDCASTP(VDGameObject*,a->userData)->rigidBody();
}


VDFixedJoint* VDJoint::isFixedJoint(){
	return reinterpret_cast<VDFixedJoint*>(this);
}

VDSpringJoint* VDJoint::isSpringJoint(){
	return reinterpret_cast<VDSpringJoint*>(this);
}

VDRevoluteJoint* VDJoint::isRevoluteJoint(){
	return reinterpret_cast<VDRevoluteJoint*>(this);
}
