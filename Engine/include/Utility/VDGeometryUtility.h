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
#ifndef _VD_GEOMETRY_UTILITY_H_
#define _VD_GEOMETRY_UTILITY_H_ 1
#include "../Rendering/VDMesh.h"
#include "../VDSystem.h"

/**
 *
 */
class VDDECLSPEC VDGeometryUtility {
  public:
	/**
	 *
	 */
	static void VDAPIENTRY subDivid(VDMesh *mesh, unsigned int subdivision);

	/**
	 *
	 */
	static void VDAPIENTRY setPivot(VDMesh *mesh);

	/**
	 *
	 */
	static void VDAPIENTRY scale(VDMesh *mesh, const VDVector3 &size);

	/*	TODO add bound code here for now*/
	/**
	 *
	 */
	static void VDAPIENTRY computeAABB(const VDVertex *vertices, unsigned int stride, int count, VDVector3 *center,
									   VDVector3 *size);
	static void VDAPIENTRY computeAABB(const VDVertex *vertices, unsigned int stride, int count, VDAABB *bounds);

	/**
	 *
	 */
	static void computeOBB(const VDVector3 *vertices, int count, VDOBB *obb, bool analytic = false);
	// static void computeOBB(const VDVector3* vertices, int count, VDOBB& obb, bool analytic = false);

	/**
	 *
	 */
	static unsigned int VDAPIENTRY getindexBufferSize(unsigned int IndicesCount);
	static unsigned int VDAPIENTRY getIndicesSize(unsigned int IndicesCount);
};

#endif
