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
#ifndef _VD_ASSET_MANANGER_H_
#define _VD_ASSET_MANANGER_H_ 1
#include"../Core/VDGUID.h"
#include"../Core/VDTypes.h"
#include"../VDDef.h"
#include"VDAssetObject.h"

/*
 *
 */
typedef struct registry{
	VDTypeInfo type;		/*	*/
	VDGUID guid;			/*	Unique identifer.	*/
	VDAssetObject* asset;	/*	Pointer to object.	*/
}VDRegistry;

/**
 *	Responsible for managing resources.
 */
class VDDECLSPEC VDAssetManager{
public:
	typedef std::map<VDGUID, VDRegistry> RegistryTable;
	typedef std::map<VDGUID, VDRegistry>::iterator RegistryTableIterator;

	/**
	 *	Get absolute path to asset root directory
	 *
	 *	@Return non null pointer.
	 */
	static const char* VDAPIENTRY getRootDirectory(void);

	/**
	 *	Set absolute asset path directory.
	 */
	static void VDAPIENTRY setRootDirectory(const char* cpath);


	/**
	 *	Get absolute path.
	 *
	 *	@Return	Absolute path for relative path.
	 */
	static char* VDAPIENTRY getAbsolutePath(const char* relativePath, char* buffer, int len = -1);

	/**
	 *	Resource type enumerator.
	 */
	enum ResourceType{
		eConfig,			/*	Application configuration file path.	*/
		eConfigInternal,	/*	Engine internal configuration file path.	*/
		eShaderPath,		/*	Default shader source directory path.	*/
		eCurrentDir,		/*	Current directory path.	*/
		eTmpAssetDir,		/*	Directory path for temporary asset is stored.	*/
	};


	/**
	 *	Get resources path.
	 *
	 *	@Return non empty string if successfully.
	 */
	static std::string VDAPIENTRY getResourcePath(ResourceType type);

	/**
	 *	Get absolute path.
	 *
	 *	@Return	non empty string if successfully.
	 */
	static std::string VDAPIENTRY getResourceAbsolutePath(ResourceType type, const char* relativepath);

	/**
	 *	Release asset from engine.
	 *
	 *	\asset asset object to be released.
	 */
	static void VDAPIENTRY releaseAsset(VDAssetObject* asset);

	/**
	 *	Assign asset object to the engine asset manager.
	 *	Asset object will be stored in a hash table with their
	 *	unique ID as key.
	 *
	 *	\asset
	 */
	static void VDAPIENTRY assignAsset(VDAssetObject* asset, ...);

	/**
	 *	Get asset by their unique identifier.
	 *	\uid
	 *
	 *	@Return pointer to asset pointing to same uid.
	 */
	static VDRegistry* VDAPIFASTENTRY getAsset(const VDGUID uid);


private:	/*	Static attributes.	*/

	static RegistryTable assetreg;		/*	*/
	static char* rootpath;				/*	*/

private:	/*	Prevent class from being instantiated.	*/

	VDAssetManager(void){}
	VDAssetManager(const VDAssetManager& other){}
};

#endif
