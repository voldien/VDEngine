/**
    Copyright (C) 2015  Valdemar Lindberg

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
#ifndef _VD_POSTEFFECTS_H_
#define _VD_POSTEFFECTS_H_ 1
#include "VDMaterial.h"
#include "../VDSystem.h"

/**
 *	Post effect for performing post effect
 *	on framebuffer output texture.
 */
class VDDECLSPEC VDPostEffect : public VDMaterial{
public:

	enum Requisity{
		Color 		= 0x1,	/*	*/
		Depth 		= 0x2,	/*	*/
		Stencil 	= 0x4,	/*	*/
		Intensity 	= 0x8	/*	*/
	};

	enum BlendMode{
		None		= 0x0,	/**/
		Multiply	= 0x1,	/*	*/
	};

	VDPostEffect(void);
	VDPostEffect(const VDPostEffect& post);
	VDPostEffect(const char* vertexShader, const char* fragmentShader);
	~VDPostEffect(void);

private:	/*	Attributes.	*/

	unsigned int flag;		/*	Post Effect Flags stats for behavior*/
	unsigned int sample;	/*	Number of Sampling.	*/
	int enable;		/*Post Effect Enable for PostProcessing The Screen.*/

public:

	bool isEnabled(void)const;
	unsigned int getsNumSample(void)const;
	void setNumSample(unsigned int sample);

	/**
	 *
	 */
	virtual void VDAPIENTRY render(void);

	/*	TODO add virtual methods for add support for inheritance the post object and deleage the responsiblity
	 * to the class inheritnace the post effect class.	*/


public:	/*	Static methods.	*/


	static std::vector<VDPostEffect*> gPostProcessingObject;

	/*
	 *	Built in Post Processing effect.
	 */

	/*
	 *	Convert Current Frame To GrayScale.
	 *	@Return
	 */
	static VDPostEffect* VDAPIENTRY grayScale(void);

	/**
	 *
	 *	@Return
	 */
	static VDPostEffect* VDAPIENTRY sepia(void);				//  sepia Color Filtering.

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY vineta(void);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY antialiasing(void);			//	antialiasing Frame

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY FSAA(unsigned int sampler);			//  Full Screen antialiasing.

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY invert(void);				//	invert Current Frame RGB. (1.0f - RGB) 

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY noise(void);				//	noise On Screen. Exemple TV noise 

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY blur(unsigned int samplerCount = 5, float Radius = 4.5f);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY colorCorrection(const VDColor& ColorBlend = VDColor(1.0f, 1.0f, 1.0f, 1.0f));

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY bloom(void);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY DOF(float FocusDistance = 0.65f, float FocusLenght = 0.55f);
	static VDPostEffect* VDAPIENTRY bokeh(void);

	/**
	 *	Screen space reflection.
	 */
	static VDPostEffect* VDAPIENTRY ssr(void);

	/**
	 *	Depth
	 */
	static VDPostEffect* VDAPIENTRY DepthBuffer(void);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY GammaCorrection(void);

	/**
	 *	Screen Space Ambient
	 */
	static VDPostEffect* VDAPIENTRY SSAO(void);

	/*
	 *	screen Space
	 */
	static VDPostEffect* VDAPIENTRY HBAO(void);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY PixelLate(void);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY LightShattering(void);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY Fog(const VDColor& fogColor, float start, float end, float density, unsigned char mode = 0);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY motionBlur(void);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY CameraMotionBlur(void);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY glow(unsigned int samplerCount = 1, float Radius = 4.5f);

	/**
	 *	High Dynamic Range
	 */
	static VDPostEffect* VDAPIENTRY HDR(void);

	/**
	 *
	 */
	static VDPostEffect* VDAPIENTRY bilateralFilter(void);
};

#endif
