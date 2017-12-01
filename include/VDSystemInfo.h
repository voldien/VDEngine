/*
    VDEngine virtual dimension game engine.
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VD_SYSTEM_INFO_H_
#define _VD_SYSTEM_INFO_H_ 1
#include"Rendering/Texture/VDTexture.h"
#include"VDDef.h"

/**
 *	Responsible for providing information
 *	about the current system.
 */
class VDDECLSPEC VDSystemInfo{
public:
	enum OperatingSystem{
		eUnix		= 0x1,					/*	*/
		eLinux 		= ( 0x2 | eUnix ),		/*	*/
		eWindow 	= 0x4,					/*	*/
		eFreeBSD 	= ( 0x8 | eUnix) ,		/*	*/
		eMac 		= (0x10 | eUnix ) ,		/*	*/
		eAndroid 	= 0x20,					/*	*/
		eIOS		= 0x40,					/*	*/

		eUnknown = (1 << 31)
	};

	/**
	 *	 Operating system name with version (Read Only).
	 */
	static OperatingSystem VDAPIENTRY operatingSystem(void);

	/**
	 *	Get application name.
	 */
	static const char* getAppliationName(void);

	/**
	 *	Get page size on the system.
	 */
	static unsigned int getPageSize(void);

	/**
	 *	Get number of cpu cores available on the system.
	 */
	static unsigned int getCPUCoreCount(void);

	/**
	 *	Is the device capable of providing the user haptic feedback by vibration
	 *
	 *	@Return true if supported, false otherwise.
	 */
	static bool VDAPIENTRY supportsVibration(void);

	/**
	 *	Get system total memory size in bytes.
	 */
	static unsigned long int VDAPIENTRY systemMemorySize(void);

	/**
	 *	Get number of render target supported
	 *	the systems OpenGL drivers.
	 */
	static bool VDAPIENTRY supportRenderTargetCount(void);

	/**
	 *	Check if framebuffer object is supported.
	 *	@Return true if supported, false otherwise.
	 */
	static bool VDAPIENTRY supportFrameBuffer(void);

	/**
	 *	Check if framebuffer object with
	 *	multi sample is supported.
	 *	@Return true if suported, false otherwise.
	 */
	static bool VDAPIENTRY supportFrameBufferMultiSample(void);

	/**
	 *	Check if Images effects is supported.
	 */
	static bool VDAPIENTRY supportsImageEffects(void);

	/*
	 *	Is GPU draw call instancing supported? (Read Only).
	 *	@Return true if supported, false otherwise.
	 */
	static bool VDAPIENTRY supportsInstancing(void);

	/*
	 *	Are render textures supported? (Read Only)
	 *	@Return
	 */
	static bool VDAPIENTRY supportsRenderTextures(void);

	/**
	 *	Get max texture resolutaion supported on
	 *	the OpenGL drivers.
	 */
	static int VDAPIENTRY maxTextureSize(void);

	/*
	 *	Are cubemap render textures supported? (Read Only)
	 *	@return
	 */
	static bool VDAPIENTRY supportsRenderToCubemap(void);

	/**
	 *	Support cubemap texture.
	 */
	static bool VDAPIENTRY supportCubeMap(void);

	/**
	 *	Support cubemap with seamless.
	 */
	static bool VDAPIENTRY supportSeamLessCubeMap(void);

	/**
	 *	Support cube texture array for containing
	 *	arrays of cubemaps.
	 */
	static bool VDAPIENTRY supportCubeMapArray(void);

	/**
	 *	Support multi viewport rendering
	 *	with fragment shader.
	 */
	static bool VDAPIENTRY supportLayerFragment(void);

	/**
	 *	Support shader image storage.
	 */
	static bool VDAPIENTRY supportShaderImageLoadStorage(void);

	/**
	 *	Check if query occlusion is supported.
	 */
	static bool VDAPIENTRY supportQueryOcclusion(void);

	/**
	 *	Are built-in shadows supported? (Read Only)
	 */
	static bool VDAPIENTRY supportsShadows(void);

	/**
	 *	Check if sprite point is supported.
	 */
	static bool VDAPIENTRY supportSpritePoint(void);

	/**
	 *	Are sparse textures supported? (Read Only)
	 */
	static bool VDAPIENTRY supportsSparseTextures(void);

	/**
	 *	Is the stencil buffer supported? (Read Only)
	 */
	static bool VDAPIENTRY supportsStencil(void);

	/**
	 *	Check if depth-stencil i supported.
	 */
	static bool VDAPIENTRY supportDepthStencil(void);

	/**
	 *	Multisample anti aliasing.
	 */
	static bool VDAPIENTRY supportMSAA(void);

	/**
	 *	Get number of multisample.
	 */
	static int VDAPIENTRY numMSAASampling(void);

	/**
	 *	Check if shader subroutine is supported
	 *	in shaders.
	 */
	static bool VDAPIENTRY supportShaderSubRoutine(void);

	/*
	 *	Support geometry shaders.
	 */
	static bool VDAPIENTRY supportGeomtry(void);

	/*
	 *	Support Tessellation shaders.
	 */
	static bool VDAPIENTRY supportTessellation(void);

	/**
	 *	Support vertex array object for rendering objects.
	 */
	static bool VDAPIENTRY supportVertexArrayObject(void);

	/**
	 *	Supports transform feedback.
	 */
	static bool VDAPIENTRY supportTransformFeedBack(void);

	/**
	 *	Is render texture format supported. (Read only)
	 */
	static bool VDAPIENTRY SupportsRenderTextureFormat(VDTexture::TextureFormat format);

	/**
	 *	Is render texture format supported. (Read only)
	 */
	static bool VDAPIENTRY SupportsTextureFormat(VDTexture::TextureFormat format);

	/**
	 *	Check if any texture compression is supported.
	 */
	static bool VDAPIENTRY supportTextureCompression(void);

	/**
	 *	Check if specified texture compression is supported. (Read only)
	 */
	static bool VDAPIENTRY supportTextureCompression(VDTexture::CompressionFormat compressionType);

	/**
	 *	Support for binding buffer to base.
	 */
	static bool VDAPIENTRY supportBufferBase(void);

	/**
	 *	Check if shader storage buffer is supported.
	 */
	static bool VDAPIENTRY supportShaderStorageBuffer(void);

	/**
	 *	Support multiple texture bind.
	 */
	static bool VDAPIENTRY supportMultiBind(void);

	/**
	 *	Get OpenGL version in decimal format.
	 */
	static unsigned int VDAPIENTRY openglVersion(void);

	/**
	 * Get OpenGl version in decimal format.
	 */
	static unsigned int VDAPIENTRY openglshadingVersion(void);

	/**
	 *	@Return true if current binded opengl context is a core profile context.
	 */
	static bool VDAPIENTRY isOpenGLCoreProfile(void);

	/**
	 * Check if OpenGL is in compatibility mode.
	 */
	static bool VDAPIENTRY isOpenGLCompatibility(void);

	/**
	 *
	 */
	typedef struct vd_compatibility_t{
		bool sBufferBase;
		bool sDepthStencil;
		bool sFramebuffer;
		bool sFrameBufferMSSA;
		bool sNonAttachableFrameBuffer;
		bool sMSAA;
		bool sCSAA;
		bool sCubeMap;
		bool sCubeMapArray;
		bool sMultiBind;				/*	Support multi bind texture.	*/
		bool sQueryOcclusion;
		bool sRenderTarget;
		bool sShaderImageLoadStorage;
		bool sShaderStorageBuffer;
		bool sImageEffect;
		bool sInstancing;
		bool sSpritePoint;
		bool sRenderTargetCubeMap;
		bool sShadow;
		bool sGeometry;
		bool sSubRoutine;
		bool sVertexArrayObject;
		bool sTransformFeedback;
		bool sTessellation;
		bool sTextureCompression;
		unsigned int glslVersion;
		unsigned int glVersion;
		bool isGLCore;
		bool sDeferredRendering;
		bool sDSR;
		bool sHDR;
		bool sSRGB;

		/*	info	*/
		unsigned int maxComputeShaderStorageBlocks;
		unsigned int maxCombinedShaderStorageBlocks;

		/*	*/
		int sMaxElementVertices;
		int sMaxElementIndices;
		int sMaxVertexAttributes;

		/*	*/
		int sMaxTextureSize;
		int sMaxAnsio;

		/*	*/
		int sMaxFrameBufferAttachment;		/**/
		int sMaxTextureUnitActive;			/**/
		int numMaxSubRoutines;				/**/

		/*	*/
		int sMaxDrawBuffers;			/*	GL_MAX_DRAW_BUFFERS	*/
		int sMaxColorAttachments;		/*	GL_MAX_COLOR_ATTACHMENTS	*/

		/*	*/
		int sMaxUniformBufferBinding;	/*		GL_MAX_UNIFORM_BUFFER_BINDINGS	*/
		int sMaxUniformBlockSize;		/*		GL_MAX_UNIFORM_BLOCK_SIZE	*/
		int sMaxUniformLocations;		/*		GL_MAX_UNIFORM_LOCATIONS	*/

	}VDCompatibility;

	/**
	 *	Query system capabilities.
	 */
	static void VDAPIENTRY determineCompatibility(VDCompatibility* compatibility);

	/**
	 *	Get cached compatibility of the system.
	 *	@Return non null.
	 */
	static VDCompatibility* VDAPIENTRY getCompatibility(void);
};

#endif
