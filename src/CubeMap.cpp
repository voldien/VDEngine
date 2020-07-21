#include <GL/glew.h>
#include <malloc.h>
#include <Misc/VDMath.h>
#include <Rendering/Texture/VDCubeMap.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <stddef.h>
#include <SDL2/SDL_stdinc.h>
#include <VDSimpleType.h>

VDCubeMap::VDCubeMap(void) : VDTexture(VDTexture::eCubeMap){
	this->mWidth = 0;
}

VDCubeMap::VDCubeMap(const VDCubeMap& cubemap){
	*this = cubemap;
}

VDCubeMap::VDCubeMap(unsigned int size, VDTexture::TextureFormat format) : VDTexture(VDTexture::eCubeMap){
	this->mWidth = size;
	this->bind();
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, format, size, size, 0, format, VDTexture::eUnsignedByte, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, format, size, size, 0, format, VDTexture::eUnsignedByte, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, format, size, size, 0, format, VDTexture::eUnsignedByte, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, format, size, size, 0, format, VDTexture::eUnsignedByte, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, format, size, size, 0, format, VDTexture::eUnsignedByte, NULL);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, format, size, size, 0, format, VDTexture::eUnsignedByte, NULL);
}

VDCubeMap::VDCubeMap(const char* alignTexture) : VDTexture(VDTexture::eCubeMap){
	this->generate(alignTexture);
}

VDCubeMap::VDCubeMap(const char* right, const char* left, const char* top, const char* bottom, const char* far, const char* near, unsigned int  bitFlag) : VDTexture(VDTexture::eCubeMap){
	this->generate(right, left, top, bottom, far, near, bitFlag);
}

VDCubeMap::~VDCubeMap(void){

}

unsigned int VDCubeMap::generate(const char* right,
				const char* left,
				const char* top,
				const char* bottom,
				const char* Far,
				const char* Near, unsigned int  bitFlag ){
	if(right == NULL || left == NULL ||
		top == NULL || bottom == NULL ||
		Far == NULL || Near == NULL)
		return SDL_FALSE;

	this->bind();
	for(unsigned int  x = 0; x < 6; x++){
		char* path;
		if(x == 0)
			path = (char*)right;
		else if(x == 1)
			path = (char*)left;
		else if(x == 2)
			path = (char*)top;
		else if(x == 3)
			path =(char*) bottom;
		else if(x == 4)
			path =(char*) Near;
		else if(x == 5)
			path = (char*)Far;
		else
			break;


		unsigned int  width,height,format,type,internalFormat;
		unsigned char* pixelPointer = NULL;

		/*	TODO resolve compression flag!	*/
		if(VDTexture2D::loadTextureContent(path, &pixelPointer, &width, &height, 0, &format, &internalFormat, &type)){
			if(bitFlag & VDTexture::eCompressed){
				internalFormat = getCompressType(internalFormat);
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + x, 0, internalFormat ,width, height, 0, format, type, pixelPointer);
			this->setFilterMode(VDTexture::eLinear);
			this->setWrapMode(VDTexture::eClampEdge);
		}
		free(pixelPointer);

	}

	return SDL_TRUE;
}

unsigned int VDCubeMap::generate(const char* alignTexture, unsigned int bitFlag){
	if(!alignTexture){
		return SDL_FALSE;
	}

	this->bind();
	unsigned int  width,height,format,type,internalFormat;
	unsigned char* pixelPointer = NULL;

	if(VDTexture2D::loadTextureContent(alignTexture,&pixelPointer,&width,&height,0,&format,&internalFormat,&type)){
		for(unsigned int  x = 0; x < 6; x++){
			if(bitFlag & VDTexture::eCompressed){
				internalFormat = getCompressType(internalFormat);
			}

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + x, 0, internalFormat ,width, height, 0, format, type, pixelPointer);
			this->setFilterMode(VDTexture::eLinear);
			this->setWrapMode(VDTexture::eClampEdge);

		}
	}
	free(pixelPointer);
	return SDL_TRUE;
}


VDQuaternion VDCubeMap::getCubePlaneQuaternion(unsigned int planetarget){

	switch(planetarget){
	case VDTexture::eCubeMapPositiveX:
		return VDQuaternion(0, VDMath::deg2Rad(90), 0);
	case VDTexture::eCubeMapPositiveX + 1:
		return VDQuaternion(0,VDMath::deg2Rad(-90), 0);
	case VDTexture::eCubeMapPositiveX + 2:
		return VDQuaternion(VDMath::deg2Rad(90), 0, 0);
	case VDTexture::eCubeMapPositiveX + 3:
		return VDQuaternion(VDMath::deg2Rad(-90), 0, 0);
	case VDTexture::eCubeMapPositiveX + 4:
		return VDQuaternion(0, VDMath::deg2Rad(0), VDMath::deg2Rad(0));
	case VDTexture::eCubeMapPositiveX + 5:
		return VDQuaternion(0, VDMath::deg2Rad(180), VDMath::deg2Rad(0));
	default:
		return VDQuaternion::identity();
	}
}

VDCubeMap* VDCubeMap::createErrorCubeMap(void){

	return NULL;
}
