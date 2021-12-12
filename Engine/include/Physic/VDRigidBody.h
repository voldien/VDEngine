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
#include<physic/RigidBody.h>
#include"VDPhysicActorBase.h"

/**
 *
 */
class VDDECLSPEC VDRigidBody : public VDPhysicActor {
public:

	enum Mode{
		Discret 	= 0x1,	/*	*/
		CCD 		= 0x2,	/*	*/
	};
	fragcore::RigidBody* m_rigidBody;

	VDRigidBody();
	VDRigidBody(const VDRigidBody& rigidbody);

	virtual void VDAPIENTRY instanceInitilize();
	virtual void VDAPIENTRY onEnable();
	virtual void VDAPIENTRY onDisable();
	virtual void VDAPIENTRY initializeComponent();
	virtual void VDAPIENTRY onDestroy();
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);

	/**
	 *
	 */
	void VDAPIENTRY addExplosionForce(float force, VDVector3& position, float Radius) {

	}

	/**
	 *	Apply Force as A Vector. which takes the magnitude as
	 *	force and direction of the vector direction.
	 */
	void VDAPIENTRY addForce(const VDVector3& force) {
		this->m_rigidBody->addForce(force);
	}

	/**
	 *
	 */
	void VDAPIENTRY addForce(float x, float y, float z) {
		this->m_rigidBody->addForce(VDVector3(x, y, z));
	}

	/**
	 *
	 */
	void VDAPIENTRY addForceAtPosition(const VDVector3& force,const VDVector3& position) {
		this->m_rigidBody->addForce(force);
	}

	/**
	 *
	 */
	void VDAPIENTRY addRelativeForce(const VDVector3& force) {
		this->m_rigidBody->addForce(force);
	}

	/**
	 *
	 */
	void VDAPIENTRY addRelativeTorque(const VDVector3& force) {
		this->m_rigidBody->addForce(force);
	}

	/**
	 *
	 */
	void VDAPIENTRY addTorque(const VDVector3& force){
		this->m_rigidBody->addForce(force);
	}

	/**
	 *
	 */
	void VDAPIFASTENTRY setCollisioMode(unsigned int state){

	}

	/**
	 *
	 */
	void VDAPIENTRY setMass(float mass) {
		this->m_rigidBody->setMass(mass);
	}

	/**
	 *
	 */
	float VDAPIFASTENTRY getMass()const{
		return this->m_rigidBody->getMass();
	}

	/**
	 *
	 */
	void VDAPIENTRY setDrag(float drag){
		this->m_rigidBody->setDrag(drag);
	}

	/**
	 *
	 */
	float VDAPIFASTENTRY getDrag()const{
		this->m_rigidBody->getDrag();
	}

	/**
	 *
	 */
	void VDAPIENTRY setAngularDrag(float angularDrag){
		this->m_rigidBody->setAngularDrag(angularDrag);
	}

	/**
	 *
	 */
	float VDAPIFASTENTRY getAngularDrag()const{
		this->m_rigidBody->getAngularDrag();
	}

	/**
	 *
	 */
	int VDAPIENTRY isSleeping()const{

	}

	/**
	 *
	 */
	void VDAPIFASTENTRY sleep(){

	}

	/**
	 *
	 */
	void VDAPIFASTENTRY wake(){

	}

	/**
	 *
	 */
	void VDAPIENTRY useGraivity(bool useGravity){

	}

	/**
	 *
	 */
	void VDAPIENTRY kinect(bool kinect){

	}

	/**
	 *
	 */
	void VDAPIFASTENTRY enableCCD(){

	}

	/**
	 *
	 */
	void VDAPIFASTENTRY disableCCD(){
		
	}

};

#endif
