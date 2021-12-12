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
#ifndef _VD_COLLISION_H_
#define _VD_COLLISION_H_ 1
#include"VDCollider.h"

/**
 *	Collision object, responsible for containing
 *	data assoicated with the collision.
 */
class VDDECLSPEC VDCollision{
public:

	VDCollision();
	VDCollision(const VDCollision& collision);

	/**
	 *	Get collider object.
	 */
	VDCollider*  VDAPIENTRY collider()const;

	/**
	 *	Get relative velocity magnitude.
	 */
	float VDAPIENTRY relativeVelocity()const;

	/**
	 *	Get transform object.
	 */
	VDTransform* VDAPIENTRY transform()const;

	/**
	 *	Get gameobject.
	 */
	VDGameObject* VDAPIENTRY gameObject()const;

	/**
	 *	Get rigidbodt object.
	 */
	VDRigidBody* VDAPIENTRY rigidBody()const;

	/**
	 *	Get contact.
	 */
	VDContact VDAPIENTRY contacts()const;

private:	/*	Attributes.	*/

	void* pair;
	void* shape;
};

#endif
