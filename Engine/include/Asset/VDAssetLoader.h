/**
    Copyright (C) 2014  Valdemar Lindberg
    VDEngine is a small game engine.

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
#ifndef _VD_ASSET_LOADER_H_
#define _VD_ASSET_LOADER_H_ 1
#include"../VDSystem.h"
#include"../Core/VDCore.h"
#include"VDDCCLoaderOption.h"

/**
 *	Abstract class for asset importer.
 *
 */
class VDDECLSPEC VDAssetLoader{
	friend class VDFBXLoader;
	friend class VDMeshLoader;
public:

	/**
	 *	Load asset from path.
	 *
	 *	@Return
	 */
	virtual int VDAPIENTRY loadContent(const char* path,
			unsigned long int SupportFlag = IMPORT_DEFAULT) = 0;

	/**
	 *	Release all resources.
	 */
	virtual void VDAPIENTRY release(void);


	/**
	 *	Get Scene Root.
	 *
	 *	@Return
	 */
	VDGameObject* VDAPIFASTENTRY sceneRoot(void);


	/**
	 *	Get Root GameObject. GameObject without a Parent.
	 *
	 *	\index
	 *
	 *	@Return pointer of GameObject.
	 */
	VDGameObject* VDAPIFASTENTRY getGameObjectRoot(unsigned int index);

	/**
	 *	Get number of gameobject root objects.
	 *
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getGameObjectRootCount(void)const;

	/**
	 *	@Return
	 */
	VDGameObject* VDAPIFASTENTRY getGameObject(unsigned int Index);

	/**
	 *
	 */
	void VDAPIFASTENTRY setGameObject(const VDGameObject* object);

	/**
	 *	@Return
	 */
	VDGameObject* VDAPIFASTENTRY findGameObject(const char* gameobjectName);

	/**
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getGameObjectCount(void)const;

	/**
	 *	@Return
	 */
	VDMesh* VDAPIFASTENTRY getMesh(unsigned int index);

	/**
	 *
	 */
	void VDAPIFASTENTRY setMesh(const VDMesh* mesh);

	/**
	 *
	 *	@Return
	 */
	VDMesh* VDAPIFASTENTRY findMesh(const char* meshName);

	/**
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getMeshCount(void)const;

	/**
	 *	@Return
	 */
	VDCamera* VDAPIFASTENTRY getCamera(unsigned int index);

	/**
	 *
	 */
	void VDAPIENTRY setCamera(const VDCamera* camera);

	/**
	 *	@Return
	 */
	VDCamera* VDAPIFASTENTRY findCamera(const char* cname);

	/**
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getCameraCount(void)const;

	/**
	 *	@Return
	 */
	VDLight* VDAPIFASTENTRY getLight(unsigned int index);

	/**
	 *
	 */
	void VDAPIENTRY setLight(const VDLight* light);

	/**
	 *	@Return
	 */
	VDLight* VDAPIFASTENTRY findLight(const char* cname);

	/**
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getLightCount(void)const;

	/**
	 *	@Return
	 */
	VDTexture2D* VDAPIFASTENTRY getTexture(unsigned int index);

	/**
	 *
	 */
	void VDAPIENTRY setTexture(const VDTexture2D* texture);

	/**
	 *	@Return
	 */
	VDTexture2D* VDAPIFASTENTRY findTexture(const char* textureName);

	/**
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getTextureCount(void)const;

	/**
	 *	@Return
	 */
	VDAnimationClip* VDAPIFASTENTRY getAnimationClip(unsigned int index);

	/**
	 *
	 */
	void VDAPIENTRY setAnimationClip(const VDAnimationClip* clip);

	/**
	 *	@Return
	 */
	VDAnimationClip* VDAPIFASTENTRY findAnimationClip(const char* cname);

	/**
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getAnimationClipCount(void)const;


	/**
	 *
	 *	@Return
	 */
	VDAnimation* VDAPIFASTENTRY getAnimation(unsigned int index);

	/**
	 *
	 */
	void VDAPIENTRY setAnimation(const VDAnimation* animation);

	/**
	 *	@Return
	 */
	VDAnimation* VDAPIFASTENTRY findAnimation(const char* cname);

	/**
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getAnimationCount(void)const;

	/**
	 *
	 *	@Return
	 */
	VDMaterial* VDAPIFASTENTRY getMaterial(unsigned int index);

	/**
	 *
	 */
	void VDAPIENTRY setMaterial(const VDMaterial* material);

	/**
	 *	@Return
	 */
	VDMaterial* VDAPIFASTENTRY findMaterial(const char* cname);

	/**
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getMaterialCount(void)const;



	/**
	 *	@Return
	 */
	VDRenderer* VDAPIFASTENTRY getRenderer(unsigned int index);

	/**
	 *
	 */
	void VDAPIENTRY setRenderer(const VDRenderer* renderer);

	/**
	 *	@Return
	 */
	VDRenderer* VDAPIFASTENTRY findRenderer(const char* cname);

	/**
	 *
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getRendererCount(void)const;


	/**
	 *	Bounds of current scene.
	 *	@Return
	 */
	VDOBB VDAPIFASTENTRY getSceneOBB(void)const;


	/**
	 *	Utility methods.
	 */
	void scale(float scale);


	/**
	 *	@Return
	 */
	inline unsigned long int getFlag(void)const{
		return flags;
	}


	/**
	 *
	 *	@Return
	 */
	const char* getPath(void)const{
		return this->path;
	}

	/**
	 *	@Return
	 */
	VDAssetLoader& operator=(const VDAssetLoader& loader);

	/**
	 *	@Return
	 */
	bool operator==(const VDAssetLoader& loader);

	/**
	 *	@Return
	 */
	bool operator!=(const VDAssetLoader& loader);

protected:	/*	Protected attributes.	*/


	unsigned long int flags;						/*	*/
	std::vector<VDMesh*> meshs;						/*	*/
	std::vector<VDMaterial*> materials;				/*	*/
	std::vector<VDTexture2D*> textures;				/*	*/
	std::map<int, VDTexture*> textureCollection;	/*	*/
	std::vector<VDCamera*> cameras;					/*	*/
	std::vector<VDLight*> lights;					/*	*/
	std::vector<VDAABB*> bounds;					/*	*/
	std::vector<VDGameObject*> object;				/*	*/
	std::vector<VDAnimation*> animations;			/*	*/
	std::vector<VDAnimationClip*> animationClip;	/*	*/
	std::vector<VDAnimationClip*> animationClips;	/*	*/
	std::vector<VDRenderer*> renderer;				/*	*/
	std::map<VDGUID, VDTypeInfo> hashType;			/*	Not supported.	*/

	char path[PATH_MAX];							/*	*/

protected:	/*	*/

	virtual ~VDAssetLoader(void){}
};

#endif
