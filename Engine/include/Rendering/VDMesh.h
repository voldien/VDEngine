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
#ifndef _VD_MESH_H_
#define _VD_MESH_H_ 1
#include"../VDSystem.h"
#include"../Asset/VDAssetObject.h"
#include"../DataStructure/VDBoundVolume.h"

/**
 *
 */
class VDDECLSPEC VDMesh : public VDAssetObject{
public:
	friend class VDGeometryProcedure;
	friend class VDGeometryUtility;

	typedef struct vd_mesh_description_t{
		unsigned int VBO;
		unsigned int VAO;
		unsigned int IBO;
		unsigned int POS_VB;
		unsigned int TEXCOORD_VB;
		unsigned int NORMAL_VB;
		unsigned int TANGENT_VB;
		unsigned int BONE_VB;
		unsigned int WVP;
		unsigned int WORLD_MAT;
		unsigned int meshFlag;
	}VDMeshDesc;

	enum meshFlag {
		eStaticMesh 		= 0x800,
		eQuadTree 			= 0x1000,
		eDynamicMesh 		= 0x2000,
		eInstanceRendering 	= 0x4000,
		eVAO 				= 0x8000,
		eVBO 				= 0x10000,
		eArray 				= 0x20000,
		eSkinned 			= 0x40000,		/**/
		eStaticBatch 		= 0x80000,		/**/
		eAABB 			= VDBound::eAABB,
		eOBB 			= VDBound::eOBB,
		eAllBound 		= VDBound::eBound,
	};

	enum BufferType{
		eBufferArray 	= 0,				/*	*/
		eElementArray	= 1,				/*	*/
	};

	enum AccessMode{
		eRead 		= 0x88B8,	/*	GL_READ_ONLY	*/
		eWrite 		= 0x88B9,	/*	GL_WRITE_ONLY	*/
		eReadWrite 	= 0x88BA,	/*	GL_READ_WRITE	*/
	};


	/**/
	enum MeshComponent{
		eVertex 			= 0x1,
		eTextureCoord 		= 0x2,
		eNormal 			= 0x4,
		eVertexColor 		= 0x8,
		eTangent 			= 0x10,
		eTextureCoord2 		= 0x20,
		eBoneID 			= 0x40,
		eBoneWeight 		= 0x80,
		eIndex 				= 0x100,
		eBiNormal 			= 0x200,
		eBitTangent			= 0x400,

		eDefaultMesh = (eVertex | eTextureCoord | eNormal | eTangent),
	};

	enum Primitive{
		Point = 0x0,					/*	GL_POINTS*/
		eLine = 0x1,					/*	GL_LINES*/
		eLineLoop = 0x2,				/*	GL_LINE_LOOP	*/
		eLineStrip = 0x3,				/*	GL_TRIANGLES*/
		eTriangles = 0x4,				/*	GL_LINE_STRIP*/
		eTriangleStrip = 0x5,			/*	GL_TRIANGLE_STRIP*/
		eTriangleFan = 0x6,				/*	GL_TRIANGLE_FAN*/
		eTriangleQuads = 0x7,			/*	GL_QUADS*/
		eTriangleQuadTrip = 0x8,		/*	GL_QUAD_STRIP*/
		eTrianglesAdjacency = 0x000C,	/*GL_TRIANGLES_ADJACENCY*/
	};

private:
	VDMesh(void);
	VDMesh(const VDMesh& mesh);
	VDMesh(const char* name);
	VDMesh(const void* VertexBuffer,
			unsigned int vertexStrideSize,
			unsigned int VertexDataSize,
			const unsigned char* indicesData,
			unsigned int indicesTypeSize,
			unsigned int indicesDataSize,
			unsigned int bitFlag = 0x0);
public:
	~VDMesh(void);

private:	/*	Attributes.	*/

	unsigned int vertexCount;	/*	Number of vertex elements.*/
	unsigned int indicesCount;	/*	Indices count.	*/
	VDMeshDesc meshdesc;	/*	MeshInstrution.	*/

	unsigned int flag;			/*	SUPPORT VALUES???	*/
	unsigned int nSizeFlag;		/*	Indices data type flag.	*/
	unsigned char drawMode;		/*	Primitivs rendering mode.	*/
	unsigned char strideSize;	/*	Size between each vertex in buffer.	*/
	VDBound bounds;	/*	Mesh geometry AABB.	*/

public:

	/**
	 *	release mesh buffer on GPU [Preference]
	 */
	virtual void VDAPIENTRY release(void);

	/**
	 *	@Return
	 */
	VDMesh& operator=(const VDMesh& mesh);

	inline void setDrawMode(unsigned int drawMode){
		this->drawMode = drawMode;
	}
	inline unsigned int getDrawMode(void)const{
		return this->drawMode;
	}

	inline unsigned int getVertexCount(void)const{
		return this->vertexCount;
	}

	inline unsigned int getPolygoneCount(void)const{
		return this->indicesCount;
	}

	inline unsigned int getVBO(void)const{
		return this->meshdesc.VBO;
	}

	inline unsigned int getVAO(void)const{
		return this->meshdesc.VAO;
	}

	inline unsigned int getIBO(void)const{
		return this->meshdesc.IBO;
	}


	VDMeshDesc* getMeshDesc(void){
		return &this->meshdesc;
	}


	inline unsigned int getNumIndices(void)const{
		return this->indicesCount;
	}

	inline unsigned int getIndicesNFlag(void)const{
		return this->nSizeFlag;
	}

	/**
	 *
	 */
	int VDAPIENTRY setMeshFlag(VDMesh::meshFlag meshFlag);

	/**
	 *	@Return
	 */
	inline unsigned int getMeshFlag(void)const{
		return this->flag;
	}


	/**
	 *	Get stride size of each vertex.
	 */
	unsigned int VDAPIFASTENTRY getVertexStride(void)const;

	/**
	 *
	 *	@Return
	 */
	unsigned int VDAPIFASTENTRY getIndicesStride(void)const;

	/**
	 *
	 */
	inline const VDBound& getBound(void)const{
		return this->bounds;
	}

	/*
	 *	Get indices data type in form of a
	 *
	 *	@Return polygone Type.
	 */
	VDTypeInfo VDAPIFASTENTRY getIndicesType(void)const;

	/**
	 *
	 */
	void VDAPIENTRY setABB(const VDAABB& bounds);
	/**
	 *
	 */
	void VDAPIENTRY setOBB(const VDOBB& bounds);

	/**
	 *
	 *	@Return
	 */
	inline VDBound::BoundType getBoundType(void)const{
		return (VDBound::BoundType)(this->getMeshFlag() & VDBound::eBound);
	}


	/**
	 *	Vertex
	 *
	 *	\index
	 *
	 *	@Return
	 */
	VDVector3 VDAPIENTRY getVertex(unsigned int index)const;

	/*
	 *
	 */
	void VDAPIENTRY setVertex(unsigned int index, const VDVector3& vertex);

	/*
	 *	Vertex Bundle
	 *	@Return
	 */
	VDVertex* VDAPIENTRY getVertexBundle(void);

	/*
	 *
	 */
	void VDAPIENTRY setVertexBundle(const VDVector3* vertex);

	/*
	 *	Get UV [Index]
	 *	@Return
	 */
	VDVector2 VDAPIENTRY getUV(unsigned int index)const;

	/*
	 *
	 */
	void VDAPIENTRY setUV(unsigned int index, const VDVector2& uv);

	/*
	 *	Get UV Bundle Data
	 *	@Return
	 */
	VDVector2* VDAPIENTRY getUVBundle(void);

	/*
	 *
	 */
	void VDAPIENTRY setUVBundle(const VDVector2* uvs);

	/*
	 *	Get Normal[Index]
	 *	@Return
	 */
 	VDVector3 VDAPIENTRY getNormal(unsigned int index)const;

 	/*
 	 *
 	 */
 	void VDAPIENTRY setNormal(unsigned int index, const VDVector3& normal);

 	/*
 	 *	Get Normal Bundle Data.
	 *	@Return
 	 */
 	VDVertex* VDAPIENTRY getNormalBundle(void);

	VDVector3 VDAPIENTRY getTangent(unsigned int index)const;					/* Get Tanget[Index] */
 	void VDAPIENTRY setTangent(unsigned int index, const VDVector3& tangent);

 	VDVertex* VDAPIENTRY getTangentBundle(void);								/* Get Tanget Bundle Data. */

	VDVector3 VDAPIENTRY getBiNormal(unsigned int index)const;					/* Get biNormal[Index] */
 	void VDAPIENTRY setBiNormal(unsigned int index, const VDVector3& biNormal);

	VDVector3* VDAPIENTRY getBiNormalBundle(void);								/* Get biNormal Bundle Data. */

	VDVector3 VDAPIENTRY getBitTangent(unsigned int index)const;					/* Get biTangent[Index] */
 	void VDAPIENTRY setBiTangent(unsigned int index, const VDVector3& biTangent);

	VDVector3* VDAPIENTRY getBitTangentBundle(void);								/* Get biTangent Bundle Data. */



	void VDAPIENTRY getMeshData(void** data, unsigned int * size);

	VDHANDLE VDAPIENTRY getVBOBuffer(void);


	/*
	 *	Get indices by index.
	 */
	unsigned int VDAPIENTRY getIndices(unsigned int index);

	/*
	 *	Get i111ndices bundle
	 */
	unsigned char* VDAPIENTRY getIndicesBundle(void);

	/*
	 *	ReCalculate Bounding Box
	 */
	void VDAPIENTRY computeBBox(void);


	/*
	 *	Calculate Normal
	 */
	void VDAPIENTRY computeNormal(void);

	/*
	 *	set RenderFlag. what component is attached in form of unsigned int .
	 */
	void VDAPIENTRY setRenderFlag(const VDTypeInfo& type);	//

	void VDAPIENTRY setBufferFlag(unsigned int bufferFlag);
	unsigned int VDAPIENTRY getBufferFlag(void);


	/**
	 *
	 */
	void VDAPIENTRY assemblyMesh(void* vertexBuffer, unsigned int vertexStrideSize,
			unsigned int VertexDataSize, void* indicesData, unsigned int  indicesTypeSize,
			unsigned int IndicesDataSize, unsigned int meshBitFlag = 0x0);

public:

	/**
	 *	Get Offset value from Vertex
	 */
	static unsigned int VDAPIFASTENTRY getVertexOffset(VDMesh::MeshComponent meshComponent);

	/**
	 *
	 */
	static unsigned int getVertexStrideSize(VDMesh::MeshComponent meshComponent);

	//static unsigned int getIndicesSize(VDMesh::MeshComponent meshComponent);

	/**
	 *
	 *	@Return
	 */
	static VDMesh* VDAPIENTRY createMesh(void);

	/**
	 *
	 */
	static void VDAPIFASTENTRY assignMesh(VDMesh* mesh);

	/**
	 *
	 */
	static VDMesh* VDAPIENTRY findMesh(const char* meshName);


	/*
	 *	Get mapped pointer to client address space.
	 *	@Return pointer in client space of the object.
	 */
	static VDHANDLE VDAPIENTRY open(unsigned int target, unsigned int object, AccessMode access);

	/*
	 *	Close
	 *	@Return
	 */
	static bool VDAPIENTRY close(unsigned int target, unsigned int object);
};

#endif
