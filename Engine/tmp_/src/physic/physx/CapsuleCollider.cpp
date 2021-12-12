#define USE_PHYSX
#include"VDCapsuleCollider.h"
#include<physx/PxPhysicsAPI.h>

using namespace std;
using namespace physx;

VDCapsuleCollider::VDCapsuleCollider() : VDCollider(eCapsule){
}

void VDCapsuleCollider::instanceInitilize(){

}

void VDCapsuleCollider::onEnable(){
	VDCollider::onEnable();
}

void VDCapsuleCollider::onDisable(){
	VDCollider::onDisable();
}

void VDCapsuleCollider::initializeComponent(){
	VDCollider::initializeComponent();
}

void VDCapsuleCollider::onDestroy(){
	// remove collider from the list!
	VDCollider::onDestroy();
}

VDBehavior* VDCapsuleCollider::copyComponent(unsigned int& dataSize){
	VDCapsuleCollider* BehaviorData = (VDCapsuleCollider*)malloc(sizeof(VDCapsuleCollider));
	memcpy(BehaviorData, this, sizeof(VDCapsuleCollider));
	dataSize = sizeof(VDCapsuleCollider);
	return BehaviorData;
}

void VDCapsuleCollider::setRadius(float radius){
	PxShape* shape = this->getShape();
	PxCapsuleGeometry cp;
	if(shape){
		shape->getCapsuleGeometry(cp);
		cp.radius = radius;
	}
}


float VDCapsuleCollider::getRadius()const{
	PxShape* shape = this->getShape();
	PxCapsuleGeometry cp;
	if(shape == nullptr)
		return 0.0f;
	else{
		shape->getCapsuleGeometry(cp);
		return cp.radius;
	}
}
void VDCapsuleCollider::setHeight(float height){
	PxShape* shape = this->getShape();
	PxCapsuleGeometry cp;
	if(shape){
		shape->getCapsuleGeometry(cp);
		cp.halfHeight = height / 2.0f;
	}
}

float VDCapsuleCollider::getHeight()const{
	PxShape* shape = this->getShape();
	PxCapsuleGeometry cp;
	if(shape == nullptr)
		return 0.0f;
	else{
		shape->getCapsuleGeometry(cp);
		return cp.halfHeight;
	}
}
