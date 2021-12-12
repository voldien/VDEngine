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
#ifndef _VD_RENDERER_H_
#define _VD_RENDERER_H_ 1
#include "../Core/VDBehavior.h"
#include "../DataStructure/VDBoundVolume.h"
#include "../VDSystem.h"
#include "VDRendering.h"


/**
 *	Responsible
 */
class VDDECLSPEC VDRenderer : public VDBehavior {
  public:
	enum Shadows {
		CastShadow = (1 << 0),
		ReciveShadow = (1 << 1),
	};

	enum RendererType {

		/*	Default rendering type.	*/
		Mesh = 0x40,
		Terrain = 0x80,
		/*	Skinned	*/
		Skinned = 0x100,
		Morph = 0x200,
		Trail = 0x800,
		Line = 0x1000,
		StaticBatch = 0x400, /*	Tree	*/

		/*
		 *	particle simulation
		 *	will be renderered when all geometry has been rendered.
		 *	as it needs the depth buffer in order to achieve
		 *	soft particle.
		 */
		Particle = 0x2000,

		/*
		 *	Lens flare will be rendered last
		 */
		LensFlare = 0x4000,

		/*	*/
		NumRenderType = (Mesh | Particle | Skinned),
	};

	VDRenderer();
	VDRenderer(RendererType type); /*	TODO perhaps make it private or protected..*/
	VDRenderer(const VDRenderer &renderer);
	VDRenderer(VDMaterial *material);

  private:				   /*	Attributes.	*/
	unsigned int flag;	   /*	*/
	VDMaterial *materials; /*	*/
	VDMesh *meshFilter;	   /*	*/

  public:
	virtual void VDAPIENTRY instanceInitilize();
	virtual void VDAPIENTRY initializeComponent();
	virtual void VDAPIENTRY onEnable();
	virtual void VDAPIENTRY onDisable();
	virtual void VDAPIENTRY onDestroy();
	virtual VDBehavior *VDAPIENTRY copyComponent(unsigned int &dataSize);

	/**
	 *  Initialize the material inside the Engine.
	 *
	 *  \material
	 */
	void VDAPIENTRY setMaterial(VDMaterial *material);

	/*
	 *  Get Material Assoication with this Renderer.
	 *
	 *  @Return
	 */
	VDMaterial *getMaterial() const { return this->materials; }

	/*
	 * 	Get Renderer Bounds of Mesh & Transformation.
	 *  @Return
	 */
	VDAABB VDAPIFASTENTRY getRenderBounds() const;

	inline const VDBound &VDAPIFASTENTRY getVolumeBounds() const { return this->getMesh()->getBound(); }

	/*
	 *	assign mesh to renderer.
	 */
	void VDAPIENTRY setMesh(VDMesh *mesh);

	/*
	 *
	 *  @Return
	 */
	inline VDMesh *VDAPIFASTENTRY getMesh() const { return this->meshFilter; }

	/*
	 *
	 */
	bool isPartOfStaticBatch() const;

	/*
	 *
	 *  @Return
	 */
	inline unsigned int VDAPIFASTENTRY getRendererFlag() const { return this->flag; }

	/*
	 *
	 */
	inline RendererType VDAPIENTRY getRenderType() const {
		return (RendererType)(this->flag & (RendererType::Mesh | RendererType::Particle | RendererType::Skinned |
											RendererType::StaticBatch | RendererType::Trail | RendererType::Line |
											RendererType::Morph | RendererType::LensFlare | RendererType::Terrain));
	}

	/*
	 *
	 */
	void VDAPIENTRY setRenderType(RendererType rendertype);

	/*
	 *
	 */
	virtual void VDAPIENTRY draw();

	// TODO optimize Designed for shadow drawing

	/*	*/
	void VDAPIENTRY drawInstances(unsigned int elemetInstance, float *wmp);
	void VDAPIENTRY drawInstances(unsigned int elementInstances, float *wmp, float *world);

	/*
	 *	TODO remove
	 */
	void VDAPIFASTENTRY enableVertexPointer();

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
	bool VDAPIFASTENTRY isSkinned() const;
	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isParticle() const;
	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isMorph() const;
	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isLensFlare() const;
	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isTerrain() const;
	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isStaticBatch();

	/*
	 *
	 *	@Return
	 */
	inline bool VDAPIFASTENTRY isCastShadow() const { return this->flag & CastShadow; }

	/*
	 *
	 *	@Return
	 */
	inline bool VDAPIFASTENTRY isReciveShadow() const { return this->flag & ReciveShadow; }

	/*
	 *	@Return
	 */
	bool VDAPIFASTENTRY isVisiable() const;

	/*
	 *
	 */
	void VDAPIFASTENTRY drawElementPatch();
	void VDAPIFASTENTRY drawArrayPatch();

	void VDAPIFASTENTRY drawMultiArrayPatch(unsigned int primcount, const unsigned int *count,
											const unsigned int *indices);
	void VDAPIFASTENTRY drawMultiElementsPatch(unsigned int primcount, const unsigned int *count,
											   const unsigned int *indices);

	void VDAPIFASTENTRY drawMultiIndirectElementsPatch(unsigned int primcount, const unsigned int *count,
													   const unsigned int *indices);
	void VDAPIFASTENTRY drawMultiIndirectArrayPatch(unsigned int primcount, const unsigned int *count,
													const unsigned int *indices);

	void VDAPIFASTENTRY drawIndirectArrayPatch();
	void VDAPIFASTENTRY drawIndirectElementPatch();

  public:
	/*
	 *
	 */
	void VDAPIENTRY internalDraw(VDMesh::Primitive drawmode = VDMesh::eTriangles, unsigned int instances = 1);

	/*
	 *
	 */
	void VDAPIENTRY internalMultiDraw(unsigned int primcount, const unsigned int *count, const unsigned int *indices,
									  VDMesh::Primitive drawMode = VDMesh::eTriangles);

	/*
	 *
	 */
	void VDAPIENTRY externalDraw(VDShader *shader = nullptr);

  public: /*	static methods.	*/
	/**
	 *	Draw.
	 */
	static void VDAPIENTRY drawMesh(VDMesh *mesh);

	/**
	 *	Draw instances.
	 */
	static void VDAPIENTRY drawInstanceMesh(VDMesh *mesh, unsigned int count);

	/**
	 *	Draw
	 */
	static void VDAPIENTRY internalShadowDraw(VDShader *firstPassShadow = nullptr, VDLight *light = nullptr,
											  VDMesh::Primitive drawmode = VDMesh::eTriangles);

	/**
	 *
	 */
	static void VDAPIENTRY internalShadowInstanceDraw(VDShader *firstPassShadow, VDLight *light);
};

#endif
