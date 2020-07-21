#include"VDRigidBody.h"


VDRigidBody::VDRigidBody(void){

}
VDRigidBody::VDRigidBody(const VDRigidBody& rigidbody){

}

void VDRigidBody::instanceInitilize(void){}
void VDRigidBody::onEnable(void){}
void VDRigidBody::onDisable(void){}
void VDRigidBody::initializeComponent(void){}
void VDRigidBody::onDestroy(void){}
VDBehavior* VDRigidBody::copyComponent(unsigned int& dataSize){
	return NULL;
}


void VDRigidBody::addExplosionForce(float force, VDVector3& position,float Radius){}

void VDRigidBody::addForce(const VDVector3& force){}

void VDRigidBody::addForce(float x, float y, float z){
	addForce(VDVector3(x,y,z));
}
