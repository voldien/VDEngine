#include <Core/VDMatrix.h>
#include <GL/glew.h>
#include <stddef.h>
#include <Rendering/VDShader.h>
#include <VDSimpleType.h>
#include <vector>
#include<Core/Math.h>

/**
 *	View space coordinate.
 */
std::vector<VDMatrix4x4> VDMatrix::viewMatrix;

/**
 *	world space coordinate.
 */
std::vector<VDMatrix4x4> VDMatrix::modelMatrix;

/**
 *	projection space coordinate.
 */
std::vector<VDMatrix4x4> VDMatrix::projectionMatrix;

/**
 *
 */
unsigned int VDMatrix::mode = VDMatrix::MatrixSpace::Model;




void VDMatrix::init(){
	const int reservedsize = 16;

	VDMatrix::mode = VDMatrix::MatrixSpace::Model;
	VDMatrix::modelMatrix.reserve(reservedsize);
	VDMatrix::viewMatrix.reserve(reservedsize);
	VDMatrix::projectionMatrix.reserve(reservedsize);

	VDMatrix::modelMatrix.push_back(VDMatrix4x4::identity());
	VDMatrix::viewMatrix.push_back(VDMatrix4x4::identity());
	VDMatrix::projectionMatrix.push_back(VDMatrix4x4::identity());
}


void VDMatrix::pushMatrix(){
	switch(VDMatrix::mode){
	case VDMatrix::MatrixSpace::Model:
		VDMatrix::modelMatrix.push_back(VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1]);
		break;
	case VDMatrix::Projection:
		VDMatrix::projectionMatrix.push_back(VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() - 1]);
		break;
	case VDMatrix::MatrixSpace::View:
		VDMatrix::viewMatrix.push_back(VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1]);
		break;
	default:
		break;
	}
}

void VDMatrix::popMatrix(){
	switch(VDMatrix::mode){
	case VDMatrix::MatrixSpace::Model:
		if(VDMatrix::modelMatrix.size() > 1)
			VDMatrix::modelMatrix.pop_back();
		break;
	case VDMatrix::Projection:
		if(VDMatrix::projectionMatrix.size() > 1)
			VDMatrix::projectionMatrix.pop_back();
		break;
	case VDMatrix::MatrixSpace::View:
		if(VDMatrix::viewMatrix.size() > 1)
			VDMatrix::viewMatrix.pop_back();
		break;
	default:
		break;
	}
}


void VDMatrix::setMatrix(const VDMatrix4x4& matrix){
	switch(mode){
	case VDMatrix::MatrixSpace::View:
		VDMatrix::viewMatrix[getViewIndex()] = *(VDMatrix4x4*)&matrix;
		break;
	case VDMatrix::MatrixSpace::Model:
		VDMatrix::modelMatrix[getModelIndex()] = *(VDMatrix4x4*)&matrix;
		break;
	case VDMatrix::Projection:
		VDMatrix::projectionMatrix[getProjectIndex()] = *(VDMatrix4x4*)&matrix;
		break;
	}

}

void VDMatrix::matrixMode(unsigned int matrixMode){
	VDMatrix::mode = matrixMode;
}


void VDMatrix::identity(){
	if(VDMatrix::mode == VDMatrix::MatrixSpace::View){
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
	else if(mode == VDMatrix::MatrixSpace::Model){
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
	else{
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
}

void VDMatrix::identity(unsigned int flag){

	if(flag &  VDMatrix::MatrixSpace::Model){
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
	if(flag & VDMatrix::MatrixSpace::View){
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
	if(flag &  VDMatrix::Projection){
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
}

void VDMatrix::translate(float x, float y, float z){
	switch(VDMatrix::mode){
	case VDMatrix::MatrixSpace::Model:
		VDMatrix::modelMatrix[modelMatrix.size() -1] *= VDMatrix4x4::translate(x,y,z);
		break;
	case VDMatrix::MatrixSpace::View:
		VDMatrix::viewMatrix[viewMatrix.size() -1] *= VDMatrix4x4::translate(-x,-y,-z);
		break;
	case VDMatrix::Projection:
		break;
	default:
		break;
	}
}

void VDMatrix::translate(const VDVector3& translation){
	switch(VDMatrix::mode){
	case VDMatrix::MatrixSpace::Model:
		VDMatrix::modelMatrix[modelMatrix.size() -1] *= VDMatrix4x4::translate(translation);
		break;
	case VDMatrix::MatrixSpace::View:{
		VDMatrix::viewMatrix[viewMatrix.size() -1] *= VDMatrix4x4::translate(-translation);

		}break;
	case VDMatrix::Projection:
		break;
	default:
		break;
	}
}

void VDMatrix::scale(const VDVector3& scale){
	switch(VDMatrix::mode){
	case VDMatrix::MatrixSpace::Model:
		VDMatrix::modelMatrix[modelMatrix.size() -1] *= HCMatrix4x4::scale(scale);
		break;
	case VDMatrix::MatrixSpace::View:
		VDMatrix::viewMatrix[viewMatrix.size() -1] *= HCMatrix4x4::scale(-scale);
		break;
	case VDMatrix::Projection:
		break;
	}
}

void VDMatrix::scale(float x, float y, float z){
	switch(VDMatrix::mode){
	case VDMatrix::MatrixSpace::Model:
		VDMatrix::modelMatrix[modelMatrix.size() -1] *= HCMatrix4x4::scale(x,y,z);
		break;
	case VDMatrix::MatrixSpace::View:
		VDMatrix::viewMatrix[viewMatrix.size() -1] *= HCMatrix4x4::scale(-x,-y,-z);
		break;
	case VDMatrix::Projection:
		break;
	}
}

void VDMatrix::scale(float alignAxis){
	switch(VDMatrix::mode){
	case VDMatrix::MatrixSpace::Model:
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] *= HCMatrix4x4::scale(alignAxis,alignAxis,alignAxis);
		break;
	case VDMatrix::MatrixSpace::View:
		VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1] *= HCMatrix4x4::scale(-alignAxis,-alignAxis,-alignAxis);;
		break;
	default:
		break;
	}
}


void VDMatrix::rotation(const VDQuaternion& rotation){
	switch(VDMatrix::mode){
	case VDMatrix::MatrixSpace::Model:

		VDMatrix::modelMatrix[modelMatrix.size() -1] *= HCMatrix4x4::rotate( rotation);
		break;
	case VDMatrix::MatrixSpace::View:
		VDMatrix::viewMatrix[viewMatrix.size() -1] *= HCMatrix4x4::rotate( rotation.conjugate());
		break;
	}
}

void VDMatrix::perspective(float angle, float ratio, float Near, float Far){
	VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() - 1] *= HCMatrix4x4::perspective(
		fragcore::Math::deg2Rad(angle), ratio, Near, Far);
}

void VDMatrix::ortho(float left, float right, float bottom, float top, float Near, float Far){
	VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() -1] *= HCMatrix4x4::orth(left,right,bottom, top, Near, Far);
}


int VDMatrix::getIndex(unsigned int mode){
	switch(mode){
	case VDMatrix::MatrixSpace::Model:
		return getModelIndex();
	case VDMatrix::MatrixSpace::View:
		return getViewIndex();
	case VDMatrix::Projection:
		return getProjectIndex();
	default:
		return -1;
	}
}

int VDMatrix::getProjectIndex(){
	return VDMatrix::projectionMatrix.size() -1;
}

int VDMatrix::getViewIndex(){
	return VDMatrix::viewMatrix.size() -1;
}

int VDMatrix::getModelIndex(){
	return VDMatrix::modelMatrix.size() -1;
}

VDMatrix4x4 VDMatrix::getModelView(){
	return (VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1] * VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1]);
}

VDMatrix4x4 VDMatrix::getModel(){
	return VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1];
}

VDMatrix4x4 VDMatrix::getView(){
	return VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1];
}

VDMatrix4x4 VDMatrix::getProjection(){
	return VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() -1];
}

VDMatrix4x4 VDMatrix::getViewProjection(){
	return VDMatrix4x4(VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() -1] *
		VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1]);
}
VDMatrix4x4 VDMatrix::getModelViewProjection(){
	return VDMatrix4x4(VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() -1] *
		VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1] *
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1]);
}


void VDMatrix::uniformLocation(const VDShader* shader){
	if(shader == nullptr){
		return;
	}
		
	/*	TODO resolve for opengl 4.0 and previous	*/
	if(shader->getFlagSet() & VDShader::eShaderModelMatrix){
		glProgramUniformMatrix4fv(shader->getProgram(),shader->matrixInfo.modelMatrix, 1, GL_FALSE,
			&(VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1])[0][0]);
	}
	if(shader->getFlagSet()  & VDShader::eShaderViewMatrix){
		glProgramUniformMatrix4fv(shader->getProgram(),shader->matrixInfo.viewMatrix, 1, GL_FALSE,
			&VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1][0][0]);
	}
	if(shader->getFlagSet()  & VDShader::eShaderModelViewMatrix){
		glProgramUniformMatrix4fv(shader->getProgram(),shader->matrixInfo.modelViewMatrix, 1, GL_FALSE,
			&(VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1] * VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1])[0][0]);
	}
	if(shader->getFlagSet()  & VDShader::eShaderProjection){
		glProgramUniformMatrix4fv(shader->getProgram(),shader->matrixInfo.projectionMatrix, 1, GL_FALSE,
			&VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() -1][0][0]);
	}
	if(shader->getFlagSet() & VDShader::eShaderModelViewProjection){
		glProgramUniformMatrix4fv(shader->getProgram(), shader->matrixInfo.modelViewProjectionMatrix, 1, GL_FALSE,
		&(VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() - 1] *
		VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() - 1] *
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() - 1])[0][0]);
	}
}
