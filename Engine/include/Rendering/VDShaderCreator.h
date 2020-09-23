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
	static VDShader* VDAPIENTRY SingleColorShader(void);
	static VDShader* VDAPIENTRY VertexColor(void);
	static VDShader* VDAPIENTRY VertexLit(void);
	static VDShader* VDAPIENTRY Unlit(void);

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY Diffuse(void);
	static VDShader* VDAPIFASTENTRY NormalDiffuse(void);
	static VDShader* VDAPIFASTENTRY Specular(void);
	static VDShader* VDAPIFASTENTRY SpecularNormal(void);
	static VDShader* VDAPIFASTENTRY SpecularMapped(void);
	static VDShader* VDAPIFASTENTRY SpecularNormalMapped(void);

	/**
	 *	Create parallax diffuse.
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY ParallaxDiffuse(void);
	static VDShader* VDAPIFASTENTRY ParallaxNormal(void);
	static VDShader* VDAPIFASTENTRY ParallaxNormalSpecular(void);
	static VDShader* VDAPIFASTENTRY ParallaxSpecular(void);
	static VDShader* VDAPIFASTENTRY ParallaxSpecularMapped(void);

	/**
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY RefractionDiffuse(void);
	static VDShader* VDAPIFASTENTRY RefractionNormal(void);
	static VDShader* VDAPIFASTENTRY RefractionSpecular(void);
	static VDShader* VDAPIFASTENTRY RefractionNormalSpecular(void);
	static VDShader* VDAPIFASTENTRY RefractionMapped(void);

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY ReflectiveDiffuse(void);
	static VDShader* VDAPIFASTENTRY ReflectiveNormal(void);
	static VDShader* VDAPIFASTENTRY ReflectiveSpecular(void);
	static VDShader* VDAPIFASTENTRY ReflectiveNormalSpecular(void);
	static VDShader* VDAPIFASTENTRY ReflectiveMapped(void);

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY TranslucentDiffuse(void);
	static VDShader* VDAPIFASTENTRY TranslucentSpecular(void);
	static VDShader* VDAPIFASTENTRY TranslucentSpecularMapped(void);
	static VDShader* VDAPIFASTENTRY TranslucentNormal(void);
	static VDShader* VDAPIFASTENTRY TranslucentSpecularNormal(void);

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY IllusionDiffuse(void);
	static VDShader* VDAPIFASTENTRY IllusionNormal(void);
	static VDShader* VDAPIFASTENTRY IllusionSpecular(void);
	static VDShader* VDAPIFASTENTRY IllusionNormalSpecular(void);
	static VDShader* VDAPIFASTENTRY IllusionReflective(void);

	static VDShader* VDAPIFASTENTRY PostOutShader(void);

	/**
	 *	create Skybox shader.
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY SkyBox(void);

	/**
	 *	Billboarding
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY SimpleBillboard(void);
	static VDShader* VDAPIFASTENTRY Billboard(void);

	/**
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY LightScattering(void);

	/**
	 *	Create approximated sub scattering surface.
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY Subsurface(void);
	static VDShader* VDAPIFASTENTRY SubsurfaceNormal(void);
	static VDShader* VDAPIFASTENTRY SubsurfaceSpecular(void);
	static VDShader* VDAPIFASTENTRY SubsurfaceNormalSpecular(void);
	static VDShader* VDAPIFASTENTRY SubsurfaceMapped(void);

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY ChromaticReflectiv(void);

	/**
	 *
	 *	@Return non-null object if created successfully.
	 */
	static VDShader* VDAPIFASTENTRY ForwardFirstPassShadow(void);
	static VDShader* VDAPIFASTENTRY CubeMapShadow(void);

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
