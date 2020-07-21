#include <Core/VDEngineCore.h>
#include <GL/glew.h>
#include <SDL2/SDL_cpuinfo.h>
#include <SDL2/SDL_platform.h>
#include <SDL2/SDL_video.h>
#include <VDSystemInfo.h>
#include <cstdlib>
#include <cstring>


VDSystemInfo::OperatingSystem VDSystemInfo::operatingSystem(void){

	const char* os = SDL_GetPlatform();

	if(strcmp(os, "Linux") == 0){
		return VDSystemInfo::eLinux;
	}
	if(strcmp(os, "Window") == 0){
		return VDSystemInfo::eWindow;
	}
	if(strcmp(os, "Android") == 0){
		return VDSystemInfo::eAndroid;
	}
	if(strcmp(os, "unix") == 0){
		return VDSystemInfo::eUnix;
	}

	return VDSystemInfo::eUnknown;
}

const char* VDSystemInfo::getAppliationName(void){
#   if defined(VD_GNUC) || defined(VD_UNIX)
	extern char* __progname;
	return __progname;
#else
	return NULL;
#endif
}

unsigned int VDSystemInfo::getPageSize(void){
	return 1024;
}

unsigned int VDSystemInfo::getCPUCoreCount(void){
	return SDL_GetCPUCount();
}


bool VDSystemInfo::supportsVibration(void){
	return false;
}


unsigned long int VDSystemInfo::systemMemorySize(void){

	return SDL_GetSystemRAM();
}




bool VDSystemInfo::supportRenderTargetCount(void){
	if(VDSystemInfo::supportFrameBuffer()){
		int num;
		glGetIntegerv(GL_MAX_DRAW_BUFFERS, &num);
		return num >= 4;
	}
	return false;
}

bool VDSystemInfo::supportFrameBuffer(void){
	return ( SDL_GL_ExtensionSupported("GL_ARB_framebuffer_object") || SDL_GL_ExtensionSupported("EXT_framebuffer_object") ) != 0 ? true : false;
}

bool VDSystemInfo::supportFrameBufferMultiSample(void){
	return ( SDL_GL_ExtensionSupported("EXT_framebuffer_multisample") | SDL_GL_ExtensionSupported("EXT_framebuffer_object") ) != 0 ? true : false;

}

bool VDSystemInfo::supportsImageEffects(void){
	return VDSystemInfo::supportFrameBuffer();
}

bool VDSystemInfo::supportsInstancing(void){
	return (SDL_GL_ExtensionSupported("GL_ARB_draw_instanced") | SDL_GL_ExtensionSupported("GL_EXT_draw_instanced") )!= 0 ? true : false;
}

bool VDSystemInfo::supportsRenderTextures(void){
	return SDL_GL_ExtensionSupported("GL_ARB_framebuffer_object");
}

bool VDSystemInfo::supportsRenderToCubemap(void){
	int support;
	glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &support);
	return support >= 16;
}

bool VDSystemInfo::supportCubeMap(void){
	return SDL_GL_ExtensionSupported("GL_ARB_texture_cube_map") || SDL_GL_ExtensionSupported("GL_EXT_texture_cube_map");
}

bool VDSystemInfo::supportSeamLessCubeMap(void){
	return SDL_GL_ExtensionSupported("GL_ARB_seamless_cube_map,");
}

bool VDSystemInfo::supportCubeMapArray(void){
	return SDL_GL_ExtensionSupported("ARB_texture_cube_map_array");
}

bool VDSystemInfo::supportLayerFragment(void){
	return SDL_GL_ExtensionSupported("GL_ARB_fragment_layer_viewport");
}

bool VDSystemInfo::supportShaderImageLoadStorage(void){
	return SDL_GL_ExtensionSupported("GL_EXT_shader_image_load_store") || SDL_GL_ExtensionSupported("GL_ARB_shader_image_load_store");
}

bool VDSystemInfo::supportQueryOcclusion(void){
	return SDL_GL_ExtensionSupported("GL_ARB_occlusion_query") | SDL_GL_ExtensionSupported("GL_NV_occlusion_query");
}

bool VDSystemInfo::supportsShadows(void){
	return supportFrameBuffer() || SDL_GL_ExtensionSupported("GL_ARB_fragment_program_shadow") || SDL_GL_ExtensionSupported("");
}

bool VDSystemInfo::supportSpritePoint(void){
	return SDL_GL_ExtensionSupported("GL_ARB_point_sprite") || SDL_GL_ExtensionSupported("GL_NV_point_sprite");
}

bool VDSystemInfo::supportsSparseTextures(void){
	return SDL_GL_ExtensionSupported("ARB_sparse_texture");
}

bool VDSystemInfo::supportsStencil(void){
	return SDL_GL_ExtensionSupported("GL_ARB_stencil_texturing");
}

bool VDSystemInfo::supportDepthStencil(void){
	return SDL_GL_ExtensionSupported("GL_EXT_packed_depth_stencil") || SDL_GL_ExtensionSupported("GL_NV_packed_depth_stencil");
}

bool VDSystemInfo::supportMSAA(void){
	return SDL_GL_ExtensionSupported("GL_ARB_multisample") ||
			SDL_GL_ExtensionSupported("GL_EXT_multisample") ||
			SDL_GL_ExtensionSupported("WGL_EXT_multisample") ||
			SDL_GL_ExtensionSupported("GLX_ARB_multisample") ||
			SDL_GL_ExtensionSupported("WGL_ARB_multisample");
}

int VDSystemInfo::numMSAASampling(void){
	int size;
	glGetIntegerv(GL_MAX_INTEGER_SAMPLES, &size);
	return size;
}

bool VDSystemInfo::supportShaderSubRoutine(void){
	return SDL_GL_ExtensionSupported("GL_ARB_shader_subroutine");
}

bool VDSystemInfo::supportGeomtry(void){
	return SDL_GL_ExtensionSupported("GL_ARB_geometry_shader4") || SDL_GL_ExtensionSupported("GL_EXT_geometry_shader4") || SDL_GL_ExtensionSupported("GL_NV_geometry_shader4");
}

bool VDSystemInfo::supportTessellation(void){
	return SDL_GL_ExtensionSupported("GL_ARB_tessellation_shader") || SDL_GL_ExtensionSupported("GL_NV_tessellation_program5");
}

bool VDSystemInfo::supportVertexArrayObject(void){
	return SDL_GL_ExtensionSupported("GL_ARB_vertex_array_object");
}

bool VDSystemInfo::supportTransformFeedBack(void){
	return  SDL_GL_ExtensionSupported("GL_ARB_transform_feedback2") || SDL_GL_ExtensionSupported("GL_NV_transform_feedback2") ||
			SDL_GL_ExtensionSupported("GL_NV_transform_feedback") || SDL_GL_ExtensionSupported("EXT_transform_feedback") ||
			SDL_GL_ExtensionSupported("GL_ARB_transform_feedback3");
}

bool VDSystemInfo::SupportsRenderTextureFormat(VDTexture::TextureFormat format){

	//glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, &sformat);
	return true;
}

bool VDSystemInfo::SupportsTextureFormat(VDTexture::TextureFormat format){
	int sformat[1024];

	//glGetIntegerv(GL_COMPRESSED_TEXTURE_FORMATS, &sformat);
	return false;
}

bool VDSystemInfo::supportTextureCompression(void){
	return 	SDL_GL_ExtensionSupported("GL_ARB_texture_compression") ||
			SDL_GL_ExtensionSupported("GL_ARB_texture_compression_bptc") ||
			SDL_GL_ExtensionSupported("GL_ARB_texture_compression_rgtc") ||
			SDL_GL_ExtensionSupported("GL_EXT_texture_compression_dxt1") ||
			SDL_GL_ExtensionSupported("GL_EXT_texture_compression_latc") ||
			SDL_GL_ExtensionSupported("GL_EXT_texture_compression_rgtc") ||
			SDL_GL_ExtensionSupported("GL_EXT_texture_compression_s3tc") ||
			SDL_GL_ExtensionSupported("GL_NV_texture_compression_vtc");
}


bool VDSystemInfo::supportTextureCompression(VDTexture::CompressionFormat compressionType){
	switch(compressionType){
	case VDTexture::eDefault:
		return supportTextureCompression();
	case VDTexture::eBPTC:
		return SDL_GL_ExtensionSupported("GL_ARB_texture_compression_bptc") || SDL_GL_ExtensionSupported("GL_EXT_texture_compression_rgtc");
	case VDTexture::eDXT1:
		return SDL_GL_ExtensionSupported("GL_EXT_texture_compression_dxt1");
	case VDTexture::eLATC:
		return false;
		break;
	default:
		return false;
	}
}

bool VDSystemInfo::supportBufferBase(void){
	return glBindBufferBase != NULL;
}

bool VDSystemInfo::supportMultiBind(void){
	return SDL_GL_ExtensionSupported("GL_ARB_multi_bind") != 0 ? true : false;
}

bool VDSystemInfo::supportShaderStorageBuffer(void){

	return SDL_GL_ExtensionSupported("GL_ARB_shader_storage_buffer_object") || SDL_GL_ExtensionSupported("GL_NV_shader_storage_buffer_object");
}

unsigned int VDSystemInfo::openglVersion(void){

	unsigned int version;
	char glstring[128] = {0};
	char* wspac;

	/*	Extract version number.	*/
	strcpy(glstring, (const char*)glGetString(GL_VERSION));
	wspac = strstr(glstring, " ");
	if(wspac){
		*wspac = '\0';
	}
	version = strtof(glstring, NULL) * 100;

	return version;
}

unsigned int VDSystemInfo::openglshadingVersion(void){

	unsigned int version;
	char glstring[128] = {0};
	char* wspac;

	/*	Extract version number.	*/
	strcpy(glstring, (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION));
	wspac = strstr(glstring, " ");
	if(wspac){
		*wspac = '\0';
	}
	version = strtof(glstring, NULL) * 100;

	return version;
}

bool VDSystemInfo::isOpenGLCoreProfile(void){
	int value;
	glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &value);
	return ( value == SDL_GL_CONTEXT_PROFILE_CORE );
}

bool VDSystemInfo::isOpenGLCompatibility(void){
	int value;
	glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &value);
	return ( value == SDL_GL_CONTEXT_PROFILE_COMPATIBILITY );
}

void VDSystemInfo::determineCompatibility(VDCompatibility* compatibility){
	/**/
	compatibility->sBufferBase = VDSystemInfo::supportBufferBase();
	compatibility->sDepthStencil = VDSystemInfo::supportDepthStencil();
	compatibility->sFramebuffer = VDSystemInfo::supportFrameBuffer();
	compatibility->sFrameBufferMSSA = VDSystemInfo::supportFrameBufferMultiSample();
	compatibility->sNonAttachableFrameBuffer = false;
	compatibility->sMSAA = VDSystemInfo::supportMSAA();
	compatibility->sCubeMap = VDSystemInfo::supportCubeMap();
	compatibility->sCubeMapArray = VDSystemInfo::supportCubeMapArray();
	compatibility->sMultiBind = VDSystemInfo::supportMultiBind();
	compatibility->sQueryOcclusion = VDSystemInfo::supportQueryOcclusion();
	compatibility->sRenderTarget = VDSystemInfo::supportsRenderTextures();
	compatibility->sShaderImageLoadStorage = VDSystemInfo::supportShaderImageLoadStorage();
	compatibility->sShaderStorageBuffer = VDSystemInfo::supportShaderStorageBuffer();
	compatibility->sImageEffect = VDSystemInfo::supportsImageEffects();

	/**/
	compatibility->sShadow = VDSystemInfo::supportsShadows();
	compatibility->sGeometry = VDSystemInfo::supportGeomtry();
	compatibility->sSubRoutine = VDSystemInfo::supportShaderSubRoutine();
	compatibility->sVertexArrayObject = VDSystemInfo::supportVertexArrayObject();
	compatibility->sTransformFeedback = VDSystemInfo::supportTransformFeedBack();
	compatibility->sTessellation = VDSystemInfo::supportTessellation();
	compatibility->sTextureCompression = VDSystemInfo::supportTextureCompression();

	/**/
	compatibility->glslVersion = VDSystemInfo::openglshadingVersion();
	compatibility->glslVersion = VDSystemInfo::openglVersion();/*	TODO resolve,*/
	compatibility->isGLCore	= VDSystemInfo::isOpenGLCoreProfile();

	compatibility->sCSAA = SDL_GL_ExtensionSupported("GL_NV_framebuffer_multisample_coverage");



	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &compatibility->sMaxElementVertices);
	glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &compatibility->sMaxElementIndices);


	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &compatibility->sMaxTextureSize);

	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &compatibility->sMaxAnsio);


	glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &compatibility->sMaxVertexAttributes);
	/**/
	//glGetIntegerv(GL_FRAME)

	/*	TODO resolve*/

	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &compatibility->sMaxTextureUnitActive);			/*	GL_MAX_TEXTURE_IMAGE_UNITS	*/
	glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &compatibility->numMaxSubRoutines);				/*	*/

	glGetIntegerv(GL_MAX_DRAW_BUFFERS, &compatibility->sMaxDrawBuffers);
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &compatibility->sMaxColorAttachments);
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &compatibility->sMaxFrameBufferAttachment);		/*	*/

	/*	Uniform buffer max.	*/
	glGetIntegerv(GL_MAX_UNIFORM_BUFFER_BINDINGS, &compatibility->sMaxUniformBufferBinding);
	glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &compatibility->sMaxUniformBlockSize);
	glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, &compatibility->sMaxUniformLocations);


	compatibility->sDeferredRendering = VDSystemInfo::supportRenderTargetCount();
	compatibility->sDSR = VDSystemInfo::supportFrameBuffer();
	compatibility->sHDR = VDSystemInfo::supportFrameBuffer();

}

VDSystemInfo::VDCompatibility* VDSystemInfo::getCompatibility(void){
	return engine.compadability;
}
