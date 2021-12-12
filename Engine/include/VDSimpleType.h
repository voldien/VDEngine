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
#ifndef _VD_SIMPLE_TYPE_H_
#define _VD_SIMPLE_TYPE_H_ 1
#include "VDDef.h"
#include "VDPrerequisites.h"
#include <Core/Color.h>
#include <Core/dataStructure/AABB.h>
#include <Core/dataStructure/OBB.h>
#include <Core/dataStructure/ONB.h>
#include <Core/dataStructure/Plane.h>
#include <Core/dataStructure/Ray.h>

/**
 *	Declare HC class object
 *	with the same namespace as
 *	for all the other classes.
 */
using VDVector3 = fragcore::Vector3;
using VDVector4 = fragcore::Vector4;
using VDVector2 = fragcore::Vector2;
using VDMatrix4x4 = fragcore::Matrix4x4;
using VDMatrix3x3 = fragcore::Matrix3x3;
using VDQuaternion = fragcore::Quaternion;
using VDAABB = fragcore::AABB;
using VDONB = fragcore::ONB;
using VDOBB = fragcore::OBB;
using VDRay = fragcore::Ray;
using VDColor = fragcore::Color;
using VDPlane = fragcore::Plane;

#ifdef __cplusplus
extern "C" {
#endif
VD_DECLARE_HANDLE(VDHANDLE);
VD_DECLARE_HANDLE(VDWin);
VD_DECLARE_HANDLE(VDOpenGLContext);
VD_DECLARE_HANDLE(VDOpenCLContext);
#ifdef __cplusplus
}
#endif

/**
 *	Callback.
 */
typedef void(VDAPIENTRY *VDCallBack)();
typedef int(VDAPIENTRY *VDCustomCallBack)(void *);

/**
 *	Get and set callback function type.
 */
typedef void *(VDAPIENTRY *VDGetCallBack)();
typedef void(VDAPIENTRY *VDSetCallBack)(void *data);

/**
 *	Class member callback.
 */
typedef void *(VDBehavior::*VDGetClassMethod)();
typedef void (VDBehavior::*VDSetClassMethod)(void *);

typedef void *VDWindow;
typedef void *VDGLContext;

/**
 *
 */
typedef struct vd_vertex_t {
	float x, y, z;
} VDVertex;

/**
 *
 */
typedef struct vd_vertex_2D_t {
  public:
	float x, y;
} VDVertex2D;

/**
 *
 */
typedef struct _TexUV {
	float u; /*  x */
	float v; /*  y */
} TexCoord, VertexUV;
/**
 *
 */
typedef struct _VertexNormalF {
	float x, y, z;

} VertexNormal, VertexBiNormal;

/**
 *
 */
typedef struct _VertexTangnetF {
	float x;
	float y;
	float z;
} VertexTangent, VertexBitTangent;

/**
 *
 */
typedef struct UVCoordinationDescription {
	VertexUV *vertexUV;
	unsigned int vertexCount;
} UVDesc;

#endif
