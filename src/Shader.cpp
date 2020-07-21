#include <Asset/VDAssetManager.h>
#include <Core/VDDebug.h>
#include <Core/VDGUID.h>
#include <Core/VDObject.h>
#include <DataStructure/VDPoolAllactor.h>
#include <GL/glew.h>
#include <Rendering/VDBufferObject.h>
#include <Rendering/VDLight.h>
#include <Rendering/VDRenderSetting.h>
#include <Rendering/VDShader.h>
#include <Rendering/VDShaderConstant.h>
#include <Rendering/VDShaderCreator.h>
#include <Rendering/VDUniformBuffer.h>
#include <Scene/VDScene.h>
#include <SDL2/SDL_stdinc.h>
#include <VDDef.h>
#include <VDSimpleType.h>
#include <VDSystemInfo.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <utility>

using namespace std;

struct cmp_str
{
   bool operator()(char const *a, char const *b)
   {
      return std::strcmp(a, b) < 0;
   }
};
map<unsigned int, VDShader*> shaderCollection;



VDShader::VDShader(void) : VDAssetObject(){
	memset(&this->common, 0, sizeof(this->common));
	memset(&this->matrixInfo, 0, sizeof(this->matrixInfo));
	memset(&this->subroutines, 0, sizeof(this->subroutines));

	this->flag = VDShader::eShaderOpaque | VDShader::eFrontCulling;
}

VDShader::VDShader(const VDShader& shader) : VDAssetObject(){
	*this = shader;
}

VDShader::VDShader(const char* cVertexFileName, const char* fragmentPath, const char* geometryPath, const char* name, const char* tessC, const char* tessE, unsigned int  flag) : VDAssetObject(){
	char* v_source,*f_source,*g_source,*tc_source,*te_source;
	v_source = f_source = g_source = tc_source = te_source = NULL;

	this->flag  = 0;
	memset(&this->common, 0, sizeof(this->common));
	memset(&this->matrixInfo, 0, sizeof(this->matrixInfo));
	memset(&this->subroutines, 0, sizeof(this->subroutines));

	/*	*/
	this->flag = VDShader::eShaderOpaque | VDShader::eFrontCulling;
	this->setName(name);


	/*	Load shader	source.	*/
	if(VDShaderCreator::loadShaderString(cVertexFileName, (void**)&v_source) < 0){

	}
	if(VDShaderCreator::loadShaderString(fragmentPath, (void**)&f_source) < 0){
		VDDebug::errorLog("");
	}
	if(VDShaderCreator::loadShaderString(geometryPath, (void**)&g_source) < 0){
		VDDebug::errorLog("");
	}
	if(VDShaderCreator::loadShaderString(tessC, (void**)&tc_source) < 0 ){
		VDDebug::errorLog("");
	}
	if(VDShaderCreator::loadShaderString(tessE, (void**)&te_source) < 0 ){
		VDDebug::errorLog("");
	}


	/*	compile shader.	*/
	this->compileShader(v_source, f_source, g_source, tc_source, te_source);

	/*	get the flag info	*/
	this->flagReference(v_source, f_source, g_source, tc_source, te_source);

	/*	initialize uniform memory	*/
	this->initFlagData();

	/*	 */
	VDShader::getUniformMatrixLocation(this);


	/*	*/
	if(VDScene::getScene()->lightinfo.lightbuffer.getTarget() == VDBufferObject::eShaderStorage)
		this->setStorageBlockBind(this->getUniformBlockIndex(VDShaderConstant::lightUniform()), VDShaderConstant::eLightning);
	else
		this->setUniformBlockBind(this->getUniformBlockIndex(VDShaderConstant::lightUniform()), VDShaderConstant::eLightning);

	/*	*/
	if(VDScene::getScene()->lightinfo.lightIndices.getTarget() == VDBufferObject::eShaderStorage)
		this->setStorageBlockBind(this->getUniformBlockIndex(VDShaderConstant::lightIndices()), VDShaderConstant::eLightIndices);
	else
		this->setUniformBlockBind(getUniformBlockIndex(VDShaderConstant::lightIndices()), VDShaderConstant::eLightIndices);

	/*	*/
	if(VDScene::getScene()->lightinfo.shadowbuffer.getTarget() == VDBufferObject::eShaderStorage){
		this->setStorageBlockBind(this->getUniformBlockIndex(VDShaderConstant::shadowstruct()), VDShaderConstant::eShadow);
	}
	else{
		this->setUniformBlockBind(getUniformBlockIndex(VDShaderConstant::shadowstruct()), VDShaderConstant::eShadow);
	}

	/*	*/
	this->setUniformBlockBind(this->getUniformBlockIndex(VDShaderConstant::engineState()), VDShaderConstant::eEngineState);

	/*	*/
	if(VDRenderSetting::getSettings()->particlebuffer.getTarget() == VDBufferObject::eShaderStorage){
		this->setStorageBlockBind(this->getUniformBlockIndex(VDShaderConstant::particleSystem()), VDShaderConstant::eParticle);
	}
	else{
		this->setUniformBlockBind(this->getUniformBlockIndex(VDShaderConstant::particleSystem()), VDShaderConstant::eParticle);
	}


	/*	Assigned shader to asset management.	*/
	this->setShader(this);
	VDAssetManager::assignAsset(this,
			cVertexFileName,
			fragmentPath,
			geometryPath,
			tessC,
			tessE, NULL);


	/*	free memory	*/
	free(v_source);
	free(f_source);
	free(g_source);
	free(tc_source);
	free(te_source);
}

VDShader::~VDShader(void){

}

unsigned int VDShader::getProgram(void)const{
	return this->program;
}

void VDShader::release(void){

	if(shaderCollection[getInstanceID()] != NULL){
		ShaderCollection::iterator it = shaderCollection.find(getInstanceID());
		shaderCollection.erase(it);
	}

	this->release(0xFFFFFF);
}


void VDShader::release(unsigned int pflag){

	if(pflag == (eVertex | eFragment | eGeometry | eProgram)){
		//shaderCollection.erase(shaderCollection.find(this->getName()));
	}

	/*	delete program	*/
	if(glIsProgram(getProgram()) && (pflag & VDShader::eProgram ) ){
		glDeleteProgram(getProgram());
		this->program  = 0;
	}
}



bool VDShader::isValid(void)const{
	int validate;
	glValidateProgram(this->getProgram());
	glGetProgramiv(this->getProgram(), GL_VALIDATE_STATUS, &validate);
	return true;
	return validate == GL_TRUE;
}

int VDShader::getUniformLocation(const char* cuniformName)const{
	return glGetUniformLocation(this->getProgram(), cuniformName);
}

int VDShader::getAttributeLocation(const char* name)const{
	return glGetAttribLocation(this->getProgram(), name);
}

void VDShader::setAttributeLocation(const char* name, unsigned int index){
	glBindAttribLocation(this->getProgram(), index, name);
	glLinkProgram(this->getProgram());
	/*	TODO add linking after*/
}

int VDShader::getFragDataLocation(const char* name)const{
	return glGetFragDataLocation(this->getProgram(), name);
}

void VDShader::setFragDataLocation(const char* fragDataName, unsigned int colorNumber){
	glBindFragDataLocation(this->getProgram(), colorNumber, fragDataName);
	glLinkProgram(this->getProgram());
	/*	TODO add linking after*/
}

void VDShader::setVaryings(int count, const char** varyings, unsigned int  mode){
	glTransformFeedbackVaryings(this->getProgram(), count, varyings, mode);
	glLinkProgram(this->getProgram());
}

unsigned int VDShader::getUniformBlockIndex(const char* uniformBlockName)const{
	return glGetUniformBlockIndex(this->getProgram(), uniformBlockName);
}

int VDShader::getUniformSize(const char* uniformName)const{
	int size; GLenum type;
	glGetActiveUniform(this->getProgram(), this->getUniformLocation(uniformName), NULL, NULL, &size, &type, NULL);
	return size;
}

int VDShader::getUniformBlockSize(const char* uniformBlockName)const{
	int size;
	glGetActiveUniformBlockiv(this->getProgram(), getUniformBlockIndex(uniformBlockName), GL_UNIFORM_BLOCK_DATA_SIZE, &size);
	return size;
}

void VDShader::setUniformBlockBind(int uniformBlockIndex, unsigned int uniformBlockBinding){
	if(uniformBlockIndex >= 0){
		glUniformBlockBinding(this->getProgram(), uniformBlockIndex, uniformBlockBinding);
	}
}


unsigned int VDShader::getStorageBlockIndex(const char* cStorageBlockName){
	return glGetProgramResourceIndex(this->getProgram(), GL_SHADER_STORAGE_BLOCK, cStorageBlockName);
}

int VDShader::getStorageBlockSize(const char* cStorageBlockName){
	int size;
	//glGetProgramResourceiv(this->getProgram(), 0, this->getStorageBlockIndex(cStorageBlockName), 1,  )
	return size;
}

void VDShader::setStorageBlockBind(unsigned int ssboBlockIndex, unsigned int SSBOBlockBinding){
	glShaderStorageBlockBinding(this->getProgram(), ssboBlockIndex, SSBOBlockBinding);
}



unsigned int VDShader::getSubRoutineIndex(ShaderType shadertype, const char* cfunctionName){
	return glGetSubroutineIndex(this->getProgram(), (unsigned int)shadertype, cfunctionName);
}
/*	TODO remake the error which the subroutine didn't work, was simply because the indices stages are lost when invoking useProgram, according to Wiki*/
void VDShader::setSubRoutine(ShaderType shaderype, unsigned int num, const unsigned int* indices){
	glUniformSubroutinesuiv(shaderype, num, indices);
}

void VDShader::setSubRoutineTmp(ShaderType shaderType, const char* funcname, const char* routineName){
	GLint active;
	GLint location;

	location = glGetSubroutineUniformLocation(this->getProgram(), shaderType, funcname);
	if(location == -1){
		this->setFlagSet(this->getFlagSet() & ~eSubRoutines);
		VDDebug::errorLog("Couldn't find subroutine location : %s.\n", funcname);
		return;
	}

	glGetProgramStageiv(this->getProgram(), shaderType, GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, &active);
	this->subroutines.numActive = active;
	if(active <= 0){
		this->setFlagSet(this->getFlagSet() & ~eSubRoutines);
		VDDebug::errorLog("Couldn't find any active subroutines : %s.\n", funcname);
		return;
	}

	this->flag |= eSubRoutines;
	this->subroutines.indices[location] = getSubRoutineIndex(shaderType, routineName);
}

unsigned int VDShader::getNumSubRoutines(void)const{
	return this->subroutines.numActive;
}

const unsigned int* VDShader::getActiveRoutinesIndices(void)const{
	return this->subroutines.indices;
}


int VDShader::getUniformLocationArray(const char* fronText, unsigned int index, const char* EndText){
	string location;
	location += fronText;
	location += "[";
	location += "%d";
	location += "]";
	location += EndText;
	char _te[128];
	//sprintf(_te,fronText "[%d]"EndText,Index);
	//sprintf(_te, (unsigned int)sizeof(_te), location.c_str(), index );
	int locationIndex = glGetUniformLocation(this->getProgram(), _te);
	return locationIndex;
}





void VDShader::flagReference(const char* cVertexFileName, const char* fragmentPath, const char* geometryPath,const char* tessC, const char* tessE){
	unsigned long int support = 0;
	const char* source = 0;
	char location_name[128];
	unsigned int x;

	for(x = 0; x < 5; x++){

		if(x == 0)
			source = cVertexFileName;
		else if(x == 1)
			source = fragmentPath;
		else if(x == 2)
			source = geometryPath;
		else if(x == 3)
			source = tessC;
		else if(x == 4)
			source = tessE;

		/**/
		if(source == NULL){
			continue;
		}
		if( strlen(source) == 0){
			continue;
		}

		/*	TODO resolve*/
		if(strstr(source, VDShaderConstant::DisplacementHeight())){
			this->common.heights = this->getUniformLocation(VDShaderConstant::DisplacementHeight());
		}
		if(strstr(source, "Shininess")){
			this->common.shininess = this->getUniformLocation("Shininess");
		}
		if(strstr(source, "refraction")){
			this->common.refraction = this->getUniformLocation("refraction");
		}

		if(strstr(source, VDShaderConstant::ModelViewProjection())){
			support |= VDShader::eShaderModelViewProjection;
		}
		if(strstr(source, VDShaderConstant::ModelViewMatrix())){
			support |= VDShader::eShaderModelViewMatrix;
		}
		if(strstr(source,VDShaderConstant::ModelMatrix())){
			support |= VDShader::eShaderModelMatrix;
		}
		if(strstr(source,VDShaderConstant::DeformMatrix())){
			support |= VDShader::eShaderDeformMatrix;
		}
		if(strstr(source, VDShaderConstant::ViewProjection())){
			support |= VDShader::eShaderViewProjectionMatrix;
		}

		if(strstr(source,VDShaderConstant::DiffuseTexture())){
			support |= VDShader::eShaderDiffuseTexture;
		}
		if(strstr(source,VDShaderConstant::NormalTexture())){
			support |= VDShader::eShaderNormalTexture;
		}
		if(strstr(source,VDShaderConstant::IllusionTexture())){
			support |= VDShader::eShaderIllusion;
		}
		if(strstr(source,VDShaderConstant::DisplacementTexture())){
			support |= VDShader::eShaderDisplacementTexture;
		}
		if(strstr(source,VDShaderConstant::ReflectionTexture())){
			support |= VDShader::eShaderCubeMapTexture;
		}
		if(strstr(source,VDShaderConstant::DiffuseColor())){
			support |= VDShader::eShaderDiffuseColor;
		}
		if(strstr(source,VDShaderConstant::SpecularColor())){
			support |= VDShader::eShaderSpecularColor;
		}
		if(strstr(source,VDShaderConstant::SpecularTexture())){
			support |= VDShader::eShaderSpecularTexture;
		}
		if(strstr(source,VDShaderConstant::ReflectionColor())){
			support |= VDShader::eShaderCubeMapColor;
		}

	}/**/

	this->flag |= support;
}




void VDShader::initFlagData(void){
	VDColor color = VDColor(0.7,0.7,0.7,1.0);

	/*	*/
	glProgramUniform1i(this->getProgram(),this->getUniformLocation(VDShaderConstant::DiffuseTexture()),VDShaderConstant::eDiffuseTexture);
	glProgramUniform1i(this->getProgram(),this->getUniformLocation(VDShaderConstant::NormalTexture()), VDShaderConstant::eNormalTexture);
	glProgramUniform1i(this->getProgram(),this->getUniformLocation(VDShaderConstant::ReflectionTexture()), VDShaderConstant::eReflectionTexture);
	glProgramUniform1i(this->getProgram(),this->getUniformLocation(VDShaderConstant::IllusionTexture()), VDShaderConstant::eIllusionTexdture);
	glProgramUniform1i(this->getProgram(),this->getUniformLocation(VDShaderConstant::DisplacementTexture()),VDShaderConstant::eDisplacementTexture);
	glProgramUniform1i(this->getProgram(),this->getUniformLocation(VDShaderConstant::SpecularTexture()), VDShaderConstant::eSpecularTexture);
	glProgramUniform1i(this->getProgram(),this->getUniformLocation(VDShaderConstant::DepthTexture()), VDShaderConstant::eDepthTexture);

	if(this->flag & VDShader::eShaderDiffuseColor){

		glProgramUniform4fv(this->getProgram(),this->getUniformLocation(VDShaderConstant::DiffuseColor()), 1, (const GLfloat*)&color[0]);
	}
	if(this->flag & VDShader::eShaderSpecularColor){
		glProgramUniform3fv(this->getProgram(),this->getUniformLocation(VDShaderConstant::SpecularColor()), 1, (const GLfloat*)&color[0]);
	}
	if(this->flag & VDShader::eShaderCubeMapColor ){
		VDColor col = VDColor(1.0f);
		glProgramUniform4fv(this->getProgram(),this->getUniformLocation(VDShaderConstant::ReflectionColor()), 1, (const GLfloat*)&col[0]);
	}

	/*	*/
	glProgramUniform1f(this->getProgram(),this->getUniformLocation(VDShaderConstant::DisplacementHeight()), 8.0f);
	glProgramUniform2f(this->getProgram(),this->getUniformLocation(VDShaderConstant::DisplacementHeight()), 0.11749996f, 0.092499979F);
	glProgramUniform1f(this->getProgram(),this->getUniformLocation("refraction"), 1.0f);

	/*	setup ambient image based uniform.	*/
	glProgramUniform1i(this->getProgram(), this->getUniformLocation(VDShaderConstant::ambientCube()), VDShaderConstant::eAmbientImageBased);


	/*	set shadow uniform values*/
	VDSystemInfo::getCompatibility()->sMaxTextureUnitActive - VDShaderConstant::eShadowMapping;

	const int shadowcount = 8;
	const int shadowcubecount = 2;
	int shadoUniform;
	int shadowsloc[16];

	/*	Shadow 2D.	*/
	for(int x = 0; x < shadowcount; x++){
		shadowsloc[x] = VDShaderConstant::eShadowMapping + x;
	}
	shadoUniform = this->getUniformLocation("ShadowSampler");
	glProgramUniform1iv(this->getProgram(), shadoUniform, shadowcubecount, shadowsloc);

	/*	Shadow cube.	*/
	for(int x = 0; x < shadowcubecount; x++){
		shadowsloc[x] = VDShaderConstant::eShadowMappingCube + x;
	}
	shadoUniform = this->getUniformLocation("ShadowCube");
	glProgramUniform1iv(this->getProgram(), shadoUniform, shadowcubecount, shadowsloc);

}

VDShader& VDShader::operator=(const VDShader& shader){
	VDAssetObject::operator=(*this);
	VD_COPY_VPTR(this, &shader);

	memcpy(&this->matrixInfo, &shader.matrixInfo, sizeof(shader.matrixInfo));
	memcpy(&this->common, &shader.common, sizeof(shader.common));
	memcpy(&this->subroutines, &shader.subroutines, sizeof(shader.subroutines));

	this->flag = shader.flag;
	VDShader::setShader(this);
	return *this;
}


void VDShader::getUniformMatrixLocation(VDShader* shader){

	if(!shader->isValid()){
		return;
	}

	/*	*/
	shader->matrixInfo.modelMatrix = shader->getUniformLocation(VDShaderConstant::ModelMatrix());
	shader->matrixInfo.viewMatrix = shader->getUniformLocation(VDShaderConstant::ViewMatrix());
	shader->matrixInfo.projectionMatrix = shader->getUniformLocation(VDShaderConstant::ProjectionMatrix());
	shader->matrixInfo.modelViewMatrix = shader->getUniformLocation(VDShaderConstant::ModelViewMatrix());
	shader->matrixInfo.modelViewProjectionMatrix = shader->getUniformLocation(VDShaderConstant::ModelViewProjection());
	shader->matrixInfo.normalMatrix = shader->getUniformLocation(VDShaderConstant::NormalMatrix());
	shader->matrixInfo.deformMatrix = shader->getUniformLocation(VDShaderConstant::DeformMatrix());
	shader->matrixInfo.viewprojection = shader->getUniformLocation(VDShaderConstant::ViewProjection());
}


void VDShader::setShader(VDShader* shader){

	if( shader == NULL ){
		VDDebug::warningLog("Can't add (NULL) Shader.\n");
		return;
	}

	if(shaderCollection[shader->getInstanceID()] == NULL){
		shaderCollection.insert(pair<unsigned int, VDShader*>(shader->getInstanceID(), shader));
		shaderCollection[shader->getInstanceID()] = shader;
	}
}

VDShader* VDShader::getShader(const VDGUID guid){
	VDShader* shad = shaderCollection[guid.getGUID()];
	return shad;
}


int VDShader::compileShader(const char* vertex, const char* fragment, const char* geomtry, const char* control, const char* evolution){

	char error[1024];
	int cshad_status;
	int vshad = 0;
	int fshad = 0;
	int gshad = 0;
	int teshad = 0;
	int tcshad = 0;

	char glversion[64];
	const char* intlist[] = {"common.glsl", "internal/functions.glsl", "internal/shadow.glsl", "internal/texture.glsl", "internal/light.glsl" };
	int arrindex = 0;
	char* tmpcommon;
	const char* vsources[16];
	const char* fsources[16];
	const char* gsources[16];
	const char* tcsources[16];
	const char* tesources[16];
	char* freelist[16];
	int freearr = 0;


	/*	Set shader version to of current opengl context. */

	char* core = "";
	if(VDSystemInfo::isOpenGLCoreProfile()){
		core = "core";
	}
	sprintf(glversion, "#version %d %s\n", VDSystemInfo::getCompatibility()->glslVersion, core);	/*	TODO evalute.*/
	vsources[arrindex] = glversion;
	fsources[arrindex] = glversion;
	gsources[arrindex] = glversion;
	tcsources[arrindex] = glversion;
	tesources[arrindex] = glversion;

	arrindex++;

	if(VDDebug::isDebugBuild()){

		/*	Add debug flag.	*/
		vsources[arrindex] = "#pragma debug (on)\n";
		fsources[arrindex] = "#pragma debug (on)\n";
		gsources[arrindex] = "#pragma debug (on)\n";
		tcsources[arrindex] = "#pragma debug (on)\n";
		tesources[arrindex] = "#pragma debug (on)\n";
		arrindex++;
	}
	else{

		/*	Add optimization.	*/
		vsources[arrindex] = "#pragma optimize (on)\n";
		fsources[arrindex] = "#pragma optimize (on)\n";
		gsources[arrindex] = "#pragma optimize (on)\n";
		tcsources[arrindex] = "#pragma optimize (on)\n";
		tesources[arrindex] = "#pragma optimize (on)\n";
		arrindex++;
	}

	vsources[arrindex] = "#define VD_VERTEX_SHADER 1\n";
	fsources[arrindex] = "#define VD_FRAGMENT_SHADER 1\n";
	gsources[arrindex] = "#define VD_GEOMETRY_SHADER 1\n";
	tcsources[arrindex] = "#define VD_TESSELLATION_CONTROL_SHADER 1\n";
	tesources[arrindex] = "#define VD_TESSELLATION_EVAULATION_SHADER 1\n";
	arrindex++;

	/*	load.	*/
	for(int i = 0; i < sizeof(intlist) / sizeof(intlist[0]); i++){
		if(VDShaderCreator::loadBuiltInShaderSource(VDShaderCreator::getAbsolutePath( intlist[i] ).c_str(), (void**)&tmpcommon) > 0){
			vsources[arrindex] = tmpcommon;
			fsources[arrindex] = tmpcommon;
			gsources[arrindex] = tmpcommon;
			tcsources[arrindex] = tmpcommon;
			tesources[arrindex] = tmpcommon;
			arrindex++;
			freelist[freearr] = tmpcommon;
			freearr++;
		}
	}

	/*	Add shader source code.	*/
	vsources[arrindex] = vertex;
	fsources[arrindex] = fragment;
	gsources[arrindex] = geomtry;
	tcsources[arrindex] = control;
	tesources[arrindex] = evolution;
	arrindex++;

	this->program = glCreateProgram();

	if(vertex){
		vshad = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vshad , arrindex, vsources, NULL);
		glCompileShader(vshad );
		glGetShaderiv(vshad , GL_COMPILE_STATUS, &cshad_status);
		glAttachShader(this->program, vshad);
	}

	if(fragment){
		fshad = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fshad , arrindex, fsources, NULL);
		glCompileShader(fshad );
		glGetShaderiv(fshad , GL_COMPILE_STATUS, &cshad_status);
		glAttachShader(this->program, fshad);
	}

	if(geomtry){
		gshad = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gshad , arrindex, gsources, NULL);
		glCompileShader(gshad);
		glGetShaderiv(gshad , GL_COMPILE_STATUS, &cshad_status);
		glAttachShader(program, gshad);
	}
	if(control){
		int shad = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(shad , arrindex, gsources, NULL);
		glCompileShader(shad );
		glGetShaderiv(shad , GL_COMPILE_STATUS, &cshad_status);
		glAttachShader(program, shad);
	}
	if(evolution){
		int shad = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(shad , arrindex, gsources, NULL);
		glCompileShader(shad );
		glGetShaderiv(shad , GL_COMPILE_STATUS, &cshad_status);
		glAttachShader(program, shad);
	}


	glLinkProgram(this->program);

	/*	*/
	validateShader(this);


	/*	*/
	glDetachShader(this->program,vshad);
	glDetachShader(this->program,fshad);
	glDetachShader(this->program,gshad);
	glDetachShader(this->program,tcshad);
	glDetachShader(this->program,teshad);
	glDeleteShader(vshad);
	glDeleteShader(fshad);
	glDeleteShader(gshad);
	glDeleteShader(tcshad);
	glDeleteShader(teshad);

	if(evolution){
		flag |= eTessellationEvaulation;
	}


	/*	*/
	for(int i = 0; i < freearr; i++){
		free(freelist[i]);
	}

	return 1;
}

unsigned int VDShader::validateShader(const VDShader* shader){

	int status, validate;
	char log[512];

	glGetProgramiv(shader->getProgram(), GL_LINK_STATUS, &status);
	glGetProgramiv(shader->getProgram(), GL_VALIDATE_STATUS, &validate);
	
	if(!status){	//Failed In Status
		if(shader->getName())
			VDDebug::errorLog("\nFailed to Link Shader %s \n ---------------------------- \n" , shader->getName());

		if (status == GL_TRUE && validate == GL_TRUE) {

		}

		if (status == GL_FALSE) {
			glGetProgramInfoLog(shader->getProgram(), sizeof(log), NULL, log);
			printf("\x1B[31m" "Failed to compile shader\n%s\n", log);
		}
		if (validate == GL_FALSE) {
			glGetProgramInfoLog(shader->getProgram(), sizeof(log), NULL, log);
			printf("\x1B[31m" "Invalid shader\n%s\n", log);
		}

		//VDShader::compilerLog(shader->getProgram(), GL_LINK_STATUS);
	}

	if(!validate){
		VDDebug::errorLog("Failed to Validate Shader : [%s]\n", shader->getName());
	}

	if(!validate || !status)
		return SDL_FALSE;

	return SDL_TRUE;
}

void VDShader::compilerLog(GLint obj, unsigned int shaderType){
	//ExShaderCompileLog(obj, shaderType);
}

void VDShader::getCompileLog(GLint obj, unsigned int type, char* infoLog){
	//ExShaderCompileLogv(obj, type, infoLog);
}



char* VDShader::getShaderSource(VDShader* shader, unsigned int shad){
	if( !shader->isValid() ){
		return NULL;
	}

	char* source = NULL;
	//if(!ExGetShaderSource(shad, &source)){
	//	return NULL;
	//}

	return source;
}

VDShader* VDShader::findShader(const char* cname){
	for(ShaderCollection::iterator x = shaderCollection.begin(); x != shaderCollection.end(); x++){
		if(x->second->getName()){
			if(strcmp(x->second->getName(), cname) == 0)
				return x->second;
		}
	}
	return NULL;
}


int VDShader::getVersion(const char* shaderSource)const{
	char* cpos = (char*)strstr(shaderSource, "#version");
	char* endpos;
	if(cpos){
		endpos = strstr(cpos, "\n");
		cpos += strlen("#version");
		return atoi(cpos);
	}else
		return -1;
}

unsigned int VDShader::getFileShaderVersion(const string& source)const{
	unsigned int firstEndLine = source.find("\n");
	unsigned int version = source.find("#version");

	if(version != string::npos){
		return stoi(string(source, version, firstEndLine - version));
	}

	return -1;
}


VDShader* VDShader::createShader(void){
	VDShader* shader = VDScene::getScene()->shaders.obtain();
	//VDShader* shader = engine.gshaders.obtain();
	VDShader tmp = VDShader();
	*shader = tmp;
	return shader;
}

VDShader* VDShader::createShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath , const char* name, const char* tessC, const char* tessE,unsigned int flag){
	VDShader* shader = VDShader::createShader();
	*shader = VDShader(vertexPath, fragmentPath, geometryPath, name, tessC, tessE, flag);
	shader->setName(name);
	return shader;
}
