#include"physic/VDCharacterControllerHit.h"

VDControllerColliderHit::VDControllerColliderHit(void){}
VDControllerColliderHit::VDControllerColliderHit(const VDControllerColliderHit& hit){}
VDControllerColliderHit::VDControllerColliderHit(const void* hit){}

VDCollider* VDControllerColliderHit::collider(void){}

VDRigidBody* VDControllerColliderHit::rigidBody(void){}

VDTransform* VDControllerColliderHit::transform(void){}

VDGameObject* VDControllerColliderHit::gameObject(void){}

VDCharacterController* VDControllerColliderHit::controller(void){}

VDVector3 VDControllerColliderHit::point(void)const{}

VDVector3 VDControllerColliderHit::normal(void)const{}

VDVector3 VDControllerColliderHit::moveDirection(void)const{}

VDVector3 VDControllerColliderHit::moveLength(void)const{}
