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
#ifndef _VD_RENDERING_API_CACHE_H_
#define _VD_RENDERING_API_CACHE_H_ 1
#include"../VDDef.h"
#include"../VDPrerequisites.h"

/**
 *
 */
class VDDECLSPEC VDRenderingAPICache{
public:

	/**
	 *
	 */
	static void VDAPIENTRY init(unsigned int numThreads);

	/**
	 *
	 */
	static void VDAPIFASTENTRY disable(void);

	/**
	 *
	 */
	static void VDAPIFASTENTRY enable(void);

	/**
	 *	@Return
	 */
	static bool VDAPIFASTENTRY isEnabled(void);


	/**
	 *	@Return
	 */
	static bool VDAPIFASTENTRY isDisable(void);

	/**
	 *
	 */
	static void VDAPIENTRY resetCache(void);


	/**
	 *
	 */
	static void VDAPIENTRY setClearColor(float red, float green, float blue, float alpha);

	/**
	 *
	 */
	static void VDAPIENTRY setViewport(int x, int y, int width, int height);


	/**
	 *
	 */
	static void VDAPIENTRY bindTexture(unsigned int target, int texture, unsigned int index);


	/**
	 *	Bind textures
	 *	\first active
	 *	\count
	 *	\textures
	 */
	static void VDAPIENTRY bindTextures(unsigned int first, int count, const int* textures);


	/**
	 *
	 */
	static void VDAPIENTRY bindSampler(unsigned int sampler);

	/**
	 *
	 */
	static void VDAPIFASTENTRY bindProgram(unsigned int program);
	static unsigned int VDAPIENTRY currentBindedProgram(void);

	/**
	 *
	 */
	static void VDAPIENTRY setCurrentProgram(const VDShader* shader);
	static void VDAPIENTRY getCurrentProgram(void);


	/**
	 *
	 */
	static void VDAPIFASTENTRY pushFrameBuffer(unsigned int target, unsigned int framebuffer);
	static void VDAPIFASTENTRY popFrameBuffer(void);

	/**
	 *
	 */
	static void VDAPIFASTENTRY bindFramebuffer(unsigned int target, unsigned int framebuffer);



	/**
	 *
	 */
	static void VDAPIFASTENTRY bindVertexArrayObject(unsigned int array);

	/**
	 *
	 */
	static void VDAPIFASTENTRY bindBuffer(unsigned int target, unsigned int buffer);

	/**
	 *
	 */
	static void VDAPIENTRY bindBufferBase(unsigned int target, unsigned int index, unsigned int buffer);



	/**/
	static void VDAPIENTRY bindRenderBuffer(unsigned int target, unsigned int renderbuffer);
	static unsigned int VDAPIENTRY getBindedRenderBuffer(void);





	/*
	 *	Set rendering state.
	 *//*	TODO add thread or opengl context, in respect to which context, or a id.*/
	static void VDAPIENTRY setState(unsigned int state, int enabled);

	/*
	 *
	 *	@Return
	 */
	static unsigned int VDAPIFASTENTRY getState(unsigned int state);



	//static void VDAPIENTRY setState

};

#endif
