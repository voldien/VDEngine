#define USE_PHYSX
#include"VDCharacterControllerHit.h"
#include<physx/PxPhysicsAPI.h>

VDCharacterControllerHit::VDCharacterControllerHit(void){
	this->data = NULL;
}

VDCharacterControllerHit::VDCharacterControllerHit(const VDCharacterControllerHit& hit){
	this->data = hit.data;
}

VDCharacterControllerHit::VDCharacterControllerHit(const void* hit){
	data = hit;
}

//			CharacterControllerHit				//
VDCollider* VDCharacterControllerHit::collider(void){
	return  VDCASTP(VDGameObject*,((physx::PxControllerShapeHit*)this->data)->actor->userData)->collider();
}

VDRigidBody* VDCharacterControllerHit::rigidBody(void){
	return  VDCASTP(VDGameObject*,((physx::PxControllerShapeHit*)this->data)->actor->userData)->rigidBody();
}

VDTransform* VDCharacterControllerHit::transform(void){
	return  VDCASTP(VDGameObject*,((physx::PxControllerShapeHit*)this->data)->actor->userData)->transform();
}

VDGameObject* VDCharacterControllerHit::gameObject(void){
	return  VDCASTP(VDGameObject*,((physx::PxControllerShapeHit*)this->data)->actor->userData);
}

VDCharacterController* VDCharacterControllerHit::controller(void){
	return  VDCASTP(VDGameObject*,((physx::PxControllerShapeHit*)this->data)->actor->userData)->getComponent<VDCharacterController>();
}

VDVector3 VDCharacterControllerHit::point(void)const{
	return *(VDVector3*)&((physx::PxControllerShapeHit*)this->data)->worldPos;
}

VDVector3 VDCharacterControllerHit::normal(void)const{
	return *(VDVector3*)&((physx::PxControllerShapeHit*)this->data)->worldNormal;
}

VDVector3 VDCharacterControllerHit::moveDirection(void)const{
	return *(VDVector3*)&((physx::PxControllerShapeHit*)this->data)->dir;
}

VDVector3 VDCharacterControllerHit::moveLength(void)const{
	return *(VDVector3*)&((physx::PxControllerShapeHit*)this->data)->length;
}
