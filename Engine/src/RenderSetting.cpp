#include <Core/VDDebug.h>
#include <Core/VDEngineCore.h>
#include <Core/VDObject.h>
#include <Core/VDScreen.h>
#include <Rendering/Texture/VDCubeMap.h>
#include <Rendering/Texture/VDRenderTexture.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/VDMesh.h>
#include <Rendering/VDRenderSetting.h>
#include <Rendering/VDShader.h>
#include <Rendering/VDShaderConstant.h>
#include <stddef.h>
#include <Scene/VDScene.h>
#include <Scene/VDSkyBox.h>
#include <Utility/VDGeometryProcedure.h>
#include <VDSimpleType.h>
#include <VDSystemInfo.h>

using namespace std;

VDEngineRenderSettings VDRenderSetting::gRenderSettings  = {0};


VDRenderSetting::VDRenderSetting(unsigned int sRenderingPath){

	/**/
	VDRenderSetting::setRenderingPath((VDRenderSetting::RenderPipeline)sRenderingPath);


	/*	framebuffers	TODO give the feature a unique name, TODO fix size*/
	if(0){
		VDRenderSetting::getSettings()->frame.numframe = 5;
		VDRenderSetting::getSettings()->frame.frames = new VDRenderTexture[VDRenderSetting::getSettings()->frame.numframe];
		VDRenderSetting::getSettings()->frame.frames[0] = VDTexture2D(VDScreen::width(), VDScreen::height(), VDTexture::eRGB, VDTexture::eRGB, VDTexture::eFloat, 0);
		VDRenderSetting::getSettings()->frame.frames[1] = VDTexture2D(VDScreen::width(), VDScreen::height(), VDTexture::eRGB, VDTexture::eRGB, VDTexture::eFloat, 0);
		VDRenderSetting::getSettings()->frame.frames[2] = VDTexture2D(VDScreen::width(), VDScreen::height(), VDTexture::eRGB, VDTexture::eRGB, VDTexture::eFloat, 0);
		VDRenderSetting::getSettings()->frame.frames[3] = VDTexture2D(VDScreen::width(), VDScreen::height(), VDTexture::eRGB, VDTexture::eRGB, VDTexture::eFloat, 0);
		VDRenderSetting::getSettings()->frame.frames[4] = VDTexture2D(VDScreen::width(), VDScreen::height(), VDTexture::eRGB, VDTexture::eRGB, VDTexture::eFloat, 0);
		VDRenderSetting::getSettings()->frame.nframe = 0;
	}

}

void VDRenderSetting::setRenderingPath(VDRenderSetting::RenderPipeline sRenderingPath){

	VDRenderTexture* releaseTarget;
	VDRenderTexture* target;
	VDEngineRenderSettings* settings = VDRenderSetting::getSettings();

	/*	Create quad display.	*/	/*	TODO resolve the issue what the quad disapears from memory.	*/
	if(!settings->quadDisplay){
		settings->quadDisplay = VDGeometryProcedure::createQuad(1.0f, 1.0f, 0, 0);
		settings->quadDisplay->setFlag(VDObject::eStatic | settings->quadDisplay->getFlag());
	}


	if(VDRenderSetting::getRenderingPath() != sRenderingPath){
		switch(sRenderingPath){
		case eForwardRendering:

			/*	TODO allocate framebuffer if supported.	*/
			releaseTarget = VDRenderSetting::getRenderingPathFrameBuffer(VDRenderSetting::getRenderingPath());
			if(releaseTarget){
				releaseTarget->release();
			}

			/*	Create forward framebuffer if supported.	*/
			if(VDSystemInfo::getCompatibility()->sFramebuffer){

				target = VDRenderSetting::getForwardFramebuffer();
				if(target == NULL){
					/**/
					VDRenderSetting::getSettings()->forward = VDRenderTexture::colorTexture(VDScreen::width(), VDScreen::height(), VDTexture::eRGB, VDTexture::eRGB, VDTexture::eUnsignedByte,  0);
					VDRenderSetting::getForwardFramebuffer()->setFlag(VDObject::eStatic | VDRenderSetting::getForwardFramebuffer()->getFlag());
				}

			}
			break;
		}
	}

	/*	Set rendering path.	*/
	settings->renderingflag = sRenderingPath;
}

VDRenderSetting::RenderPipeline VDRenderSetting::getRenderingPath(void){return (RenderPipeline)gRenderSettings.renderingflag;}



void VDRenderSetting::setFrameBufferSize(int width, int height){
	switch(VDRenderSetting::getRenderingPath()){
	case VDRenderSetting::eForwardRendering:
		VDRenderSetting::getForwardFramebuffer()->resize(width, height);
		break;
	default:
		VDDebug::criticalLog("No valid rendering path framebuffer.\n");
		break;
	}
	if(VDRenderSetting::getSettings()->posttexture){
		VDRenderSetting::getSettings()->posttexture->resize(width, height);
	}
}

VDRenderTexture* VDRenderSetting::getForwardFramebuffer(void){return gRenderSettings.forward;}

VDRenderTexture* VDRenderSetting::getRenderingPathFrameBuffer(RenderPipeline sRenderingPath){
	switch(VDRenderSetting::getRenderingPath()){
	case VDRenderSetting::eForwardRendering:
		return VDRenderSetting::getForwardFramebuffer();
	default:
		return NULL;
	}
}

void VDRenderSetting::useFog(bool fog){	/*	TODO fix such that there is a seperate variable for enable and disable.	*/
	VDRenderSetting::setFogType(fog ? FogFlag::eFogEnable : FogFlag::eFogDisable);
}


bool VDRenderSetting::isFogEnable(void){return getFogType() != 0;}

void VDRenderSetting::setFogType(FogFlag fogtype){
	VDScene::getScene()->uniform.engineState.fogType = fogtype;
}
VDRenderSetting::FogFlag VDRenderSetting::getFogType(void){
	return (VDRenderSetting::FogFlag)VDScene::getScene()->uniform.engineState.fogType;
}

void VDRenderSetting::setFogMinDistance(float start){
	VDScene::getScene()->uniform.engineState.fogStart = start;
}
float VDRenderSetting::getFogMinDistance(void){
	return VDScene::getScene()->uniform.engineState.fogStart;
}

void VDRenderSetting::setFogMaxDistance(float end){
	VDScene::getScene()->uniform.engineState.fogEnd = end;
}
float VDRenderSetting::getFogMaxDistance(void){
	return VDScene::getScene()->uniform.engineState.fogEnd;
}

void VDRenderSetting::setFogColor(const VDColor& color){
	VDScene::getScene()->uniform.engineState.fogColor = color;
}
VDColor VDRenderSetting::getFogColor(void){
	return VDScene::getScene()->uniform.engineState.fogColor;
}

void VDRenderSetting::setFogDensity(float density){
	VDScene::getScene()->uniform.engineState.fogDensity = density;
}
float VDRenderSetting::getFogDensity(void){
	return VDScene::getScene()->uniform.engineState.fogDensity;
}



void VDRenderSetting::setAmbientColor(const VDColor& color){
	VDScene::getScene()->ambientColor = color;
	VDScene::getScene()->uniform.engineState.ambientColor = color;
}
VDColor VDRenderSetting::getAmbientColor(void){
	return VDScene::getScene()->ambientColor;
}


void VDRenderSetting::setAmbientIntensity(float intensity){
	VDScene::getScene()->uniform.engineState.ambientIntensity = intensity;
}
float VDRenderSetting::getAmbientIntensity(void){
	return VDScene::getScene()->uniform.engineState.ambientIntensity;
}

void VDRenderSetting::setImageAmbient(VDCubeMap* cubemap, bool compute){
	if(VDScene::getScene()->ambientImageBased != NULL)
		VDScene::getScene()->ambientImageBased->deincrement();

	if(compute){

	}
	VDScene::getScene()->ambientImageBased = cubemap;



	/*	generate image based ambient lightning.	*/
	//if(!engine.scene.ambientImageBased)
	//	engine.scene.ambientImageBased = new VDCubeMap(128, skybox->getCubeMap()->getinternalFormat());


	//VDCubeMap* imagetex = engine.scene.ambientImageBased;
	//VDCubeMap* tex = skybox->getCubeMap();
	//for(int x = 0; x < 6; x++){
	//	void* pixels = NULL;
		//pixels = tex->getPixelData(0, tex->getinternalFormat(), tex->getType());
		/*	downscale	*/

		/*	blur	*/


		/**/
	//	imagetex->setPixelData(0, imagetex->width(),
	//			imagetex->width(),
	//			0, imagetex->getinternalFormat(),
	//			imagetex->getinternalFormat(),
	//			VDTexture::eByte, pixels);

	//	free(pixels);
	//}


	/*	bind image based ambient cubemap.	*/
	VDScene::getScene()->ambientImageBased->bind(VDShaderConstant::eAmbientImageBased);
}
VDCubeMap* VDRenderSetting::getImageAmbient(void){
	return VDScene::getScene()->ambientImageBased;
}

void VDRenderSetting::setAmbientType(VDRenderSetting::AmbientType type){
	VDScene::getScene()->ambientType = type;

	/*	if image based and there is an skybox. Then generate the imagebased.	*/
	if( ( type == VDRenderSetting::eImageBased ) && VDRenderSetting::getSkyBox()){
		if(VDRenderSetting::getSkyBox()->getCubeMap()){

		}
	}/*	*/

}
VDRenderSetting::AmbientType VDRenderSetting::getAmbientType(void){
	return (VDRenderSetting::AmbientType)VDScene::getScene()->ambientType;
}

void VDRenderSetting::setSkyBox(VDSkyBox* skybox){

	VDScene::getScene()->skybox = skybox;

	if(skybox){
		if(skybox->getCubeMap()){
			skybox->getCubeMap()->bind(VDShaderConstant::eSkyBox);

			setImageAmbient(skybox->getCubeMap());
		}
	}

	/*	update */
	VDRenderSetting::setAmbientType(VDRenderSetting::getAmbientType());
}
VDSkyBox* VDRenderSetting::getSkyBox(void){
	return VDScene::getScene()->skybox;
}

unsigned int VDRenderSetting::getFlag(void){return gRenderSettings.flag;}

VDEngineRenderSettings* VDRenderSetting::getSettings(void){
	return &VDRenderSetting::gRenderSettings;
}

