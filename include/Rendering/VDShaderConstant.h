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
#ifndef _SHADER_CONSTANT_H_
#define _SHADER_CONSTANT_H_ 1
#include"VDSystem.h"

/**
 *
 */
class VDDECLSPEC VDShaderConstant{
public:

	/*
	 *
	 */
	enum{
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
	enum TextureLocation{
		/**
		 *	Deferred
		 */
		eDeferredDiffuse 	= 0,		/**/
		eDeferredNormal 	= 1,		/**/
		eDeferredWorld 		= 2,		/**/
		eDeferredSpecular 	= 3,		/**/
		eDeferredIllusion 	= 4,		/**/
		eDeferredDepthTexture = 5,		/**/


		/**
         *
         */
		eDiffuseTexture 		= 0,
		eNormalTexture 			= 1,
		eReflectionTexture 		= 2,
		eIllusionTexdture 		= 3,
		eDisplacementTexture 	= 4,
		eSpecularTexture 		= 5,
		eLightMappingTexture 	= 6,
		eDepthTexture 			= 7,
		eCustom1 				= 7,
		eCustom8 				= 7,
      
		eMotionTexture0 	= 8,
		eSplashTexture 		= 8,
      	/**/
		eSkyBox = 9,
      	/*
      	 *
      	 */
		eAmbientImageBased = 10,

		eShadowMapping = 11,
		eShadowMappingCube = 31,

      	eMaxTextureUnit = 0xF /*	The least number of binded texture unit.*/

	};


	/*
	 *	Vertex attributes constant location.
	 */
	enum AttributeLocation{
		eVERTEX_LOCATION = 0x0,
		eTEXTURECOORD_LOCATION = 0x1,
		eNORMAL_LOCATION = 0x2,
		eTANGENT_LOCATION = 0x3,
		eBONE_ID_LOCATION = 0x5,
		eBONE_WEIGHT_LOCATION = 0x6,
		eVERTEXCOLOR_LOCATION = 0x7,
		eBINORMAL_LOCATION  = 0x8,
		eBITTANGENT_LOCATION = 0x9,
		eWVP_LOCATION = 0xA,
		eWORLD_LOCATION = 0xB,
	};

  
	/*
	 *	Fragment location for fragment shader. 
     */
	enum FragDataLocation{
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
	enum BufferBase{
      	/*
         *
         */
		eMorphVertex = 0,
		eMorphNormal = 1,
		eMorphTangent = 2,

      	/*
         *	engine uniform requsites location.
         */
		//eShaderLightIndices = 2,
		//eSkinnedBone = 4,
		//eShaderParticle = 5,
		//eShaderLightShadow = 6,
		//eShaderLight = 7,
		//eShaderEngineInfo = 8,
      	eMaxDefaultUniformLocation = 12,
	};

	/**
	 *
	 */
	enum BindingLocation{
		eLightning 	= 1,
		eShadow 	= 2,
		eLightIndices 	= 3,
		eEngineState 	= 4,
		eParticle 		= 5,
	};


	/**
	 *	Syntax Pointer Of Shader Language of DiffuseColor.
	 */
	inline static const char* DiffuseColor(void){return "DiffuseColor";}
	inline static const char* ReflectionColor(void){return "ReflectionColor";}
	inline static const char* SpecularColor(void){return "SpecularColor";}
	inline static const char* FragColor(void){return "fragColor";}
	inline static const char* AmbientColor(void){return "AmbientColor";}
	inline static const char* texCoord(void){return "TextureCoord";}
	inline static const char* vertex(void){return "Vertex";}
	inline static const char* Normal(void){return "Normal";}
	inline static const char* tangent(void){return "tangent";}
	inline static const char* VertexColour(void){return "VertexColor";}
	inline static const char* DiffuseTexture(void){return "DiffuseTexture";}
	inline static const char* NormalTexture(void){return "NormalTexture";}
	inline static const char* WorldTexture(void){return "WorldTexture";}
	inline static const char* SpecularTexture(void){ return "SpecularTexture";}
	inline static const char* DepthTexture(void){return "DepthTexture";}
	inline static const char* ReflectionTexture(void){return "ReflectionTexture";}
	inline static const char* IllusionTexture(void){return "IllusionTexture";}
	inline static const char* DisplacementTexture(void){return "DisplacementTexture";}
	inline static const char* DisplacementHeight(void){return "DisplacementHeight";}
	inline static const char* Offset(void){return "Offset";}
	inline static const char* Tile(void){return "Tile";}
	inline static const char* TextureSampler(void){return "TextureSampler";}
	inline static const char* CameraPosition(void){return "CameraPos";}
	inline static const char* CameraDirection(void){return "CameraDir";}
	inline static const char* worldSpace(void){return "worldSpace";}
	inline static const char* ScreenSpace(void){return "ScreenSpace";}

	inline static const char* ProjectionMatrix(void){return "ProjectionMatrix";}
	inline static const char* ViewMatrix(void){return "ViewMatrix";}
	inline static const char* ModelMatrix(void){return "ModelMatrix";}
	inline	static const char* ModelViewProjection(void){return "ModelViewProjection";}
	inline static const char* ModelViewMatrix(void){return "ModelViewMatrix";}
	inline static const char* ViewProjection(void){return "ViewProjection";}

	inline static const char* NormalMatrix(void){return "NormalMatrix";}
	inline static const char* DeformMatrix(void){return "DeformMatrix";}

	inline static const char* ambientCube(void){return "ambientCube";}
	inline static const char* lightCookie(void){return "lightcookie";}


	inline static const char* Time(void){return "time";}

	/**/
	inline static const char* engineState(void){return "enginestate";}
	inline static const char* particleSystem(void){return "particleSystem";}
	inline static const char* lightIndices(void){return "lightIndices";}
	inline static const char* lightUniform(void){return "lightuniform";}
	inline static const char* shadowstruct(void){return "shadowstructure";}

};


#endif
