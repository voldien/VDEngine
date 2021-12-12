#define USE_PHYSX
#include"VDRaycastHit.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;


VDRaycastHit::VDRaycastHit(){

}

VDRaycastHit::VDRaycastHit(const VDRaycastHit& hit){
	//*this = hit;
}


VDCollider* VDRaycastHit::collider()const{
	return VDCASTP(VDGameObject*,this->hitdata.actor->userData)->collider();
}

VDRigidBody* VDRaycastHit::rigidBody()const{
	return VDCASTP(VDGameObject*,this->hitdata.actor->userData)->rigidBody();
}

VDGameObject* VDRaycastHit::gameObject()const{
	return VDCASTP(VDGameObject*,this->hitdata.actor->userData);
}

VDTransform* VDRaycastHit::transform()const{
	return VDCASTP(VDGameObject*,this->hitdata.actor->userData)->transform();
}

VDVector3 VDRaycastHit::point()const{
	return *VDCASTP(const VDVector3*,&this->hitdata.position);
}

VDVector3 VDRaycastHit::normal()const{
	return *VDCASTP(const VDVector3*,&this->hitdata.normal);
}

float VDRaycastHit::distance()const{
	return this->hitdata.distance;
}

VDVector2 VDRaycastHit::barycentric()const{
	return VDVector2(this->hitdata.u,this->hitdata.v);
}
