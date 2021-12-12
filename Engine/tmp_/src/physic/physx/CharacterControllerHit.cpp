#define USE_PHYSX
#include"VDCharacterControllerHit.h"
#include<physx/PxPhysicsAPI.h>

VDCharacterControllerHit::VDCharacterControllerHit(){
	this->data = nullptr;
}

VDCharacterControllerHit::VDCharacterControllerHit(const VDCharacterControllerHit& hit){
	this->data = hit.data;
}

VDCharacterControllerHit::VDCharacterControllerHit(const void* hit){
	data = hit;
}

//			CharacterControllerHit				//
VDCollider* VDCharacterControllerHit::collider(){
	return  VDCASTP(VDGameObject*,((physx::PxControllerShapeHit*)this->data)->actor->userData)->collider();
}

VDRigidBody* VDCharacterControllerHit::rigidBody(){
	return  VDCASTP(VDGameObject*,((physx::PxControllerShapeHit*)this->data)->actor->userData)->rigidBody();
}

VDTransform* VDCharacterControllerHit::transform(){
	return  VDCASTP(VDGameObject*,((physx::PxControllerShapeHit*)this->data)->actor->userData)->transform();
}

VDGameObject* VDCharacterControllerHit::gameObject(){
	return  VDCASTP(VDGameObject*,((physx::PxControllerShapeHit*)this->data)->actor->userData);
}

VDCharacterController* VDCharacterControllerHit::controller(){
	return  VDCASTP(VDGameObject*,((physx::PxControllerShapeHit*)this->data)->actor->userData)->getComponent<VDCharacterController>();
}

VDVector3 VDCharacterControllerHit::point()const{
	return *(VDVector3*)&((physx::PxControllerShapeHit*)this->data)->worldPos;
}

VDVector3 VDCharacterControllerHit::normal()const{
	return *(VDVector3*)&((physx::PxControllerShapeHit*)this->data)->worldNormal;
}

VDVector3 VDCharacterControllerHit::moveDirection()const{
	return *(VDVector3*)&((physx::PxControllerShapeHit*)this->data)->dir;
}

VDVector3 VDCharacterControllerHit::moveLength()const{
	return *(VDVector3*)&((physx::PxControllerShapeHit*)this->data)->length;
}
