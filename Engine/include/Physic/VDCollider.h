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
#ifndef _VD_COLLIDER_H_
#define _VD_COLLIDER_H_ 1
#include"../Core/VDShape.h"
#include"VDPhysicActorBase.h"
/**
 *	Base class for Collider object.
 */
class VDDECLSPEC VDCollider : public VDPhysicActor, public VDShape{
public:
	 enum CollisionType{
		eUnknown 			= 0x0,		/*	*/
		ePlane 				= 0x1,		/*	*/
		eBox 				= 0x2,		/*	*/
		eSphere 			= 0x3,		/*	*/
		eCylinder 			= 0x4,		/*	*/
		eCapsule 			= 0x5,		/*	*/
		eMesh 				= 0x6,		/*	*/
		eWheel 				= 0x7,		/*	*/
		eTerrain 			= 0x8,		/*	*/
		eConvex 			= 0x9,		/*	*/
		eCharacterController = 0xA,		/*	*/
		eOnTriggerEnter,				/*	*/
		eOnTriggerExit,					/*	*/
		eOnTriggerStay,					/*	*/
		eRigidBody = 0x20,				/*	*/
		eRigidBodyDynamic = 0x40,		/*	*/
		eAddedActor = 0x80,				/*	*/
		eIsTrigged = 0x100,				/*	*/
		eIsShape = 0x200,				/*	*/
	};

	VDCollider(void);
	VDCollider(const VDCollider& collider);
	VDCollider(CollisionType collisionType);


	virtual void VDAPIENTRY instanceInitilize(void);
	virtual void VDAPIENTRY onEnable(void);
	virtual void VDAPIENTRY onDisable(void);
	virtual void VDAPIENTRY initializeComponent(void);
	virtual void VDAPIENTRY onDestroy(void);
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);

	/**
	 *	Set collider actor to be triggered or non.
	 *	Triggered actor will not be effected by collision. Rather
	 *	information about collision will only be sent.
	 */
	void VDAPIENTRY isTrigger(bool trigger);

	/*
	 *	Set VDPhysic Material to Collider.
	 */
	void VDAPIENTRY setMaterial(const VDPhysicMaterial* material);

	/**
	 *	Get Reference To VDPhysicMaterial.
	 *
	 *	@Return
	 */
	VDPhysicMaterial VDAPIFASTENTRY getMaterial(void)const;

	/**
	 *	Get collider type.
	 *
	 *	@Return
	 */
	CollisionType VDAPIFASTENTRY getColliderType(void)const;


	/**
	 *	Get collider shape center value.
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY getCenter(void)const;

	/**
	 *	Set Center Value of the Shape.
	 */
	void VDAPIENTRY setCenter(const VDVector3& center);


	VDCollider& operator=(const VDCollider& collider);

private:	/*	Attributes.	*/

	CollisionType type;		/*	collision type.	*/

private:
	/*
	 *	Set reference of this in Collider
	 *	return true if shape was found and assign
	 */
	int VDAPIENTRY setReferenceOnActor(void);
	void VDAPIENTRY initCollision(void);

};

extern VDDECLSPEC std::vector<VDCollider*> colliderCollection;

#endif
