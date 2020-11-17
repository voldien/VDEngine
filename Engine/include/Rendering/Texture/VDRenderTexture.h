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
#ifndef _VD_RENDER_TEXTURE_H_
#define _VD_RENDER_TEXTURE_H_ 1
#include "VDTexture.h"
#include "VDTexture2D.h"

/**
 *
 */
class VDDECLSPEC VDRenderTexture : public fragcore::FrameBuffer {
public:
	enum Template{
		Color 		= 0x1,
		Luminance 	= 0x2,
		ShadowMapping 	= 0x3,
		Stencil 	= 0x4,
		DetphStencil 	= 0x5,
	};

	enum Attachment{
		DepthAttachment 	= 0x8D00,
		StencilAttachment 	= 0x8D20,
		ColorAttachment0 	= 0x8CE0,
		DepthStencilAttachment = 0x821A,	/*	GL_DEPTH_STENCIL_ATTACHMENT	*/
	};
	VDRenderTexture(void);
	VDRenderTexture(const VDRenderTexture& renderTexture);
	VDRenderTexture(unsigned int width, unsigned int height, unsigned int SurfaceFormat = VDTexture::eRGB, unsigned int SurfaceinternalFormat = VDTexture::eRGB, unsigned int SurfaceType = VDTexture::eUnsignedByte, unsigned int mipMap = 0);
	~VDRenderTexture(void);

protected:	/*	Attributes.	*/

	unsigned int framebuffer;	/*	Framebuffer unqiue identifier.	*/


public:	/*	Public methods.	*/

	/**
	 *	Release resources.
	 */
	virtual void VDAPIENTRY release(void);

	/**
	 *	@Return true if framebuffer id is an framebuffer object.
	 */
	bool VDAPIENTRY isValid(void)const;

	/*
	 *
	 */
	void VDAPIENTRY init(Attachment attachment, VDTexture::TextureFormat format, const VDSize& size);

	/**
	 *	Resize Texture connected to the framebuffer. current
	 *	data will be overwritten by 0.
	 */
	void VDAPIENTRY resize(unsigned int width, unsigned int height, unsigned int layer = 1);

	/*
	 *	Set number of samples.
	 */
	void VDAPIENTRY setSamples(unsigned int sample);

	/*
	 *	TODO rename perhaps!
	 *	@Return
	 */
	int VDAPIENTRY getSamples(void);

	/*
	 *	Get color render buffer.
	 *	@Return
	 */
	VDRenderBuffer colorBuffer(void);

	/*
	 *
	 *	@Return
	 */
	VDRenderBuffer depth(void);

	/*
	 *
	 *	@Return
	 */
	VDRenderBuffer stencil(void);

	/**
	 *
	 */
	void VDAPIENTRY setTextureAttachment(Attachment attachment, VDTexture* texture);

	/**
	 *
	 */
	void VDAPIENTRY setAttachment(Attachment attachment, VDRenderBuffer* renderbuffer);

	/*
	 *
	 *	@Return
	 */
	void VDAPIENTRY setAttachment(unsigned int attachment);


	/*
	 *
	 *	@Return
	 */
	VDTexture VDAPIENTRY getTextureAttachment(int index, Attachment attachment = ColorAttachment0);

	/*
	 *
	 *	@Return
	 */
	unsigned int VDAPIENTRY getAttachmentNative(int index, unsigned int attachment = ColorAttachment0);


	/*
	 *
	 *	@Return
	 */
	VDRenderBuffer VDAPIENTRY getRenderBuffer(int index, Attachment attachment = ColorAttachment0);

	/*
	 *
	 */
	void VDAPIENTRY bind(void);

	/*
	 *
	 */
	void VDAPIENTRY unBind(void);

	/*
	 *
	 */
	void VDAPIENTRY bindTextures(unsigned int startActive = 0);

	/*
	 *
	 */
	void VDAPIENTRY blitTo(VDRenderTexture* framebuffer);

	/*
	 *
	 */
	void VDAPIENTRY read(void);

	/*
	 *
	 */
	void VDAPIENTRY write(void);

	/**
	 *	Clear all attachment buffers.
	 */
	void VDAPIENTRY clear(void);

	/**
	 *	@Return true if rendertexture is a cubemap.
	 */
	bool VDAPIFASTENTRY isCubemap(void);

	/**
	 *	@Return true if rendertexture is a 3D texture.
	 */
	bool VDAPIFASTENTRY isVolume(void);


	/**
	 *	@Return
	 */
	inline unsigned int getFramebuffer(void)const{
		return this->framebuffer;
	}

	/**
	 *
	 */
	unsigned int getAttachemtIndices(Attachment attachment, int* indices);

	/**
	 *	Get number of attachment attached to
	 *	the framebuffer.
	 *	@Return
	 */
	unsigned int VDAPIENTRY getNumOfAttachment(void);

	/**/
	bool VDAPIENTRY isColorAttached(Attachment attachment = Attachment::ColorAttachment0);
	bool VDAPIENTRY isDepthAttached(void);
	bool VDAPIENTRY isStencilAttached(void);

	/*
	 *	Get number of renderbuffer attached to
	 *	the framebuffer.
	 *	@Return
	 */
	unsigned int VDAPIENTRY getNumOfRenderBuffer(void);

	/*
	 *	Check framebuffer error.
	 *	@Return
	 */
	static unsigned int VDAPIENTRY checkError(void);

	// static unsigned int VDAPIENTRY getMaxColorAttachment(void){
	// 	return VDRenderTexture::ColorAttachment0 + VDSystemInfo::getCompatibility()->sMaxColorAttachments;
	// }

public:	/*	Factory methods.	*/

	/**
	 *	Create Color Texture.
	 *
	 *	@Return
	 */
	static VDRenderTexture* colorTexture(unsigned int width, unsigned int height, unsigned int SurfaceFormat = VDTexture::eBGRA, unsigned int SurfaceinternalFormat = VDTexture::eRGBA, unsigned int SurfaceType = VDTexture::eUnsignedByte, unsigned int MipMap = 0);

	/*
	 *
	 *	@Return
	 */
	static VDRenderTexture* LuminanceTexture(unsigned int width, unsigned int height, unsigned int SurfaceType = VDTexture::eUnsignedByte, unsigned int SurfaceFormat = VDTexture::eBGRA, unsigned int SurfaceinternalFormat = VDTexture::eLuminance, unsigned int MipMap = 0);

	/**
	 *
	 *	@Return
	 */
	static VDRenderTexture* StencilTexture(unsigned int width, unsigned int  height, unsigned int SurfaceType = VDTexture::eUnsignedByte, unsigned int SurfaceFormat = VDTexture::eBGRA, unsigned int SurfaceinternalFormat = VDTexture::eLuminance, unsigned int MipMap = 0);

	/**
	 *
	 *	@Return
	 */
	static VDRenderTexture* colorCubeMap(unsigned int width, unsigned int height, unsigned int surfaceType = VDTexture::eUnsignedByte, unsigned int surfaceFormat = VDTexture::eRGBA, unsigned int surfaceInternalFormat = VDTexture::eRGBA, unsigned int mipmap = 0);

	/**
	 *
	 *	@Return
	 */
	static VDRenderTexture* luminanceCubeMap(unsigned int width, unsigned int height, unsigned int surfaceType = VDTexture::eUnsignedByte, unsigned int surfaceFormat = VDTexture::eRGBA, unsigned int surfaceInternalFormat = VDTexture::eRGBA, unsigned int mipmap = 0);

	/**
	 *	Create shadow map framebuffer.
	 *
	 *	@Return
	 */
	static VDRenderTexture* ShadowMap(unsigned int width, unsigned int height, unsigned int SurfaceFormat = VDTexture::eDepthComponent, unsigned int SurfaceinternalFormat = VDTexture::eDepthComponent32, unsigned int surfaceType = VDTexture::eFloat, unsigned int MipMap = 0);

	/**
	 *
	 *	@Return
	 */
	static VDRenderTexture* ShadowCubeMap(unsigned int width, unsigned int height, unsigned int SurfaceFormat = VDTexture::eDepthComponent, unsigned int SurfaceinternalFormat = VDTexture::eDepthComponent32, unsigned int surfaceType = VDTexture::eFloat,  unsigned int MipMap = 0);

	/**
	 *	Create RenderTexture Based on Templates.
	 *	@Return
	 */
	static VDRenderTexture* createRenderTexture(const VDSize& size, unsigned int templateType);


	/**
	 *	@Return
	 */
	static VDRenderTexture* getTemporary(int width, int height, int depthBuffer = 0, VDTexture::TextureFormat format = VDTexture::eRGB, int antiAliasing = 1);


	/**
	 *
	 */
	static void blit(VDRenderTexture* read, VDRenderTexture* write);
};

#endif
