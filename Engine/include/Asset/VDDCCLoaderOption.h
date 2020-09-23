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
#ifndef _VD_DCC_LOADER_OPTION_H_
#define _VD_DCC_LOADER_OPTION_H_ 1
#include "../Rendering/VDMesh.h"
#include <climits>

/**
 *
 */
class VDAssetConstant{
public:
	enum AssertLoad : unsigned long int{
		eVertex = VDMesh::eVertex,
		eTexureCoord = VDMesh::eTextureCoord,
		eNormal = VDMesh::eNormal,
		eTangent = VDMesh::eTangent,


		eLight = 0x10000,						// import of light from scene data.
		eCamera =0x20000,						// import camera from the scene data
		eCollision = 0x40000,					// creation collision out of mesh.
		eBone = 0x80000,
		eSkinned = 0x80000,		//
		eSplitMaterialMesh = 0x100000,			// Split Mesh with more than 1 Material attached to same mesh.
		eAnimation = 0x200000,					// Import Animation
		eTexture = 0x400000,					// Import Texture
		eFlipUV = 0x800000,						// Flip UV 
		eMaterial = 0x1000000,					// Import Material Preference.
		eadvanceMaterial = 0x2000000,			// Import Advanced Material.
		eMesh =   0x4000000,					// Import Mesh
		eConvex = 0x8000000,					// Collision Convex
		eRigidBody = 0x10000000,				// RigidBody
		eRigidBodyBySceneData = 0x20000000,		// 
		eAudioGeometry = 0x40000000,			// FMOD Audio Geometry
		eMeshReference = 0x80000000,			// Identity Identical Mesh and use reference instance of instance physical data.
		eShaderTessellation = 0x100000000,		// Tessellation on shader if hardware support.
		eCharacterController = 0x200000000,		// Import Character Controller based on Fixed Keyword
		eRemoveUnReferenceData = 0x400000000,	// Remove UnReference Data
		eAudio = 0x800000000,					// Import Audio
		eBoundingBox = 0x1000000000,			// 
		eAutoMaterial = 0x2000000000,			//
		eTextureCompressed = 0x4000000000,		//
		eMeshCompressed = 0x8000000000,			//
		eTerrain = 0x10000000000,				//
		eReflection = 0x20000000000,			//
		eBatchOptimization = 0x80000000000,		// will combind mesh that have same material to one mesh.
		eLightMappingUV = 0x100000000000,		// Import Second UV Map Data if the Model has it. or create in
		eVertexArrayMesh = 0x200000000000,		//
		eLightMappingUVCreate = 0x400000000000,	// Import Second UV Map Data if the Model has it. or create in
		eEnviormentReflection = 0x800000000000,	// create reflection map.
		eDefaultReflection = 0x1000000000000,	// use of skybox reflection map
		eOnlyLoadContent = 0x2000000000000,
		eHierarchy = 0x4000000000000,
		eImportDefault = (eTextureCompressed | eMeshReference | eRigidBodyBySceneData | eCollision | eSkinned |  eAnimation | eMaterial | eLight | eTexture | eMesh | VDMesh::eVertex | VDMesh::eNormal | VDMesh::eTangent | VDMesh::eTextureCoord | eDefaultReflection | eHierarchy),
		eImportQuality = (eImportDefault | eAudioGeometry | eRigidBodyBySceneData | eShaderTessellation),
		eImportPerformance = ((eImportDefault ^ eCollision) | eRemoveUnReferenceData),
		eImportOptimized = (eImportDefault |eMeshReference),
		eImportAuto = 0x2,
		eImportWorld = (ULLONG_MAX),
		eAll = (ULLONG_MAX),
	};
};

#define IMPORT_MESH_VERTEX VERTEX
#define IMPORT_MESH_UV NORMAL
#define IMPORT_MESH_NORMAL TANGENT
#define IMPORT_MESH_TANGENT TEXTURECOORDINATION
#define IMPORT_MESH_BINORMAL
#define IMPORT_MESH_BITTANGENT

#define IMPORT_MESH  (unsigned long long) ( VDAssetConstant::eMesh | VDMesh::eVertex | VDMesh::eNormal | VDMesh::eTangent | VDMesh::eTextureCoord )
#define IMPORT_MESH_REFERENCE (unsigned long long)VDAssetConstant::eMeshReference
#define IMPORT_CAMERA (unsigned long long)VDAssetConstant::eCamera
#define IMPORT_LIGHT (unsigned long long)VDAssetConstant::eLight
#define IMPORT_COLLISION (unsigned long long)VDAssetConstant::eCollision
#define IMPORT_SKINNED (unsigned long long)VDAssetConstant::eSkinned
#define IMPORT_SPLITMATERIALMESH (unsigned long long)VDAssetConstant::eSplitMaterialMesh
#define IMPORT_ANIMATION (unsigned long long)VDAssetConstant::eAnimation
#define IMPORT_TEXTURE (unsigned long long)VDAssetConstant::eTexture
#define IMPORT_FLIPUV (unsigned long long)VDAssetConstant::eFlipUV
#define IMPORT_MATERIAL (unsigned long long)VDAssetConstant::eMaterial
#define IMPORT_ADVANCE_MATERIAL (unsigned long long)VDAssetConstant::eadvanceMaterial
#define IMPORT_SHADERTESSELLATION (unsigned long long)VDAssetConstant::eShaderTessellation		// material with displacement texture will get tessleation version of the Material.
#define IMPORT_TEXTURE_COMPRESSED (unsigned long long)VDAssetConstant::eTextureCompressed
#define IMPORT_MESH_COMPRESSED (unsigned long long)VDAssetConstant::eMeshCompressed
#define IMPORT_CONVEX_COLLISION (unsigned long long)VDAssetConstant::eConvex
#define IMPORT_RIGIDBODY (unsigned long long)VDAssetConstant::eRigidBody
#define IMPORT_RIGIDBODY_SCENE (unsigned long long)VDAssetConstant::eRigidBodyBySceneData
#define IMPORT_TERRAIN (unsigned long long)VDAssetConstant::eTerrain
#define IMPORT_CHARACTERCONTROLLER (unsigned long long)VDAssetConstant::eCharacterController
#define IMPORT_BATCH_OPTIMIZATION (unsigned long long)VDAssetConstant::eBatchOptimization
#define IMPORT_UV2 (unsigned long long)VDAssetConstant::eLightMappingUV
#define IMPORT_UV2Create (unsigned long long)VDAssetConstant::eLightMappingUV
#define IMPORT_DEFAULTREFLECTIONMAP (unsigned long long)VDAssetConstant::eDefaultReflection
#define IMPORT_ALL (unsigned long long)VDAssetConstant:::eAll
#define IMPORT_HIERARCHY VDAssetConstant::eHierarchy


#define IMPORT_DEFAULT (unsigned long long)VDAssetConstant::eImportDefault
#define IMPORT_PERFORMANCE (unsigned long long)VDAssetConstant::eImportPerformance
#define IMPORT_QUALITY (unsigned long long)VDAssetConstant::eImportQuality
#define IMPORT_AUTO (unsigned long long)VDAssetConstant::eImportAuto

#endif
