#include"physic/VDCollider.h"


VDCollider::VDCollider() : VDPhysicActor(){

}

VDCollider::VDCollider(const VDCollider& collider){

}

VDCollider::VDCollider(CollisionType collisionType){

}

void VDCollider::instanceInitilize(){}
void VDCollider::onEnable(){}
void VDCollider::onDisable(){}
void VDCollider::initializeComponent(){}
void VDCollider::onDestroy(){}
VDBehavior* VDCollider::copyComponent(unsigned int& dataSize){}
