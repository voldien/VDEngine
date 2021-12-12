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
#ifndef _VD_COMPONENT_H_
#define _VD_COMPONENT_H_ 1
#include "../VDDef.h"
#include "../VDPrerequisites.h"
#include "../VDSimpleType.h"
#include "VDObject.h"
#include "VDTypes.h"

/**
 * @brief Base class for behaviors.
 *
 */
class VDDECLSPEC VDComponent : public VDObject { // TOOD add non copyable
	friend class VDGameObject;

  protected:
	VDComponent() = default;
	VDComponent(const VDComponent &other) = delete;
	virtual ~VDComponent();

  private:					   /*	Attributes.	*/
	VDGameObject *pgameObject; /*	Component pointer to the gameobject connected to.	*/

  public: /*	Public methods.	*/
	VDComponent &operator=(const VDComponent &rh) = delete;
	bool operator==(const VDComponent *lh) const; /*	Componets Equal Operator	*/
	bool operator!=(const VDComponent *lh) const; /* Componets Not Equal Operator	*/

	/**
	 *	Get animation.
	 */
	VDAnimation *VDAPIENTRY animation();

	/**
	 *	Get transformation.
	 */
	VDTransform *VDAPIENTRY transform() const;

	/**
	 *	Get camera.
	 */
	VDCamera *VDAPIENTRY camera();

	/**
	 *	Get renderer.
	 */
	VDRenderer *VDAPIENTRY renderer();

	/**
	 *	Get gameobject assoicated with the component.
	 */
	VDGameObject *VDAPIENTRY gameObject() const;

	/**
	 *	Get audio source component from gameobject.
	 */
	VDAudioSource *VDAPIENTRY audio();

	/**
	 *	Get light component from gameobject.
	 */
	VDLight *VDAPIENTRY light();

	/**
	 *	Get rigidbody component from gameobject.
	 */
	VDRigidBody *VDAPIENTRY rigidBody();

	/**
	 *	Get collider component from gameobject.
	 */
	VDCollider *VDAPIENTRY collider();

	/**
	 *	Check if component of type exists
	 *	in gameobject.
	 */
	bool VDAPIENTRY existComponet(const VDTypeInfo &info);

	/**
	 *	Check if object is of type.
	 */
	template <class T> inline bool is() const { return this->existComponet(VDTypeInfo::getType<T>()); }

	/**
	 *	Cast object to any type.
	 */
	template <class T> inline T *cast() const { return (T *)this; }

	/**
	 *	Instantiate this GameObject.
	 *	@Return non-null identical object.
	 */
	VDGameObject *VDAPIENTRY instantiate();

	/**
	 *	Instantiate this GameObject.
	 *	@Return non-null identical object.
	 */
	VDGameObject *VDAPIENTRY instantiate(const VDVector3 &position, const VDQuaternion &rotation);

	/**
	 *	Get component if exists.
	 */
	template <class T> inline T *getComponent() { return (T *)getComponent(VDTypeInfo::getType<T>()); }

	/**
	 *	@Return non null pointer of object is successfully.
	 */
	void *VDAPIFASTENTRY getComponent(const VDTypeInfo &info);

  protected:
	/**
	 *	Set gameobject reference, for the gameobject
	 *	the component is attached to.
	 */
	void VDAPIFASTENTRY setGameObject(VDGameObject *gameobject);

  public: /*	Static methods.	*/
	/**
	 *	Destroy game object.
	 */
	static void VDAPIENTRY destroy(VDGameObject *gameObject);
};

#endif
