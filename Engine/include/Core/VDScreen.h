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
#ifndef _VD_SCREEN_H_
#define _VD_SCREEN_H_ 1
#include"../VDDef.h"
#include"../DataStructure/VDPoint.h"

/**
 *	Get information of current visible screen.
 */
class VDDECLSPEC VDScreen {
public:


	/**
	 *	Get screen size in width.
	 *
	 *	@Return window width in pixel units.
	 */
	static int VDAPIFASTENTRY width(void);

	/**
	 *	Get screen size in height.
	 *
	 *	@Return window height in pixel units.
	 */
	static int VDAPIFASTENTRY height(void);

	/**
	 *	Get screen aspect.
	 *
	 *	@Return ratio.
	 */
	static float VDAPIENTRY aspect(void);

	/**
	 *	Return if application is fullscreen.
	 *
	 *	@Return true if fullscreen. Otherwise not.
	 */
	static bool VDAPIFASTENTRY isFullScreen(void);

	/**
	 *	Set resolution.
	 *
	 *	\width
	 *
	 *	\height
	 *
	 *	\fullscreen
	 */
	static void VDAPIENTRY setResolution(int width, int height, bool fullscreen);

	/**
	 * 	Get view rect.
	 *
	 *	@Return
	 */
	static VDRect VDAPIENTRY getViewRect(void);


	/**
	 *	Set window screen index.
	 *
	 *	@Return
	 */
	static int VDAPIENTRY setScreen(int index);


	/**
	 *	Get screen index.
	 *
	 *	@Return
	 */
	static int VDAPIENTRY getScreenIndex(void);

	/**
	 *	Set window position
	 */
	static void VDAPIENTRY setLocation(int x, int y);

	/**
	 *	Set window position
	 */
	static void VDAPIENTRY setLocation(const VDPoint& point);


	/**
	 *	Get window location.
	 *
	 *	@Return
	 */
	static VDPoint VDAPIENTRY getLocation(void);


	/**
	 *
	 */
	static void VDAPIENTRY setCursorVisability(bool visable);


	/**
	 *
	 *	@Return true if cursoir is visable.
	 */
	static bool VDAPIENTRY isCursorVisible(void);

};

#endif
