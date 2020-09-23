#include <DataStructure/VDDoubleBufferedAllocator.h>
#include <DataStructure/VDStackAllactor.h>


VDDoubleBufferedAllocator::VDDoubleBufferedAllocator(void){
	this->m_curStack = 0;
	this->m_stack[0] = VDStackAllocator();
	this->m_stack[1] = VDStackAllocator();
}

VDDoubleBufferedAllocator::VDDoubleBufferedAllocator(const VDDoubleBufferedAllocator& doublebuffer){
	*this = doublebuffer;
}

VDDoubleBufferedAllocator::VDDoubleBufferedAllocator(unsigned int sizeBytes){
	this->m_curStack = 0;
	this->m_stack[0].alloc(sizeBytes);
	this->m_stack[1].alloc(sizeBytes);
}

VDDoubleBufferedAllocator::~VDDoubleBufferedAllocator(void){
	this->getStack(0)->clear();
	this->getStack(1)->clear();
}


void VDDoubleBufferedAllocator::alloc(unsigned int sizeBytes){
	this->m_stack[0].alloc(sizeBytes);
	this->m_stack[1].alloc(sizeBytes);
}

void VDDoubleBufferedAllocator::allocateAligned(unsigned int sizeBytes, int alignment){
	sizeBytes += (sizeBytes % alignment);
	this->alloc(sizeBytes);
}

void VDDoubleBufferedAllocator::clear(void){
	this->m_stack[this->m_curStack].clear();
}

unsigned int VDDoubleBufferedAllocator::getMarker(void)const{
	return this->m_stack[this->m_curStack].getMarker();
}

void* VDDoubleBufferedAllocator::fetch(unsigned int sizeBytes){
	return this->m_stack[this->m_curStack].fetch(sizeBytes);
}

void VDDoubleBufferedAllocator::freeToMarker(unsigned int marker){
	return this->m_stack[this->m_curStack].freeToMarker(marker);
}

void VDDoubleBufferedAllocator::swap(void){
	this->m_curStack = ~this->m_curStack & 0x1;
}

VDStackAllocator* VDDoubleBufferedAllocator::getCurrentStack(void){
	return &this->m_stack[this->m_curStack];
}


VDStackAllocator* VDDoubleBufferedAllocator::getStack(int index)const{
	return (VDStackAllocator*)&this->m_stack[index];
}

VDDoubleBufferedAllocator& VDDoubleBufferedAllocator::operator=(const VDDoubleBufferedAllocator& alloc){
	*this->getStack(0) = *alloc.getStack(0);
	*this->getStack(1) = *alloc.getStack(1);
	this->m_curStack = alloc.m_curStack;
	return *this;
}
