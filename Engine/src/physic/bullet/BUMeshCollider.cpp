#include"VDMeshCollider.h"


VDMeshCollider::VDMeshCollider(void){}
VDMeshCollider::VDMeshCollider(const VDMeshCollider& collider){}
VDMeshCollider::VDMeshCollider(bool convex){}
VDMeshCollider::VDMeshCollider(const VDMesh* mesh, bool convex, VDGameObject* gameobject){}
VDMeshCollider::~VDMeshCollider(void){}


void VDMeshCollider::instanceInitilize(void){}
void VDMeshCollider::onEnable(void){}
void VDMeshCollider::onDisable(void){}
void VDMeshCollider::initializeComponent(void){}
void VDMeshCollider::onDestroy(void){}
VDBehavior* VDMeshCollider::copyComponent(unsigned int& dataSize){}
