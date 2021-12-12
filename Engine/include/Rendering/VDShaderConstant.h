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
#ifndef _SHADER_CONSTANT_H_
#define _SHADER_CONSTANT_H_ 1
#include "VDSystem.h"

/**
 *
 */
class VDDECLSPEC VDShaderConstant {
  public:
	/*
	 *
	 */
	enum {
		SC_TRANSFORM_M,
		SC_CAMERA_POSITON,
		SC_CAMERA_DIRECITON,
		SC_CAMERA_UP,
		SC_CAMERA_RIGHT,

		SC_MATERIAL_EMISSIVE,
		SC_MATERIAL_AMBIENT,
		SC_MATERIAL_DIFFUSE,
		SC_MATERIAL_SPECULAR,
		SC_SHININESS,

		SC_LIGHT_POSITION,
		SC_LIGHT_DIRECTION,
		SC_LIGHT_AMBIENT,
		SC_LIGHT_DIFFUSE,
		SC_LIGHT_SPECULAR,
		SC_LIGHT_SPOTCUTOFF,
		SC_USER_DEFINED,

		eShadowMappingOffset = 5,
	};

	/*
	 *
	 */
	enum TextureLocation {
		/**
		 *	Deferred
		 */
		eDeferredDiffuse = 0,	   /**/
		eDeferredNormal = 1,	   /**/
		eDeferredWorld = 2,		   /**/
		eDeferredSpecular = 3,	   /**/
		eDeferredIllusion = 4,	   /**/
		eDeferredDepthTexture = 5, /**/

		/**
		 *
		 */
		eDiffuseTexture = 0,
		eNormalTexture = 1,
		eReflectionTexture = 2,
		eIllusionTexdture = 3,
		eDisplacementTexture = 4,
		eSpecularTexture = 5,
		eLightMappingTexture = 6,
		eDepthTexture = 7,
		eCustom1 = 7,
		eCustom8 = 7,

		MotionTexture0 = 8,
		SplashTexture = 8,
		/**/
		SkyBox = 9,
		/*
		 *
		 */
		AmbientImageBased = 10,

		hadowMapping = 11,
		ShadowMappingCube = 31,

		MaxTextureUnit = 0xF /*	The least number of binded texture unit.*/

	};

	/*
	 *	Vertex attributes constant location.
	 */
	enum AttributeLocation {
		VERTEX_LOCATION = 0x0,
		TEXTURECOORD_LOCATION = 0x1,
		NORMAL_LOCATION = 0x2,
		TANGENT_LOCATION = 0x3,
		BONE_ID_LOCATION = 0x5,
		BONE_WEIGHT_LOCATION = 0x6,
		VERTEXCOLOR_LOCATION = 0x7,
		BINORMAL_LOCATION = 0x8,
		BITTANGENT_LOCATION = 0x9,
		WVP_LOCATION = 0xA,
		WORLD_LOCATION = 0xB,
	};

	/*
	 *	Fragment location for fragment shader.
	 */
	enum FragDataLocation {
		eFragColor = 0,
		eFragDiffuse = 1,
		eFragNormal = 2,
		eFragWorld = 3,
		eFragSpecular = 4,
		eFragIllusion = 5,
	};

	/*
	 *	Uniform binding location
	 */
	enum BufferBase {
		/*
		 *
		 */
		eMorphVertex = 0,
		eMorphNormal = 1,
		eMorphTangent = 2,

		/*
		 *	engine uniform requsites location.
		 */
		// eShaderLightIndices = 2,
		// eSkinnedBone = 4,
		// eShaderParticle = 5,
		// eShaderLightShadow = 6,
		// eShaderLight = 7,
		// eShaderEngineInfo = 8,
		eMaxDefaultUniformLocation = 12,
	};

	/**
	 *
	 */
	enum BindingLocation {
		eLightning = 1,
		eShadow = 2,
		eLightIndices = 3,
		eEngineState = 4,
		eParticle = 5,
	};

	/**
	 *	Syntax Pointer Of Shader Language of DiffuseColor.
	 */
	inline static const char *DiffuseColor() { return "DiffuseColor"; }
	inline static const char *ReflectionColor() { return "ReflectionColor"; }
	inline static const char *SpecularColor() { return "SpecularColor"; }
	inline static const char *FragColor() { return "fragColor"; }
	inline static const char *AmbientColor() { return "AmbientColor"; }
	inline static const char *texCoord() { return "TextureCoord"; }
	inline static const char *vertex() { return "Vertex"; }
	inline static const char *Normal() { return "Normal"; }
	inline static const char *tangent() { return "tangent"; }
	inline static const char *VertexColour() { return "VertexColor"; }
	inline static const char *DiffuseTexture() { return "DiffuseTexture"; }
	inline static const char *NormalTexture() { return "NormalTexture"; }
	inline static const char *WorldTexture() { return "WorldTexture"; }
	inline static const char *SpecularTexture() { return "SpecularTexture"; }
	inline static const char *DepthTexture() { return "DepthTexture"; }
	inline static const char *ReflectionTexture() { return "ReflectionTexture"; }
	inline static const char *IllusionTexture() { return "IllusionTexture"; }
	inline static const char *DisplacementTexture() { return "DisplacementTexture"; }
	inline static const char *DisplacementHeight() { return "DisplacementHeight"; }
	inline static const char *Offset() { return "Offset"; }
	inline static const char *Tile() { return "Tile"; }
	inline static const char *TextureSampler() { return "TextureSampler"; }
	inline static const char *CameraPosition() { return "CameraPos"; }
	inline static const char *CameraDirection() { return "CameraDir"; }
	inline static const char *worldSpace() { return "worldSpace"; }
	inline static const char *ScreenSpace() { return "ScreenSpace"; }

	inline static const char *ProjectionMatrix() { return "ProjectionMatrix"; }
	inline static const char *ViewMatrix() { return "ViewMatrix"; }
	inline static const char *ModelMatrix() { return "ModelMatrix"; }
	inline static const char *ModelViewProjection() { return "ModelViewProjection"; }
	inline static const char *ModelViewMatrix() { return "ModelViewMatrix"; }
	inline static const char *ViewProjection() { return "ViewProjection"; }

	inline static const char *NormalMatrix() { return "NormalMatrix"; }
	inline static const char *DeformMatrix() { return "DeformMatrix"; }

	inline static const char *ambientCube() { return "ambientCube"; }
	inline static const char *lightCookie() { return "lightcookie"; }

	inline static const char *Time() { return "time"; }

	/**/
	inline static const char *engineState() { return "enginestate"; }
	inline static const char *particleSystem() { return "particleSystem"; }
	inline static const char *lightIndices() { return "lightIndices"; }
	inline static const char *lightUniform() { return "lightuniform"; }
	inline static const char *shadowstruct() { return "shadowstructure"; }
};

#endif
