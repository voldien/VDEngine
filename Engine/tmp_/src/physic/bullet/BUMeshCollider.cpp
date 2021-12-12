#include"VDMeshCollider.h"


VDMeshCollider::VDMeshCollider(){}
VDMeshCollider::VDMeshCollider(const VDMeshCollider& collider){}
VDMeshCollider::VDMeshCollider(bool convex){}
VDMeshCollider::VDMeshCollider(const VDMesh* mesh, bool convex, VDGameObject* gameobject){}
VDMeshCollider::~VDMeshCollider(){}


void VDMeshCollider::instanceInitilize(){}
void VDMeshCollider::onEnable(){}
void VDMeshCollider::onDisable(){}
void VDMeshCollider::initializeComponent(){}
void VDMeshCollider::onDestroy(){}
VDBehavior* VDMeshCollider::copyComponent(unsigned int& dataSize){}
