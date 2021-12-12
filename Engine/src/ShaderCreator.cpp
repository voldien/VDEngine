#include <Asset/VDAssetManager.h>
#include <GL/glew.h>
#include <Rendering/VDShader.h>
#include <Rendering/VDShaderConstant.h>
#include <Rendering/VDShaderCreator.h>
#include <VDSimpleType.h>
#include <cstring>
#include <string>

//VDZipFile* zip = VDZipFile::createZipFileObject(VDAssetManager::getResourcePath(VDAssetManager::eShaderPath).c_str());



VDShader* VDShaderCreator::ComponentOutPut(unsigned int componets){
	VDShader* componentshader = VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Debug/ComponentOutPutV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Debug/ComponentOutPutF.glsl" ).c_str(),
		"",
		"ComponentOutPut");

	glProgramUniform1i(componentshader->getProgram(),componentshader->getUniformLocation("componentFlag"), componets);
	glProgramUniform1f(componentshader->getProgram(),componentshader->getUniformLocation("normalSize"), 3.0f);
	glProgramUniform1f(componentshader->getProgram(),componentshader->getUniformLocation("tangentSize"), 3.0f);
	//glUniform1i(componentshader->getUniformLocation(Shader::DiffuseTexture()), DIFFUSE_LOCATION);
	//glUniform1i(componentshader->getUniformLocation(Shader::NormalTexture()), NORMALTEXTURE_LOCATION);
	//glUniform1i(componentshader->getUniformLocation(Shader::ReflectionTexture()), REFLECTION_LOCATION);
	//glUniform1i(componentshader->getUniformLocation(Shader::SpecularTexture()), 0);
	return componentshader;
}

VDShader* VDShaderCreator::ComponentGeometryOutPut(unsigned int componet){
	VDShader* componentGeometry = VDShader::createShader(
	VDShaderCreator::getAbsolutePath( "Debug/Geometry/ComponentGeometryOutPutV.glsl" ).c_str(),
	VDShaderCreator::getAbsolutePath( "Debug/Geometry/ComponentGeometryOutPutF.glsl" ).c_str(),
	VDShaderCreator::getAbsolutePath( "Debug/Geometry/ComponentGeometryOutPutG.glsl" ).c_str(),
		"ComponentGeometryOutPut");
	componentGeometry->bind();
	glUniform1i(componentGeometry->getUniformLocation("componentFlag"), componet);
	return componentGeometry;
}

VDShader* VDShaderCreator::SingleColorShader(){

	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Legacy/SingleColorV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Legacy/SingleColorF.glsl" ).c_str(),
		"",
		"SingleColor");
}
VDShader* VDShaderCreator::VertexColor(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath("Legacy/VertexColorV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath("Legacy/VertexColorF.glsl" ).c_str(),
		"",
		"VertexColor");
}
VDShader* VDShaderCreator::VertexLit(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "VertexLit/VertexLitV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "VertexLit/VertexLitF.glsl" ).c_str(),
		"",
		"VertexLit");
}
VDShader* VDShaderCreator::Unlit(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Legacy/UnlitV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Legacy/UnliteF.glsl" ).c_str(),
		"",
		"unlit");
}

VDShader* VDShaderCreator::Diffuse(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Diffuse/DiffuseV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Diffuse/DiffuseF.glsl" ).c_str(),
		"",
		"Diffuse");
}
VDShader* VDShaderCreator::NormalDiffuse(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Diffuse/DiffuseNormalV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Diffuse/DiffuseNormalF.glsl" ).c_str(),
		"",
		"NormalDiffuse");
}
VDShader* VDShaderCreator::SpecularNormal(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Diffuse/DiffuseSpecularNormalV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Diffuse/DiffuseSpecularNormalF.glsl" ).c_str(),
		"",
		"SpecularNormal");
}
VDShader* VDShaderCreator::Specular(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Diffuse/SpecularDiffuseV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Diffuse/SpecularDiffuseF.glsl" ).c_str(),
		"",
		"Specular");
}

VDShader* VDShaderCreator::SpecularMapped(){	// specular with specular map on diffuse materail
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Diffuse/DiffuseSpecularMappedV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Diffuse/DiffuseSpecularMappedF.glsl" ).c_str(),
		"",
		"DiffuseSpecularMapped");
}

VDShader* VDShaderCreator::SpecularNormalMapped(){	// specular with specular map on DiffuseNormal material.
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Diffuse/DiffuseNormalSpecularMappedV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Diffuse/DiffuseNormalSpecularMappedF.glsl" ).c_str(),
		"",
		"DiffuseSpecularNormalMapped");
}

VDShader* VDShaderCreator::ParallaxDiffuse(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Parallax/ParallaxDiffuseV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Parallax/ParallaxDiffuseF.glsl" ).c_str(),
		"",
		"parallaxDiffuse");
}

VDShader* VDShaderCreator::ParallaxNormal(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Parallax/ParallaxNormalV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Parallax/ParallaxNormalF.glsl" ).c_str(),
		"",
		"parallaxNormal");
}
VDShader* VDShaderCreator::ParallaxNormalSpecular(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Parallax/ParallaxSpecularNormalV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Parallax/ParallaxSpecularNormalF.glsl" ).c_str(),
		"",
		"parallaxNormalSpecular");
}
VDShader* VDShaderCreator::ParallaxSpecular(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Parallax/ParallaxSpecularV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Parallax/ParallaxSpecularF.glsl" ).c_str(),
		"",
		"ParallaxSpecular");
}

VDShader* VDShaderCreator::ChromaticReflectiv(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Reflective/Chromatic/ChromaticReflectivV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Reflective/Chromatic/ChromaticReflectivF.glsl" ).c_str(),
		"",
		"ChromaticReflectiv");
}



VDShader* VDShaderCreator::RefractionDiffuse(){
	return VDShader::createShader();
}
VDShader* VDShaderCreator::RefractionNormal(){
	return VDShader::createShader();
}
VDShader* VDShaderCreator::RefractionSpecular(){
	return VDShader::createShader();
}
VDShader* VDShaderCreator::RefractionNormalSpecular(){
	return VDShader::createShader();
}
VDShader* VDShaderCreator::RefractionMapped(){
	return VDShader::createShader();
}




VDShader* VDShaderCreator::ReflectiveDiffuse(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Reflective/ReflectiveDiffuseV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Reflective/ReflectiveDiffuseF.glsl" ).c_str(),
		"",
		"ReflectiveDiffuse");
}
VDShader* VDShaderCreator::ReflectiveNormal(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Reflective/ReflectiveNormalV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Reflective/ReflectiveNormalF.glsl" ).c_str(),
		"",
		"ReflectiveNormal");
}
VDShader* VDShaderCreator::ReflectiveSpecular(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Reflective/ReflectiveSpecularV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Reflective/ReflectiveSpecularF.glsl" ).c_str(),
		"",
		"ReflectiveSpecular");
}
VDShader* VDShaderCreator::ReflectiveNormalSpecular(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Reflective/ReflectiveNormalSpecularV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Reflective/ReflectiveNormalSpecularF.glsl" ).c_str(),
		"",
		"ReflectiveNormalSpecular");
}
VDShader* VDShaderCreator::ReflectiveMapped(){
	return VDShader::createShader();
}



VDShader* VDShaderCreator::TranslucentDiffuse(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Transparent/TransparentDiffuseV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Transparent/TransparentDiffuseF.glsl" ).c_str(),
		"",
		"TransparentDiffuse");
}
VDShader* VDShaderCreator::TranslucentSpecular(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Transparent/TransparentSpecularV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Transparent/TransparentSpecularF.glsl" ).c_str(),
		"",
		"TransparentSpecular");
}
VDShader* VDShaderCreator::TranslucentNormal(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Transparent/TransparentNormalV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Transparent/TransparentNormalF.glsl" ).c_str(),
		"",
		"TransparentNormal");
}
VDShader* VDShaderCreator::TranslucentSpecularNormal(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Transparent/TransparentNormalSpecularV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Transparent/TransparentNormalSpecularF.glsl" ).c_str(),
		"",
		"TransparentNormalSpecular");
}

VDShader* VDShaderCreator::IllusionDiffuse(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Illusion/IllusionDiffuseV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Illusion/IllusionDiffuseF.glsl" ).c_str(),
		"",
		"IllusionDiffuse");
}
VDShader* VDShaderCreator::IllusionNormal(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Illusion/IllusionNormalV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Illusion/IllusionNormalF.glsl" ).c_str(),
		"",
		"IllusionNormal");
}
VDShader* VDShaderCreator::IllusionSpecular(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Illusion/IllusionSpecularV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Illusion/IllusionSpecularF.glsl" ).c_str(),
		"",
		"IllusionSpecular");
}
VDShader* VDShaderCreator::IllusionNormalSpecular(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Illusion/IllusionNormalSpecularV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Illusion/IllusionNormalSpecularF.glsl" ).c_str(),
		"",
		"IllusionNormalSpecular");
}

VDShader* VDShaderCreator::SkyBox(){
	VDShader* SkyBox = VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "SkyBox/skyboxV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "SkyBox/skyboxF.glsl" ).c_str(),
		"",
		"SkyBox");

	unsigned int i = VDShaderConstant::SkyBox;
	SkyBox->bind();
	VDColor color = VDColor(1.0f);
	glProgramUniform1iv(SkyBox->getProgram(), SkyBox->getUniformLocation(VDShaderConstant::ReflectionTexture()) , 1, (GLint*)&i);
	glProgramUniform4fv(SkyBox->getProgram(), SkyBox->getUniformLocation(VDShaderConstant::DiffuseColor()) , 1 , (GLfloat*)&color[0]);

	return SkyBox;
}

VDShader* VDShaderCreator::PostOutShader(){
	VDShader* shader = VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "PostProcessing/BasicPostVertexShader.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "PostProcessing/PostColorOutPut.glsl" ).c_str(),
		"",
		"PostOutputShader");
	shader->bind();
	glUniform1i(shader->getUniformLocation(VDShaderConstant::DiffuseTexture()),0);
	return shader;
}

VDShader* VDShaderCreator::SimpleBillboard(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath("Billbording/BillbordingV.glsl").c_str(),
		VDShaderCreator::getAbsolutePath("Billbording/BillbordingF.glsl").c_str(),
		VDShaderCreator::getAbsolutePath("Billbording/BillbordingGPoint.glsl").c_str(),
		"SimpleBillboard");
}

VDShader* VDShaderCreator::Subsurface(){
	return VDShader::createShader();
}
VDShader* VDShaderCreator::SubsurfaceNormal(){
	return VDShader::createShader();
}
VDShader* VDShaderCreator::SubsurfaceSpecular(){
	return VDShader::createShader();
}
VDShader* VDShaderCreator::SubsurfaceNormalSpecular(){
	return VDShader::createShader();
}
VDShader* VDShaderCreator::SubsurfaceMapped(){
	return VDShader::createShader();
}

VDShader* VDShaderCreator::ForwardFirstPassShadow(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Shadow/shadowV.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Shadow/shadowF.glsl" ).c_str(),
		"",
		"simpleShadow");
}

VDShader* VDShaderCreator::CubeMapShadow(){
	return VDShader::createShader(
		VDShaderCreator::getAbsolutePath( "Shadow/shadowcubemapV.glsl.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Shadow/shadowcubemapF.glsl.glsl" ).c_str(),
		VDShaderCreator::getAbsolutePath( "Shadow/shadowcubemapG.glsl" ).c_str(),
		"simpleShadow");
}

VDShader* VDShaderCreator::createPostProcessingShader(const char* cVertexShader,
		const char* cFragmentShader, const char* cGeometryShader){
	VDShader* processingShader = VDShader::createShader(
		cVertexShader,
		cFragmentShader,
		cGeometryShader,
		"");
	return processingShader;
}


long int VDShaderCreator::loadShaderString(const char* cfilename, void** data){
	long int nbytes;

	if(cfilename == nullptr){
		return -1;
	}

	// if(strstr(cfilename, "glsl.gz") != nullptr){
	// 	nbytes = VDGZFile::loadString(cfilename, (char**)data);
	// 	if(nbytes <= 0){

	// 	}
	// }else{
	// 	nbytes = VDFile::loadString(cfilename, (char**)data);
	// 	if(nbytes <= 0){

	// 	}
	// }

	return nbytes;
}

long int VDShaderCreator::loadBuiltInShaderSource(const char* cfilename, void** pbuffer){

	/*	TODO add support for gzip.	*/
	long int nbytes;

	if(cfilename == nullptr){
		return -1;
	}

	// if(strstr(cfilename, "glsl.gz") != nullptr){
	// 	nbytes = VDGZFile::loadString(cfilename, (char**)pbuffer);
	// 	if(nbytes <= 0){

	// 	}
	// }else{
	// 	nbytes = VDFile::loadString(cfilename, (char**)pbuffer);
	// 	if(nbytes <= 0){

	// 	}
	// }

	return nbytes;

}


