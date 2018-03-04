#define USE_PHYSX
#include<physx/PxPhysics.h>
#include"VDCharacterController.h"

using namespace std;
using namespace physx;

VDCharacterController::VDCharacterController(void) : VDCollider(eCharacterController){
	this->controller = NULL;
	this->mindistance = 0.00015f;
}

VDCharacterController::VDCharacterController(VDCharacterController& controller): VDCollider(eCharacterController){
	this->controller = NULL;
	this->mindistance = 0.00015f;
}


void VDCharacterController::instanceInitilize(void){

}

void VDCharacterController::onEnable(void){
	VDCollider::onEnable();
}

void VDCharacterController::onDisable(void){
	VDCollider::onDisable();
}

void VDCharacterController::initializeComponent(void){
	if(!VDPhysic::isPhysicEnabled())
		return;

	if(!this->controller)
		this->controller = VDPhysic::createCharacterController(this->transform());
	if(this->controller)
		this->actor = this->controller->getActor();

}

void VDCharacterController::onDestroy(void){
	this->controller->release();

}

VDBehavior* VDCharacterController::copyComponent(unsigned int& dataSize){
	VDCharacterController* controller = (VDCharacterController*)malloc(sizeof(VDCharacterController));
	memcpy(controller,this, sizeof(VDCharacterController));
	dataSize = sizeof(VDCharacterController);
	return (VDBehavior*)controller;
}

int VDCharacterController::setShape(CharacterType type){

	return SDL_TRUE;
}

unsigned int VDCharacterController::getCollisionFlag(void)const{
	PxControllerState state;
	this->controller->getState(state);
	return state.collisionFlags;
}

int VDCharacterController::move(const VDVector3& motion){

	if(this->getState()){
		PxControllerFilters filters =PxControllerFilters(NULL);
		PxControllerCollisionFlags collisonFlag = this->controller->move(*((const PxVec3*)&motion.e[0]),this->mindistance,  VDTime::deltaTime(),(PxControllerFilters)filters);

		this->transform()->setPosition(
				VDVector3((float)this->controller->getPosition().x,
			(float)this->controller->getPosition().y,
			(float)this->controller->getPosition().z));

		return *(int*)&collisonFlag;
	}
	else{
		PxExtendedVec3 pos = PxExtendedVec3(
				(this->transform()->getPosition() + motion).x(),
				(this->transform()->getPosition() + motion).y(),
				(this->transform()->getPosition() + motion).z() );
		this->controller->setPosition(pos);

		this->transform()->setPosition(this->transform()->getPosition() + motion);
	}
	return SDL_TRUE;
}

void VDCharacterController::setRadius(float radius){
	switch(this->controller->getType()){
	case PxControllerShapeType::eCAPSULE:
		break;
	case PxControllerShapeType::eBOX:
		break;
	default:
		break;
	}
}

float VDCharacterController::getRadius(void)const{
	switch(this->controller->getType()){
	case PxControllerShapeType::eBOX:
		return this->PxGetBoxGeometry().halfExtents.magnitude();
	case PxControllerShapeType::eCAPSULE:
		return this->PxGetCapsuleGeometry().radius;
	default:
		return 0.0f;
	}
}

float VDCharacterController::getHeight(void)const{
	switch(this->controller->getType()){
	case PxControllerShapeType::eBOX:
		return this->PxGetBoxGeometry().halfExtents.y;
	case PxControllerShapeType::eCAPSULE:
		return this->PxGetCapsuleGeometry().halfHeight;
	default:
		return 0.0f;
	}
}

void VDCharacterController::setHeight(float height){
	if(this->controller)
		this->controller->resize(height);
}
