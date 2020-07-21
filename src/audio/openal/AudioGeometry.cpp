#include"VDAudioGeometry.h"
#include"VDEngine.h"
#include<AL/al.h>
#include<AL/alc.h>

VDAudioGeometry::VDAudioGeometry(void): VDBehavior(){
	this->audioGeometry = NULL;
}

VDAudioGeometry::VDAudioGeometry(const VDAudioGeometry& audioGeometry) : VDBehavior(){
	*this = audioGeometry;
}

VDAudioGeometry::VDAudioGeometry(const VDMesh* mesh) : VDBehavior(){
	this->audioGeometry = NULL;
}

void VDAudioGeometry::instanceInitilize(void){

}

void VDAudioGeometry::initializeComponent(void){
	this->initGeometry();
}

void VDAudioGeometry::onEnable(void){

}

void VDAudioGeometry::onDisable(void){

}

void VDAudioGeometry::onDestroy(void){

}

VDBehavior* VDAudioGeometry::copyComponent(unsigned int& dataSize){
	VDAudioGeometry* audiogeometry = (VDAudioGeometry*)malloc(sizeof(VDAudioGeometry));
	memcpy(audiogeometry,this, sizeof(VDAudioGeometry));
	dataSize = sizeof(VDAudioGeometry);
	return (VDBehavior*)audiogeometry;
}

int VDAudioGeometry::initGeometry(void){
	return 0;
}

int VDAudioGeometry::initGeometry(const VDMesh* mesh){
	return 0;
}

void VDAudioGeometry::setPosition(const VDVector3& position){

}

void VDAudioGeometry::setRotation(const VDQuaternion& rotation){

}
