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
#ifndef _VD_QUALITY_SETTING_H_
#define _VD_QUALITY_SETTING_H_ 1
#include "../VDDef.h"
#include "../VDSystem.h"

/**
 *
 */
class VDDECLSPEC VDQualitySetting {
  public:
	enum ShadowFilter {
		eSimple = (1 << 1),	  /*	Normal hard shadows.	*/
		ePCF = (1 << 2),	  /*	Percentage filtering.	*/
		eVariance = (1 << 3), /*	Not supported.	*/
	};

	enum SampleType {
		eAntiAliasingEnable = 0x1,
		None = (1 << 4),  /*	*/
		eSSAA = (1 << 6), /*	Supersample  anti aliasing.	*/
		eMSAA = (1 << 9), /*	Multisample anti-aliasing.	*/
		eSA = (1 << 10),  /*	*/
	};

	enum Culling {
		eFrustum,		  /*	*/
		eEarlyZRejection, /*	*/
	};

	enum ColorSpace {
		eGamma,	 /*	*/
		eLinear, /*	*/
		eSrga,	 /*	*/
	};

  public: /*	Public static methods.	*/
	/**
	 *	Use shadow.
	 */
	static void VDAPIENTRY useShadow(bool shadow);

	/**
	 *	Get shadow filter.
	 *
	 *	@Return
	 */
	static ShadowFilter VDAPIENTRY getShadowFilter();

	/**
	 *	Set shadow filter.
	 */
	static void VDAPIENTRY setShadowFilter(ShadowFilter filter);

	/**
	 *	Set shadow distance.
	 */
	static void VDAPIENTRY setShadowDistance(float distance);

	/**
	 *	Get shadow distance.
	 */
	static float VDAPIFASTENTRY getShadowDistance();

	/**
	 *	Use anti-aliasing.
	 */
	static VDAPIENTRY void useAntaiAlising(bool use);

	/**
	 *	Set current anti-aliasing sample mode.
	 */
	static void VDAPIENTRY setSamplerMode(SampleType mode);

	/**
	 *	Get current anti-aliasing sample mode.
	 */
	static SampleType VDAPIENTRY getSampleMode();

	/**
	 *	Set number of anti-alasing samples.
	 */
	static void VDAPIENTRY setAntaiAlisingSampling(unsigned int sampling);

	/**
	 *	@Return number of anti aliasing sampling.
	 */
	static unsigned int VDAPIENTRY getAntaiAlisingSampling();

	/**
	 *	Set current culling mode.
	 */
	static void VDAPIENTRY setCulling(Culling culling);

	/**
	 *	Get current culling mode.
	 */
	static Culling VDAPIENTRY getCulling();

	/**
	 *	Set current texture LOD level.
	 */
	static void VDAPIENTRY setTextureLod(unsigned int lodLevel);

	/**
	 *	Get current texture LOD level.
	 */
	static int VDAPIENTRY getTextureLod();

	/**
	 *	Set texture current texture anisotropy.
	 */
	static void VDAPIENTRY setTextureAnisotropy(float Anisotropylevel);

	/**
	 *	Get current texture anisotropy.
	 */
	static float VDAPIENTRY getTextureAnisotropy();

	/**
	 *	Set current color space.
	 */
	static void VDAPIENTRY setColorSpace(ColorSpace colorspace);

	/**
	 *	Get current color space.
	 */
	static ColorSpace VDAPIENTRY getColorSpace();

	/**
	 *	Set VSync.
	 */
	static void VDAPIENTRY setVSync(bool enable);

	/**
	 *	Get Vsync status.
	 *
	 *	@Return true if sync enabled.
	 */
	static bool VDAPIENTRY getVSync();

	/**
	 * Is shadow enabled.
	 */
	static bool isShadowEnable();

	/**
	 *	Is anti-aliasing enabled.
	 */
	static bool isAntiAliasingEnable();
};

#endif
