/*
    VDEngine virtual dimension game engine.
    Copyright (C) 2014  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _VD_DOUBLE_BUFFERED_ALLACATOR_H_
#define _VD_DOUBLE_BUFFERED_ALLACATOR_H_ 1
#include"VDStackAllactor.h"

/**
 *	DoubleBufferedAllocator is two allocate buffer.
 */
class VDDECLSPEC VDDoubleBufferedAllocator{
public:

	VDDoubleBufferedAllocator(void);
	VDDoubleBufferedAllocator(const VDDoubleBufferedAllocator& doublebuffer);
	explicit VDDoubleBufferedAllocator(unsigned int sizeBytes);
	~VDDoubleBufferedAllocator(void);

	/**
	 *	Allocate n number of bytes.
	 */
	void VDAPIENTRY alloc(unsigned int sizeBytes);

	/**
	 *	Allocate n number of bytes aligned.
	 *
	 *	@Return first memory address.
	 */
	void VDAPIENTRY allocateAligned(unsigned int sizeBytes, int alignment);

	/**
	 *	Set marker to zero.
	 */
	void VDAPIFASTENTRY clear(void);

	/**
	 *	Return marker offset.
	 *	@Return
	 */
	unsigned int VDAPIENTRY getMarker(void)const;

	/**
	 *	Fetch block of memory.
	 */
	void* VDAPIENTRY fetch(unsigned int sizeBytes);

	/**
	 *	Release everything to marker.
	 */
	void VDAPIFASTENTRY freeToMarker(unsigned int marker);

	/**
	 *	Swap buffers.
	 */
	void VDAPIENTRY swap(void);

	/**
	 *	Get current stack buffer.
	 */
	VDStackAllocator* VDAPIENTRY getCurrentStack(void);

	/**
	 *	Get current by index.
	 */
	VDStackAllocator* VDAPIENTRY getStack(int index)const;

	/**
	 *	@Return
	 */
	VDDoubleBufferedAllocator& operator=(const VDDoubleBufferedAllocator& alloc);

private:	/*	Attributes.	*/

	/*
	 *
	 */
	unsigned int m_curStack;

	/*
	 *
	 */
	VDStackAllocator m_stack[2];
};

#endif
