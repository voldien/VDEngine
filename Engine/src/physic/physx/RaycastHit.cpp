#define USE_PHYSX
#include"VDRaycastHit.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;


VDRaycastHit::VDRaycastHit(void){

}

VDRaycastHit::VDRaycastHit(const VDRaycastHit& hit){
	//*this = hit;
}


VDCollider* VDRaycastHit::collider(void)const{
	return VDCASTP(VDGameObject*,this->hitdata.actor->userData)->collider();
}

VDRigidBody* VDRaycastHit::rigidBody(void)const{
	return VDCASTP(VDGameObject*,this->hitdata.actor->userData)->rigidBody();
}

VDGameObject* VDRaycastHit::gameObject(void)const{
	return VDCASTP(VDGameObject*,this->hitdata.actor->userData);
}

VDTransform* VDRaycastHit::transform(void)const{
	return VDCASTP(VDGameObject*,this->hitdata.actor->userData)->transform();
}

VDVector3 VDRaycastHit::point(void)const{
	return *VDCASTP(const VDVector3*,&this->hitdata.position);
}

VDVector3 VDRaycastHit::normal(void)const{
	return *VDCASTP(const VDVector3*,&this->hitdata.normal);
}

float VDRaycastHit::distance(void)const{
	return this->hitdata.distance;
}

VDVector2 VDRaycastHit::barycentric(void)const{
	return VDVector2(this->hitdata.u,this->hitdata.v);
}
