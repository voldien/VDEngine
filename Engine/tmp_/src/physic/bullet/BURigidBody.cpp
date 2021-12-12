#include"VDRigidBody.h"


VDRigidBody::VDRigidBody(){

}
VDRigidBody::VDRigidBody(const VDRigidBody& rigidbody){

}

void VDRigidBody::instanceInitilize(){}
void VDRigidBody::onEnable(){}
void VDRigidBody::onDisable(){}
void VDRigidBody::initializeComponent(){}
void VDRigidBody::onDestroy(){}
VDBehavior* VDRigidBody::copyComponent(unsigned int& dataSize){
	return nullptr;
}


void VDRigidBody::addExplosionForce(float force, VDVector3& position,float Radius){}

void VDRigidBody::addForce(const VDVector3& force){}

void VDRigidBody::addForce(float x, float y, float z){
	addForce(VDVector3(x,y,z));
}
