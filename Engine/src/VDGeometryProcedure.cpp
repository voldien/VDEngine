#include <Core/VDTypes.h>
#include <GL/glew.h>
#include <malloc.h>
#include <Rendering/VDRenderingAPICache.h>
#include <stddef.h>
#include <Utility/VDGeometryProcedure.h>
#include <VDSimpleType.h>

VDMesh* VDGeometryProcedure::createQuad(float Width, float Height, unsigned int SubDivision, bool PivotPoint){

	unsigned char* vertexData = NULL;
	unsigned char* indicesData = NULL;
	unsigned int vertexSize = 0;
	unsigned int indicesSize = 0;
	VDMesh* quadMesh = NULL;

	float g_vertex_buffer_data[] = {
				/**/
				-1.0f, -1.0f, 0,
				0.0f,0.0f,
				0, 0, -1,
				1, 0, 0,

				/**/
				-1.0f, 1.0f, 0,
				0.0f,0.0f,
				0, 0, 1,
				1, 0, 0,

				/**/
				1.0f , 1.0f, 0,
				0.0f,0.0f,
				0, 0, 1,
				1, 0, 0,


				/**/
				1.0f , 1.0f, 0,
				0.0f,0.0f,
				0, 0, 1,
				1, 0, 0,

				/**/
				1.0f, -1.0f, 0,
				0.0f,0.0f,
				0, 0, 1,
				1, 0, 0,
				/**/
				-1.0f, -1.0f, 0,
				0.0f,0.0f,
				0, 0, -1,
				1, 0, 0,

	};

	quadMesh = VDMesh::createMesh();
	glGenBuffers(1, &quadMesh->meshdesc.VBO);
	VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER, quadMesh->meshdesc.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	quadMesh->strideSize = 44;
	quadMesh->vertexCount = sizeof(g_vertex_buffer_data) / ( quadMesh->strideSize);

	quadMesh->flag |= VDMesh::eVertex | VDMesh::eTextureCoord | VDMesh::eNormal | VDMesh::eTangent;
	quadMesh->flag |= VDMesh::eVBO;
	quadMesh->nSizeFlag = GL_UNSIGNED_BYTE;
	quadMesh->setDrawMode(GL_TRIANGLES);

	return quadMesh;
}

VDMesh* VDGeometryProcedure::createCube(float size, unsigned int subDivision){
	unsigned char* vertexData;
	unsigned char* indicesData;
	unsigned int vertexSize, indicesSize;
	VDMesh* cubeMesh = NULL;


	/*	TODO make it use draw elements instead, with GL_TRIANGLE_STRIP*/
	static const float g_vertex_buffer_data[] = {
	      -1.0f,-1.0f,-1.0f, // triangle 1 : begin
	      -1.0f,-1.0f, 1.0f,
	      -1.0f, 1.0f, 1.0f, // triangle 1 : end
	      1.0f, 1.0f,-1.0f, // triangle 2 : begin
	      -1.0f,-1.0f,-1.0f,
	      -1.0f, 1.0f,-1.0f, // triangle 2 : end
	     1.0f,-1.0f, 1.0f,
	     -1.0f,-1.0f,-1.0f,
	     1.0f,-1.0f,-1.0f,
	     1.0f, 1.0f,-1.0f,
	     1.0f,-1.0f,-1.0f,
	    -1.0f,-1.0f,-1.0f,
	     -1.0f,-1.0f,-1.0f,
	     -1.0f, 1.0f, 1.0f,
	     -1.0f, 1.0f,-1.0f,
	     1.0f,-1.0f, 1.0f,
	     -1.0f,-1.0f, 1.0f,
	     -1.0f,-1.0f,-1.0f,
	     -1.0f, 1.0f, 1.0f,
	     -1.0f,-1.0f, 1.0f,
	     1.0f,-1.0f, 1.0f,
	     1.0f, 1.0f, 1.0f,
	     1.0f,-1.0f,-1.0f,
	     1.0f, 1.0f,-1.0f,
	     1.0f,-1.0f,-1.0f,
	     1.0f, 1.0f, 1.0f,
	     1.0f,-1.0f, 1.0f,
	     1.0f, 1.0f, 1.0f,
	     1.0f, 1.0f,-1.0f,
	     -1.0f, 1.0f,-1.0f,
	     1.0f, 1.0f, 1.0f,
	     -1.0f, 1.0f,-1.0f,
	     -1.0f, 1.0f, 1.0f,
	     1.0f, 1.0f, 1.0f,
	     -1.0f, 1.0f, 1.0f,
	     1.0f,-1.0f, 1.0f
	};

	cubeMesh = VDMesh::createMesh();

	glGenBuffers(1,&cubeMesh->meshdesc.VBO);
	VDRenderingAPICache::bindBuffer(GL_ARRAY_BUFFER,cubeMesh->meshdesc.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),g_vertex_buffer_data, GL_STATIC_DRAW);
	cubeMesh->vertexCount = sizeof(g_vertex_buffer_data) / (sizeof(float) * 3);
	cubeMesh->strideSize = 12;
	cubeMesh->flag |= VDMesh::eVertex | VDMesh::eVBO;

	return cubeMesh;
}


VDMesh* VDGeometryProcedure::createBoundingBox(void){
	unsigned char* vdata = NULL;
	unsigned char* idata = NULL;
	VDMesh* boundingBox = NULL;

	return boundingBox;
}
