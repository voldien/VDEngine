#include <Core/VDConfig.h>
#include <Core/VDDebug.h>
#include <DataStructure/VDSize.h>
#include <Misc/VDFile.h>
#include <SDL2/SDL_stdinc.h>
#include <VDSystemInfo.h>
#include <cstdio>
#include <string>

void VDConfigure::defaultConfig(VDConfigure::VDConfig* config) {
	VDSize size;

	/**/
	config->width = size.width();
	config->height = size.height();
	config->resizable = SDL_TRUE;
	config->fullscreen = SDL_FALSE;
	config->debug = SDL_FALSE;

	/**/
	config->ntaskcores = VDSystemInfo::getCPUCoreCount();

	/**/
	config->verbose = SDL_TRUE;
}
