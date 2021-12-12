#include <Core/VDDebug.h>
#include <GL/glew.h>
#include <malloc.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/VDRenderingAPICache.h>
#include <stddef.h>
#include <VDSystemInfo.h>
#include<Core/Math.h>

VDTexture::VDTexture() : VDAssetObject(){
	this->setTextureTarget(VDTexture::eTexture1D);
	glGenTextures(1, &this->texture);
	this->texture = 0;
	this->mWidth = 0;
}

VDTexture::VDTexture(const VDTexture& texture){
	*this = texture;
}

VDTexture::VDTexture(TextureTarget target) : VDAssetObject(){
	this->setTextureTarget(target);
	glGenTextures(1, &this->texture);
	this->setWrapMode(VDTexture::WrapMode::eRepeat);
	this->setFilterMode(VDTexture::FilterMode::eLinear);
	this->mWidth = 0;
}

VDTexture::VDTexture(unsigned int width, unsigned int SurfaceinternalFormat, unsigned int SurFaceFormat, unsigned int SurfaceType, unsigned int mipMap) : VDAssetObject(){
	this->setTextureTarget(VDTexture::eTexture1D);
	this->mWidth = 0;

	glGenTextures(1,&this->texture);
	this->bind();
	glTexImage1D(this->getTarget(), 0, SurfaceinternalFormat, width, 0, SurFaceFormat,SurfaceType, nullptr);

	this->unBind();
}

VDTexture::~VDTexture(){

}

void VDTexture::release(){
	if(this->isValid()){
		glDeleteTextures(1, &this->texture);
		this->setTextureID(0);
	}
}

void VDTexture::setAnisoLevel(float aniostropic){
	this->bind();
	aniostropic = fragcore::Math::min<float>(aniostropic, (float)VDSystemInfo::getCompatibility()->sMaxAnsio);
	glTexParameterf(this->getTarget(), GL_TEXTURE_MAX_ANISOTROPY_EXT, aniostropic);
}

float VDTexture::getAnsioLevel()const{
	this->bind();
	float pvalue;
	glGetTexParameterfv(this->getTarget(), GL_TEXTURE_MAX_ANISOTROPY_EXT, &pvalue);
	return pvalue;
}

bool VDTexture::isValid()const{
	return (glIsTexture(this->getTexture()) == GL_TRUE);
}

bool VDTexture::isCompressed()const{
	this->bind();
	int compressed;
	glGetTexLevelParameteriv(this->getTarget(), 0, GL_TEXTURE_COMPRESSED_ARB, &compressed);
	return (compressed != 0);
}

void VDTexture::copy(){
	this->bind();
	glCopyTexImage1D(getTarget(), 0, this->getInternalFormat(), 0, 0, this->width(), 0);
}

void VDTexture::copy(unsigned int xoffset, unsigned int yoffset){
	this->bind();
	glCopyTexImage1D(getTarget(), 0, this->getInternalFormat(), xoffset, yoffset, this->width(), 0);
}

VDTexture::TextureFormat VDTexture::getInternalFormat()const{
	VDTexture::TextureFormat internal;
	this->bind();
	glGetTexLevelParameteriv(this->getTarget(), 0, GL_TEXTURE_INTERNAL_FORMAT, (int*)&internal);
	return internal;
}

void VDTexture::setInternalFormat(VDTexture::TextureFormat format, unsigned int type){
	int w, h, l;
	VDTexture::TextureFormat internalformat = format;
	this->bind();

	if(this->getTarget() != VDTexture::eCubeMap){
		glGetTexLevelParameteriv(this->getTarget(), 0, GL_TEXTURE_WIDTH, &w);
		glGetTexLevelParameteriv(this->getTarget(), 0, GL_TEXTURE_HEIGHT, &h);
		glGetTexLevelParameteriv(this->getTarget(), 0, GL_TEXTURE_DEPTH, &l);
	}

	if(format == getInternalFormat()){
		return;
	}

	if(type == -1){

	}

	if(type == VDTexture::eFloat){
		switch(format){
		case VDTexture::eRGB:
			internalformat = VDTexture::eRGB32F;
			break;
		case VDTexture::eRGBA:
			internalformat = VDTexture::eRGBA32F;
		break;
		}
	}

	/*	*/
	switch(this->getTarget()){
	case VDTexture::TextureTarget::eTexture1D:
		glTexImage1D(this->getTarget(), 0, internalformat, w, 0, format, type, nullptr);
		break;
	case VDTexture::TextureTarget::eTexture1DArray:
		glTexImage2D(this->getTarget(), 0, internalformat, w, h, 0, format, type, nullptr);
		break;
	case VDTexture::TextureTarget::eTexture2D:
		glTexImage2D(this->getTarget(), 0, internalformat, w, h, 0, format, type, nullptr);
		break;
	case VDTexture::TextureTarget::eTexture2DArray:
		glTexImage3D(this->getTarget(), 0, internalformat, w, h, l, 0, format, type, nullptr);
		break;
	case VDTexture::TextureTarget::eTexture3D:
		glTexImage3D(this->getTarget(), 0, internalformat, w, h, l, 0, format, type, nullptr);
		break;
	case VDTexture::TextureTarget::eCubeMap:
		for(int x = 0; x < 6; x++){
			glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X + x, 0, GL_TEXTURE_WIDTH, &w);
			glGetTexLevelParameteriv(GL_TEXTURE_CUBE_MAP_POSITIVE_X + x, 0, GL_TEXTURE_HEIGHT, &h);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + x, 0, internalformat, w, h, 0, format, type, nullptr);
		}
		break;
	default:
		break;
	}
}

int VDTexture::getTextureSize(unsigned int level)const{
	int size;
	int w,h,d;
	int r,g,b,a,l,i;
	r = g = b = a = l = i = 0;

	this->bind();
	glGetTexLevelParameteriv(this->getTarget(), level, GL_TEXTURE_WIDTH, 		&w);
	glGetTexLevelParameteriv(this->getTarget(), level, GL_TEXTURE_HEIGHT, 		&h);
	glGetTexLevelParameteriv(this->getTarget(), level, GL_TEXTURE_DEPTH, 		&d);
	glGetTexLevelParameteriv(this->getTarget(), level, GL_TEXTURE_RED_SIZE, 	&r);
	glGetTexLevelParameteriv(this->getTarget(), level, GL_TEXTURE_GREEN_SIZE, 	&g);
	glGetTexLevelParameteriv(this->getTarget(), level, GL_TEXTURE_BLUE_SIZE, 	&b);
	glGetTexLevelParameteriv(this->getTarget(), level, GL_TEXTURE_ALPHA_SIZE, 	&a);
	/*	*/
	if(!VDSystemInfo::getCompatibility()->isGLCore){
		glGetTexLevelParameteriv(this->getTarget(), level, GL_TEXTURE_LUMINANCE_SIZE, 	&l);
		glGetTexLevelParameteriv(this->getTarget(), level, GL_TEXTURE_INTENSITY_SIZE, 	&i);
	}

	return fragcore::Math::clamp<int>(w * h * d * ((r + g + b + a + l + i) / 8), 0, (1 << 30));
}

int VDTexture::getCompressedTextureSize(unsigned int level)const{
	int size;
	this->bind();
	glGetTexLevelParameteriv(this->getTarget(), level, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &size);
	return size;
}

void VDTexture::compress(CompressionFormat format){
	VDTexture::TextureFormat internal;
	VDTexture::TextureFormat compress;
	VDTexture::TextureDataType type = VDTexture::eUnsignedByte;
	int w, h, l;
	char* texel = nullptr;

	if(this->isCompressed()){
		return;
	}

	if(VDSystemInfo::supportTextureCompression(format) == false){
		VDDebug::criticalLog("Compression format not supported.\n");
		return;
	}

	this->bind();
	glGetTexLevelParameteriv(this->getTarget(), 0, GL_TEXTURE_WIDTH, &w);
	glGetTexLevelParameteriv(this->getTarget(), 0, GL_TEXTURE_HEIGHT, &h);
	glGetTexLevelParameteriv(this->getTarget(), 0, GL_TEXTURE_DEPTH, &l);


	/**/
	internal = getInternalFormat();
	compress = (VDTexture::TextureFormat)getCompressType(internal, format);
	unsigned int formatSizeType = sizeof(unsigned char);
	texel = (char*)malloc(formatSizeType * this->getTextureSize(0));
	this->getPixelData(0, internal, type);
	//this->setPixelData(0, )

	/**/
	switch(getTarget()){
	case eTexture1D:
		glGetTexImage(this->getTarget(), 0, internal, VDTexture::eUnsignedByte, texel);
		break;
	case eTexture2D:
	case eTexture2DMultiSample:
		glGetTexImage(this->getTarget(), 0, internal, VDTexture::eUnsignedByte, texel);
		glTexImage2D(this->getTarget(), 0, compress, w, h, 0, internal, VDTexture::eUnsignedByte, texel);
		break;
	case eTexture2DArray:
	case eTexture2DArrayMultiSample:
		glGetTexImage(this->getTarget(), 0, internal, VDTexture::eUnsignedByte, texel);
		break;
	case eCubeMap:
		glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, internal, VDTexture::eUnsignedByte, texel);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0,  0, compress, w, h, 0, internal, VDTexture::eUnsignedByte, texel);
		glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, internal, VDTexture::eUnsignedByte, texel);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1,  0, compress, w, h, 0, internal, VDTexture::eUnsignedByte, texel);
		glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, internal, VDTexture::eUnsignedByte, texel);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2,  0, compress, w, h, 0, internal, VDTexture::eUnsignedByte, texel);
		glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, internal, VDTexture::eUnsignedByte, texel);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3,  0, compress, w, h, 0, internal, VDTexture::eUnsignedByte, texel);
		glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, internal, VDTexture::eUnsignedByte, texel);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4,  0, compress, w, h, 0, internal, VDTexture::eUnsignedByte, texel);
		glGetTexImage(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, internal, VDTexture::eUnsignedByte, texel);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5,  0, compress, w, h, 0, internal, VDTexture::eUnsignedByte, texel);
		break;
	}


	this->updateMipMap();
	free(texel);
}

void VDTexture::bind()const{
	/*	bind on a reserved active unit.	*/
	VDRenderingAPICache::bindTexture(this->getTarget(), this->getTexture(), VDSystemInfo::getCompatibility()->sMaxTextureUnitActive - 1);
}

void VDTexture::bind(unsigned int active){
	VDRenderingAPICache::bindTexture(this->getTarget(), this->getTexture(), active);
}

void VDTexture::unBind()const{
	VDRenderingAPICache::bindTexture(target, 0, 0);
}

void VDTexture::setWrapMode(VDTexture::WrapMode mode){
	this->bind();
	unsigned int wrap;
	switch(mode){
	case eClamp:
		wrap = GL_CLAMP;
		break;
	case eClampBorder:
		wrap = GL_CLAMP_TO_BORDER;
		break;
	case eRepeat:
		wrap = GL_REPEAT;
		break;
	case eClampEdge:
		wrap = GL_CLAMP_TO_EDGE;
		break;
	}

	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(getTarget(), GL_TEXTURE_WRAP_R, wrap);
}
VDTexture::WrapMode VDTexture::getWrapMode()const{
	int mode;
	int modet;
	int moder;
	this->bind();
	glGetTexParameteriv(this->getTarget(), GL_TEXTURE_WRAP_S, &mode);
	glGetTexParameteriv(this->getTarget(), GL_TEXTURE_WRAP_T, &modet);
	glGetTexParameteriv(this->getTarget(), GL_TEXTURE_WRAP_R, &moder);
	return (VDTexture::WrapMode)mode;
}

void VDTexture::setFilterMode(FilterMode mode){
	unsigned int filterMode;
	/*	TODO fix for mippapping */
	switch(mode){
	case eLinear:
		filterMode = GL_LINEAR;
		break;
	case eNearest:
		filterMode = GL_NEAREST;
		break;
	}
	this->bind();

	glTexParameteri(getTarget(), GL_TEXTURE_MAG_FILTER, filterMode);
	glTexParameteri(getTarget(), GL_TEXTURE_MIN_FILTER, filterMode);
}
VDTexture::FilterMode VDTexture::getFilterMode()const{
	int filterMode;
	this->bind();
	glGetTexParameteriv(getTarget(), GL_TEXTURE_MAG_FILTER, &filterMode);
	switch(filterMode){
	case GL_LINEAR:
		return VDTexture::FilterMode::eLinear;
	case GL_NEAREST:
		return VDTexture::FilterMode::eNearest;
	default:
		break;
	}
	return (VDTexture::FilterMode)filterMode;
}

void VDTexture::setBaseLevel(unsigned int level){
	this->bind();
	glTexParameteri(this->target, GL_TEXTURE_BASE_LEVEL, level);
}
int VDTexture::getBaseLevel()const{
	int pvalue;
	this->bind();
	glGetTexParameteriv(this->getTarget(), GL_TEXTURE_BASE_LEVEL, &pvalue);
	return pvalue;
}

void VDTexture::setMaxMipMaps(int levels){
	this->bind();
	glTexParameteri(this->getTarget(), GL_TEXTURE_MAX_LEVEL, levels);	/*	TODO resolve the max level by its size */
}
int VDTexture::getMaxMipMaps(){
	int level;
	this->bind();
	glGetTexParameteriv(this->getTarget(), GL_TEXTURE_MAX_LEVEL, &level);
	return level;
}

void VDTexture::updateMipMap(){
	this->bind();
	glGenerateMipmap(this->getTarget());
}

void VDTexture::setMipMapBias(float bias){
	this->bind();
	glTexParameterf(this->getTarget(), GL_TEXTURE_LOD_BIAS, bias);
}
float VDTexture::getMipMapBias()const{
	float pvalue;
	this->bind();
	glGetTexParameterfv(this->getTarget(), GL_TEXTURE_LOD_BIAS, &pvalue);
	return pvalue;
}


unsigned int VDTexture::getCompressType(unsigned int internalFormat, CompressionFormat compression)const{
	if(VDSystemInfo::getCompatibility()->sTextureCompression == false){
		VDDebug::warningLog("Compression not supported. Revert format %d.\n", internalFormat);
		return internalFormat;
	}

	switch(internalFormat){
	case GL_RGB:
		switch(compression){
		default:
		case eDefault:
			return GL_COMPRESSED_RGB;
		case eDXT1:
			return GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
		}
		break;
	case GL_RGBA:
		switch(compression){
		default:
		case eDefault:
			return GL_COMPRESSED_RGBA;
		case eDXT1:
			return GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		}
		break;
	case GL_ALPHA:
		switch(compression){
		default:
		case eDefault:
			return GL_COMPRESSED_ALPHA;
		case eDXT1:
			return GL_COMPRESSED_ALPHA;
		}
		break;
	case GL_LUMINANCE:
		switch(compression){
		default:
		case eDefault:
		case eDXT1:
			return GL_COMPRESSED_RED;
			return GL_COMPRESSED_LUMINANCE;
		case eLATC:
			return GL_COMPRESSED_LUMINANCE_LATC1_EXT;
		}
		break;
	case GL_LUMINANCE_ALPHA:
		switch(compression){
		default:
		case eDefault:
			return GL_COMPRESSED_LUMINANCE_ALPHA;
		case eLATC:
			return GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT;
		}
		break;
	case GL_SRGB:
	case GL_SRGB8:
		switch(compression){
		default:
		case eDefault:
			return GL_COMPRESSED_SRGB;

		}
		break;
	default:
		return internalFormat;
	}
	return internalFormat;
}

unsigned int VDTexture::getNoneCompressType(unsigned int internalFormat)const{

	switch(internalFormat){
		case GL_COMPRESSED_RGB:
		case GL_COMPRESSED_RGB_S3TC_DXT1_EXT:
			return GL_RGB;
		case GL_COMPRESSED_RGBA:
		case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
			return GL_RGBA;
		case GL_COMPRESSED_LUMINANCE_ALPHA_LATC2_EXT:
			return GL_LUMINANCE_ALPHA;
		default:
			return internalFormat;
	}
}

unsigned int VDTexture::getSRGBFormat(unsigned int internalFormat)const{


	switch(internalFormat){
		case eRGB: return GL_SRGB;
		case eRGBA: return GL_SRGB8_ALPHA8;
		case GL_LUMINANCE: return GL_SLUMINANCE;
		case GL_LUMINANCE_ALPHA:return GL_SLUMINANCE_ALPHA;
		case GL_COMPRESSED_RGB: return GL_COMPRESSED_SRGB;
		case GL_COMPRESSED_RGBA: return GL_COMPRESSED_SRGB_ALPHA;
		case GL_COMPRESSED_RGB_S3TC_DXT1_EXT: return GL_COMPRESSED_SRGB_S3TC_DXT1_EXT;
		case GL_COMPRESSED_RGBA_S3TC_DXT1_EXT: return GL_COMPRESSED_SRGB_ALPHA_S3TC_DXT1_EXT;
	default:return internalFormat;
	}
}

void VDTexture::setTextureTarget(VDTexture::TextureTarget textureTarget){
	if(getTarget() == textureTarget){

	}
	target = textureTarget;
}

unsigned int VDTexture::getTarget()const{
	return this->target;
}

void VDTexture::setTextureID(unsigned int idTexture){
	this->texture = idTexture;
}

unsigned int VDTexture::getTexture()const{
	return this->texture;
}

void VDTexture::setPixelData(unsigned int level, unsigned int width, unsigned int height, unsigned int layer, VDTexture::TextureFormat internal, VDTexture::TextureFormat format, VDTexture::TextureDataType type, void* pixels, int plane){
	this->bind();
	switch(this->getTarget()){
	case eTexture1D:
		glTexImage1D(this->getTarget(), 0, internal, width , 0, format, type, pixels);
		break;
	case eTexture2D:
		glTexImage2D(this->getTarget(), level, internal, width, height, 0, format, type, pixels);
		break;
	case eTexture2DArray:
	break;
	case eCubeMap:{
		if(plane == -1){
			glTexImage2D(eCubeMapPositiveX + 0, level, internal, width, height, 0, format, type, pixels);
			glTexImage2D(eCubeMapPositiveX + 1, level, internal, width, height, 0, format, type, pixels);
			glTexImage2D(eCubeMapPositiveX + 2, level, internal, width, height, 0, format, type, pixels);
			glTexImage2D(eCubeMapPositiveX + 3, level, internal, width, height, 0, format, type, pixels);
			glTexImage2D(eCubeMapPositiveX + 4, level, internal, width, height, 0, format, type, pixels);
			glTexImage2D(eCubeMapPositiveX + 5, level, internal, width, height, 0, format, type, pixels);
			glTexParameteri(getTarget(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(getTarget(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(getTarget(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(getTarget(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(getTarget(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}else{
			glTexImage2D(plane, level, internal, width, height, 0, format, type, pixels);
		}
	}break;
	case eCubeMapArray:
		break;
	default:
		break;
	}
}

void VDTexture::setSubData(unsigned int width, unsigned int height, unsigned int layer, VDTexture::TextureFormat format, VDTexture::TextureFormat internal, VDTexture::TextureDataType type, void* data){
	this->bind();
	switch(this->getTarget()){
	case VDTexture::eTexture2D:
		break;
	case VDTexture::eTexture2DArray:
		break;
	case VDTexture::eTexture2DArrayMultiSample:
		break;
	case VDTexture::eTexture3D:
		break;
	default:
		break;
	}
}

void* VDTexture::getPixelData(unsigned int level, VDTexture::TextureFormat format, VDTexture::TextureDataType type){
	unsigned int size = getTextureSize(level);
	void* pixels = malloc(size);
	glGetTexImage(this->getTarget(), 0, format, type, pixels);
	return pixels;
}
