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
#ifndef _VD_BEHAVIOR_H_
#define _VD_BEHAVIOR_H_ 1
#include "VDComponent.h"
#include "../VDDef.h"

/**
 *	Base class for enable behavior for
 *	attachable components for gameobjects.
 */
class VDDECLSPEC VDBehavior : public VDComponent{
public:

	enum State{
		eEnable 			= 0x1,	/*	*/
		eBehavior			= 0x2,	/*	*/
		eCustomBehavior 	= 0x4,	/*	*/
		eRigidbodyActor 	= 0x8,	/*	*/
		eColliderTrigger 	= 0x10,	/*	*/
		eColliderShape 		= 0x20,	/*	*/
	};

	VDBehavior(void);
	~VDBehavior(void);

	/**
	 *	Enable behavior.
	 */
	void VDAPIFASTENTRY enable(void);

	/**
	 *	Disable behavior.
	 */
	void VDAPIFASTENTRY disable(void);

	/**
	 *	Check if disabled.
	 */
	bool VDAPIFASTENTRY isDisabled(void)const;

	/**
	 *	Check if enabled.
	 */
	bool VDAPIFASTENTRY isEnabled(void)const;

	/**
	 *	Set Componet Enable State. OnEnable or OnDisable
	 *	Will be read Depending on Componets enable value
	 *	end Result.
	 */
	void VDAPIFASTENTRY setState(unsigned int state);

	/**
	 *	Get state flag.
	 */
	unsigned int VDAPIFASTENTRY getState(void)const;

	/**
	 *	overridable initialize Component. Will Be
	 *	Read When calling GameObject->addComponet(float).
	 *	Don't Call this Method as long you know what
	 *	it does in and out.
	 */
	virtual void VDAPIENTRY initializeComponent(void);
	

	/**
	 *	Overridable void Method On Destrution of
	 *	Object. Method will be called while Destukor
	 *	In Action.
	 */
	virtual void VDAPIENTRY onDestroy(void);

	/**
	 *	Overridable void Method On Component Enable
	 *	Method will be read on Its Enableable.
	 *	Useful method to switch variable on Enable Changes.
	 */
	virtual void VDAPIENTRY onEnable(void);

	/**
	 *	Overriable void Method On Component Disable.
	 *	Method will be read on Itd Disable
	 *	Useful method to switch variable on Disable Changes
	 */
	virtual void VDAPIENTRY onDisable(void);

	/**
	 *	Event when behavior has been detached.
	 */
	virtual void VDAPIENTRY onDetach(void);

	/**
	 *	Overriable void Method. On Debug in ViewPort
	 *	Method will run when debug is enable.
	 *
	 *	[Note]
	 */
	virtual void VDAPIENTRY onDebugDisplay(void);


	/**
	 *	Overriable Behavior Method. Create a copy
	 *	of ParentClass.
	 *	[dataSize] returns a size of ParentClass.
	 *	Behavior copy can be cast to float parent class
	 *	to Get Scope of all Data.
	 *	@Return
	 */
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);


	/**
	 *	Overriable Behavior Method. Initilize of
	 *	Instance of Origional Data. Used for
	 *	Treating the Data differently.
	 */
	virtual void VDAPIENTRY instanceInitilize(void);


	/**
	 *	Event on pre render of object.
	 */
	virtual void VDAPIENTRY onPreRender(void);

	/**
	 *	Event on reset.
	 */
	virtual void VDAPIENTRY reset(void);

	/**
	 *	Event when application gets focused.
	 */
	virtual void VDAPIENTRY onApplicationFocus(void);

	/**
	 *	Event when application gets unfocused.
	 */
	virtual void VDAPIENTRY onApplicationUnFocus(void);

	/**
	 *	Event when application gets before quiting.
	 */
	virtual void VDAPIENTRY onApplicationQuit(void);

	/**
	 *	Event when application gets paused.
	 */
	virtual void VDAPIENTRY onApplicationPause(void);

	/**
	 *
	 */
	VDBehavior& operator=(const VDBehavior& behavior);

	/**
	 *	Get custom behavior.
	 */
	VDCustomBehavior* VDAPIFASTENTRY getCustomBehavior(void);

	/**
	 *	Check if is a behavior.
	 */
	int VDAPIFASTENTRY isBehavior(void)const;

	/**
	 *	Check if a custom behvior.
	 */
	int VDAPIFASTENTRY isCustomBehavior(void)const;

protected:

	/**
	 *
	 */
	void VDAPIFASTENTRY setVTable(const void* data);

	/**
	 *
	 */
	const void* VDAPIFASTENTRY getVTable(void)const;


protected:	/*	Attributes.	*/

	unsigned int menable;
};

#endif
