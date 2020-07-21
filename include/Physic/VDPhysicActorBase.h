/**
    Copyright (C) 2014  Valdemar Lindberg

    This getProgram() is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This getProgram() is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this getProgram().  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VD_PHYSIC_ACTOR_BASE_H_
#define _VD_PHYSIC_ACTOR_BASE_H_ 1
#include"../Core/VDBehavior.h"
#include"../VDDef.h"

#if defined(VD_INTERNAL) && defined(USE_PHYSX)
	#include<physx/PxPhysicsAPI.h>
#endif

/**
 *	Base class for physic actor part
 *	of the engine scene.
 */
class VDDECLSPEC VDPhysicActor : public VDBehavior{
public:
	VDPhysicActor(void);
	VDPhysicActor(const VDPhysicActor& actor);


	virtual void VDAPIENTRY onEnable(void);
	virtual void VDAPIENTRY onDisable(void);
	virtual void VDAPIENTRY initializeComponent(void);
	virtual void VDAPIENTRY onDestroy(void);

	/*
	 *	is RigidBody Attached to this Gameobject.
	 *
	 *	@Return
	 */
	bool VDAPIFASTENTRY isRigidBodyAttached(void)const;

	/*
	 *	is Collider Attached to this Gameobject.
	 *	@Return
	 */
	bool VDAPIFASTENTRY isColliderAttached(void)const;


	/*
	 *	Get if Actor Connected to this Collider is a Dynamic Actor.
	 *	@Return
	 */
	bool VDAPIFASTENTRY isDynamicRigid(void);

	/*
	 *	Get if Actor Connected to this Collider is a Dynamic Actor.
	 *	@Return
	 */
	bool VDAPIFASTENTRY isStaticRigid(void);

	/*
	 *	initialize the physic Actor.
	 *	@Return
	 */
	bool VDAPIENTRY initVDPhysicObject(bool iscollider, bool isrigidbody);


	/*
	 *	Get Actor of this GameObject. check of actor will be performend
	 *	at Collider & Rigidbody Component.
	 *	@Return
	 */
	void* VDAPIFASTENTRY getActor(void)const;

	/*
	 *
	 */
	void VDAPIENTRY setActor(void* actor);


#if defined(VD_INTERNAL) && defined(USE_PHYSX)

	/*
	 *	actor pointer.
	 */
	physx::PxCloth* VDAPIFASTENTRY getClothActor(void);


	physx::PxParticleBase* VDAPIFASTENTRY GetParticleBaseActor(void);
	physx::PxRigidDynamic* VDAPIFASTENTRY GetDynamicActor(void);
	physx::PxRigidStatic* VDAPIFASTENTRY GetStaticActor(void);

	/*
	 *	Get PxActor as RigidActor.
	 */
	physx::PxRigidActor* VDAPIFASTENTRY GetRigidActor(void);
	physx::PxShape* VDAPIFASTENTRY getShape(unsigned int index = 0);
 	int VDAPIFASTENTRY getShapeCount(void);
	void VDAPIFASTENTRY DetachShape(int index = 0);


	physx::PxGeometryHolder VDAPIFASTENTRY PxGetGeometry(void); 
	physx::PxBoxGeometry VDAPIFASTENTRY PxGetBoxGeometry(void);
	physx::PxCapsuleGeometry VDAPIFASTENTRY PxGetCapsuleGeometry(void);
	physx::PxSphereGeometry VDAPIFASTENTRY PxGetSphereGeometry(void);
	physx::PxGeometryType::unsigned int VDAPIFASTENTRY PxGetGeometryType(void);



	void VDAPIFASTENTRY PxReleaseActor(void);

	void VDAPIENTRY PxShapeVisualization(bool Visualization);
	int VDAPIFASTENTRY PxIsShapeVisualization(void);

	void VDAPIENTRY PxSimulate(bool simulate);

	void VDAPIENTRY PxShapeSimulate(bool shapesimulate);
	void VDAPIENTRY PxShapeSceneQuerty(bool querty);
	void VDAPIENTRY PxShapeDrainParticle(bool drain);

	void VDAPIENTRY PxShapeModifyContact(bool modifyContact);


	void VDAPIENTRY PxSetGlobalPosition(const VDVector3& position);

	VDVector3 VDAPIFASTENTRY PxGetGlobalPosition(void)const;

	void VDAPIENTRY PxSetGlobalRotation(const VDQuaternion& rotation);

	VDQuaternion VDAPIFASTENTRY PxGetGlobalRotation(void)const;


	void VDAPIENTRY PxSetGlobalTransform(VDTransform* transform);
#else

#endif

	union{
#if defined(VD_INTERNAL) && defined(USE_PHYSX)
		physx::PxRigidActor* actor;
#else
		void* actor;
#endif
	};

};

#endif
