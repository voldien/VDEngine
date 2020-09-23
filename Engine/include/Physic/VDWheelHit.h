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
#ifndef _VD_WHEEL_HIT_H_
#define _VD_WHEEL_HIT_H_ 1
#include"VDDef.h"
#include"VDPrerequisites.h"


/**
 *	Wheel Hit
 */
class VDDECLSPEC VDWheelHit{
public:
	VDWheelHit(void);
	VDWheelHit(const VDWheelHit& hit);

	/**
	 *	Get collider.
	 *
	 *	@Return
	 */
	VDCollider* VDAPIFASTENTRY collider(void);

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY force(void)const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY forwardDir(void)const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY forwardSlip(void)const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY normal(void)const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY point(void)const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY sidewaysDir(void)const;

	/**
	 *
	 *	@Return
	 */
	VDVector3 VDAPIFASTENTRY sidewaysSlip(void)const;

};

#endif
