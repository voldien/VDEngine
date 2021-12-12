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
#ifndef _VD_SKYBOX_H_
#define _VD_SKYBOX_H_ 1
#include "../Core/VDBehavior.h"
#include "../VDDef.h"

/**
 *	Skybox, draws a cube over
 *	the camera view and creates the illusion
 *	of a sky.
 */
class VDDECLSPEC VDSkyBox : public VDBehavior {
  public:
	VDSkyBox();
	VDSkyBox(const VDSkyBox &skybox);
	~VDSkyBox();

	virtual void VDAPIENTRY instanceInitilize();
	virtual void VDAPIENTRY onEnable();
	virtual void VDAPIENTRY onDisable();
	virtual void VDAPIENTRY onDestroy();
	virtual void VDAPIENTRY initializeComponent();
	virtual VDBehavior *VDAPIENTRY copyComponent(unsigned int &dataSize);

  private:				  /*	Attributes.	*/
	VDCubeMap *cubeMap;	  /*	*/
	VDMesh *skyBoxMesh;	  /*	*/
	VDMaterial *material; /*	*/

  public:
	/**
	 *	Render skybox.
	 */
	void VDAPIENTRY render(const VDQuaternion &quat = VDQuaternion::Identity());

	/**
	 *	Set skybox cubemap.
	 *
	 *	If skybox is used as main skybox. it will be updated.
	 */
	void VDAPIENTRY setCubeMap(VDCubeMap *cubemap);

	/**
	 *	Get skybox cubemap referrence.
	 *
	 *	@Return
	 */
	VDCubeMap *VDAPIFASTENTRY getCubeMap() const;

  public: /*	Factory methods.	*/
	/**
	 *
	 *	@Return
	 */
	static VDSkyBox *VDAPIENTRY createDefaultSkyBox(VDCubeMap *cubeMap, const VDColor &color = VDColor());
};

#endif
