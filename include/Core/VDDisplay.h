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
#ifndef _VD_DISPLAY_H_
#define _VD_DISPLAY_H_ 1
#include"../VDSystem.h"

/**
 *	Class for getting information about the displays.
 */
class VDDECLSPEC VDDisplay{
public:

	/**
	 *
	 */
	typedef struct vd_resolution_t{
		int x;				/*	Screen x position in pixels.	*/
		int y;				/*	Screen y position in pixels.*/
		int width;			/*	screen width in pixels*/
		int height;			/*	Screen height in pixels*/
		int refereshRate;	/*	Refresh rate in Hz.*/
		int displayIndex;	/*	Display index.	*/
	}Resolution;


	/**
	 *	Get number of display present.
	 *
	 *	@Return number of displays.
	 */
	static int VDAPIENTRY getNumDisplays(void);

	/**
	 *	Get all possible resolution configuration for primary screen.
	 */
	static void VDAPIENTRY getPrimaryScreenResolutions(int* num, Resolution** resolutions);

	/**
	 *	Get all possible resolution configuration for display by its index.
	 */
	static void VDAPIENTRY getScreenResolutions(int index, int* num, Resolution** resolutions);


	/**
	 *	Get Primary screen resolution.
	 *
	 *	@Return size in pixels.
	 */
	static VDSize VDAPIENTRY getPrimaryScreenSize(void);

};

#endif
