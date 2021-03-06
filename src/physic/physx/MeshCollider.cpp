#define USE_PHYSX
#include"VDMeshCollider.h"
#include<physx/PxPhysicsAPI.h>

using namespace std; 
using namespace physx;
  

VDMeshCollider::VDMeshCollider(void) : VDCollider(eMesh){

}

VDMeshCollider::VDMeshCollider(const HandleMeshEx& meshHAndlerData, bool convex, VDGameObject* gameobject) : VDCollider((convex == true) ? eConvex : eMesh){
	this->setGameObject(  gameobject );
	this->initVDPhysicObject(true, (this->rigidBody() != NULL) ?  true : false);
	VDPhysic::createShape(this, (unsigned int)this->getColliderType(), &meshHAndlerData);
	VDPhysic::addActor(this->getActor());

}

void VDMeshCollider::instanceInitilize(void){ 

} 
void VDMeshCollider::onEnable(void){ 
    VDCollider::onEnable(); 

} 
void VDMeshCollider::onDisable(void){ 
    VDCollider::onDisable(); 

} 
void VDMeshCollider::initializeComponent(void){ 
    VDCollider::initializeComponent(); 

} 
void VDMeshCollider::onDestroy(void){ 
    VDCollider::onDestroy(); 

} 
VDBehavior* VDMeshCollider::copyComponent(unsigned int& dataSize){ 
    VDMeshCollider* meshCollider = (VDMeshCollider*)malloc(sizeof(VDMeshCollider)); 
    memcpy(meshCollider,this, sizeof(VDMeshCollider)); 
    dataSize = sizeof(VDMeshCollider); 
    return (VDBehavior*)meshCollider; 
} 
  
int VDMeshCollider::convex(bool convex){
    int success = SDL_FALSE; 

    if(convex){ 
        PxShape* shape = this->getShape(); 
        if(!shape)
            return SDL_FALSE; 
        if(this->renderer() != NULL && this->renderer()->getMesh() != NULL){
  
            PxConvexMesh* convex = VDPhysic::genConvexCollision(this->renderer()->getMesh());
			PxMaterial* ma = VDPhysic::getPhysicHandle()->createMaterial(0.5f, 0.5f,0.1f); 
              
            this->actor->createShape(PxConvexMeshGeometry(convex), *ma, 
                PxTransform(*(PxVec3*)&this->transform()->getPosition(),*(PxQuat*)&this->transform()->getRotation()));
            //shape->setGeometry(PxConvexMeshGeometry(convex)); 
            shape->release();
        } 
    } 
    else{ // if convex mesh already exist, remove it !! 
  
    } 

    return success; 
}

void VDMeshCollider::setScale(const VDVector3& scale){
	if(this->getShape()){
		PxTriangleMeshGeometry tg;
		this->getShape()->getTriangleMeshGeometry(tg);
		tg.scale.scale = *VDCASTP(const PxVec3*,&scale);
	}
}

VDVector3 VDMeshCollider::getScale(void)const{
	if(this->getShape()){
		PxTriangleMeshGeometry tg;
		this->getShape()->getTriangleMeshGeometry(tg);
		return *VDCASTP(const VDVector3*,&tg.scale.scale);
	}
	return VDVector3();
}
