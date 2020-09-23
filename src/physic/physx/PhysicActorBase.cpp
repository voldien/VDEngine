#define USE_PHYSX
#include"VDRigidBody.h"
#include"VDPhysicActorBase.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;

VDPhysicActor::VDPhysicActor(void) : VDBehavior(){
	this->actor = NULL;
}

void VDPhysicActor::onEnable(void){

}

void VDPhysicActor::onDisable(void){

}

void VDPhysicActor::initializeComponent(void){
	this->transform()->base = this;
}

void VDPhysicActor::onDestroy(void){

}

PxCloth* VDPhysicActor::getClothActor(void){
	return VDCASTP(PxActor*,getActor() )->isCloth();
}

PxParticleBase* VDPhysicActor::GetParticleBaseActor(void){
	return VDCASTP(PxActor*,getActor() )->isParticleBase();
}

PxRigidDynamic* VDPhysicActor::GetDynamicActor(void){
	return VDCASTP(PxRigidDynamic*, this->actor);
}

PxRigidStatic* VDPhysicActor::GetStaticActor(void){
	return VDCASTP(PxRigidStatic*, this->actor);
}

PxRigidActor* VDPhysicActor::GetRigidActor(void){
	return VDCASTP(PxRigidActor*, this->actor);
}

PxShape* VDPhysicActor::getShape(unsigned int index){
	if(this->GetRigidActor()){
		PxShape* shape = NULL;
		this->GetRigidActor()->getShapes(&shape, sizeof(PxShape),index);
		return shape;
	}
	else
		return NULL;
}
int VDPhysicActor::getShapeCount(void){
	if(this->GetRigidActor())
		return this->GetRigidActor()->getNbShapes();
	else
		return -1;
}
void VDPhysicActor::DetachShape(int index){
	if(this->GetRigidActor())
		this->GetRigidActor()->detachShape(*this->getShape(index));
}

PxGeometryHolder VDPhysicActor::PxGetGeometry(void){
	if(this->getShape()){
		return this->getShape()->getGeometry();
	}
	else{
		return PxGeometryHolder();
	}
}
PxBoxGeometry VDPhysicActor::PxGetBoxGeometry(void){
	if(this->getShape()){
		return this->getShape()->getGeometry().box();
	}
	else
		return PxBoxGeometry();
}
PxCapsuleGeometry VDPhysicActor::PxGetCapsuleGeometry(void){
	if(this->getShape()){
		return this->getShape()->getGeometry().capsule();
	}
	else
		return PxCapsuleGeometry();
}
PxSphereGeometry VDPhysicActor::PxGetSphereGeometry(void){
	if(this->getShape()){
		return this->getShape()->getGeometry().sphere();
	}
	else
		return PxSphereGeometry();
}
PxGeometryType::unsigned int VDPhysicActor::PxGetGeometryType(void){
	if(this->getShape()){
		return this->getShape()->getGeometry().getType();
	}
	else
		return PxGeometryType::eINVALID;
}

void* VDPhysicActor::getActor(void)const{
	return this->actor;
}

void VDPhysicActor::setActor(void* actor){
	this->actor = actor;
}

void VDPhysicActor::PxReleaseActor(void){
	if(this->GetRigidActor()){
		this->GetRigidActor()->release();
	}
}

void VDPhysicActor::PxShapeVisualization(bool Visualization){
#ifdef EX_DEBUG
	PxShape* shape = this->getShape();
	if(shape){
		shape->setFlag(PxShapeFlag::eVISUALIZATION, Visualization);
	}
#endif
}

int VDPhysicActor::PxIsShapeVisualization(void){
	PxShape* shape = this->getShape();
	//if(shape != NULL)
	//	return PX_FLAGS_OPERATORS(shape->getFlags(),PxShapeFlag::eVISUALIZATION) != 0 ? SDL_TRUE : SDL_FALSE;
	//else
		return -1;
}

void VDPhysicActor::PxSimulate(bool simulation){
	PxShape* shape = this->getShape();
	if(shape){
		VDCASTP(PxActor*, getActor())->setActorFlag(PxActorFlag::eDISABLE_SIMULATION,!simulation);
	}
}

void VDPhysicActor::PxShapeSimulate(bool shapesimulate){
	PxShape* shape = this->getShape();
	if(shape != NULL){
		if(this->menable & VDBehavior::ColliderShape){
			shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, !shapesimulate);
			shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, shapesimulate);
		}
		if(this->menable & VDBehavior::ColliderTrigger){
			shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !shapesimulate);
			shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, shapesimulate);
		}
	}
}

void VDPhysicActor::PxShapeSceneQuerty(bool querty){
	PxShape* shape = this->getShape();
	if(shape != NULL){
		shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, querty);
	}
}

void VDPhysicActor::PxShapeDrainParticle(bool drain){
	PxShape* shape = this->getShape();
	if(shape != NULL){
		shape->setFlag(PxShapeFlag::ePARTICLE_DRAIN, drain);
	}
}

void VDPhysicActor::PxShapeModifyContact(bool modifyContact){
	if(this->getShape() == NULL)
		return;
	PxShape* shape = this->getShape();
	PxFilterData filterdata;
	filterdata.word0 = PxPairFlag::eMODIFY_CONTACTS;
	shape->setSimulationFilterData(filterdata);
	//this->getShape()->
}

void VDPhysicActor::PxSetGlobalPosition(const VDVector3& position){
	if(this->actor->isRigidDynamic())
		this->actor->setGlobalPose(PxTransform(*VDCASTP(const PxVec3*, &position),this->actor->getGlobalPose().q),false);
	else{
		if(this->actor->getNbShapes() > 0){
			//PxVec3 tempPos = this->getShape()->getLocalPose().p;
			//this->getShape()->setLocalPose(PxTransform(*CASTP(const PxVec3*, &(VDVector3((float*)&tempPos) - position)),this->getShape()->getLocalPose().q));
		}
	}
}

VDVector3 VDPhysicActor::PxGetGlobalPosition(void)const{
	return *VDCASTP(const VDVector3*,&this->actor->getGlobalPose().p);
}


bool VDPhysicActor::isRigidBodyAttached(void)const{
	return (this->rigidBody() != nullptr);
}

/*  is Collider Attached to this Gameobject.
*/
bool VDPhysicActor::isColliderAttached(void)const{
	return (this->collider() != nullptr);
}


bool VDPhysicActor::isDynamicRigid(void){
	if(this->actor != NULL){
		return (this->actor->isRigidDynamic() != NULL) ? true : false;
	}
	else
		 return false;
}

bool VDPhysicActor::isStaticRigid(void){
	if(this->actor != NULL){
		return (this->actor->isRigidStatic() != NULL) ? true : false;
	}
	else
		 return false;
}

bool VDPhysicActor::initVDPhysicObject(bool iscollider, bool isrigidbody){
	// both are connected!
	if(iscollider && isrigidbody){
		this->actor = this->rigidBody()->getActor();
	}
	else{
		// only one of them are connected!
		if(iscollider)
			setActor(VDPhysic::createRigidStatic((VDCollider*)this) );
		else if(isrigidbody)
			setActor(VDPhysic::createRigidDynamic((VDRigidBody*)this));
	}
	return SDL_TRUE;
}
