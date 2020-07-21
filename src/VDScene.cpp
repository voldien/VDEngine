#include <Core/VDDebug.h>
#include <Core/VDEngineCore.h>
#include <Rendering/VDRender.h>
#include <Rendering/VDRenderCollection.h>
#include <Rendering/VDRenderSetting.h>
#include <Scene/VDScene.h>
#include <cstring>
#include <list>


void VDScene::init(void){

	/*	setup scene data */
	VDScene::getScene()->version = VD_ENGINE_VERSION;
	VDScene::getScene()->flag = 0;
	memcpy(VDScene::getScene()->name, "default scene", sizeof("default scene"));
	VDRenderSetting::setAmbientColor(VDColor(0.7));

	/*		*/
	VDScene::getScene()->keys.resize(128);
	VDScene::getScene()->gameobjects.resize(1024);
	VDScene::getScene()->nodes.resize(1024);
	VDScene::getScene()->meshs.resize(512);
	VDScene::getScene()->audios.resize(16);
	VDScene::getScene()->lights.resize(16);
	VDScene::getScene()->lightcollection.resize(128);
	VDScene::getScene()->materials.resize(128);
	VDScene::getScene()->shaders.resize(64);
	VDScene::getScene()->curves.resize(64);
	VDScene::getScene()->cameras.resize(16);
	VDScene::getScene()->mainCamera = NULL;
	VDScene::getScene()->currentCamera = NULL;

	/*	*/
	VDScene::getScene()->uniform.engineState.numSpot = 0;
	VDScene::getScene()->uniform.engineState.numPoint = 0;
	VDScene::getScene()->uniform.engineState.numDirection = 0;
	VDScene::getScene()->uniform.engineState.numLights = 0;
	VDScene::getScene()->uniform.engineState.numShadows = 0;
	VDScene::getScene()->uniform.engineState.numShadowDirection = 0;
	VDScene::getScene()->uniform.engineState.numShadowPoint = 0;
	VDScene::getScene()->uniform.engineState.numShadowSpot = 0;
	VDScene::getScene()->lightinfo.directIndices.resize(1024);
	VDScene::getScene()->lightinfo.spotIndices.resize(1024);
	VDScene::getScene()->lightinfo.pointIndices.resize(1024);
	VDScene::getScene()->lightinfo.shadowDirectionIndices.resize(128);
	VDScene::getScene()->lightinfo.shadowSpotIndices.resize(128);
	VDScene::getScene()->lightinfo.shadowPointIndices.resize(128);

}



void VDScene::addstaticObject(VDGameObject* object, bool wasStatic){
	if(!object){
		return;
	}

	/*	make the rendering object static.	*/
	if(object->renderer()){
		VDRenderer::RendererType type = object->renderer()->getRenderType();
		RenderCollectionHeap& heap = VDRenderCollection::getRenderType(VDRenderer::eStaticBatch);


		/*	compute which position in octree to be locate.*/
	}
}

void VDScene::removeStaticObject(VDGameObject* obj, bool wasStatic){
	if(!obj)
		return;


}

void VDScene::clear(void){

	gSerlizedGameObject.clear();

	VDScene::getScene()->cameras.clean();
	VDScene::getScene()->gameobjects.clean();
	VDScene::getScene()->audios.clean();
	VDScene::getScene()->curves.clean();

	VDScene::getScene()->lights.clean();
	VDScene::getScene()->gLightCollection.clear();

	VDDebug::debugLog("Cleared scene data.\n");
}


VDEngineScene* VDScene::getScene(void){
	return engine.scene;
}

