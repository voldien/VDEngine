#define USE_PHYSX
#include"VDPlaneCollider.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;

VDPlaneCollider::VDPlaneCollider(void) : VDCollider(ePlane){

}

VDPlaneCollider::VDPlaneCollider(const VDPlaneCollider& collider) : VDCollider(ePlane){

}

void VDPlaneCollider::instanceInitilize(void){

}

void VDPlaneCollider::onEnable(void){
	VDCollider::onEnable();
}

void VDPlaneCollider::onDisable(void){
	VDCollider::onDisable();
}

void VDPlaneCollider::initializeComponent(void){
	VDCollider::initializeComponent();
}

void VDPlaneCollider::onDestroy(void){
	VDCollider::onDestroy();
}

VDBehavior* VDPlaneCollider::copyComponet(unsigned int& dataSize){
	VDPlaneCollider* planeCollider = (VDPlaneCollider*)malloc(sizeof(VDPlaneCollider));
	memcpy(planeCollider,this, sizeof(VDPlaneCollider));
	dataSize = sizeof(VDPlaneCollider);
	return (VDBehavior*)planeCollider;
}

VDVector3 VDPlaneCollider::getNormal(void)const{

	PxTransform trans = getShape()->getLocalPose();
	PxPlane p = PxPlaneEquationFromTransform(trans);
	return *(VDVector3*)&p.n;
}

void VDPlaneCollider::setNormal(const VDVector3& normal){
	/**/
	PxPlane p = PxPlane(
			*(PxVec3*)&this->transform()->getPosition(),
			PxVec3(0,0,1) );
	PxTransform trans = PxTransformFromPlaneEquation(p);
	this->getShape()->getActor()->setGlobalPose(trans);

	/**/
	p = PxPlane(PxVec3(0,0,0),*(PxVec3*)&normal);
	trans = PxTransformFromPlaneEquation(p);
	this->getShape()->setLocalPose(trans);
}
