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
#ifndef _VD_SHADER_CREATOR_H_
#define _VD_SHADER_CREATOR_H_ 1
#include"../Asset/VDAssetManager.h"
#include"../VDDef.h"

/**
 *	Responsible for creating built in
 *	shaders.
 */
class VDDECLSPEC VDShaderCreator {
public:

	/**
	 *	Debug Purposes.
	 *
	 *	@Return
	 */
	static VDShader* VDAPIENTRY ComponentOutPut(unsigned int componet);
	static VDShader* VDAPIENTRY ComponentGeometryOutPut(unsigned int componet);

	/**
	 *	Legacy shader. High compatibility.
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIENTRY SingleColorShader();
	static VDShader* VDAPIENTRY VertexColor();
	static VDShader* VDAPIENTRY VertexLit();
	static VDShader* VDAPIENTRY Unlit();

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY Diffuse();
	static VDShader* VDAPIFASTENTRY NormalDiffuse();
	static VDShader* VDAPIFASTENTRY Specular();
	static VDShader* VDAPIFASTENTRY SpecularNormal();
	static VDShader* VDAPIFASTENTRY SpecularMapped();
	static VDShader* VDAPIFASTENTRY SpecularNormalMapped();

	/**
	 *	Create parallax diffuse.
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY ParallaxDiffuse();
	static VDShader* VDAPIFASTENTRY ParallaxNormal();
	static VDShader* VDAPIFASTENTRY ParallaxNormalSpecular();
	static VDShader* VDAPIFASTENTRY ParallaxSpecular();
	static VDShader* VDAPIFASTENTRY ParallaxSpecularMapped();

	/**
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY RefractionDiffuse();
	static VDShader* VDAPIFASTENTRY RefractionNormal();
	static VDShader* VDAPIFASTENTRY RefractionSpecular();
	static VDShader* VDAPIFASTENTRY RefractionNormalSpecular();
	static VDShader* VDAPIFASTENTRY RefractionMapped();

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY ReflectiveDiffuse();
	static VDShader* VDAPIFASTENTRY ReflectiveNormal();
	static VDShader* VDAPIFASTENTRY ReflectiveSpecular();
	static VDShader* VDAPIFASTENTRY ReflectiveNormalSpecular();
	static VDShader* VDAPIFASTENTRY ReflectiveMapped();

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY TranslucentDiffuse();
	static VDShader* VDAPIFASTENTRY TranslucentSpecular();
	static VDShader* VDAPIFASTENTRY TranslucentSpecularMapped();
	static VDShader* VDAPIFASTENTRY TranslucentNormal();
	static VDShader* VDAPIFASTENTRY TranslucentSpecularNormal();

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY IllusionDiffuse();
	static VDShader* VDAPIFASTENTRY IllusionNormal();
	static VDShader* VDAPIFASTENTRY IllusionSpecular();
	static VDShader* VDAPIFASTENTRY IllusionNormalSpecular();
	static VDShader* VDAPIFASTENTRY IllusionReflective();

	static VDShader* VDAPIFASTENTRY PostOutShader();

	/**
	 *	create Skybox shader.
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY SkyBox();

	/**
	 *	Billboarding
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY SimpleBillboard();
	static VDShader* VDAPIFASTENTRY Billboard();

	/**
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY LightScattering();

	/**
	 *	Create approximated sub scattering surface.
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY Subsurface();
	static VDShader* VDAPIFASTENTRY SubsurfaceNormal();
	static VDShader* VDAPIFASTENTRY SubsurfaceSpecular();
	static VDShader* VDAPIFASTENTRY SubsurfaceNormalSpecular();
	static VDShader* VDAPIFASTENTRY SubsurfaceMapped();

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY ChromaticReflectiv();

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY ForwardFirstPassShadow();
	static VDShader* VDAPIFASTENTRY CubeMapShadow();

	/**
	 *
	 */
	static VDShader* createPostProcessingShader(const char* cVertexShader,
			const char* cFragmentShader, const char* cGeometryShader);

	/**
	 *	Get absolute path.
	 *	@Return
	 */
	static inline std::string getAbsolutePath(const char* relative) {
#ifdef _DEBUG
		return (VDAssetManager::getResourcePath(VDAssetManager::eShaderPath)
				+ "/" + relative);
#else
		return (VDAssetManager::getResourcePath(VDAssetManager::eShaderPath)
				+ "/" + relative + ".gz");
#endif
	}

	/**
	 *	Load shader string.
	 */
	static long int loadShaderString(const char* __restrict__ cfilename, void** __restrict__ data);

	/*
	 *	@Return
	 */
	static long int loadBuiltInShaderSource(const char* __restrict__ cfilename, void** __restrict__ pbuffer);

};

#endif
