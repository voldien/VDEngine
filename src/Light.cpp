#include <Core/VDBehavior.h>
#include <Core/VDDebug.h>
#include <Core/VDEngineCore.h>
#include <Core/VDQualitySetting.h>
#include <DataStructure/VDStackAllactor.h>
#include <DataStructure/VDVector.h>
#include <GL/glew.h>
#include <hpmcpp/HCQuaternion.h>
#include <hpmcpp/HCVector3.h>
#include <Misc/VDMath.h>
#include <Rendering/Texture/VDCubeMap.h>
#include <Rendering/Texture/VDRenderTexture.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Rendering/VDCamera.h>
#include <Rendering/VDLight.h>
#include <Rendering/VDMesh.h>
#include <Rendering/VDRender.h>
#include <Rendering/VDRenderingAPICache.h>
#include <Rendering/VDRenderSetting.h>
#include <Rendering/VDShader.h>
#include <Rendering/VDUniformBuffer.h>
#include <stdlib.h>
#include <Scene/VDFrustum.h>
#include <Scene/VDScene.h>
#include <Scene/VDTransform.h>
#include <SDL2/SDL_stdinc.h>
#include <Rendering/VDRenderSetting.h>
#include <Rendering/VDShader.h>
#include <VDSimpleType.h>
#include <VDSystemInfo.h>
#include <cstring>

using namespace std;

typedef VDVector<VDLight*> VDLightCollection;
typedef VDLightCollection::Iterator VDLightCollectionIterator;
VDLightCollectionIterator nonshadowLight;
VDLightCollectionIterator shadowLight;
/*	TODO check if it's possible to use*/

VDLight::VDLight(void) : VDFrustum(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f){
	this->setColor(VDColor(1.0f));
	this->setIntensity(1.0f);
	this->type = 0;
	this->range = 10.0f;
	this->outerCone = 0.90f;
	this->innerCone = 0.80f;
	this->flag = VDLight::eMediumShadowQuality | VDLight::ePoint;
	this->setShadowStrength(1.0);
	this->setShadowTexture(NULL);
	this->setType(VDLight::ePoint);
	this->setAttenuation(VDLight::Attenuation::eConstant, 1.0);
	this->setAttenuation(VDLight::Attenuation::eLinear, 0.1);
	this->setAttenuation(VDLight::Attenuation::eQuadratic, 0.025);
	this->setShadowBias(0.005f);

	this->quadraticAtteuation = 0.0075f;
	this->linearAtteuation = 0.55f;
	this->constAtteuation = 1.0f;
}

VDLight::VDLight(const VDLight& light){
	*this = light;
}

VDLight::VDLight(LightType lightType) : VDFrustum(-5.0f, 5.0f, -5.0f, 5.0f, -5.0f, 5.0f){
	this->setColor(VDColor(1.0f));
	this->setIntensity(1.0f);
	this->range = 10.0f;
	this->outerCone = 0.80f;
	this->innerCone = 0.90f;
	this->shadowStrength = 1.0f;
	this->flag = eMediumShadowQuality | VDLight::ePoint;

	this->setShadowTexture(NULL);
	this->setType(lightType);
	this->setShadowBias(0.005f);

	this->quadraticAtteuation = 0.0075f;
	this->linearAtteuation = 0.055f;
	this->constAtteuation = 1.0f;
}

void VDLight::instanceInitilize(void){

}


void VDLight::initializeComponent(void){
	//gLightCollection.push_back(this); // apply componet
	VDScene::getScene()->uniform.engineState.numLights++;

	this->setType((VDLight::LightType)getType());
	if(getType() != VDLight::ePoint){
		VDScene::getScene()->lightcollection.push_back(this);
		//gLightCollection.insert(gLightCollection.begin(), this);
	}
	else{
		VDScene::getScene()->lightcollection.push_back(this);
		//gLightCollection.insert(gLightCollection.end(), this);
	}
}

void VDLight::onEnable(void){
	/*	inform the uniform buffer its to be rendered */

}

void VDLight::onDisable(void){
	/*	inform the uniform buffer its not to be rendered */

}

void VDLight::onDestroy(void){

	this->detachShadowComponent();
	VDScene::getScene()->uniform.engineState.numLights;
	VDScene::getScene()->uniform.engineState.numLights--;
}

VDBehavior* VDLight::copyComponent(unsigned int& dataSize){
	VDLight* light = (VDLight*)malloc(sizeof(VDLight));
	memcpy(light,this, sizeof(VDLight));
	dataSize = sizeof(VDLight);
	return (VDBehavior*)light;
}

void VDLight::setAttenuation(VDLight::Attenuation lightAttenuation, float attenuation){
	switch(lightAttenuation){
	case eConstant:
		this->constAtteuation = attenuation;
		break;
	case eLinear:
		this->linearAtteuation = attenuation;
		break;
	case eQuadratic:
		this->quadraticAtteuation = attenuation;
		break;
	default:
		break;
	}
}

float VDLight::getAtteuation(VDLight::Attenuation lightAttenuation){
	switch(lightAttenuation){
	case eConstant:
		return this->constAtteuation;
	case eLinear:
		return this->linearAtteuation;
	case eQuadratic:
		return this->quadraticAtteuation;
	default:
		return 0.0f;
	}
}


void VDLight::setType(VDLight::LightType lighType){

	/*	*/
	if(this->getType() == lighType){
		VDDebug::warningLog("Invalid light type; %d.\n", lighType);
		return;
	}

	switch(this->getType()){
	case VDLight::eDirection:
		VDScene::getScene()->uniform.engineState.numDirection = VDMath::clamp<int>(VDScene::getScene()->uniform.engineState.numDirection - 1, 0 , 0xfffffff);
		break;
	case VDLight::ePoint:
		VDScene::getScene()->uniform.engineState.numPoint = VDMath::clamp<int>(VDScene::getScene()->uniform.engineState.numPoint - 1, 0 , 0xfffffff);
		break;
	case VDLight::eSpot:
		VDScene::getScene()->uniform.engineState.numSpot = VDMath::clamp<int>(VDScene::getScene()->uniform.engineState.numSpot - 1, 0 , 0xfffffff);
		break;
	}


	/**/
	switch(lighType){
	case VDLight::eDirection:
		VDScene::getScene()->uniform.engineState.numDirection += 1;
		this->setOrth(VDMath::infinity, -VDMath::infinity, VDMath::infinity, -VDMath::infinity, VDMath::infinity, -VDMath::infinity);
		break;
	case VDLight::ePoint:
		VDScene::getScene()->uniform.engineState.numPoint += 1;
		this->setOrth(getRange(),-getRange(),getRange(),-getRange(),getRange(),-getRange());
		break;
	case VDLight::eSpot:
		VDScene::getScene()->uniform.engineState.numPoint += 1;
		this->setPerspective( VDMath::deg2Rad(getOuterCone() * 90.0f ), 1, 0.5, getRange());
		break;
	}


	/*	TODO : fix shadow mapping type*/
	if(this->getShadowTexture()){

	}

	this->type = lighType;

}

void VDLight::setIntensity(float intensity){
	this->intensity = intensity;
}

void VDLight::setColor(const VDColor& color){
	this->diffuseColor = color;
}

void VDLight::setOuterCone(float Cutoff){
	this->outerCone = VDMath::clamp( Cutoff, 0.0, 1.0);
}

void VDLight::setInnerCone(float InnerCone){
	this->innerCone = VDMath::clamp( InnerCone, 0.0, 1.0);
}

void VDLight::setRange(float range){
	this->range = VDMath::max<float>(range, 0.1);
	this->setFar(range);
	this->calcFrustumPlanes(this->transform()->getPosition(), VDVector3::up(), VDVector3::forward());
}


void VDLight::setShadowStrength(float strenght){
	this->shadowStrength = strenght;
}

void VDLight::setShadowBias(float bias){
	this->shadowBias = bias;
}


void VDLight::enableShadow(bool enabled){

	if(enabled && VDSystemInfo::getCompatibility()->sShadow){
		if(!this->isShadowBufferAttached()){
			this->attachShadowComponent(eMediumShadowQuality);
		}


	}
	else{
		this->detachShadowComponent();
		VDScene::getScene()->lightcollection.push_front(this);
	}

	/*	TODO relocate.	*/
	if(enabled){
		switch(this->getType()){
		case eDirection:
			VDScene::getScene()->uniform.engineState.numShadowDirection++;
			break;
		case eSpot:
			VDScene::getScene()->uniform.engineState.numShadowSpot++;
			break;
		case ePoint:
			VDScene::getScene()->uniform.engineState.numShadowPoint++;
			break;
		default:
			break;
		}
	}
}

void VDLight::setShadow(unsigned int shadowFlag){
	if((shadowFlag & eHardShadow) != 0 || (shadowFlag & eSoftShadow) != 0){
		// there is a need a shadow mapping.
		this->attachShadowComponent(shadowFlag);
		this->flag |= eShadowEnable;
	}
	else{
		this->detachShadowComponent();
		//attachShadowComponent(ShadowFlag);
		// shadow not applyed.
		this->flag = (~eShadowEnable & this->flag);
	}
	this->flag |= shadowFlag;

}

void VDLight::setShadowSize(unsigned int size){
	if(this->getShadowTexture()){
		size = VDMath::min<int>(VDSystemInfo::getCompatibility()->sMaxTextureSize, size);
		this->getShadowTexture()->resize(size, size);
	}
}

int VDLight::getShadowSize(void)const{
	if(this->getShadowTexture()){
		return this->getShadowTexture()->width();
	}
	return 0;
}

void VDLight::setShadowTexture(VDRenderTexture* renderTexture){
	this->shadowBuffer = renderTexture;
}

VDMatrix4x4 VDLight::getShadowMatrix(unsigned int pointLightIndex)const{
	VDMatrix4x4 lightprojectM;
	VDTransform* transform = this->transform();

	float shadowDist = VDQualitySetting::getShadowDistance();
	switch(this->getType()){
	case VDLight::eDirection:

		lightprojectM = HCMatrix4x4::rotate(transform->getRotation().conjugate());

		if(VDCamera::getCurrentCamera()){
			VDVector3 pos = VDCamera::getCurrentCamera()->transform()->getPosition();
			lightprojectM *= HCMatrix4x4::translate(-VDCamera::getCurrentCamera()->transform()->getPosition());
		}

		/*	TODO improve position in respect to the orth box.*/

		lightprojectM = HCMatrix4x4::orth(
				-shadowDist,
				shadowDist,
				-shadowDist,
				shadowDist,
				-shadowDist,
				shadowDist) * lightprojectM;
	break;
	case VDLight::ePoint:{
		VDQuaternion projangle = VDCubeMap::getCubePlaneQuaternion(pointLightIndex + VDTexture::eCubeMapPositiveX);

		lightprojectM = VDMatrix4x4::rotate(projangle.conjugate());

		lightprojectM *= VDMatrix4x4::translate(-transform->getPosition());

		lightprojectM = (VDMatrix4x4::perspective(VDMath::deg2Rad( 90.0f ), 1.0f, 0.15f, 0.15f + this->getRange()) * lightprojectM);

	}break;
	case VDLight::eSpot:
		lightprojectM = VDMatrix4x4::rotate(transform->getRotation().conjugate());

		lightprojectM *= VDMatrix4x4::translate(-transform->getPosition());

		lightprojectM = (VDMatrix4x4::perspective(VDMath::deg2Rad( this->getOuterCone() * 180.0f ) , 1.0f, 0.5f, 0.5f + this->getRange()) * lightprojectM);

		break;
	default:
		break;
	}


	return lightprojectM;
}


int VDLight::attachShadowComponent(unsigned int shadowFlag){
	unsigned int size = 128;
	if(shadowFlag == 0){
		return SDL_FALSE;
	}

	if( shadowFlag & eLowShadowQuality ){size = 256;}
	else if( shadowFlag & eMediumShadowQuality ){size = 512;}
	else if( shadowFlag & eHighShadowQuality ){size = 1024;}
	else if( shadowFlag & eUltraShadowQuality ){size = 2048;}
	else if( shadowFlag & eSuperShadowQuality ){size = 4096;}

	/*	get the minium value in order to fix max texture size.	*/
	size = VDMath::min<int>(VDSystemInfo::getCompatibility()->sMaxTextureSize, size);

	if( !(this->getType() & VDLight::ePoint) ){

		if(!this->getShadowTexture()){
			this->shadowBuffer = VDRenderTexture::ShadowMap(size, size, VDTexture::eDepthComponent, VDTexture::eDepthComponent32, VDTexture::eFloat);
		}
		else{
			this->getShadowTexture()->resize(size, size);
		}
	}
	else
		this->shadowBuffer = VDRenderTexture::ShadowCubeMap(size, size);

	if(this->getShadowTexture()->isValid()){

	}

	return SDL_TRUE;
}


void VDLight::detachShadowComponent(void){
	if(this->isShadowBufferAttached()){
		this->shadowBuffer->deincrement();
		delete this->shadowBuffer;
		this->shadowBuffer = NULL;
	}
}

void VDLight::updateLightUniformLocation(VDStackAllocator* allocator){
	//allocator = (VDStackAllocator*)((VDTaskSchedule::VDTaskPackage*)allocator)->begin;
	UniformLight* uniformLight = (UniformLight*)allocator->fetch(VDScene::getScene()->uniform.engineState.numLights * sizeof(UniformLight));
	register VDLight* light;

	const unsigned int shadowOffset = 128;
	const unsigned int DirectionLightOffset = 128 * 4;
	const unsigned int PointLightOffset = 1024 + DirectionLightOffset;
	const unsigned int SpotLightOffset = 1024 + PointLightOffset;

	unsigned int lightIndex = 0;

	VDScene::getScene()->lightinfo.directIndices.clear();
	VDScene::getScene()->lightinfo.pointIndices.clear();
	VDScene::getScene()->lightinfo.spotIndices.clear();



	VDScene::getScene()->lightinfo.lightbuffer.bind();
	for(int x = 0; x < VDScene::getScene()->lightcollection.size(); x ++){
		light = VDScene::getScene()->lightcollection[x];

		/**/
		if(light->getType() != VDLight::ePoint){
			uniformLight[x].direction = light->transform()->getRotation().forward().normalize();
		}
		uniformLight[x].angle = light->getOuterCone();
		uniformLight[x].color = light->getColor();
		uniformLight[x].intensity = light->getIntensity();
		uniformLight[x].range = light->getRange();
		uniformLight[x].shadowStrength = light->getShadowStrenght();
		uniformLight[x].type = light->isEnabled() ? light->getType() : 0;
		uniformLight[x].position = light->transform()->getPosition();
		uniformLight[x].shadowIndex = lightIndex;
		/**/
		uniformLight[x].shadowBias = light->getShadowBias();


		/*	update transform.	*/
		light->calcFrustumPlanes(light->transform()->getPosition(),
				light->transform()->transformDirection(VDVector3::forward()),
				light->transform()->transformDirection(VDVector3::up()),
				light->transform()->transformDirection(VDVector3::right()) );


		/*	compute indices.	*/
		if(light->isShadowBufferAttached() && VDQualitySetting::isShadowEnable()){
			lightIndex++;
			continue;
		}
		switch(light->getType()){
		case VDLight::ePoint:
			VDScene::getScene()->lightinfo.pointIndices.push(x);
			break;
		case VDLight::eDirection:
			VDScene::getScene()->lightinfo.directIndices.push(x);
			break;
		case VDLight::eSpot:
			VDScene::getScene()->lightinfo.spotIndices.push(x);
			break;
		default:
			break;
		}

	}

	/*	update light buffer.	*/
	VDScene::getScene()->lightinfo.lightbuffer.write(uniformLight, 0 ,
			VDScene::getScene()->uniform.engineState.numLights * sizeof(UniformLight));

	/*	update light indices.	*/
	VDScene::getScene()->lightinfo.lightIndices.write(&VDScene::getScene()->lightinfo.directIndices[0],
			DirectionLightOffset * sizeof(GLint),
			VDScene::getScene()->lightinfo.directIndices.size() * sizeof(GLint));
	VDScene::getScene()->lightinfo.lightIndices.write(&VDScene::getScene()->lightinfo.pointIndices[0],
			PointLightOffset * sizeof(GLint),
			VDScene::getScene()->lightinfo.pointIndices.size() * sizeof(GLint));
	VDScene::getScene()->lightinfo.lightIndices.write(&VDScene::getScene()->lightinfo.spotIndices[0],
			SpotLightOffset * sizeof(GLint),
			VDScene::getScene()->lightinfo.spotIndices.size() * sizeof(GLint));

}


void VDLight::drawLightAccumulationShadow(VDCamera* camera){
	unsigned int numShadow = 0;
	unsigned int samplerCount = 0;
	unsigned int cubeSamplerCount = 0;
	int x,y;
	VDMesh::Primitive drawmode = VDMesh::eTriangles;
	register VDLight* light;
	register VDShader* shadowShader;
	register VDShader* shadowCubeShader;
	register VDShader* shadowCascade;
	VDEngineLightShadow shadowUniform[32];

	const VDMatrix4x4 biasMatrix = VDMatrix4x4::biasMatrix();

	/*	clear indices buffer.	*/
	VDScene::getScene()->lightinfo.shadowDirectionIndices.clear();
	VDScene::getScene()->lightinfo.shadowSpotIndices.clear();
	VDScene::getScene()->lightinfo.shadowPointIndices.clear();

	/*	*/
	switch(VDQualitySetting::getShadowFilter()){
		case VDQualitySetting::ShadowFilter::eSimple:
		case VDQualitySetting::ShadowFilter::ePCF:
			shadowShader = VDRenderSetting::getSettings()->lightShadowFirstPass;
			shadowCubeShader = VDRenderSetting::getSettings()->lightShadowCubeMap;
			break;
	}

	/*	*/
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	/**/
	for(x = 0; x < VDScene::getScene()->lightcollection.size(); x++){
		light = VDScene::getScene()->lightcollection[x];
		if(light->isDisabled() || light->isShadowBufferAttached() == false){
			continue;
		}


		/*	check if light frustum is visiable in camera frustum.*/
		/*
		if(camera->isFrustumCulling()){
			if(light->intersectionFrustum(*camera) == VDFrustum::eOut){
				continue;
			}
		}
		*/


		/*	add to shadow buffer.	*/
		switch(light->getType()){
		case VDLight::ePoint:
			VDScene::getScene()->lightinfo.shadowPointIndices.push(x);
			break;
		case VDLight::eDirection:
			VDScene::getScene()->lightinfo.shadowDirectionIndices.push(x);
			break;
		case VDLight::eSpot:
			VDScene::getScene()->lightinfo.shadowSpotIndices.push(x);
			break;
		default:
			break;
		}


		/*	bind shadow framebuffer.	*/
		light->getShadowTexture()->write();
		VDRenderingAPICache::setViewport(0, 0, light->getShadowTexture()->width(), light->getShadowTexture()->height());
		glClear(GL_DEPTH_BUFFER_BIT);

		/*	light sources except the point light.	*/
		if(light->getType() != VDLight::ePoint){
			memcpy(&shadowUniform[numShadow].shadow[0][0], &( biasMatrix * light->getShadowMatrix(0) )[0][0], sizeof(VDMatrix4x4) );
			samplerCount++;
			shadowShader->bind();
			VDRenderer::internalShadowDraw(shadowShader, light, drawmode);
		}
		else{
			memcpy(&shadowUniform[numShadow].shadow[0][0], (&( biasMatrix * light->getShadowMatrix(0) )[0][0]), sizeof(VDMatrix4x4) );
			cubeSamplerCount++;

			shadowCubeShader->bind();
			VDMatrix4x4 proj[6];
			VDMatrix4x4 glproj[6];
			for(int x = 0; x < 6; x++){
				glproj[x] =  light->getShadowMatrix(x);
			}
			glProgramUniformMatrix4fv(shadowCubeShader->getProgram(), shadowCubeShader->getMatrinxInfo()->viewprojection, 6, GL_FALSE, &glproj[0][0][0]);
			VDRenderer::internalShadowDraw(shadowCubeShader , light, drawmode);


		}

		/*	Unbind framebuffer.	*/
		light->getShadowTexture()->unBind();

		/*	perform guassian blur if shadow filter is Variance.	*/
		if( VDQualitySetting::getShadowFilter() == VDQualitySetting::ShadowFilter::eVariance ){


		}else{


		}

		/*	Increment shadow.	*/
		numShadow++;
	}/*	light sources*/

	const unsigned int shadowDirectionOffset = 128;
	const unsigned int shadowSpotOffset = 128 * 2;
	const unsigned int shadowPointOffset = 128 * 3;

	/*	update light indices.*/
	VDScene::getScene()->uniform.engineState.numShadows = numShadow;
	VDScene::getScene()->lightinfo.lightIndices.write(VDScene::getScene()->lightinfo.shadowDirectionIndices.getData(),
			shadowDirectionOffset * sizeof(GLint),
			VDScene::getScene()->lightinfo.shadowDirectionIndices.size() * sizeof(GLint));

	VDScene::getScene()->lightinfo.lightIndices.write(VDScene::getScene()->lightinfo.shadowSpotIndices.getData(),
			shadowSpotOffset * sizeof(GLint),
			VDScene::getScene()->lightinfo.shadowSpotIndices.size() * sizeof(GLint));

	VDScene::getScene()->lightinfo.lightIndices.write(VDScene::getScene()->lightinfo.shadowPointIndices.getData(),
			shadowPointOffset * sizeof(GLint),
			VDScene::getScene()->lightinfo.shadowPointIndices.size() * sizeof(GLint));


	/*	Update shadow buffer.	*/
	VDScene::getScene()->lightinfo.shadowbuffer.write(&shadowUniform[0],  sizeof(shadowUniform[0]) * numShadow);


	/*	reset framebuffer states.*/
	VDRenderingAPICache::bindFramebuffer(GL_FRAMEBUFFER, 0);


	/*	reset statements.	*/
	glCullFace(GL_BACK);
	glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
}


int VDLight::lightCount(void){
	return VDScene::getScene()->lightcollection.size();
}
