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
#ifndef _VD_INTERNAL_TEXTURE_ALGORITHMIC_H_
#define _VD_INTERNAL_TEXTURE_ALGORITHMIC_H_ 1
#include "../Rendering/VDColor32.h"
#include "../VDSystem.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 *
 */
VDDECLSPEC int VDIntGenRandomTexture(unsigned char **pixelResult, unsigned int Width, unsigned int Height,
									 unsigned int TextureFormat);

/**
 *
 */
VDDECLSPEC int VDIntGenColorTexture(unsigned char **pixelResult, unsigned int Width, unsigned int Height,
									unsigned int TextureFormat, unsigned char *colors);

/**
 *
 */
VDDECLSPEC int VDIntGenLinearTexture(unsigned char **pixelResult, unsigned int Width, unsigned int Height,
									 unsigned int TextureType, unsigned char *colours, unsigned int from = 0,
									 unsigned int to = 0, int vertical = 0);

/**
 *
 */
VDDECLSPEC int VDIntGenChecker(unsigned char **pixelsResult, unsigned int Width, unsigned int Height,
							   int CheckerXDimension, int CheckerYDimension, unsigned int TextureType,
							   unsigned int TextureFlag = 0x0);

/**
 *
 */
VDDECLSPEC int VDIntGenChecker2(unsigned char **pixelsResult, unsigned int Width, unsigned int Height,
								int CheckerXDimension, int CheckerYDimension, const VDColor32 &firstCheckerColor,
								const VDColor32 &secondCheckerColor, unsigned int TextureType,
								unsigned int TextureFlag = 0x0);

/**
 *
 */
VDDECLSPEC int VDIntGenGridTexture(unsigned char **pixelResult, unsigned int Width, unsigned int height,
								   unsigned int gridX, unsigned int gridY, unsigned int thickness,
								   const unsigned char *Backcolours, const unsigned char *foreColours,
								   unsigned int TextureFormat);

/**
 *
 */
VDDECLSPEC int VDIntConvertToAlphaMap(unsigned char **pixelResult, const unsigned char *templateTexture,
									  unsigned int Width, unsigned int Height, unsigned int TextureType);

/**
 *
 */
VDDECLSPEC int VDIntConvertToNormalMap(unsigned char **pixelResult, const unsigned char *templateTexture,
									   unsigned int Width, unsigned int Height, unsigned int TextureType, float Slope,
									   float bumpiness);
VDDECLSPEC int VDIntConvertToDisplaceMap(unsigned char **pixelResult, const unsigned char *templateTexture,
										 unsigned int Width, unsigned int Height, unsigned int TextureType);
VDDECLSPEC int VDIntConvertToInvert(unsigned char **pixelResult, const unsigned char *templateTexture,
									unsigned int Width, unsigned int Height, unsigned int TextureType);

VDDECLSPEC int VDIntConvertToGrayScale(unsigned char **pixelResult, const unsigned char *templateTexture,
									   unsigned int Width, unsigned int Height, unsigned int TextureType);
VDDECLSPEC int VDIntBlendTextures(unsigned char **pixelResult, unsigned char *C_templateTexture,
								  unsigned char *t_templateTexture, unsigned int Width, unsigned int Height,
								  unsigned int TextureType, float Mix);

/**
 *
 */
VDDECLSPEC unsigned int VDIntGetTextureBpp(const unsigned int TextureFlag);

/**
 *
 */
VDDECLSPEC int VDIntMallocTexture(void **data, unsigned int Width, unsigned int Height, unsigned int TextureFormat);

#ifdef __cplusplus
}
#endif

#endif
