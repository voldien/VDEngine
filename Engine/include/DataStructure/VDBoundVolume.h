/*
 *	VDEngine virtual dimension game engine.
 *	Copyright (C) 2014  Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _VD_BOUND_VOLUME_H_
#define _VD_BOUND_VOLUME_H_ 1
#include "../VDSimpleType.h"

/**
 *	Bound volume. Used for
 *	enabling most efficient volume
 *	depending on what object.
 */
union VDBound {
  public:
	enum BoundType {
		eAABB = 0x1,
		eOBB = 0x2,
		eBound = (eAABB | eOBB),
	};

  public:		 /*	Attributes.	*/
	VDAABB aabb; /*	Align axis bounding box.	*/
	VDOBB obb;	 /*	Oriented bounding box.	*/

  public:
	VDBound() {}
	VDBound(const VDBound &bound) { *this = bound; }
	VDBound &operator=(const VDBound &bound) {
		memcpy(this, &bound, sizeof(VDBound));
		return *this;
	}
};

#endif
