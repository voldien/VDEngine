#include <GL/glew.h>
#include <Rendering/VDRenderBuffer.h>


VDRenderBuffer::VDRenderBuffer() : VDAssetObject(){
	this->setRenderId(0);
	glGenRenderbuffers(1, &this->renderer);
}

VDRenderBuffer::VDRenderBuffer(unsigned int buffer) : VDAssetObject(){
	this->setRenderId(buffer);
}

VDRenderBuffer::VDRenderBuffer(const VDRenderBuffer& buffer){
	this->setRenderId(buffer.renderer);
}

void VDRenderBuffer::release(){
	glDeleteRenderbuffers(1, &this->renderer);
}

void VDRenderBuffer::bind(){
	glBindRenderbuffer(GL_RENDERBUFFER, this->renderer);
}


void VDRenderBuffer::unbind(){
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

bool VDRenderBuffer::isValid()const{
	return glIsRenderbuffer(this->renderer) == GL_TRUE;

}

VDTexture::TextureFormat VDRenderBuffer::getInternalFormat(){
	VDTexture::TextureFormat internal;
	this->bind();
	glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_INTERNAL_FORMAT, (GLint*)&internal);
	return internal;
}


void VDRenderBuffer::setStorage(unsigned int width, unsigned int height, VDTexture::TextureFormat format){
	if(!this->isValid()){
		glGenRenderbuffers(1, &this->renderer);
	}
	this->bind();
	glRenderbufferStorage(GL_RENDERBUFFER, format, width, height);
}

void VDRenderBuffer::setSampleStorage(unsigned int samples, unsigned int width, unsigned int height, VDTexture::TextureFormat format){
	if(!isValid()){
		glGenRenderbuffers(1, &this->renderer);
	}
	this->bind();
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, format, width, height);
}
