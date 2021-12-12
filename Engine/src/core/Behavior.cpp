#include <Core/VDBehavior.h>
#include <malloc.h>
#include <VDDef.h>
#include <cstring>


VDBehavior::VDBehavior() : VDComponent(){
	this->menable = Enable;
}

VDBehavior::~VDBehavior(){

}

void VDBehavior::enable(){
	this->menable |= Enable;
	this->onEnable();
}

void VDBehavior::disable(){
	this->menable = this->menable & ~Enable;
	this->onDisable();
}

bool VDBehavior::isDisabled()const{
	return (this->menable & VDBehavior::Enable) == 0;
}

bool VDBehavior::isEnabled()const{
	return (this->menable & VDBehavior::Enable) == VDBehavior::Enable ;
}

void VDBehavior::setState(unsigned int state){
	this->menable = state;
}

unsigned int VDBehavior::getState()const{
	return this->menable;
}

void VDBehavior::initializeComponent(){
	this->menable |= VDBehavior::Behavior;

}

void VDBehavior::onDestroy(){

}

void VDBehavior::onEnable(){

}

void VDBehavior::onDisable(){

}

void VDBehavior::onDetach(){

}





void VDBehavior::onDebugDisplay(){

}

VDBehavior* VDBehavior::copyComponent(unsigned int& dataSize){
	VDBehavior* BehaviorData = (VDBehavior*)malloc(sizeof(VDBehavior));
	memcpy(BehaviorData, this, sizeof(VDBehavior));
	dataSize = sizeof(VDBehavior);
	return BehaviorData;
}

void VDBehavior::instanceInitilize(){

}

void VDBehavior::onPreRender(){

}

void VDBehavior::reset(){return;}

void VDBehavior::onApplicationFocus() {
	return;
}
void VDBehavior::onApplicationUnFocus() {
	return;
}
void VDBehavior::onApplicationQuit() {
	return;
}
void VDBehavior::onApplicationPause() {
	return;
}

VDCustomBehavior* VDBehavior::getCustomBehavior() {
	return this->cast<VDCustomBehavior>();
}

int VDBehavior::isBehavior() const {
	return (this->menable & VDBehavior::Behavior);
}

int VDBehavior::isCustomBehavior() const {
	return (this->menable & VDBehavior::CustomBehavior);
}

void VDBehavior::setVTable(const void* data){
	VD_COPY_VPTR(this, data);
}

const void* VDBehavior::getVTable()const{
	return this;
}

// VDBehavior& VDBehavior::operator=(const VDBehavior& behavior){
// 	VDComponent::operator=(behavior);
// 	setVTable(behavior.getVTable());
// 	this->menable = behavior.menable;
// 	return *this;
// }
