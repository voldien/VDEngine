#include <GL/glew.h>
#include <malloc.h>
#include <Rendering/VDBufferObject.h>
#include <Rendering/VDRenderingAPICache.h>
#include <Rendering/VDUniformBuffer.h>
#include <stddef.h>


VDUniformBuffer::VDUniformBuffer(void){
	this->mUniBuffer = 0;
	this->setTarget(eUniform);
}

VDUniformBuffer::VDUniformBuffer(unsigned int buffer){
	this->mUniBuffer = 0;
	this->setTarget(eUniform);
	this->setSize(buffer);
}

VDUniformBuffer::VDUniformBuffer(const VDUniformBuffer& buffer){
	this->mUniBuffer = buffer.mUniBuffer;
}

VDUniformBuffer::~VDUniformBuffer(void){

}

void VDUniformBuffer::release(void){
	if(this->isValid()){
		glDeleteBuffers(1, (const GLuint*)&this->mUniBuffer);
	}
}

bool VDUniformBuffer::isValid(void)const{
	return glIsBuffer(this->mUniBuffer) == GL_TRUE;
}

int VDUniformBuffer::getSize(void){
	int nBufferSize;
	this->bind();
	glGetBufferParameteriv(this->getTarget(), GL_BUFFER_SIZE, &nBufferSize);
	return nBufferSize;
}


void VDUniformBuffer::setSize(int size){
	if(!this->isValid()){
		glGenBuffers(1, (GLuint*)&this->mUniBuffer);
	}
	this->bind();
	glBufferData(this->getTarget(), size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(this->getTarget(), 0);
}

void VDUniformBuffer::setSize(unsigned int nBytes, void* pValues, unsigned int flag){
	this->bind();
	glBufferData(this->getTarget(), nBytes, pValues, flag);
	glBindBuffer(this->getTarget(), 0);
}


void VDUniformBuffer::write(const void* pbuffer, int rSize){
	this->bind();
	glBufferSubData(this->getTarget(), 0, rSize, pbuffer);
	glBindBuffer(this->getTarget(), 0);
}

void VDUniformBuffer::write(const void* pbuffer, int offset, int rSize){
	this->bind();
	glBufferSubData(this->getTarget(), offset, rSize, pbuffer);
	glBindBuffer(this->getTarget(), 0);
}

void* VDUniformBuffer::read(int rSize){
	void* data = malloc(rSize);
	this->bind();
	glGetBufferSubData(this->getTarget(), 0, rSize, data);
	return data;
}

void VDUniformBuffer::bind(void){
	VDRenderingAPICache::bindBuffer(this->getTarget(), this->mUniBuffer);
}

void VDUniformBuffer::bindBase(unsigned int index){
	this->bindbase = index;
	VDRenderingAPICache::bindBufferBase(this->getTarget(), index, this->mUniBuffer);
}

int VDUniformBuffer::getUniformBuffer(void)const{return this->mUniBuffer;}
