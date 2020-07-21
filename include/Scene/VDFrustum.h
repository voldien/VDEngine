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
#ifndef _VD_FRUSTUM_H_
#define _VD_FRUSTUM_H_ 1
#include"../Core/VDBehavior.h"
#include"../DataStructure/VDBoundVolume.h"
#include"../DataStructure/VDPlane.h"
#include"../VDDef.h"
#include"../VDSimpleType.h"

/**
 *	View frustum, where everything inside the
 *	frustum is visable.
 */
class VDDECLSPEC VDFrustum : public VDBehavior{
public:

	/**
	 *
	 */
	enum Intersection{
		eOut 		= 0,	/*	Outside the frustum.	*/
		eIn 		= 1,	/*	Insode the frustum.	*/
		eIntersect	= 2,	/*	Intersecting the frustum.*/
	};

	/**
	 *
	 */
	enum FrustumPlanes{
		eTOP 	= 0,
		eBOTTOM = 1,
		eLEFT 	= 2,
		eRIGHT 	= 3,
		eNEARP 	= 4,
		eFARP 	= 5
	};


	VDFrustum(void);
	VDFrustum(const VDFrustum& frustum);
	VDFrustum(float fov, float aspect, float near, float far);
	VDFrustum(float right, float left, float bottom, float top, float near, float far);

	/**
	 *
	 */
	void VDAPIENTRY setFov(float fov);

	/**
	 *
	 */
	void VDAPIENTRY setNear(float near);

	/**
	 *
	 */
	void VDAPIENTRY setFar(float far);

	/**
	 *
	 */
	void VDAPIENTRY setRatio(float ratio);

	/**
	 *
	 */
	float VDAPIENTRY getFov(void) const;

	/**
	 *
	 */
	float VDAPIENTRY getNear(void) const;

	/**
	 *
	 */
	float VDAPIENTRY getFar(void) const;

	/**
	 *
	 */
	float VDAPIENTRY getRatio(void)const;

	/**
	 *
	 */
	const VDMatrix4x4& VDAPIENTRY getProjectionMatrix(void)const;

	/**
	 *	Calculate the frustum planes.
	 */
	void VDAPIENTRY calcFrustumPlanes(const VDVector3& position, const VDVector3& look, const VDVector3& up, const VDVector3& right);

	/**
	 *	Calculate the frustum planes.
	 */
	void VDAPIENTRY calcFrustumPlanes(const VDVector3& position, const VDVector3& up, const VDVector3& right);

	/**
	 *	Create perspective frustum
	 *	\fov in radian..
	 */
	void VDAPIENTRY setPerspective(float fov, float aspect, float near, float far);


	/**
	 *	Create orth frustum.
	 */
	void VDAPIENTRY setOrth(float left, float right, float bottom, float top, float near, float far);

	/**
	 *	Check if point.
	 *	@Return
	 */
	Intersection VDAPIENTRY checkPoint(const VDVector3& pos)const;

	/**
	 *
	 *	@Return
	 */
	Intersection VDAPIENTRY intersectionAABB(const VDVector3& min, const VDVector3& max);
	Intersection VDAPIENTRY intersectionAABB(const VDAABB& bounds);

	/**
	 *
	 *	@Return
	 */
	Intersection VDAPIENTRY intersectionOBB(const VDVector3& x, const VDVector3& y, const VDVector3& z);
	Intersection VDAPIENTRY intersectionOBB(const VDOBB& obb);

	/**
	 *
	 *	@Return
	 */
	Intersection VDAPIENTRY intersectPlane(const VDPlane& plane)const;

	/**
	 *
	 *	@Return
	 */
	Intersection VDAPIENTRY intersectBoundingVolume(const VDBound& bounds, VDBound::BoundType type, const VDVector3& position);

	/**
	 *
	 *	@Return
	 */
	Intersection VDAPIENTRY intersectionFrustum(const VDFrustum& frustum)const;


private:	/*	Attributes.	*/

	VDPlane planes[6];						/*	*/
	float fov, ratio, Znear, Zfar, tang;	/*	*/
	float nw, nh, fh, fw;					/*	*/
	VDMatrix4x4 projectionMatrix;				/*	*/


};
#endif
