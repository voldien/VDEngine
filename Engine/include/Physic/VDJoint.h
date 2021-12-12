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
#ifndef _VD_JOINT_H_
#define _VD_JOINT_H_ 1
#include"VDPhysic.h"
#include"../Core/VDBehavior.h"

/**
 *
 */
class VDDECLSPEC VDJoint : public VDPhysicActor{
public:
	VDJoint();
	VDJoint(const VDJoint& joint);
	VDJoint(VDRigidBody* rigidbody);

	virtual void instanceInitilize();
	virtual void onEnable();
	virtual void onDisable();
	virtual void initializeComponent();
	virtual void onDestroy();
	virtual VDBehavior* copyComponent(unsigned int& dataSize);

	/**
	 *
	 */
	void VDAPIENTRY attachJoint(VDRigidBody* object);

	/**
	 *
	 */
	void VDAPIENTRY Break();

	/**
	 *
	 */
	VDVector3 VDAPIENTRY getRelativeAngularVelocity()const;

	/**
	 *
	 */
	VDVector3 VDAPIENTRY getRelativeLinearVelocity()const;


	/**
	 *
	 */
	void VDAPIENTRY setBreakForce(float force, float torque);

	/**
	 *
	 */
	void VDAPIENTRY getBreakForce(float* force, float* torque);

	/**
	 *	@Return
	 */
	VDRigidBody* VDAPIENTRY getAttachedRigidBody()const;

protected:

	union{
#if defined(VD_INTERNAL) && defined(USE_PHYSX)
		physx::PxJoint* joint;
#else
		void* joint;
#endif
	};

#if defined(VD_INTERNAL) && defined(USE_PHYSX)
	inline physx::PxDistanceJoint* VDAPIENTRY pxGetDistanceJoint(){return VDCASTP(physx::PxDistanceJoint*,this->joint);}
	inline physx::PxFixedJoint* VDAPIENTRY pxGetFixedJoint(){return VDCASTP(physx::PxFixedJoint*, this->joint);}
	//INLINE physx::PxDistanceJoint* VDAPIENTRY pxGetDistanceJoint(){return CASTP(physx::PxDistanceJoint*,this->joint);}
#endif

	/**
	 *
	 */
	VDFixedJoint* isFixedJoint();
	/**
	 *
	 */
	VDSpringJoint* isSpringJoint();
	/**
	 *
	 */
	VDRevoluteJoint* isRevoluteJoint();

};
#endif
