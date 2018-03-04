#include <Core/VDLibrary.h>
#include <stddef.h>
#include <SDL2/SDL_loadso.h>


VDLibrary::VDLibrary(void){
	this->mlib = NULL;
}

VDLibrary::VDLibrary(const char* clibrary){
	this->mlib = NULL;
	this->open(clibrary);
}

VDLibrary::VDLibrary(const VDLibrary& library){
	*this = library;
}

VDLibrary::~VDLibrary(void){
	this->close();
}

bool VDLibrary::open(const char* clibrary){
	this->mlib = SDL_LoadObject(clibrary);
	return this->mlib != NULL;
}

void VDLibrary::close(void){
	SDL_UnloadObject(this->mlib);
}

void* VDLibrary::getfunc(const char* pProcName){
	return SDL_LoadFunction(this->mlib, pProcName);
}
