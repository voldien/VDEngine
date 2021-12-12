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
#ifndef _VD_RENDER_BUFFER_H_
#define _VD_RENDER_BUFFER_H_ 1
#include "Texture/VDTexture.h"
#include "../VDDef.h"

/**
 *	Renderer buffer assoicated with framebuffer object.
 */
class VDDECLSPEC VDRenderBuffer : public VDAssetObject{
	friend class VDRenderTexture;
public:
	VDRenderBuffer();
	explicit VDRenderBuffer(unsigned int buffer);
	VDRenderBuffer(const VDRenderBuffer& buffer);

	/**
	 *	Release resources assoicated with the
	 *	object.
	 */
	virtual void VDAPIENTRY release();

	/**
	 *
	 */
	void VDAPIENTRY bind();

	/**
	 *
	 */
	void VDAPIENTRY unbind();

	/**
	 *	@Return true if renderbuffer is valid.
	 */
	bool VDAPIENTRY isValid()const;

	/**
	 *
	 */
	void VDAPIENTRY setStorage(unsigned int width, unsigned int height, VDTexture::TextureFormat format);

	/**
	 *
	 */
	void VDAPIENTRY setSampleStorage(unsigned int samples, unsigned int width, unsigned int height, VDTexture::TextureFormat format);


	/**
	 *	@Return
	 */
	VDTexture::TextureFormat VDAPIENTRY getInternalFormat();


	inline unsigned int getRendererID()const{
		return this->renderer;
	}

protected:

	inline void setRenderId(unsigned int render){
		this->renderer = render;
	}

private:	/*	Attributes.	*/

	unsigned int renderer;	/*	Renderer buffer unique identifier.	*/
};

#endif
