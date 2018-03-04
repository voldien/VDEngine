/**
    Copyright (C) 2016  Valdemar Lindberg
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
#ifndef _VD_ASSET_URL_FETCH_H_
#define _VD_ASSET_URL_FETCH_H_ 1
#include"../VDSystem.h"


/**
 *	Fetch asset remote.
 */
class VDDECLSPEC VDAssetURLFetch{
public:
	VDAssetURLFetch(void);
	VDAssetURLFetch(const char* url);
	VDAssetURLFetch(const VDAssetURLFetch& url);
	~VDAssetURLFetch(void);

	/**
	 *
	 *	@Return true is succufully.
	 */
	bool VDAPIENTRY load(const char* url);

	/**
	 *
	 *	@Return
	 */
	VDTexture2D* VDAPIENTRY getTexture(void);

	/**
	 *
	 *	@Return
	 */
	VDAudioClip* VDAPIENTRY getAudioClip(void);

	/**
	 *
	 *	@Return
	 */
	VDMesh* VDAPIENTRY getMesh(void);

	/**
	 *
	 *	@Return
	 */
	char* VDAPIENTRY getText(void);

	/**
	 *
	 *	@Return
	 */
	VDMaterial* VDAPIENTRY getMaterial(void);

	/**
	 *
	 *	@Return
	 */
	VDCubeMap* VDAPIENTRY getCubeMap(void);

	/**
	 *
	 *	@Return
	 */
	VDTypeInfo VDAPIENTRY getAssetType(void)const;


	/**
	 *
	 *	@Return
	 */
	const char* VDAPIENTRY getAbsolutePath(void)const;

	/**
	 *
	 *	@Return
	 */
	const char* VDAPIENTRY getRelativePath(void)const;


private:	/*	Attributes.	*/

	char tmpPath[PATH_MAX];		/*	*/
	FILE* ramDisk;				/*	*/

public:	/*	Static methods.	*/

	/**
	 *	Get caching directory.
	 *
	 *	@Return
	 */
	static const char* getCacheDirectory(void);
};


#endif
