#define USE_PHYSX
#include"VDMeshCollider.h"
#include"VDBoxCollider.h"
#include"VDSphereCollider.h"
#include"VDRigidBody.h"
#include<physx/PxPhysicsAPI.h>

using namespace std;
using namespace physx;
vector<VDRigidBody*> rigidBodyCollection;



VDRigidBody::VDRigidBody(void) : VDPhysicActor(){
	this->actor = NULL;
}

void VDRigidBody::instanceInitilize(void){
	VDPhysic::addActor(this->actor);

	if(getActor())
		VDCAST(PxActor*, getActor())->userData = gameObject();
	rigidBodyCollection.push_back(this);
}

void VDRigidBody::initializeComponent(void){
	VDPhysicActor::initializeComponent();
	this->initVDPhysicObject((this->collider() != NULL) ?  true : false,true);
	this->kinect(false);
	this->useGraivity(true);
	this->setMass(1.0f);
	this->PxShapeSimulate(true);
	this->GetDynamicActor()->setLinearDamping(0.0f);
	this->GetDynamicActor()->setAngularDamping(0.05f);
	rigidBodyCollection.push_back(this);

	// define gameobject as a rigidbody atteched
	this->gameObject()->setActive(this->gameObject()->getActiveFlag() | VDGameObject::eRigidbody);
}

void VDRigidBody::onEnable(void){
	this->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, false);
}

void VDRigidBody::onDisable(void){
	this->GetDynamicActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);
}

void VDRigidBody::onDestroy(void){
	for(std::vector<VDRigidBody*>::iterator x = rigidBodyCollection.begin(); x != rigidBodyCollection.end(); x++){
		if((*x) == this){
			rigidBodyCollection.erase(x);
			//TODO Clean Actor Data and Collider Information
			VDPhysic::removeActor(this->getActor());
			// Remove All Data Releated to this.
			if(!this->isColliderAttached())
				this->PxReleaseActor();
			break;
		}
	}
}

VDBehavior* VDRigidBody::copyComponent(unsigned int& dataSize){
	VDRigidBody* rigid = (VDRigidBody*)malloc(sizeof(VDRigidBody));
	memcpy(rigid,this, sizeof(VDRigidBody));
	dataSize = sizeof(VDRigidBody);
	VDPhysic::copyInstanceActor(this,rigid);
	return (VDBehavior*)rigid;
}

void VDRigidBody::addForce(const VDVector3& force){
	((PxRigidDynamic*)this->actor)->addForce(*VDCASTP(const PxVec3*,&force));
}

void VDRigidBody::addForceAtPosition(const VDVector3& force,const  VDVector3& position){
	PxRigidBodyExt::addForceAtPos(*(PxRigidBody*)this->actor,*(PxVec3*)&force,*(PxVec3*)&position); 
}

void VDRigidBody::addRelativeForce(const VDVector3& force){

}

void VDRigidBody::addRelativeTorque(const VDVector3& force){

}

void VDRigidBody::addTorque(const VDVector3& force){
	((PxRigidDynamic*)this->actor)->addTorque(*VDCASTP(const PxVec3*,&force));
}

void VDRigidBody::setMass(float Mass){
	this->GetDynamicActor()->setMass(Mass);
}

float VDRigidBody::getMass(void)const{
	return ((PxRigidDynamic*)this->actor)->getMass();
}

void VDRigidBody::setDrag(float drag){
	((PxRigidDynamic*)this->actor)->setLinearDamping(drag);
}

float VDRigidBody::getDrag(void)const{
	return ((PxRigidDynamic*)this->actor)->getLinearDamping();
}

void VDRigidBody::sleep(void){
	this->GetDynamicActor()->putToSleep();
}

void VDRigidBody::wake(void){
	this->GetDynamicActor()->wakeUp();
}

void VDRigidBody::useGraivity(bool useGravity){
	this->GetRigidActor()->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, (useGravity == true) ? false : true);
}

void VDRigidBody::kinect(bool kinect){
	this->GetDynamicActor()->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, kinect);
}
