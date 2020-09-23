#include <Core/VDDebug.h>
#include <Core/VDEngineCore.h>
#include <SDL2/SDL_video.h>

void __attribute__ ((constructor)) my_load(void){

	/*	OpenGL set attributes*/

	//XInitThreads();
	/*
	if(ExIsExtensionSupported(glXGetClientString((Display*)display, GLX_EXTENSIONS), "GLX_ARB_multisample")){
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
	}
	else{
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
	}
	*/

	/*	*/
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 	8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 	8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 	8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 	0);

	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE, 		0);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE, 	0);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE, 	0);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, 	0);


	/*
	if(ExIsExtensionSupported(glXGetClientString((Display*)display,GLX_EXTENSIONS), "GLX_EXT_framebuffer_sRGB") ||
			ExIsExtensionSupported(glXGetClientString((Display*)display,GLX_EXTENSIONS), "GLX_ARB_framebuffer_sRGB") ){
		SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, SDL_TRUE);
	}
	else{
		SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, SDL_FALSE);
	}
	*/
	//SDL_GL_SetAttribute(EX_OPENGL_ACCELERATED_VISUAL,0);
	SDL_GL_SetAttribute(SDL_GL_STEREO,	0);





	/*	context	version	*/
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


	/*	*/
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 0);


	/*	set OpenGL context flag to debug for debug build.	*/
	if(VDDebug::isDebugBuild()){
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG );
	}
	else{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0 );	/*EX_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG fix*/
	}

	/*	engine requires 3.0 version of OpenGL to run properly	*/
	//if(ExGetOpenGLVersion(NULL,NULL) < 330){
	//	SDL_GL_SetAttribute(EX_OPENGL_CONTEXT_PROFILE_MASK, EX_GL_CONTEXT_PROFILE_COMPATIBILITY);
	//	SDL_GL_SetAttribute(EX_OPENGL_CONTEXT_FLAGS, EX_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

	//		/*	*/
	//	SDL_GL_SetAttribute(EX_OPENGL_MAJOR_VERSION,3);
	//	SDL_GL_SetAttribute(EX_OPENGL_MINOR_VERSION,3);
	//}

	engine.log = stdout;
}
