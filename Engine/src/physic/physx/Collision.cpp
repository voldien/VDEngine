#define USE_PHYSX
#include"VDCollision.h"
#include"VDContact.h"
#include"VDCollider.h"
#include<physx/PxPhysics.h>


using namespace physx;

VDCollision::VDCollision(void){
	this->pair = NULL;
	this->shape = NULL;
}

VDCollision::VDCollision(const VDCollision& collision){
	this->pair = collision.pair;
	this->shape = collision.shape;
}

VDCollider* VDCollision::collider(void)const{
	return VDCASTP(VDCollider*, VDCASTP(physx::PxShape*,shape)->userData);
}

float VDCollision::relativeVelocity(void)const{
	return NULL;
}

VDTransform*  VDCollision::transform(void)const{
	return VDCASTP(VDGameObject*,VDCASTP(physx::PxShape*,shape)->getActor()->userData)->transform();
}

VDGameObject* VDCollision::gameObject(void)const{
	return VDCASTP(VDGameObject*,VDCASTP(physx::PxShape*,shape)->getActor()->userData);
}

VDRigidBody*  VDCollision::rigidBody(void)const{
	return VDCASTP(VDGameObject*,VDCASTP(physx::PxShape*,shape)->getActor()->userData)->rigidBody();
}

VDContact VDCollision::contacts(void)const{
	if(VDCASTP(physx::PxContactPair*,pair)->events & PxPairFlag::eNOTIFY_CONTACT_POINTS){

		VDContact conc;
		VDCASTP(physx::PxContactPair*,pair)->extractContacts(conc.pcontact, VDCASTP(physx::PxContactPair*,pair)->contactStreamSize);
		conc.count = VDCASTP(physx::PxContactPair*,pair)->contactCount;
		return conc;
	}
	else
		return VDContact();
}


