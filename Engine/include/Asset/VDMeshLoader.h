/*
 *	VDEngine virtual dimension game engine.
 *	Copyright (C) 2014  Valdemar Lindberg
 *
 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _VD_MESHLOADER_H_
#define _VD_MESHLOADER_H_ 1
#include "../Animation/VDAnimationClip.h"
#include "../Rendering/Texture/VDTexture2D.h"
#include "VDAssetLoader.h"
#include "VDDCCLoaderOption.h"


#ifdef VD_INTERNAL
#include <assimp/ai_assert.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#endif

/**
 *
 */
class VDDECLSPEC VDMeshLoader : public VDAssetLoader {
  public:
	VDMeshLoader();
	VDMeshLoader(const VDMeshLoader &meshloader);
	~VDMeshLoader();

	/**
	 *	Release
	 */
	virtual void VDAPIENTRY release() override;

	/**
	 *	@Return
	 */
	int VDAPIFASTENTRY isValid() const;

	/**
	 *	@Return
	 */
	virtual int VDAPIENTRY loadContent(const char *path, unsigned long int SupportFlag = IMPORT_DEFAULT);

#if defined(VD_INTERNAL) || defined(VD_ASSIMP)
  private:
	/**
	 *
	 */
	void VDAPIENTRY initNoodeRoot(const aiNode *nodes, VDGameObject *parent = nullptr);

	/**
	 *	Load scene
	 */
	void VDAPIENTRY initScene(const aiScene *scene);

	/**
	 *	@Return
	 */
	VDMaterial *VDAPIENTRY initMaterial(aiMaterial *material);

	/**
	 *	@Return
	 */
	VDMesh *VDAPIENTRY initMesh(const aiMesh *mesh, unsigned int index);

	/**
	 *	@Return
	 */
	VDTexture2D *VDAPIENTRY initTexture(aiTexture *texture, unsigned int index);

	/**
	 *	@Return
	 */
	VDCamera *VDAPIENTRY initCamera(aiCamera *camera, unsigned int index);

	/**
	 *	@Return
	 */
	VDAnimationClip *VDAPIENTRY initAnimation(const aiAnimation *animation, unsigned int index);

	/**
	 *	@Return
	 */
	VDLight *VDAPIENTRY initLight(const aiLight *light, unsigned int index);

	/**
	 *	@Return
	 */
	static unsigned int VDAPIENTRY getdataStructSize(unsigned int RenderSupport);

  public: /*	*/
	VDGameObject *generateGameObjectHierarchy();
	VDGameObject *convertToSingle();

	/**
	 *
	 */
	void VDAPIENTRY initAnimationPosition(aiNodeAnim *position, VDAnimationClip *animationClip);

	/**
	 *
	 */
	void VDAPIENTRY initAnimationRotation(aiNodeAnim *rotation, VDAnimationClip *animationClip);

	/**
	 *
	 */
	void VDAPIENTRY initAnimationScale(aiNodeAnim *scale, VDAnimationClip *animationClip);
#endif

	/**
	 *
	 *	@Return
	 */
	VDMeshLoader &operator=(const VDMeshLoader &meshloader);

  protected:
	union {
#ifdef VD_INTERNAL
		aiScene *sceneRef;
#else
		void *sceneRef;
#endif
	};
};

#endif
