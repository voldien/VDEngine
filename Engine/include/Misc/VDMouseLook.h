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
#ifndef _VD_MOUSE_LOOK_H_
#define _VD_MOUSE_LOOK_H_ 1
#include "../Core/VDCustomBehavior.h"
#include "../DataStructure/VDPoint.h"

/**
 *	Responsible for adding mouse
 *	look around for the camera controller.
 */
class VDDECLSPEC VDMouseLook : public VDCustomBehavior{
public:
	enum rotationState{
		eX,
		eY,
		eXandY,
		eFreeRotation,
	};
	VDMouseLook(void);
	VDMouseLook(const VDMouseLook& look);
	VDMouseLook(rotationState state);
	~VDMouseLook(void);

private:	/*	Attributes.	*/

	float sensitivityX;
	float sensitivityY;

	float minimumX;
	float maximumX;

	float minimumY;
	float maximumY;

	float rotationY;
	float rotationX;
	rotationState state;

	VDPoint mousepos;
	VDPoint mousedelta;

public:	/*	public methods.	*/

	/**
	 *
	 */
	virtual void lateUpdate(void);

	/**
	 *
	 */
	virtual void onAwake(void);

	/**
	 *
	 */
	void setXSensitivity(float);

	/**
	 *
	 */
	float getXSensitivity(void)const;

	/**
	 *
	 */
	void setRotationMode(rotationState state);

	/**
	 *
	 */
	rotationState getRotationMode(void)const;
};

#endif
