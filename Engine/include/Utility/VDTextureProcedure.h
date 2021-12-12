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
#ifndef _VD_TEXTURE_PROCEDURE_H_
#define _VD_TEXTURE_PROCEDURE_H_ 1
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/VDColor32.h>
#include <SDL2/SDL_stdinc.h>
#include <VDDef.h>

/**
 *
 */
class VDDECLSPEC VDTextureProcedure{
public:

	/**
	 *	Construct
	 *
	 *	@Return
	 */
	static VDTexture2D* VDAPIENTRY genMipmapLevelDebugger(unsigned int mipmapLevel = 6);


	/**
	 *	Create Checker Texture.
	 *
	 *	@Return None nullptr pointer if
	 */
	static VDTexture2D* VDAPIENTRY genCheckTexture(unsigned int width, unsigned int height, unsigned int checkWith, unsigned int checkHeight, unsigned int  SurfaceinternalFormat = VDTexture::eLuminance, unsigned int  SurFaceFormat = VDTexture::eLuminance, unsigned int  SurfaceType = VDTexture::eUnsignedByte, unsigned int  MipMap = VDTexture2D::eMipMapping);

	/**
	 *	Create Checker Texture
	 *
	 *	@Return
	 */
	static VDTexture2D* VDAPIENTRY genCheckerTexture2(unsigned int width, unsigned int height, unsigned int checkWidth, unsigned int checkerHeight, const VDColor32& foreColor, const VDColor32& backColor, unsigned int SurfaceinternalFormat = VDTexture::eLuminance, unsigned int  SurFaceFormat = VDTexture::eLuminance, unsigned int  SurfaceType = VDTexture::eUnsignedByte, unsigned int  MipMap = VDTexture2D::eMipMapping);

	/**
	 *	Create Linear createGrid Texture
	 *	@Return
	 */
	static VDTexture2D* VDAPIENTRY genLinearGridTexture(unsigned int width, unsigned int height, unsigned int linearX, unsigned int linearY, unsigned int  thickness,const VDColor32& backColor,const VDColor32& foreColor, unsigned int SurfaceinternalFormat = VDTexture::TextureFormat::eRGB, unsigned int  SurFaceFormat = VDTexture::TextureFormat::eRGB, unsigned int  SurfaceType = VDTexture::eUnsignedByte, unsigned int  MipMap = VDTexture2D::eMipMapping);

	/**
	 *	Create Color Texture
	 *	@Return
	 */
	static VDTexture2D* VDAPIENTRY genColorTexture(unsigned int width, unsigned int height, const VDColor32& color, unsigned int SurfaceinternalFormat = VDTexture::TextureFormat::eRGB, unsigned int  SurFaceFormat = VDTexture::TextureFormat::eRGB, unsigned int  SurfaceType = VDTexture::eUnsignedByte, unsigned int  MipMap = VDTexture2D::eMipMapping | VDTexture::eCompressed);

	/*
	 *	Create Random Texture
	 *	@Return
	 */
	static VDTexture2D* VDAPIENTRY RandomTexture(unsigned int width, unsigned int height, unsigned int SurfaceinternalFormat = VDTexture::TextureFormat::eRGB, unsigned int  SurFaceFormat = VDTexture::TextureFormat::eRGB, unsigned int  SurfaceType = VDTexture::eUnsignedByte, unsigned int  MipMap = VDTexture2D::eMipMapping);

	/**
	 *	@Return
	 */
	static VDTexture2D* VDAPIENTRY LinearTexture(unsigned int width, unsigned int height,unsigned int start, unsigned int  end, VDColor32 color, unsigned int  SurfaceinternalFormat = VDTexture::TextureFormat::eRGB, unsigned int  SurFaceFormat = VDTexture::TextureFormat::eRGB, unsigned int  SurfaceType = VDTexture::eUnsignedByte, unsigned int  MipMap = SDL_FALSE);

	/**
	 *	@Return
	 */
	static VDTexture2D* VDAPIENTRY genErrorTexture(unsigned int width, unsigned int height, unsigned int SurfaceinternalFormat = VDTexture::TextureFormat::eRGB, unsigned int  SurFaceFormat = VDTexture::TextureFormat::eRGB, unsigned int  SurfaceType = VDTexture::eUnsignedByte, unsigned int flag = VDTexture2D::eMipMapping | VDTexture::eCompressed);


	/**
	 *	@Return
	 */
	static VDTexture2D* VDAPIENTRY blackTexture();

	/**
	 *	@Return
	 */
	static VDTexture2D* VDAPIENTRY whiteTexture();

};

#endif
