#define USE_PHYSX
#include"VDCapsuleCollider.h"
#include<physx/PxPhysicsAPI.h>

using namespace std;
using namespace physx;

VDCapsuleCollider::VDCapsuleCollider(void) : VDCollider(eCapsule){
}

void VDCapsuleCollider::instanceInitilize(void){

}

void VDCapsuleCollider::onEnable(void){
	VDCollider::onEnable();
}

void VDCapsuleCollider::onDisable(void){
	VDCollider::onDisable();
}

void VDCapsuleCollider::initializeComponent(void){
	VDCollider::initializeComponent();
}

void VDCapsuleCollider::onDestroy(void){
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


float VDCapsuleCollider::getRadius(void)const{
	PxShape* shape = this->getShape();
	PxCapsuleGeometry cp;
	if(shape == NULL)
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

float VDCapsuleCollider::getHeight(void)const{
	PxShape* shape = this->getShape();
	PxCapsuleGeometry cp;
	if(shape == NULL)
		return 0.0f;
	else{
		shape->getCapsuleGeometry(cp);
		return cp.halfHeight;
	}
}
