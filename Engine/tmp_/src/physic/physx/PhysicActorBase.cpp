#define USE_PHYSX
#include"VDRigidBody.h"
#include"VDPhysicActorBase.h"
#include<physx/PxPhysicsAPI.h>

using namespace physx;

VDPhysicActor::VDPhysicActor() : VDBehavior(){
	this->actor = nullptr;
}

void VDPhysicActor::onEnable(){

}

void VDPhysicActor::onDisable(){

}

void VDPhysicActor::initializeComponent(){
	this->transform()->base = this;
}

void VDPhysicActor::onDestroy(){

}

PxCloth* VDPhysicActor::getClothActor(){
	return VDCASTP(PxActor*,getActor() )->isCloth();
}

PxParticleBase* VDPhysicActor::GetParticleBaseActor(){
	return VDCASTP(PxActor*,getActor() )->isParticleBase();
}

PxRigidDynamic* VDPhysicActor::GetDynamicActor(){
	return VDCASTP(PxRigidDynamic*, this->actor);
}

PxRigidStatic* VDPhysicActor::GetStaticActor(){
	return VDCASTP(PxRigidStatic*, this->actor);
}

PxRigidActor* VDPhysicActor::GetRigidActor(){
	return VDCASTP(PxRigidActor*, this->actor);
}

PxShape* VDPhysicActor::getShape(unsigned int index){
	if(this->GetRigidActor()){
		PxShape* shape = nullptr;
		this->GetRigidActor()->getShapes(&shape, sizeof(PxShape),index);
		return shape;
	}
	else
		return nullptr;
}
int VDPhysicActor::getShapeCount(){
	if(this->GetRigidActor())
		return this->GetRigidActor()->getNbShapes();
	else
		return -1;
}
void VDPhysicActor::DetachShape(int index){
	if(this->GetRigidActor())
		this->GetRigidActor()->detachShape(*this->getShape(index));
}

PxGeometryHolder VDPhysicActor::PxGetGeometry(){
	if(this->getShape()){
		return this->getShape()->getGeometry();
	}
	else{
		return PxGeometryHolder();
	}
}
PxBoxGeometry VDPhysicActor::PxGetBoxGeometry(){
	if(this->getShape()){
		return this->getShape()->getGeometry().box();
	}
	else
		return PxBoxGeometry();
}
PxCapsuleGeometry VDPhysicActor::PxGetCapsuleGeometry(){
	if(this->getShape()){
		return this->getShape()->getGeometry().capsule();
	}
	else
		return PxCapsuleGeometry();
}
PxSphereGeometry VDPhysicActor::PxGetSphereGeometry(){
	if(this->getShape()){
		return this->getShape()->getGeometry().sphere();
	}
	else
		return PxSphereGeometry();
}
PxGeometryType::unsigned int VDPhysicActor::PxGetGeometryType(){
	if(this->getShape()){
		return this->getShape()->getGeometry().getType();
	}
	else
		return PxGeometryType::eINVALID;
}

void* VDPhysicActor::getActor()const{
	return this->actor;
}

void VDPhysicActor::setActor(void* actor){
	this->actor = actor;
}

void VDPhysicActor::PxReleaseActor(){
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

int VDPhysicActor::PxIsShapeVisualization(){
	PxShape* shape = this->getShape();
	//if(shape != nullptr)
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
	if(shape != nullptr){
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
	if(shape != nullptr){
		shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, querty);
	}
}

void VDPhysicActor::PxShapeDrainParticle(bool drain){
	PxShape* shape = this->getShape();
	if(shape != nullptr){
		shape->setFlag(PxShapeFlag::ePARTICLE_DRAIN, drain);
	}
}

void VDPhysicActor::PxShapeModifyContact(bool modifyContact){
	if(this->getShape() == nullptr)
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

VDVector3 VDPhysicActor::PxGetGlobalPosition()const{
	return *VDCASTP(const VDVector3*,&this->actor->getGlobalPose().p);
}


bool VDPhysicActor::isRigidBodyAttached()const{
	return (this->rigidBody() != nullptr);
}

/*  is Collider Attached to this Gameobject.
*/
bool VDPhysicActor::isColliderAttached()const{
	return (this->collider() != nullptr);
}


bool VDPhysicActor::isDynamicRigid(){
	if(this->actor != nullptr){
		return (this->actor->isRigidDynamic() != nullptr) ? true : false;
	}
	else
		 return false;
}

bool VDPhysicActor::isStaticRigid(){
	if(this->actor != nullptr){
		return (this->actor->isRigidStatic() != nullptr) ? true : false;
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
