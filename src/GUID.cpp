#include <Core/VDGUID.h>

unsigned long long int VDGUID::nextID = 0;
int VDGUID::bitSize = 32;

unsigned long long int VDGUID::getNextID(void){
	return VDGUID::nextID++;
}

void VDGUID::setNextID(unsigned long long int id){
	VDGUID::nextID = id;
}
