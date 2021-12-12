#define USE_PHYSX
#include"VDCollision.h"
#include"VDContact.h"
#include"VDCollider.h"
#include<physx/PxPhysics.h>


using namespace physx;

VDCollision::VDCollision(){
	this->pair = nullptr;
	this->shape = nullptr;
}

VDCollision::VDCollision(const VDCollision& collision){
	this->pair = collision.pair;
	this->shape = collision.shape;
}

VDCollider* VDCollision::collider()const{
	return VDCASTP(VDCollider*, VDCASTP(physx::PxShape*,shape)->userData);
}

float VDCollision::relativeVelocity()const{
	return nullptr;
}

VDTransform*  VDCollision::transform()const{
	return VDCASTP(VDGameObject*,VDCASTP(physx::PxShape*,shape)->getActor()->userData)->transform();
}

VDGameObject* VDCollision::gameObject()const{
	return VDCASTP(VDGameObject*,VDCASTP(physx::PxShape*,shape)->getActor()->userData);
}

VDRigidBody*  VDCollision::rigidBody()const{
	return VDCASTP(VDGameObject*,VDCASTP(physx::PxShape*,shape)->getActor()->userData)->rigidBody();
}

VDContact VDCollision::contacts()const{
	if(VDCASTP(physx::PxContactPair*,pair)->events & PxPairFlag::eNOTIFY_CONTACT_POINTS){

		VDContact conc;
		VDCASTP(physx::PxContactPair*,pair)->extractContacts(conc.pcontact, VDCASTP(physx::PxContactPair*,pair)->contactStreamSize);
		conc.count = VDCASTP(physx::PxContactPair*,pair)->contactCount;
		return conc;
	}
	else
		return VDContact();
}


