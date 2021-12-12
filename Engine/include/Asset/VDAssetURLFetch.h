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
#ifndef _VD_ASSET_URL_FETCH_H_
#define _VD_ASSET_URL_FETCH_H_ 1
#include "../VDSystem.h"

/**
 *	Fetch asset remote.
 */
class VDDECLSPEC VDAssetURLFetch {
  public:
	VDAssetURLFetch();
	VDAssetURLFetch(const char *url);
	VDAssetURLFetch(const VDAssetURLFetch &url);
	~VDAssetURLFetch();

	/**
	 *
	 *	@Return true is succufully.
	 */
	bool VDAPIENTRY load(const char *url);

	/**
	 *
	 *	@Return
	 */
	VDTexture2D *VDAPIENTRY getTexture();

	/**
	 *
	 *	@Return
	 */
	VDAudioClip *VDAPIENTRY getAudioClip();

	/**
	 *
	 *	@Return
	 */
	VDMesh *VDAPIENTRY getMesh();

	/**
	 *
	 *	@Return
	 */
	char *VDAPIENTRY getText();

	/**
	 *
	 *	@Return
	 */
	VDMaterial *VDAPIENTRY getMaterial();

	/**
	 *
	 *	@Return
	 */
	VDCubeMap *VDAPIENTRY getCubeMap();

	/**
	 *
	 *	@Return
	 */
	VDTypeInfo VDAPIENTRY getAssetType() const;

	/**
	 *
	 *	@Return
	 */
	const char *VDAPIENTRY getAbsolutePath() const;

	/**
	 *
	 *	@Return
	 */
	const char *VDAPIENTRY getRelativePath() const;

  private:					/*	Attributes.	*/
	char tmpPath[PATH_MAX]; /*	*/
	FILE *ramDisk;			/*	*/

  public: /*	Static methods.	*/
	/**
	 *	Get caching directory.
	 *
	 *	@Return
	 */
	static const char *getCacheDirectory();
};

#endif
