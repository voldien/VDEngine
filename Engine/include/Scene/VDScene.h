/**
    VDEngine virtual dimension
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
#ifndef _VD_SCENE_H_
#define _VD_SCENE_H_ 1
#include<Core/dataStructure/PoolAllocator.h>
#include"../Animation/VDAnimation.h"
#include"../Animation/VDKeyFrame.h"
#include"../Audio/VDAudio.h"
#include"../Physic/VDPhysic.h"
#include"../Rendering/VDRendering.h"
#include"../Rendering/VDLight.h"
#include"VDGameObject.h"
#include"VDTransform.h"
#include"../Rendering/VDCamera.h"
#include"../VDSystem.h"

/**
 *
 */
typedef struct vd_engine_scene_t {

	unsigned int version;	/*	Version of the engine scene asset.	*/
	unsigned int flag;
	char name[256];

	/*
	 *
	 */
	VDColor ambientColor;
	unsigned int ambientType;

	/*
	 *
	 */
	unsigned int numMesh;
	unsigned int numObjects;
	unsigned int numGameObjects;

	/*
	 *
	 */
	VDCamera* mainCamera;
	VDCamera* currentCamera;
	fragcore::PoolAllocator<VDCamera> cameras;
	std::vector<VDCamera*> gCameraCollection;

	/*
	 *
	 */
	VDSkyBox* skybox;
	VDCubeMap* ambientImageBased;

	/*
	 *
	 */
	fragcore::PoolAllocator<VDGameObject> gameobjects;

	/*
	 *
	 */
	fragcore::PoolAllocator<VDTransform> nodes;

	/*
	 *
	 */
	fragcore::PoolAllocator<VDMaterial> materials;
	vector<VDMaterial*> pmaterials;

	/*
	 *
	 */
	fragcore::PoolAllocator<VDMesh> meshs;
	std::map<const char*, VDMesh*> gMeshCollection;

	/*
	 *
	 */
	fragcore::PoolAllocator<VDShader> shaders;
	ShaderCollection shaderCollection;

	/*
	 *
	 */
	fragcore::PoolAllocator<VDLight> lights;
	vector<VDLight *> lightcollection;
	std::map<int,VDLight*> gLightCollection;

	/**
	 *
	 */
	fragcore::PoolAllocator<VDTexture> textures;
	std::map<const char*, VDTexture2D*> textureCollection;

	/**
	 *
	 */
	fragcore::PoolAllocator<VDRenderTexture> rendertexture;
	vector<VDRenderTexture*> rendertextures;

	/**
	 *
	 */
	fragcore::PoolAllocator<VDAudioClip> audios;
	std::map<const char*,VDAudioClip*> audioClipCollection;
	VDAudioListener* gListener;

	vector<VDAnimation*> AnimationCollection;

	/**
	 *
	 */
	fragcore::PoolAllocator<VDAnimationClip> animationClips;
	vector<VDAnimationClip*> panimationClips;

	/**
	 *
	 */
	fragcore::PoolAllocator<VDCurve> curves;
	vector<VDCurve*> pcurves;

	/**
	 *
	 */
	vector<VDAudioSource*> audioSources; // list of all AudioSource.

	/**
	 *
	 */
	vector<VDRigidBody*> rigidBodyCollection;
	fragcore::PoolAllocator<VDKeyFrame> keys; /**/
	fragcore::StackAllocator resouces; /**/

	/**
	 *	scene light info.
	 */
	VDEngineLight lightinfo;

	/**
	 *
	 */
	VDSceneUniform uniform;

}VDEngineScene;


/**
 *
 */
class VDDECLSPEC VDScene {
public:	/*	Static methods.	*/

	/**
	 *
	 */
	static void VDAPIENTRY init(void);

	/**
	 *
	 */
	static void VDAPIENTRY addGameObject(VDGameObject* object);

	/**
	 *
	 */
	static void VDAPIENTRY addstaticObject(VDGameObject* object, bool wasStatic = false);

	/**
	 *
	 */
	static void VDAPIENTRY removeStaticObject(VDGameObject* obj, bool wasStatic = false);


	static void addCamera(VDCamera* camera);

	/**
	 *
	 */
	static void VDAPIENTRY clear(void);


	/**/
	static VDEngineScene* VDAPIFASTENTRY getScene(void);
};


#endif
