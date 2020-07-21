#include <Core/VDDisplay.h>
#include <Core/VDEngine.h>
#include <DataStructure/VDSize.h>
#include <malloc.h>
#include <SDL2/SDL_video.h>
#include <cassert>
#include <cstring>

int VDDisplay::getNumDisplays(void){
	return SDL_GetNumVideoDisplays();
}

void VDDisplay::getPrimaryScreenResolutions(int* num, Resolution** resolutions){

	int curdisp = 0;

	curdisp = SDL_GetWindowDisplayIndex((SDL_Window*)VDEngine::getWindow());
	VDDisplay::getScreenResolutions(curdisp, num, resolutions);
}

void VDDisplay::getScreenResolutions(int index, int* num, Resolution** resolutions){

	int curdisp;
	int nummode;
	SDL_DisplayMode mode;
	int i;

	/*	*/
	curdisp = index;
	nummode = SDL_GetNumDisplayModes(curdisp);

	/*	*/
	*num = nummode;
	*resolutions = (VDDisplay::Resolution*)malloc(sizeof(Resolution) * nummode);
	assert(*resolutions);
	memset(*resolutions, 0, sizeof(Resolution) * nummode);

	/*	*/
	for( i = 0; i < nummode; i++){
		if( SDL_GetDisplayMode(curdisp, i, &mode) > 0){
			( *resolutions )[i].displayIndex = curdisp;
			( *resolutions )[i].width = mode.w;
			( *resolutions )[i].height = mode.h;
			( *resolutions )[i].refereshRate = mode.refresh_rate;
		}
	}

}

VDSize VDDisplay::getPrimaryScreenSize(void){

	VDSize size = VDSize(0, 0);
	SDL_DisplayMode mode = { 0 };

	if( SDL_GetDesktopDisplayMode( 0 , &mode) == 0){
		size.setWidth( mode.w );
		size.setHeight( mode.h );
	}

	return size;
}
