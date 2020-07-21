#include"VDWheelCollider.h"
#include"VDCollision.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;


VDWheelCollider::VDWheelCollider(void) : VDCollider(eWheel){

}

void VDWheelCollider::initializeComponent(void){
	VDCollider::initializeComponent();

}

void VDWheelCollider::instanceInitilize(void){

}

void VDWheelCollider::onEnable(void){

}

void VDWheelCollider::onDisable(void){

}

void VDWheelCollider::onDestroy(void){

}

VDBehavior* VDWheelCollider::copyComponent(unsigned int& dataSize){
	VDWheelCollider* wheel = (VDWheelCollider*)malloc(sizeof(VDWheelCollider));
	memcpy(wheel,this, sizeof(VDWheelCollider));
	dataSize = sizeof(VDWheelCollider);
	return (VDBehavior*)wheel;
}

