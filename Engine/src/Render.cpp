#include <Core/VDBehavior.h>
#include <Core/VDComponent.h>
#include <Core/VDCustomBehavior.h>
#include <Core/VDDebug.h>
#include <Core/VDGUID.h>
#include <Core/VDMatrix.h>
#include <Core/VDObject.h>
#include <DataStructure/VDVector.h>
#include <GL/glew.h>
#include <HCAABB.h>
#include <HCVector3.h>
#include <malloc.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Rendering/VDLight.h>
#include <Rendering/VDMaterial.h>
#include <Rendering/VDMesh.h>
#include <Rendering/VDRender.h>
#include <Rendering/VDRenderCollection.h>
#include <Rendering/VDRenderingAPICache.h>
#include <Rendering/VDShader.h>
#include <Rendering/VDShaderConstant.h>
#include <Scene/VDGameObject.h>
#include <Scene/VDTransform.h>
#include <SDL2/SDL_stdinc.h>
#include <VDDef.h>
#include <VDSimpleType.h>
#include <cmath>
#include <cstring>
#include <map>

using namespace std;

RenderCollection rendercollection;

VDRenderer::VDRenderer(void) : VDBehavior(){
	this->materials = NULL;
	this->flag = (eCastShadow | eReciveShadow | eMesh);
	this->setMaterial(gDefaulMaterial);
	this->setRenderType(VDRenderer::eMesh);
	this->meshFilter = NULL;
	this->setMesh(NULL);
}

VDRenderer::VDRenderer(RendererType type){
	this->materials = NULL;
	this->flag = (eCastShadow | eReciveShadow | eMesh);
	this->setMaterial(gDefaulMaterial);
	this->setRenderType(type);
	this->meshFilter = NULL;
	this->setMesh(NULL);
}

VDRenderer::VDRenderer(VDMaterial* material) : VDBehavior(){
	this->materials = NULL;
	this->flag = (eCastShadow | eReciveShadow);
	this->setRenderType(VDRenderer::eMesh);
	this->setMaterial(material);
	this->meshFilter = NULL;
	this->setMesh(NULL);
}

VDRenderer::VDRenderer(const VDRenderer& renderer){
	*this = renderer;
}

void VDRenderer::instanceInitilize(void){
	//this->setMaterial(this->materials);
}

void VDRenderer::initializeComponent(void){

}

void VDRenderer::onEnable(void){
	// if no broodBehavior, then we don't need to send information
	if(!this->gameObject()->hasCustomBehavior()){
		return;
	}

	for(unsigned int x = 0; x < this->gameObject()->getComponentCount(); x++){
		if(this->gameObject()->getComponentByIndex(x)->isCustomBehavior())
			VDCASTP(VDCustomBehavior*,this->gameObject()->getComponentByIndex(x))->onBecameVisible();
	}
}

void VDRenderer::onDisable(void){
	// if no broodBehavior, then we don't need to send information
	if(!this->gameObject()->hasCustomBehavior()){
		return;
	}

	for(unsigned int x = 0; x < this->gameObject()->getComponentCount(); x++){
		if(this->gameObject()->getComponentByIndex(x)->isCustomBehavior())
			VDCASTP(VDCustomBehavior*,this->gameObject()->getComponentByIndex(x))->onBecameInvisible();
	}
}

void VDRenderer::onDestroy(void){
	VDRenderCollection::removeObjectFromCollection(this, this->getMaterial());
	this->setMesh(NULL);
}

VDBehavior* VDRenderer::copyComponent(unsigned int& dataSize){
	VDRenderer* renderer = (VDRenderer*)malloc(sizeof(VDRenderer));
	memcpy(renderer,this, sizeof(VDRenderer));
	dataSize = sizeof(VDRenderer);
	return (VDBehavior*)renderer;
}


void VDRenderer::setMaterial(VDMaterial* material){
	if(material == NULL || material->getShader() == NULL){
		VDDebug::criticalLog("Invalid material object\n");
		return;
	}

	bool isStatic;
	bool opque = material->isOpaque();
	bool translucent = material->isTranslucent();
	if(this->gameObject())
		isStatic = this->gameObject()->isStatic();


	/*	check if current material is being replaced*/
	if(this->getMaterial() != material && this->getMaterial() != NULL){
		this->getMaterial()->deincrement();

		/*	remove */
		VDRenderCollection::removeObjectFromCollection(this, this->getMaterial());
	}

	/*	assign	*/
	this->materials = material;
	material->increment();

	RendererType type = getRenderType();
	RenderCollectionHeap* collectIT;// = &rendercollection[type];
	collectIT = &VDRenderCollection::getRenderType(type);

	RenderCollectionMaterialHeap* renderTypeColorCollection = &collectIT->materialType[opque == true ? VDShader::eShaderOpaque : VDShader::eShaderTranslucent];

	renderTypeColorCollection->collec[VDGUID(material->getInstanceID() )].index  = material;
	renderTypeColorCollection->collec[VDGUID(material->getInstanceID() )].renderers.push_back(this);
}


VDAABB VDRenderer::getRenderBounds(void)const{
	if(getMesh()){
		return VDAABB(getMesh()->getBound().aabb.getSize() * this->transform()->getScale() , this->transform()->getPosition()  + getMesh()->getBound().aabb.getCenter()  );
	}
	else
		return VDAABB(INFINITY,0.0f);
}

void VDRenderer::setMesh(VDMesh* mesh){
	if(!mesh && getMesh() != NULL){
		getMesh()->deincrement();
	}

	this->meshFilter = mesh;
	if(this->getMesh()){
		this->getMesh()->increment();
	}
}

bool VDRenderer::isPartOfStaticBatch(void)const{
	return getRendererFlag() & VDMesh::eStaticBatch;
}


void VDRenderer::setRenderType(VDRenderer::RendererType rendertype){/*	TODO fix the rendercollection. */
	VDRenderer::RendererType tmp = this->getRenderType();
	this->flag = ( this->flag & ~( eMesh | eParticle | eSkinned | eStaticBatch | eTrail | eLine | eMorph | eLensFlare | eTerrain) )  | ( rendertype & ( eMesh | eParticle | eSkinned | eStaticBatch | eTrail | eLine | eMorph | eLensFlare | eTerrain) );

	if(tmp != rendertype)
		VDRenderCollection::replace(this, tmp, rendertype, this->getMaterial());
}


void VDRenderer::drawInstances(unsigned int elemetInstance, float* wmp){
	if(!getMesh())
		return;

	if(this->meshFilter->getMeshFlag() & VDMesh::eVAO){

		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, getMesh()->getMeshDesc()->WVP);
		glBufferData(GL_ARRAY_BUFFER,elemetInstance * sizeof(VDMatrix4x4), wmp, GL_DYNAMIC_DRAW);

		glBindVertexArray(getMesh()->getVAO());

		glDrawElementsInstancedBaseVertex(getMesh()->getDrawMode(),
				getMesh()->getNumIndices(),
				getMesh()->getIndicesNFlag(),
			(const void*)0,
			elemetInstance,
			0);

		glBindVertexArray(0);
	}
}

void VDRenderer::enableVertexPointer(void){
	return;
	if(this->meshFilter->getMeshFlag() & VDMesh::eVertex)
		glVertexAttribPointer(VDShaderConstant::VERTEX_LOCATION, 3, GL_FLOAT, GL_FALSE,this->meshFilter->getVertexStride(), (const void*)0); //			Vertex
	
	if(this->meshFilter->getMeshFlag() & VDMesh::eTextureCoord)
		glVertexAttribPointer(VDShaderConstant::eTEXTURECOORD_LOCATION, 2, GL_FLOAT, GL_FALSE,this->meshFilter->getVertexStride(), (const void*)12);//	TexCoord	(3 VertexPosition * (4 as float))
	
	if(this->meshFilter->getMeshFlag() & VDMesh::eNormal)
		glVertexAttribPointer(VDShaderConstant::eNORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE,this->meshFilter->getVertexStride(), (const void*)20);//	Normal
	
	if(this->meshFilter->getMeshFlag() & VDMesh::eTangent)
		glVertexAttribPointer(VDShaderConstant::eTANGENT_LOCATION, 3, GL_FLOAT, GL_FALSE, this->meshFilter->getVertexStride(), (const void*)32);
	
	if(this->meshFilter->getMeshFlag() & VDMesh::eBoneID)
		glVertexAttribPointer(VDShaderConstant::eBONE_ID_LOCATION, 4, GL_INT, GL_FALSE, this->meshFilter->getVertexStride(), (const void*)44);

	if(this->meshFilter->getMeshFlag() & VDMesh::eBoneWeight)
		glVertexAttribPointer(VDShaderConstant::eBONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, this->meshFilter->getVertexStride(), (const void*)60);
	
	if(this->meshFilter->getMeshFlag() & VDMesh::eVertexColor)
		glVertexAttribPointer(VDShaderConstant::eVERTEXCOLOR_LOCATION, 4, GL_FLOAT, GL_FALSE, this->meshFilter->getVertexStride(), (const void*)12);
}

void VDRenderer::draw(void){
	this->internalDraw();
}

void VDRenderer::internalDraw(VDMesh::Primitive drawmode, unsigned int instances){
	if(!this->getMesh()){
		return;
	}

	if(getMesh()->getMeshFlag() & VDMesh::eStaticBatch){

	}


	if((this->getMesh()->getMeshFlag() & VDMesh::eVAO)){

		glBindVertexArray(this->getMesh()->getVAO());

		/**/
		switch(getMesh()->getPolygoneCount()){
		case 0:
			if(this->getMaterial()->isTessellation()){
				glPatchParameteri(GL_PATCH_VERTICES, 3);
				this->drawArrayPatch();
			}

			glDrawArraysInstanced(drawmode, 0, this->getMesh()->getVertexCount(), instances);
			break;
		default:
			if(this->getMaterial()->isTessellation()){
				glPatchParameteri(GL_PATCH_VERTICES, 3);
				this->drawElementPatch();
			}

			/*BaseVertex*/
			glDrawElementsInstanced(drawmode,
				this->getMesh()->getPolygoneCount(),
				getMesh()->getIndicesNFlag(), NULL, instances);
			break;
		}

		glBindVertexArray(0);
	}
}


void VDRenderer::internalMultiDraw(unsigned int primcount, const unsigned int* count, const unsigned int* indices, VDMesh::Primitive drawMode){
	if(!getMesh()){
		return;
	}

	glBindVertexArray(getMesh()->getVAO());
	switch(getMesh()->getPolygoneCount()){
	case 0:
		if(this->getMaterial()->isTessellation()){
			glPatchParameteri(GL_PATCH_VERTICES, 3);
			this->drawMultiArrayPatch(primcount, count, indices);
		}

		glMultiDrawArrays(drawMode, (const GLsizei*)count, (const GLsizei*)indices, primcount);
		break;
	default:
		if(this->getMaterial()->isTessellation()){
			glPatchParameteri(GL_PATCH_VERTICES, 3);
			this->drawMultiElementsPatch(primcount, count, indices);
		}

		glMultiDrawElements(drawMode, (const GLsizei*)count, getMesh()->getIndicesNFlag(), (const GLvoid**)indices, primcount);
		break;
	}
	glBindVertexArray(0);
}

void VDRenderer::externalDraw(VDShader* shader){
	VDMatrix::matrixMode(VDMatrix::Model);
	VDMatrix::pushMatrix();	
	VDMatrix::identity(VDMatrix::Model);

	VDMatrix::translate(transform()->getPosition());
	VDMatrix::rotation(transform()->getRotation());
	VDMatrix::scale(transform()->getScale());
	VDMatrix::uniformLocation(shader);

	this->internalDraw();

	VDMatrix::popMatrix();
}

void VDRenderer::internalShadowDraw(VDShader* Shadowpass, VDLight* light, VDMesh::Primitive drawmode){


	VDMatrix::matrixMode(VDMatrix::Model);
	VDMatrix::pushMatrix();

	register VDTransform* trans;
	register VDRenderer* render;
	VDMatrix4x4 viewproject;
	for(RenderCollection::iterator y = VDRenderCollection::getRenderCollection().begin(); y != VDRenderCollection::getRenderCollection().end(); y++){
		if(y->first == VDRenderer::eLensFlare){
			continue;
		}

		for(LightTransmissionObjectType::iterator h = (*y).second.materialType.begin(); h != (*y).second.materialType.end(); h++ ){

			for(MaterialRendererArrayCollection::iterator z = (*h).second.collec.begin(); z != (*h).second.collec.end(); z++){

				for(int x = (*z).second.renderers.size() - 1; x >= 0; x--){
					render = (*z).second.renderers[x];
					if(render->getMesh() == NULL){
						continue;
					}

					if((render->getRendererFlag() & eCastShadow) && render->isVisiable()){
						if(!light->intersectBoundingVolume(render->getVolumeBounds(), render->getMesh()->getBoundType(), render->transform()->getPosition() )){
							continue;
						}

						/**/
						if(render->getMaterial()->isTranslucent()){
							/*	bind diffuse textures*/
							render->getMaterial()->getTexture(VDShaderConstant::DiffuseTexture)->bind(0);
						}


						VDMatrix::identity(VDMatrix::Model);
						VDMatrix::translate(render->transform()->getPosition());
						VDMatrix::rotation(render->transform()->getRotation());
						VDMatrix::scale(render->transform()->getScale());

						switch(light->getType()){
						case VDLight::Point:
							glProgramUniformMatrix4fv(Shadowpass->getProgram(), Shadowpass->matrixInfo.modelMatrix,
													1,
													GL_FALSE,
													&VDMatrix::getModel()[0][0]);
							break;
						case VDLight::eDirection:
						case VDLight::eSpot:
							glProgramUniformMatrix4fv(Shadowpass->getProgram(), Shadowpass->matrixInfo.modelViewProjectionMatrix,
								1,
								GL_FALSE,
								&((light->getShadowMatrix(0) * VDMatrix::getModel())[0][0] ));
							break;
						}

						/**/
						render->internalDraw(drawmode);
					}/**/
			}


			}/*	*/
		}
	}/*collection*/


	VDMatrix::matrixMode(VDMatrix::Model);
	VDMatrix::popMatrix();		
}

void VDRenderer::castShadow(int castShadodw){
	this->flag = (castShadodw == SDL_TRUE) ? (getRendererFlag() | eCastShadow) : ((~eCastShadow) | this->getRendererFlag());
}

void VDRenderer::reciveShadow(int reciveShadow){
	this->flag = (reciveShadow == SDL_TRUE) ? (getRendererFlag() | eReciveShadow) : ((~eReciveShadow) | this->getRendererFlag());
}

bool VDRenderer::isSkinned(void)const{
	return (this->getRenderType() & VDMesh::eSkinned) != 0 ? SDL_TRUE : SDL_FALSE;
}
bool VDRenderer::isParticle(void)const{ return (this->getRenderType()  & VDRenderer::eParticle); }
bool VDRenderer::isMorph(void)const{ return (this->getRenderType()  & VDRenderer::eMorph);}
bool VDRenderer::isLensFlare(void)const{ return (this->getRenderType()  & VDRenderer::eLensFlare);}
bool VDRenderer::isTerrain(void)const{	return (this->getRenderType() & VDRenderer::eTerrain);}

bool VDRenderer::isVisiable(void)const{
	return this->isEnabled();
}




void VDRenderer::drawElementPatch(void){
	glDrawElements(GL_PATCHES, this->meshFilter->getNumIndices(), this->meshFilter->getIndicesNFlag(), NULL);
}

void VDRenderer::drawMultiElementsPatch(unsigned int primcount, const unsigned int* count, const unsigned int* indices){
	glMultiDrawElements(GL_PATCHES, (const GLsizei*)count, getMesh()->getIndicesNFlag(), (const GLvoid**)indices, primcount);
}

void VDRenderer::drawArrayPatch(void){
	glDrawArrays(GL_PATCHES, 0, this->getMesh()->getVertexCount());
}

void VDRenderer::drawMultiArrayPatch(unsigned int primcount, const unsigned int* count, const unsigned int* indices){
	glMultiDrawArrays(GL_PATCHES, (const GLsizei*)count, (const GLsizei*)indices, primcount);
}




void VDRenderer::drawMesh(VDMesh* mesh){

	if((mesh->getMeshFlag() & VDMesh::eVAO)){ // If no Indices Exist in mesh!
		glBindVertexArray(mesh->getVAO());

		switch(mesh->getPolygoneCount()){
		case 0:
			glDrawArrays(mesh->getDrawMode(),0, mesh->getVertexCount());
			break;
		default:
			glDrawElementsBaseVertex(mesh->getDrawMode(),
					mesh->getNumIndices(),
					mesh->getIndicesNFlag(), 0, 0);
			break;
		}

		glBindVertexArray(0);
	}
}


void VDRenderer::drawInstanceMesh(VDMesh* mesh, unsigned int count){
	if(count == 0){
		return;
	}

	if(mesh->getMeshFlag() & VDMesh::eVAO){

		glBindVertexArray(mesh->getVAO());

		switch(mesh->getPolygoneCount()){
		case 0:
			glDrawArraysInstanced(mesh->getDrawMode(), 0, mesh->getVertexCount(), count);
			break;
		default:
			glDrawElementsInstanced(mesh->getDrawMode(),
					mesh->getNumIndices(),
					mesh->getIndicesNFlag(),
				(const void*)0,
				count );
			break;
		}

		glBindVertexArray(0);
	}
}
