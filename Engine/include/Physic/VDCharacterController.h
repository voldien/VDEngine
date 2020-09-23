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
#ifndef _VD_CHARACTER_CONTROLLER_H_
#define _VD_CHARACTER_CONTROLLER_H_ 1
#include <Physic/VDCharacterControllerHit.h>
#include <Physic/VDCollider.h>

enum CharacterControllerHit{
	eCOLLISION_SIDES	= (1<<0),	//!< Character is colliding to the sides.
	eCOLLISION_UP		= (1<<1),	//!< Character has collision above.
	eCOLLISION_DOWN		= (1<<2),	//!< Character has collision below.
};

#define COLLISION_SIDE CharacterControllerHitunsigned int::eCOLLISION_SIDES
#define COLLISION_UP CharacterControllerHitunsigned int::eCOLLISION_UP
#define COLLISION_DOWN CharacterControllerHitunsigned int::eCOLLISION_DOWN
#define CHARACTER_SHAPE_CAPSULE CharacterController::eCapsuleCharacter
#define CHARACTER_SHAPE_BOX CharacterController::eBoxCharacter


/**
 *
 */
class VDDECLSPEC VDCharacterController : public VDCollider{
public:
	enum CharacterType{
		eCapsuleCharacter = 0x1,
		eBoxCharacter = 0x2,
	};
	VDCharacterController(void);
	VDCharacterController(VDCharacterController& controller);

	virtual void VDAPIENTRY instanceInitilize(void);
	virtual void VDAPIENTRY onEnable(void);
	virtual void VDAPIENTRY onDisable(void);
	virtual void VDAPIENTRY initializeComponent(void);
	virtual void VDAPIENTRY onDestroy(void);
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);

	/**
	 *
	 *	@Return
	 */
	int VDAPIENTRY setShape(CharacterType type);

	/**
	 *
	 *	@Return
	 */
	CharacterType VDAPIENTRY getShapeType(void)const;

	/**
	 *
	 *	@Return
	 */
	unsigned int VDAPIENTRY getCollisionFlag(void)const;

	/*
	 *
	 *	@Return
	 */
	int VDAPIENTRY move(const VDVector3& motion);


	/*
	 *
	 */
	void VDAPIENTRY setMinMove(float movement);

	/*
	 *
	 *	@Return
	 */
	float VDAPIFASTENTRY getMinMove(void)const;


	/*
	 *
	 */
	void VDAPIENTRY setRadius(float radius);

	/*
	 *
	 */
	float VDAPIFASTENTRY getRadius(void)const;

	/*
	 *
	 */
	float VDAPIFASTENTRY getHeight(void)const;

	/*
	 *
	 */
	void VDAPIENTRY setHeight(float height);


private:	/*	Attributes.	*/
	float mindistance;

#if defined(VD_INTERNAL) && defined(USE_PHYSX)
	physx::PxController* controller;
#else
	void* controller;
#endif

	
};

#endif
