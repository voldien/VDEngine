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
#ifndef _VD_CHARACTER_CONTROLLER_HIT_
#define _VD_CHARACTER_CONTROLLER_HIT_ 1
#include"VDCollider.h"
#include"../VDSimpleType.h"

/**
 *
 */
class VDDECLSPEC VDCharacterControllerHit{
public:
	VDCharacterControllerHit(void);
	VDCharacterControllerHit(const VDCharacterControllerHit& hit);
	VDCharacterControllerHit(const void* hit);

	/**
	 *
	 *	@Return
	 */
	VDCollider* VDAPIFASTENTRY collider(void);

	/**
	 *
	 *	@Return
	 */
	VDRigidBody* VDAPIFASTENTRY rigidBody(void);

	/**
	 *
	 *	@Return
	 */
	VDTransform* VDAPIFASTENTRY transform(void);

	/**
	 *
	 *	@Return
	 */
	VDGameObject* VDAPIFASTENTRY gameObject(void);

	/**
	 *
	 *	@Return
	 */
	VDCharacterController* VDAPIFASTENTRY controller(void);

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY point(void)const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY normal(void)const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY moveDirection(void)const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY moveLength(void)const;

private:	/*	Attributes.	*/

	union{
		void* data;
	};

};

#endif
