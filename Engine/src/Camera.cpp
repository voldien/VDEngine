#include "Rendering/VDQualitySetting.h"
#include <Core/VDDebug.h>
#include <Core/VDInput.h>
#include <Core/VDLayer.h>
#include <Core/VDMatrix.h>
#include <Core/VDScreen.h>
#include <Core/VDTime.h>
#include <DataStructure/VDRect.h>
#include <DataStructure/VDSize.h>
#include <Physic/VDPhysic.h>
#include <Physic/VDRaycastHit.h>
#include <Rendering/VDCamera.h>
#include <Rendering/VDPostEffect.h>
#include <Rendering/VDRender.h>
#include <Rendering/VDRenderSetting.h>
#include <Rendering/VDShader.h>
#include <Scene/VDFrustum.h>
#include <Scene/VDScene.h>
#include <Scene/VDSkyBox.h>
#include <Scene/VDTransform.h>
#include <VDSimpleType.h>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iterator>
#include <malloc.h>
#include <vector>

using namespace std;

VDCamera::VDCamera() : VDFrustum() {
	this->setViewPort(VDRect(0, 0, 1.0f, 1.0f));
	this->setFov(70.0f);
	this->setFar(1000.0f);
	this->setNear(0.15f);
	this->flag = 0;
	this->renderTexture = nullptr;
	this->setProjectionMode(VDCamera::Perspective);
	this->setBackColor(VDColor(0));
	this->setCullingMask(VDLayer::getIndexByName("all"));
	this->setRenderTexture(nullptr);
	this->setClearMode(VDCamera::SkyBox);
	this->setClearFlag(VDCamera::eDepth);
	this->useFrustumCulling(true);
}

VDCamera::VDCamera(const VDCamera &camera) { *this = camera; }

void VDCamera::instanceInitilize() {}

void VDCamera::initializeComponent() {

	if (VDCamera::getMainCamera() == nullptr) {
		VDCamera::setMainCamera(this);
	}

	VDScene::getScene()->gCameraCollection.push_back(this);
	this->updateCameraMatrix();
}

void VDCamera::onEnable() { /*	*/
}

void VDCamera::onDisable() {
	if (isMainCamera()) {
	}

	for (int x = VDScene::getScene()->gCameraCollection.size() - 1; x >= 0; x--) {
		if (VDScene::getScene()->gCameraCollection[x] != this) { // If Camera In List Isn't this Camera
			// TODO DO something.

			break;
		}
	} /**/
}

void VDCamera::onDestroy() {
	for (vector<VDCamera *>::iterator x = VDScene::getScene()->gCameraCollection.begin();
		 x != VDScene::getScene()->gCameraCollection.end(); x++) {
		if (*x == this) {
			VDScene::getScene()->gCameraCollection.erase(x);
			break;
		}
	}
	if (isMainCamera()) {
	}
	for (int x = VDScene::getScene()->gCameraCollection.size() - 1; x >= 0; x--) {
		if (VDScene::getScene()->gCameraCollection[x] != this) {
			VDCamera::setMainCamera(VDScene::getScene()->gCameraCollection[x]);
			break;
		}
	}
}

VDBehavior *VDCamera::copyComponent(unsigned int &dataSize) {
	VDCamera *camera = (VDCamera *)malloc(sizeof(VDCamera));
	memcpy(camera, this, sizeof(VDCamera));
	dataSize = sizeof(VDCamera);
	return (VDBehavior *)camera;
}

void VDCamera::hdr(bool enabled) {
	// if(VDSystemInfo::getCompatibility()->sFramebuffer &&
	// VDSystemInfo::SupportsRenderTextureFormat(VDTexture::eRGBA32F) ){ 	if(enabled) 		this->flag |= eHDR;
	// else this->flag = (flag & ~eHDR); }else{ 	VDDebug::errorLog("HDR is not supported.\n");
	// }
}

bool VDCamera::isHDREnabled() const { return (this->flag & VDCamera::eHDR) != SDL_FALSE; }

void VDCamera::setClearMode(ClearMode clear) {
	this->flag = (this->flag & ~(ClearMode::DontClear | ClearMode::Clear | ClearMode::SkyBox)) |
				 (clear & (ClearMode::DontClear | ClearMode::Clear | ClearMode::SkyBox));
}

VDCamera::ClearMode VDCamera::getClearMode() const {
	return (VDCamera::ClearMode)(this->flag & (ClearMode::DontClear | ClearMode::Clear | ClearMode::SkyBox));
}

void VDCamera::setClearFlag(ClearBuffer clearBuffer) {
	this->flag = (this->flag & ~eClearAll) | (clearBuffer & eClearAll);
}

VDCamera::ClearBuffer VDCamera::getClearFlag(ClearBuffer clearBuffer) const {
	return (VDCamera::ClearBuffer)(this->flag & eClearAll);
}

void VDCamera::setProjectionMode(ProjectionMode projection) {
	this->flag = (this->flag & ~(VDCamera::ProjectionMode::Perspective | VDCamera::ProjectionMode::Orthographic)) |
				 (projection & (VDCamera::ProjectionMode::Perspective | VDCamera::ProjectionMode::Orthographic));
}

VDCamera::ProjectionMode VDCamera::getProjectionMode() const {
	return (VDCamera::ProjectionMode)(this->flag & (VDCamera::Perspective | VDCamera::Orthographic));
}

void VDCamera::setPolygoneMode(PolygoneMode mode) {
	this->flag = (this->flag & ~(PolygoneMode::Point | PolygoneMode::eTriangle | PolygoneMode::eWireFrame)) |
				 (mode & (PolygoneMode::Point | PolygoneMode::eTriangle | PolygoneMode::eWireFrame));
}

VDCamera::PolygoneMode VDCamera::getPolygoneMode(PolygoneMode mode) {
	return (VDCamera::PolygoneMode)(this->flag &
									(PolygoneMode::Point | PolygoneMode::eTriangle | PolygoneMode::eWireFrame));
}

void VDCamera::setCullingMask(const VDLayer &mask) { this->cullingmask = mask; }

VDRenderSetting::RenderPipeline VDCamera::getRenderingPath() const { return VDRenderSetting::getRenderingPath(); }

void VDCamera::setPostEffect(VDPostEffect *postEffect, unsigned int index) {
	if (!postEffect) {
		return;
	}

	/*	Check if image effect is supported.	*/
	this->posteffect(true);

	this->postEffect.push_back(postEffect); /*	TODO change to set at */

	/*	Check if post render texture has been created.	*/
	// if (VDRenderSetting::getSettings()->posttexture == nullptr) {
	// 	VDRenderSetting::getSettings()->posttexture =
	// 		VDRenderTexture::createRenderTexture(VDSize(VDScreen::width(), VDScreen::height()), VDRenderTexture::Color);
	// }
}

void VDCamera::removePostEffect(VDPostEffect *postEffect) {
	if (!postEffect) {
		return;
	}

	for (vector<VDPostEffect *>::iterator x = this->postEffect.begin(); x != this->postEffect.end(); x++) {
		if (postEffect == (*x)) {
			this->postEffect.erase(x);
			/**/
			// postEffect->deincrement();
			break;
		}
	}

	/**/
	if (this->postEffect.size() == 0)
		this->flag = (~VDCamera::ePostEffect & this->flag);
}

void VDCamera::removePostEffect(int index) {
	if (index > this->postEffect.size())
		return;
	else
		removePostEffect(this->postEffect[index]);
}

void VDCamera::removeAllPostEffect() {
	int x;
	for (x = 0; x < postEffect.size(); x++) {
		this->removePostEffect(x);
	}
	this->postEffect.clear();
}

void VDCamera::enableRenderTexture(bool enabled) {
	if (enabled) {
		this->flag |= eRenderTexture;
	} else {
		this->flag = this->flag & ~eRenderTexture;
	}
}



void VDCamera::setRenderTexture(VDRenderTexture *rendertexture) {
	this->enableRenderTexture(rendertexture != nullptr);

	this->renderTexture = rendertexture;
}

VDRenderTexture *VDCamera::getOutpuFrameBuffer() {
	if (this->getRenderTexture() && (this->flag & VDCamera::eRenderTexture)) {
		return this->getRenderTexture();
	} else {
		return VDRenderSetting::getRenderingPathFrameBuffer(this->getRenderingPath());
	}
}

VDRect VDCamera::pixelRect() const {
	return VDRect(this->viewPort.x() * (float)VDScreen::width(), this->viewPort.y() * (float)VDScreen::height(),
				  this->viewPort.width() * (float)VDScreen::width(),
				  this->viewPort.height() * (float)VDScreen::height());
}

void VDCamera::beginSceneRender() {

	/*	Set	current camera being used.	*/
	// VDCamera::setCurrentCamera(this);
	// VDRect viewport = pixelRect();
	// VDRenderTexture* target;

	// /*	update uniform shared infor buffer!	*/
	// VDScene::getScene()->uniform.engineState.ambientColor = VDRenderSetting::getAmbientColor();
	// VDScene::getScene()->uniform.engineState.cameraDir =
	// transform()->transformDirection(VDVector3::UnitZ()).normalize();
	// VDScene::getScene()->uniform.engineState.cameraPosition = transform()->getPosition();
	// VDScene::getScene()->uniform.engineState.cameraNear = this->getNear();
	// VDScene::getScene()->uniform.engineState.cameraFar = this->getFar();
	// VDScene::getScene()->uniform.engineState.projection = this->getProjectionMatrix();
	// VDScene::getScene()->uniform.engineState.viewMatrix = this->transform()->getViewMatrix();
	// VDScene::getScene()->uniform.engineState.viewProjection = this->getProjectionViewMatrix();
	// VDScene::getScene()->uniform.engineState.height = viewport.height();
	// VDScene::getScene()->uniform.engineState.width = viewport.width();
	// VDScene::getScene()->uniform.engineState.xpos = VDInput::x();
	// VDScene::getScene()->uniform.engineState.ypos = VDInput::y();
	// VDScene::getScene()->uniform.engineState.time = VDTime::timef();
	// VDScene::getScene()->uniform.engineState.deltaTime = VDTime::deltaTime();	/*	TODO relocate later */
	// VDScene::getScene()->uniform.engineState.shadow = (int)VDQualitySetting::getShadowFilter();
	// VDScene::getScene()->uniform.engineState.ambientType = VDRenderSetting::getAmbientType();
	// /*	Update engine state.	*/
	// VDScene::getScene()->uniform.enginestate.write( &VDScene::getScene()->uniform.engineState,
	// sizeof(VDScene::getScene()->uniform.engineState));

	// /*	push model matrix for object matrixs	*/
	// VDMatrix::MatrixSpace::matrixMode(VDMatrix::MatrixSpace::Projection);
	// VDMatrix::MatrixSpace::pushMatrix();
	// VDMatrix::MatrixSpace::identity(VDMatrix::MatrixSpace::Projection);

	// /*	Create perspective for the camera.	*/
	// if((this->flag & VDCamera::Perspective)){
	// 	VDMatrix::MatrixSpace::perspective(this->getFov(), this->getAspect(), this->getNear(), this->getFar());
	// }
	// else{
	// 	VDMatrix::MatrixSpace::ortho(
	// 		(float)-VDScreen::width(),
	// 		(float)VDScreen::width(),
	// 		(float)-VDScreen::height(),
	// 		(float)VDScreen::height(),
	// 		-(this->getFar() * 0.5f),
	// 		(this->getFar() * 0.5f));
	// }

	// /*	*/
	// if( this->usePostEffect()){
	// 	if(this->getNumPostEffects() > 0){
	// 		if(this->getRenderTexture() != nullptr){
	// 			this->getRenderTexture()->write();
	// 		}
	// 		else {
	// 			target = this->getOutpuFrameBuffer();
	// 			if(target)
	// 				target->write();
	// 		}
	// 	}
	// }else if(this->isHDREnabled()){
	// 	this->getOutpuFrameBuffer()->write();
	// }

	// if( this->flag & eWireFrame ){
	// 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// }
	// else
	// 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// /*	global view matrix assignment	*/
	// VDMatrix::MatrixSpace::matrixMode(VDMatrix::MatrixSpace::View);
	// VDMatrix::MatrixSpace::pushMatrix();
	// VDMatrix::MatrixSpace::identity(VDMatrix::MatrixSpace::View);
	// VDMatrix::MatrixSpace::rotation(transform()->getRotation());
	// VDMatrix::MatrixSpace::translate(transform()->getPosition());

	// VDRect viewRect = pixelRect();

	// if(this->isMainCamera()){

	// 	float viewportscale = VDQualitySetting::getSampleMode() & VDQualitySetting::eSSAA ? 2.0f : 1.0f;
	// 	target = VDRenderSetting::getRenderingPathFrameBuffer(this->getRenderingPath());
	// 	if(viewportscale > 1.1 && target){
	// 		switch(getRenderingPath()){
	// 		case VDRenderSetting::eForwardRendering:
	// 			VDRenderSetting::getForwardFramebuffer()->write();
	// 			VDRenderSetting::getForwardFramebuffer()->resize(viewRect.width() * viewportscale, viewRect.height() *
	// viewportscale); 			break; 		default: 			assert(0);
	// 		}
	// 	}
	// 	VDRenderingAPICache::setViewport(viewRect.x(), viewRect.y(), viewRect.width() * viewportscale,viewRect.height()
	// * viewportscale);

	// }
	// else{
	// 	if(!this->isMainCamera()){
	// 		this->getRenderTexture()->write();
	// 		viewRect = VDRect(0,0, this->getRenderTexture()->width(), this->getRenderTexture()->height());
	// 		VDRenderingAPICache::setViewport((int)viewRect.x(),
	// 				(int)viewRect.y(),
	// 				(int)viewRect.width(),
	// 				(int)viewRect.height());
	// 		glTextureBarrierNV();
	// 	}
	// }

	// if( this->flag & VDCamera::DontClear ){
	// 	glClear(GL_DEPTH_BUFFER_BIT);
	// }
	// else if( this->flag & VDCamera::Clear ){
	// 	VDRenderingAPICache::setClearColor(getBackColor().x(), getBackColor().y(), getBackColor().z(),
	// getBackColor().w()); 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// }
	// else if(this->flag & VDCamera::SkyBox){
	// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// }

	/* update perspective !! 	*/
	VDMatrix::matrixMode(VDMatrix::MatrixSpace::Model);
}

void VDCamera::endSceneRender() {

	// VDRenderTexture* writetarget;
	// VDRenderTexture* readtarget;

	// /*	render skybox	*/
	// if( flag & SkyBox  ){
	// 	if(VDScene::getScene()->skybox){
	// 		glDepthFunc(GL_LEQUAL);
	// 		VDScene::getScene()->skybox->render(this->transform()->getRotation());
	// 	}
	// }

	// if(this->getRenderTexture() == nullptr){
	// 	writetarget = VDRenderSetting::getRenderingPathFrameBuffer(this->getRenderingPath());
	// }
	// else{
	// 	writetarget = this->getRenderTexture();
	// }

	// /**/
	// VDMatrix::MatrixSpace::matrixMode(VDMatrix::MatrixSpace::Projection);
	// VDMatrix::MatrixSpace::popMatrix();
	// VDMatrix::MatrixSpace::matrixMode(VDMatrix::MatrixSpace::View);
	// VDMatrix::MatrixSpace::popMatrix();
	// VDMatrix::MatrixSpace::matrixMode(VDMatrix::MatrixSpace::Model);

	// if(this->isHDREnabled()){
	// 	/*	tone the texture*/
	// 	VDRenderingAPICache::bindFramebuffer(GL_FRAMEBUFFER, 0);
	// 		/*	*/
	// 		VDRenderSetting::getSettings()->toneMapping->bind();
	// 		VDRenderSetting::getRenderingPathFrameBuffer(this->getRenderingPath())->read();
	// 		VDRenderSetting::getRenderingPathFrameBuffer(this->getRenderingPath())->bindTextures(0);

	// 		VDRenderTexture* output = this->getOutpuFrameBuffer();
	// 		if(output){
	// 			output->write();
	// 		}
	// 		else{
	// 			VDRenderingAPICache::bindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	// 		}

	// 		VDRenderer::drawMesh(VDRenderSetting::getSettings()->quadDisplay);
	// }

	// /*	if DSR is enabled	*/
	// if((VDQualitySetting::getSampleMode() & VDQualitySetting::eSSAA )  && VDQualitySetting::isAntiAliasingEnable() ){
	// 	/*	*/
	// 	if(getRenderTexture())
	// 		getRenderTexture()->read();
	// 	else{
	// 		VDRenderSetting::getForwardFramebuffer()->read();
	// 	}

	// 	//glReadBuffer(GL_BACK);
	// 	VDRenderingAPICache::bindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	// 	//glReadBuffer(GL_FRONT);
	// 	glBlitFramebuffer(0,0,VDScreen::width() * 2, VDScreen::height() * 2,
	// 			0,0,VDScreen::width(), VDScreen::height(),
	// 			GL_COLOR_BUFFER_BIT, GL_NEAREST);
	// 	//VDRenderSetting::getRenderingPathFrameBuffer(this->getRenderingPath())->blitTo(nullptr);
	// }

	// /*	*/
	// VDRenderingAPICache::bindFramebuffer(GL_FRAMEBUFFER, 0);
}

VDVector3 VDCamera::screenSpaceToWorldSpace(const VDVector2 &ScreenPos) const {
	VDVector3 world_pos;
	VDRaycastHit hit;
	// iterate throught all the object in culling view

	// send a ray
	if (VDPhysic::rayCast(transform()->getPosition(), transform()->transformDirection(VDVector3::UnitZ()), hit)) {
	}
	// cube intersection

	// give you the point.

	return world_pos;
}

VDRay VDCamera::screenPointToRay(const VDVector2 &screenCoordinate) {
	VDRay ray;
	ray.setOrigin(this->transform()->getPosition());
	int width = VDScreen::width() * 0.5;
	int height = VDScreen::height() * 0.5;

	float dx = tanf(getFov() * 0.5) * (screenCoordinate.x() / width - 1) / getAspect();
	float dy = tanf(getFov() * 0.5) * (screenCoordinate.y() / height - 1) / getAspect();
	VDVector2 xy = 2.0f * screenCoordinate - VDVector2(1.0f, 1.0f);
	VDVector3 dir = this->transform()->transformDirection(VDVector3::UnitZ());
	dir.normalize();
	ray.setDirection(dir);

	return ray;
}

VDGameObject *VDCamera::screenSpaceToWorldSpaceObject(const VDVector2 &screenPos) {
	VDVector3 world_pos;
	VDRaycastHit hit;
	VDVector3 direction = transform()->transformDirection(VDVector3::UnitZ());
	direction =
		VDVector3(direction.y() + (2.0f * (screenPos.x() / (float)VDScreen::width()) - 1.0f) * (getFov() / 90.0f),
				  direction.y() + (2.0f * (screenPos.y() / (float)VDScreen::height()) - 1.0f) * (getFov() / 90.0f),
				  direction.z());

	if (VDPhysic::rayCast(transform()->getPosition(), transform()->transformDirection(VDVector3::UnitZ()), hit)) {
		return hit.gameObject();
	}

	return nullptr;
}

VDVector2 VDCamera::worldSpaceToScreenSpace(const VDVector3 &WorldPos) {
	VDVector2 viewSize = VDVector2(VDScreen::width(), VDScreen::height());
	// glm::vec4 clipSpace = this->getProjectionMatrix() * (this->transform()->getViewMatrix() * glm::vec4(WorldPos.x(),
	// WorldPos.y(), WorldPos.z(), 1.0f)); VDVector4 ndcSpacePos = *(VDVector4*)&( clipSpace / clipSpace.w ); VDVector2
	// screenSpace = VDVector2( &( (ndcSpacePos + 1.0f) * 0.5f)[0] );
	return VDVector2();
}

VDMatrix4x4 VDCamera::getProjectionViewMatrix() const {
	return this->getProjectionMatrix() * this->transform()->getViewMatrix();
}

void VDCamera::updateCameraMatrix() {
	/*
	if(this->flag & Orthographic){
		this->projectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10 ,10);
	}
	else if(this->flag & Perspective){
		this->projectionMatrix = glm::perspective<float>(this->getFov(), this->getAspect(), this->getNear(),
	this->getFar());
	}*/

	this->setPerspective(this->getFov(), this->getRatio(), this->getNear(), this->getFar());
	this->updateFrustum();
}

void VDCamera::useOcclusionCulling(bool use) {
	if (use) {
		this->flag |= eOcclusionCulling;
	} else {
		this->flag = this->flag & ~eOcclusionCulling;
	}
}

void VDCamera::useFrustumCulling(bool use) {
	if (use)
		this->flag |= eFrustumCulling;
	else
		this->flag = this->flag & ~eFrustumCulling;
}

void VDCamera::updateFrustum() {
	this->calcFrustumPlanes(this->transform()->getPosition(), this->transform()->transformDirection(VDVector3::UnitZ()),
							this->transform()->transformDirection(VDVector3::UnitY()),
							this->transform()->transformDirection(VDVector3::UnitX()));
}

int VDCamera::getCameraIndex() {
	for (unsigned int x = 0; x < VDScene::getScene()->gCameraCollection.size(); x++) {
		if (VDScene::getScene()->gCameraCollection[x] == this)
			return x;
	}
	return -1;
}

bool VDCamera::isMainCamera() const { return this == VDCamera::getMainCamera(); }

float VDCamera::getAspect() const {
	return ((this->getViewPort().width() * (float)VDScreen::width())) /
		   ((this->getViewPort().height() * (float)VDScreen::height()));
}

void VDCamera::setViewPort(const VDRect &viewport) {
	this->viewPort = viewport;
	this->setRatio((float)pixelRect().width() / (float)pixelRect().height());
	// updateCameraMatrix();
}

VDCamera *VDCamera::getCurrentCamera() { return VDScene::getScene()->currentCamera; }

void VDCamera::setCurrentCamera(VDCamera *camera) { VDScene::getScene()->currentCamera = camera; }

VDCamera *VDCamera::getCamera(unsigned int index) { return VDScene::getScene()->gCameraCollection[index]; }

int VDCamera::getCameraCount() { return VDScene::getScene()->gCameraCollection.size(); }

void VDCamera::setMainCamera(VDCamera *camera) { VDScene::getScene()->mainCamera = camera; }

VDCamera *VDCamera::getMainCamera() { return VDScene::getScene()->mainCamera; }
