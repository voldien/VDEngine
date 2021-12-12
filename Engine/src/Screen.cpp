#include <Core/VDDisplay.h>
#include <Core/VDEngine.h>
#include <Core/VDEngineCore.h>
#include <Core/VDScreen.h>
#include <DataStructure/VDPoint.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>


int VDScreen::width(){
	int w,h;
	SDL_GetWindowSize((SDL_Window*)VDEngine::getWindow(), &w, &h);
	return w;
}

int VDScreen::height(){
	int w,h;
	SDL_GetWindowSize((SDL_Window*)VDEngine::getWindow(), &w, &h);
	return h;
}

float VDScreen::aspect(){
	int w,h;
	SDL_GetWindowSize((SDL_Window*)VDEngine::getWindow(), &w, &h);
	return (float)w / (float)h;
}


bool VDScreen::isFullScreen(){
	return engine.fullscreen != SDL_FALSE;
}

void VDScreen::setResolution(int width, int height, bool fullscreen){

	/*	*/
	SDL_SetWindowSize((SDL_Window*)VDEngine::getWindow(), width, height);

	/*	*/
	SDL_SetWindowFullscreen((SDL_Window*)VDEngine::getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
	engine.fullscreen = fullscreen;
}

int VDScreen::setResolution(VDDisplay::Resolution* resolution){

	SDL_DisplayMode mode = {0};

	mode.w = resolution->width;
	mode.h = resolution->height;
	mode.refresh_rate = resolution->refereshRate;

	SDL_SetWindowDisplayMode((SDL_Window*)VDEngine::getWindow(), &mode);

	return 1;
}


static int private_displayIndex = 0;
int VDScreen::setScreen(int index){
	SDL_Rect rect;
	private_displayIndex = index;

	SDL_GetDisplayBounds(index, &rect);

	SDL_SetWindowPosition((SDL_Window*)VDEngine::getWindow(), rect.x, rect.y);
}

int VDScreen::getScreenIndex(){
	return private_displayIndex;
}



void VDScreen::setLocation(int x, int y){
	SDL_SetWindowPosition((SDL_Window*)VDEngine::getWindow(), x, y);
}

void VDScreen::setLocation(const VDPoint& point){
	VDScreen::setLocation(point.x(), point.y());
}

VDPoint VDScreen::getLocation(){
	VDPoint point;
	SDL_GetWindowPosition((SDL_Window*)VDEngine::getWindow(), &point[0], &point[1]);
	return point;
}

void VDScreen::setCursorVisability(bool visable){
	SDL_ShowCursor(visable ? 1 : 0);
	engine.cursorVisible = visable;
}

bool VDScreen::isCursorVisible(){
	return engine.cursorVisible;
}
