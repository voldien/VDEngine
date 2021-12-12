#undef USE_PHYSX
#define USE_BULLET

#include"VDPhysic.h"
#include"VDEngine.h"
#include<bullet/btBulletCollisionCommon.h>




void VDPhysic::initialize(){

	btBroadphaseInterface*                  _broadphase;
	btDefaultCollisionConfiguration*        _collisionConfiguration;
	btCollisionDispatcher*                  _dispatcher;
	btSequentialImpulseConstraintSolver*    _solver;
	btDiscreteDynamicsWorld*                _world;

	VDDebug::log("Started to initialization of Bullet Physic.\n");



	VDDebug::log("Creating Broad phase.\n");
	engine.physic._broadphase = new btDbvtBroadphase();
	if(!engine.physic._broadphase){
		VDDebug::errorLog("Failed to create btDbvtBroadphase.\n");
	}

	engine.physic._collisionConfiguration = new btDefaultCollisionConfiguration();
	if(!engine.physic._collisionConfiguration){
		VDDebug::errorLog("Failed to create DefaultCollisionConfiguration.\n");
	}


	engine.physic._dispatcher = new btCollisionDispatcher((btDefaultCollisionConfiguration*)engine.physic._collisionConfiguration);
	if(!engine.physic._dispatcher){
		VDDebug::errorLog("Failed to create CollisionDispatcher.\n");
	}


	//engine.physic._solver = new btSequentialImpulseConstraintSolver();
	if(!engine.physic._solver){
		VDDebug::errorLog("Failed to create SequentialImpulseConstraintSolver.\n");
	}

/*
	engine.physic._world = new btDiscreteDynamicsWorld((btCollisionDispatcher*)engine.physic._dispatcher,
			(btDbvtBroadphase*)engine.physic._broadphase,
			(btSequentialImpulseConstraintSolver*)engine.physic._solver,
			(btDefaultCollisionConfiguration*)engine.physic._collisionConfiguration);
	*/

	if(!engine.physic._world){
		VDDebug::errorLog("Failed to create DiscreteDynamicsWorld.\n");
	}

}

void VDPhysic::release(){

	/*	*/
	delete engine.physic._broadphase;
	delete engine.physic._collisionConfiguration;
	delete engine.physic._dispatcher;
	delete engine.physic._solver;
	delete engine.physic._world;

	//plDeleteDynamicsWorld((plDynamicsWorldHandle)engine.physic.gPhysxScene);
	//plDeletePhysicsSdk((plPhysicsSdkHandle)engine.physic.gPhysic);
}


void VDPhysic::initDebug(const char* pvdHostIp){

}


int VDPhysic::initVehicleSDK(){

	return 1;
}

int VDPhysic::initialzeScene(){

	return 1;
}


void VDPhysic::simulation(){

}


void VDPhysic::update(){

}

void VDPhysic::setGravity(const VDVector3& gravity){

	//engine.physic._world->setGravity(*(btVector3*)&gravity);
}

VDVector3 VDPhysic::getGravity(){
	//return *(VDVector3*)&engine.physic._world->getGravity();
}

bool VDPhysic::isPhysicEnabled(){
	return true;
}


bool VDPhysic::rayCast(const VDVector3& origin, const VDVector3& direction, float distance){}


bool VDPhysic::rayCast(const VDVector3& origin, const VDVector3& direction, float distance, VDRaycastHit& hit){}

bool VDPhysic::rayCast(const VDVector3& origin, const VDVector3& direction, VDRaycastHit& hit){}

bool VDPhysic::lineCast(const VDVector3& start, const VDVector3& end){}

bool VDPhysic::lineCast(const VDVector3& start, const VDVector3& end, VDRaycastHit& hit){}

int VDPhysic::overlapSphere(const VDVector3& position, float radius, VDRaycastHit& hit){}




/*	btCollisionObject as the main actor I would believe.	*/




void VDPhysic::addActor(void* actor){

}


void VDPhysic::removeActor(void* actor){

}























/*
PxPhysics* VDPhysic::getVDPhysicHandle(){
	return engine.physic.gPhysic;
}

PxScene* VDPhysic::getVDPhysicScene(){
	return engine.physic.gPhysxScene;
}
*/
