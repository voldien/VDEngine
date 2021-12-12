#include <Asset/VDAssetManager.h>
#include <Asset/VDAssetObject.h>
#include <stddef.h>

VDAssetObject::VDAssetObject() : VDObject(), fragcore::SmartReference(){
	//this->reference = VDSmartReference();
	//this->reference.setPointer(this);
}

VDAssetObject::VDAssetObject(const VDAssetObject& assetObject){
	*this = assetObject;
}

VDAssetObject::~VDAssetObject(){
	this->deincrement();
}

void VDAssetObject::release(){

}

// void VDAssetObject::increment(){
// 	this->getReference().increment();
// 	VDAssetManager::assignAsset((VDAssetObject*)this, nullptr);
// }

// void VDAssetObject::deincrement(){
// 	this->getReference().deincreemnt();
// 	if(this->getReference().getIndexCount() <= 0){

// 		/*	release only if object is not set to static flag.	*/
// 		if( !(this->getFlag() & VDObject::eStatic) ){
// 			this->release();
// 			VDAssetManager::releaseAsset(this);
// 		}
// 	}
// }


VDAssetObject& VDAssetObject::operator=(const VDAssetObject& object){
	VDObject::operator=(object);
	/**/
//	this->reference = object.reference;
	// this->getReference().increment();
	// this->getReference().setPointer(object.getReference().getPointer());
	return *this;
}
