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
#ifndef _VD_TEXTURE2D_H_
#define _VD_TEXTURE2D_H_ 1
#include<FragCore.h>
#include"../../VDSystem.h"
#include"../../DataStructure/VDDataStructure.h"
#include"./../VDColor32.h"
#include"VDTexture.h"

/**
 *
 */
class VDDECLSPEC VDTexture2D : public fragcore::Texture {
	friend class VDRenderTexture;
public:
// 	VDTexture2D();
// 	VDTexture2D(const VDTexture2D& texture);
// 	VDTexture2D(unsigned int width, unsigned int height,
// 	        unsigned int SurfaceinternalFormat = VDTexture::eRGB,
// 	        unsigned int SurFaceFormat = VDTexture::eRGB,
// 	        unsigned int SurfaceType = VDTexture::eUnsignedByte,
// 	        unsigned int flag = MipMapping);
// 	VDTexture2D(const char* path, unsigned int TextureFlag = eMipMapping | VDTexture::eCompressed);
// 	~VDTexture2D();

// protected:	/*	*/
// 	unsigned int format;		/*	Texture format.	*/

// 	/*
// 	 *	internal Texture Component,
// 	 */
// 	unsigned int internalFormat;	/**/

// 	/*
// 	 *	Texture Data Type;
// 	 */
// 	unsigned int type;		/**/

// 	/*
// 	 *	Texture Flag Stats
// 	 */
// 	unsigned short flag;		/**/

// 	/*
// 	 *	Texture2D Height In pixels.
// 	 */
// 	unsigned int mHeight;		/*	*/

// public:

// 	/**
// 	 *	Release resources.
// 	 */
// 	virtual void VDAPIENTRY release();


// 	/*
// 	 *
// 	 */
// 	unsigned int bpp()const;

// 	inline unsigned int height()const{
// 		return this->mHeight;
// 	}


// public:
// 	/*
// 	 *
// 	 */
// 	void setProperty(unsigned int TexturePropertyType, int TypeValue);

// 	/**
// 	 *
// 	 */
// 	void setProperty(unsigned int TexturePropertyType, float TypeValue);

// 	/**
// 	 *
// 	 */
// 	unsigned int getProperty(unsigned int TexturePropertyType);

// 	/**
// 	 *
// 	 *	@Return
// 	 */
// 	void* VDAPIENTRY pixels(unsigned int level = 0, VDTexture::TextureFormat intformat = (VDTexture::TextureFormat)-1, int types = -1);	/*	TODO relocate to VDTexture*/

// 	/*
// 	 *	update Data from Loading Reference.
// 	 */
// 	void update();

// 	/**
// 	 *
// 	 */
// 	void setTextureFormat(VDTexture::TextureFormat textureFormat);






// 	/**/
// 	unsigned int loadTexture(const char* path, unsigned int textureBitFlag = eMipMapping);


// public:	/*	Static methods.	*/

	/**
	 *	@Return
	 */
	static unsigned int loadTextureContent(const char* path,
	        unsigned char** pixel, unsigned int * Width, unsigned int * Height,
	        unsigned int * bpp, unsigned int * TextureForamt = nullptr,
	        unsigned int * internalTextureFormat = nullptr,
	        unsigned int * TextureType = nullptr, unsigned int MipMap = 1);

	/**
	 *	@Return
	 */
	static unsigned int saveTextureContent(const char* path,
	        VDTexture2D* texture, unsigned int TextureFormat);

	/**
	 *	@Return
	 */
	static unsigned int saveTextureContent(const char* path,
	        unsigned char* PixelBuffer, unsigned int Width, unsigned int Height,
	        unsigned int TextureinternalFormat, unsigned int TextureType,
	        unsigned int saveFormat);

	/**
	 *	@Return
	 */
	inline static VDTexture2D* findTexture(const char* fileName) {
		return VDTexture2D::existTexture(fileName);
	}

	/**
	 *	@Return
	 */
	static VDTexture2D* existTexture(const char* path);

	/**/
	static void  assignTexture(VDTexture2D* texture, const char* pathName = "");
};

extern std::map<const char*, VDTexture2D*> textureCollection;
#endif
