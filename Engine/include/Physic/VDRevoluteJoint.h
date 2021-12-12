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
#ifndef _VD_REVOLUTE_JOINT_H_
#define _VD_REVOLUTE_JOINT_H_ 1
#include <Physic/VDJoint.h>

/**
 *
 */
class VDDECLSPEC VDRevoluteJoint : public VDJoint{
public:
	VDRevoluteJoint();
	VDRevoluteJoint(const VDRevoluteJoint& joint);
	VDRevoluteJoint(VDRigidBody* rigidbody);

	virtual void VDAPIENTRY instanceInitilize();
	virtual void VDAPIENTRY onEnable();
	virtual void VDAPIENTRY onDisable();
	virtual void VDAPIENTRY initializeComponent();
	virtual void VDAPIENTRY onDestroy();
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);

	/**
	 *
	 */
	void VDAPIENTRY attachJoint(VDRigidBody* object);

};

#endif
