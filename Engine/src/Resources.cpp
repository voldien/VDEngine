#include <Asset/VDAssetManager.h>
#include <Asset/VDDCCLoaderOption.h>
#include <Asset/VDMeshLoader.h>
#include <Asset/VDResources.h>
#include <Audio/VDAudioClip.h>
#include <Core/VDDebug.h>
#include <Core/VDQualitySetting.h>
#include <Core/VDTypes.h>
#include <DataStructure/VDVector.h>
#include <malloc.h>
#include <Misc/VDFile.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Rendering/Texture/VDCubeMap.h>
#include <Rendering/VDMaterial.h>
#include <Rendering/VDMesh.h>
#include <stddef.h>
#include <VDDef.h>
#include <typeinfo>

void* VDResources::load(const char* cfilename, const VDTypeInfo& info){

	void* asset = NULL;

	/**/
	if(!VDFile::existFile(cfilename)){
		VDDebug::errorLog("%s is not a file.\n", cfilename);
		return NULL;
	}

	/**/
	if(*info.getType() == typeid(VDTexture2D)){
		asset = new VDTexture2D(cfilename, VDTexture::eMipMapping | VDTexture::eCompressed);
		VDCAST(VDTexture2D*, asset)->setAnisoLevel(VDQualitySetting::getTextureAnisotropy());
	}

	/**/
	if(*info.getType() == typeid(VDCubeMap)){


	}

	/**/
	if(*info.getType() == typeid(VDMesh)){
		/*	check if supported by assimp, or fbx.*/
		VDMeshLoader loader;
		loader.loadContent(cfilename, IMPORT_MESH);
		asset = loader.getMesh(0);
		loader.release();
	}
	/**/
	if(*info.getType() == typeid(VDAudioClip)){
		VDAudioClip* clip = new VDAudioClip();
		clip->load(cfilename, VDAudioClip::eCompressed);
	}

	/**/
	if(*info.getType() == typeid(VDMaterial)){
		VDMaterial* material = VDMaterial::createMaterial();
	}

	/**/
	if(*info.getType() == typeid(VDShader)){
		char* source = NULL;
		char* vs,*fs,*gs,*tcs,*tes;
		VDFile::load(cfilename, &source);
		free(source);
	}


	finished:	/*	*/

	/*	if succesully resouce load, add object to asset manager register	*/
	VDAssetManager::assignAsset((VDAssetObject*)asset);

	return asset;
}


void* VDResources::loadAll(const char* cfilename, const VDTypeInfo& info){
	VDVector<VDAssetObject*> assetObjects;
	void* p;

	/**/
	if(!VDFile::existFile(cfilename)){
		VDDebug::errorLog("%s is not a file.\n", cfilename);
		return NULL;
	}


	if(*info.getType() == typeid(VDTexture2D)){
		p = new VDTexture2D(cfilename, VDTexture::eMipMapping | VDTexture::eCompressed);

	}

	if(*info.getType() == typeid(VDShader)){

	}

	return p;
}


void* VDResources::unLoadAll(const char* cfilename, const VDTypeInfo& info){
	void* p;

	/*TODO get references node from asset registry!	*/
	if(*info.getType() == typeid(VDTexture2D)){

	}

	return p;
}
