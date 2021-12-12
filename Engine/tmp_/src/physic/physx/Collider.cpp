#define USE_PHYSX
#include"VDPhysicActorBase.h"

#include"VDCollider.h"
#include"VDRigidBody.h"
#include"VDPhysicMaterial.h"
#include<physx/PxPhysicsAPI.h>


using namespace physx;
using namespace std;
vector<VDCollider*> colliderCollection;

VDCollider::VDCollider() : VDPhysicActor(){
	this->type = eUnknown;
}

VDCollider::VDCollider(const VDCollider& collider) : VDPhysicActor(){
	*this = collider;
}

VDCollider::VDCollider(CollisionType collisionType) : VDPhysicActor(){
	this->type = collisionType;
}

void VDCollider::instanceInitilize(){

}

void VDCollider::onEnable(){
	this->PxShapeSimulate(true);
}

void VDCollider::onDisable(){
	this->PxShapeSimulate(false);
}

void VDCollider::initializeComponent(){
	if(!VDPhysic::isPhysicEnabled())
		return;

	VDPhysicActor::initializeComponent();

	this->initVDPhysicObject(true, (this->rigidBody() != nullptr) ?  true : false);

	if(!getShape())
		this->initCollision(); // if actor is null.


	this->PxShapeSimulate(true);
	this->PxSimulate(true);
	this->isTrigger(false);
	this->PxShapeSceneQuerty(true);
	this->menable |= VDBehavior::ColliderShape;
	colliderCollection.push_back(this);

	this->PxSetGlobalPosition(this->transform()->getPosition());
	//this->PxSetGlobalRotation(this->transform()->getRotation());

}

void VDCollider::onDestroy(){
	// remove collider from the list!
	for(vector<VDCollider*>::iterator x = colliderCollection.begin(); x != colliderCollection.end(); x++){
		if((*x) == this){
			if(!this->isRigidBodyAttached()){
				VDPhysic::removeActor(this->getActor());
				this->PxReleaseActor();
			}
			else this->getShape()->release();
			// don't remove actor
			colliderCollection.erase(x);
			break;
		}
	}
}

VDBehavior* VDCollider::copyComponent(unsigned int& dataSize){
	VDCollider* collider = (VDCollider*)malloc(sizeof(VDCollider));
	memcpy(collider,this, sizeof(VDCollider));
	dataSize = sizeof(VDCollider);
	return (VDBehavior*)collider;
}

void VDCollider::isTrigger(bool trigger){
	if(this->getShape()){
		if(!trigger)
			this->menable = (~VDBehavior::ColliderTrigger & this->menable) | VDBehavior::ColliderShape;
		else
			this->menable = (~VDBehavior::ColliderShape & this->menable) | VDBehavior::ColliderTrigger;
		this->getShape()->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !trigger);
		this->getShape()->setFlag(PxShapeFlag::eTRIGGER_SHAPE, trigger);
	}
}

void VDCollider::setMaterial(const VDPhysicMaterial* material){
	if(!material)
		return;

	this->getShape()->setMaterials((PxMaterial*const*)material->getMaterial(), 1);
}

VDPhysicMaterial VDCollider::getMaterial()const{
	VDPhysicMaterial shapematerial;
	this->getShape()->getMaterials(&shapematerial.m_material, sizeof(PxMaterial));
	return shapematerial;
}

VDCollider::CollisionType VDCollider::getColliderType()const{
	return this->type;
}

VDVector3 VDCollider::getCenter()const{
	if(this->getShape()){
		return *VDCASTP(const VDVector3*,&this->getShape()->getLocalPose().p);
	}
	else
		return VDVector3();
}

void VDCollider::setCenter(const VDVector3& center){
	if(this->getShape()){
		this->getShape()->setLocalPose(PxTransform(*VDCASTP(const PxVec3*,&center)));
	}
}

VDCollider& VDCollider::operator=(const VDCollider& collider){

	return *this;
}


void VDCollider::initCollision(){
	VDPhysic::createShape(this, (unsigned int)this->getColliderType());
	VDPhysic::addActor(this->getActor());
}


int VDCollider::setReferenceOnActor(){
	PxShape* shape = this->getShape();

	if(shape){
		shape->userData = this;
		return SDL_TRUE; // find a shape of collider. 
	}
	return SDL_FALSE;
}
