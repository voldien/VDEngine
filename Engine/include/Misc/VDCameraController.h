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
#ifndef _VD_CAMERA_CONTROLLER_H_
#define _VD_CAMERA_CONTROLLER_H_ 1
#include "../Physic/VDCharacterControllerHit.h"
#include "../Core/VDCustomBehavior.h"
#include "../Scene/VDGameObject.h"
#include "../Misc/VDMouseLook.h"

/**
 *
 */
class VDDECLSPEC VDCameraController : public VDCustomBehavior {
public:
	VDCameraController();
	VDCameraController(const VDCameraController& controller);
	~VDCameraController();

	//virtual void VDAPIENTRY onDestroyed();
	virtual void VDAPIENTRY fixedUpdate();
	virtual void VDAPIENTRY onAwake();
	virtual void VDAPIENTRY onCharacterController(VDCharacterControllerHit& hit);

private:	/*	Attributes.	*/

	float sensityX;
	float sensityY;
	float speed;
	float maxSpeed;
	float gravity;
	unsigned int flag;
	VDCharacterController* characterController;
	VDCamera* camera;
public:
	void VDAPIENTRY setCharacterMode(unsigned int mode, int enabled);
};

#endif
