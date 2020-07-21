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
#ifndef _VD_BUFFER_OBJECT_H_
#define _VD_BUFFER_OBJECT_H_ 1
#include"../VDSystem.h"
#include"../Asset/VDAssetObject.h"

/**
 *	Base object class for OpenGL buffer object.
 */
class VDDECLSPEC VDBufferObject : public VDAssetObject{
public:

	/**
	 *	OpenGL buffer target enum.
	 */
	enum Target{
		eUniform = 0x8A11,				/*	GL_UNIFORM_BUFFER	*/
		eShaderStorage = 0x90D2,		/*	GL_SHADER_STORAGE_BUFFER.	*/
		eTransformFeedback,				/*	GL_TRANSFORM_FEEDBACK.	*/
		eArrray = 0x8892,				/*	GL_ARRAY_BUFFER.	*/
		eElementArray,					/*	GL_ELEMENT_ARRAY_BUFFER.	*/
		ePixelBufferObject = 0x88EB,	/*	GL_PIXEL_PACK_BUFFER	*/
		ePixelUnPackObject = 0x88EC,	/*	GL_PIXEL_UN:PACK_BUFFER	*/
	};

	VDBufferObject(void);
	virtual ~VDBufferObject(void);

	/**
	 *	Release
	 */
	virtual void VDAPIENTRY release(void);

	/**
	 *	Determine if buffer is valid.
	 *
	 *	@Return true if valid otherwise false.
	 */
	virtual bool VDAPIENTRY isValid(void)const = 0;

	/**
	 *
	 */
	virtual int VDAPIENTRY getSize(void) = 0;

	/**
	 *	Set size.
	 */
	virtual void VDAPIENTRY setSize(unsigned int nBytes, void* pValues, unsigned int flag) = 0;

	/**
	 *
	 */
	inline void setTarget(unsigned int target){
		this->target = target;
	}

	/**
	 *
	 */
	inline unsigned int getTarget(void)const{
		return this->target;
	}

protected:	/*	Attributes.	*/

	unsigned int target;	/*	Buffer target.	*/
	int bindbase;			/*	Base buffer binded too.	*/
};

#endif
