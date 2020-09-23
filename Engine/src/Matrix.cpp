#include <Core/VDMatrix.h>
#include <GL/glew.h>
#include <Misc/VDMath.h>
#include <stddef.h>
#include <Rendering/VDShader.h>
#include <VDSimpleType.h>
#include <vector>


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
unsigned int VDMatrix::mode = VDMatrix::eModel;




void VDMatrix::init(void){
	const int reservedsize = 16;

	VDMatrix::mode = VDMatrix::eModel;
	VDMatrix::modelMatrix.reserve(reservedsize);
	VDMatrix::viewMatrix.reserve(reservedsize);
	VDMatrix::projectionMatrix.reserve(reservedsize);

	VDMatrix::modelMatrix.push_back(VDMatrix4x4::identity());
	VDMatrix::viewMatrix.push_back(VDMatrix4x4::identity());
	VDMatrix::projectionMatrix.push_back(VDMatrix4x4::identity());
}


void VDMatrix::pushMatrix(void){
	switch(VDMatrix::mode){
	case VDMatrix::eModel:
		VDMatrix::modelMatrix.push_back(VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1]);
		break;
	case VDMatrix::eProjection:
		VDMatrix::projectionMatrix.push_back(VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() - 1]);
		break;
	case VDMatrix::eView:
		VDMatrix::viewMatrix.push_back(VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1]);
		break;
	default:
		break;
	}
}

void VDMatrix::popMatrix(void){
	switch(VDMatrix::mode){
	case VDMatrix::eModel:
		if(VDMatrix::modelMatrix.size() > 1)
			VDMatrix::modelMatrix.pop_back();
		break;
	case VDMatrix::eProjection:
		if(VDMatrix::projectionMatrix.size() > 1)
			VDMatrix::projectionMatrix.pop_back();
		break;
	case VDMatrix::eView:
		if(VDMatrix::viewMatrix.size() > 1)
			VDMatrix::viewMatrix.pop_back();
		break;
	default:
		break;
	}
}


void VDMatrix::setMatrix(const VDMatrix4x4& matrix){
	switch(mode){
	case VDMatrix::eView:
		VDMatrix::viewMatrix[getViewIndex()] = *(VDMatrix4x4*)&matrix;
		break;
	case VDMatrix::eModel:
		VDMatrix::modelMatrix[getModelIndex()] = *(VDMatrix4x4*)&matrix;
		break;
	case VDMatrix::eProjection:
		VDMatrix::projectionMatrix[getProjectIndex()] = *(VDMatrix4x4*)&matrix;
		break;
	}

}

void VDMatrix::matrixMode(unsigned int matrixMode){
	VDMatrix::mode = matrixMode;
}


void VDMatrix::identity(void){
	if(VDMatrix::mode == VDMatrix::eView){
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
	else if(mode == VDMatrix::eModel){
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
	else{
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
}

void VDMatrix::identity(unsigned int flag){

	if(flag &  VDMatrix::eModel){
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
	if(flag & VDMatrix::eView){
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
	if(flag &  VDMatrix::eProjection){
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] = VDMatrix4x4::identity();
	}
}

void VDMatrix::translate(float x, float y, float z){
	switch(VDMatrix::mode){
	case VDMatrix::eModel:
		VDMatrix::modelMatrix[modelMatrix.size() -1] *= VDMatrix4x4::translate(x,y,z);
		break;
	case VDMatrix::eView:
		VDMatrix::viewMatrix[viewMatrix.size() -1] *= VDMatrix4x4::translate(-x,-y,-z);
		break;
	case VDMatrix::eProjection:
		break;
	default:
		break;
	}
}

void VDMatrix::translate(const VDVector3& translation){
	switch(VDMatrix::mode){
	case VDMatrix::eModel:
		VDMatrix::modelMatrix[modelMatrix.size() -1] *= VDMatrix4x4::translate(translation);
		break;
	case VDMatrix::eView:{
		VDMatrix::viewMatrix[viewMatrix.size() -1] *= VDMatrix4x4::translate(-translation);

		}break;
	case VDMatrix::eProjection:
		break;
	default:
		break;
	}
}

void VDMatrix::scale(const VDVector3& scale){
	switch(VDMatrix::mode){
	case VDMatrix::eModel:
		VDMatrix::modelMatrix[modelMatrix.size() -1] *= HCMatrix4x4::scale(scale);
		break;
	case VDMatrix::eView:
		VDMatrix::viewMatrix[viewMatrix.size() -1] *= HCMatrix4x4::scale(-scale);
		break;
	case VDMatrix::eProjection:
		break;
	}
}

void VDMatrix::scale(float x, float y, float z){
	switch(VDMatrix::mode){
	case VDMatrix::eModel:
		VDMatrix::modelMatrix[modelMatrix.size() -1] *= HCMatrix4x4::scale(x,y,z);
		break;
	case VDMatrix::eView:
		VDMatrix::viewMatrix[viewMatrix.size() -1] *= HCMatrix4x4::scale(-x,-y,-z);
		break;
	case VDMatrix::eProjection:
		break;
	}
}

void VDMatrix::scale(float alignAxis){
	switch(VDMatrix::mode){
	case VDMatrix::eModel:
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1] *= HCMatrix4x4::scale(alignAxis,alignAxis,alignAxis);
		break;
	case VDMatrix::eView:
		VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1] *= HCMatrix4x4::scale(-alignAxis,-alignAxis,-alignAxis);;
		break;
	default:
		break;
	}
}


void VDMatrix::rotation(const VDQuaternion& rotation){
	switch(VDMatrix::mode){
	case VDMatrix::eModel:

		VDMatrix::modelMatrix[modelMatrix.size() -1] *= HCMatrix4x4::rotate( rotation);
		break;
	case VDMatrix::eView:
		VDMatrix::viewMatrix[viewMatrix.size() -1] *= HCMatrix4x4::rotate( rotation.conjugate());
		break;
	}
}

void VDMatrix::perspective(float angle, float ratio, float Near, float Far){
	VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() -1] *= HCMatrix4x4::perspective(
			VDMath::deg2Rad(angle), ratio, Near, Far);
}

void VDMatrix::ortho(float left, float right, float bottom, float top, float Near, float Far){
	VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() -1] *= HCMatrix4x4::orth(left,right,bottom, top, Near, Far);
}


int VDMatrix::getIndex(unsigned int mode){
	switch(mode){
	case VDMatrix::eModel:
		return getModelIndex();
	case VDMatrix::eView:
		return getViewIndex();
	case VDMatrix::eProjection:
		return getProjectIndex();
	default:
		return -1;
	}
}

int VDMatrix::getProjectIndex(void){
	return VDMatrix::projectionMatrix.size() -1;
}

int VDMatrix::getViewIndex(void){
	return VDMatrix::viewMatrix.size() -1;
}

int VDMatrix::getModelIndex(void){
	return VDMatrix::modelMatrix.size() -1;
}

VDMatrix4x4 VDMatrix::getModelView(void){
	return (VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1] * VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1]);
}

VDMatrix4x4 VDMatrix::getModel(void){
	return VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1];
}

VDMatrix4x4 VDMatrix::getView(void){
	return VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1];
}

VDMatrix4x4 VDMatrix::getProjection(void){
	return VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() -1];
}

VDMatrix4x4 VDMatrix::getViewProjection(void){
	return VDMatrix4x4(VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() -1] *
		VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1]);
}
VDMatrix4x4 VDMatrix::getModelViewProjection(void){
	return VDMatrix4x4(VDMatrix::projectionMatrix[VDMatrix::projectionMatrix.size() -1] *
		VDMatrix::viewMatrix[VDMatrix::viewMatrix.size() -1] *
		VDMatrix::modelMatrix[VDMatrix::modelMatrix.size() -1]);
}


void VDMatrix::uniformLocation(const VDShader* shader){
	if(shader == NULL){
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
