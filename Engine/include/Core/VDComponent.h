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
#ifndef _VD_COMPONENT_H_
#define _VD_COMPONENT_H_ 1
#include"../VDDef.h"
#include"VDTypes.h"
#include"VDObject.h"

/**
 *	Base class for behaviors.
 */
class VDDECLSPEC VDComponent : public VDObject {//TOOD add non copyable
	friend class VDGameObject;
protected:
	VDComponent(void);
	VDComponent(const VDComponent& other) = default;
	virtual ~VDComponent(void);

private:	/*	Attributes.	*/

	VDGameObject* pgameObject;	/*	Component pointer to the gameobject connected to.	*/

public:	/*	Public methods.	*/

	VDComponent& operator=(const VDComponent& rh);
	bool operator==(const VDComponent* lh)const; 		/*	Componets Equal Operator	*/
	bool operator!=(const VDComponent* lh)const; 		/* Componets Not Equal Operator	*/


	/**
	 *	Get animation.
	 */
	VDAnimation* VDAPIFASTENTRY animation(void);

	/**
	 *	Get transformation.
	 */
	VDTransform* VDAPIFASTENTRY transform(void)const;

	/**
	 *	Get camera.
	 */
	VDCamera* VDAPIFASTENTRY camera(void);

	/**
	 *	Get renderer.
	 */
	VDRenderer* VDAPIFASTENTRY renderer(void);

	/**
	 *	Get gameobject assoicated with the component.
	 */
	VDGameObject* VDAPIFASTENTRY gameObject(void)const;

	/**
	 *	Get audio source component from gameobject.
	 */
	VDAudioSource* VDAPIFASTENTRY audio(void);

	/**
	 *	Get light component from gameobject.
	 */
	VDLight* VDAPIFASTENTRY light(void);

	/**
	 *	Get rigidbody component from gameobject.
	 */
	VDRigidBody* VDAPIFASTENTRY rigidBody(void);

	/**
	 *	Get collider component from gameobject.
	 */
	VDCollider* VDAPIFASTENTRY collider(void);

	/**
	 *	Check if component of type exists
	 *	in gameobject.
	 */
	bool VDAPIFASTENTRY existComponet(const VDTypeInfo& info);

	/**
	 *	Check if object is of type.
	 */
	template<class T>
	inline bool is(void) const {
		return this->existComponet(VDTypeInfo::getType<T>());
	}

	/**
	 *	Cast object to any type.
	 */
	template<class T>
	inline T* cast(void) const {
		return (T*)this;
	}

	/**
	 *	Instantiate this GameObject.
	 *	@Return non-null identical object.
	 */
	VDGameObject* VDAPIENTRY instantiate(void);

	/**
	 *	Instantiate this GameObject.
	 *	@Return non-null identical object.
	 */
	VDGameObject* VDAPIENTRY instantiate(const VDVector3& position, const VDQuaternion& rotation);

	/**
	 *	Get component if exists.
	 */
	template<class T>
	inline T* getComponent(void) {
		return (T*)getComponent(VDTypeInfo::getType<T>());
	}

	/**
	 *	@Return non null pointer of object is successfully.
	 */
	void* VDAPIFASTENTRY getComponent(const VDTypeInfo& info );

protected:

	/**
	 *	Set gameobject reference, for the gameobject
	 *	the component is attached to.
	 */
	void VDAPIFASTENTRY setGameObject(VDGameObject* gameobject);

public:	/*	Static methods.	*/

	/**
	 *	Destroy game object.
	 */
	static void VDAPIENTRY destroy(VDGameObject* gameObject);

};

#endif
