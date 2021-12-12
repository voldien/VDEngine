#include"VDPhysicActorBase.h"
#include<bullet/btBulletCollisionCommon.h>

VDPhysicActor::VDPhysicActor() : VDBehavior(){
	this->actor = nullptr;
}

VDPhysicActor::VDPhysicActor(const VDPhysicActor& actor){

}

void VDPhysicActor::onEnable(){}
void VDPhysicActor::onDisable(){}
void VDPhysicActor::initializeComponent(){

}
void VDPhysicActor::onDestroy(){}

bool VDPhysicActor::isRigidBodyAttached()const{
	VDCASTP(btCollisionObject* , this->actor)->getActivationState();
}

bool VDPhysicActor::isColliderAttached()const{

}
