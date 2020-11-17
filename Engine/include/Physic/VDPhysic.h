/*
    VDEngine virtual dimension game engine.
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VD_PHYSIC_H_
#define _VD_PHYSIC_H_ 1
#include<physic/PhysicInterface.h>
#include"VDPhysicMaterial.h"
#include"../VDDef.h"
#include"../VDSimpleType.h"
#include <vector>

using namespace std;

class PhysicUserControllerHitReport;

/**
 *	Class forwarding bullet classes.
 */
class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;

/**
 *
 */
typedef struct physic_engine{
	union{
#ifdef VD_INTERNAL
	#ifdef USE_PHYSX
		struct{
			PhysicUserControllerHitReport* gPhysiccontrollerreport;
			physx::PxPhysics* gPhysic;
			physx::PxFoundation* gFoundation;
			physx::PxCooking* gCooking;
			physx::PxScene* gPhysxScene;
			physx::PxProfileZoneManager* gProfileManager;
			physx::PxControllerManager* gControlManager;
			physx::PxCudaContextManager* gCudaContextManager;
		};
	#elif defined(USE_BULLET)
		struct{
			void* _broadphase;
			void* _collisionConfiguration;
			void* _dispatcher;
			void* _solver;
			btDiscreteDynamicsWorld* _world;
			void* gProfileManager;
			void* gControlManager;
			void* gCudaContextManager;
		};
	#endif
#else
		struct{
			void* gPhysiccontrollerreport;
			void* gPhysic;
			void* gFoundation;
			void* gCooking;
			void* gPhysxScene;
			void* gProfileManager;
			void* gControlManager;
			void* gCudaContextManager;
		};
#endif
	};
	unsigned int PhysicThreadCount;
}VDPhysicEngine;

#define PX_MATERIAL_DEFAULT_VALUE 0.5f,0.5f, 0.01f
#define PX_MATERIAL_ICE_VALUE 0.5f,0.5f, 0.01f
#define PX_MATERIAL_STONE_VALUE 0.5f,0.5f, 0.01f
#define PX_MATERIAL_WOOD_VALUE 0.5f,0.5f, 0.01f
#define PX_MATERIAL_DEFAULT_VALUE 0.5f,0.5f, 0.01f

extern VDDECLSPEC std::vector<VDPhysicMaterial*> gVDPhysicMaterialCollection;


/**
 *
 */
class VDDECLSPEC VDPhysic : fragcore::Singleton<VDPhysic> {
public:

	/**
	 *	Initialize VDPhysic. Must be called before
	 *	any other physic methods is invoked.
	 */
	static void VDAPIENTRY initialize(void);

	/**
	 *	release alldData association with physic.
	 */
	static void VDAPIENTRY release(void);

	/**
	 *	Initialize Debug Connection with PVD.
	 */
	static void VDAPIENTRY initDebug(const char* pvdHostIp = "127.0.0.1");

	/**
	 *	Initialize Vehicle SDK in order to
	 *	enable vehicle support.
	 */
	static int VDAPIENTRY initVehicleSDK(void);

	/**
	 *
	 */
	static int VDAPIENTRY initialzeScene(void);


public:

	/**
	 *	simulate the physic objects.
	 */
	static void VDAPIENTRY simulation(void);

	/**
	 *
	 */
	static void VDAPIENTRY update(void);


	static void VDAPIENTRY setGravity(const VDVector3& gravity);

	static VDVector3 VDAPIENTRY getGravity(void);

	/**
	 *
	 *	@Return
	 */
	static bool VDAPIFASTENTRY isPhysicEnabled(void);

public:	/*	*/

	/**
	 *	Relevant function for user
	 *	@Return
	 */
	static bool VDAPIENTRY rayCast(const VDVector3& origin, const VDVector3& direction, float distance);

	/**
	 *
	 *	@Return
	 */
	static bool VDAPIENTRY rayCast(const VDVector3& origin, const VDVector3& direction, float distance, VDRaycastHit& hit);

	/**
	 *
	 *	@Return
	 */
	static bool VDAPIENTRY rayCast(const VDVector3& origin, const VDVector3& direction, VDRaycastHit& hit);

	/**
	 *
	 *	@Return
	 */
	static bool VDAPIENTRY lineCast(const VDVector3& start, const VDVector3& end);

	/**
	 *
	 *	@Return
	 */
	static bool VDAPIENTRY lineCast(const VDVector3& start, const VDVector3& end, VDRaycastHit& hit);


	/**
	 *
	 *	@Return
	 */
	int VDAPIENTRY overlapSphere(const VDVector3& position, float radius, VDRaycastHit& hit);



public:	/*	*/

	/**
	 *	Not supported.
	 */
	static void VDAPIENTRY genRagDoll(VDGameObject* root);

	/**
	 *	Create VDPhysicMaterial if no one of template exists
	 *	@Return non null pointer if succesfully.
	 */
	static VDPhysicMaterial* VDAPIENTRY createMaterial(unsigned int materialtemplate);

	/**
	 *	Create new VDPhysic Material. Even if VDPhysic Material with
	 *	exists with the same properteis.
	 *	@Return
	 */
	static VDPhysicMaterial* VDAPIENTRY createMaterial(float staticFriction, float dynamicFriction, float Restitution);

	/**
	 *	Find Material Based on it's material Template
	 *	@Return
	 */
	static VDPhysicMaterial* VDAPIENTRY findMaterial(int materialtemplate);

	/**
	 *	Find Material Based on it's material Propertis[Bounciess, static friction, dynamic friction]
	 *	@Return
	 */
	static VDPhysicMaterial* VDAPIENTRY findMaterial(double staticFriction, double dynamicFriction, double Restitution);

	/**
	 *	Add physic actor to physic scene.
	 */
	static void VDAPIENTRY addActor(void* actor);

	/**
	 *	Remove physic actor from physic scene.
	 */
	static void VDAPIFASTENTRY removeActor(void* actor);


#if defined(VD_INTERNAL) && defined(USE_PHYSX)



	/*	TODO resolve the return value to be able to put in developer space.	*/

	/**
	 *	Create Static RigidActor if Collider Actor is null. otherwise.
	 *	return value will be the current collider actor.
	 */
	static physx::PxRigidStatic* VDAPIENTRY createRigidStatic(VDCollider* transform);

	/**
	 * 	Create Dynamic RigidActor. if actor is attacehd to rigidbody
	 *	GameObject it will only be converted to Dynamic Actor with
	 *	same Properties.
	 */
	static physx::PxRigidDynamic* VDAPIENTRY createRigidDynamic(VDRigidBody* rigidBody);


	/**
	 *	Convert Dynamic Actor To static Actor. attribute
	 *	of Actor gets copy.
	 */
	static physx::PxRigidDynamic* VDAPIENTRY convertDynamicActor(physx::PxRigidStatic* dynamicActor);


	/**
	 *	Convert Static Actor To Dynamic Actor. attribute
	 *	of Actor gets copy.
	 */
	static physx::PxRigidStatic* VDAPIENTRY convertStaticActor(physx::PxRigidDynamic* staticActor);


	/**
	 *	Create a Instance of Copy Attribute from origonalActor to
	 *	Clone Actor
	*/
	static physx::PxRigidActor* VDAPIENTRY copyInstanceActor(VDPhysicActor* origonalActor,VDPhysicActor* CloneActor, bool shareShape = false);


	/**
	 *
	 */
	static physx::PxCloth* VDAPIENTRY createClothActor(VDCloth* cloth, const HandleMeshEx* meshHandler);


	/**
	 *	Save the data of the scene onto a disk
	 */
	static void VDAPIENTRY serializeActor(physx::PxActor* actor,VDBehavior* behavior); 


	/**
	 *
	 */
	static int VDAPIENTRY initlizeRigidBody(VDRigidBody* rigigBody);



#ifdef OPENGL_PHYSX
#endif

	/**
	 *	Create Shape for Collider Object.
	 *	collisionFlag is float of collider float. initlize of float will be defined automatily by the engine.
	 *	@Return
	 */
	static physx::PxShape* VDAPIENTRY createShape(VDCollider* collider, unsigned int collisionFlag, HandleMeshEx* handleMesh);

	/**
	 *	Create Shape for Collider Object.
	 *	collisionFlag is float of collider float. initlize of float will be defined automatily by the engine.
	 *	@Return
	 */
	static physx::PxShape* VDAPIENTRY createShape(VDCollider*  collider, unsigned int collisionFlag);

	/**
	 *
	 */
	static void VDAPIENTRY setupFiltering(physx::PxShape* shape, unsigned int filterGroup, unsigned int filterMask);

	/**
	 *	Create a CharacterController.
	 */
	static physx::PxController* VDAPIENTRY createCharacterController(VDTransform* transform);


	/**
	 *	Generate a Collision mesh based on Mesh
	 */
	static physx::PxTriangleMesh* VDAPIENTRY genMeshCollision(VDMesh* mesh);

	/**
	 *	Generate a Collision mesh based on MeshHandle Data Description
	 */
	static physx::PxTriangleMesh* VDAPIENTRY genMeshCollision(const HandleMeshEx& meshHandler);

	/**
	 *	Generate Convex Collision Mesh based on Mesh.
	 */
	static physx::PxConvexMesh* VDAPIENTRY genConvexCollision(VDMesh* mesh);

	/**
	 *	Generate Convex Collision Mesh based on HandleMeshEx.
	 */
	static physx::PxConvexMesh* VDAPIENTRY genConvexCollision(const HandleMeshEx& meshHandler);


	/**
	 *
	 */
	static physx::PxClothParticle* VDAPIENTRY genClothParticle(const HandleMeshEx& meshHandler);

	/**
	 *
	 */
	static physx::PxClothFabric* VDAPIENTRY genClothFabric(const HandleMeshEx& meshHandler);

	/**
	 *
	 */
	static physx::PxClothFabric* VDAPIENTRY genClothFabric(VDMesh* mesh);


	/**
	 *
	 */
	static physx::PxParticleSystem* VDAPIENTRY genParticleSystem( unsigned int maxParticleCount);

	/**
	 *
	 */
	static physx::PxParticleFluid* VDAPIENTRY genParticleFluid( unsigned int maxParticleCount);

	/**
	 *
	 *	@Return
	 */
	static int VDAPIENTRY CreateParticle(physx::PxParticleBase* particleBase);


	/**
	 *
	 */
	static physx::PxHeightFieldSample* VDAPIENTRY createHeightFieldSample(VDTerrain* terrain);

	/**
	 *
	 */
	static physx::PxHeightFieldSample* VDAPIENTRY CreateHeightFieldSample(VDMesh* terrain);

	/**
	 *
	 *	@Return
	 */
	static physx::PxHeightField* VDAPIENTRY genHeightCollision(VDTerrain* terrain);




	/**
	 *
	 *	@Return
	 */
	static physx::PxPhysics* VDAPIFASTENTRY getPhysicHandle(void);

	/**
	 *
	 *	@Return
	 */
	static physx::PxScene* VDAPIFASTENTRY getPhysicScene(void);

	/**
	 *
	 *	@Return
	 */
	static physx::PxFoundation* VDAPIFASTENTRY getFoundationHandle(void);

	/**
	 *
	 *	@Return
	 */
	static physx::PxControllerManager* VDAPIFASTENTRY getControllerManager(void);

	/**
	 *
	 *	@Return
	 */
	static physx::PxProfileZoneManager* VDAPIFASTENTRY getProfileZoneManager(void);

	/**
	 *
	 *	@Return
	 */
	static physx::PxVisualDebugger* VDAPIFASTENTRY getVisualDebugger(void);

	/**
	 *	Get PhysX Cuda Context Manager Pointer.
	 *	@Return
	 */
	static physx::PxCudaContextManager* VDAPIFASTENTRY getCudaContextManager(void);

	/**
	 *  convert a Transform To PxTransform Instance.
	 *	makes PX able to accept the content;
	 */
	static physx::PxTransform VDAPIENTRY createPxTransformInstance(const VDTransform* transform);

	/**
	 *	Create a PxTransform Based On Bounds offset. and Quaternion Offset.
	 *	Used for creating a Shape with offset Collision dections based on it's origional Postion Geometry
	 *	[Bounds] Offset Value .
	 *	[Quaternion] Offset In Rotation.
	 */
	static physx::PxTransform VDAPIENTRY createPxTransformInstance(const VDAABB& offset,const VDQuaternion& quaternion = VDQuaternion::identity());

#endif
	VDPhysicEngine *engine;
};
#endif
