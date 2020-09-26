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
#ifndef _VD_CONFIG_H_
#define _VD_CONFIG_H_ 1
#include"../VDDef.h"
#include<Core/IConfig.h>

/**
 *
 */
class VDDECLSPEC VDConfigure : public fragcore::IConfig {
public:

	/**
	 *
	 */
	typedef struct vd_config{
		/*	*/
		unsigned int ntaskcores;
		unsigned int debug;

		/*	default screen.	*/
		unsigned int width;
		unsigned int height;
		unsigned int dps;
		unsigned int resizable;
		unsigned int fullscreen;


		/*	rendering.	*/
		unsigned int glversion;
		unsigned int glprofile;
		unsigned int renderingapi;

		/*	*/
		unsigned int verbose;
		unsigned int inotify;

		/*	graphic behavior.	*/
		unsigned int graphicbackground;

		/*	input.	*/
		unsigned int keyfetchbackground;
	}VDConfig;

	/**
	 *	Generate default config.
	 */
	static void VDAPIENTRY defaultConfig(VDConfig* config);
};

#endif 
