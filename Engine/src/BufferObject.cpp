#include <Rendering/VDBufferObject.h>

VDBufferObject::VDBufferObject(void){
	this->bindbase = 0;
	this->target = 0;
}
VDBufferObject::~VDBufferObject(void){
	this->release();
}


void VDBufferObject::release(void){

}
