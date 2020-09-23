#include"VDPhysicActorBase.h"
#include<bullet/btBulletCollisionCommon.h>

VDPhysicActor::VDPhysicActor(void) : VDBehavior(){
	this->actor = NULL;
}

VDPhysicActor::VDPhysicActor(const VDPhysicActor& actor){

}

void VDPhysicActor::onEnable(void){}
void VDPhysicActor::onDisable(void){}
void VDPhysicActor::initializeComponent(void){

}
void VDPhysicActor::onDestroy(void){}

bool VDPhysicActor::isRigidBodyAttached(void)const{
	VDCASTP(btCollisionObject* , this->actor)->getActivationState();
}

bool VDPhysicActor::isColliderAttached(void)const{

}
