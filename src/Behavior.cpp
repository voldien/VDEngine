#include <Core/VDBehavior.h>
#include <malloc.h>
#include <VDDef.h>
#include <cstring>


VDBehavior::VDBehavior(void) : VDComponent(){
	this->menable = eEnable;
}

VDBehavior::~VDBehavior(void){

}

void VDBehavior::enable(void){
	this->menable |= eEnable;
	this->onEnable();
}

void VDBehavior::disable(void){
	this->menable = this->menable & ~eEnable;
	this->onDisable();
}

bool VDBehavior::isDisabled(void)const{
	return (this->menable & VDBehavior::eEnable) == 0;
}

bool VDBehavior::isEnabled(void)const{
	return (this->menable & VDBehavior::eEnable) == VDBehavior::eEnable ;
}

void VDBehavior::setState(unsigned int state){
	this->menable = state;
}

unsigned int VDBehavior::getState(void)const{
	return this->menable;
}

void VDBehavior::initializeComponent(void){
	this->menable |= VDBehavior::eBehavior;

}

void VDBehavior::onDestroy(void){

}

void VDBehavior::onEnable(void){

}

void VDBehavior::onDisable(void){

}

void VDBehavior::onDetach(void){

}





void VDBehavior::onDebugDisplay(void){

}

VDBehavior* VDBehavior::copyComponent(unsigned int& dataSize){
	VDBehavior* BehaviorData = (VDBehavior*)malloc(sizeof(VDBehavior));
	memcpy(BehaviorData, this, sizeof(VDBehavior));
	dataSize = sizeof(VDBehavior);
	return BehaviorData;
}

void VDBehavior::instanceInitilize(void){

}

void VDBehavior::onPreRender(void){

}

void VDBehavior::reset(void){return;}

void VDBehavior::onApplicationFocus(void) {
	return;
}
void VDBehavior::onApplicationUnFocus(void) {
	return;
}
void VDBehavior::onApplicationQuit(void) {
	return;
}
void VDBehavior::onApplicationPause(void) {
	return;
}

VDCustomBehavior* VDBehavior::getCustomBehavior(void) {
	return this->cast<VDCustomBehavior>();
}

int VDBehavior::isBehavior(void) const {
	return (this->menable & VDBehavior::eBehavior);
}

int VDBehavior::isCustomBehavior(void) const {
	return (this->menable & VDBehavior::eCustomBehavior);
}

void VDBehavior::setVTable(const void* data){
	VD_COPY_VPTR(this, data);
}

const void* VDBehavior::getVTable(void)const{
	return this;
}

VDBehavior& VDBehavior::operator=(const VDBehavior& behavior){
	VDComponent::operator=(behavior);
	setVTable(behavior.getVTable());
	this->menable = behavior.menable;
	return *this;
}
