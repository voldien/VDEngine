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
#ifndef _VD_TRANSFORM_FEEDBACK_H_
#define _VD_TRANSFORM_FEEDBACK_H_ 1
#include"VDBufferObject.h"
#include"../VDDef.h"
#include"VDMesh.h"

/**
 *
 */
class VDDECLSPEC VDTransformFeedback : public VDBufferObject{
public:
	VDTransformFeedback(void);
	explicit VDTransformFeedback(unsigned int buffer);
	VDTransformFeedback(const VDTransformFeedback& feedback);
	~VDTransformFeedback(void);

	/**
	 *	Release resources assoicated.
	 */
	virtual void release(void);

	/**
	 *	@Return
	 */
	virtual bool VDAPIENTRY isValid(void)const;

	/**
	 *
	 */
	virtual int VDAPIENTRY getSize(void);

	/**
	 *
	 */
	virtual void VDAPIENTRY setSize(unsigned int nBytes, void* pValues, unsigned int flag);

	/**
	 *
	 */
	void VDAPIENTRY bind(void);

	/**
	 *
	 */
	void VDAPIENTRY unBind(void);



private: /*	Attributes	*/

	unsigned int trfb;

public:	/*	Static methods.	*/

	/**
	 *
	 */
	void VDAPIENTRY begin(VDMesh::Primitive primitiv);

	/**
	 *
	 */
	void VDAPIENTRY end(void);

	/**
	 *
	 */
	void VDAPIENTRY pause(void);

	/**
	 *
	 */
	void VDAPIENTRY resume(void);

};

#endif
