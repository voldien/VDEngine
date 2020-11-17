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
#ifndef _VD_RENDERSETTING_H_
#define _VD_RENDERSETTING_H_ 1
#include "../VDDef.h"

/**
 *	TODO hide inside settings source code definition.
 */
typedef struct vd_engine_rendersettings_t{

	unsigned int flag;
	unsigned int renderingflag;
	float fogMinDistance;
	float fogMaxDistance;

	unsigned int query;

	/*	*/
	typedef struct vd_snapshot_array_t{
		VDTexture2D* frames;
		unsigned int nframe;
		unsigned int numframe;
	}VDSnapShotArray;

	/*	*/
	VDSnapShotArray frame;

	/*	Rendering pipeline framebuffer.	*/
	VDRenderTexture* forward;

	/*	Renderpipelineshaders	*/
	VDShader* forwardRendering;
	VDShader* fowardShadowing;
	VDShader* lightShadowFirstPass;
	VDShader* lightShadowSecondPass;
	VDShader* lightShadowCubeMap;
	VDShader* reflectivecubemappass;
	VDShader* toneMapping;

	/*	*/
	//VDUniformBuffer particlebuffer;

	/*	*/
	VDRenderTexture* posttexture;

	/*	*/
	VDMesh* quadDisplay;		/*	*/
}VDEngineRenderSettings;

/**
 *
 */
class VDDECLSPEC VDRenderSetting{
	friend class VDEngine;
public:

	/**
	 *
	 */
	enum FogFlag{
		eFogDisable = 0x0,			/*	Fog disable.	*/
		eFogEnable 	= 0x1,			/*	*/
		eFogLinear 	= 0x2,			/*	Linear fog.	*/
		eFogExp 	= 0x3,			/*	exponential fog.	*/
		eFogExp2 	= 0x4,			/*	*/
	};

	/**
	 *
	 */
	enum AmbientType{
		eConstant 	= 0x1,	/*	*/
		eImageBased = 0x2,	/*	*/
	};

	/**
	 *
	 */
	enum RenderPipeline{
		eForwardRendering 	= (1 << 5),		/*	*/
	};

	VDRenderSetting(void){}
	VDRenderSetting(unsigned int sRenderingPath);
	
protected:	/*	Attributes.	*/

	static VDEngineRenderSettings gRenderSettings;	/*	*/

public:

	/**
	 *	Set rendering path.
	 *
	 *	\sRenderingPath
	 */
	static void VDAPIENTRY setRenderingPath(RenderPipeline sRenderingPath);

	/**
	 *	Get	rendering path.
	 *
	 *	@Return
	 */
	static RenderPipeline VDAPIENTRY getRenderingPath(void);

	/**
	 *
	 */
	static void setFrameBufferSize(int width, int height);

	/**
	 *	@Return
	 */
	static VDRenderTexture* getForwardFramebuffer(void);

	/**
	 *
	 */
	static bool VDAPIENTRY needFrameBuffer(void);

	/**
	 *
	 */
	static VDRenderTexture* VDAPIFASTENTRY getRenderingPathFrameBuffer(RenderPipeline sRenderingPath);


public:	/*	*/

	/**
	 *	Enable Fog.
	 */
	static void VDAPIENTRY useFog(bool fog);

	/**
	 *	@Return
	 */
	static bool VDAPIENTRY isFogEnable(void);

	/**
	 *
	 */
	static void VDAPIENTRY setFogType(FogFlag fogtype);
	static FogFlag VDAPIENTRY getFogType(void);

	/**
	 *	Set fog minimum distance.
	 */
	static void VDAPIENTRY setFogMinDistance(float fdis);
	static float VDAPIENTRY getFogMinDistance(void);

	/**
	 *
	 */
	static void VDAPIENTRY setFogMaxDistance(float fdis);
	static float VDAPIENTRY getFogMaxDistance(void);

	/**
	 *
	 */
	static void VDAPIENTRY setFogColor(const VDColor& color);

	/**
	 *	@Return
	 */
	static VDColor VDAPIENTRY getFogColor(void);

	/**
	 *
	 */
	static void VDAPIENTRY setFogDensity(float density);

	/**
	 *	@Return
	 */
	static float VDAPIENTRY getFogDensity(void);

	/**
	 *
	 */
	static void VDAPIENTRY setAmbientColor(const VDColor& color);

	/**
	 *	@Return
	 */
	static VDColor VDAPIENTRY getAmbientColor(void);

	/**
	 *
	 */
	static void VDAPIENTRY setAmbientIntensity(float intensity);
	static float VDAPIENTRY getAmbientIntensity(void);

	/**
	 *
	 */
	static void VDAPIENTRY setImageAmbient(VDCubeMap* cubemap, bool compute = false);

	/**
	 *
	 *	@Return
	 */
	static VDCubeMap* VDAPIENTRY getImageAmbient(void);

	/**
	 *	Set ambient light type.
	 */
	static void VDAPIENTRY setAmbientType(AmbientType type);

	/**
	 *	@Return
	 */
	static AmbientType VDAPIENTRY getAmbientType(void);


	/**
	 *	Set skybox.
	 *
	 */
	static void VDAPIENTRY setSkyBox(VDSkyBox* skybox);

	/**
	 *
	 *	@Return
	 */
	static VDSkyBox* VDAPIFASTENTRY getSkyBox(void);

	/**
	 *
	 *	@Return
	 */
	static unsigned int VDAPIENTRY getFlag(void);

	/**
	 *
	 *	@Return
	 */
	static VDEngineRenderSettings* VDAPIFASTENTRY getSettings(void);

};

#endif
