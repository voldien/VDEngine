#include"VDAudioGeometry.h"
#include"VDEngine.h"
#include<AL/al.h>
#include<AL/alc.h>

VDAudioGeometry::VDAudioGeometry(): VDBehavior(){
	this->audioGeometry = nullptr;
}

VDAudioGeometry::VDAudioGeometry(const VDAudioGeometry& audioGeometry) : VDBehavior(){
	*this = audioGeometry;
}

VDAudioGeometry::VDAudioGeometry(const VDMesh* mesh) : VDBehavior(){
	this->audioGeometry = nullptr;
}

void VDAudioGeometry::instanceInitilize(){

}

void VDAudioGeometry::initializeComponent(){
	this->initGeometry();
}

void VDAudioGeometry::onEnable(){

}

void VDAudioGeometry::onDisable(){

}

void VDAudioGeometry::onDestroy(){

}

VDBehavior* VDAudioGeometry::copyComponent(unsigned int& dataSize){
	VDAudioGeometry* audiogeometry = (VDAudioGeometry*)malloc(sizeof(VDAudioGeometry));
	memcpy(audiogeometry,this, sizeof(VDAudioGeometry));
	dataSize = sizeof(VDAudioGeometry);
	return (VDBehavior*)audiogeometry;
}

int VDAudioGeometry::initGeometry(){
	return 0;
}

int VDAudioGeometry::initGeometry(const VDMesh* mesh){
	return 0;
}

void VDAudioGeometry::setPosition(const VDVector3& position){

}

void VDAudioGeometry::setRotation(const VDQuaternion& rotation){

}
