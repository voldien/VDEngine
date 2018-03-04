#include <Animation/VDAnimation.h>
#include <bits/move.h>
#include <Core/VDBehavior.h>
#include <Core/VDComponent.h>
#include <Core/VDCustomBehavior.h>
#include <Core/VDDebug.h>
#include <Core/VDEngine.h>
#include <Core/VDEngineCore.h>
#include <Core/VDLayer.h>
#include <Core/VDMatrix.h>
#include <Core/VDQualitySetting.h>
#include <Core/VDScreen.h>
#include <Core/VDTaskSchedule.h>
#include <DataStructure/VDBoundVolume.h>
#include <DataStructure/VDDoubleBufferedAllocator.h>
#include <DataStructure/VDQueue.h>
#include <DataStructure/VDRect.h>
#include <DataStructure/VDVector.h>
#include <GL/glew.h>
#include <Rendering/Texture/VDRenderTexture.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/VDCamera.h>
#include <Rendering/VDLight.h>
#include <Rendering/VDMaterial.h>
#include <Rendering/VDMesh.h>
#include <Rendering/VDPostEffect.h>
#include <Rendering/VDRender.h>
#include <Rendering/VDRenderCollection.h>
#include <Rendering/VDRenderingAPICache.h>
#include <Rendering/VDRenderPipeline.h>
#include <Rendering/VDRenderSetting.h>
#include <Rendering/VDShader.h>
#include <Rendering/VDShaderConstant.h>
#include <stddef.h>
#include <Scene/VDGameObject.h>
#include <Scene/VDScene.h>
#include <Scene/VDTransform.h>
#include <SDL2/SDL_stdinc.h>
#include <VDDef.h>
#include <VDSystemInfo.h>
#include <cassert>
#include <map>

VDVector< VDQueue<VDRenderer*> >VDRenderPipeLine::queues;


void VDRenderPipeLine::render(VDDoubleBufferedAllocator* allocator){
	register VDCamera* cam = VDCamera::getMainCamera();

	/*	render all non main cameras.	*/
	for(int x = 0; x < VDCamera::getCameraCount(); x++){
		if( ( VDCamera::getCamera(x)->isMainCamera() == false) &&
				VDCamera::getCamera(x)->isEnabled() &&
				VDCamera::getCamera(x)->isRenderTarget()){
			VDRenderPipeLine::drawCamera(VDCamera::getCamera(x), allocator);
		}
	}

	/*	render main camera last.	*/
	if(cam != NULL){
		VDRenderPipeLine::drawCamera( VDCamera::getMainCamera(), allocator );
	}
}


void VDRenderPipeLine::drawCamera(VDCamera* camera, VDDoubleBufferedAllocator* allocator){
	for(int x = 0; x < queues.size();x++){
		queues[x].clear();
	}

	/**/
	VDCamera::setCurrentCamera(camera);
	VDRenderPipeLine::drawLight(camera, allocator);
	camera->updateCameraMatrix();

	/**/
	VDRenderPipeLine::occlude(camera, allocator);

	/*	bind shadow textures.	*/
	VDRenderPipeLine::bindShadowMaps(camera);
	camera->beginSceneRender();


	/**/
	//VDDebug::debugLog("number of culled object in queue %d\n", queue.getSize());
	//VDEngine::getTaskSchedule().wait();
	switch(camera->getRenderingPath()){
	case VDRenderSetting::RenderPipeline::eForwardRendering:
		internalForwardRendering(camera, camera, allocator);
		break;
	default:
		break;
	}

	/*	End camera.	*/
	camera->endSceneRender();

	/*	post effect	*/
	if(VDSystemInfo::getCompatibility()->sImageEffect){
		VDRenderPipeLine::renderPostEffect(camera, camera->getRenderingPath());
	}



	/*	TODO relocate it to the debug class draw method.*/
	/*	draw tools	*/
	if(VDDebug::isDebugEnabled()){
		if(camera == VDCamera::getMainCamera()){
			int numTools = VDEngine::getDebug()->getTools().size();
			for(int x = 0; x < numTools; x++){
				//VDEngine::getDebug()->getTools()[x]->draw();
			}
		}
	}
}

void VDRenderPipeLine::renderPostEffect(VDCamera* camera, VDRenderSetting::RenderPipeline path){
	if(camera->usePostEffect() == false || camera->getNumPostEffects() == 0){
			return;
	}

	VDRect rect = camera->pixelRect();
	VDPostEffect* effect;
	VDRenderTexture* rendertarget;
	VDRenderTexture* tmp;

	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_COLOR, GL_DST_COLOR);

	/*	Accuire rendertexture.	*/
	if(camera->getRenderTexture() == NULL){
		rendertarget = VDRenderSetting::getRenderingPathFrameBuffer(path);
	}
	else{
		rendertarget = camera->getRenderTexture();
	}
	tmp = VDRenderSetting::getSettings()->posttexture;


	/*	bind rendertarget.	*/
	VDTexture tex1 = rendertarget->getTextureAttachment(0, VDRenderTexture::eColorAttachment0);
	VDTexture tex2 = VDRenderSetting::getSettings()->posttexture->getTextureAttachment(0, VDRenderTexture::eColorAttachment0);
	VDTexture* ptex1 = &tex1;
	VDTexture* ptex2 = &tex2;

	tmp->write();
	VDRenderingAPICache::setClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	rendertarget->read();

	/*	fix for more than 2 post effects.	*/
	VDRenderTexture* ptmp0 = rendertarget;
	VDRenderTexture* ptmp1 = tmp;
	VDRenderingAPICache::setViewport(0, 0, rect.width(), rect.height());
	for(unsigned int x = 0; x < camera->getNumPostEffects(); x++){
		ptmp0->read();
		ptmp1->write();

		/*	*/
		effect = camera->getPostEffect(x);
		if(!effect->isEnabled()){
			continue;
		}

		/*	*/
		ptex1->bind(VDShaderConstant::eDiffuseTexture);
		ptex1->bind(VDShaderConstant::eIllusionTexdture);
		effect->getShader()->bind();

		for(unsigned int z = 0; z < effect->getsNumSample(); z++){
			camera->getPostEffect(x)->render();
		}

		/*	ping pong texture	*/
		std::swap(ptmp0, ptmp1);
		std::swap(ptex1, ptex2);

	}/*	main post effect iterator loop.	*/


	if(camera->isMainCamera()){
		VDRenderTexture::blit(tmp, rendertarget);
		VDRenderTexture::blit(tmp, NULL);
	}
	else{
		VDRenderTexture::blit(tmp, rendertarget);
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

}

void VDRenderPipeLine::drawLight(VDCamera* camera, VDDoubleBufferedAllocator* allocator){
	if(!VDQualitySetting::isShadowEnable()){
		return;
	}
	VDLight::drawLightAccumulationShadow(camera);
}

void VDRenderPipeLine::drawShadowTask(VDTaskSchedule::VDTaskPackage* package){

}

void VDRenderPipeLine::bindShadowMaps(VDCamera* camera){
	register VDLight* light;
	int shadCub = 0;
	int shadTexIndex = 0;
	int x;
	int shadTex;

	/*	bind shadow textures. TODO bind only visible one.	*/
	for(int x = 0; x < VDScene::getScene()->lightcollection.size(); x ++){
		light = VDScene::getScene()->lightcollection[x];

		if(light->isShadowBufferAttached()){

			shadTex = light->getShadowTexture()->getAttachmentNative(0, VDRenderTexture::eDepthAttachment);
			light->getShadowTexture()->unBind();

			if(light->getShadowTexture()->isCubemap()){
				//shadTex.bind(VDShaderConstant::eShadowMappingCube + shadCub);
				shadCub++;
			}
			else if(light->getShadowTexture()->isVolume()){

			}
			else{
				VDRenderingAPICache::bindTexture(VDRenderTexture::eTexture2D, shadTex, VDShaderConstant::eShadowMapping + shadTexIndex);
				//shadTex.bind(VDShaderConstant::eShadowMapping + shadTexIndex);
				shadTexIndex++;
			}

		}
	}
}


void VDRenderPipeLine::occlude(VDFrustum* camera, VDDoubleBufferedAllocator* allocator){

	/**/
	unsigned int numRenderer = VDRenderCollection::numRenderer();
	numRenderer = VDRenderCollection::getRenderColorTypeNumRenderers(VDRenderer::eMesh, VDRenderCollection::eOpaque);
	const int packageSize = 16;
	int n;


	/*	*/
	register RenderCollection::iterator i = VDRenderCollection::getRenderCollection().begin();
	register RenderCollection::iterator j = VDRenderCollection::getRenderCollection().end();

	/*	iterate through all of a given	*/
	for(; i != j; i++){

		/*	don't render particle and lensflare.	*/
		if((*i).first >= VDRenderer::eParticle){
			continue;
		}

		/**/
		for(LightTransmissionObjectType::iterator a = (*i).second.materialType.begin(); a != (*i).second.materialType.end(); a++){
			for(MaterialRendererArrayCollection::iterator x = a->second.collec.begin(); x != a->second.collec.end(); x++){
				register VDMaterial* m = (*x).second.index;
				numRenderer = x->second.renderers.size();
				int lastchunk = numRenderer % packageSize;
				VDTaskSchedule* schedular = &VDEngine::getTaskSchedule();
				VDTaskSchedule::VDTaskPackage task = {0};

				for(n = 0; n < numRenderer; n += packageSize){
					task.begin = &x->second.renderers[n];
					task.end = &x->second.renderers[n] +  ( (numRenderer - n) >=  packageSize ? packageSize : lastchunk ) ;
					task.callback = (VDTaskSchedule::VDTaskCallback)occludeTask;
					task.flag = 0;
					task.offset = n;
					task.size = packageSize;
					occludeTask(&task);
				}

			}
		}
	}

	/*	send package for particle culling.	*/
	if(0){
		static void* particleIndices = allocator->fetch(256);
		VDTaskSchedule::VDTaskPackage partiTask = {0};
		void** partiProt = (void**)allocator->fetch(256);
		partiTask.begin = partiProt;
		partiProt[0] = particleIndices;
		partiProt[1] = &VDRenderCollection::getRenderColorTypeIt(VDRenderer::eParticle, VDRenderCollection::eTranslucent)->second.renderers[0];
		partiTask.end = &VDRenderCollection::getRenderColorTypeIt(VDRenderer::eParticle,
									VDRenderCollection::eTranslucent)->second.renderers[
									VDRenderCollection::getRenderColorTypeIt(VDRenderer::eParticle, VDRenderCollection::eTranslucent)->second.renderers.size()];

		partiTask.size = 256;
		partiTask.callback = (VDTaskSchedule::VDTaskCallback)particleTask;
		partiTask.offset = 0;
		partiTask.flag = 0x4;
		//VDEngine::getTaskSchedule().submitTask(&partiTask);
	}



	/*	TODO let the camera decide.	*/
	if(VDQualitySetting::getCulling() == VDQualitySetting::eEarlyZRejection){
		if(!VDSystemInfo::getCompatibility()->sShaderImageLoadStorage){
			/*	write to the framebuffer.	*/
			VDCamera* cam = VDCamera::getCurrentCamera();
			VDRenderTexture* rendertex = cam->getRenderTexture();
			VDRenderTexture* target = VDRenderSetting::getRenderingPathFrameBuffer(VDRenderSetting::getRenderingPath());
			if(target){
				target->write();
			}

		/*	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
			glDepthMask(SDL_TRUE);
			glEnable(GL_STENCIL_TEST);
			glEnable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			glDepthFunc(GL_LESS);
			VDQueue<VDRenderer*>::Iterator it = queue.begin();

			while(it != queue.end()){
				register VDRenderer* rend = (*it);
				assert(rend);
				VDTransform* trans = rend->transform();
				VDMatrix4x4 mvp = cam->getProjectionViewMatrix() * trans->getMatrix();
				rend->getMaterial()->getShader()->bind();
				rend->getMaterial()->setMatrix4v(VDShaderConstant::ModelViewProjection(), &mvp[0][0], 1);
				rend->draw();
				it++;
			}

			glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
			*/
			//glDepthMask(SDL_TRUE);
			//glEnable(GL_STENCIL_TEST);
			//glEnable(GL_DEPTH_TEST);
			//glDisable(GL_CULL_FACE);
		}
	}

	/*	send data to queue*/
	VDDebug::debugLog("End of Occluder.\n");
}


void VDRenderPipeLine::occludeTask(VDTaskSchedule::VDTaskPackage* package){
	unsigned int ind;
	//ind = ((VDTaskSchedule::VDTaskPool*)package->pool)->coreIndex;
	ind = 0;

	/*	fetch needed information.	*/
	VDCamera* curCamera = VDCamera::getCurrentCamera();
	bool useFrustum = curCamera ? curCamera->isFrustumCulling() : true;
	bool useOcclusion = curCamera ? curCamera->isFrustumCulling() : true;
	VDLayer layer = curCamera ? curCamera->getCullingMask() : VDLayer((unsigned int)-1);
	VDGameObject* gobj;

	/*	iterate through all renderer pointers.	*/
	for(VDRenderer** y = (VDRenderer**)package->begin; y != (VDRenderer**)package->end; y++){
		VDRenderer*rend = *y;
		/*	Check if renderer exists or if layer is valid.	*/
		if(rend == NULL || !(layer & rend->gameObject()->getLayer()) ){
			continue;
		}


		/*	discard if object is not enabled or no mesh.	*/
		if(!rend->isVisiable() || rend->getMesh() == NULL){
			continue;
		}

		gobj = rend->gameObject();
		if(gobj->hasCustomBehavior()){
			for(unsigned int z = 0; z < gobj->getComponentCount();z++){
				if(gobj->getComponentByIndex(z)->isCustomBehavior()){
					VDCASTP(VDCustomBehavior*, gobj->getComponentByIndex(z))->onPreCulled();
				}
			}
		}/**/


		VDBound::BoundType type = (VDBound::BoundType)( rend->getMesh()->getMeshFlag() & VDBound::eBound );
		if(!useFrustum || curCamera->intersectionAABB(rend->getRenderBounds())){	/*	TMP */


			if(rend->getMaterial()->isOpaque()){
				queues[ind].enqueue(rend);
			}
			else{
				queues[ind].push_front(rend);
			}


			if(gobj->getActiveFlag() & VDGameObject::eAnimation){
				gobj->animation()->internalUpdate();
			}

		}/**/
	}/**/

}

void VDRenderPipeLine::particleTask(VDTaskSchedule::VDTaskPackage* package){
	void* indices = VDCAST( void**, package->begin)[0];
	package->cbegin += sizeof(void*);
	//package->begin = VDCAST(void**, package->begin)[0];
	for(; package->begin != package->end; package->cbegin += sizeof(void*)){
		VDRenderer* rend = (VDRenderer*)package->begin;


	}
}

void VDRenderPipeLine::internalForwardRendering(VDFrustum* frustum, VDCamera* camera, VDDoubleBufferedAllocator* allocator, VDQueue<VDRenderer*>* renderers){
	unsigned int cull = 0;
	register VDLight* light;
	VDTransform* trans;
	register VDRenderer* rend;
	bool useFrustum = camera ? camera->isFrustumCulling() : true;
	bool useOcclusion = camera ? camera->isFrustumCulling() : true;
	VDLayer layer = camera ? camera->getCullingMask() : VDLayer((unsigned int)-1);
	VDQueue<VDRenderer*>* squeue;
	unsigned numQueues = queues.size();

	/*	*/
	if(!renderers){
		//squeue = &queue;
	}else{
		squeue = renderers;
	}


	/*	*/
	VDMatrix::matrixMode(VDMatrix::eModel);
	VDMatrix::pushMatrix();


	/*	set depth function if early z rejection. */
	if(VDQualitySetting::getCulling() == VDQualitySetting::Culling::eEarlyZRejection){
		glDepthFunc(GL_LEQUAL);
	}

	for(int x = 0; x < numQueues; x++){
		squeue = &queues[x];
		while(squeue->isEmpty() != true){
			register VDMaterial* m;
			rend = squeue->dequeue();
			assert(rend);
			/*	get material of object.	*/
			m = rend->getMaterial();
			assert(m);
			m->bind();

			/**/
			if(m->isTranslucent()){
				glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
				glDepthMask(GL_FALSE);
				VDRenderingAPICache::setState(GL_BLEND, SDL_TRUE);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}else{
				glDepthMask(GL_TRUE);
				VDRenderingAPICache::setState(GL_BLEND, SDL_FALSE);
			}
			if(m->isFrontCulling()){		/*	sort object by culling state as well [TODO]*/
				glCullFace(GL_FRONT);
			}
			if(m->isBackCulling()){
				glCullFace(GL_BACK);
			}


			trans = rend->transform();

			VDMatrix::identity(VDMatrix::eModel);
			VDMatrix::matrixMode(VDMatrix::eModel);
			VDMatrix::translate(trans->getPosition());
			VDMatrix::rotation(trans->getRotation());
			VDMatrix::scale(trans->getScale());

			VDMatrix::uniformLocation(rend->getMaterial()->getShader());

			rend->draw();
		}
	}

	VDMatrix::matrixMode(VDMatrix::eModel);
	VDMatrix::popMatrix();
}

