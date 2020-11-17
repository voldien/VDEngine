#include <Animation/VDAnimationClip.h>
#include <Asset/VDAssetLoader.h>
#include <Core/VDObject.h>
#include <HCAABB.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Rendering/VDMaterial.h>
#include <Rendering/VDMesh.h>
#include <Rendering/VDRender.h>
#include <Scene/VDGameObject.h>
#include <Scene/VDTransform.h>
#include <VDDef.h>
#include <VDSimpleType.h>
#include <cstring>
#include <vector>


VDGameObject* VDAssetLoader::sceneRoot(void){
	VDGameObject* root = VDGameObject::createGameObject();
	int x;
	if(getGameObjectRootCount() != 0){
		for(x = 0; x < getGameObjectRootCount(); x++){
			root->transform()->addChild(getGameObjectRoot(x)->transform());
		}
	}
	else{
		for(x = 0; x < getGameObjectCount(); x++){
			if(root->transform()->getParent() == NULL)
				root->transform()->addChild(getGameObject(x)->transform());
		}
	}
	return root;
}


VDGameObject* VDAssetLoader::getGameObjectRoot(unsigned int index){

	unsigned int parentIndex = 0;
	unsigned int x;
	if(this->object.size() == 0){
		return NULL;
	}


	// ignore scene root node
	for(x = 1; x < this->object.size(); x++){
		if(this->object[x]->transform()->getParent() == this->sceneRoot()->transform())
			parentIndex++;

		if(parentIndex == index)
			break;
	}

	return this->object[parentIndex];
}


unsigned int VDAssetLoader::getGameObjectRootCount(void)const{
	return 0;
}

VDGameObject* VDAssetLoader::getGameObject(unsigned int index){
	return (this->object.size() > index) ? this->object[index] : NULL;
}

void VDAssetLoader::setGameObject(const VDGameObject* object){
	this->object.push_back((VDGameObject*)object);
}

VDGameObject* VDAssetLoader::findGameObject(const char* cname){
	if(!cname)
		return NULL;

	if(strlen(cname) == 0)
		return NULL;

	for(unsigned int x = 0; x < this->object.size(); x++){
		if(strcmp(this->object[x]->getName(),cname) == 0)
			return this->object[x];
	}
	return NULL;
}

unsigned int VDAssetLoader::getGameObjectCount(void)const{
	return object.size();
}

VDMesh* VDAssetLoader::getMesh(unsigned int index){
	return (index < this->meshs.size()) ? this->meshs[index] : NULL;
}

void VDAssetLoader::setMesh(const VDMesh* mesh){
	meshs.push_back((VDMesh*)mesh);
}

VDMesh* VDAssetLoader::findMesh(const char* meshName){
	for(unsigned int x = 0; x < this->meshs.size();x++){

		if(!this->meshs[x]->getName())
			continue;

		if(strcmp(this->meshs[x]->getName(), meshName) == 0){
			return this->meshs[x];
		}
	}
	return NULL;
}

unsigned int VDAssetLoader::getMeshCount(void)const{
	return meshs.size();
}


VDCamera* VDAssetLoader::getCamera(unsigned int index){
	return (index < this->cameras.size()) ? this->cameras[index] : NULL;
}

void VDAssetLoader::setCamera(const VDCamera* camera){
	this->cameras.push_back((VDCamera*)camera);
}

VDCamera* VDAssetLoader::findCamera(const char* cname){
	VDGameObject* lgameObject = this->findGameObject(cname);
	if(lgameObject)
		return lgameObject->camera();
	else
		return NULL;
}

unsigned int VDAssetLoader::getCameraCount(void)const{
	return cameras.size();
}


VDLight* VDAssetLoader::getLight(unsigned int index){
	return (index < this->lights.size()) ? this->lights[index] : NULL;
}

void VDAssetLoader::setLight(const VDLight* light){
	this->lights.push_back((VDLight*)light);
}

unsigned int VDAssetLoader::getLightCount(void)const{
	return lights.size();
}

VDTexture2D* VDAssetLoader::getTexture(unsigned int index){
	return (index < this->textures.size()) ? (VDTexture2D*)this->textures[index] : NULL;
}

void VDAssetLoader::setTexture(const VDTexture2D* texture){
	textures.push_back((VDTexture2D*)texture);
}


VDTexture2D* VDAssetLoader::findTexture(const char* textureName){
	for(unsigned int x = 0; x < this->textures.size(); x++){
		if(strcmp(VDCASTP(VDTexture2D*,this->textures[x])->getName(),textureName) == 0)
			return VDCASTP(VDTexture2D*,this->textures[x]);
	}
	return NULL;
}

unsigned int VDAssetLoader::getTextureCount(void)const{
	return this->textures.size();
}


VDMaterial* VDAssetLoader::getMaterial(unsigned int index){
	return (index < this->materials.size()) ? this->materials[index] : NULL;
}

void VDAssetLoader::setMaterial(const VDMaterial* material){
	this->materials.push_back((VDMaterial*)material);
}


VDMaterial* VDAssetLoader::findMaterial(const char* materialName){
	for(unsigned int x = 0; x < this->materials.size(); x++){
		if(strcmp(this->materials[x]->getName(),materialName) == 0)
			return this->materials[x];

	}
	return NULL;
}

unsigned int VDAssetLoader::getMaterialCount(void)const{
	return materials.size();
}


VDAnimationClip* VDAssetLoader::getAnimationClip(unsigned int index){
	return (index < this->animationClips.size()) ?  this->animationClips[index] : NULL;
}

void VDAssetLoader::setAnimationClip(const VDAnimationClip* clip){
	this->animationClips.push_back((VDAnimationClip*)clip);
}

unsigned int VDAssetLoader::getAnimationClipCount(void)const{
	return this->animationClips.size();
}



VDAnimation* VDAssetLoader::getAnimation(unsigned int index){
	return (index < this->animations.size()) ?  this->animations[index] : NULL;
}

void VDAssetLoader::setAnimation(const VDAnimation* animation){
	this->animations.push_back((VDAnimation*)animation);
}

VDAnimation* VDAssetLoader::findAnimation(const char* cname){
	return NULL;
}

unsigned int VDAssetLoader::getAnimationCount(void)const{
	return this->animations.size();
}

VDRenderer* VDAssetLoader::getRenderer(unsigned int index){
	return (index < this->renderer.size()) ? this->renderer[index] : NULL;
}

void VDAssetLoader::setRenderer(const VDRenderer* renderer){
	this->renderer.push_back((VDRenderer*)renderer);
}

VDRenderer* VDAssetLoader::findRenderer(const char* cname){
	VDGameObject* g = findGameObject(cname);
	if(g)
		return g->renderer();
	return NULL;
}

unsigned int VDAssetLoader::getRendererCount(void)const{
	return renderer.size();
}

void VDAssetLoader::release(void){
	int x;

	/*	*/
	for(x = 0; x < getGameObjectCount(); x++){
		this->getMesh(x)->deincrement();
	}

	for(x = 0; x < getMeshCount(); x++){
		this->getMesh(x)->deincrement();
	}

	for(x = 0; x < getCameraCount(); x++){

	}
	for(x = 0; x < getTextureCount(); x++){
		this->getTexture(x)->deincrement();
	}

	for(x = 0; x < getAnimationClipCount(); x++){
		this->getAnimationClip(x)->deincrement();
	}

	for(x = 0; x < getMaterialCount(); x++){
		this->getMaterial(x)->deincrement();
	}

	this->object.clear();
	this->meshs.clear();
	this->cameras.clear();
	this->lights.clear();
	this->textures.clear();
	this->animationClips.clear();
	this->animations.clear();
	this->materials.clear();
	this->renderer.clear();
	memset(this->path, '\0', sizeof(path) );
}

VDAssetLoader& VDAssetLoader::operator=(const VDAssetLoader& loader){
	this->object = loader.object;
	this->meshs = loader.meshs;
	this->cameras = loader.cameras;
	this->textures = loader.textures;
	this->animationClips = loader.animationClips;
	this->animations = loader.animations;
	this->materials = loader.materials;
	this->renderer = loader.renderer;

	return *this;
}

bool VDAssetLoader::operator==(const VDAssetLoader& loader){

	return false;
}

bool VDAssetLoader::operator!=(const VDAssetLoader& loader){

	return false;
}

