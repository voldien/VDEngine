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
#ifndef _VD_CAMERA_H_
#define _VD_CAMERA_H_ 1
#include "../Core/VDLayer.h"
#include "../DataStructure/VDRect.h"
#include "../DataStructure/VDVector.h"
#include "Texture/VDRenderTexture.h"
#include "VDPostEffect.h"
#include "VDRenderSetting.h"
#include <stddef.h>
#include "../Scene/VDFrustum.h"
#include "../VDSystem.h"

/**
 *
 */
class VDDECLSPEC VDCamera : public VDFrustum {
public:

	enum ClearMode{
		DontClear 	= (1 << 0),	/*	*/
		Clear 		= (1 << 1),	/*	*/
		SkyBox 	= (1 << 2)	/*	*/
	};

	enum ProjectionMode{
		Perspective 	= (1 << 3),	/*	*/
		Orthographic 	= (1 << 4),	/*	*/
	};

	enum Culling{
		eFrustumCulling 	= (1 << 5),
		eCullBox 			= (1 << 6),
		eCullSphere 		= (1 << 7),
		eCullPortal 		= (1 << 8),
		eOcclusionCulling 	= (1 << 9),
		eFrustumOptions 	= (eFrustumCulling | eCullBox | eCullSphere | eCullPortal | eOcclusionCulling)
	};

	enum PolygoneMode{
		eWireFrame 	= (1 << 10),	/*	*/
		Point 		= (1 << 11),	/*	*/
		eTriangle 	= (1 << 12),	/*	*/
	};

	enum LightDynamic{
		eHDR = (1 << 13)	/*	High Dynamic Range. Not supported.	*/
	};

	enum ClearBuffer{
		Color 		= (1 << 23),		/*	Clear color.	*/
		eDepth 		= (1 << 24),		/*	Clear depth.	*/
		eStencil 	= (1 << 25),	/*	Clear stencil.	*/
		eClearAll 	= (Color | eDepth | eStencil),
	};

	enum CameraBitFlag{
		eRenderTexture = (1 << 17),
		ePostEffect = (1 << 18),
		eVertexLitRendering = (1 << 19),
		eForwardRendering = (1 << 20),
		eDeferredRendering = (1 << 21),
		eCulling= (1 << 22),
	};

	VDCamera(void);
	VDCamera(const VDCamera& camera);


private: /*	Attributes.	*/

	VDColor backColor;						/*	Back color for clearing screen.	*/
	VDRect viewPort;						/*	Normalized viewport of camera.	*/
	unsigned int flag;						/*	Camera flag states	*/
	VDLayer cullingmask;					/*	Culling masking.	*/
	VDVector<VDPostEffect*> postEffect;		/*	Post effects.	*/
	VDRenderTexture* renderTexture;			/*	Rendertarget.	*/

public:	/*	Public methods.	*/


	virtual void VDAPIENTRY instanceInitilize(void);
	virtual void VDAPIENTRY initializeComponent(void);
	virtual void VDAPIENTRY onEnable(void);
	virtual void VDAPIENTRY onDisable(void);
	virtual void VDAPIENTRY onDestroy(void);
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);

	/**
	 *	Set HDR.
	 */
	void VDAPIENTRY hdr(bool enabled);

	/**
	 *	Determine if HDR is enabled.
	 *
	 *	@Return true if HDR is enabled.
	 */
	bool VDAPIENTRY isHDREnabled(void)const;

	/**
	 *
	 */
	void VDAPIFASTENTRY setClearMode(ClearMode clear);

	/**
	 *
	 *	@Return ClearMode
	 */
	ClearMode VDAPIENTRY getClearMode(void)const;

	/**
	 *
	 */
	void VDAPIFASTENTRY setClearFlag(ClearBuffer clearBuffer);

	/**
	 *
	 *	@Return
	 */
	ClearBuffer VDAPIENTRY getClearFlag(ClearBuffer clearBuffer)const;


	/**
	 *
	 */
	void VDAPIENTRY setProjectionMode(ProjectionMode projection);

	/**
	 *	@Return
	 */
	ProjectionMode VDAPIENTRY getProjectionMode(void)const;


	/*
	 *
	 */
	void VDAPIFASTENTRY setPolygoneMode(PolygoneMode mode);

	/*
	 *
	 *	@Return
	 */
	PolygoneMode VDAPIENTRY getPolygoneMode(PolygoneMode mode);


	/**
	 *
	 */
	void VDAPIENTRY setCullingMask(const VDLayer& mask);

	/**
	 *
	 *	@Return
	 */
	inline VDLayer VDAPIENTRY getCullingMask(void)const{
		return this->cullingmask;
	}


	/**
	 *	Get renderingPath
	 *
	 *	@Return
	 */
	VDRenderSetting::RenderPipeline VDAPIENTRY getRenderingPath(void)const;



	/**
	 *
	 *	@Return
	 */
	inline unsigned int getNumPostEffects(void)const{
		return this->postEffect.size();
	}

	/**
	 *
	 *	@Return
	 */
	bool usePostEffect(void)const{
		return (this->flag & ePostEffect) != 0;
	}

	void posteffect(bool posteffect){
		if(posteffect){
			this->flag |= ePostEffect;
		}else{
			this->flag = this->flag & ~ePostEffect;
		}
	}

	/**
	 *
	 *	Set PostEffect.
	 */
	void VDAPIFASTENTRY setPostEffect(VDPostEffect* postEffect, unsigned int index = 0);

	/**
	 *
	 *	@Return
	 */
	VDPostEffect* VDAPIFASTENTRY getPostEffect(unsigned int index)const{
		return (index < this->postEffect.size()) ? this->postEffect[index] : NULL;
	}

	/**
	 *
	 *	Remove PostEffect.
	 */
	void VDAPIFASTENTRY removePostEffect(VDPostEffect* postEffect);

	/**
	 *
	 *	Remove PostEffect Reference of Index.
	 */
	void VDAPIFASTENTRY removePostEffect(int index);

	/**
	 *
	 *	Remove all PostEffect References
	 */
	void VDAPIFASTENTRY removeAllPostEffect(void);

	/**
	 *
	 */
	void VDAPIENTRY enableRenderTexture(bool enabled);

	/**
	 *	Create render Target.
	 *
	 *	@Return
	 */
	VDRenderTexture* VDAPIENTRY createRenderTexture(const VDSize& size, unsigned int rendertextureType = VDRenderTexture::Color);

	/**
	 *	Get render Texture Target.
	 *
	 *	@Return
	 */
	inline VDRenderTexture* VDAPIFASTENTRY getRenderTexture(void)const{
		return this->renderTexture;
	}

	/**
	 *
	 */
	void VDAPIENTRY setRenderTexture(VDRenderTexture* rendertexture);

	/**
	 *
	 */
	void VDAPIENTRY removeRenderTexture(void);

	/**
	 *	@Return true if rendertarget is available and enabled.
	 */
	inline bool VDAPIENTRY isRenderTarget(void)const{
		return (this->flag & eRenderTexture) && ( this->getRenderTexture() != NULL );
	}


	/**
	 *
	 */
	VDRenderTexture* VDAPIENTRY getOutpuFrameBuffer(void);

	/**
	 *	Get rectangle in pixel size.
	 *
	 *	@Return
	 */
	VDRect VDAPIFASTENTRY pixelRect(void)const;


	/**
	 *
	 */
	void VDAPIENTRY beginSceneRender(void);


	/**
	 *
	 *
	 */
	void VDAPIENTRY endSceneRender(void);


	/**
	 *	Send Ray From screenSpace to worldSpace.
	 *
	 *	@Return
	 */
	VDVector3 VDAPIENTRY screenSpaceToWorldSpace(const VDVector2& screenPos)const;


	/**
	 *
	 *	@Return
	 */
	VDRay VDAPIENTRY screenPointToRay(const VDVector2& screenCoordinate);

	/**
	 *	TODO Change the naming.
	 *
	 *	\screenPos in pixel
	 *
	 *	@Return
	 */
	VDGameObject* VDAPIENTRY screenSpaceToWorldSpaceObject(const VDVector2& screenPos);

	/**
	 *	Get ScreenSpace From worldSpace related to Camera Oriention.
	 *
	 *	@Return normalize coordinate.
	 */
	VDVector2 VDAPIENTRY worldSpaceToScreenSpace(const VDVector3& WorldPos);

	/**
	 *
	 *	@Return
	 */
	VDMatrix4x4 VDAPIENTRY getProjectionViewMatrix(void)const;

	/**
	 *
	 */
	void VDAPIFASTENTRY updateCameraMatrix(void);


	/**
	 *	TODO rename
	 */
	void VDAPIENTRY useOcclusionCulling(bool use);
	void VDAPIENTRY useFrustumCulling(bool use);
	inline bool VDAPIENTRY isOcclusionCulling(void)const{return ( this->flag & eOcclusionCulling ) != 0;}
	inline bool VDAPIENTRY isFrustumCulling(void)const{return ( this->flag & eFrustumCulling ) != 0;}

	/**
	 *
	 */
	void VDAPIFASTENTRY updateFrustum(void);

	/**
	 *	Get camera index.
	 *
	 *	@Return non negative index.
	 */
	int VDAPIFASTENTRY getCameraIndex(void);

	/**
	 *	Determine if camera object is main camera.
	 *
	 *	@Return true if main camera.
	 */
	bool VDAPIFASTENTRY isMainCamera(void)const;



	/**
	 *
	 *	@Return
	 */
	inline VDRect VDAPIFASTENTRY getViewPort(void)const{return this->viewPort;}
	void VDAPIFASTENTRY setViewPort(const VDRect& viewport);

	/**
	 *
	 *	@Return
	 */
	VDColor VDAPIFASTENTRY getBackColor(void)const{return this->backColor;}

	/**
	 *
	 */
	void VDAPIFASTENTRY setBackColor(const VDColor& backColor){this->backColor = backColor;}

	/**
	 *
	 *	@Return
	 */
	float VDAPIFASTENTRY getAspect(void)const;



public:	/*	Static methods.	*/

	/**
	 *	Set Main Camera Of Current Scene.
	 */
	static void VDAPIENTRY setMainCamera(VDCamera* camera);

	/**
	 *	Get Main Camera Of Current Scene.
	 *
	 *	@Return
	 */
	static VDCamera* VDAPIENTRY getMainCamera(void);

	/**
	 *	Get Current Camera That's being used.
	 *
	 *	@Return
	 */
	static VDCamera* VDAPIENTRY getCurrentCamera(void);

	/**
	 *	Set current camera To be Used.
	 */
	static void VDAPIFASTENTRY setCurrentCamera(VDCamera* camera);

	/**
	 *	Get camera by it's index.
	 *
	 *	@Return
	 */
	static VDCamera* VDAPIENTRY getCamera(unsigned int index);

	/**
	 *	Get Camera Count of All Camera In Scene.
	 *
	 *	@Return
	 */
	static int VDAPIENTRY getCameraCount(void);

};

#endif
