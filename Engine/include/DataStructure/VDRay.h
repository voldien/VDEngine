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
#ifndef _RAY_H_
#define _RAY_H_ 1
#include"VDSimpleType.h"

/**
 *
 */
class VDRay {
public:
	VDRay(void);
	VDRay(const VDVector3& origin, const VDVector3& direction);
	VDRay(const VDRay& ray);

	inline VDVector3 getOrigin(void) const {
		return this->m[0];
	}

	inline void setOrigin(const VDVector3& origin) {
		this->m[0] = origin;
	}

	/**
	 *	Get direction.
	 *
	 *	@Return normalized direction.
	 */
	inline VDVector3 getDirection(void) const {
		return this->m[1];
	}

	/**
	 *
	 */
	inline void setDirection(const VDVector3& direction) {
		this->m[1] = direction;
	}

	/**
	 *
	 *	@Return
	 */
	inline VDVector3 pointAtParameter(float t) const {
		return getOrigin() + t * this->getDirection();
	}

private:
	/*	Attributes.	*/

	/**
	 *	#0 origin
	 *	#1 direction
	 */
	VDVector3 m[2];

};

inline VDRay::VDRay(void) {
}

inline VDRay::VDRay(const VDVector3& origin, const VDVector3& direction) {
	this->setOrigin(origin);
	this->setDirection(direction);
}

inline VDRay::VDRay(const VDRay& ray) {
	this->setOrigin(ray.getOrigin());
	this->setDirection(ray.getDirection());
}

#endif
