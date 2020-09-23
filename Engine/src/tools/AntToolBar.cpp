//#include <AntTweakBar.h>
#include <Audio/VDAudioSetting.h>
#include <Core/VDDebug.h>
#include <Core/VDEngine.h>
#include <Core/VDInput.h>
#include <Core/VDQualitySetting.h>
#include <Core/VDScreen.h>
#include <Core/VDTime.h>
#include <Core/VDTypes.h>
#include <DataStructure/VDPoolAllactor.h>
#include <Rendering/VDCamera.h>
#include <Rendering/VDRenderSetting.h>
#include <stdint.h>
#include <Scene/VDGameObject.h>
#include <Tools/VDTweakBar.h>
#include <VDDef.h>
#include <VDSimpleType.h>
#include <VDSystemInfo.h>

// VDTweakBar::VDTweakBar(void){
// 	this->antcallback.resize(100);
// 	this->init();
// }

// VDTweakBar::~VDTweakBar(void){

// }

// void VDTweakBar::draw(void){
// 	TwDraw();
// }

// void VDTweakBar::onResize(int width, int height){
// 	TwWindowSize(width, height);
// 	TwSetCurrentWindow((intptr_t)VDEngine::getDrawable());
// }

// void VDTweakBar::onMouse(int x, int y, int button){
// 	TwMouseMotion(x,y);
// 	//TwMouseButton()
// }

// void VDTweakBar::onMouseWheel(int direction){
// 	TwMouseWheel(direction);
// }

// void VDTweakBar::onMousePressed(VDInput::Button pressed){
// 	TwMouseButton((TwMouseAction)TW_MOUSE_PRESSED, (TwMouseButtonID)pressed);
// }

// void VDTweakBar::onMouseReleased(VDInput::Button released){
// 	TwMouseButton((TwMouseAction)TW_MOUSE_RELEASED, (TwMouseButtonID)released);
// }


// void VDTweakBar::onKeyPressed(unsigned int  code){
// 	int mod = 0;
// 	/*
// 	if(event->alt)
// 		mod |= TW_KMOD_ALT;
// 	if(event->ctrl)
// 		mod |= TW_KMOD_CTRL;
// 	if(event->shift)
// 		mod |= TW_KMOD_SHIFT;
// 	*/

// 	TwKeyPressed(code, mod);
// }



// static void private_setcallback(const void* value, VDTweakBar::VDTweakCallbackAttribute* clientData){
// 	VDSetCallBack func = (VDSetCallBack)clientData->set;
// 	switch(clientData->type){
// 	case TW_TYPE_COLOR4F:
// 		func((VDColor*)value);
// 		break;
// 	default:
// 		func( VDCASTP(void*, *(unsigned int*)value) );
// 		break;
// 	}
// }

// static void private_getcallback(void* value, VDTweakBar::VDTweakCallbackAttribute* clientdata){
// 	VDGetCallBack func = (VDGetCallBack)clientdata->get;

// 	*(unsigned int*)value = (intptr_t)func();
// }

// static void private_method_setcallback(const void* value, VDTweakBar::VDTweakCallbackAttribute* clientData){
// 	VDSetClassMethod func = (VDSetClassMethod)clientData->mset;
// 	VDBehavior* obj = (VDBehavior*)clientData->getObject();

// 	switch(clientData->type){
// 	case TW_TYPE_COLOR4F:
// 		((obj)->*func)((VDColor*)value);
// 		break;
// 	default:
// 		((obj)->*func)( VDCASTP(void*, *(unsigned int*)value) );
// 		break;
// 	}
// }


// static void private_method_getcallback(void* value, VDTweakBar::VDTweakCallbackAttribute* clientdata){
// 	VDGetClassMethod func = (VDGetClassMethod)clientdata->mget;
// 	VDBehavior* obj = (VDBehavior*)clientdata->getObject();

// 	*(unsigned int*)value =  (intptr_t)((obj)->*func)();
// }


// void VDTweakBar::init(void){
// 	TwInit(VDSystemInfo::getCompatibility()->isGLCore ? TwGraphAPI::TW_OPENGL_CORE : TwGraphAPI::TW_OPENGL, VDEngine::getOpenGLContext());
// 	this->onResize(VDScreen::width(), VDScreen::height());

// 	TwType seasonType;


// 	/**/
// 	TwBar* ga = TwNewBar("Main Camera");
// 	VDTweakCallbackAttribute* propertie = antcallback.obtain();
// 	propertie->mget = (VDGetClassMethod)&VDCamera::getBackColor;
// 	propertie->mset = (VDSetClassMethod)&VDCamera::setBackColor;
// 	propertie->getObject = (VDGetCallBack)VDCamera::getMainCamera;
// 	propertie[0].type = TW_TYPE_COLOR4F;
// 	TwAddVarCB(ga, "backcolor", TW_TYPE_COLOR4F, (TwSetVarCallback)private_method_setcallback, (TwGetVarCallback)private_method_getcallback, propertie , "");

// 	propertie = antcallback.obtain();
// 	propertie->mget = (VDGetClassMethod)&VDCamera::getFar;
// 	propertie->mset = (VDSetClassMethod)&VDCamera::setFar;
// 	propertie->getObject = (VDGetCallBack)VDCamera::getMainCamera;
// 	TwAddVarCB(ga, "far", TW_TYPE_FLOAT, (TwSetVarCallback)private_method_setcallback, (TwGetVarCallback)private_method_getcallback, propertie , "");


// 	propertie = antcallback.obtain();
// 	propertie->mget = (VDGetClassMethod)&VDCamera::getNear;
// 	propertie->mset = (VDSetClassMethod)&VDCamera::setNear;
// 	propertie->getObject = (VDGetCallBack)VDCamera::getMainCamera;
// 	TwAddVarCB(ga, "near", TW_TYPE_FLOAT, (TwSetVarCallback)private_method_setcallback, (TwGetVarCallback)private_method_getcallback, propertie , "");

// 	propertie = antcallback.obtain();
// 	propertie->mget = (VDGetClassMethod)&VDCamera::getClearMode;
// 	propertie->mset = (VDSetClassMethod)&VDCamera::setClearMode;
// 	propertie->getObject = (VDGetCallBack)VDCamera::getMainCamera;
// 	TwEnumVal clearmode[] = { 	{VDCamera::eDontClear, "DontClear"},
// 								{VDCamera::eClear, "Clear"},
// 								{VDCamera::eSkyBox, "SkyBox"}
// 							};
// 	seasonType = TwDefineEnum("clear_mode", clearmode, 3);
// 	TwAddVarCB(ga, "clearMode", seasonType, (TwSetVarCallback)private_method_setcallback, (TwGetVarCallback)private_method_getcallback, propertie , "clear_mode");


// 	propertie = antcallback.obtain();
// 	propertie->mget = (VDGetClassMethod)&VDCamera::getProjectionMode;
// 	propertie->mset = (VDSetClassMethod)&VDCamera::setProjectionMode;
// 	propertie->getObject = (VDGetCallBack)VDCamera::getMainCamera;
// 	TwEnumVal projectionmode[] = { 	{VDCamera::eOrthographic, "Orthographic"},
// 								{VDCamera::ePerspective, "Perspective"},
// 							};
// 	seasonType = TwDefineEnum("projection_mode", projectionmode, 2);
// 	TwAddVarCB(ga, "ProjectionMode", seasonType, (TwSetVarCallback)private_method_setcallback, (TwGetVarCallback)private_method_getcallback, propertie , "clear_mode");


// 	propertie = antcallback.obtain();
// 	propertie->mget = (VDGetClassMethod)&VDCamera::getPolygoneMode;
// 	propertie->mset = (VDSetClassMethod)&VDCamera::setPolygoneMode;
// 	propertie->getObject = (VDGetCallBack)VDCamera::getMainCamera;
// 	TwEnumVal polygonemode[] = { 	{VDCamera::Point, "Point"},
// 								{VDCamera::eWireFrame, "WireFrame"},
// 								{VDCamera::eTriangle, "Triangle"}
// 							};
// 	seasonType = TwDefineEnum("polygonemode", polygonemode, sizeof(polygonemode) / sizeof(polygonemode[0]));
// 	TwAddVarCB(ga, "polygonemode", seasonType, (TwSetVarCallback)private_method_setcallback, (TwGetVarCallback)private_method_getcallback, propertie , "clear_mode");


// 	propertie = antcallback.obtain();
// 	propertie->mget = (VDGetClassMethod)&VDCamera::isHDREnabled;
// 	propertie->mset = (VDSetClassMethod)&VDCamera::hdr;
// 	propertie->getObject = (VDGetCallBack)VDCamera::getMainCamera;
// 	TwAddVarCB(ga, "HDR", TW_TYPE_BOOLCPP, (TwSetVarCallback)private_method_setcallback, (TwGetVarCallback)private_method_getcallback, propertie , "");


// 	propertie = antcallback.obtain();
// 	propertie->mget = (VDGetClassMethod)&VDCamera::usePostEffect;
// 	propertie->mset = (VDSetClassMethod)&VDCamera::posteffect;
// 	propertie->getObject = (VDGetCallBack)VDCamera::getMainCamera;
// 	TwAddVarCB(ga, "post effect", TW_TYPE_BOOLCPP, (TwSetVarCallback)private_method_setcallback, (TwGetVarCallback)private_method_getcallback, propertie , "");




// 	/*	*/
// 	TwBar* qu =  TwNewBar("visual settings");

// 	TwAddSeparator(qu, "shadow","");

// 	propertie = antcallback.obtain();
// 	propertie->get = (void*)VDQualitySetting::isShadowEnable;
// 	propertie->set = (void*)VDQualitySetting::useShadow;
// 	TwAddVarCB(qu, "shadow enabled", TW_TYPE_BOOLCPP, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	TwEnumVal shadowFilter[] = { 	{VDQualitySetting::ShadowFilter::eSimple, "Simple"},
// 									{VDQualitySetting::ShadowFilter::ePCF, "PCF"},
// 									{VDQualitySetting::ShadowFilter::eVariance, "Variance"}
// 								};
// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDQualitySetting::getShadowFilter;
// 	propertie[0].set = (void*)VDQualitySetting::setShadowFilter;
// 	seasonType = TwDefineEnum("shadowfilter", shadowFilter, 3);
// 	TwAddVarCB(qu, "shadow filter", seasonType, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");


// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDQualitySetting::getShadowDistance;
// 	propertie[0].set = (void*)VDQualitySetting::setShadowDistance;
// 	TwAddVarCB(qu, "shadow distance", TW_TYPE_FLOAT, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	/**/
// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDRenderSetting::getAmbientColor;
// 	propertie[0].set = (void*)VDRenderSetting::setAmbientColor;
// 	propertie[0].type = TW_TYPE_COLOR4F;
// 	TwAddVarCB(qu, "color", TW_TYPE_COLOR4F,(TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie, "");

// 	/*	*/
// 	TwEnumVal AntiAmbientType[] = { 		{VDRenderSetting::AmbientType::eConstant, "Constant"},
// 									{VDRenderSetting::AmbientType::eImageBased, "ImageBased"}
// 	};
// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDRenderSetting::getAmbientType;
// 	propertie[0].set = (void*)VDRenderSetting::setAmbientType;
// 	seasonType = TwDefineEnum("ambientType", AntiAmbientType, sizeof(AntiAmbientType) / sizeof(AntiAmbientType[0]));
// 	TwAddVarCB(qu, "ambient Type", seasonType,(TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie, "");


// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDRenderSetting::getAmbientIntensity;
// 	propertie[0].set = (void*)VDRenderSetting::setAmbientIntensity;
// 	TwAddVarCB(qu, "ambient intensity", TW_TYPE_FLOAT, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	/*
// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDRenderSetting::getAmbientColor;
// 	propertie[0].set = (void*)VDRenderSetting::setAmbientColor;
// 	propertie[0].type = TW_TYPE_COLOR4F;
// 	TwAddVarCB(qu, "color", TW_TYPE_COLOR4F,(TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie, "");
// 	*/

// 	TwAddSeparator(qu, "anti aliasing","anti aliasing");
// 	TwEnumVal AntiFilter[] = { 		{VDQualitySetting::SampleType::None, "None"},
// 									{VDQualitySetting::SampleType::eMSAA, "MSAA"},
// 									{VDQualitySetting::SampleType::eSA, "SA"},
// 									{VDQualitySetting::SampleType::eSSAA, "SSAA"},
// 								};
// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDQualitySetting::getSampleMode;
// 	propertie[0].set = (void*)VDQualitySetting::setSamplerMode;
// 	seasonType = TwDefineEnum("anti", AntiFilter, sizeof(AntiFilter) / sizeof(AntiFilter[0]));
// 	TwAddVarCB(qu, "anti ", seasonType, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDQualitySetting::getAntaiAlisingSampling;
// 	propertie[0].set = (void*)VDQualitySetting::setAntaiAlisingSampling;
// 	TwAddVarCB(qu, "anti samples", TW_TYPE_INT32, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");


// 	TwAddSeparator(qu, "fog","fog");
// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDRenderSetting::getFogColor;
// 	propertie[0].set = (void*)VDRenderSetting::setFogColor;
// 	propertie[0].type = TW_TYPE_COLOR4F;
// 	TwAddVarCB(qu, "color ", TW_TYPE_COLOR4F, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDRenderSetting::getFogDensity;
// 	propertie[0].set = (void*)VDRenderSetting::setFogDensity;
// 	TwAddVarCB(qu, "density ", TW_TYPE_FLOAT, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");


// 	TwEnumVal fogType[] = { 		{VDRenderSetting::eFogDisable, "None"},
// 									{VDRenderSetting::eFogLinear, "Linear"},
// 									{VDRenderSetting::eFogExp, "Exp"},
// 									{VDRenderSetting::eFogExp2, "Exp2"},
// 								};
// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDRenderSetting::getFogType;
// 	propertie[0].set = (void*)VDRenderSetting::setFogType;
// 	seasonType = TwDefineEnum("fog", fogType, sizeof(fogType) / sizeof(fogType[0]));
// 	TwAddVarCB(qu, "type ", seasonType, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDRenderSetting::getFogMaxDistance;
// 	propertie[0].set = (void*)VDRenderSetting::setFogMaxDistance;
// 	TwAddVarCB(qu, "max distance", TW_TYPE_FLOAT, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	propertie = antcallback.obtain();
// 	propertie[0].get = (void*)VDRenderSetting::getFogMinDistance;
// 	propertie[0].set = (void*)VDRenderSetting::setFogMinDistance;
// 	TwAddVarCB(qu, "min distance", TW_TYPE_FLOAT, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");



// 	TwAddSeparator(qu, "colorspace","colorspace");

// 	propertie = antcallback.obtain();
// 	TwEnumVal colorspace[] = { 	{VDQualitySetting::ColorSpace::eGamma, "Gamma"},
// 									{VDQualitySetting::ColorSpace::eLinear, "Linear"},
// 									{VDQualitySetting::ColorSpace::eSrga, "SRGBA"},
// 								};
// 	propertie->get = (void*)VDQualitySetting::getColorSpace;
// 	propertie->set = (void*)VDQualitySetting::setColorSpace;
// 	seasonType = TwDefineEnum("colorspace", colorspace, sizeof(colorspace) / sizeof(colorspace[0]));
// 	TwAddVarCB(qu, "ColorSpace", seasonType, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	TwAddSeparator(qu, "texture","texture");

// 	propertie = antcallback.obtain();
// 	propertie->get = (void*)VDQualitySetting::getTextureLod;
// 	propertie->set = (void*)VDQualitySetting::setTextureLod;
// 	TwAddVarCB(qu, "TextureLoad", TW_TYPE_INT32, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	propertie = antcallback.obtain();
// 	propertie->get = (void*)VDQualitySetting::getTextureAnisotropy;
// 	propertie->set = (void*)VDQualitySetting::setTextureAnisotropy;
// 	TwAddVarCB(qu, "Texture Aniso", TW_TYPE_FLOAT, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");


// 	TwAddSeparator(qu, "culling","culling");


// 	TwAddSeparator(qu, "renderingpipeline","renderingpipeline");
// 	propertie = antcallback.obtain();
// 	propertie->get = (void*)VDRenderSetting::getRenderingPath;
// 	propertie->set = (void*)VDRenderSetting::setRenderingPath;
// 	TwEnumVal RenderPipeLine[] = {
// 								{VDRenderSetting::RenderPipeline::eForwardRendering, "Forward"},
// 							};
// 	seasonType = TwDefineEnum("renderpipeline", RenderPipeLine, 2);
// 	TwAddVarCB(qu, "render pipeline type", seasonType, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");



// 	propertie = antcallback.obtain();
// 	propertie->get = (void*)VDQualitySetting::getVSync;
// 	propertie->set = (void*)VDQualitySetting::setVSync;
// 	TwAddVarCB(qu, "VSync", TW_TYPE_BOOLCPP, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");




// 	/*	*/
// 	//propertie = antcallback.obtain();
// 	//propertie->get = (void*)VDQualitySetting::getCulling;
// 	//propertie->set = (void*)VDQualitySetting::setCulling;
// 	//TwAddVarCB(qu, "Culling", TW_TYPE_BOOLCPP, (TwSetVarCallback)setcallback, (TwGetVarCallback)getcallback, propertie , "");

// 	TwAddSeparator(qu, "audio","audio");
// 	/*	Audio	*/
// 	propertie = antcallback.obtain();
// 	propertie->get = (void*)VDAudioSetting::getMasterVolume;
// 	propertie->set = (void*)VDAudioSetting::setMasterVolume;
// 	TwAddVarCB(qu, "Volume", TW_TYPE_FLOAT, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	propertie = antcallback.obtain();
// 	propertie->get = (void*)VDAudioSetting::getSampleRate;
// 	propertie->set = (void*)VDAudioSetting::setSampleRate;
// 	TwAddVarCB(qu, "Sample", TW_TYPE_UINT32, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");

// 	propertie = antcallback.obtain();
// 	propertie->get = (void*)VDAudioSetting::getVolumeSpeed;
// 	propertie->set = (void*)VDAudioSetting::setVolumeSpeed;
// 	TwAddVarCB(qu, "Speed", TW_TYPE_FLOAT, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");



// 	if(VDDebug::isDebugEnabled() || VDDebug::isDebugBuild()){
// 		TwAddSeparator(qu, "Debug", "");
// 	}

// 	/*	time.	*/
// 	TwAddSeparator(qu, "time", "time");
// 	propertie = antcallback.obtain();
// 	propertie->get = (void*)VDTime::getTimeScale;
// 	propertie->set = (void*)VDTime::setTimeScale;
// 	TwAddVarCB(qu, "timescale", TW_TYPE_FLOAT, (TwSetVarCallback)private_setcallback, (TwGetVarCallback)private_getcallback, propertie , "");
// }


// void VDTweakBar::release(void){
// 	TwTerminate();
// }

// void VDTweakBar::update(void){

// 	TwMouseMotion(VDInput::x(), VDInput::y());
// 	//TwMouseButton(VDInput::isKeyDown(EXK_h) ? TW_MOUSE_PRESSED : TW_MOUSE_RELEASED , TW_MOUSE_LEFT );
// 	//TwKeyPressed(VDInput::getKey(), TW_KMOD_NONE);


// 	VDGameObject* obj;
// 	obj = VDCamera::getMainCamera()->screenSpaceToWorldSpaceObject(VDVector2(VDInput::x(),VDInput::x()));
// 	if(obj){
// 		TwBar* ga =  TwNewBar("GameObject");
// 		for(int x = 0; obj->getComponentCount(); x++){
// 			obj->getComponentByIndex(x);
// 			VDTypeInfo type;
// 		}
// 	}
// }
