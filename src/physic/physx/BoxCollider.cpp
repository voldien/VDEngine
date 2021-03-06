#define USE_PHYSX
#include"VDBoxCollider.h"
#include"VDRigidBody.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;
using namespace std;


VDBoxCollider::VDBoxCollider(void) : VDCollider(eBox){

}

void VDBoxCollider::instanceInitilize(void){
	if(this->isRigidBodyAttached())
		this->actor = this->rigidBody()->actor;
}

void VDBoxCollider::onEnable(void){
	VDCollider::onEnable();
}

void VDBoxCollider::onDisable(void){
	VDCollider::onDisable();
}

void VDBoxCollider::initializeComponent(void){
	VDCollider::initializeComponent();
}

void VDBoxCollider::onDestroy(void){
	VDCollider::onDestroy();
}

VDBehavior* VDBoxCollider::copyComponent(unsigned int& dataSize){
	VDBoxCollider* BehaviorData = (VDBoxCollider*)malloc(sizeof(VDBoxCollider));
	memcpy(BehaviorData, this, sizeof(VDBoxCollider));
	dataSize = sizeof(VDBoxCollider);
	return BehaviorData;
}

void VDBoxCollider::setSize(const VDVector3& size){
	PxShape* shape = this->getShape();
	if(shape)
		shape->setGeometry(PxBoxGeometry(*(PxVec3*)&(size * 0.5f)));

}

VDVector3 VDBoxCollider::getSize(void)const{
	if(this->getShape()){
		PxBoxGeometry box;
		this->getShape()->getBoxGeometry(box);
		return *VDCASTP(const VDVector3*,&box.halfExtents);
	}
	else
		return VDVector3();
}
