#include <Core/VDBehavior.h>
#include <Core/VDMatrix.h>
#include <Core/VDObject.h>
#include <GL/glew.h>
#include <malloc.h>
#include <Rendering/Texture/VDCubeMap.h>
#include <Rendering/VDMaterial.h>
#include <Rendering/VDMesh.h>
#include <Rendering/VDRender.h>
#include <Rendering/VDRenderingAPICache.h>
#include <Rendering/VDRenderSetting.h>
#include <Rendering/VDShader.h>
#include <Rendering/VDShaderCreator.h>
#include <Scene/VDScene.h>
#include <Scene/VDSkyBox.h>
#include <SDL2/SDL_stdinc.h>
#include <Utility/VDGeometryProcedure.h>
#include <VDSimpleType.h>
#include <cstring>


VDSkyBox::VDSkyBox(void) : VDBehavior(){

	this->material = VDMaterial::createMaterial();
	this->material->setName("SkyBox");

	//VDShader* _shader = VDShader::findShader("SkyBox");
	this->material->setShader(VDShaderCreator::SkyBox());
	this->skyBoxMesh = VDGeometryProcedure::createCube(3.0f, 0);
	this->cubeMap = NULL;

}

VDSkyBox::VDSkyBox(const VDSkyBox& skybox){
	VDBehavior::operator=(skybox);
	*this = skybox;
}

VDSkyBox::~VDSkyBox(void){
	delete skyBoxMesh;
	material->release();
}


void VDSkyBox::instanceInitilize(void){

}

void VDSkyBox::onEnable(void){

}

void VDSkyBox::onDisable(void){

}

void VDSkyBox::onDestroy(void){
	if(this == VDScene::getScene()->skybox){
		VDRenderSetting::setSkyBox(NULL);
	}
}

void VDSkyBox::initializeComponent(void){

}

VDBehavior* VDSkyBox::copyComponent(unsigned int& dataSize){
	VDSkyBox* skybox = (VDSkyBox*)malloc(sizeof(VDSkyBox));
	memcpy(skybox,this, sizeof(VDSkyBox));
	dataSize = sizeof(VDSkyBox);
	return (VDBehavior*)skybox;
}

void VDSkyBox::render(const VDQuaternion& quat){
	if(this->isDisabled() || this->getCubeMap() == NULL)
		return;

	VDMatrix::matrixMode(VDMatrix::eView);
	VDMatrix::pushMatrix();
	VDMatrix::identity(VDMatrix::eView);

	GLint OldCullFaceMode;
	//glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
	GLint OldDepthFuncMode;
	//glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

	VDRenderingAPICache::setState(GL_CULL_FACE, SDL_FALSE);
	VDRenderingAPICache::setState(GL_DEPTH_TEST, SDL_TRUE);
	VDRenderingAPICache::setState(GL_STENCIL_TEST, SDL_TRUE);
	VDRenderingAPICache::setState(GL_BLEND, SDL_FALSE);


	this->material->bind();
	VDMatrix::rotation(quat);
	glUniformMatrix4fv(this->material->getShader()->matrixInfo.modelViewProjectionMatrix, 1, GL_FALSE, (float*)&VDMatrix::getViewProjection()[0][0]);
	VDRenderer::drawMesh(this->skyBoxMesh);


	VDRenderingAPICache::setState(GL_CULL_FACE, 1);
	VDRenderingAPICache::setState(GL_DEPTH_TEST, 1);
	VDRenderingAPICache::setState(GL_STENCIL_TEST, 1);
	VDRenderingAPICache::setState(GL_BLEND, 0);

	VDMatrix::matrixMode(VDMatrix::eView);
	VDMatrix::popMatrix();
}

void VDSkyBox::setCubeMap(VDCubeMap* cubemap){
	this->cubeMap = cubemap;
	this->material->setTexture(0, cubemap);


	/*	update rendering setting*/
	if(VDRenderSetting::getSkyBox() == this){
		VDRenderSetting::setSkyBox(this);
	}
}

VDCubeMap* VDSkyBox::getCubeMap(void)const{
	return this->cubeMap;
}



VDSkyBox*  VDSkyBox::createDefaultSkyBox(VDCubeMap* cubeMap, const VDColor& color){
	VDSkyBox* skyBox = new VDSkyBox();
	skyBox->setCubeMap(cubeMap);
	return skyBox;
}

