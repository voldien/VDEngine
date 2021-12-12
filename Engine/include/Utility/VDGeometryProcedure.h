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
#ifndef _VD_GEOMETRY_PROCEDURE_H_
#define _VD_GEOMETRY_PROCEDURE_H_ 1
#include "../Rendering/VDMesh.h"
#include "../VDSystem.h"
#include <vector>

/**
 *
 */
class VDDECLSPEC VDGeometryProcedure {
  public:
	enum GridType {
		normal = 0x1,  /* single color.	*/
		maya = 0x2,	   /* single color, execpt middle cross, black highlight	*/
		unity3D = 0x8, /* normal grid			*/
	};

	/**
	 *	@Return
	 */
	static VDMesh *VDAPIENTRY createQuad(float width, float height, unsigned int subDivision, bool PivotPoint = true);

	/**
	 *
	 *	@Return
	 */
	static VDMesh *VDAPIENTRY createCube(float size, unsigned int SubDivision);

	/*
	 *
	 *	@Return
	 */
	static VDMesh *VDAPIENTRY createSphere(float radius, unsigned int Slices, unsigned int SubDivision);

	/*
	 *
	 *	@Return
	 */
	static VDMesh *VDAPIENTRY createGrid(unsigned int x, unsigned int y, float deltaSpace, GridType gridFlag);

	/*
	 *
	 *	@Return
	 */
	static VDMesh *VDAPIENTRY createFrustum(float angle, float aspect);

	/*
	 *
	 *	@Return
	 */
	static VDMesh *VDAPIENTRY createBoundingBox();
};

#endif
