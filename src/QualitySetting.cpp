#include <Core/VDDebug.h>
#include <Core/VDEngine.h>
#include <Core/VDEngineCore.h>
#include <Core/VDQualitySetting.h>
#include <DataStructure/VDVector.h>
#include <GL/glew.h>
#include <Misc/VDMath.h>
#include <Rendering/Texture/VDCubeMap.h>
#include <Rendering/Texture/VDRenderTexture.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Rendering/VDLight.h>
#include <Rendering/VDRenderBuffer.h>
#include <Rendering/VDShader.h>
#include <stddef.h>
#include <Scene/VDScene.h>
#include <SDL2/SDL_video.h>
#include <VDSimpleType.h>
#include <VDSystemInfo.h>
#include <cfloat>
#include <cmath>
#include <map>

/**
 *
 */
typedef struct vd_engine_quality_settings{

	bool useShadow;
	unsigned int shadowsFilter;
	float shadowdistance;

	bool useAntiAliasing;
	int anitAlising;
	int sampleMode;
	int sampleCount;

	unsigned int culling;
	unsigned int textureQuality;
	float anisotropic;				/*	Default texture anisotropic.	*/


	int textureLod;
	unsigned int TextureQuality;
	unsigned int colorspace;
	bool vsync;

}VDEngineQualitySettings;


VDEngineQualitySettings gQualitySettings = {0};

void VDQualitySetting::useShadow(bool shadow){
	shadow = VDSystemInfo::supportsShadows() ? shadow : false;
	gQualitySettings.useShadow = shadow;

	if(shadow){
		VDQualitySetting::setShadowFilter((ShadowFilter)gQualitySettings.shadowsFilter);
	}
	else{
		VDQualitySetting::ShadowFilter filter = VDQualitySetting::getShadowFilter();
		VDQualitySetting::setShadowFilter((ShadowFilter)0);
		gQualitySettings.shadowsFilter = filter;


		/*	clean all depth buffer */
		for(int x = 0; x < VDScene::getScene()->lightcollection.size(); x++){
			if(VDScene::getScene()->lightcollection[x]->getShadowTexture()){
				VDScene::getScene()->lightcollection[x]->getShadowTexture()->clear();
			}
		}

	}
}

VDQualitySetting::ShadowFilter VDQualitySetting::getShadowFilter(void){
	return (VDQualitySetting::ShadowFilter)gQualitySettings.shadowsFilter;
}

void VDQualitySetting::setShadowFilter(ShadowFilter filter){
	gQualitySettings.shadowsFilter = filter;
	VDScene::getScene()->uniform.engineState.shadow = filter;
	VDTexture texture;
	register VDLight* light;

	const char* shadfunc2D;
	const char* shadfuncCube;

	if(VDSystemInfo::supportShaderSubRoutine()){
		for(ShaderCollection::iterator it = shaderCollection.begin(); it != shaderCollection.end(); it++){
			if(it->second == NULL){
				continue;
			}

			switch(filter){
			case eSimple:
				shadfunc2D = "getShadowFactor";
				shadfuncCube = "getShadowCubeFactor";
				break;
			case ePCF:
				shadfunc2D = "getShadowFactorPCF";
				shadfuncCube = "getShadowCubeFactorPCF";
				break;
			case eVariance:
				shadfunc2D =  "getVarianceShadow";
				shadfuncCube = "getShadowCubeFactorVariance";
				break;
			default:
				shadfunc2D =  "getNoneShadow";
				shadfuncCube =  "getNoneShadow";
			}

			it->second->setSubRoutineTmp((VDShader::ShaderType)GL_FRAGMENT_SHADER, "getCubeShadow", shadfuncCube);
			it->second->setSubRoutineTmp((VDShader::ShaderType)GL_FRAGMENT_SHADER, "getShadow", shadfunc2D);
		}
	}

	/*	make shadow maps configured for correspondg filter.	*/
	switch(filter){
	case eSimple:
		for(int x = 0; x < VDScene::getScene()->lightcollection.size(); x++){
			light = VDScene::getScene()->lightcollection[x];
			if(!VDScene::getScene()->lightcollection[x]->isShadowBufferAttached())
				continue;

			texture = VDScene::getScene()->lightcollection[x]->getShadowTexture()->getTextureAttachment(0, VDRenderTexture::eDepthAttachment);
			texture.setInternalFormat(VDTexture::eDepthComponent, GL_FLOAT);
			glBindTexture(texture.getTarget(), texture.getTexture());
			glTexParameteri(texture.getTarget(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(texture.getTarget(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glBindTexture(texture.getTarget(),0);
		}
		break;
	case ePCF:
		for(int x = 0; x < VDScene::getScene()->lightcollection.size(); x++){
			light = VDScene::getScene()->lightcollection[x];
			if(!VDScene::getScene()->lightcollection[x]->isShadowBufferAttached())
				continue;

			texture = VDScene::getScene()->lightcollection[x]->getShadowTexture()->getTextureAttachment(0, VDRenderTexture::eDepthAttachment);
			texture.setInternalFormat(VDTexture::eDepthComponent, GL_FLOAT);
			glBindTexture(texture.getTarget(), texture.getTexture());
			glTexParameteri(texture.getTarget(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(texture.getTarget(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glBindTexture(texture.getTarget(), 0);
		}
		break;
	case eVariance:

		for(int x = 0; x < VDScene::getScene()->lightcollection.size(); x++){
			light = VDScene::getScene()->lightcollection[x];
			if(!VDScene::getScene()->lightcollection[x]->isShadowBufferAttached())
				continue;

			texture = VDScene::getScene()->lightcollection[x]->getShadowTexture()->getTextureAttachment(0, VDRenderTexture::eDepthAttachment);
			VDScene::getScene()->lightcollection[x]->getShadowTexture()->setTextureAttachment(VDRenderTexture::eDepthAttachment, (VDTexture*)NULL);

			if(light->getType() != VDLight::ePoint){
			VDRenderBuffer depthbuffer = VDRenderBuffer();
			depthbuffer.setStorage(light->getShadowTexture()->width(), light->getShadowTexture()->height(), VDTexture::eDepthComponent32);
			VDScene::getScene()->lightcollection[x]->getShadowTexture()->setAttachment(VDRenderTexture::eDepthAttachment, &depthbuffer);
			}else{
				VDCubeMap cubedepth = VDCubeMap(light->getShadowTexture()->width());
				cubedepth.setInternalFormat(VDTexture::eDepthComponent32, GL_FLOAT);
				light->getShadowTexture()->setTextureAttachment(VDRenderTexture::eDepthAttachment, &cubedepth);
			}

			texture.setInternalFormat(VDTexture::eRGB, VDTexture::eFloat);
			glBindTexture(texture.getTarget(), texture.getTexture());
			glTexParameteri(texture.getTarget(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(texture.getTarget(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glBindTexture(texture.getTarget(), 0);
			VDScene::getScene()->lightcollection[x]->getShadowTexture()->setTextureAttachment(VDRenderTexture::eColorAttachment0, &texture);

		}
		break;
	case 0:
	default:
		break;
	}
}

void VDQualitySetting::setShadowDistance(float distance){
	gQualitySettings.shadowdistance = VDMath::clamp<float>(distance, 0.1, FLT_MAX);
}

float VDQualitySetting::getShadowDistance(void){
	return gQualitySettings.shadowdistance;
}

void VDQualitySetting::setSamplerMode(SampleType mode){

	switch(mode){
	case VDQualitySetting::eSSAA:
		break;
	case VDQualitySetting::eMSAA:
		if(VDSystemInfo::getCompatibility()->sMSAA){	/*	TODO VDSystemInfo::getCompatibility()->sframebufferMSAA*/
			gQualitySettings.sampleMode = mode;
			VDQualitySetting::setAntaiAlisingSampling(VDQualitySetting::getAntaiAlisingSampling());
		}
		else{
			VDDebug::errorLog("MSAA not support : MSAA framebuffer not supported\n");
			setSamplerMode(getSampleMode());
		}
		break;
	case VDQualitySetting::eSA:
		break;
	default:
		gQualitySettings.sampleMode = VDQualitySetting::SampleType::eNone;
	}
}

VDQualitySetting::SampleType VDQualitySetting::getSampleMode(void){
	return (SampleType)gQualitySettings.sampleMode;
}

void VDQualitySetting::useAntaiAlising(bool use){
	if(use && !gQualitySettings.useAntiAliasing){
		VDQualitySetting::setSamplerMode(VDQualitySetting::getSampleMode());
		VDQualitySetting::setAntaiAlisingSampling(VDQualitySetting::getAntaiAlisingSampling());
		if(VDQualitySetting::getSampleMode() == eMSAA){
			glEnable(GL_MULTISAMPLE);
		}
	}
	else{
		glDisable(GL_MULTISAMPLE);
	}
	gQualitySettings.useAntiAliasing = use;
}

void VDQualitySetting::setAntaiAlisingSampling(unsigned int aaSample){
	if(aaSample){
		/*	setting up MSAA*/
		if(VDQualitySetting::getSampleMode() == VDQualitySetting::SampleType::eMSAA){

			/*	check if number of sample is a power of two value.	*/
			if((float)VDMath::modd((double)log2(aaSample)) != 0.0f){
				VDDebug::errorLog("MSAA has to be in power of two.\n");
				return;
			}

			if(VDQualitySetting::getAntaiAlisingSampling() == aaSample){
				return;
			}


			unsigned int sample = VDSystemInfo::numMSAASampling();
			glGetIntegerv(GL_MAX_INTEGER_SAMPLES, (GLint*)&sample);
			aaSample = VDMath::clamp<unsigned int>(aaSample, 0, sample);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, aaSample);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);


			/*	TODO resolved why it does not really work.	*/
			SDL_GLContext glccurrent = VDEngine::getOpenGLContext();
			SDL_GLContext* glc = VDEngine::querySharedOpenGLContext();
			if(glc == NULL){
				VDDebug::criticalLog("Failed to create shared OpenGL context revert back.\n");
				return;
			}
			SDL_GL_DeleteContext(glccurrent);
			VDEngine::bindOpenGLContext(*glc);
			engine.glc = (VDOpenGLContext)*glc;

			/**/
			//glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_FASTEST);

		}



		//glHint(GL_NV_multisample_filter_hint,
		//glGetMultisamplefv(
		//glSampleMaski(
		//glSampleCoverageARB(aaSample, SDL_FALSE);
		// set the amount as well.
	}

	gQualitySettings.sampleCount = aaSample;
}

unsigned int VDQualitySetting::getAntaiAlisingSampling(void){
	return gQualitySettings.sampleCount;
}


void VDQualitySetting::setCulling(Culling culling){

	if(culling == VDQualitySetting::Culling::eEarlyZRejection){
		if(!VDSystemInfo::getCompatibility()->sShaderImageLoadStorage){
			VDDebug::warningLog("Early hardware z rejection is not supported.\n");
		}
	}else{

	}

	gQualitySettings.culling = culling;
}

VDQualitySetting::Culling VDQualitySetting::getCulling(void){
	return (VDQualitySetting::Culling)gQualitySettings.culling;
}
void VDQualitySetting::setTextureLod(unsigned int lodLevel){
	VDTexture* text;
	for(map<const char*, VDTexture2D*>::iterator x = VDScene::getScene()->textureCollection.begin(); x != VDScene::getScene()->textureCollection.end(); x++){
		text = (*x).second;
		if(text){
			if(text->isTexture2D()){
				x->second->setBaseLevel(lodLevel);
			}
		}
	}
	gQualitySettings.textureLod = lodLevel;
}

int VDQualitySetting::getTextureLod(void){
	return gQualitySettings.textureLod;
}


void VDQualitySetting::setTextureAnisotropy(float anisotropylevel){
	/*	TODO clmap the value.	*/
	for(map<const char*, VDTexture2D*>::iterator x =  VDScene::getScene()->textureCollection.begin(); x != VDScene::getScene()->textureCollection.end(); x++){
		x->second->setAnisoLevel(anisotropylevel);
	}
	gQualitySettings.anisotropic = anisotropylevel;
}

float VDQualitySetting::getTextureAnisotropy(void){
	return gQualitySettings.anisotropic;
}


void VDQualitySetting::setColorSpace(ColorSpace colorspace){
	switch (colorspace) {
		case eLinear:
			glDisable(GL_FRAMEBUFFER_SRGB);
			break;
		case eGamma:
			glDisable(GL_FRAMEBUFFER_SRGB);
			break;
		case eSrga:
			glEnable(GL_FRAMEBUFFER_SRGB);
			break;
		default:
			glDisable(GL_FRAMEBUFFER_SRGB);
			break;
	}

	gQualitySettings.colorspace = colorspace;
}

VDQualitySetting::ColorSpace VDQualitySetting::getColorSpace(void){
	return (VDQualitySetting::ColorSpace)gQualitySettings.colorspace;
}

void VDQualitySetting::setVSync(bool enable){
	SDL_GL_SetSwapInterval(enable);
	gQualitySettings.vsync = enable;
}

bool VDQualitySetting::getVSync(void){
	return gQualitySettings.vsync;
}

static inline bool VDQualitySetting::isShadowEnable(void){return gQualitySettings.useShadow;}

static bool VDQualitySetting::isAntiAliasingEnable(void){ return gQualitySettings.useAntiAliasing;}
