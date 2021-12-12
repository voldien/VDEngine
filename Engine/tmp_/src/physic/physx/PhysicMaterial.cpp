#include"VDPhysicMaterial.h"
#include"VDMath.h"
#include"VDPhysic.h"
#include<ELT/math/quad.h>
#include<physx/PxPhysicsAPI.h>


using namespace physx;
extern std::vector<VDPhysicMaterial*> gPhysicMaterialCollection;


/*					VDPhysicMaterial			*/
float VDPhysicMaterial::getStaticFriction(){
	return ((PxMaterial*)this->m_material)->getStaticFriction();
}

void VDPhysicMaterial::setStaticFriction(float staticfriction){
	((PxMaterial*)this->m_material)->setStaticFriction(staticfriction);
}

float VDPhysicMaterial::getDynamicFriction(){
	return ((PxMaterial*)this->m_material)->getDynamicFriction();
}

void VDPhysicMaterial::setDynamicFriction(float dynamicfriction){
	((PxMaterial*)this->m_material)->setStaticFriction(dynamicfriction);
}

float VDPhysicMaterial::getBounciness(){
	return ((PxMaterial*)this->m_material)->getRestitution();
}

void VDPhysicMaterial::setBounciness(float bounciness){
	((PxMaterial*)this->m_material)->setRestitution(VDMath::clamp<float>(bounciness, 0.0f,1.0f));
}

void VDPhysicMaterial::setProperties(float staticFriction, float dynamicFriction, float restriction){
		//assign material properties
	((PxMaterial*)this->m_material)->setStaticFriction(staticFriction);
	((PxMaterial*)this->m_material)->setDynamicFriction(dynamicFriction);
	((PxMaterial*)this->m_material)->setRestitution(restriction);
}

void VDPhysicMaterial::enableFriction(){
	((PxMaterial*)this->m_material)->setFlag(PxMaterialFlag::eDISABLE_FRICTION, false);
}
void VDPhysicMaterial::disableFriction(){
	((PxMaterial*)this->m_material)->setFlag(PxMaterialFlag::eDISABLE_FRICTION, true);
}


VDPhysicMaterial::VDPhysicMaterial(){
	this->m_material = nullptr;
	gPhysicMaterialCollection.push_back(this);
}

VDPhysicMaterial::VDPhysicMaterial(const VDPhysicMaterial& material){
	this->m_material = material.m_material;
}

int VDPhysicMaterial::getCollectionSize(){
	return gPhysicMaterialCollection.size();
}
