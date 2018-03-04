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
#ifndef _VD_PLANE_COLLIDER_H_
#define _VD_PLANE_COLLIDER_H_ 1
#include"VDCollider.h"
#include"VDPhysic.h"

/**
 *	infinite plane collider.
 */
class VDDECLSPEC VDPlaneCollider : public VDCollider{
public:
	VDPlaneCollider(void);
	VDPlaneCollider(const VDPlaneCollider& collider);

	virtual void VDAPIENTRY instanceInitilize(void);
	virtual void VDAPIENTRY onEnable(void);
	virtual void VDAPIENTRY onDisable(void);
	virtual void VDAPIENTRY initializeComponent(void);
	virtual void VDAPIENTRY onDestroy(void);
	virtual VDBehavior* VDAPIENTRY copyComponet(unsigned int& dataSize);

	/**
	 *	Get plane normal.
	 *
	 *	@Return
	 */
	VDVector3 VDAPIENTRY getNormal(void)const;

	/*
	 *
	 */
	void VDAPIENTRY setNormal(const VDVector3& normal);

	/**
	 *
	 */
	bool VDAPIENTRY intersect(const VDVector3& orig, const VDVector3 dir, VDRaycastHit& hit)const;

	/**
	 *
	 */
	bool VDAPIENTRY intersect(const VDRay& ray, VDRaycastHit& hit)const;

};

#endif
