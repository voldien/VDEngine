#include"VDCharacterController.h"


VDCharacterController::VDCharacterController(){

}

VDCharacterController::VDCharacterController(VDCharacterController& controller){

}


void VDCharacterController::instanceInitilize(){}
void VDCharacterController::onEnable(){}
void VDCharacterController::onDisable(){}
void VDCharacterController::initializeComponent(){}
void VDCharacterController::onDestroy(){}
VDBehavior* VDCharacterController::copyComponent(unsigned int& dataSize){}



/*
 *
 */
int VDCharacterController::setShape(CharacterType type){}

/*
 *
 */
VDCharacterController::CharacterType VDCharacterController::getShapeType()const{}

/*
 *
 */
unsigned int VDCharacterController::getCollisionFlag()const{}

/*
 *
 */
int VDCharacterController::move(const VDVector3& motion){
	this->transform()->setPosition( this->transform()->getPosition() + motion);
	return 0;
}


void VDCharacterController::setMinMove(float movement){}


float VDCharacterController::getMinMove()const{}



void VDCharacterController::setRadius(float radius){}


float VDCharacterController::getRadius()const{}


float VDCharacterController::getHeight()const{}


void VDCharacterController::setHeight(float height){}
