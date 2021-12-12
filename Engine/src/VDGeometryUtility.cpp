#include <GL/glew.h>
#include <malloc.h>
#include <stddef.h>
#include <Utility/VDGeometryUtility.h>
#include <VDSimpleType.h>
#include <climits>

void VDGeometryUtility::scale(VDMesh* mesh, const VDVector3& size){
	float* data = (float*)VDMesh::open(GL_ARRAY_BUFFER, mesh->getVBO(), VDMesh::AccessMode::eReadWrite);
	VDVertex* vertices = mesh->getVertexBundle();
	for(int x = 0; x < mesh->getVertexCount(); x++){
		vertices[x].x *= size.x();
		vertices[x].y *= size.y();
		vertices[x].z *= size.z();
	}

	for(int x = 0; x < mesh->getVertexCount(); x++){
		mesh->setVertex(x, *(VDVector3*)&vertices[x]);
	}
	VDMesh::close(GL_ARRAY_BUFFER, mesh->getVBO());
	free(vertices);
}



void VDGeometryUtility::computeAABB(const VDVertex* vertices, unsigned int stride, int count, VDVector3* center, VDVector3* size){
	float MaxX = 0.0f, MinX = 0.0f, MaxY = 0.0f, MinY = 0.0f, MaxZ = 0.0f,MinZ = 0.0f;
	float* vertex = (float*)vertices;

	stride /= sizeof(float);
	for(unsigned int x = 0; x < count; x++){


		if(vertex[x * stride] > MaxX){
			MaxX = vertex[x * stride];
		}
		if(vertex[x * stride] < MinX){
			MinX = vertex[x * stride];
		}

		if(vertex[x * stride + 1] > MaxY){
			MaxY = vertex[x * stride + 1];
		}
		if(vertex[x * stride + 1] < MinY){
			MinY = vertex[x * stride + 1];
		}
		if(vertex[x * stride + 2] > MaxZ){
			MaxZ = vertex[x * stride + 2];
		}
		if(vertex[x * stride + 2] < MinZ){
			MinZ = vertex[x * stride + 2];
		}


	}
	if(size != nullptr){
		size[0] = (float)(MaxX - MinX);
		size[1] = (float)(MaxY - MinY);
		size[2] = (float)(MaxZ - MinZ);
	}
	if(center != nullptr){
		center[0] = (MinX + MaxX) / 2.0f;
		center[1] = (MinY + MaxY) / 2.0f;
		center[2] = (MinZ + MaxZ) / 2.0f;
	}

}

void VDGeometryUtility::computeAABB(const VDVertex* vertices, unsigned int stride, int count, VDAABB* bounds){
	VDGeometryUtility::computeAABB(vertices, stride, count, &(*bounds)[0], &(*bounds)[1]);
}

void VDGeometryUtility::computeOBB(const VDVector3* vertices, int count, VDOBB* obb, bool analytic){

}


unsigned int VDGeometryUtility::getindexBufferSize(unsigned int IndicesCount){
	if(IndicesCount < UCHAR_MAX)
		return sizeof(unsigned char);
	else if(IndicesCount < USHRT_MAX)
		return sizeof(unsigned short);
	else if(IndicesCount < UINT_MAX)
		return sizeof(unsigned int);
	else if(IndicesCount < ULONG_MAX)
		return sizeof(unsigned long int);
	else if(IndicesCount < ULLONG_MAX)
		return sizeof(unsigned long long int);
	else
		return nullptr;
}

unsigned int VDGeometryUtility::getIndicesSize(unsigned int IndicesCount){
	if(IndicesCount < UCHAR_MAX)
		return sizeof(unsigned char);
	else if(IndicesCount < USHRT_MAX)
		return sizeof(unsigned short);
	else if(IndicesCount < UINT_MAX)
		return sizeof(unsigned int);
	else if(IndicesCount < ULONG_MAX)
		return sizeof(unsigned long int);
	else if(IndicesCount < ULLONG_MAX)
		return sizeof(unsigned long long int);
	else
		return nullptr;
}
