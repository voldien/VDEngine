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
#ifndef _VD_RIGIDBODY_H_
#define _VD_RIGIDBODY_H_ 1
#include"VDPhysicActorBase.h"

/**
 *
 */
class VDDECLSPEC VDRigidBody : public VDPhysicActor{
public:

	enum Mode{
		eDiscret 	= 0x1,	/*	*/
		eCCD 		= 0x2,	/*	*/
	};

	VDRigidBody(void);
	VDRigidBody(const VDRigidBody& rigidbody);

	virtual void VDAPIENTRY instanceInitilize(void);
	virtual void VDAPIENTRY onEnable(void);
	virtual void VDAPIENTRY onDisable(void);
	virtual void VDAPIENTRY initializeComponent(void);
	virtual void VDAPIENTRY onDestroy(void);
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);

	/**
	 *
	 */
	void VDAPIENTRY addExplosionForce(float force, VDVector3& position, float Radius);

	/**
	 *	Apply Force as A Vector. which takes the magnitude as
	 *	force and direction of the vector direction.
	 */
	void VDAPIENTRY addForce(const VDVector3& force);

	/**
	 *
	 */
	void VDAPIENTRY addForce(float x, float y, float z);

	/**
	 *
	 */
	void VDAPIENTRY addForceAtPosition(const VDVector3& force,const VDVector3& position);

	/**
	 *
	 */
	void VDAPIENTRY addRelativeForce(const VDVector3& force);

	/**
	 *
	 */
	void VDAPIENTRY addRelativeTorque(const VDVector3& force);

	/**
	 *
	 */
	void VDAPIENTRY addTorque(const VDVector3& force);

	/**
	 *
	 */
	void VDAPIFASTENTRY setCollisioMode(unsigned int state);

	/**
	 *
	 */
	void VDAPIENTRY setMass(float mass);

	/**
	 *
	 */
	float VDAPIFASTENTRY getMass(void)const;

	/**
	 *
	 */
	void VDAPIENTRY setDrag(float drag);

	/**
	 *
	 */
	float VDAPIFASTENTRY getDrag(void)const;

	/**
	 *
	 */
	void VDAPIENTRY setAngularDrag(float angularDrag);

	/**
	 *
	 */
	float VDAPIFASTENTRY getAngularDrag(void)const;

	/**
	 *
	 */
	int VDAPIENTRY isSleeping(void)const;

	/**
	 *
	 */
	void VDAPIFASTENTRY sleep(void);

	/**
	 *
	 */
	void VDAPIFASTENTRY wake(void);

	/**
	 *
	 */
	void VDAPIENTRY useGraivity(bool useGravity);

	/**
	 *
	 */
	void VDAPIENTRY kinect(bool kinect);

	/**
	 *
	 */
	void VDAPIFASTENTRY enableCCD(void);

	/**
	 *
	 */
	void VDAPIFASTENTRY disableCCD(void);

};

#endif
