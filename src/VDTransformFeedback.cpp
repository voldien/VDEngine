#include <GL/glew.h>
#include <Rendering/VDTransformFeedback.h>

VDTransformFeedback::VDTransformFeedback(void) :  VDBufferObject(){
	this->trfb = 0;
	this->setTarget(GL_TRANSFORM_FEEDBACK);
}

VDTransformFeedback::VDTransformFeedback(unsigned int buffer){
	this->trfb = buffer;
	this->setTarget(GL_TRANSFORM_FEEDBACK);
}

VDTransformFeedback::VDTransformFeedback(const VDTransformFeedback& feedback){
	this->trfb = 0;
	this->setTarget(GL_TRANSFORM_FEEDBACK);
}

VDTransformFeedback::~VDTransformFeedback(void){

}

void VDTransformFeedback::release(void){
	if(this->isValid()){
		glDeleteTransformFeedbacks(1, (const GLuint*)this->trfb);
	}
}


bool VDTransformFeedback::isValid(void)const{
	return glIsTransformFeedback(this->trfb) == GL_TRUE;
}

int VDTransformFeedback::getSize(void) {
	return 0;
}

void VDTransformFeedback::setSize(unsigned int nBytes, void* pValues, unsigned int flag){

}

void VDTransformFeedback::bind(void){
	glBindTransformFeedback(this->getTarget(), this->trfb);
}

void VDTransformFeedback::unBind(void){
	glBindTransformFeedback(this->getTarget(), 0);
}
