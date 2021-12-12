#include <malloc.h>
#include <Rendering/Texture/VDTexture.h>
#include <stddef.h>
#include <Utility/VDTextureAlgorithmic.h>
#include <Utility/VDTextureUtility.h>

VDTexture2D* VDTextureUtility::genNormal(VDTexture2D* texture, float slope, float bumpiness){

	unsigned char* normalPix = nullptr;
	VDTexture2D* texNormal = nullptr;
	unsigned char* tempPix = (unsigned char*)texture->getPixelData(0, VDTexture::eRGB, VDTexture::eUnsignedByte);

	if(VDIntConvertToNormalMap(&normalPix, tempPix, texture->width(), texture->height(), texture->getInternalFormat(), slope,bumpiness)){
		/*	add	GL_RG*/
		texNormal = new VDTexture2D(texture->width(), texture->height(), VDTexture::eRGB, VDTexture::eRGB, VDTexture::eUnsignedByte);
		//texNormal->setData(0, nullptr, normalPix);
	}
	free(tempPix);
	free(normalPix);

	return texNormal;
}

VDTexture2D* VDTextureUtility::genInvert(VDTexture2D* texture){

	return nullptr;
}

