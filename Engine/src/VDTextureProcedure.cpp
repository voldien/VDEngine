#include <Core/VDObject.h>
#include <malloc.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <stddef.h>
#include <Utility/VDTextureAlgorithmic.h>
#include <Utility/VDTextureProcedure.h>
#include <cmath>

VDTexture2D* VDTextureProcedure::genMipmapLevelDebugger(unsigned int levels){
	unsigned int size = (unsigned int)powf(2, levels);

	VDTexture2D* texture = new VDTexture2D(size, size, VDTexture2D::eRGB, VDTexture2D::eRGB, VDTexture2D::eUnsignedByte, VDTexture2D::eMipMapping);
	texture->setMaxMipMaps(levels);
	unsigned char* data = (unsigned char*)malloc(sizeof(unsigned char) * 3 * size * size);

	for(unsigned int x = 0 ; x < levels; x++){

		for(int y = 0; y < size; y++){
			for(int z = 0; z < size; z++){
				data[y * size * 3 + z * 3 + 0] = 0.5f * (sinf(0.4 * x * 0.5) + 1.0f) 		* 255.0f;
			    data[y * size * 3 + z * 3 + 1] = 0.5f * (cosf(0.8 * x * 0.5) + 1.0f) 		* 255.0f;
				data[y * size * 3 + z * 3 + 2] = 0.5f * (sinf(2.4 * x * 0.5 - 1.5) +1.0f) * 255.0f;
			}
		}
		texture->setPixelData(0, texture->width(), texture->height(), 0, VDTexture::eRGB, VDTexture::eRGB, VDTexture::eUnsignedByte, data);
	}
	free(data);
	return texture;
}



VDTexture2D* VDTextureProcedure::genCheckTexture(unsigned int width, unsigned int height, unsigned int checkWith,unsigned int checkHeight, unsigned int SurfaceinternalFormat, unsigned int SurFaceFormat , unsigned int SurfaceType, unsigned int  MipMap){
	unsigned char* pixelData = NULL;
	VDTexture2D* chTexture = NULL;

	if(VDIntGenChecker(&pixelData, width, height, checkWith, checkHeight, SurfaceinternalFormat)){
		chTexture = new VDTexture2D(width, height, SurfaceinternalFormat, SurFaceFormat,SurfaceType, MipMap);
		chTexture->setPixelData(0, chTexture->width(), chTexture->height(), 0, VDTexture::eRGB, VDTexture::eRGB, VDTexture::eUnsignedByte, pixelData);
		VDTexture2D::assignTexture(chTexture, "CheckerTexture");
	}
	free(pixelData);
	return chTexture;
}

VDTexture2D* VDTextureProcedure::genCheckerTexture2(unsigned int width, unsigned int height, unsigned int checkWidth, unsigned int checkerHeight, const VDColor32& foreColor, const VDColor32& backColor, unsigned int SurfaceinternalFormat, unsigned int SurFaceFormat, unsigned int SurfaceType, unsigned int mipmap){
	unsigned char* pixelData = NULL;
	VDTexture2D* ch_texture = NULL;

	if(VDIntGenChecker2(&pixelData, width, height, checkWidth, checkerHeight, foreColor, backColor, SurfaceinternalFormat)){
		ch_texture = new VDTexture2D(width, height, SurfaceinternalFormat, SurFaceFormat, SurfaceType, mipmap);
		//ch_texture->setData(0, NULL, pixelData);
		ch_texture->setName("CheckerTexture2_");
		VDTexture2D::assignTexture(ch_texture, "CheckerTexture2");
	}
	free(pixelData);
	return ch_texture;
}



VDTexture2D* VDTextureProcedure::genLinearGridTexture(unsigned int width, unsigned int height, unsigned int linearX, unsigned int linearY, unsigned int thickness,const VDColor32& backColor,const VDColor32& foreColor, unsigned int SurfaceinternalFormat, unsigned int SurFaceFormat , unsigned int SurfaceType, unsigned int  MipMap){
	unsigned char* pixelData = NULL;
	VDTexture2D* lg_texture = NULL;
	if(VDIntGenGridTexture(&pixelData, width, height, linearX, linearY,thickness,(unsigned char*)&backColor,(unsigned char*)&foreColor, SurfaceinternalFormat)){
		lg_texture = new VDTexture2D(width, height, SurfaceinternalFormat, SurFaceFormat,SurfaceType,MipMap);
		//lg_texture->setData(0, NULL,pixelData);
		VDTexture2D::assignTexture(lg_texture, "LinearGridTexture");
	}
	free(pixelData);
	return lg_texture;
}

VDTexture2D* VDTextureProcedure::genColorTexture(unsigned int width, unsigned int height,const VDColor32& color, unsigned int SurfaceinternalFormat ,unsigned int SurFaceFormat ,unsigned int SurfaceType ,unsigned int mipmap){
	unsigned char* colPix = NULL;
	VDTexture2D* colTex = NULL;

	if(VDIntGenColorTexture(&colPix,width, height,SurfaceinternalFormat, (unsigned char*)&color)){
		colTex = new VDTexture2D(width, height, SurfaceinternalFormat, SurFaceFormat, SurfaceType, mipmap);
		//colTex->setData(0,NULL, colPix);
		//colTex->Name = "ColorTexture";
		VDTexture2D::assignTexture(colTex, "ColorTexture");
	}
	free(colPix);

	return colTex;
}

VDTexture2D* VDTextureProcedure::RandomTexture(unsigned int width, unsigned int height, unsigned int SurfaceinternalFormat, unsigned int SurFaceFormat, unsigned int SurfaceType, unsigned int  MipMap){
	unsigned char* randomPix = NULL;
	VDTexture2D* randomTex = NULL;
	if(VDIntGenRandomTexture(&randomPix,width, height,SurfaceinternalFormat)){
		randomTex = new VDTexture2D(width,height, SurfaceinternalFormat, SurFaceFormat, SurfaceType,MipMap);
		//randomTex->setData(0,NULL, randomPix);
		//colTex->Name = "ColorTexture";
		VDTexture2D::assignTexture(randomTex, "RandomTexture");
	}
	free(randomPix);
	return randomTex;
}

VDTexture2D* VDTextureProcedure::LinearTexture(unsigned int width, unsigned int height,unsigned int start, unsigned int end, VDColor32 color, unsigned int SurfaceinternalFormat, unsigned int SurFaceFormat, unsigned int SurfaceType, unsigned int  MipMap ){
	unsigned char* linPix = NULL;
	VDTexture2D* lintex = NULL;
	if(VDIntGenLinearTexture(&linPix, width ,height, SurfaceinternalFormat,(unsigned char*)&color, start, end)){
		lintex = new VDTexture2D(width, height,SurfaceinternalFormat, SurFaceFormat, SurfaceType);
		//lintex->setData(0, NULL,linPix);
	}
	free(linPix);
	return lintex;
}

VDTexture2D* VDTextureProcedure::genErrorTexture(unsigned int width, unsigned int height, unsigned int SurfaceinternalFormat, unsigned int SurFaceFormat, unsigned int SurfaceType , unsigned int  textureFlag){
	if(VDTexture2D::findTexture("ErrorTexture.exEngine") != NULL)// check if texture exists
		return VDTexture2D::findTexture("ErrorTexture.exEngine");
	else{
		//unsigned char* errPix = NULL;
		//Texture2D* errTex = NULL;
		//if(ExProcChecker2(&errPix, width, height, width / 8, height / 8, Color32::Black(), Color32::Purple() * 1.24f, SurfaceinternalFormat)){
		//	errTex = new Texture2D(width, height, SurfaceinternalFormat, SurFaceFormat,SurfaceType,textureFlag);
		//	errTex->setData(0, NULL,errPix);
		//	errTex->Name = EX_TEXT("ErrorTexture.exEngine");
		//	Texture2D::assignTexture(errTex, "ErrorTexture.exEngine");
		//}
		//free(errPix);
		return 0;//return errTex ;
	}
}


VDTexture2D* VDTextureProcedure::blackTexture(void){
	return VDTextureProcedure::genColorTexture(1, 1, VDColor32::Black(), VDTexture::eRed, VDTexture::eRed, VDTexture::eUnsignedByte, 0);
}

VDTexture2D* VDTextureProcedure::whiteTexture(void){
	return VDTextureProcedure::genColorTexture(1, 1, VDColor32::White(), VDTexture::eRed, VDTexture::eRed, VDTexture::eUnsignedByte, 0);
}
