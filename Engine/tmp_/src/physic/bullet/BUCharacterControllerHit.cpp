#include"physic/VDCharacterControllerHit.h"

VDControllerColliderHit::VDControllerColliderHit(){}
VDControllerColliderHit::VDControllerColliderHit(const VDControllerColliderHit& hit){}
VDControllerColliderHit::VDControllerColliderHit(const void* hit){}

VDCollider* VDControllerColliderHit::collider(){}

VDRigidBody* VDControllerColliderHit::rigidBody(){}

VDTransform* VDControllerColliderHit::transform(){}

VDGameObject* VDControllerColliderHit::gameObject(){}

VDCharacterController* VDControllerColliderHit::controller(){}

VDVector3 VDControllerColliderHit::point()const{}

VDVector3 VDControllerColliderHit::normal()const{}

VDVector3 VDControllerColliderHit::moveDirection()const{}

VDVector3 VDControllerColliderHit::moveLength()const{}
