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
	VDCharacterControllerHit();
	VDCharacterControllerHit(const VDCharacterControllerHit& hit);
	VDCharacterControllerHit(const void* hit);

	/**
	 *
	 *	@Return
	 */
	VDCollider* VDAPIFASTENTRY collider();

	/**
	 *
	 *	@Return
	 */
	VDRigidBody* VDAPIFASTENTRY rigidBody();

	/**
	 *
	 *	@Return
	 */
	VDTransform* VDAPIFASTENTRY transform();

	/**
	 *
	 *	@Return
	 */
	VDGameObject* VDAPIFASTENTRY gameObject();

	/**
	 *
	 *	@Return
	 */
	VDCharacterController* VDAPIFASTENTRY controller();

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY point()const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY normal()const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY moveDirection()const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY moveLength()const;

private:	/*	Attributes.	*/

	union{
		void* data;
	};

};

#endif
