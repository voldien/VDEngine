/**
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
#ifndef _VD_RENDERER_H_
#define _VD_RENDERER_H_ 1
#include"../VDSystem.h"
#include"../Core/VDBehavior.h"
#include"VDRendering.h"
#include"../DataStructure/VDBoundVolume.h"

/**
 *	Responsible
 */
class VDDECLSPEC VDRenderer : public VDBehavior{
public:
	enum Shadows{
		eCastShadow = (1 << 0),
		eReciveShadow = (1 << 1),
	};

	enum RendererType{

		/*	Default rendering type.	*/
		eMesh = 0x40,
		eTerrain = 0x80,
		/*	Skinned	*/
		eSkinned = 0x100,
		eMorph = 0x200,
		eTrail = 0x800,
		eLine = 0x1000,
		eStaticBatch = 0x400,	/*	Tree	*/

		/*
		 *	particle simulation
		 *	will be renderered when all geometry has been rendered.
		 *	as it needs the depth buffer in order to achieve
		 *	soft particle.
		 */
		eParticle = 0x2000,

		/*
		 *	Lens flare will be rendered last
		 */
		eLensFlare = 0x4000,


		/*	*/
		eNumRenderType = (eMesh | eParticle | eSkinned),
	};

	VDRenderer(void);
	VDRenderer(RendererType type);	/*	TODO perhaps make it private or protected..*/
	VDRenderer(const VDRenderer& renderer);
	VDRenderer(VDMaterial* material);

private:	/*	Attributes.	*/

	unsigned int flag;		/*	*/
	VDMaterial* materials;	/*	*/
	VDMesh* meshFilter;		/*	*/

public:

	virtual void VDAPIENTRY instanceInitilize(void);
	virtual void VDAPIENTRY initializeComponent(void);
	virtual void VDAPIENTRY onEnable(void);
	virtual void VDAPIENTRY onDisable(void);
	virtual void VDAPIENTRY onDestroy(void);
	virtual VDBehavior* VDAPIENTRY copyComponent(unsigned int& dataSize);


	/**
	 *  Initialize the material inside the Engine.
	 *
	 *  \material
	 */
	void VDAPIENTRY setMaterial(VDMaterial* material);

	/*
	 *  Get Material Assoication with this Renderer.
	 *
	 *  @Return
	 */
	VDMaterial* getMaterial(void)const{return this->materials;}

	/*
	 * 	Get Renderer Bounds of Mesh & Transformation.
	 *  @Return
	 */
	VDAABB VDAPIFASTENTRY getRenderBounds(void)const;


	inline const VDBound& VDAPIFASTENTRY getVolumeBounds(void)const{
		return this->getMesh()->getBound();
	}


	/*
	 *	assign mesh to renderer.
	 */
	void VDAPIENTRY setMesh(VDMesh* mesh);

	/*
	 *
	 *  @Return
	 */
	inline VDMesh* VDAPIFASTENTRY getMesh(void)const{
		return this->meshFilter;
	}

	/*
	 *
	 */
	bool isPartOfStaticBatch(void)const;


	/*
	 *
	 *  @Return
	 */
	inline unsigned int VDAPIFASTENTRY getRendererFlag(void)const{
		return this->flag;
	}

	/*
	 *
	 */
	inline RendererType VDAPIENTRY getRenderType(void)const{
		return (RendererType)(this->flag  & ( RendererType::eMesh | RendererType::eParticle | RendererType::eSkinned | RendererType::eStaticBatch | RendererType::eTrail | RendererType::eLine | RendererType::eMorph | RendererType::eLensFlare | RendererType::eTerrain) );
	}

	/*
	 *
	 */
	void VDAPIENTRY setRenderType(RendererType rendertype);

	/*
	 *
	 */
	virtual void VDAPIENTRY draw(void);



	// TODO optimize Designed for shadow drawing

	/*	*/
	void VDAPIENTRY drawInstances(unsigned int elemetInstance, float* wmp);
	void VDAPIENTRY drawInstances(unsigned int elementInstances, float* wmp, float* world);


	/*
	 *	TODO remove
	 */
	void VDAPIFASTENTRY enableVertexPointer(void);

	/*
	 *	Renderer Cast Shadow. [means it will never be called in
	 *  Internal Shadow Rendering]. = Performance.
	 */
	void VDAPIENTRY castShadow(int castShadodw);

	/*
	 *	Renderer Recive Shadow.
	 */
	void VDAPIENTRY reciveShadow(int reciveShadow);


	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isSkinned(void)const;
	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isParticle(void)const;
	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isMorph(void)const;
	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isLensFlare(void)const;
	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isTerrain(void)const;
	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isStaticBatch(void);

	/*
	 *
	 *	@Return
	 */
	inline bool VDAPIFASTENTRY isCastShadow(void)const{return this->flag & eCastShadow;}

	/*
	 *
	 *	@Return
	 */
	inline bool VDAPIFASTENTRY isReciveShadow(void)const{return this->flag & eReciveShadow;}

	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isVisiable(void)const;


	/*
	 *
	 */
	void VDAPIFASTENTRY drawElementPatch(void);
	void VDAPIFASTENTRY drawArrayPatch(void);

	void VDAPIFASTENTRY drawMultiArrayPatch(unsigned int primcount, const unsigned int* count, const unsigned int* indices);
	void VDAPIFASTENTRY drawMultiElementsPatch(unsigned int primcount, const unsigned int* count, const unsigned int* indices);

	void VDAPIFASTENTRY drawMultiIndirectElementsPatch(unsigned int primcount, const unsigned int* count, const unsigned int* indices);
	void VDAPIFASTENTRY drawMultiIndirectArrayPatch(unsigned int primcount, const unsigned int* count, const unsigned int* indices);

	void VDAPIFASTENTRY drawIndirectArrayPatch(void);
	void VDAPIFASTENTRY drawIndirectElementPatch(void);

public:

	/*
	 *
	 */
	void VDAPIENTRY internalDraw(VDMesh::Primitive drawmode = VDMesh::eTriangles, unsigned int instances = 1);

	/*
	 *
	 */
	void VDAPIENTRY internalMultiDraw(unsigned int primcount, const unsigned int* count, const unsigned int* indices, VDMesh::Primitive drawMode = VDMesh::eTriangles);

	/*
	 *
	 */
	void VDAPIENTRY externalDraw(VDShader* shader = NULL);


public:	/*	static methods.	*/

	/**
	 *	Draw.
	 */
	static void VDAPIENTRY drawMesh(VDMesh* mesh);

	/**
	 *	Draw instances.
	 */
	static void VDAPIENTRY drawInstanceMesh(VDMesh* mesh, unsigned int count);

	/**
	 *	Draw
	 */
	static void VDAPIENTRY internalShadowDraw(VDShader* firstPassShadow = NULL, VDLight* light = NULL, VDMesh::Primitive drawmode = VDMesh::eTriangles);

	/**
	 *
	 */
	static void VDAPIENTRY internalShadowInstanceDraw(VDShader* firstPassShadow, VDLight* light);

	

};

#endif
