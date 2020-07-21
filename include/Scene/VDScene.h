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

#include"../Animation/VDAnimation.h"
#include"../Animation/VDKeyFrame.h"
#include"../Audio/VDAudio.h"
#include"../DataStructure/VDPoolAllactor.h"
#include"../DataStructure/VDStackAllactor.h"
#include"../DataStructure/VDVector.h"
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
typedef struct vd_engine_scene_t{

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
	VDPoolAllactor<VDCamera> cameras;
	std::vector<VDCamera*> gCameraCollection;

	/*
	 *
	 */
	VDSkyBox* skybox;
	VDCubeMap* ambientImageBased;

	/*
	 *
	 */
	VDPoolAllactor<VDGameObject> gameobjects;

	/*
	 *
	 */
	VDPoolAllactor<VDTransform> nodes;

	/*
	 *
	 */
	VDPoolAllactor<VDMaterial> materials;
	VDVector<VDMaterial*> pmaterials;

	/*
	 *
	 */
	VDPoolAllactor<VDMesh> meshs;
	std::map<const char*, VDMesh*> gMeshCollection;

	/*
	 *
	 */
	VDPoolAllactor<VDShader> shaders;
	ShaderCollection shaderCollection;

	/*
	 *
	 */
	typedef VDVector<VDLight*> VDLightCollection;
	typedef VDLightCollection::Iterator VDLightCollectionIterator;
	VDPoolAllactor<VDLight> lights;
	VDLightCollection lightcollection;
	std::map<int,VDLight*> gLightCollection;

	/**
	 *
	 */
	VDPoolAllactor<VDTexture> textures;
	std::map<const char*, VDTexture2D*> textureCollection;

	/**
	 *
	 */
	VDPoolAllactor<VDRenderTexture> rendertexture;
	VDVector<VDRenderTexture*> rendertextures;

	/**
	 *
	 */
	VDPoolAllactor<VDAudioClip> audios;
	std::map<const char*,VDAudioClip*> audioClipCollection;
	VDAudioListener* gListener;

	VDVector<VDAnimation*> AnimationCollection;

	/**
	 *
	 */
	VDPoolAllactor<VDAnimationClip> animationClips;
	VDVector<VDAnimationClip*> panimationClips;

	/**
	 *
	 */
	VDPoolAllactor<VDCurve> curves;
	VDVector<VDCurve*> pcurves;

	/**
	 *
	 */
	VDVector<VDAudioSource*> audioSources; // list of all AudioSource.

	/**
	 *
	 */
	VDVector<VDRigidBody*> rigidBodyCollection;
	VDPoolAllactor<VDKeyFrame> keys;	/**/
	VDStackAllocator resouces;			/**/

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
class VDDECLSPEC VDScene{
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
