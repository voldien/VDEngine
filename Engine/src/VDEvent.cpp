#include <Core/VDEngineCore.h>
#include <Core/VDEvent.h>
#include <DataStructure/VDVector.h>

VDEvent::VDEvent(void){
	VDEvent::getEvents()->push(this);
}

VDEvent::VDEvent(const VDEvent& event){
	*this = event;
}

VDEvent::~VDEvent(void){
	VDEvent::getEvents()->erase(this);
}


void VDEvent::onResize(int width, int height){

}

void VDEvent::onMouse(int x, int y, int button){

}


void VDEvent::onMouseMotion(int xmotion, int ymotion, VDInput::Button ){

}

void VDEvent::onMousePressed(VDInput::Button pressed){

}

void VDEvent::onMouseReleased(VDInput::Button released){

}

void VDEvent::onMouseWheel(int direction){

}

void VDEvent::onKeyPressed(unsigned int keycode){

}

void VDEvent::onKeyRelease(unsigned int keycode){

}

void VDEvent::onKey(unsigned int keycode){

}

unsigned int VDEvent::getNumEvents(void){
	return VDEvent::getEvents()->size();
}

vector<VDEvent*>* VDEvent::getEvents(void){
	return &engine.events;
}

VDEvent* VDEvent::getEvent(unsigned int index){
	return VDEvent::getEvents()->operator [](index);
}

