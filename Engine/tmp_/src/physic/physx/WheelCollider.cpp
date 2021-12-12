#include"VDWheelCollider.h"
#include"VDCollision.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;


VDWheelCollider::VDWheelCollider() : VDCollider(eWheel){

}

void VDWheelCollider::initializeComponent(){
	VDCollider::initializeComponent();

}

void VDWheelCollider::instanceInitilize(){

}

void VDWheelCollider::onEnable(){

}

void VDWheelCollider::onDisable(){

}

void VDWheelCollider::onDestroy(){

}

VDBehavior* VDWheelCollider::copyComponent(unsigned int& dataSize){
	VDWheelCollider* wheel = (VDWheelCollider*)malloc(sizeof(VDWheelCollider));
	memcpy(wheel,this, sizeof(VDWheelCollider));
	dataSize = sizeof(VDWheelCollider);
	return (VDBehavior*)wheel;
}

