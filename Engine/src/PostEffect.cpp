
#include <Rendering/Texture/VDTexture2D.h>
#include <Rendering/VDPostEffect.h>
#include <Rendering/VDRender.h>
#include <Rendering/VDRenderSetting.h>
#include <Rendering/VDShaderConstant.h>
#include <Rendering/VDShaderCreator.h>
#include <stddef.h>
#include <SDL2/SDL_stdinc.h>
#include <Utility/VDTextureProcedure.h>
#include <Utility/VDTextureUtility.h>
#include <VDSimpleType.h>
#include <vector>
#include<Core/Math.h>



using namespace std;
std::vector<VDPostEffect*> VDPostEffect::gPostProcessingObject;

VDPostEffect::VDPostEffect(void) : VDMaterial(){
	this->enable = SDL_TRUE;
	this->sample = 1;
	this->flag = 0;
}

VDPostEffect::VDPostEffect(const char* vertexShader, const char* fragmentShader) : VDMaterial() {
	this->setShader(VDShaderCreator::createPostProcessingShader(vertexShader, fragmentShader, NULL));
	this->enable = SDL_TRUE;
	this->flag = Color;
	this->sample = 1;

	gPostProcessingObject.push_back(this);
}

VDPostEffect::~VDPostEffect(void){

}

bool VDPostEffect::isEnabled(void)const{
	return this->enable != 0;
}

unsigned int VDPostEffect::getsNumSample(void)const{
	return sample;
}

void VDPostEffect::setNumSample(unsigned int sample){
	this->sample = sample;
}


void VDPostEffect::render(void){
	VDRenderer::drawMesh(VDRenderSetting::getSettings()->quadDisplay);
}

VDPostEffect* VDPostEffect::grayScale(void){
	VDPostEffect* grayScale = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/grayscale.glsl");
	return grayScale;
}

VDPostEffect* VDPostEffect::sepia(void){
	VDPostEffect* sepia = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/sepia.glsl");
	return sepia;
}

VDPostEffect* VDPostEffect::vineta(void){
	VDPostEffect* vineta = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/vignetting.glsl");
	return vineta;
}

VDPostEffect* VDPostEffect::FSAA(unsigned int sampler){
	VDPostEffect* fsaa = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/FSAA.glsl");
	fsaa->setInt("AAsampler", sampler);
	return fsaa;
}

VDPostEffect* VDPostEffect::invert(void){
	VDPostEffect* InvertPost = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/invert.glsl");
	return InvertPost;
}


VDPostEffect* VDPostEffect::noise(void){
	VDPostEffect* noise = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/noise.glsl");
	return noise;
}


VDPostEffect* VDPostEffect::blur(unsigned int samplerCount, float radius){
	VDPostEffect* blur = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/blur.glsl"
		);

	blur->flag |= Color;
	blur->sample = 4;
	blur->setInt("BlurAmount",(unsigned int)(radius * 2.0f));
	blur->setfloat("BlurScale", 1.0f);
	return blur;
}

VDPostEffect* VDPostEffect::colorCorrection(const VDColor& ColorBlend){
	VDPostEffect* ColorCorrectionPost = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/colorCorrection.glsl");
	ColorCorrectionPost->setColor(VDShaderConstant::DiffuseColor(), ColorBlend);
	return ColorCorrectionPost;
}

VDPostEffect* VDPostEffect::DOF(float focusDistance, float focusLenght){
	VDPostEffect* DofEffect = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/dof.glsl"
		);
	DofEffect->sample = 1;
	DofEffect->flag = Color | eDepth;
	DofEffect->setInt(VDShaderConstant::DepthTexture(), 1);

	DofEffect->setfloat("FocusDistance",focusDistance);
	DofEffect->setfloat("FocusLenght",focusLenght);
	return DofEffect;
}

VDPostEffect* VDPostEffect::bokeh(void){
	VDPostEffect* bokeh = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/bokeh.glsl"
		);
	return bokeh;
}


VDPostEffect* VDPostEffect::DepthBuffer(void){
	VDPostEffect* depthEffect = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl" ,
		"shader/PostProcessing/Depth.glsl"
		);
	depthEffect->flag = eDepth;
	depthEffect->setInt(VDShaderConstant::DepthTexture(),1);
	return depthEffect;
}

VDPostEffect* VDPostEffect::GammaCorrection(void){
	VDPostEffect* gamma = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl" ,
		"shader/PostProcessing/gammecorrection.glsl" );
	gamma->flag = Color;
	return gamma;
}

VDPostEffect* VDPostEffect::SSAO(void){
	VDPostEffect* postSAO = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/ssao.glsl");
	postSAO->setInt("NormalTexture",2);
	postSAO->setInt("WorldTexture",3);
	postSAO->setInt(VDShaderConstant::DepthTexture(),1);
	postSAO->setInt("NormalRandomize",4);
	VDTexture2D* randomTex = VDTextureProcedure::RandomTexture(64,64);
	VDTexture2D* normal = VDTextureUtility::genNormal(randomTex);
	delete randomTex;
	postSAO->setTexture(4, normal);
	return postSAO;
}

VDPostEffect* VDPostEffect::HBAO(void){
	VDPostEffect* postHBAO = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/HBAmbientOcclusion.glsl");
	return NULL;
}

VDPostEffect* VDPostEffect::LightShattering(void){
	VDPostEffect* LightshattPost = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/VolumetricLight.glsl");

	LightshattPost->flag = Color | eDepth;
	LightshattPost->setInt(VDShaderConstant::DepthTexture(),1);
	LightshattPost->setInt("RadianSampler", 20);
	LightshattPost->setVec3("lightPos", VDVector3(0.4,-0.4, 200));

	return LightshattPost;
}

VDPostEffect* VDPostEffect::Fog(const VDColor& fogColor, float start, float end, float density, unsigned char mode){
	VDPostEffect* fogPost = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/Fog.glsl");
	fogPost->flag = Color | eDepth;
	fogPost->setInt(VDShaderConstant::DepthTexture(),1);
	fogPost->setInt("FogMode",mode);
	fogPost->setColor(VDShaderConstant::DiffuseColor(), fogColor);
	fogPost->setfloat("startValue",start);
	fogPost->setfloat("endValue",end);
	fogPost->setfloat("density", fragcore::Math::clamp(density, 0.0001f, 1.0f));
	return fogPost;
}

VDPostEffect* VDPostEffect::motionBlur(void){
	VDPostEffect* motionBlur = new VDPostEffect(
			"shader/PostProcessing/BasicPostVertexShader.glsl",
			"shader/PostProcessing/motionblur.glsl");

	motionBlur->setInt("DiffuseTexture0", 6);
	motionBlur->setInt("DiffuseTexture1", 7);
	motionBlur->setInt("DiffuseTexture2", 8);
	motionBlur->setInt("DiffuseTexture3", 9);
	motionBlur->setInt("DiffuseTexture4", 10);

	motionBlur->sample = 1;
	motionBlur->flag = (Color | eDepth);
	return motionBlur;
}

VDPostEffect* VDPostEffect::bloom(void){
	VDPostEffect* BloomPost = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/bloom.glsl"
		);
	BloomPost->sample = 1;
	BloomPost->flag = Color | eDepth | sIntensity;
	return BloomPost;
}

VDPostEffect* VDPostEffect::glow(unsigned int samplerCount, float Radius){
	VDPostEffect* glowEffect = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/glow.glsl");

	glowEffect->flag = (Color);
	glowEffect->setInt("BlurAmount",(unsigned int)(Radius * 2.0f));
	glowEffect->setInt("GlowSettings", (2 | 4 | 8));

	return glowEffect;
}

VDPostEffect* VDPostEffect::HDR(void){
	VDPostEffect* hdr = new VDPostEffect(
		"shader/PostProcessing/BasicPostV.glsl",
		"shader/PostProcessing/HDR.glsl");

	return hdr;
}
