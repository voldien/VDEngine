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
#ifndef _VD_BOX_COLLIDER_H_
#define _VD_BOX_COLLIDER_H_ 1
#include"VDCollider.h"

/**
 *	Box collider.
 */
class VDDECLSPEC VDBoxCollider : public VDCollider {
public:
	VDBoxCollider(void);
	VDBoxCollider(const VDBoxCollider& collider);

	virtual void VDAPIENTRY instanceInitilize(void);
	virtual void VDAPIENTRY onEnable(void);
	virtual void VDAPIENTRY onDisable(void);
	virtual void VDAPIENTRY initializeComponent(void);
	virtual void VDAPIENTRY onDestroy(void);
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);

	/**
	 *	Set size of the box collider.
	 *	Width,height and depth is multiple by 2 by
	 *	the size.
	 */
	void VDAPIENTRY setSize(const VDVector3& size);

	/**
	 *	Get box size.
	 */
	VDVector3 VDAPIFASTENTRY getSize(void)const;

	/**
	 *	Perform a ray intersects the box.
	 *	@Return true if intersected.
	 */
	bool VDAPIENTRY intersect(const VDVector3& orig, const VDVector3 dir, VDRaycastHit& hit)const;

	/**
	 *	Perform a ray intersects the box.
	 *	@Return true if intersected.
	 */
	bool VDAPIENTRY intersect(const VDRay& ray, VDRaycastHit& hit)const;

};

#endif
