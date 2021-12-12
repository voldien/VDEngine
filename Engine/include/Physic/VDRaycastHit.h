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
#ifndef _VD_RAY_CAST_H_
#define _VD_RAY_CAST_H_ 1
#include <Physic/VDCollider.h>
#include <Physic/VDContact.h>
#include"VDSystem.h"
#include"VDSimpleType.h"

/**
 *
 */
class VDDECLSPEC VDRaycastHit{
public:
	VDRaycastHit();
	VDRaycastHit(const VDRaycastHit& hit);

	/**
	 *	Get collider if hitted any.
	 */
	VDCollider* VDAPIFASTENTRY collider()const;

	/**
	 *	Get rigidbody if hitted any.
	 */
	VDRigidBody* VDAPIFASTENTRY rigidBody()const;

	/**
	 *	Get gameobject if hitted any.
	 */
	VDGameObject* VDAPIFASTENTRY gameObject()const;

	/**
	 *	Get gameobjects transform if hitted any.
	 */
	VDTransform* VDAPIFASTENTRY transform()const;

	/**
	 *	Get point in worldspace of the hit.
	 */
	VDVector3 VDAPIFASTENTRY point()const;

	/*
	 *	Get normal surface the ray hit.
	 */
	VDVector3 VDAPIFASTENTRY normal()const;

	/**
	 *	Get distance between the ray caster and point
	 *	hitted.
	 */
	float VDAPIFASTENTRY distance()const;

	/**
	 *	Get barycentric coordinate of the triangle hitted.
	 */
	VDVector2 VDAPIFASTENTRY barycentric()const;


#if defined(VD_INTERNAL) && defined(USE_PHYSX)
	VDRaycastHit(physx::PxRaycastHit& hitdata){
		this->hitdata = hitdata;
	}


#endif

	union{
#if defined(VD_INTERNAL) && defined(USE_PHYSX)
		physx::PxRaycastHit hitdata;
#else
		void* hitdata;
#endif
	};

};


#endif
