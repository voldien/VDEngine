#include"VDCharacterController.h"


VDCharacterController::VDCharacterController(void){

}

VDCharacterController::VDCharacterController(VDCharacterController& controller){

}


void VDCharacterController::instanceInitilize(void){}
void VDCharacterController::onEnable(void){}
void VDCharacterController::onDisable(void){}
void VDCharacterController::initializeComponent(void){}
void VDCharacterController::onDestroy(void){}
VDBehavior* VDCharacterController::copyComponent(unsigned int& dataSize){}



/*
 *
 */
int VDCharacterController::setShape(CharacterType type){}

/*
 *
 */
VDCharacterController::CharacterType VDCharacterController::getShapeType(void)const{}

/*
 *
 */
unsigned int VDCharacterController::getCollisionFlag(void)const{}

/*
 *
 */
int VDCharacterController::move(const VDVector3& motion){
	this->transform()->setPosition( this->transform()->getPosition() + motion);
	return 0;
}


void VDCharacterController::setMinMove(float movement){}


float VDCharacterController::getMinMove(void)const{}



void VDCharacterController::setRadius(float radius){}


float VDCharacterController::getRadius(void)const{}


float VDCharacterController::getHeight(void)const{}


void VDCharacterController::setHeight(float height){}
