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
#ifndef _VD_UNIFORM_BUFFER_H_
#define _VD_UNIFORM_BUFFER_H_ 1
#include "VDBufferObject.h"
#include "../VDDef.h"

/**
 *	Uniform shader buffer. Used for global
 *	shader uniform storage.
 */
class VDDECLSPEC VDUniformBuffer : public VDBufferObject{
public:
	VDUniformBuffer(void);
	explicit VDUniformBuffer(unsigned int buffer);
	VDUniformBuffer(const VDUniformBuffer& buffer);
	virtual ~VDUniformBuffer(void);

	/**
	 *	Release resources assoicated.
	 */
	virtual void release(void);

	/**
	 *	Determine if object is valid.
	 *
	 *	@Return true if valid.
	 */
	virtual bool VDAPIENTRY isValid(void)const;

	/**
	 *	Get current size of the buffer.
	 */
	int VDAPIENTRY getSize(void);

	/**
	 *	Resize buffer.
	 */
	virtual void VDAPIENTRY setSize(int size);

	/**
	 *	Resize and assign buffer value.
	 */
	virtual void VDAPIENTRY setSize(unsigned int nBytes, void* pValues, unsigned int flag);

	/**
	 *	Write to buffer.
	 */
	void VDAPIENTRY write(const void* pbuffer, int rSize);

	/**
	 *	Writt to buffer.
	 */
	void VDAPIENTRY write(const void* pbuffer, int offset, int rSize);

	/**
	 *	Read from buffer.
	 */
	void* VDAPIENTRY read(int rSize);

	/**
	 *	Bind buffer.
	 */
	void VDAPIENTRY bind(void);

	/**
	 *	Bind buffer to base index.
	 */
	void VDAPIENTRY bindBase(unsigned int index);

	/**
	 *	Get buffer unique ID.
	 */
	int VDAPIENTRY getUniformBuffer(void)const;

private:	/*	Attributes.	*/

	int mUniBuffer;	/*	*/
};

#endif
