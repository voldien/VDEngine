#include <Core/VDApplication.h>
#include <Core/VDDebug.h>
#include <Core/VDEngine.h>
#include <Core/VDObject.h>
#include <GL/glew.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Rendering/VDColor32.h>
#include <Rendering/VDMaterial.h>
#include <Rendering/VDRenderingAPICache.h>
#include <Rendering/VDShader.h>
#include <Rendering/VDShaderConstant.h>
#include <Rendering/VDShaderCreator.h>
#include <Scene/VDScene.h>
#include <Utility/VDTextureProcedure.h>
#include <Utility/VDTextureUtility.h>
#include <VDSimpleType.h>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

/**/
VDMaterial* gDefaulMaterial = nullptr;
VDTexture2D* resourceErrorTexture = nullptr;


VDMaterial::VDMaterial() : VDAssetObject(){

	this->shader = nullptr;
	memset(this->textures, nullptr, sizeof(this->textures));
	this->setTexture(VDShaderConstant::eDiffuseTexture, resourceErrorTexture);

	/*	Assign default texture.	*/
	if(this->getDefaultMaterial()){
		this->setTexture(VDShaderConstant::eDiffuseTexture, getDefaultMaterial()->getTexture(VDShaderConstant::eDiffuseTexture));
	}
}

VDMaterial::VDMaterial(VDShader* shader) : VDAssetObject() {
	this->shader = nullptr;
	this->setShader(shader);
	memset(this->textures,nullptr,sizeof(this->textures));
	// assigned  the default texture, to be able render anything 
	if(this->getDefaultMaterial()){
		this->setTexture(VDShaderConstant::eDiffuseTexture, this->getDefaultMaterial()->getTexture(VDShaderConstant::eDiffuseTexture));
	}
}

VDMaterial::VDMaterial(const VDMaterial& material){
	*this = material;
}


VDMaterial::~VDMaterial(){
	if(VDScene::getScene()->materials.isValidItem(*this))
		VDScene::getScene()->materials.Return(this);
}

VDMaterial& VDMaterial::operator=(const VDMaterial& materail){
	VDObject::operator=(materail);
	this->shader = materail.getShader();
	memcpy(this->textures,materail.textures,sizeof(materail.textures));
	return *this;
}

void VDMaterial::release(){
	int x;
	if(this->getShader()){
		this->getShader()->deincrement();
	}
	/*	deincrement all texture associated.	*/
	for(x = 0; x < sizeof(textures) / sizeof(textures[0]); x++){
		if(this->getTexture(x) != nullptr){
			this->getTexture(x)->deincrement();
		}
	}
}

void VDMaterial::setShader(VDShader* shader){
	if(shader == this->getShader()){
		return;
	}

	/*	Validate if shader is working.	*/
	if(!shader->isValid()){
		VDDebug::errorLog("Invalid shader : %s, attempting to assign to material :%s .\n", shader->getName(), this->getName());

		/*	assigned default shader.	*/
		this->setShader(VDShaderCreator::SingleColorShader());
		return;
	}

	/*	if another shader object is already attached.	*/
	if(this->getShader() && !shader){
		this->getShader()->deincrement();
	}

	/*	*/
	this->shader = shader;
	if(this->getShader()){
		this->getShader()->increment();
	}
}

VDShader* VDMaterial::getShader()const{
	return this->shader;
}

void VDMaterial::bindProperties(){

	int index = 0;

	/*	TODO relocate it later, create pointer variable to be asigned on initialize of the engine.*/
	if(!VDSystemInfo::getCompatibility()->sMultiBind){
		int tex[16];
		for(int x = 0; x < sizeof(this->textures) / sizeof(this->textures[0]); x++){
			tex[x] = ( this->getTexture(x) != nullptr ) ? this->getTexture(x)->getTexture() : nullptr;
		}

		VDRenderingAPICache::bindTextures(0, sizeof(this->textures) / sizeof(this->textures[0]), tex);
	}
	else{
		for(int x = 0; x < sizeof(this->textures) / sizeof(this->textures[0]); x++){
			if(this->getTexture(x))
				this->getTexture(x)->bind(x);
		}
	}
}

void VDMaterial::bind(){
	if(!getShader()){
		return;
	}

	this->getShader()->bind();
	this->bindProperties();
	if(getShader()->isFlagSet(VDShader::eSubRoutines) ){
		getShader()->setSubRoutine((VDShader::ShaderType)GL_FRAGMENT_SHADER, getShader()->getNumSubRoutines(), getShader()->getActiveRoutinesIndices());
	}
}

void VDMaterial::setTexture(int index, VDTexture* texture){
	if(texture == nullptr || index >= (sizeof(this->textures) / sizeof(this->textures[0])) -1){
		return;
	}

	if(this->textures[index] != nullptr && texture == nullptr){
		this->textures[index]->deincrement();
		this->textures[index] = texture;
	}
	else{
		this->textures[index] = texture;
		this->textures[index]->increment();
	}
}

VDTexture2D* VDMaterial::getTexture(const char* samplename){
	int index = this->getInt(samplename);
	return textures[index]->isTexture2D();
}

VDTexture2D* VDMaterial::getTexture(int index){
	return textures[index]->isTexture2D();
}

void VDMaterial::setTextureOffset(const char* sample, const VDVector2& offset){
	if(!this->getShader()){
		return;
	}
	glProgramUniform2fv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(sample), 1, (float*)&offset);
}

void VDMaterial::setTextureTile(const char* sample, const VDVector2& tile){
	if(!this->getShader())
		return;
	glProgramUniform2fv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(sample), 1, (float*)&tile);
}

VDVector2 VDMaterial::getTextureOffset(const char* sample){
	if(!this->getShader())
		return VDVector2(-1.0f, -1.0f);

	VDVector2 textureprop;
	glGetUniformfv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(sample), (float*)&textureprop);
	return VDVector2();
}

VDVector2 VDMaterial::getTextureTile(const char* textureSampler){
	if(!this->getShader())
		return VDVector2(-1.0f, -1.0f);

	VDVector2 textureprop;
	glGetUniformfv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(textureSampler), (float*)&textureprop);
	return VDVector2();
}

void VDMaterial::setVec2(const char* uniformName,const VDVector2& vec2){
	if(!this->getShader()){
		return;
	}
	glProgramUniform2fv(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName), 1, (float*)&vec2);
}

void VDMaterial::setVec2(const char* uniformName, float x, float y){
	if(!this->getShader())
		return;
	glProgramUniform2f(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName),x,y);
}


void VDMaterial::setVec2v(const char* uniformName,unsigned int count, const VDVector2* vector){
	if(!this->getShader())
		return;
	glProgramUniform2fv(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName), count, (float*)vector);
}

VDVector2 VDMaterial::getVec2(const char* uniformName){
	if(!this->getShader())
		return VDVector2(-1.0f, -1.0f);
	float _v[2];
	glGetUniformfv(this->getShader()->getProgram(),
		this->getShader()->getUniformLocation(uniformName),
		_v);
	return VDVector2(_v[0], _v[1]);
}
VDVector2* VDMaterial::getVec2v(const char* uniformName, unsigned int IndexOffset, unsigned int Count){
	if(!this->getShader())
		return nullptr;

	VDVector2* pvalue = (VDVector2*)malloc(this->getShader()->getUniformSize(uniformName) * sizeof(VDVector2));
	for(unsigned int x = 0; x < Count; x++){

		glGetUniformfv(this->getShader()->getProgram(), this->getShader()->getUniformLocationArray(uniformName,x + IndexOffset, ""),&pvalue[x][0]);
		continue;
	}
	return pvalue;
}

void VDMaterial::setVec3(const char* uniformName,const VDVector3& vec3){
	if(!this->getShader())
		return;
	glProgramUniform3fv(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName),1, (float*)&vec3);
}

void VDMaterial::setVec3(const char* uniformName, float x, float y, float z){
	if(!this->getShader())
		return;
	glProgramUniform3f(shader->getProgram(),this->getShader()->getUniformLocation(uniformName), x,y,z);
}

void VDMaterial::SetVec3v(const char* uniformName,unsigned int count, const VDVector3* vector){
	if(!this->getShader())
		return;
	glProgramUniform3fv(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName), count, (float*)vector);
}

VDVector3 VDMaterial::getVec3(const char* uniformName){
	if(!this->getShader())
		return VDVector3(-1.0f);
	VDVector3 v;
	glGetUniformfv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(uniformName),(float*)&v);
	return v;
}
VDVector3* VDMaterial::getVec3v(const char* uniformName, unsigned int IndexOffset, unsigned int Count){
	if(!this->getShader())return nullptr;
	VDVector3* pvalue = (VDVector3*)malloc(sizeof(VDVector3) * this->getShader()->getUniformSize(uniformName));
	return pvalue;
}
void VDMaterial::setVec4(const char* uniformName,const VDVector4& vec4){
	if(!this->getShader())
		return;
	glProgramUniform4fv(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName),1, (float*)&vec4);
}

void VDMaterial::setVec4(const char* uniformName, float x, float y, float z,float w){
	if(!this->getShader())
		return;
	glProgramUniform4f(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName),x,y,z,w);
}

void VDMaterial::SetVec4v(const char* uniformName,unsigned int count, const VDVector4* vector){
	if(!this->getShader())
		return;
	glProgramUniform4fv(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName), count, (float*)vector);
}

VDVector4 VDMaterial::getVec4(const char* uniformName){
	if(!this->getShader())return VDVector4(-1.0f);
	VDVector4 v;
	glGetUniformfv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(uniformName),(float*)&v);
	return v;
}
VDVector4* VDMaterial::getVec4v(const char* uniformName, unsigned int IndexOffset, unsigned int Count){
	if(!this->getShader()) return nullptr;
	VDVector4* pvalue = (VDVector4*)malloc(sizeof(VDVector4) * this->getShader()->getUniformSize(uniformName));
	return pvalue;
}

void VDMaterial::setColor(const char* uniformName,float r, float g, float b, float a){
	if(!this->getShader()){
		return;
	}
	glProgramUniform4f(this->getShader()->getProgram(), glGetUniformLocation(this->getShader()->getProgram(), VDShaderConstant::DiffuseColor()),r,g,b,a);
}

void VDMaterial::setColor(const char* uniformName,const VDColor& color){
	if(!this->getShader())
		return;
	glProgramUniform4fv(this->getShader()->getProgram(), glGetUniformLocation(this->getShader()->getProgram(), uniformName),1,(float*)&color);
}

VDColor VDMaterial::getColor(const char* uniformName){
	if(!this->getShader())
		return VDColor(-1.0f, -1.0f, -1.0f, -1.0f);
	VDColor color;
	glGetUniformfv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(uniformName),(float*)&color);
	return color;
}

void VDMaterial::setfloat(const char* uniformName, float value){
	if(!this->getShader())
		return;
	glProgramUniform1fv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(uniformName), 1, &value);
}

void VDMaterial::setfloatv(const char* uniformName, unsigned int count, float* pValue){
	if(!this->getShader())
		return;
	glProgramUniform1fv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(uniformName), count, pValue);
}

float VDMaterial::getfloat(const char* uniformName){
	if(!this->getShader())
		return 0.0f;
	float unfloat;
	glGetUniformfv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(uniformName),&unfloat);
	return unfloat;
}

float* VDMaterial::getfloatv(const char* uniformName, unsigned int indexOffset, unsigned int count){
	if(!this->getShader())
		return nullptr;

	float* pvalue = (float*)malloc(sizeof(float) * shader->getUniformSize(uniformName));
	for(unsigned int x = 0; x < count; x++){
		glGetUniformfv(this->getShader()->getProgram(), this->getShader()->getUniformLocationArray(uniformName, x,""), &pvalue[x]);

	}
	return pvalue;
}

void VDMaterial::setInt(const char* uniformName, int value){
	if(!this->getShader())
		return;
	glProgramUniform1i(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName), value);
}

void VDMaterial::setIntv(const char* uniformName, unsigned int count, const int* pValue){
	if(!this->getShader())
		return;
	glProgramUniform1iv(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName),count, pValue);
}

int VDMaterial::getInt(const char* uniformName){
	if(!this->getShader())
		return -1;
	int unInt;
	glGetUniformiv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(uniformName), &unInt);
	return unInt;
}

int* VDMaterial::getInt(const char* uniformName, unsigned int indexOffset, unsigned int count){
	if(!this->getShader()){
		return nullptr;
	}

	int* p_int = (int*)malloc(this->getShader()->getUniformSize(uniformName) * sizeof(int));
	for(unsigned int x = 0; x < count; x++){
		glGetUniformiv(this->getShader()->getProgram(), this->getShader()->getUniformLocationArray(uniformName,x + indexOffset,""),&p_int[indexOffset + x]);
		continue;
	}
	return p_int;
}

void VDMaterial::setMatrix4(const char* uniformName,const VDMatrix4x4& matrix){
	if(!this->getShader())
		return;

	glProgramUniformMatrix4fv(this->getShader()->getProgram(), this->getShader()->getUniformLocation(uniformName), 1, GL_FALSE, &matrix[0][0]);
}

void VDMaterial::setMatrix4v(const char* uniformName,float* matrix, unsigned int count){
	if(!this->getShader())
		return;

	glProgramUniformMatrix4fv(this->getShader()->getProgram(),this->getShader()->getUniformLocation(uniformName), count, GL_FALSE, matrix);
}

VDMatrix4x4 VDMaterial::getMatrix4(const char* name){
	if(!this->getShader())
		return VDMatrix4x4();

	VDMatrix4x4 mat;
	glGetUniformfv(this->getShader()->getProgram(),
		this->getShader()->getUniformLocation(name), &mat[0][0]);
	return  mat;
}

vector<VDMatrix4x4> VDMaterial::getMatrix4v(const char* uniformName, unsigned int count){
	if(!this->getShader())
		return vector<VDMatrix4x4>();

	vector<VDMatrix4x4> mat; mat.reserve(count);
	for(unsigned int x = 0; x < count; x++){
		glGetUniformfv(this->getShader()->getProgram(), this->getShader()->getUniformLocationArray(uniformName,x,""), &mat[0][0][0]);
	}

	return mat;
}



void VDMaterial::setOpaque(){
	if(this->getShader()){
		this->getShader()->setFlagSet( ( this->getShader()->getFlagSet() & ~VDShader::eShaderTranslucent)  | VDShader::eShaderOpaque);
	}
}
void VDMaterial::setTranslucent(){
	if(this->getShader()){
		this->getShader()->setFlagSet( ( this->getShader()->getFlagSet() & ~VDShader::eShaderOpaque)  | VDShader::eShaderTranslucent);
	}
}



VDMaterial* VDMaterial::createMaterial(){
	VDMaterial* material = VDScene::getScene()->materials.obtain();
	*material = VDMaterial();
	material->mmame = nullptr;	/*TODO remove later when C++ compiler bug has been resolved.*/
	return material;
}

VDMaterial* VDMaterial::createMaterial(VDShader* shader){
	VDMaterial* material = VDMaterial::createMaterial();
	material->setShader(shader);
	return material;
}


VDMaterial* VDMaterial::createDefaultMaterial(unsigned int preset){
	VDMaterial* material = nullptr;
	VDShader* shader;

	switch(preset){
	// case VDEngine::DefualtMaterialLowQuality:{
	// 		material = VDMaterial::createMaterial();
	// 		shader = VDShaderCreator::Diffuse();

	// 		/*	Determine if shader is valid.	*/
	// 		if(!shader->isValid()){
	// 			VDDebug::log("Default low quality shader is invalid. Loading legacy shader.\n");
	// 			shader = VDShaderCreator::Unlit();

	// 			if(shader == nullptr || !shader->isValid()){
	// 				VDDebug::criticalLog("Engine panic.\n");
	// 				VDApplication::quit(EXIT_FAILURE);
	// 			}

	// 			material->setShader(shader);
	// 		}
	// 		material->setShader(shader);

	// 		/*	*/
	// 		VDTexture2D* defaulTexture =  VDTextureProcedure::whiteTexture();
	// 		material->setTexture(VDShaderConstant::eDiffuseTexture, defaulTexture);

	// 		material->setName("DefaultMaterial");
	// 		break;
	// 	}
	// case VDEngine::DefualtMaterialHighQuality:{
	// 		material = VDMaterial::createMaterial();
	// 		shader = VDShaderCreator::SpecularNormal();

	// 		/*	Determine if shader is valid.	*/
	// 		if(!shader->isValid()){
	// 			VDDebug::log("Default high quality shader is invalid. Loading legacy shader.\n");
	// 			shader = VDShaderCreator::Unlit();

	// 			if(shader == nullptr || !shader->isValid()){
	// 				VDDebug::criticalLog("Engine panic.\n");
	// 				VDApplication::quit(EXIT_FAILURE);
	// 			}

	// 			material->setShader(shader);
	// 		}
	// 		material->setShader(shader);


	// 		VDTexture2D* defaulTexture = VDTextureProcedure::genCheckerTexture2(1024, 1024, 128, 128, VDColor32::White(), VDColor32::Red(), VDTexture::eRGB, VDTexture::eRGB, VDTexture::eUnsignedByte, VDTexture::eMipMapping);
	// 		VDTexture2D* defaultNormal = VDTextureUtility::genNormal(defaulTexture);
	// 		// if(defaulTexture != nullptr){
	// 		// 	defaulTexture->compress();
	// 		// }
	// 		// if(defaultNormal){
	// 		// 	defaultNormal->compress();
	// 		// }

	// 		// material->setTexture(VDShaderConstant::eDiffuseTexture, defaulTexture);
	// 		// material->setTexture(VDShaderConstant::eNormalTexture, defaultNormal);

	// 		material->setName("DefaultMaterial");
	// 		break;
	// 	}
	default:
		break;
	}

	/*	set object in a non auto release by the asset manager.	*/
	// material->setFlag(material->getFlag() | VDObject::Static);
	// material->getShader()->setFlag(material->getShader()->getFlag() | VDObject::Static);
	// material->getTexture(0)->setFlag(material->getTexture(0)->getFlag() | VDObject::Static);


	return material;
}

VDMaterial* VDMaterial::getDefaultMaterial(){
	return gDefaulMaterial;
}

VDTexture2D* VDMaterial::getDefaultTexture(){
	return (VDMaterial::getDefaultMaterial() != nullptr) ? gDefaulMaterial->getTexture(0) : nullptr;
}
