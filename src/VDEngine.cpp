
#include <Asset/VDAssetManager.h>
#include <Audio/VDAudio.h>
#include <Audio/VDAudioListener.h>
#include <Core/VDApplication.h>
#include <Core/VDDebug.h>
#include <Core/VDDisplay.h>
#include <Core/VDEngine.h>
#include <Core/VDEngineCore.h>
#include <Core/VDEvent.h>
#include <Core/VDInput.h>
#include <Core/VDLayer.h>
#include <Core/VDMatrix.h>
#include <Core/VDObject.h>
#include <Core/VDQualitySetting.h>
#include <Core/VDScreen.h>
#include <Core/VDTime.h>
#include <DataStructure/VDDoubleBufferedAllocator.h>
#include <DataStructure/VDPoolAllactor.h>
#include <DataStructure/VDQueue.h>
#include <DataStructure/VDSize.h>
#include <getopt.h>
#include <GL/glew.h>
#include <hpm/hpm.h>
#include <Misc/VDFile.h>
#include <Misc/VDMath.h>
#include <Physic/VDPhysic.h>
#include <Rendering/Texture/VDCubeMap.h>
#include <Rendering/Texture/VDTexture.h>
#include <Rendering/Texture/VDTexture2D.h>
#include <Rendering/VDBufferObject.h>
#include <Rendering/VDColor32.h>
#include <Rendering/VDLight.h>
#include <Rendering/VDMaterial.h>
#include <Rendering/VDRender.h>
#include <Rendering/VDRenderingAPICache.h>
#include <Rendering/VDRenderPipeline.h>
#include <Rendering/VDRenderSetting.h>
#include <Rendering/VDShader.h>
#include <Rendering/VDShaderConstant.h>
#include <Rendering/VDShaderCreator.h>
#include <Rendering/VDUniformBuffer.h>
#include <signal.h>
#include <Scene/VDGameObject.h>
#include <Scene/VDScene.h>
#include <Scene/VDSkyBox.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_filesystem.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_platform.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <Utility/VDTextureProcedure.h>
#include <VDSystemInfo.h>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include<HpmCpp.h>
#include<fragcore/FragCore.h>
#include<fragcore/Window/WindowManager.h>


#define VDENGINE_DEINIT (1 << 31)

VDEngineCore engine;

extern char* getGameEngineDefaultTitle(void);

/*	signal interrupt event	*/
void catchEngineSignal(int signal){

	/*	TODO make sure that a dump file of information is created here or somewhere else!	*/
	switch(signal){
	case SIGINT:{
		VDDebug::log("Interrupt.\n");
		VDApplication::quit(EXIT_SUCCESS);
	}break;
	case SIGILL:{
		/**/
		VDDebug::log("Invalid instruction.\n");
		VDApplication::quit(EXIT_FAILURE);
	}break;
	case SIGSEGV:{
		/**/
		VDDebug::log("Segmentation Violation.\n");
		VDApplication::quit(EXIT_FAILURE);
	}break;
	case SIGKILL:{
		VDDebug::log("Kill request.\n");
		VDApplication::quit();
	}break;
	case SIGUSR1:
		break;
	default:
		VDApplication::quit();
		break;
	}
}

int VDEngine::init(int argc, const char** argv, VDEngine::SubSystem subsystem){

	int ret = SDL_FALSE;
	VDSize size;
	char buf[PATH_MAX];

	unsigned int majver, minver, reviver;
	int glflagatt;
	int glatt;

	/*	Initialize values.	*/
	engine.active = engine.active & ~VDENGINE_DEINIT;

	/*	Get VDEngine build version and output it.	*/
	VDDebug::log("VDEngine version %s\n", VDEngine::getVersion());
	VDDebug::log("==========================\n\n");
	VDDebug::log("Platform %s\n", SDL_GetPlatform());


	/*	add signal routine	*/
	signal(SIGINT,	catchEngineSignal);
	signal(SIGILL,	catchEngineSignal);
	signal(SIGKILL,	catchEngineSignal);
	signal(SIGSEGV,	catchEngineSignal);

	/*	Add engine terminate function in the event of a crash.	*/
	atexit(VDEngine::releaseEngine);

	/*	Read arguments	*/
	engine.config = (VDConfigure::VDConfig*)malloc(sizeof(VDConfigure::VDConfig));
	memset(engine.config, 0, sizeof(VDConfigure::VDConfig));
	VDConfigure::defaultConfig(engine.config);
	std::string cconfigfile = VDAssetManager::getResourcePath(VDAssetManager::ResourceType::eConfig);
	VDDebug::log("Reading configuration file %s.\n", cconfigfile.c_str());


	/*	TODO resolve absolute path for engine files in respect to what platform.	*/
	// if(VDConfigure::loadConfigFile(cconfigfile.c_str(), engine.config) == SDL_FALSE){
	// 	VDDebug::errorLog("Failed to load configuration file %s\n", cconfigfile.c_str());
	// }

	/*	Read first pass of option argument.	*/
	if(VDEngine::readArgument(argc, argv, 1) == 2){
		VDApplication::quit(EXIT_SUCCESS);
	}


	/*	Initialize the engine once.	*/
	if(engine.flag & VDEngine::eInitialize){
		VDDebug::log("Engine has already been initialized.\n");
		return VDEngine::eInitialize;
	}

	/*	*/
	engine.flag |= VDEngine::eInitialize;
	engine.flag |= subsystem;


	//HpmCpp::init(HpmCpp::eHPM_DEFAULT);
	if(!hpm_init(HPM_DEFAULT)){
		fprintf(stderr, "Failed to init hpm.\n");
		exit(EXIT_FAILURE);
	}



	/*	Initialize EC core.	*/
	ret = SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER);
	if(ret != 0){
		fprintf(stderr, "SDL_Init failed, %s.\n", SDL_GetError());
		VDApplication::quit(EXIT_FAILURE);
	}


	/*	Reserve OpenGL context pointers	*/
	engine.glcontext.resize(2 * VDSystemInfo::getCPUCoreCount());


	/*	Get primary monitor configured resolutions.	*/
	size = VDDisplay::getPrimaryScreenSize();
	VDDebug::log("Creating window with dimensions.\n");

	/*	Create window!	*/
	engine.window = (VDWindow*)SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			size.width() / 2, size.height() / 2,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if(engine.window == NULL){
		/*	failed	*/
		VDDebug::errorLog("Failed to create Window, %s.\n", SDL_GetError());
		VDApplication::quit(EXIT_FAILURE);
	}


	/*	Create OpenGL context.	*/
#ifdef _DEBUG
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_FLAGS, &glflagatt);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, glflagatt | SDL_GL_CONTEXT_DEBUG_FLAG);
#endif
	engine.glc = (VDGLContext)SDL_GL_CreateContext((SDL_Window*)engine.window);

	/*	Check if OpenGL context was successfully created.	*/
	if(engine.glc == NULL){
		VDDebug::errorLog("Failed to create OpenGL core context.\n");

		/*	setup for creating a forward compatible context	*/
		VDDebug::log("Attempting to create another context solution.\n");
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

		/*	*/
		if(! (engine.glc = SDL_GL_CreateContext((SDL_Window*)engine.window)) ){
			VDDebug::errorLog("Couldn't create OpenGL context.\n");
			VDApplication::quit(EXIT_FAILURE);
		}
	}

	/*	Allocate reference to drawable and OpenGL context.	*/
	engine.drawable = (VDWindow*)SDL_GL_GetCurrentWindow();
	engine.glc = (VDGLContext)SDL_GL_GetCurrentContext();
	VDEngine::bindOpenGLContext(engine.glc);


	/*	OpenGL information.	*/
	VDDebug::log("\nOpenGL settings.\n");
	VDDebug::log("GL_VENDOR: %s.\n", glGetString(GL_VENDOR));
	VDDebug::log("GL_RENDERER: %s.\n", glGetString(GL_RENDERER));
	VDDebug::log("GL_VERSION: %s. \n", glGetString(GL_VERSION));
	VDDebug::log("GL_SHADING: %s. \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	VDDebug::log("GL_EXTENSIONS:%s\n", glGetString(GL_EXTENSIONS));


	/*	Determine Compatibility	*/
	VDDebug::log("\nCaching compatibility.\n");
	engine.compadability = (VDSystemInfo::VDCompatibility*)malloc(sizeof(VDSystemInfo::VDCompatibility));
	VDSystemInfo::determineCompatibility(engine.compadability);


	/*	*/
	VDEngine::setWindowTitle(getGameEngineDefaultTitle());
	SDL_ShowWindow((SDL_Window*)VDEngine::getWindow());


	/*	Initialize GLEW.	*/
	if(VDSystemInfo::isOpenGLCoreProfile()){
		glewExperimental = SDL_TRUE;
		VDDebug::log("Enabling GLEW core \n");
	}
	VDDebug::log("Initialize GLEW library.\n");
	if((ret = glewInit()) != GLEW_OK){
		VDDebug::errorLog("Failed to initialize GLEW | error :%s.\n Application will be terminated.\n", glewGetErrorString(ret));
		VDApplication::quit(EXIT_FAILURE);
	}


	/*	Asset Manager	*/
	VDAssetManager::setRootDirectory(SDL_GetBasePath());
	VDDebug::log("Current Directory %s\n", VDAssetManager::getRootDirectory());


	/*	Create task scheduler.	*/
	// VDDebug::log("Creating TaskSchedule.\n");
	// engine.schedule = VDTaskSchedule();
	// engine.schedule.init(VDEngine::getConfig()->ntaskcores <= 0 ? VDSystemInfo::getCPUCoreCount() : VDEngine::getConfig()->ntaskcores);
	// VDRenderingAPICache::init(VDEngine::getTaskSchedule().getNumTaskPool());
	// VDRenderingAPICache::enable();
	// VDRenderPipeLine::queues.resize(VDEngine::getTaskSchedule().getNumTaskPool());
	// for(int x = 0; x < VDEngine::getTaskSchedule().getNumTaskPool(); x++){
	// 	VDRenderPipeLine::queues.push( VDQueue<VDRenderer*>(4096) );
	// }


	/*	Create engine scene.	*/
	VDDebug::log("Creating scene data struct.\n");
	engine.scene = new VDEngineScene();
	VDScene::init();

	/*	*/
	VDBufferObject::Target bufferTarget;
	if(VDSystemInfo::getCompatibility()->sShaderStorageBuffer){
		bufferTarget = VDBufferObject::eShaderStorage;
	}
	else{
		bufferTarget = VDBufferObject::eUniform;
	}

	/*	*/
	bufferTarget = VDBufferObject::eUniform;
	VDDebug::log("Number of allocated lights, %d.\n", VDSystemInfo::getCompatibility()->sMaxUniformBlockSize / sizeof(UniformLight));
	VDScene::getScene()->lightinfo.lightbuffer.setFlag(VDScene::getScene()->lightinfo.lightbuffer.getFlag() | VDObject::eStatic);
	VDScene::getScene()->lightinfo.lightbuffer.setTarget(bufferTarget);
	VDScene::getScene()->lightinfo.lightbuffer.setSize( VDSystemInfo::getCompatibility()->sMaxUniformBlockSize);
	VDScene::getScene()->lightinfo.lightbuffer.bindBase(VDShaderConstant::eLightning);

	/*	shadow buffer.	*/
	VDScene::getScene()->lightinfo.shadowbuffer.setFlag(VDScene::getScene()->lightinfo.shadowbuffer.getFlag() | VDObject::eStatic);
	VDScene::getScene()->lightinfo.shadowbuffer.setSize(16384);
	VDScene::getScene()->lightinfo.shadowbuffer.setTarget(bufferTarget);
	VDScene::getScene()->lightinfo.shadowbuffer.bindBase(VDShaderConstant::eShadow);

	/*	light indices.	*/
	VDScene::getScene()->lightinfo.lightIndices.setTarget(bufferTarget);
	VDScene::getScene()->lightinfo.lightIndices.setFlag(VDScene::getScene()->lightinfo.lightIndices.getFlag() | VDObject::eStatic);
	VDScene::getScene()->lightinfo.lightIndices.setSize(VDSystemInfo::getCompatibility()->sMaxUniformBlockSize);
	VDScene::getScene()->lightinfo.lightIndices.bindBase(VDShaderConstant::eLightIndices);

	/*	particle system.	*/
	VDRenderSetting::gRenderSettings.particlebuffer.setTarget(bufferTarget);
	VDRenderSetting::gRenderSettings.particlebuffer.setFlag(VDRenderSetting::gRenderSettings.particlebuffer.getFlag() | VDObject::eStatic);
	VDRenderSetting::gRenderSettings.particlebuffer.setSize(VDSystemInfo::getCompatibility()->sMaxUniformBlockSize);
	VDRenderSetting::gRenderSettings.particlebuffer.bindBase(VDShaderConstant::eParticle);

	/*	engine state	*/
	//engine.uniform.enginestate = VDUniformBuffer();
	VDScene::getScene()->uniform.enginestate.setFlag(VDScene::getScene()->uniform.enginestate.getFlag() | VDObject::eStatic);
	VDScene::getScene()->uniform.enginestate.setSize(sizeof(VDScene::getScene()->uniform.engineState));
	VDScene::getScene()->uniform.enginestate.bindBase(VDShaderConstant::eEngineState);

	/*	Rendering Settings	*/
	VDDebug::log("===Initializing Rendering settings===.\n\n");
	engine.renderSettings = VDRenderSetting(VDRenderSetting::eForwardRendering);

	/**/
	VDRenderSetting::useFog(false);
	VDRenderSetting::setFogType(VDRenderSetting::FogFlag::eFogLinear);
	VDRenderSetting::setFogColor(VDColor(0.3,0.3,0.3,1.0));
	VDRenderSetting::setFogDensity(0.4f);
	VDRenderSetting::setFogMaxDistance(1000.0f);
	VDRenderSetting::setFogMinDistance(100.0f);

	/**/
	VDRenderSetting::setAmbientColor(VDColor(0.3,0.3,0.3,1.0));
	VDRenderSetting::setAmbientType(VDRenderSetting::AmbientType::eConstant);
	VDRenderSetting::setAmbientIntensity(1.0f);

	/*	Quality settings	*/
	VDDebug::log("===Initializing Quality Settings.===\n\n");
	VDQualitySetting::useShadow(true);
	VDQualitySetting::setShadowDistance(75.0f);
	VDQualitySetting::setShadowFilter(VDQualitySetting::ShadowFilter::eSimple);
	VDQualitySetting::useAntaiAlising(false);
	VDQualitySetting::setSamplerMode(VDQualitySetting::SampleType::None);
	VDQualitySetting::setTextureLod(0);
	VDQualitySetting::setTextureAnisotropy(4.0f);
	VDQualitySetting::setColorSpace(VDQualitySetting::ColorSpace::eLinear);
	VDQualitySetting::setVSync(true);
	VDQualitySetting::setCulling(VDQualitySetting::Culling::eFrustum);


	/*	Determine which shader to load based on the OpenGL version.	*/
	/*	TODO make a location for all the shader.*/
	if(1){

		VDRenderSetting::gRenderSettings.lightShadowFirstPass = VDShaderCreator::ForwardFirstPassShadow();

		VDRenderSetting::gRenderSettings.toneMapping = VDShader::createShader("shader/PostProcessing/BasicPostV.glsl","shader/PostProcessing/tonemapping.glsl","","ToneMapping");

		/*	geometry shader supported.	*/
		if(VDSystemInfo::getCompatibility()->sGeometry){
			VDRenderSetting::gRenderSettings.lightShadowCubeMap = VDShaderCreator::CubeMapShadow();
			VDRenderSetting::gRenderSettings.reflectivecubemappass = VDShader::createShader("","","","Reflective");

		}
		else{	/*	Alternative solutions.	*/
			VDRenderSetting::gRenderSettings.lightShadowCubeMap = VDShaderCreator::CubeMapShadow();
			VDRenderSetting::gRenderSettings.reflectivecubemappass = VDShader::createShader("","","","Reflective");
		}
	}

	/*	default layer	*/
	VDLayer::setIndextName((unsigned int)(-1) & ~(1 << 31), "all");

	/*	Initialize matrix.	*/
	VDMatrix::init();


	/*	Initialize sub system.	*/
	VDDebug::log("=========Initializing subsystems.========\n\n");
	if(!VDEngine::initSubSystem((VDEngine::SubSystem)engine.flag)){
		VDDebug::errorLog("Failure in initialize sub system.\n");
	}


	/*	input	*/
	VDScreen::setCursorVisability(true);



	/*	rendering	*/

	/*	animation	*/


	/*	create default shader	*/
	gDefaulMaterial = VDMaterial::createDefaultMaterial(
		(engine.flag & VDEngine::eDefualtMaterialLowQuality) != 0 ? VDEngine::eDefualtMaterialLowQuality : VDEngine::eDefualtMaterialHighQuality);
	if(VDMaterial::getDefaultMaterial()->getShader()->isValid() == false){

	}

	/*	second phase of reading user arguments options.	*/
	if(VDEngine::readArgument(argc, argv, 0) == 2){
		VDApplication::quit(EXIT_SUCCESS);
	}

	/*	point sprite settings	*/
	if(VDSystemInfo::supportSpritePoint()){
		//glEnable(GL_POINT_SPRITE);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
		glPointParameterf(GL_POINT_FADE_THRESHOLD_SIZE, 1.0f);
	}
	else
		VDDebug::errorLog("Point sprite not supported.\n> Can results in artifacts for GUI and the spritebatch rendering\n");


	/*	initialize default value for stencil.	*/
	if(SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &glatt) > 0 ){
		VDRenderingAPICache::setState(GL_STENCIL_TEST, SDL_TRUE);
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
		glStencilMask(0xFF);
	}


	/*	Enable alpha test if framebuffer support it and was requested in the argument.	*/
	if(SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &glatt) > 0 ){
		VDRenderingAPICache::setState(GL_ALPHA_TEST, SDL_TRUE);
	}
	else{
		VDRenderingAPICache::setState(GL_ALPHA_TEST, SDL_FALSE);
	}

	/*	*/
	//ret |= engine.schedule.runTaskSch();

	return ret;
}

int VDEngine::initSubSystem(VDEngine::SubSystem subsystem){


	if(subsystem & VDEngine::Debug){
		engine.debug = new VDDebug();
		engine.debug->init();


		VDTexture2D* tex = VDTextureProcedure::genCheckerTexture2(1024, 1024, 64, 64, VDColor32::Black(), VDColor32::Gray(), VDTexture::eRGB, VDTexture::eRGB, VDTexture::eUnsignedByte, VDTexture::eMipMapping);
		void* data = tex->getPixelData(0, VDTexture::eRGB, VDTexture::eByte);
		/*	TODO create some debugging assets!	*/
		VDCubeMap* debugCubemap = new VDCubeMap();
		debugCubemap->setPixelData(0, 1024, 1024, 0, VDTexture::eRGB, VDTexture::eRGB, VDTexture::eByte, data);
		if(VDRenderSetting::getSkyBox() == NULL){
			VDSkyBox* sky = new VDSkyBox();
			sky->setCubeMap(debugCubemap);
			VDRenderSetting::setSkyBox(sky);
		}

		free(data);
		delete tex;


		/**/
		engine.log = VDFile::safeOpenWrite("log.txt");

		/**/
		//if(( engine.log = fdopen(fileno(stdout),"w+") ) == -1)
	    //   fprintf(stderr,"error");
		//*stdout = *engine.log;
		//setvbuf(fopen, NULL, _IONBF, 0 );
	}


	/*	Initialize physic engine.	*/
	if(subsystem & VDEngine::ePhysic){
		VDPhysic::initialize();
	}

	/*	Audio */
	if(subsystem & VDEngine::eAudio){
		VDAudio::init();
	}

	return subsystem;
}


int VDEngine::releaseSubSystem(SubSystem subsystem){

	int status = 1;

	/*	*/
	if(subsystem & VDEngine::Debug){
		if(VDEngine::getDebug()){
			VDEngine::getDebug()->release();
		}
	}

	/*	*/
	if( subsystem & VDEngine::ePhysic ){
		/*	Physic release.	*/
		VDPhysic::release();
	}

	if(subsystem & VDEngine::eAudio){
		VDAudio::release();
	}

	return status;
}

void VDEngine::releaseEngine(void){

	int i;
	int result = 1;

	/*	check if engine has been deinitialized	*/
	if(engine.active & VDENGINE_DEINIT){
		VDDebug::debugLog("");
		return;
	}


	/*	Terminate task sch	*/
	//result = VDEngine::getTaskSchedule().terminateTaskSch();


	/*	Release subsystem.	*/
	if(VDEngine::releaseSubSystem(VDEngine::getSubSystemFlag()) == 0x1){
		/*	*/
	}

	/*	OpenGL	*/
	for(i = 0; i < engine.glcontext.reserved(); i++ ){
		if(engine.glcontext[i] != NULL){
			SDL_GL_DeleteContext(engine.glcontext[i]);
		}
	}
	if(VDEngine::getOpenGLContext()){
		SDL_GL_DeleteContext(VDEngine::getOpenGLContext());
	}


	SDL_Quit();
}



int VDEngine::readArgument(int argc, const char** argv, unsigned int pre){
	int c;
	int optindex;
	int x;
	static struct option longoption[] = {
			{"version", 		no_argument,		0,	'v'},
			{"help", 			no_argument,		0,	'H'},
			{"fullscreen", 		no_argument,		0,	'f'},
			{"daemon", 			no_argument,		0,	'D'},
			{"vsync", 			no_argument,		0,	'j'},
			{"Verbose", 		no_argument,		0,	'V'},
			{"physic", 			no_argument,		0,	'P'},
			{"inotiy", 			optional_argument,	0,	'n'},
			{"debug", 			optional_argument,	0,	'd'},
			{"server",			optional_argument,	0,	's'},
			{"renderer", 		optional_argument,	0,	'r'},
			{"opengl", 			optional_argument,	0,	'g'},
			{"audio", 			optional_argument,	0,	'a'},
			{"emulate", 		optional_argument,	0,	'e'},
			{"alphachannel", 	optional_argument,	0,	'e'},
			{"client", 			required_argument,	0,	'c'},
			{"port", 			required_argument,	0,	'p'},
			{"host", 			required_argument,	0,	'h'},
			{"logging", 		required_argument,	0,	'l'},
			{"taskschedule", 	required_argument,	0,	't'},
			/*	Long options only.	*/

			{NULL, NULL, NULL, NULL}
	};

	/*	Get config network.	*/
	VDConfigure::VDConfig* config = VDEngine::getConfig();

	/*	print command line argument.	*/
	VDDebug::log("command line : ");
	for(x = 0; x < argc; x++){
		VDDebug::log("%s ", argv[x]);
	}
	VDDebug::log("\n");

	const char* shortarg = "DVvHsa:h:sp:x:l:t:d:g:r:nPh:fjr:";

	/**/
	if(pre){
		VDDebug::debugLog("Reading first console argument pass.\n");
		while((c = getopt_long(argc, (char *const *)argv, shortarg, longoption, &optindex)) != EOF){

			switch(c){
			case 'H':{
				printf("help:\n");
				return 2;
			}
			case 'v':{	/*	version.	*/
				unsigned int major, minor, revision;
				VDEngine::getBuildVersion(&major, &minor, &revision);
				VDDebug::log("version : %d.%d.%d\n", major, minor, revision);
				return 2;
			}
			case 'V':	/*	Verbose.	*/
				config->verbose = SDL_TRUE;
				break;
			case 'd':	/*	debug.	*/
				if(optarg){
					if(strcmp(optarg, "1") == 0 || strcmp(optarg, "true") == 0 || strlen(optarg) == 0){
						VDDebug::log("Argument for enable debugging.\n");
						int st;
						engine.flag |= VDEngine::Debug;
						SDL_GL_GetAttribute(SDL_GL_CONTEXT_FLAGS, &st);
						SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG | st);
					}
					else{
						VDDebug::log("Argument for disable debugging.\n");
						engine.flag = engine.flag & ~VDEngine::Debug;
					}
				}
				else{
					VDDebug::log("Argument for enable debugging.\n");
					engine.flag |= VDEngine::Debug;
					SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
				}
				break;
			case 'n':	/**/
				config->inotify = SDL_TRUE;
				break;
			case 'l':{
				if(optarg){
					engine.log = fopen(optarg, "wb");
					/**/
					//if(dup2(stdout,engine.log) == -1)
					//   fprintf(stderr,"error");
					/**/
					//if(dup2(stderr,engine.log) == -1)
					//    fprintf(stderr,"error");

					/**/

					/*  cause fork to fail somehow*/
					//*stdout = *engine.log;
					//setvbuf(engine.log, NULL, _IONBF, 0 );
				}
				}break;
			case 'P':	/*	Physic engine.	*/
					engine.flag |= VDEngine::ePhysic;
				break;
			case 't':{	/*	task schedule core count.	*/
				if(optarg){
					config->ntaskcores = atoi(optarg);
				}
			}
			break;
			case 'r':	/*	rendering profile mask.	*/
				/*	set opengl context attributes.	*/
				if(optarg){
					bool isDebug = VDDebug::isDebugEnabled();

					if(strcmp(optarg, "opengl") == 0){
						VDDebug::log("OpenGL compatibility.\n");
						SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG  | isDebug ? SDL_GL_CONTEXT_DEBUG_FLAG : 0);
						SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
					}
					else if(strcmp(optarg, "openglcore") == 0){
						VDDebug::log("OpenGL Core.\n");
						SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG  | isDebug ? SDL_GL_CONTEXT_DEBUG_FLAG : 0);
						SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
					}
					else if(strcmp(optarg, "opengles") == 0){
						VDDebug::log("OpenGL ES.\n");
						SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG  | isDebug ? SDL_GL_CONTEXT_DEBUG_FLAG : 0);
						SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
					}
					else{
						SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG  | isDebug ? SDL_GL_CONTEXT_DEBUG_FLAG : 0);
						SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
					}
				}
				break;
			case 'g':	/*	set opengl version.	*/

				if(optarg){
					SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, atoi(optarg) / 100);
					SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, ( atoi(optarg) % 100 ) / 10);
				}
				break;
			default:
				break;
			}

			argv[optind];

		}/**/
	}
	else{

		VDDebug::debugLog("Reading second console argument pass.\n");
		while((c = getopt_long(argc, (char *const *)argv, shortarg, longoption, &optindex)) != EOF){

			switch(c){
			case 'j':
				VDQualitySetting::setVSync(true);
				break;
			case 'r':
				break;
			case 'v':
				break;
			case 'a':
				break;
			case 'p':
				break;
			case 'f':{
				VDSize size = VDDisplay::getPrimaryScreenSize();
				VDScreen::setResolution(size.width(), size.height(), true);
			}break;
			default:
				break;
			}

		}/*	*/

	}/*	*/

	/*	reset opt	*/
	optarg = NULL;
	opterr = 0;
	optind = 0;

	return SDL_TRUE;
}


int VDEngine::run(void){
	int status = 1;
	SDL_Event event;

	/*	cached allocated chunk of data.	*/
	VDDoubleBufferedAllocator g_doubleFrameAllocator(1024 * 1024);

	/**/
	SDL_Window* drawable = SDL_GL_GetCurrentWindow();

	while(true){
		g_doubleFrameAllocator.swap();
		g_doubleFrameAllocator.clear();

		/*	system poll event	*/
		while(SDL_PollEvent(&event)){

			if(event.type == SDL_KEYUP){
				for(int x = 0; x < VDEvent::getNumEvents(); x++){
					VDEvent::getEvent(x)->onKeyRelease(event.key.keysym.sym);
				}
			}
			if(event.type == SDL_KEYDOWN){
				VDDebug::debugLog("Character : %c.\n", event.key.keysym.sym);
				/**/
				for(int x = 0; x < VDEvent::getNumEvents(); x++){
					VDEvent::getEvent(x)->onKeyPressed(event.key.keysym.sym);
				}

				/*	*/
				if(event.key.keysym.sym == SDLK_RETURN && ( event.key.keysym.mod & SDLK_LCTRL) ){
					VDScreen::setResolution(VDDisplay::getPrimaryScreenSize().width(), VDDisplay::getPrimaryScreenSize().height(), !VDScreen::isFullScreen());
				}

			}


			if(event.type == SDL_MOUSEBUTTONDOWN){
				for(int x = 0; x < VDEvent::getNumEvents(); x++){
					VDEvent::getEvent(x)->onMousePressed((VDInput::Button)event.button.button);
				}
			}

			if(event.type == SDL_MOUSEBUTTONUP){
				for(int x = 0; x < VDEvent::getNumEvents(); x++){
					VDEvent::getEvent(x)->onMouseReleased((VDInput::Button)event.button.button);
				}
			}

			if(event.type == SDL_MOUSEWHEEL){
				for(int x = 0; x < VDEvent::getNumEvents(); x++){
					VDEvent::getEvent(x)->onMouseWheel(event.wheel.y);
				}
			}

			if(event.type == SDL_MOUSEMOTION){
				VDDebug::debugLog(" %d, %d motion.\n", event.motion.x, event.motion.y);
				for(int x = 0; x < VDEvent::getNumEvents(); x++){
					VDEvent::getEvent(x)->onMouse(event.motion.x, event.motion.y, 0);
				}
			}

			if(event.type == SDL_WINDOWEVENT){
				switch(event.window.event){
				case SDL_WINDOWEVENT_EXPOSED:
					break;
				case SDL_WINDOWEVENT_RESIZED:
					VDRenderingAPICache::setViewport(0, 0,
							VDMath::max( event.window.data1,1),
							VDMath::max( event.window.data2, 1) );
					VDRenderSetting::setFrameBufferSize(event.window.data1, event.window.data2);
					for(int x = 0; x < VDEvent::getNumEvents(); x++){
						VDEvent::getEvent(x)->onResize(event.window.data1, event.window.data2);
					}
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:

					VDApplication::focus();
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					VDApplication::unFocus();
					break;
				default:
					break;
				}
			}

			if(event.type == SDL_QUIT){
				VDApplication::quit(EXIT_SUCCESS);
			}

		}


		/*	Update time ticks.	*/
		VDTime::internal_update();
		/*	Update input.	*/
		VDInput::internal_update();


		// /*	update routines.	*/
		// VDGameObject::internalGameObjectUpdate(&g_doubleFrameAllocator);
		// for(int x =0; x < engine.routines[VDEngine::SubRoutine::eUpdate].size(); x++ ){
		// 	VDTaskSchedule::VDTaskPackage pack = {0};
		// 	pack.callback = (VDTaskSchedule::VDTaskCallback)VDEngine::getCallBack(VDEngine::SubRoutine::eUpdate)[x];
		// 	VDEngine::getTaskSchedule().submitTask(&pack);
		// }

		// /*	Update fixed routines.	*/
		// VDGameObject::internalGameObjectFixedUpdate(&g_doubleFrameAllocator);
		// for(int x =0; x < engine.routines[VDEngine::SubRoutine::eFixedUpdate].size(); x++ ){
		// 	VDTaskSchedule::VDTaskPackage pack = {0};
		// 	pack.callback = (VDTaskSchedule::VDTaskCallback)VDEngine::getCallBack(VDEngine::SubRoutine::eFixedUpdate)[x];
		// 	VDEngine::getTaskSchedule().submitTask(&pack);
		// }

		/*	main render pipeline.	*/
		VDRenderPipeLine::render(&g_doubleFrameAllocator);

		/*	Update lights.	*/
		VDLight::updateLightUniformLocation(g_doubleFrameAllocator.getCurrentStack());

		/*	Swap to next framebuffer.	*/
		SDL_GL_SwapWindow(drawable);


		/*	Update physic simulation.	*/
		if(VDPhysic::isPhysicEnabled()){
			VDPhysic::simulation();
		}

		/*	*/
		if( VDEngine::getSubSystemFlag() & VDEngine::eAudio){
			VDAudioListener::updateAudioListener(&g_doubleFrameAllocator);
		}
	}

	return status;
}

unsigned int VDEngine::getFlag(void){
	return engine.flag;
}

VDEngine::SubSystem VDEngine::getSubSystemFlag(void){
	return (VDEngine::SubSystem) ( engine.flag & VDEngine::SubSystem::eAll );
}

VDWindow* VDEngine::getWindow(void){
	return engine.window;
}

VDWindow* VDEngine::getDrawable(void){
	return engine.drawable;
}

void VDEngine::setWindow(VDWindow* window){
	engine.window = window;
}
void VDEngine::setDrawable(VDWindow* window){
	engine.drawable = window;
}

void VDEngine::setWindowTitle(const char* title){
	SDL_SetWindowTitle((SDL_Window*)VDEngine::getWindow(), title);
}

void VDEngine::bindOpenGLContext(const SDL_GLContext glContext){
	SDL_GL_MakeCurrent(NULL, NULL);
	if(SDL_GL_MakeCurrent((SDL_Window*)VDEngine::getDrawable(), glContext) < 0){
		VDDebug::errorLog("Failed to bind OpengGL context.\n", SDL_GetError());
	}
}

SDL_GLContext VDEngine::getOpenGLContext(void){
	return engine.glc;
}

SDL_GLContext* VDEngine::querySharedOpenGLContext(void){
	SDL_GLContext* context  = engine.glcontext.obtain();

	//*context =  (VDOpenGLContext)ExCreateGLSharedContext(VDEngine::getDrawable(), VDEngine::getOpenGLContext());

	if(!(SDL_GLContext)*context){
		VDDebug::errorLog("Failed to create shared OpenGL Context.\n");
		VDEngine::returnOpenGLContext(context);
		return NULL;
	}
	return context;
}

void VDEngine::returnOpenGLContext(SDL_GLContext* context){
	if(*context){
		SDL_GL_DeleteContext(*context);
	}
	engine.glcontext.Return(context);
}

void VDEngine::setCallBack(SubRoutine enumCallBack, VDCustomCallBack callback){
	if(!callback){
		VDDebug::warningLog("Invalid callback.\n");
		return;
	}
	/*	Assign subroutine callback.	*/
	engine.routines[enumCallBack].push(callback);
}

void VDEngine::removeCallBack(SubRoutine enumCallBack, VDCallBack callback){
	engine.routines.at(enumCallBack);
	engine.routines.erase(enumCallBack);
}

VDVector<VDCustomCallBack>& VDEngine::getCallBack(SubRoutine enumCallBack){
	return engine.routines[enumCallBack];
}

// VDTaskSchedule& VDEngine::getTaskSchedule(void){
// 	return engine.schedule;
// }

VDDebug* VDEngine::getDebug(void){
	return engine.debug;
}

VDConfigure::VDConfig* VDEngine::getConfig(void){
	return engine.config;
}

unsigned int VDEngine::getBuildVersion(unsigned int* major, unsigned int* minor, unsigned int* revision){

	// if(major){
	// 	*major = MAJOR_VERSION;
	// }
	// if(minor){
	// 	*minor = MINOR_VERSION;
	// }
	// if(revision){
	// 	*revision = PATCH_VERSION;
	// }

	// return ( MAJOR_VERSION * 100 + MINOR_VERSION * 10 + PATCH_VERSION );
}

#define VD_ENGINE_DEFAULT_TITLE VD_TEXT("%s | VDEngine Version %s")
#define VD_COMPILER_VERSION(major, minor, revision) VD_STR(major)VD_TEXT(".")VD_STR(minor)VD_TEXT(".")VD_STR(revision)
const char* VDEngine::getVersion(void){
	return VD_COMPILER_VERSION(MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION);
}


char* getGameEngineDefaultTitle(void){
	static char text[512] = {0};
	char app[PATH_MAX];

	sprintf(text,VD_ENGINE_DEFAULT_TITLE,
			VDSystemInfo::getAppliationName(),
			VDEngine::getVersion());
	return text;
}
