#include <Core/VDDebug.h>
#include <DataStructure/VDStackAllactor.h>
#include <malloc.h>
#include <cstring>


VDStackAllocator::VDStackAllocator(void){
	this->mData = NULL;
	this->mMarker = NULL;
	this->mSize = 0;
}

VDStackAllocator::VDStackAllocator(const VDStackAllocator& stack){
	this->mSize = 0;
	*this = stack;
}

VDStackAllocator::VDStackAllocator(unsigned int stackSizeBytes){
	this->mMarker = 0;
	this->mData = NULL;
	this->mSize = 0;
	this->alloc(stackSizeBytes);
}

VDStackAllocator::~VDStackAllocator(void){
	free(this->mData);
}

void* VDStackAllocator::alloc(unsigned int sizeBytes){
	mSize = sizeBytes;
	mData = realloc(mData, sizeBytes);
	if(!mData){
		VDDebug::errorLog("Failed to allocate %d kb.\n", ( sizeBytes / 1024 ) );
	}
	return mData;
}

unsigned int VDStackAllocator::getSize(void)const{
	return this->mSize;
}

void* VDStackAllocator::allocateAligned(unsigned int sizeBytes, int alignment){
	sizeBytes += (sizeBytes % alignment);
	return this->alloc(sizeBytes);
}

void VDStackAllocator::clear(void){
	this->mMarker = 0;
}

unsigned int VDStackAllocator::getMarker(void)const{
	return this->mMarker;
}

void* VDStackAllocator::fetch(unsigned int sizeBytes){
	void* p = this->mData + getMarker();
	this->mMarker += sizeBytes;
	return p;
}

void VDStackAllocator::freeToMarker(unsigned int marker){
	this->mMarker = marker;
}

VDStackAllocator& VDStackAllocator::operator=(const VDStackAllocator& alloc){
	this->alloc(alloc.getSize());
	memcpy(this->mData, alloc.mData, alloc.getMarker());
	return *this;
}
