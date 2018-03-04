#include <Animation/VDAnimation.h>
#include <Audio/VDAudioSource.h>
#include <Core/VDComponent.h>
#include <Core/VDObject.h>
#include <Core/VDTypes.h>
#include <Physic/VDCollider.h>
#include <Physic/VDRigidBody.h>
#include <Rendering/VDCamera.h>
#include <Rendering/VDLight.h>
#include <stddef.h>
#include <Scene/VDGameObject.h>
#include <Scene/VDTransform.h>
#include <VDSimpleType.h>
#include <cassert>
#include <typeinfo>
#include <vector>

VDComponent::VDComponent(void) : VDObject(){
	this->pgameObject = NULL;
}

VDComponent::~VDComponent(void){
}

VDComponent& VDComponent::operator=(const VDComponent& rh){
	VDObject::operator=(rh);
	this->pgameObject = rh.gameObject();
	return *this;
}

bool VDComponent::operator==(const VDComponent* lh)const{
	return ( this == lh);
}

bool VDComponent::operator!=(const VDComponent* lh)const{
	return (this != lh);
}

VDAnimation* VDComponent::animation(void){
	return this->pgameObject->getComponent<VDAnimation>();	
}

VDCamera* VDComponent::camera(void){
	return this->pgameObject->getComponent<VDCamera>();
}

VDTransform* VDComponent::transform(void)const{
	return (VDTransform*)this->pgameObject->componets[0];
}

VDRenderer* VDComponent::renderer(void){
	return this->pgameObject->getComponent<VDRenderer>();
}

VDGameObject* VDComponent::gameObject(void)const{
	return this->pgameObject;
}

VDAudioSource* VDComponent::audio(void){
	return this->pgameObject->getComponent<VDAudioSource>();
}

VDLight* VDComponent::light(void){
	return this->pgameObject->getComponent<VDLight>();
}

VDCollider* VDComponent::collider(void){
	return this->pgameObject->getComponent<VDCollider>();	
}

VDRigidBody* VDComponent::rigidBody(void){
	return this->pgameObject->getComponent<VDRigidBody>();	
}

bool VDComponent::existComponet(const VDTypeInfo& info){
	for(int x = this->pgameObject->componets.size() - 1; x >= 0; x--){
		if(info == typeid(*this->pgameObject->componets[x]))
			return true;
	}
	/*for(int x = this->gameObjectPointer->Componets.size() - 1; x >= 0; x--){
		if(info.before(typeid(*this->gameObjectPointer->Componets[x])) >= 1)
			return SDL_TRUE;
		else
			continue;
	}*/
	/*for(int x = this->gameObjectPointer->CustomComponets.size() -1; x >= 0; x--){
		if(info == typeid(this->gameObjectPointer->CustomComponets[x])){
			return SDL_TRUE;
		}
		else{
			continue;
		}	
	}*/

	return false;
}

VDGameObject* VDComponent::instantiate(void){
	return this->gameObject()->instantiate();
}

VDGameObject* VDComponent::instantiate(const VDVector3& position, const VDQuaternion& rotation){
	return this->gameObject()->instantiate(position, rotation);
}

void* VDComponent::getComponent(const VDTypeInfo& typeinfo){

	/**/
	for(int x = gameObject()->componets.size() - 1; x >= 0; x--){
		if( typeid(*gameObject()->componets[x]) == *typeinfo.getType())
			return  gameObject()->componets[x];
	}

	/**/
	for(int x = gameObject()->componets.size() - 1; x >= 0; x--){
		if(typeid(VDBehavior).before(typeid(*gameObject()->componets[x])) >= 1)
			return gameObject()->componets[x];
	}
	return NULL;
}

void VDComponent::setGameObject(VDGameObject* gameobject){
	assert(gameobject);
	this->pgameObject = gameobject;
}


void VDComponent::destroy(VDGameObject* gameObject){
	VDGameObject::removeGameObject(gameObject);
}
