#include <Core/VDObject.h>
#include <DataStructure/VDBoundVolume.h>
#include <DataStructure/VDPoolAllactor.h>
#include <GL/glew.h>
#include <HCAABB.h>
#include <HCVector3.h>
#include <Rendering/VDMesh.h>
#include <Rendering/VDRenderingAPICache.h>
#include <Rendering/VDShaderConstant.h>
#include <stdlib.h>
#include <Scene/VDScene.h>
#include <SDL2/SDL_stdinc.h>
#include <Utility/VDGeometryUtility.h>
#include <VDSimpleType.h>
#include <cstring>
#include <map>
#include <utility>

using namespace std;


VDMesh::VDMesh(void) : VDAssetObject(){
	this->setDrawMode(GL_TRIANGLES);
	this->vertexCount = 0;
	this->indicesCount = 0;
	this->nSizeFlag = GL_UNSIGNED_SHORT;
	this->flag = 0;
	this->bounds.aabb = VDAABB();
	this->strideSize = this->getVertexStride();

	memset(&this->meshdesc,0, sizeof(VDMeshDesc));
}

VDMesh::VDMesh(const VDMesh& mesh) : VDAssetObject() {
	*this = mesh;
}

VDMesh::VDMesh(const void* VertexBuffer, unsigned int vertexStrideSize,
		unsigned int VertexDataSize, const  unsigned char* indicesData,
		unsigned int indicesTypeSize,unsigned int IndicesDataSize,
		unsigned int bitFlag) : VDAssetObject(){
	this->setDrawMode(GL_TRIANGLES);
	this->vertexCount = 0;
	this->indicesCount = 0;
	this->nSizeFlag = GL_UNSIGNED_SHORT;
	this->flag = (VDMesh::eVertex | VDMesh::eNormal | VDMesh::eTextureCoord | VDMesh::eTangent);
	this->bounds.aabb = VDAABB();
	this->strideSize = vertexStrideSize;

	memset(&this->meshdesc,0, sizeof(VDMeshDesc));
	this->assemblyMesh((unsigned char*)VertexBuffer, vertexStrideSize, VertexDataSize, (unsigned char*)indicesData, indicesTypeSize, IndicesDataSize, flag);
}

VDMesh::~VDMesh(void){
	if(VDScene::getScene()->meshs.isValidItem(*this)){
		VDScene::getScene()->meshs.Return(this);
	}
}

void VDMesh::release(void){

	if(glIsBuffer(this->meshdesc.VBO)){
		glDeleteBuffers(1, &this->meshdesc.VBO);
	}
	if(glIsBuffer(this->meshdesc.IBO)){
		glDeleteBuffers(1, &this->meshdesc.IBO);
	}
	if(glIsVertexArray(this->meshdesc.VAO)){
		glDeleteVertexArrays(1,&this->meshdesc.VAO);
	}

	if(glIsBuffer(this->meshdesc.POS_VB)){
		glDeleteBuffers(1, &this->meshdesc.POS_VB);
	}
	if(glIsBuffer(this->meshdesc.TEXCOORD_VB)){
		glDeleteBuffers(1, &this->meshdesc.TEXCOORD_VB);
	}
	if(glIsBuffer(this->meshdesc.NORMAL_VB)){
		glDeleteBuffers(1, &this->meshdesc.NORMAL_VB);
	}
	if(glIsBuffer(this->meshdesc.TANGENT_VB)){
		glDeleteBuffers(1, &this->meshdesc.TANGENT_VB);
	}
	if(glIsBuffer(this->meshdesc.BONE_VB)){
		glDeleteBuffers(1, &this->meshdesc.BONE_VB);
	}

	for(map<const char*, VDMesh*>::iterator x = VDScene::getScene()->gMeshCollection.begin(); x != VDScene::getScene()->gMeshCollection.end(); x++){
		if(x->second == this){
			VDScene::getScene()->gMeshCollection.erase(x);
			break;
		}
	}
}

VDMesh& VDMesh::operator=(const VDMesh& mesh){
	VDAssetObject::operator=(*this);
	memcpy(&this->meshdesc, &mesh.meshdesc, sizeof(mesh.meshdesc));
	this->vertexCount = mesh.getVertexCount();
	this->indicesCount = mesh.getNumIndices();
	this->drawMode = mesh.getDrawMode();
	this->nSizeFlag = mesh.nSizeFlag;
	//this->bounds_ = mesh.bounds_;
	this->bounds = mesh.bounds;
	this->flag = mesh.flag;

	return *this;
}

unsigned int VDMesh::getVertexStride(void)const{
	unsigned int stride = 0;
	if(this->getMeshFlag() & eVertex ){
		stride += sizeof(VDVertex);
	}
	if(this->getMeshFlag() & eTextureCoord){
		stride += sizeof(VertexUV);
	}
	if(this->getMeshFlag() & eNormal){
		stride += sizeof(VertexNormal);
	}
	if(this->getMeshFlag() & eTangent){
		stride += sizeof(VertexTangent);
	}
	if(this->getMeshFlag() & eBiNormal){
		stride += sizeof(VertexBiNormal);
	}
	if(this->getMeshFlag() & eBitTangent){
		stride += sizeof(VertexBitTangent);
	}
	return stride;
}

unsigned int VDMesh::getIndicesStride(void)const{
	return VDGeometryUtility::getIndicesSize(this->getNumIndices());
}

void VDMesh::setABB(const VDAABB& bounds){
	this->bounds.aabb = bounds;
	this->flag = ( this->flag & ~eAllBound) | eAABB;
}

void VDMesh::setOBB(const VDOBB& bounds){
	this->bounds.obb = bounds;
	this->flag = ( this->flag & ~eAllBound) | eOBB;
}

/*	TODO for all get and set data, query the type for efficenty by bit flag instead of making a opengl call.*/
VDVector3 VDMesh::getVertex(unsigned int index)const{
	VDVector3 pVertex; 
	if(glIsVertexArray(this->meshdesc.VAO)){
		if(glIsBuffer(this->meshdesc.VBO)){
			VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
			glGetBufferSubData(GL_ARRAY_BUFFER, index * this->strideSize, sizeof(VDVertex),(void*)&pVertex);
			return pVertex;
		}
		else if(glIsBuffer(this->meshdesc.POS_VB)){
			VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.POS_VB);
			glGetBufferSubData(GL_ARRAY_BUFFER, index * sizeof(VDVertex), sizeof(VDVertex),(void*)&pVertex);
			return pVertex;
		}
	}
	else if(glIsBuffer(this->meshdesc.VBO)){
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
		glGetBufferSubData(GL_ARRAY_BUFFER, index * this->strideSize,sizeof(VDVertex),(void*)&pVertex);
		return pVertex;
	}

	return pVertex;
}

void VDMesh::setVertex(unsigned int index, const VDVector3& vertex){
	if(glIsVertexArray(this->meshdesc.VAO)){
		if(glIsBuffer(this->meshdesc.POS_VB)){
			VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.POS_VB);
			glBufferSubData(GL_ARRAY_BUFFER, index * sizeof(VDVector3), sizeof(VDVertex), &vertex);
		}
		else if(glIsBuffer(this->meshdesc.VBO)){
			VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
			glBufferSubData(GL_ARRAY_BUFFER, index * this->getVertexStride(), sizeof(VDVertex), &vertex);
		}
	}
	else if(glIsBuffer(this->meshdesc.VBO)){
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
		glBufferSubData(GL_ARRAY_BUFFER, index * this->getVertexStride(), sizeof(VDVertex), &vertex);

	}
}

VDVertex* VDMesh::getVertexBundle(void){

	if(glIsBuffer(this->meshdesc.POS_VB)){
		VDVertex* pVertices = (VDVertex*)malloc(sizeof(VDVertex) * this->getVertexCount());
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.POS_VB);
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VDVertex) * this->getVertexCount(), pVertices);
		return pVertices;
	}
	else if(glIsBuffer(this->meshdesc.VBO)){
		VDVertex* pVertices = (VDVertex*)malloc(sizeof(VDVertex) * this->getVertexCount());
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
		for(unsigned int x = 0;x < this->getVertexCount(); x++){
			glGetBufferSubData(GL_ARRAY_BUFFER, (x * this->strideSize), sizeof(VDVertex),&pVertices[x]);

		}
		return pVertices;
	}

	return NULL;
}

VDVector2 VDMesh::getUV(unsigned int index)const{
	VDVector2 UV;
	if((this->flag & VDMesh::eVAO ) && this->meshdesc.TEXCOORD_VB != 0){
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.TEXCOORD_VB);
		glGetBufferSubData(GL_ARRAY_BUFFER, index * sizeof(VDVertex2D),sizeof(VDVertex2D),(void*)&UV);
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, 0);
	}
	else if(getVBO() != 0){
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
		glGetBufferSubData(GL_ARRAY_BUFFER, ( index * this->strideSize ) + sizeof(VDVertex), sizeof(VDVector2), (void*)&UV);
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, 0);
	}
	return UV;
}

VDVector2* VDMesh::getUVBundle(void){
	if(glIsVertexArray(this->meshdesc.VAO)){
		VDVector2* pUV = (VDVector2*)malloc(sizeof(VertexUV) * this->vertexCount);
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.TEXCOORD_VB);
		glGetBufferSubData(GL_ARRAY_BUFFER,0, sizeof(VertexUV) * this->vertexCount, pUV);
		return pUV;
	}
	else if(glIsBuffer(this->meshdesc.VBO)){
		VDVector2* p_Uv = (VDVector2*)malloc(sizeof(VDVector2) * this->vertexCount);
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
		for(unsigned int x = 0;x < this->getVertexCount(); x++){
			glGetBufferSubData(GL_ARRAY_BUFFER, (x * this->strideSize) + sizeof(VDVector3), sizeof(VDVector2), &p_Uv[x]);
		}

		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, 0);
		return p_Uv;
	}
	return NULL;
}

VDVector3 VDMesh::getNormal(unsigned int index)const{
	VDVector3 normal; 
	if(getVBO()){
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
		glGetBufferSubData(GL_ARRAY_BUFFER, index * this->strideSize + sizeof(VDVector3) + sizeof(VDVector2),sizeof(VDVector3),(void*)&normal);
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, 0);
	}
	return normal;
}

VDVertex* VDMesh::getNormalBundle(void){
	if(glIsVertexArray(this->meshdesc.VAO)){
		VDVertex* pnormal = (VDVertex*)malloc(sizeof(VertexNormal) * this->getVertexCount());
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.NORMAL_VB);
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexNormal) * this->vertexCount,pnormal);
		return pnormal;
	}
	else if(glIsBuffer(this->meshdesc.VBO)){
		VDVertex* p_Ver = (VDVertex*)malloc(sizeof(VDVector3) * this->getVertexCount());
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
		for(unsigned int x = 0;x < this->getVertexCount(); x++){
			glGetBufferSubData(GL_ARRAY_BUFFER, (x * this->strideSize) + sizeof(VDVertex) + sizeof(VDVector2), sizeof(VDVertex), &p_Ver[x]);

		}
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, 0);
		return p_Ver;
	}
	return NULL;
}

VDVector3 VDMesh::getTangent(unsigned int index)const{
	VDVector3 tangent; 
	VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
	glGetBufferSubData(GL_ARRAY_BUFFER, index * this->strideSize + sizeof(VDVertex) * 2 + sizeof(VDVector3),sizeof(VDVector3),(void*)&tangent);
	VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, 0);
	return tangent;
}

VDVertex* VDMesh::getTangentBundle(void){
	if(glIsVertexArray(this->meshdesc.VAO)){
		VDVertex* ptangent = (VDVertex*)malloc(sizeof(VertexTangent) * this->vertexCount);
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.NORMAL_VB);
		glGetBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexTangent) * this->vertexCount,ptangent);
		return ptangent;
	}
	else if(glIsBuffer(this->meshdesc.VBO)){
		VDVertex* p_tan = (VDVertex*)malloc(sizeof(VDVertex) * this->vertexCount);
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, this->meshdesc.VBO);
		for(unsigned int x = 0;x < this->vertexCount; x++){
			glGetBufferSubData(GL_ARRAY_BUFFER, x * this->strideSize + sizeof(VDVertex) + sizeof(VDVector2) + sizeof(VDVertex), sizeof(VDVertex),&p_tan[x]);

		}
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, 0);
		return p_tan;
	}
	else
		return NULL;
}

VDVector3 VDMesh::getBiNormal(unsigned int index)const{		/* Get biNormal[Index] */
	return cross(this->getNormal(index), this->getTangent(index));
}

VDVector3* VDMesh::getBiNormalBundle(void){		/* Get biNormal Bundle Data. */
	for(unsigned int x = 0;x < this->vertexCount; x++){


	}
	return NULL;
}

VDVector3 VDMesh::getBitTangent(unsigned int index)const{	/* Get biTangent[Index] */
	return cross(this->getTangent(index),this->getNormal(index));
}

VDVector3* VDMesh::getBitTangentBundle(void){	/* Get biTangent Bundle Data. */
	return NULL;
}

VDHANDLE VDMesh::getVBOBuffer(void){
	void* buffer = (void*)malloc(this->getVertexCount() * this->getVertexStride());
	VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER,this->meshdesc.VBO);
	glGetBufferSubData(GL_ARRAY_BUFFER, 0, this->vertexCount * this->getVertexStride(),buffer);
	return (VDHANDLE)buffer;
}

unsigned int VDMesh::getIndices(unsigned int index){
	unsigned int indicesData;
	VDRenderingAPICache::bindBuffer(GL_ELEMENT_ARRAY_BUFFER,this->meshdesc.IBO);
	glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, index * this->getIndicesStride(), this->getIndicesStride(),&indicesData);
	VDRenderingAPICache::bindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	return indicesData;
}

unsigned char* VDMesh::getIndicesBundle(void){
	unsigned char* pIndices = (unsigned char*)malloc(this->indicesCount * this->getIndicesStride());
	if(pIndices){
		VDRenderingAPICache::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->meshdesc.IBO);
		glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER,0, this->indicesCount * this->getIndicesStride(), pIndices);
		VDRenderingAPICache::bindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	}
	return pIndices;
}


void VDMesh::computeBBox(void){
	VDVertex* vertex = getVertexBundle();
	if(!vertex)
		return;


	if(flag & eAABB){
		//ExComputeBBox((unsigned char*)vertex, this->getVertexStride(), vertexCount * this->getVertexStride(), (float*)&this->bounds.aabb.mhalfsize, (float*)&this->bounds.aabb.mcenter);
		VDGeometryUtility::computeAABB((const VDVertex*)vertex, this->getVertexStride(), this->getVertexCount(), (VDAABB*)&this->bounds.aabb);
	}
	if(flag & eOBB){
		VDGeometryUtility::computeOBB((const VDVector3*)vertex, this->getVertexCount(), (VDOBB*)&this->bounds.obb, true);
	}

	free(vertex);
}


void VDMesh::assemblyMesh(void* vertexbuffer, GLuint vertexStrideSize, unsigned int VertexDataSize, void* indices, GLuint indicesSize,GLuint IndicesDataSize, unsigned int bitFlag){
	GLuint VBO = 0;
	GLuint IBO = 0;

	if(!vertexbuffer || !indices)
		return;


	glGenVertexArrays(1, &this->meshdesc.VAO);
	glBindVertexArray(this->getVAO());


	if(VertexDataSize != 0 && vertexStrideSize != 0){
		glGenBuffers(1, &VBO);
		VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, VertexDataSize, vertexbuffer,
			(indices != NULL) ? GL_STATIC_READ : GL_STATIC_DRAW);

	}
	if(indices != NULL){
		glGenBuffers(1, &IBO);
		VDRenderingAPICache::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndicesDataSize, indices, GL_STATIC_DRAW);
		this->indicesCount = (IndicesDataSize / indicesSize);

	}

	this->flag |= eVAO;

	if( bitFlag & VDMesh::eVertex){
		glEnableVertexAttribArray(VDShaderConstant::VERTEX_LOCATION);
		glVertexAttribPointer(VDShaderConstant::VERTEX_LOCATION, 3, GL_FLOAT, GL_FALSE, vertexStrideSize, 0); //			Vertex
	}
	if( bitFlag & VDMesh::eTextureCoord){
		glEnableVertexAttribArray(VDShaderConstant::eTEXTURECOORD_LOCATION);
		glVertexAttribPointer(VDShaderConstant::eTEXTURECOORD_LOCATION, 2, GL_FLOAT, GL_FALSE, vertexStrideSize, (const void*)12);//	TexCoord	(3 VertexPosition * (4 as float))
	}
	if( bitFlag & VDMesh::eNormal){
		glEnableVertexAttribArray(VDShaderConstant::eNORMAL_LOCATION);
		glVertexAttribPointer(VDShaderConstant::eNORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE,vertexStrideSize, (const void*)20);//	Normal
	}
	if( bitFlag & VDMesh::eTangent){
		glEnableVertexAttribArray(VDShaderConstant::eTANGENT_LOCATION);
		glVertexAttribPointer(VDShaderConstant::eTANGENT_LOCATION, 3, GL_FLOAT, GL_FALSE, vertexStrideSize, (const void*)32);	//tangent
	}
	if( bitFlag & VDMesh::eBoneID ){
		glEnableVertexAttribArray(VDShaderConstant::eBONE_ID_LOCATION);
		glVertexAttribIPointer(VDShaderConstant::eBONE_ID_LOCATION , 4, GL_UNSIGNED_INT, vertexStrideSize, (const void*)44);
	}
	if( bitFlag & VDMesh::eBoneWeight ){
		glEnableVertexAttribArray(VDShaderConstant::eBONE_WEIGHT_LOCATION);
		glVertexAttribPointer(VDShaderConstant::eBONE_WEIGHT_LOCATION , 4, GL_FLOAT, GL_FALSE, vertexStrideSize, (const void*)60);
	}

	glBindVertexArray(0);

	this->flag |= bitFlag;
	this->vertexCount = VertexDataSize / vertexStrideSize;
	this->meshdesc.VBO = VBO;
	this->meshdesc.IBO = IBO;
	this->strideSize = vertexStrideSize;


	switch(indicesSize){
	case 1:
		this->nSizeFlag = GL_UNSIGNED_BYTE;
		break;
	case 2:
		this->nSizeFlag = GL_UNSIGNED_SHORT;
		break;
	case 4:
		this->nSizeFlag = GL_UNSIGNED_INT;
		break;
	default:
		break;
	}

	//TODO FIX
	// compute the vertex info
	VDGeometryUtility::computeAABB((VDVertex*)vertexbuffer, vertexStrideSize, this->getVertexCount(), &this->bounds.aabb);
	this->setABB(this->bounds.aabb);

	VDMesh::assignMesh(this);
}

int VDMesh::setMeshFlag(VDMesh::meshFlag meshFlag){
	switch(meshFlag){
	case VDMesh::eInstanceRendering:	// initilize 
	case VDMesh::eVAO:
		{
			if((this->flag & meshFlag) != 0)
				return 2;
			else{
				//this->genVAO();
				//glBindVertexArray(this->meshdesc.VAO);
				if(!glIsBuffer(this->meshdesc.WVP)){
					glGenBuffers(1,&this->meshdesc.WVP);
					VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER,this->meshdesc.WVP);
					/*for(unsigned int x = 0; x <4; x++){
						glVertexAttribPointer(WVP_LOCATION + x, 4, GL_FLOAT, GL_FALSE, sizeof(VDMatrix4x4), (const void*)(sizeof(float) * x * 4));
						glEnableVertexAttribArray(WVP_LOCATION + x);
						glVertexAttribDivisor(WVP_LOCATION + x, 1);
					}*/
					//this->InitInstanceBuffer(meshFlag);
				}
				//glBindVertexArray(0);
			}
		}
		break;
	case VDMesh::eStaticMesh:
	case VDMesh::eVBO:
		{
			if((this->flag & meshFlag) != 0)
				return 2;
			else{

			}
		}
		break;
	default:
		return 0;
	}
	return SDL_TRUE;
}

VDMesh* VDMesh::createMesh(void){
	VDMesh* mesh = VDScene::getScene()->meshs.obtain();
	*mesh = VDMesh();
	return mesh;
}

void VDMesh::assignMesh(VDMesh* mesh){
	VDScene::getScene()->gMeshCollection.insert(std::pair<const char*,VDMesh*>(mesh->getName(), mesh));
}

VDMesh* VDMesh::findMesh(const char* pathName){
	for(std::map<const char*, VDMesh*>::iterator x = VDScene::getScene()->gMeshCollection.begin(); x != VDScene::getScene()->gMeshCollection.end(); x++){
		if(!x->second->getName()){
			continue;
		}
		unsigned int compareX = strcmp(pathName,x->second->getName());
		if(!compareX){	// 0 == match.
			return x->second;
		}
	}
	return NULL;
}

unsigned int VDMesh::getVertexOffset(VDMesh::MeshComponent meshComponent){
	unsigned int offsetStride  = 0;

	if(meshComponent & eVertex){
		offsetStride += 0;
	}
	if(meshComponent & eTextureCoord){
		offsetStride += sizeof(VDVector3);
	}
	if(meshComponent & eNormal){
		offsetStride += (meshComponent & eTextureCoord) != 0 ? sizeof(VDVector2) : sizeof(VDVector3);
	}
	if(meshComponent & eTangent){
		offsetStride += sizeof(VDVector3);
	}
	if(meshComponent & eBiNormal){
		offsetStride += sizeof(VDVector3);
	}
	if(meshComponent & eBitTangent ){
		offsetStride += sizeof(VDVector3);
	}

	return offsetStride;
}

unsigned int VDMesh::getVertexStrideSize(VDMesh::MeshComponent meshComponent){
	unsigned int stride = 0;
	if(meshComponent & eVertex)
		stride += sizeof(VDVertex);
	if(meshComponent & eTextureCoord)
		stride += sizeof(VertexUV);
	if(meshComponent & eNormal)
		stride += sizeof(VertexNormal);
	if(meshComponent & eTangent)
		stride += sizeof(VertexTangent);
	if(meshComponent & eBiNormal)
		stride += sizeof(VertexBiNormal);
	if(meshComponent & eBitTangent)
		stride += sizeof(VertexBitTangent);
	return stride;
}



VDHANDLE VDMesh::open(unsigned int target, unsigned int object, AccessMode access){
	VDRenderingAPICache::bindBuffer(target, object);
	return (VDHANDLE)glMapBuffer(target, access);

}

bool VDMesh::close(unsigned int target, unsigned int object){
	VDRenderingAPICache::bindBuffer(target, object);
	return glUnmapBuffer(target);
}
