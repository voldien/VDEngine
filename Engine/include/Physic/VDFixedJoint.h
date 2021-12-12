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
#ifndef _VD_FIXED_JOINT_H_
#define _VD_FIXED_JOINT_H_ 1
#include "Physic/VDJoint.h"

/**
 *
 */
class VDDECLSPEC VDFixedJoint : public VDJoint{
public:
	VDFixedJoint();
	VDFixedJoint(const VDFixedJoint& joint);
	VDFixedJoint(VDRigidBody* rigidbody);


	virtual void VDAPIENTRY instanceInitilize();
	virtual void VDAPIENTRY initializeComponent();
	virtual void VDAPIENTRY onEnable();
	virtual void VDAPIENTRY onDisable();
	virtual void VDAPIENTRY onDestroy();
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);

	/*
	 *
	 */
	void VDAPIENTRY attachJoint(VDRigidBody* rigidbody);

};

#endif
