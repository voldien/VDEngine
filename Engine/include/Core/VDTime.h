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
#ifndef _VD_TIME_H_
#define _VD_TIME_H_ 1
#include"../VDDef.h"

/**
 *	Time class, responsible for providing
 *	the time in multiple resolution and
 *	different types of time.
 */
class VDDECLSPEC VDTime{
	friend class VDEngine;
public:

	/**
	 *	Get delta time since last frame.
	 *
	 *	@Return seconds.
	 */
	static float VDAPIENTRY deltaTime(void);

	/**
	 *	Get delta time since last frame
	 *	in high precision.
	 *
	 *	@Return seconds.
	 */
	static double VDAPIENTRY deltaTimed(void);

	/**
	 *	Get smooth delta time. It uses
	 *	the average delta time over multiple
	 *	frames delta time.
	 */
	static float VDAPIENTRY smoothDeltaTime(void);

	/**
	 *	Get time sense engine was initialized.
	 *	@Return number of seconds.
	 */
	static unsigned int VDAPIENTRY time(void);

	/**
	 *	Get time since the engine was initialized.
	 *	@Return number of seconds and fractions of seconds.
	 */
	static float VDAPIENTRY timef(void);

	/**
	 *	Get time in high precision.
	 */
	static double VDAPIENTRY timed(void);

	/**
	 *	Get unix epoch time stamp.
	 *	@Return
	 */
	static long int VDAPIENTRY getUnixTime(void);

	/**
	 *	Get time scale.
	 */
	static float VDAPIFASTENTRY getTimeScale(void);

	/**
	 *	Set time scale.
	 */
	static void VDAPIENTRY setTimeScale(float scale);

	/**
	 *	Not supported.
	 */
	static float VDAPIENTRY timeSinceLevelLoad(void);

	/**
	 *	Get fixed update time in milliseconds.
	 *
	 *	@Return
	 */
	static float VDAPIENTRY fixedTime(void);

	/**
	 *	Set fixed time update intervale.
	 */
	static void VDAPIENTRY setFixedTime(float time);

	/**
	 *	Get time resolution engine supports.
	 */
	static long int VDAPIENTRY getTimeResolution(void);

	/**
	 *	Make current thread sleep in miliseconds.
	 */
	static void VDAPIFASTENTRY sleep(long int msec);


private:
	/**
	 *	Update internal time. Used by the engine
	 *	internally only.
	 */
	static void VDAPIENTRY internal_update(void);


	static float internal_delta_timef(void);
	static float internal_delta_timed(void);


private:	/*	Static attributes.	*/

	static long int ticks;			/*	*/
	static long int ticksSinceLevel;	/*	*/
	static float scale;			/*	*/
	static float fixed;			/*	*/

};

#endif
