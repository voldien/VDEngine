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
#ifndef _VD_KEY_FRAME_H_
#define _VD_KEY_FRAME_H_ 1
#include"../VDDef.h"

/**
 *	Key frame is the small component of
 *	animation
 */
class VDDECLSPEC VDKeyFrame {
public:
	VDKeyFrame(void);
	VDKeyFrame(const VDKeyFrame& key);
	VDKeyFrame(float value, float time);
	VDKeyFrame(float value, float time, float tangentIn, float tangentOut);

	/**
	 *	@Return
	 */
	inline float getTime(void) const {
		return this->time;
	}

	/**
	 *	@Return
	 */
	inline float getValue(void) const {
		return this->value;
	}

	/**
	 *	@Return
	 */
	inline void setTime(float time) {
		this->time = time;
	}

	/**
	 *	@Return
	 */
	inline void setValue(float value) {
		this->value = value;
	}

protected:
	float tangentIn; /*	*/
	float tangentOut; /*	*/
	float time; /*	*/
	float value; /*	*/
};

#endif
