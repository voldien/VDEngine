/**
    Copyright (C) 2014  Valdemar Lindberg

    This getProgram() is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This getProgram() is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this getProgram().  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VD_INPUT_H_
#define _VD_INPUT_H_ 1
#include "../VDDef.h"
#include "../VDSimpleType.h"
#include <SDL2/SDL_keycode.h>

/**
 *
 */
class VDDECLSPEC VDInput {
public:
	typedef struct axis_input{

	}AxisInput;

	enum Button{
		Left 	= 0x1,
		Right 	= 0x2,
		Middle = 0x4
	};

	enum {
		Vertical 	= 0x2000,				// Movement of Controller[keyboard, XBoxController Joystict. etc]
		Horizontal 	= 0x4000,			// Movement of Controller[keyboard, XBoxController Joystict. etc]
		CAMERA_X 	= 0x8000,				// Camera Movement In X [Mouse Movement, XBoxController Left JoyStick, X
		CAMERA_Y 	= 0x10000,			// Camera Movement In Y [Mouse Movement, XBoxController Left
		Jump 		= 0x20000,
		Fire1 		= 0x40000,
		Fire2 		= 0x80000,
		Fire3 		= 0x100000
	};

	/**
	 *
	 */
	static void VDAPIENTRY getAccelerationEvent(void);

	/**
	 *	Get Axis
	 */
	static float VDAPIENTRY getAxis(unsigned int axisFlag);

	/**
	 *
	 */
	static float VDAPIENTRY getAxis(char* axisFlag);

	/*
	 *
	 */
	static float VDAPIENTRY getAxisRaw(unsigned int axisFlag);

	/*
	 *
	 */
	static int VDAPIENTRY getTouch(void);

	/**
	 *
	 */
	static VDPoint VDAPIENTRY location(void);

	/**
	 *	Get mouse position relative to the monitor
	 *
	 *	@Return mouse position.
	 */
	static VDPoint VDAPIENTRY mousePosition(void);

	/**
	 *
	 */
	static int VDAPIFASTENTRY x(void);

	/**
	 *
	 */
	static int VDAPIFASTENTRY y(void);

	/**
	 *	@Return
	 */
	static int VDAPIFASTENTRY deltaX(void);

	/**
	 *
	 */
	static int VDAPIFASTENTRY deltaY(void);

	/**
	 *
	 */
	static VDVector2 VDAPIENTRY getMotion(void);


	/**
	 *	@Return
	 */
	static int VDAPIFASTENTRY isKeyDown(SDL_Keycode keyCode);

	/**
	 *	@Return
	 */
	static int VDAPIFASTENTRY isKeyUp(SDL_Keycode keyCode);

	/**
	 *	@Return
	 */
	static int VDAPIFASTENTRY isKey(SDL_Keycode keyCode);

	/*
	 *
	 *	@Return
	 */
	static int VDAPIFASTENTRY getButton(VDInput::Button button);

	/**
	 *	@Return
	 */
	static int VDAPIFASTENTRY getButtonDown(VDInput::Button button);

	/**
	 *	@Return
	 */
	static int VDAPIFASTENTRY getButtonUp(VDInput::Button button);


	/*
	 *	@Return
	 */
	static int VDAPIENTRY resetInputAxis(void);

	/*	TODO Add input settings */

	/**
	 *	Update input.
	 */
	static void VDAPIENTRY internal_update(void);
};

#endif
