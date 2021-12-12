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
#ifndef _VD_TEXTURE_H_
#define _VD_TEXTURE_H_ 1
#include"../../VDSystem.h"
#include"../../Asset/VDAssetObject.h"

/**
 *	Base texture class.
 */
class VDTexture : public fragcore::Texture {
	friend class VDRenderTexture;
public:
	enum TextureFlag{
		eCompressed 	= (1 << 0),
		eMipMapping 	= (1 << 1),
		eAniostropic 	= (1 << 2),
		eSrgb 		= (1 << 3),
	};

	enum Wrap{
		eWrapS = 0x1,
		eWrapT = 0x2,
		eWrapR = 0x4,
	};

	/*
	 *
	 */
	enum TexFilter{
		eMin = 0x1,
		eMag = 0x2,
	};

	/*
	 *
	 */
	enum WrapMode{
		eClamp = (1 << 4),
		eRepeat = (1 << 5),
		eClampBorder = (1 << 6),
		eClampEdge = (1 << 7),
	};

	enum FilterMode{
		eLinear = (1 << 8),
		eNearest = (1 << 9),
	};

	enum TextureTarget {
		eTexture1D 		= 0x0DE0,				/*	GL_TEXTURE_1D*/
		eTexture2D 		= 0x0DE1,				/*	GL_TEXTURE_2D	*/
		eTexture2DMultiSample 	= 0x9100,		/*	*/
		eCubeMap 		= 0x8513,					/*	GL_TEXTURE_CUBE_MAP	*/
		eCubeMapArray 		= 0x9009,
		eTexture1DArray 	= 0x8C18,			/**/
		eTexture2DArray 	= 0x8C1A,			/**/
		eTexture2DArrayMultiSample = 0x9102,/**/
		eTexture3D 		= 0x806F,				/*	GL_TEXTURE_3D	*/
		eTextureBuffer 		= 0x8C2A,			/*	GL_TEXTURE_BUFFER	*/
	};

	enum TextureFormat{	/*	TODO fetch the const value!*/
		eDefaultFormat 		= -1,
		eDepthComponent 	= 0x1902,		/*	GL_DEPTH_COMPONENT	*/
		eDepthComponent16 	= 0x81A5,		/*	GL_DEPTH_COMPONENT16	*/
		eDepthComponent24 	= 0x81A6,		/*	GL_DEPTH_COMPONENT24	*/
		eDepthComponent32 = 0x81A7,		/*	GL_DEPTH_COMPONENT32	*/
		eLuminance = 0x1909,			/**/
		eLumiannceAlpha = 0x190A,		/**/
		eAlpha = 0x1906,				/**/
		eRed = 0x1903,
		eRGB = 0x1907,					/**/
		eRGB8 = 0x8051,					/**/
		eRGBA = 0x1908,					/**/
		eBGR = 0x806F,					/**/
		eBGRA = 0x80E1,					/**/
		eRGB16 = 0x8054,				/**/
		eRGBA16 = 0x805B,				/**/
		eLuminance16 = 0x8042,			/**/
		eAlpha16 = 0x803E,				/**/
		eRGB32I = 0x8D83,				/**/
		eRGB32F = 0x8815,				/*	GL_RGB32F	*/
		eRGBA32I = 0x8D82,				/**/
		eRGBA32F = 0x8814,				/*	GL_RGBA32F	*/
		eLuminance32,					/**/
		eSRGB = 0x8C40,					/**/
		eSRGBA = 0x8C42,				/**/
		eCompressRBG = 0x84ED,			/**/
		eCompressRGBA = 0x84EE,			/**/
		eCompressLuminance_DXT1,		/**/
		eCompressRGB_DXT1 = 0x83F0,		/**/
		eCompressRGBA_DXT1 = 0x83F1,	/**/
		eCompressRGBA_DXT3 = 0x83F2 ,	/**/
		eCompressRGBA_DXT5 = 0x83F3,	/**/

		eCompressRGB8_ETC2 = 0x9274,	/**/
		eCompressRGB8_PUNCHTHROUGH_ETC2 = 0x9276,//GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 ,


		eCubeMapPositiveX = 0x8515,
		/*
		eCubeMapPositiveX = 0x8516,
		eCubeMapPositiveX = 0x8517,
		eCubeMapPositiveX = 0x8518,
		eCubeMapPositiveX = 0x8519,
		eCubeMapPositiveX = 0x851A,
		*/
	};

	enum CompressionFormat{
		eDefault = 0,
		eBPTC,				/*ARB_texture_compression_bptc*/
		eRGTC,				/**/
		eDXT1,
		eLATC,
		eEGTC,
		eS3TC,
		eVTC,
		eRTC,
		eDXT3,
		eFXT1,
	};

	enum TextureDataType{
		eUnsignedByte 	= 0x1401,	/*	GL_UNSIGNED_BYTE	*/
		eByte 		= 0x1400,	/*	GL_BYTE		*/
		eUnsignedShort 	= 0x1403,	/*	GL_UNSIGNED_SHORT	*/
		eFloat 		= 0x1406,	/*	GL_FLOAT	*/
		eHalfFloat 	= 0x140B,	/*	GL_HALF_FLOAT	*/
		eFixedFloat,			/*	*/
	};

	VDTexture();
	VDTexture(const VDTexture& texture);
	VDTexture(TextureTarget target);
	VDTexture(unsigned int width, unsigned int SurfaceinternalFormat, unsigned int SurFaceFormat = TextureFormat::eRGB, unsigned int SurfaceType = eUnsignedByte, unsigned int mipmapping = eMipMapping);
	~VDTexture();

	/**
	 *	Release all resource associated with texture
	 *	object.
	 */
	virtual void VDAPIENTRY release();

	/**
	 *	is Texture Valid
	 *
	 *	@Return true if valid texture.
	 */
	bool VDAPIFASTENTRY isValid() const;

	/**
	 *	Is Texture Compressed
	 *
	 *	@Return true if compressed.
	 */
	bool VDAPIFASTENTRY isCompressed() const;

	/**
	 *	Copy current framebuffer to texture.
	 */
	void VDAPIENTRY copy();

	/**
	 *	Copy section of current framebuffer to texture.
	 */
	void VDAPIENTRY copy(unsigned int xoffset, unsigned int yoffset);

	/**
	 *	Get
	 */
	TextureFormat VDAPIENTRY getInternalFormat() const;

	/**
	 *
	 */
	void VDAPIENTRY setInternalFormat(TextureFormat format, unsigned int type = -1);

	/**
	 *	Get texture size in bytes based on TODO .
	 *
	 *	@Return
	 */
	int VDAPIENTRY getTextureSize(unsigned int level = 0) const;

	/**
	 *	@Return	size n bytes.
	 *
	 */
	int VDAPIENTRY getCompressedTextureSize(unsigned int level = 0) const;

	/**
	 *
	 */
	void VDAPIENTRY compress(CompressionFormat type = CompressionFormat::eDefault);

	/**
	 *	bind on a reserved active unit.
	 *
	 */
	void VDAPIENTRY bind()const;

	/*
	 *
	 */
	void VDAPIENTRY bind(unsigned int active);

	/**
	 *	unBind All Texture of target texture type.
	 */
	void VDAPIENTRY unBind()const;


	/**
	 *
	 */
	void VDAPIENTRY setWrapMode(WrapMode mode);

	/**
	 *
	 *	@Return
	 */
	WrapMode VDAPIENTRY getWrapMode()const;

	/**
	 *
	 */
	void VDAPIENTRY setFilterMode(FilterMode mode);

	/**
	 *	@Return
	 */
	FilterMode VDAPIENTRY getFilterMode()const;

	/**
	 *	Set base level of texture.
	 */
	void VDAPIENTRY setBaseLevel(unsigned int level);

	/**
	 *	Get Base Level of Texture.
	 *	@Return
	 */
	int VDAPIENTRY getBaseLevel()const;

	/**
	 *
	 */
	/*TODO perhaps rename */
	void VDAPIENTRY setMaxMipMaps(int levels);

	/**
	 *	@Return
	 */
	/*TODO perhaps rename */
	int VDAPIENTRY getMaxMipMaps();


	/**
	 *	Update mipmapping.
	 */
	void VDAPIENTRY updateMipMap();

	/**
	 *
	 */
	void VDAPIENTRY setMipMapBias(float bias);

	/**
	 *
	 *	@Return
	 */
	float VDAPIENTRY getMipMapBias()const;


	/**
	 *	Create Alpha Channel of current Textures Luminance.
	 */
	void VDAPIENTRY useRGBAlpha();

	/**
	 *	Enable or Disable SRGB.
	 */
	void VDAPIENTRY isSRGB(unsigned int isSRGB)const;

	/**
	 *	set anisotropy texture level
	 */
	void VDAPIENTRY setAnisoLevel(float ansi);

	/**
	 *	Get anisotropy texture level.
	 *	@Return
	 */
	float VDAPIENTRY getAnsioLevel()const;

	inline int width()const{
		return this->mWidth;
	}


	/**
	 *
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getCompressType(unsigned int internalFormat, CompressionFormat compression = CompressionFormat::eDefault)const;

	/**
	 *
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getNoneCompressType(unsigned int internalFormat)const;

	/**
	 *	Get GLenum Of Current internal SRGB
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getSRGBFormat(unsigned int internalFormat)const;

	/**
	 *	@Return	TODO check if needed.
	 */
	TextureDataType VDAPIENTRY getType();

	/**
	 *	Set texture target.
	 *	@Return
	 */
	void VDAPIFASTENTRY setTextureTarget(VDTexture::TextureTarget textureTarget);


public:

	/**
	 *
	 */
	unsigned int VDAPIFASTENTRY getTarget() const;

	/**
	 *
	 */
	void VDAPIFASTENTRY setTextureID(unsigned int idTexture);

	/**
	 *
	 */
	unsigned int VDAPIFASTENTRY getTexture() const;

public:

	/**
	 *
	 */
	void VDAPIENTRY setPixelData(unsigned int level, unsigned int width, unsigned int height, unsigned int layer, VDTexture::TextureFormat internal, VDTexture::TextureFormat format, VDTexture::TextureDataType type, void* pixels, int plane = -1);

	/**
	 *
	 */
	void VDAPIENTRY setSubData(unsigned int width, unsigned int height, unsigned int layer, VDTexture::TextureFormat format, VDTexture::TextureFormat internal, VDTexture::TextureDataType type, void* data);


	/**
	 *	@Return
	 */
	void* VDAPIENTRY getPixelData(unsigned int level, VDTexture::TextureFormat format, VDTexture::TextureDataType type);


public:

	/**
	 *
	 *	@Return
	 */
	VDTexture* VDAPIENTRY isTexture()const{
		return reinterpret_cast<VDTexture*>((VDTexture*)this);
	}

	/**
	 *
	 *	@Return
	 */
	VDTexture2D* VDAPIENTRY isTexture2D()const{
		return reinterpret_cast<VDTexture2D*>((VDTexture*)this);
	}


protected:

	void setWidth(unsigned int width){
		this->mWidth = width;
	}

protected:	/*	Attributes.	*/

	TextureTarget target;	/*	Texture target.	*/
	unsigned int texture;	/*	Texture identification value.	*/
	unsigned int mWidth;	/*	*/

public:

	/**
	 *	Get max texture anisotropy for this hardware.
	 */
	static float getMaxTextureAnisotropy();

};

#endif
