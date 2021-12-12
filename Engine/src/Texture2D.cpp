#include <Core/VDDebug.h>
#include <Core/VDObject.h>
#include <Core/VDQualitySetting.h>
#include <FreeImage.h>
#include <GL/glew.h>
#include <malloc.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Scene/VDScene.h>
#include <SDL2/SDL_stdinc.h>
#include <Utility/VDTextureProcedure.h>
#include <cmath>
#include <cstring>
#include <map>
#include <string>
#include <utility>

using namespace std;


VDTexture2D::VDTexture2D() : VDTexture(){
	this->mWidth = 0;
	this->mHeight = 0;
	this->format = 0;
	this->internalFormat = 0;
	this->type = 0;
	this->flag = 0;
	this->setTextureTarget(VDTexture::eTexture2D);
}

VDTexture2D::VDTexture2D(unsigned int width, unsigned int height, unsigned int SurfaceinternalFormat, unsigned int SurFaceFormat, unsigned int SurfaceType, unsigned int TextureFlag){

	this->mWidth = width;
	this->mHeight = height;
	this->format = SurFaceFormat;
	this->internalFormat = SurfaceinternalFormat;
	this->type = SurfaceType;
	this->flag = 0;

	this->flag |= TextureFlag;

	this->setTextureTarget(eTexture2D);

	glGenTextures(1, &this->texture);
	this->bind();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	this->setWrapMode(VDTexture::eRepeat);
	this->setFilterMode(VDTexture::eNearest);


	if(this->flag & VDTexture::eMipMapping ){
		this->setMaxMipMaps(log2f(width > height ? width * 0.25 : height * 0.25 ) );
	}
	if( this->flag & eAniostropic ){
		this->setAnisoLevel( VDQualitySetting::getTextureAnisotropy() );
	}

	/*
	glTexParameteri(this->getTarget(), GL_TEXTURE_MIN_FILTER, ((this->flag & VDTexture::eMipMapping) != 0 ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR));
	glTexParameteri(this->getTarget(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	*/

	if( this->flag & eSrgb ){
		glTexImage2D(this->target, 0, this->getSRGBFormat(this->internalFormat), this->mWidth, this->mHeight, 0, format, this->type, (GLvoid*)nullptr);
	}
	else{
		if(this->flag & eCompressed){
			this->internalFormat = getCompressType(this->internalFormat);
		}
		glTexImage2D(this->getTarget(), 0, this->internalFormat, this->mWidth, this->mHeight, 0, format, this->type, (GLvoid*)nullptr);
	}

	if(glGetError() != GL_NO_ERROR){
		//Debug::errorLog("Failed to Create Texture %s\n", glewGetErrorString(glGetError()));
	}
}

VDTexture2D::VDTexture2D(const char* path, unsigned int textureFlag) : VDTexture(){
	this->internalFormat = eRGB;
	this->setTextureTarget(VDTexture::eTexture2D);
	this->loadTexture(path, textureFlag);
}

VDTexture2D::~VDTexture2D(){
}

void VDTexture2D::release(){
	VDTexture::release();

	//remove from texture holder
	this->internalFormat = 0;
	this->type = 0;
	this->format = 0;
	this->mWidth = 0;
	this->mHeight = 0;
	this->flag = 0;
	for(map<const char*, VDTexture2D*>::iterator x = VDScene::getScene()->textureCollection.begin(); x != VDScene::getScene()->textureCollection.end(); x++){
		if(x->second == this){
			VDScene::getScene()->textureCollection.erase(x);
			break;
		}
	}
}

unsigned int VDTexture2D::bpp()const{
	return 24;//ExGetTextureBpp(this->format);
}

void VDTexture2D::setProperty(GLenum TexturePropertyType, int TypeValue){
	glBindTexture(this->target, this->texture);
	glTexParameteri(this->target, TexturePropertyType, TypeValue);
}

GLenum VDTexture2D::getProperty(GLenum TexturePropertyType){
	int properyV;
	this->bind();
	glGetTexParameteriv(this->target, TexturePropertyType, &properyV);
	this->unBind();
	return properyV;
}

void* VDTexture2D::pixels(unsigned int level, VDTexture::TextureFormat intformat, int types){

	unsigned char* pixels;

	if(!this->isValid()){
		return nullptr;
	}

	/**/
	if(intformat == -1){
		intformat = this->getInternalFormat();
	}
	/**/
	if(types == -1){
		types = this->type;
	}
	/**/
	return this->getPixelData(0, intformat, (VDTexture::TextureDataType)types);
	return (void*)pixels;
}


void VDTexture2D::update(){
	this->release();
	this->loadTexture(this->getName(), this->flag);
}

unsigned int VDTexture2D::loadTexture(const char* path, unsigned int supportFlag){
	if(this->isValid()){
		this->release();
	}

	unsigned int _width = 0, _height = 0, _bpp = 0;
	unsigned char* pixels = nullptr;
	this->setName(path);


	/*	Check if Image already Exists!	*/
	VDTexture2D* existTexture = VDTexture2D::existTexture(path);
	if(existTexture != nullptr){
		*this = *existTexture;
		//Texture2D::assignTexture(this,
		return SDL_TRUE;
	}
	else{	/*	load TextureData.	*/

		if(!VDTexture2D::loadTextureContent(path, &pixels, &_width, &_height, &_bpp, &format, &internalFormat, &type, supportFlag)){
			if(VDTexture2D::findTexture("ErrorTexture.exEngine")){
				const char* tempName = this->getName();
				memcpy(this, VDTextureProcedure::genErrorTexture(512,512), sizeof(VDTexture2D));
				VDTexture2D::assignTexture(this,tempName);
			}
			else{
				return SDL_FALSE;
			}
		}

	}

	glGenTextures(1, &this->texture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	this->bind();
	this->setWrapMode(VDTexture::eRepeat);
	this->setFilterMode(VDTexture::eLinear);

	if( supportFlag & VDTexture::eCompressed){
		glTexImage2D(this->getTarget(), 0, this->getCompressType(this->internalFormat), _width, _height, 0, this->format, this->type, pixels);
	}
	else{
		glTexImage2D(this->getTarget(), 0, internalFormat, _width, _height, 0, format, type, pixels);
	}
	
	int error = glGetError();
	if( supportFlag & VDTexture::eMipMapping ){
		this->updateMipMap();
	}

	if( supportFlag & VDTexture::eAniostropic ){
		this->setAnisoLevel(VDQualitySetting::getTextureAnisotropy() );
	}

	this->mWidth = (unsigned short)_width;
	this->mHeight = (unsigned short)_height;

	char* textureName = nullptr;
	std::string _converted = path;
	//memcpy(&textureName,(char*)_converted.c_str(),strlen(_converted.c_str()) + 1);
	//VDTexture2D::assignTexture(this,textureName);

	free(pixels);
	return SDL_TRUE;
}



unsigned int VDTexture2D::loadTextureContent(const char* path, unsigned char** pixel, unsigned int* Width, unsigned int* Height, unsigned int* bpp, unsigned int* TextureFormat, unsigned int* internalTextureFormat, unsigned int* TextureType,unsigned int  MipMap){
	unsigned int _width = 0,_height = 0, _bpp, _format = 0,_internalForamt = 0, _type = 0;
	void* dataPointer;
	FIBITMAP* image;
	int picture_type;
	FREE_IMAGE_COLOR_TYPE colortype;

	FreeImage_Initialise(0);
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path, 0);
	image = FreeImage_Load(format, path, 0);
	if(image == nullptr){
		VDDebug::criticalLog("Failed to load %s\n", path);
		return 0;
	}

	if(format == FIF_TIFF){
		FreeImage_FlipVertical(image);
	}
	picture_type = FreeImage_GetImageType(image);
	*Width = FreeImage_GetWidth(image);
	*Height = FreeImage_GetHeight(image);
	int __size = ( FreeImage_GetBPP(image) / 8 ) * *Width * *Height;
	BYTE *bits = FreeImage_GetBits(image);
	*pixel = (unsigned char*)malloc(__size);
	memcpy(*pixel, (unsigned char*)bits, __size);

	colortype = FreeImage_GetColorType(image);
	if(colortype == FIC_RGB){
		*TextureFormat = GL_BGR;
		*internalTextureFormat = GL_RGB;
	}
	else if(colortype == FIC_RGBALPHA){
		*TextureFormat = GL_BGRA;
		*internalTextureFormat = GL_RGBA;
	}
	else if(colortype == FIC_PALETTE || colortype == FIC_MINISBLACK || colortype == FIC_MINISWHITE){
		*TextureFormat = GL_RED;
		*internalTextureFormat = GL_RED;
	}

	*TextureType = GL_UNSIGNED_BYTE;
	FreeImage_Unload(image);


	FreeImage_DeInitialise();
	return SDL_TRUE;
}

void VDTexture2D::assignTexture(VDTexture2D* texture, const char* pathName){
	if(!texture){
		return;
	}else{
		VDScene::getScene()->textureCollection.insert(std::pair<const char*, VDTexture2D*>(pathName,texture));
	}
}

VDTexture2D* VDTexture2D::existTexture(const char* path){

	return nullptr;
	for(std::map<const char*, VDTexture2D*>::iterator x = VDScene::getScene()->textureCollection.begin(); x != VDScene::getScene()->textureCollection.end(); x++){
		if(x->second->getName() == nullptr)
			continue; // name is null. can't check.
		if(strcmp(path, x->second->getName()) == 0)
			return x->second;
	}
	return nullptr;
}

unsigned int VDTexture2D::saveTextureContent(const char* path, VDTexture2D* texture, unsigned int TextureFormat){
	if(texture == nullptr || path == nullptr){
		return SDL_FALSE;
	}
	unsigned int success;
	void* ppData = (unsigned char*)texture->pixels(0, VDTexture::eRGB, VDTexture::eUnsignedByte);

	success = VDTexture2D::saveTextureContent(path, (unsigned char*)ppData, texture->width(), texture->height(), texture->getInternalFormat(), VDTexture::eUnsignedByte ,TextureFormat);
	free(ppData);
	return success;;
}

unsigned int VDTexture2D::saveTextureContent(const char* path, unsigned char* PixelBuffer,unsigned int Width,unsigned int Height, unsigned int TextureinternalFormat, unsigned int TextureType, unsigned int saveFormat ){

	if(path == nullptr || PixelBuffer == nullptr){
		return SDL_FALSE;
	}

	/**/
	unsigned int success = SDL_FALSE;
	FREE_IMAGE_FORMAT fif = FIF_BMP;

	/**/
	FreeImage_Initialise(0);
	FIBITMAP* Image = FreeImage_ConvertFromRawBits(PixelBuffer, Width, Height, 3, 8, 0xFF0000, 0x00FF00, 0x0000FF, false);
	FreeImage_Save(fif, Image, "test.bmp", 0);
	FreeImage_Unload(Image);
	FreeImage_DeInitialise();
	return success;
}
