#include <Core/VDDebug.h>
#include <Core/VDEngine.h>
#include <Core/VDInput.h>
#include <DataStructure/VDPoint.h>
#include <stddef.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_mouse.h>
#include <VDSimpleType.h>

int xdelta;
int ydelta;
VDPoint pmdelta;
VDPoint mdelta;

float VDInput::getAxis(unsigned int AxisFlag){


	// if(SDL_GetKeyboardFocus() == VDEngine::getWindow()){
	// 	switch(AxisFlag){
	// 	//case MOUSE_X:
	// 	//	return (float)ExGetMouseDeltaX();
	// 	//case MOUSE_Y:
	// 	//	return (float)ExGetMouseDeltaY();
	// 	//case MOUSE_MAGNITUDE:
	// 	//	return ExGetMouseMagnitude();
	// 	//case JOYSTICK_1_X:
	// 	//	//return (float)ExGetJoyStickDirection(0).x / ExGetJoyStickMagnitude(0);
	// 	//case JOYSTICK_1_Y:
	// 	//	return (float)ExGetJoyStickDirection(0).y / ExGetJoyStickMagnitude(0);
	// 	//case JOYSTICK_2_X:
	// 	//	return (float)ExGetJoyStickDirection(1).x / ExGetJoyStickMagnitude(1);
	// 	//case YOUSTICK_2_Y:
	// 	//	return (float)ExGetJoyStickDirection(1).y / ExGetJoyStickMagnitude(1);
	// 	//case JOYSTICK_1_MAGNITUDE:
	// 	//	return ExGetJoyStickMagnitude(0);
	// 	//case JOYSTICK_2_MAGNITUDE:
	// 	//	return ExGetJoyStickMagnitude(1);
	// 	//case MOUSE0:
	// 		//return (float)ExGetButton(MOUSE0) || ExIsJoyStickButton(0,0);
	// 	//case MOUSE1:
	// 	//	return (float)ExGetButton(MOUSE1) || ExIsJoyStickButton(MOUSE1,0);
	// 	//case MOUSE2:
	// 	//	return (float)ExGetButton(MOUSE2) || ExIsJoyStickButton(MOUSE2,0);
	// 	//case MOTION_X:
	// 	//	return (ExgetLDirection(0).x * ExgetLMagnitude(0));
	// 	//case MOTION_Y:
	// 	//	return (ExgetLDirection(0).y * ExgetLMagnitude(0));
	// 	case VDInput::eVertical:
	// 		return   ((float)VDInput::isKeyDown(SDLK_w) - (float)VDInput::isKeyDown(SDLK_s));
	// 	case VDInput::eHorizontal:
	// 		return  ((float)VDInput::isKeyDown(SDLK_d) - (float)VDInput::isKeyDown(SDLK_a));
	// 	case VDInput::eCAMERA_X:
	// 		return 0;
	// 		//return ExGetMouse;
	// 	case VDInput::eCAMERA_Y:
	// 		return 0;
	// 	case VDInput::eJump:
	// 		return (float)((VDInput::isKeyDown(SDLK_SPACE)) ); // | ExXIsPadDown(EXK_XINPUT_GAMEPAD_A,0));
	// 	case VDInput::eFire1:
	// 		return (float)((VDInput::getButton(VDInput::eRight)) ) ;// | ExXIsPadDown(XINPUT_GAMEPAD_X,0));
	// 	case VDInput::eFire2:
	// 		return (float)((VDInput::getButton(VDInput::eLeft)) ); // | ExXIsPadDown(XINPUT_GAMEPAD_B,0));
	// 	case VDInput::eFire3:
	// 		return (float)((VDInput::getButton(VDInput::eMiddle)) ); // | ExXIsPadDown(XINPUT_GAMEPAD_Y,0));
	// 	default:
	// 		return 0.0f;
	// 	}
	// }
	return 0.0f;
}

VDPoint VDInput::location(){
	VDPoint p;
	SDL_GetMouseState(&p[0],&p[1]);
	return p;
}

VDPoint VDInput::mousePosition(){
	VDPoint p;

	// if(VDEngine::getWindow() != SDL_GetKeyboardFocus()){
	// 	return VDPoint(0);
	// }

	SDL_GetMouseState(&p[0], &p[1]);

	return p;
}

int VDInput::x(){
	int x,y;
	/**/
	// if(VDEngine::getWindow() != SDL_GetKeyboardFocus()){
	// 	return 0;
	// }
	/**/
	SDL_GetMouseState(&x, &y);
	return x;
}

int VDInput::y(){
	int x,y;
	// if(VDEngine::getWindow() != SDL_GetKeyboardFocus()){
	// 	return 0;
	// }

	SDL_GetMouseState(&x, &y);
	return y;
}

int VDInput::deltaX(){
	return mdelta.x();
}
int VDInput::deltaY(){
	return mdelta.y();
}

VDVector2 VDInput::getMotion(){
	return VDVector2(mdelta.x(), mdelta.y());
}

int VDInput::isKeyDown(SDL_Keycode keyCode){
	SDL_GetKeyboardState(nullptr)[keyCode];

	return 0; //return ExIsKeyDown(keyCode) && (VDEngine::getWindow() == SDL_GetKeyboardFocus());
}

int VDInput::isKeyUp(SDL_Keycode keyCode){
	return 0; //return ExIsKeyDown(keyCode) && ( VDEngine::getWindow() == SDL_GetKeyboardFocus() );
}

int VDInput::isKey(SDL_Keycode keyCode){
	return 0; //return ExIsKeyDown(keyCode) && ( VDEngine::getWindow() == SDL_GetKeyboardFocus() );
}

int VDInput::getButton(VDInput::Button button){
	return SDL_GetMouseState(nullptr,nullptr);
}

int VDInput::getButtonDown(VDInput::Button button){
	int x,y;
	return SDL_GetMouseState(&x, &y) == button;
}

int VDInput::getButtonUp(VDInput::Button button){
	int x,y;
	return SDL_GetMouseState(&x, &y) == button;
}




void VDInput::internal_update(){
	mdelta = VDInput::mousePosition() - pmdelta;
	pmdelta = VDInput::mousePosition();

	xdelta = VDInput::x();
	ydelta = VDInput::y();
	VDDebug::log("%d.%d\n", xdelta, ydelta);
}

