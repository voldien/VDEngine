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
#ifndef _VD_CUBE_MAP_TEXTURE_H_
#define _VD_CUBE_MAP_TEXTURE_H_ 1
#include"../VDRenderBuffer.h"
#include"VDTexture.h"
#include"VDTexture2D.h"

/**
 *
 */
class VDDECLSPEC VDCubeMap : public VDTexture {
public:

	VDCubeMap();
	VDCubeMap(const VDCubeMap& cubemap);
	VDCubeMap(unsigned int size, VDTexture::TextureFormat format = VDTexture::eRGB);
	VDCubeMap(const char* alignTexture);
	VDCubeMap(const char* right, const char* left, const char* top, const char* bottom, const char* far, const char* near, unsigned int bitFlag = VDTexture::eCompressed | VDTexture::eMipMapping);
	~VDCubeMap();

	/**
	 *	@Return
	 */
	unsigned int VDAPIENTRY generate(const char* right,
				const char* left,
				const char* top,
				const char* bottom,
				const char* far,
				const char* near,
				unsigned int bitFlag = VDTexture::eCompressed | VDTexture::eMipMapping);

	/**
	 *	@Return
	 */
	unsigned int VDAPIENTRY generate(const char* alignTexture, unsigned int bitFlag = VDTexture::eCompressed | VDTexture::eMipMapping);

public:	/*	Static methods.	*/

	/**
	 *	@Return
	 */
	static VDQuaternion getCubePlaneQuaternion(unsigned int target);

	/*
	 *
	 */
	static VDCubeMap* VDAPIENTRY createErrorCubeMap();
};
#endif
