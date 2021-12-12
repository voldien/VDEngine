#define USE_PHYSX
#include"VDSphereCollider.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;

VDSphereCollider::VDSphereCollider() : VDCollider(eSphere){

}

void VDSphereCollider::instanceInitilize(){

}

void VDSphereCollider::onEnable(){
	VDCollider::onEnable();
}

void VDSphereCollider::onDisable(){
	VDCollider::onDisable();
}

void VDSphereCollider::initializeComponent(){
	VDCollider::initializeComponent();
}

void VDSphereCollider::onDestroy(){
	VDCollider::onDestroy();
}

VDBehavior* VDSphereCollider::copyComponent(unsigned int& dataSize){
	VDSphereCollider* BehaviorData = (VDSphereCollider*)malloc(sizeof(VDSphereCollider));
	memcpy(BehaviorData, this, sizeof(VDSphereCollider));
	dataSize = sizeof(VDSphereCollider);
	return BehaviorData;
}

void VDSphereCollider::setRadius(float radius){
	PxShape* shape = this->getShape();
	if(!shape)
		return;
	shape->setGeometry(PxSphereGeometry(radius));
}

float VDSphereCollider::getRadius()const{
	PxShape* shape = this->getShape();
	PxSphereGeometry s;
	if(!shape)
		return 0.0f;
	else{
		shape->getSphereGeometry(s);
		return s.radius;
	}
}
