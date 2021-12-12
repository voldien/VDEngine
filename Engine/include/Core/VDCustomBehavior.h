/*
 *	VDEngine virtual dimension game engine.
 *	Copyright (C) 2014  Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _VD_CUSTOMBEHAVIOR_H_
#define _VD_CUSTOMBEHAVIOR_H_ 1
#include "../VDDef.h"
#include "VDBehavior.h"

/**
 *	Class for adding custom behavior
 *	to gameobjects.
 */
class VDDECLSPEC VDCustomBehavior : public VDBehavior {
  public:
	VDCustomBehavior();
	VDCustomBehavior(const VDCustomBehavior &brood);

	/**
	 *	CallBack when object has been created.
	 */
	virtual void VDAPIENTRY onAwake();

	/**
	 *	Update callBack function. Call Every Frame.
	 */
	virtual void VDAPIENTRY update();

	/**
	 *	Fixed update.
	 */
	virtual void VDAPIENTRY fixedUpdate();

	/**
	 *	Update callback function. callback when
	 *	all update callback.
	 */
	virtual void VDAPIENTRY lateUpdate();

	/**
	 *	Event when GUI is being rendered.
	 */
	virtual void VDAPIENTRY onGUI();

	/**
	 *	On CharacterController Hit CallBack.
	 */
	virtual void VDAPIENTRY onCharacterController(const VDCharacterControllerHit &hit);

	/**
	 *	On Collision Enter Hit CallBack.
	 */
	virtual void VDAPIENTRY onCollisionEnter(const VDCollision &collision);

	/**
	 *	On Collision Exit CallBack
	 */
	virtual void VDAPIENTRY onCollisionExit(const VDCollision &collision);

	/**
	 *	On Collision Stay.
	 */
	virtual void VDAPIENTRY onCollisionStay(const VDCollision &collision);

	/**
	 *	On Trigger Enter Callback event
	 */
	virtual void VDAPIENTRY onTriggerEnter(VDCollider *collider);

	/**
	 *	Event when a trigger collider exists.
	 */
	virtual void VDAPIENTRY onTriggerExit(VDCollider *collider);

	/**
	 *	Event when joint breaks.
	 */
	virtual void VDAPIENTRY onJointBreak(float breakForce);

	/*
	 *	On Renderer Behavior Disable CallBack Event.
	 */
	virtual void VDAPIENTRY onBecameInvisible();

	/**
	 *	On Renderer Behavior Enable CallBack Event.
	 */
	virtual void VDAPIENTRY onBecameVisible();

	/**
	 *	On GameObject Determined to Rendered
	 */
	virtual void VDAPIENTRY onPreCulled();

	/**
	 *	Initialize the component.
	 */
	virtual void VDAPIENTRY initializeComponent() override;

	/**
	 *	Copy behavior object.
	 */
	virtual VDBehavior *VDAPIENTRY copyComponent(unsigned int &dataSize) override;
};
#endif
