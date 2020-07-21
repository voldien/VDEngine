#include <Audio/VDAudioListener.h>
#include <Core/VDBehavior.h>
#include <Core/VDComponent.h>
#include <Core/VDDebug.h>
#include <Core/VDInput.h>
#include <Core/VDObject.h>
#include <Core/VDTime.h>
#include <Misc/VDMouseLook.h>
#include <Physic/VDCharacterController.h>
#include <Physic/VDCharacterControllerHit.h>
#include <Physic/VDRaycastHit.h>
#include <Physic/VDRigidBody.h>
#include <Rendering/VDCamera.h>
#include <stddef.h>
#include <Scene/VDCameraController.h>
#include <Scene/VDGameObject.h>
#include <Scene/VDTransform.h>
#include <SDL2/SDL_keycode.h>
#include <vl/Vector3.h>
#include <VDSimpleType.h>

VDCameraController::VDCameraController(void) : VDCustomBehavior(){
	this->sensityX = 0.15f;
	this->sensityY = 0.4f;
	this->speed = 9.5f;
	this->maxSpeed = 10.0f;
	this->gravity = 9.82f;
	this->characterController = NULL;
	this->gravity = 1;
	this->camera = NULL;
	this->flag = 0;
}

VDCameraController::VDCameraController(const VDCameraController& controller){
	*this = controller;
}

VDCameraController::~VDCameraController(void){

}

void VDCameraController::onAwake(void){

	VDGameObject* cameraObject = VDGameObject::createGameObject();
	this->camera = cameraObject->addComponet<VDCamera>();
	cameraObject->setName("CameraController MainCamera");
	cameraObject->addComponet<VDAudioListener>();
	cameraObject->addComponet<VDMouseLook>();
	this->transform()->addChild(cameraObject->transform());

	/*
	this->gameObject()->addComponet<VDLight>();

	this->light()->setType(VDLight::eSpot);
	this->light()->setIntensity( 0.7f );
	this->light()->setRange( 30.0f );
	this->light()->setColor( VDColor::white() );
	this->light()->setState(0);
	this->transform()->setPosition(VDVector3(0,0,0));
*/
	this->characterController = this->gameObject()->addComponet<VDCharacterController>();
	cameraObject->transform()->setLocalPosition(VDVector3(0.0f, this->characterController->getHeight() / 2.0f, 0.0f));

	//this->gameObject()->addComponet<VDRenderer>()->setMesh(VDMesh::createCube(0.5f, 1, VDTYPEMI(VDVertex,unsigned char)));
}


void VDCameraController::fixedUpdate(void){
	VDRaycastHit hit;
	VDVector3 deltaMotion = VDVector3(0.0f);

	deltaMotion += this->camera->transform()->transformDirection(VDVector3::forward()) * VDInput::getAxis(VDInput::eVertical) * this->speed;
	deltaMotion += this->camera->transform()->transformDirection(VDVector3::right()) * VDInput::getAxis(VDInput::eHorizontal) * this->speed;

	if(VDInput::isKeyDown(SDLK_n) || VDInput::isKeyDown(SDLK_m)){
		deltaMotion *= 2.15f;
	}
	if(this->characterController->getCollisionFlag() == 0 ){
		deltaMotion[1] -= gravity;
	}
	if(VDInput::isKey(SDLK_SPACE)){
		deltaMotion[1] += gravity * 10;
	}
	if(VDInput::isKey(SDLK_z)){
		deltaMotion[1] -= gravity * 10;
	}


	if(VDDebug::isDebugEnabled()){
//		if(engine.event->key.code == EXK_k){
//			VDCamera::getCurrentCamera()->setPolygoneMode(  VDCamera::eWireFrame );
//		}
		if(VDInput::isKey(SDLK_t)){
			this->characterController->setState(0);
			VDCamera::getCurrentCamera()->setPolygoneMode(VDCamera::eTriangle);
		}
		if(VDInput::isKey(SDLK_y)){
			this->characterController->setState(1);
		}
		if(VDInput::isKey(SDLK_t)){
			this->characterController->setState(0);
		}


		if(VDInput::isKey(SDLK_f)){

		}

		/*
		if(VDInput::isKey(EXK_F1)){
			this->camera->setDebugMode(VDCamera::eWireFrame,1);
		}
		if(VDInput::isKey(EXK_F2)){
			this->camera->setDebugMode(VDCamera::eWireFrame,0);
		}
		*/
		if(VDInput::isKey(SDLK_F3)){

		}
		if(VDInput::isKey(SDLK_F4)){

		}
		if(VDInput::isKey(SDLK_F5)){

		}
		if(VDInput::isKey(SDLK_F6)){

		}

	}


	this->characterController->move(deltaMotion * VDTime::deltaTime());
	VDRay ray = this->camera->screenPointToRay(VDVector2(VDInput::x(), VDInput::y()));
}


void VDCameraController::onCharacterController(VDCharacterControllerHit& hit){
	if(hit.rigidBody()){
		hit.rigidBody()->addForce(hit.moveDirection() * 20);
	}
}

void VDCameraController::setCharacterMode(unsigned int mode, int enabled){
	this->flag = mode;
}
