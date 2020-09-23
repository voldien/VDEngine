/**
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
#ifndef _VD_PLANE_H_
#define _VD_PLANE_H_ 1
#include"../VDSimpleType.h"
#include<iostream>

/**
 *
 */
class VDPlane {
public:
	inline VDPlane(void) {
	}
	inline VDPlane(const VDVector3& normal) {
		this->normal = normal;
		this->d = 0;
	}
	VDPlane(const VDVector3& point, const VDVector3& normal) {
		this->setNormalAndPoint(normal, point);
	}
	inline VDPlane(const VDPlane& plane) {
		*this = plane;
	}

	/**
	 *	@Return
	 */
	inline VDVector3 getNormal(void) const {
		return this->normal;
	}

	/**
	 *
	 */
	inline void setNormal(const VDVector3& normal) {
		this->normal = normal;
	}

	/**
	 *	@Return
	 */
	inline float distance(const VDVector3& point) const {
		return dot(normal, point) + d;
	}

	/**
	 *
	 *	@Return
	 */
	inline float distance(void) const {
		return this->d;
	}

	/**
	 *
	 *	@Return
	 */
	inline VDVector3 getPoint(void) const {
		return d * this->getNormal();
	}

	/**
	 *
	 */
	void setNormalAndPoint(const VDVector3& normal, const VDVector3& point) {
		this->normal = normal.normalize();
		this->d = -dot(this->normal, point);
	}

	/**
	 *	Construct plane.
	 */
	void set3DPoints(const VDVector3& v1, const VDVector3& v2, const VDVector3& v3) {
		this->normal = cross((v1 - v2), (v1 - v3)).normalize();
		this->d = -dot(this->normal, v2);
	}

protected:	/*	Attributes.	*/

	VDVector3 normal;		/*	*/
	float d;			/*	*/

public:
	/*	Static methods.	*/

	/**
	 *
	 *	@Return
	 */
	static VDPlane fromPoints(const VDVector3& v1, const VDVector3& v2,
			const VDVector3& v3) {
		VDPlane tmp;
		VDVector3 e1 = v2 - v1;
		VDVector3 e2 = v3 - v1;

		tmp.normal = cross(e1, e2).normalize();
		tmp.d = -dot(tmp.normal, v2);
		return tmp;
	}

};

#endif
