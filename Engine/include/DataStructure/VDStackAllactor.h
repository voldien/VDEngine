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
#ifndef _VD_STACK_ALLACTOR_H_
#define _VD_STACK_ALLACTOR_H_ 1
#include"../VDDef.h"

/**
 *	Single stack buffer.
 */
class VDDECLSPEC VDStackAllocator{
public:

	VDStackAllocator(void);
	VDStackAllocator(const VDStackAllocator& stack);
	explicit VDStackAllocator(unsigned int stackSizeBytes);
	~VDStackAllocator(void);

	/**
	 *	Allocate n number of bytes.
	 *	@Return first memory address.
	 */
	void* VDAPIENTRY alloc(unsigned int sizeBytes);

	/**
	 *	Get size of the allocated data block
	 *	in bytes.
	 */
	unsigned int getSize(void)const;

	/**
	 *	Allocate aligned memory block.
	 *	@Return first memory address.
	 */
	void* VDAPIENTRY allocateAligned(unsigned int sizeBytes, int alignment);

	/**
	 *	Set marker to zero.
	 */
	void VDAPIFASTENTRY clear(void);


	/**
	 *	@Return marker offset.
	 */
	unsigned int VDAPIENTRY getMarker(void)const;

	/**
	 *	@Return non null pointer if successfully.
	 */
	void* VDAPIFASTENTRY fetch(unsigned int sizeBytes);

	/**
	 *	Release everything to marker.
	 */
	void VDAPIFASTENTRY freeToMarker(unsigned int marker);

	/**
	 *	@Return
	 */
	VDStackAllocator& operator=(const VDStackAllocator& alloc);

	/**
	 *
	 *	@Return
	 */
	bool operator==(const VDStackAllocator& alloc);

	/**
	 *
	 *	@Return
	 */
	bool operator!=(const VDStackAllocator& alloc);

private:	/*	Attributes.	*/

	void* mData;			/*	*/
	unsigned int mSize;		/*	*/
	unsigned int mMarker;	/*	*/
};

#endif
