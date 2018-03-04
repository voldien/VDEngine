#include"physic/VDCollider.h"


VDCollider::VDCollider(void) : VDPhysicActor(){

}

VDCollider::VDCollider(const VDCollider& collider){

}

VDCollider::VDCollider(CollisionType collisionType){

}

void VDCollider::instanceInitilize(void){}
void VDCollider::onEnable(void){}
void VDCollider::onDisable(void){}
void VDCollider::initializeComponent(void){}
void VDCollider::onDestroy(void){}
VDBehavior* VDCollider::copyComponent(unsigned int& dataSize){}
